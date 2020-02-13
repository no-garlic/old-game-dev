// ----------------------------------------------------------------------------
// File: Properties.h
// Desc: This class encapsulates the storage of configuration data. It allows 
//       this data to be read and saved to a stream. It also allows quick 
//       retrieval of data.
// Properties Stream Format:
//      - All empty lines and lines beginning with ## are ignored.
//      - All lines beginning with a # (and not ##) are comments and are 
//        associated with the next section or key read.
//      - All lines beginning with [ denote the start of the section. The 
//        section's name is enclosed within the [] pair. All keys following 
//        belong to this section until a new section starts
//      - Any other line is a key. The key is the string until the first : or = 
//        is found, trimmed on both sides to remove whitespace. The value is 
//        whatever is left on the line, to the right of the : or = (trimmed 
//        for whitespace). This may be an empty string if the : or = character 
//        is not found on the line.
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef PROPERTIES_H
#define PROPERTIES_H


// ----------------------------------------------------------------------------
// Includes for the properties class
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include "Common/OSClasses.h"
#include "Common/Logging.h"
#include "common/Exceptions.h"
#include <map>
#include <string>
#include <vector>


// ----------------------------------------------------------------------------
// Name: Properties (class)
// Desc: This class encapsulates the storage of configuration data. It allows 
//       this data to be read and saved to a stream. It also allows quick 
//       retrieval of data.
// ----------------------------------------------------------------------------
class Properties
{
public:
    // ------------------------------------------------------------------------
    // Constructors, including a copy constructor, and destructor
    // ------------------------------------------------------------------------
             Properties();
             Properties(const Properties &other);
    explicit Properties(const std::string &filename);
            ~Properties();

    // ------------------------------------------------------------------------
    // Assignment operator, as we are providing a copy constrctor
    // ------------------------------------------------------------------------
    Properties  &operator=(const Properties &other);

    
    // ------------------------------------------------------------------------
    // Set the defaults using another Properties object
    // ------------------------------------------------------------------------
    void        SetDefaults(const Properties *pdefaults);

    
    // ------------------------------------------------------------------------
    // Load / Save the properties
    // ------------------------------------------------------------------------
    void        Open(std::istream &in);
    void        Open(const std::string &filename);
    void        Save(std::ostream &out, const std::string &header);
    void        Save(const std::string &filename, const std::string &header);
    void        Dump(std::ostream &out);

    
    // ------------------------------------------------------------------------
    // Getting properties
    // ------------------------------------------------------------------------
    template <typename T>
    T           GetProperty(const std::string &section, 
                            const std::string &key) const;
    template <typename T>
    T           GetProperty(const std::string &section, 
                            const std::string &key, T default_value) const;

    
    // ------------------------------------------------------------------------
    // Setting properties
    // ------------------------------------------------------------------------
    template <typename T>
    void        SetProperty(const std::string &section, 
                            const std::string &key, T value);

    
    // ------------------------------------------------------------------------
    // Setting comments
    // ------------------------------------------------------------------------
    void        SetSectionComments(const std::string &section, 
                                   const std::vector<std::string> &comments);
    void        SetKeyComments(    const std::string &section, 
                                   const std::string &key, 
                                   const std::vector<std::string> &comments);

    
    // ------------------------------------------------------------------------
    // Removal
    // ------------------------------------------------------------------------
    bool        RemoveSection(const std::string &section);
    bool        RemoveKey(const std::string &section, const std::string &key);

    
    // ------------------------------------------------------------------------
    // Enumeration of sections and keys
    // ------------------------------------------------------------------------
    std::vector<std::string>    ListSections() const;
    std::vector<std::string>    ListKeys(const std::string &section) const;
    bool                        IsProperty(const std::string &section, const std::string &key) const;

private:
    // ------------------------------------------------------------------------
    // The type that we use to store the section/key pair
    // ------------------------------------------------------------------------
    typedef   std::pair<std::string, std::string>                                           SectionKeyPair;
    typedef   std::map<std::string, std::vector<std::string> >                              SectionMap;
    typedef   std::map<SectionKeyPair, std::pair<std::string, std::vector<std::string> > >  KeyMap;

private:
    // ------------------------------------------------------------------------
    // Privates for this class
    // ------------------------------------------------------------------------
    SectionMap          m_section_map;      // The map to store our sections in
    KeyMap              m_key_map;          // The maps to store our keys in
    Properties         *m_pdefaults;        // Keep track of our default values
    mutable OS::Mutex   m_mutex;            // The mutex for thread-safety

}; // class Properties


// ----------------------------------------------------------------------------
// Name: Properties::GetProperty
// Temp: The property type
// Desc: Retrieves a property from the configuration data. If the property is 
//       found the value is cast to the desired type and returned. If the key or
//       section does not exist the default properties object is used to 
//       retrieve the value.  If there is no default property either then an 
//       exception is thrown.
// Parm: const std::string &section - the section to get the property from - may
//       be "" for the untitled section
// Parm: const std::string &key     - the key to find
// Retn: T                          - the property value
// ----------------------------------------------------------------------------
template <typename T>
T Properties::GetProperty(const std::string &section, const std::string &key) const
{
    OS::MutexLock l(m_mutex);

    // First we try and find the key, and check that it exists
    KeyMap::const_iterator iter = m_key_map.find(SectionKeyPair(section, key));
    if (iter == m_key_map.end())
    {
        // The key doesn't exist. If we have any defaults, check them
        if (m_pdefaults)
            return m_pdefaults->GetProperty<T>(section, key);

        // Otherwise, throw an exception
        throw InvalidParameterException(FLSTAMP) << 
            "No value could be found for the [" << section << " - " << key << "] key.";
    } // if

    // Now try and cast the resultant string to the requested type
    T result;
    try
    {
        result = LexicalCast<T>(iter->second.first);
    } // try
    catch (GeneralException &e)
    {
        // Create the description string, and add a trace
        std::string desc = "Attempting to cast [" + section + " - " + key + "] value of " + 
            iter->second.first + " to requested type failed";
        e.AddStackTrace(FLSTAMP, desc.c_str());
        throw e;
    } // catch

    return result;
} // GetProperty


// ----------------------------------------------------------------------------
// Name: Properties::GetProperty
// Temp: The property type
// Desc: Retrieves a property from the configuration data. If the property is 
//       found the value is cast to the desired type and returned. If the key or
//       section does not exist the default properties object is used to 
//       retrieve the value. If this fails too the supplied default value is 
//       returned.
// Parm: const std::string &section - the section to get the property from - may
//       be "" for the untitled section
// Parm: const std::string &key     - the key to find
// Parm: T default_value            - the default property value
// Retn: T                          - the property value
// ----------------------------------------------------------------------------
template <typename T>
T Properties::GetProperty(const std::string &section, const std::string &key, T default_value) const
{
    OS::MutexLock l(m_mutex);

    // First we try and find the key, and check that it exists
    KeyMap::const_iterator iter = m_key_map.find(SectionKeyPair(section, key));
    if (iter == m_key_map.end())
    {
        // If we have some defaults, use those, otherwise just return the
        // default value
        return m_pdefaults ? m_pdefaults->GetProperty(section, key, default_value) : default_value;
    } // if

    // Now try and cast the resultant string to the requested type
    try
    {
        return LexicalCast<T>(iter->second.first);
    } // try
    catch (GeneralException &e)
    {
        // Add a trace and log the exception
        // Create the description string, and add a trace
        std::string desc = "Attempting to cast [" + section + " - " + key + "] value of " + 
            iter->second.first + " to requested type failed";
        e.AddStackTrace(FLSTAMP, desc.c_str());
        Trace::g_plog->LogException(e);
    } // catch

    return default_value;
} // GetProperty


// ----------------------------------------------------------------------------
// Name: Properties::SetProperty
// Temp: The type of the value that we are setting.
// Desc: Sets the property/value associated with the key in the section 
//       specified. If the value did not already exist then it is created.
// Parm: const std::string &section - The section to set the key in.  May be "" 
//       for the untitled section.
// Parm: const std::string &key     - The key to set the value against
// Parm: T value                    - the value to store
// ----------------------------------------------------------------------------
template <typename T>
void Properties::SetProperty(const std::string &section, const std::string &key, T value)
{
    OS::MutexLock l(m_mutex);

    // Firstly check that this section exists. If not, we need to add an
    // entry for it
    if (m_section_map.find(section) != m_section_map.end())
        m_section_map.insert(SectionMap::value_type(section, SectionMap::mapped_type()));

    // Now set the value in the key map, preserving comments if it
    // already exists
    SectionKeyPair   skp(section, key);
    KeyMap::iterator iter = m_key_map.find(skp);

    // Set up our new value
    KeyMap::mapped_type mt(LexicalCast<std::string>(value), std::vector<std::string>());

    // If we already had comments, preserve them
    if ( iter != m_key_map.end())
        mt.second = iter->second.second;

    // Change the contents of the map to reflect this setting
    m_key_map[skp] = mt;
} // SetProperty


#endif // PROPERTIES_H

// -- EOF

