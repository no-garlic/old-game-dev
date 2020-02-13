// ----------------------------------------------------------------------------
// File: Properties.cpp
// Desc: Properties class just like a ini file, only better
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


// ----------------------------------------------------------------------------
// Includes for the properties class
// ----------------------------------------------------------------------------
#include "Common/Properties.h"
#include <algorithm>
#include <fstream>
#include <time.h>


// ----------------------------------------------------------------------------
// Name: Properties::Properties
// Desc: Default constructor
// ----------------------------------------------------------------------------
Properties::Properties()
{
    m_pdefaults = 0;
} // Properties


// ----------------------------------------------------------------------------
// Name: Properties::Properties
// Desc: Constructor that initializes using a file. This is provided simply for 
//       convenience, and can be replicated through using the default 
//       constructor and the Open() function.
// Parm: const std::string &filename - the filename of the properties to load
// ----------------------------------------------------------------------------
Properties::Properties(const std::string &filename)
{
    m_pdefaults = 0;

    // Open the file specified
    Open(filename);
} // Properties


// ----------------------------------------------------------------------------
// Name: Properties::Properties
// Desc: Copy constructor. Used when we take a copy of a Properties object to 
//       use as our default properties (see SetDefaults(). This copies the maps,
//       and clones the default Properties object in use, if there is one.
// Parm: const Properties &other - the object to copy
// ----------------------------------------------------------------------------
Properties::Properties(const Properties &other)
{
    // Copy the maps, create a new default Properties object, and don't do
    // anything about the mutex
    m_section_map   = other.m_section_map;
    m_key_map       = other.m_key_map;
    m_pdefaults     = other.m_pdefaults ? new Properties(*other.m_pdefaults) : 0;
} // Properties


// ----------------------------------------------------------------------------
// Name: Properties::~Properties
// Desc: Destructor
// ----------------------------------------------------------------------------
Properties::~Properties()
{
    // Simply check to see if we have a Properties object that we are using
    // for default value, and delete it if so.
    delete m_pdefaults;
} // ~Properties


// ----------------------------------------------------------------------------
// Name: Properties::operator=
// Desc: Assignment operator - copies all properties just like the copy 
//       constructor
// Parm: const Properties &other - the properties to copy
// Retn: Properties &            - a reference to this class
// ----------------------------------------------------------------------------
Properties &Properties::operator=(const Properties &other)
{
    // Copy the maps, create a new default Properties object, and don't do
    // anything about the mutex
    m_section_map = other.m_section_map;
    m_key_map     = other.m_key_map;
    m_pdefaults   = other.m_pdefaults ? new Properties(*other.m_pdefaults) : 0;

    return *this;
} // operator=


// ----------------------------------------------------------------------------
// Name: Properties::SetDefaults
// Desc: Sets the default properties to use if a property cannot be found in our
//       own map. This involves first releasing any resources associated with 
//       our current default Properties object, and storing a copy of the 
//       incoming new default Properties object.
// Parm: const Properties *pdefaults - Pointer to the new Properties object to 
//       use for default values. This is cloned. A value of NULL instructs the 
//       object not to use any default values.
// ----------------------------------------------------------------------------
void Properties::SetDefaults(const Properties *pdefaults)
{
    OS::MutexLock l(m_mutex);

    // If we already have a default Properties object, destroy it.
    if (m_pdefaults)
    {
        delete m_pdefaults;
        m_pdefaults = 0;
    } // if

    // If ths incoming pointer is valid, create a copy of the object pointed
    // to.
    if (pdefaults)
        m_pdefaults = new Properties(*pdefaults);
} // SetDefaults


// ----------------------------------------------------------------------------
// Name: Properties::Open
// Desc: Opens a stream provided and reads out the properties infromation, in 
//       the format required be a properties stream.
// Parm: std::istream &in - the stream to read the properties from, typically 
//       will be a file
// ----------------------------------------------------------------------------
void Properties::Open(std::istream &in)
{
    OS::MutexLock l(m_mutex);

    // Clear our current contents
    m_section_map.clear();
    m_key_map.clear();

    std::string              line;
    std::string              curr_sec = "";
    std::vector<std::string> comments;

    m_section_map.insert(SectionMap::value_type("", comments));

    // Keep on reading in a line until we get to the end of the file
    while (!in.eof() && !in.fail() && !in.bad())
    {
        // Read in the line
        std::getline(in, line);

        // Trim the line to remove all leading and trailing whitespace
        line.erase(line.begin(), std::find_if (line.begin(), line.end(), std::not1(std::ptr_fun(&iswspace))));
        line.erase(std::find_if (line.rbegin(), line.rend(), std::not1(std::ptr_fun(&iswspace))).base(), line.end());

        // Our behaviour now depends on the what the line now holds
        if (!line.empty())
        {
            if (line[0] == '[')
            {
                // Now find the next ] to finish the section name
                line = line.substr(1, line.find(']') - 1);

                // Add this section name, along with any associated comments
                // and clear our list of comments
                m_section_map.insert(SectionMap::value_type(line, comments));
                curr_sec = line;
                comments.clear();
            }
            else if (line[0] == '#')
            {
                // A comment - read in the next character too. If it is a
                // white space we will ignore it, but if it is another
                // hash we will ignore the entire line
                if (line[1] != '#')
                {
                    // Remove all whitespace, including the leading hash, so
                    // start the search from the second character
                    line.erase(line.begin(), std::find_if (line.begin() + 1, line.end(), std::not1(std::ptr_fun(&iswspace))));

                    // This now forms a comment, so add it to the vector
                    comments.push_back(line);
                } // if
            }
            else
            {
                // Must be a key. Read in until the next = or :
                std::string::size_type equals_pos = line.find_first_of(":=");
                std::string            key        = line.substr(0, equals_pos);

                // Trim this key so it has no whitespace on the right either
                key.erase(std::find_if (key.rbegin(), key.rend(), std::not1(std::ptr_fun(&iswspace))).base(), key.end());

                // Now the value is what is left ...
                std::string value = (equals_pos == std::string::npos) ? "" : line.substr(equals_pos);

                // ... without the = or : ...
                if (!value.empty())
                    value = value.substr(1);

                // ... and trimmed for leading whitespace
                value.erase(value.begin(), std::find_if (value.begin(), value.end(), std::not1(std::ptr_fun(&iswspace))));

                // Now add the key/value pair, with comments
                m_key_map[SectionKeyPair(curr_sec, key)] = KeyMap::mapped_type(value, comments);
                comments.clear();
            } // if
        } // if
    } // while
} // Open


// ----------------------------------------------------------------------------
// Name: Properties::Open
// Desc: Opens a file and reads in the configuration data from it, presuming 
//       that the format is that required. This function is provided mainly for 
//       convenience. The equivalent is to open a file stream and call the other
//       Open() function.
// Parm: const std::string &filename - the file to open
// ----------------------------------------------------------------------------
void Properties::Open(const std::string &filename)
{
    // Open a file, and use this as the ostream
    std::ifstream file(filename.c_str());

    // Check that the file is open
    if (file.bad() || file.fail())
        throw InvalidParameterException(FLSTAMP) << "Error opening file: " << filename;

    // Read the file in
    Open(file);
} // Open



//
//  Parameters:
//      std::ostream &out - The output stream to save to.
//      const std::string &header - The string to use in the header line.

// ----------------------------------------------------------------------------
// Name: Properties::Save
// Desc: Saves the configuration data to the output stream provided in the 
//       standard format. In addition, the first line will be a discardable 
//       comment line with the header string provided, and the second line will 
//       be a discardable comment with a timestamp.
// Parm: std::ostream &out          - the output stream to save to
// Parm: const std::string &header  - the string to use in the header line
// ----------------------------------------------------------------------------
void Properties::Save(std::ostream &out, const std::string &header)
{
    OS::MutexLock l(m_mutex);

    // Write the header as a comment
    if (!header.empty())
        out << "## " << header << std::endl;

    // Time stamp the file
    {
        time_t now = time(0);

        // Convert this time into local time
        tm local_now = *localtime(&now);

        // Convert this to a string and output to the stream
        out << "## " << asctime(&local_now) << std::endl;
    } // scope

    // Now we are ready to print all of our keys. We can do this simply
    // by iterating through the keys map, which is already sorted for us.
    // We need to keep track of our current section, in case it changes.
    std::string curr_sec = "";
    for (KeyMap::iterator iter = m_key_map.begin(); iter != m_key_map.end(); ++iter)
    {
        // Check the section to see if we have to start a new section
        if (iter->first.first != curr_sec)
        {
            // Add another blank line
            out << std::endl;

            // New section - write its comments, and then it
            SectionMap::iterator sec_iter = m_section_map.find(iter->first.first);
            if (sec_iter != m_section_map.end())
            {
                // Write the comments
                for (unsigned int i = 0; i < sec_iter->second.size(); ++i)
                    out << "# " << sec_iter->second[i] << std::endl;
            } // if

            // Write the section name
            out << "[" << iter->first.first << "]" << std::endl;

            // Update our copy of the current section
            curr_sec = iter->first.first;
        } // for

        // Add the key to the file
        // Add the comments first, if there are any
        for (unsigned int i = 0; i < iter->second.second.size(); ++i)
            out << "# " << iter->second.second[i] << std::endl;

        // Write the key and value
        out << iter->first.second;
        if (!iter->second.first.empty())
            out << "=" << iter->second.first;
        out << std::endl;
    } // for
} // Save


// ----------------------------------------------------------------------------
// Name: Properties::Save
// Desc: Saves the configuration data to a file. This is provided for 
//       convenience. The equivalent would be to create the output file stream 
//       and call the other Save() function.
// Parm: const std::string &filename - the filname of the file to save to
// Parm: const std::string &header   - the string to use for the header comment
// ----------------------------------------------------------------------------
void Properties::Save(const std::string &filename, const std::string &header)
{
    // Create the file, and use this as the istream
    std::ofstream file(filename.c_str());

    // Check that the file is open
    if (file.bad() || file.fail())
        throw InvalidParameterException(FLSTAMP) << "Error opening file: " << filename;

    // Save the file
    Save(file, header);
} // Save


// ----------------------------------------------------------------------------
// Name: Properties::SetSectionComments
// Desc: Sets the comments associated with a section (and are listed prior to it
//       in the saved file). If the section does not exist it is created.
// Parm: const std::string &section                - the section to add the 
//       comments to
// Parm: const std::vector<std::string> &comments  - the list of comments to add
//       , one comment per line.
// ----------------------------------------------------------------------------
void Properties::SetSectionComments(const std::string &section, const std::vector<std::string> &comments)
{
    OS::MutexLock l(m_mutex);

    // If the section does not exist we will add it
    m_section_map[section] = comments;
} // SetSectionComments


// ----------------------------------------------------------------------------
// Name: Properties::SetKeyComments
// Desc: Sets the comments associated with a key (and are listed prior to it in 
//       the saved file). If the key does not exist then no action is taken - we
//       cannot create the key because we don't have a value!
// Parm: const std::string &section                - the section that the key 
//       can be found in
// Parm: const std::string &key                    - the key to add the comments
//       to
// Parm: const std::vector<std::string> &comments  - the list of comments to add
//       , one comment per line.
// ----------------------------------------------------------------------------
void Properties::SetKeyComments(const std::string &section, const std::string &key, const std::vector<std::string> &comments)
{
    OS::MutexLock l(m_mutex);

    // Try and get an iterator to this key
    KeyMap::iterator iter = m_key_map.find(SectionKeyPair(section, key));

    // Only set the comments if this key exists
    if (iter != m_key_map.end())
        iter->second.second = comments;
} // SetKeyComments


// ----------------------------------------------------------------------------
// Name: Properties::RemoveSection
// Desc: Removes a section, all of it's keys, and all of it's comments
// Parm: const std::string &section - the section to remove
// Retn: bool                       - true if successfully removed
// ----------------------------------------------------------------------------
bool Properties::RemoveSection(const std::string &section)
{
    OS::MutexLock l(m_mutex);

    // Check our section map to see that we exist
    SectionMap::iterator sec_iter;
    if ((sec_iter = m_section_map.find(section)) != m_section_map.end())
    {
        // Remove all keys for this section first, while the section map
        // iterator is still valid
        KeyMap::iterator key_iter(m_key_map.begin());
        while (key_iter != m_key_map.end())
        {
            // Remove this entry if it belongs to this section
            if (key_iter->first.first == section)
                m_key_map.erase(key_iter++);
            else
                ++key_iter;
        } // while

        // Remove the entry from the section map
        m_section_map.erase(sec_iter);

        return true;
    } // if

    // The section didn't exist
    return false;
} // RemoveSection


// ----------------------------------------------------------------------------
// Name: Properties::RemoveKey
// Desc: Removes a key from a section, and its comments. If this results in a 
//       section being empty the section is removed too.
// Parm: const std::string &section - the section to remove
// Parm: const std::string &key     - the key to remove
// Retn: bool                       - true if successful
// ----------------------------------------------------------------------------
bool Properties::RemoveKey(const std::string &section, const std::string &key)
{
    OS::MutexLock l(m_mutex);

    // This is a simply call to the map's erase function.
    if (m_key_map.erase(SectionKeyPair(section, key)) == 0)
        return false;

    // Check that there still exists a key for this section, otherwise we
    // need to remove it from the section map too
    KeyMap::iterator iter(m_key_map.begin());
    while (iter != m_key_map.end())
    {
        if (iter->first.first == section)
            break;
    } // while

    // If we didn't find another key we need to remove the section
    if (iter == m_key_map.end())
        m_section_map.erase(section);

    // We successfully removed the key!
    return true;
} // RemoveKey


// ----------------------------------------------------------------------------
// Name: Properties::ListSections
// Desc: Lists all of the sections in the contained configuration data, not 
//       including the default properties.
// Retn: std::vector<std::string> - the list of section names
// ----------------------------------------------------------------------------
std::vector<std::string> Properties::ListSections() const
{
    OS::MutexLock l(m_mutex);

    // Iterator through the section map and copy into the vector
    std::vector<std::string> sections_vec;
    for (SectionMap::const_iterator iter = m_section_map.begin(); iter != m_section_map.end(); ++iter)
        sections_vec.push_back(iter->first);

    return sections_vec;
} // ListSections


// ----------------------------------------------------------------------------
// Name: Properties::ListKeys
// Desc: Lists all of the keys in a specified section, not including the default
//       properties.
// Parm: const std::string &section - the section to list the keys for
// Retn: std::vector<std::string>   - the list of keys
// ----------------------------------------------------------------------------
std::vector<std::string> Properties::ListKeys(const std::string &section) const
{
    OS::MutexLock l(m_mutex);

    // Iterator through the section map and copy into the vector if the
    // section is correct
    std::vector<std::string> keys_vec;
    for (KeyMap::const_iterator iter = m_key_map.begin(); iter != m_key_map.end(); ++iter)
    {
        if (iter->first.first == section)
            keys_vec.push_back(iter->first.second);
    } // for

    return keys_vec;
} // ListKeys


// ----------------------------------------------------------------------------
// Name: Properties::IsProperty
// Desc: Determines if the section, key pair exists in the list of properties. 
//       Default properties are not checked.
// Parm: const std::string &section - the section
// Parm: const std::string &key     - the key
// Retn: bool                       - true if the property exists
// ----------------------------------------------------------------------------
bool Properties::IsProperty(const std::string &section, const std::string &key) const
{
    return m_key_map.find(SectionKeyPair(section, key)) != m_key_map.end();
} // IsProperty


// ----------------------------------------------------------------------------
// Name: Properties::Dump
// Desc: A debugging function provided to get a quick dump of the properties 
//       being stored. The default properties are not displayed. Typically this 
//       information would be dumped to cout. Each key and its associated value 
//       are displayed.
// Parm: std::ostream &out - the output stream
// ----------------------------------------------------------------------------
void Properties::Dump(std::ostream &out)
{
    OS::MutexLock l(m_mutex);

    // Header
    out << "Properties dump." << std::endl << std::endl;

    // Iterate through the list of sections, and get all of the keys
    // for each section, and then iterate through each key, dumping their
    // values
    std::vector<std::string> sections = ListSections();
    for (unsigned int i = 0; i < sections.size(); ++i)
    {
        out << "[" << sections[i] << "]" << std::endl;

        // Get all the keys for this section
        std::vector<std::string> keys = ListKeys(sections[i]);
        for (unsigned int j = 0; j < keys.size(); ++j)
        {
            // Find the entry in the key map, and dump it
            KeyMap::iterator iter = m_key_map.find(SectionKeyPair(sections[i], keys[j]));
            if (iter != m_key_map.end())
                out << keys[i] << " - " << iter->second.first << std::endl;
        } // for
    } // for
} // Dump


// -- EOF

