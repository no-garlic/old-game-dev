
#ifndef __CONFIG_H_
#define __CONFIG_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "stdType.h"
#include "stdStr.h"


// ----------------------------------------------------------------------------
// The indent size when writing to a config file
// ----------------------------------------------------------------------------
#define CONFIG_FILE_INDENT_SIZE   ((uint) 2)


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
struct ConfigValue;
struct ConfigSection;
class  ConfigFile;


// ----------------------------------------------------------------------------
// Typedefs
// ----------------------------------------------------------------------------
typedef std::map<String, ConfigValue>   ConfigValueMap;
typedef std::map<String, ConfigSection> ConfigSectionMap;

// ----------------------------------------------------------------------------
// Name: ConfigValue
// Desc: A key and value for a configuration item
// ----------------------------------------------------------------------------
struct ConfigValue
{
  String  Key;        // The key
  String  Value;      // The value

  // Default constructor
  ConfigValue()  {}

  // --------------------------------------------------------------------------
  // Desc: Copy constructor
  // Parm: a_other the other object to copy
  // --------------------------------------------------------------------------
  ConfigValue(const ConfigValue &a_other) : Key(a_other.Key), Value(a_other.Value) {}

  // --------------------------------------------------------------------------
  // Desc: Destructor
  // --------------------------------------------------------------------------
  ~ConfigValue() {}

  // --------------------------------------------------------------------------
  // Desc: Test if the value is valid
  // --------------------------------------------------------------------------
  bool IsValid() { return !(Key.empty()); }  

  // --------------------------------------------------------------------------
  // Desc: Convert this value to a float
  // Retn: the value as a float
  // --------------------------------------------------------------------------
  operator float() const          { return LexicalCast<float, String>(Value); }

  // --------------------------------------------------------------------------
  // Desc: Convert this value to an integer
  // Retn: the value as an integer
  // --------------------------------------------------------------------------
  operator uint() const           { return LexicalCast<uint,  String>(Value); }

  // --------------------------------------------------------------------------
  // Desc: Convert this value to an integer
  // Retn: the value as an integer
  // --------------------------------------------------------------------------
  operator DWORD() const          { return LexicalCast<DWORD, String>(Value); }

  // --------------------------------------------------------------------------
  // Desc: Convert this value to an integer
  // Retn: the value as an integer
  // --------------------------------------------------------------------------
  operator int() const            { return LexicalCast<int,   String>(Value); }

  // --------------------------------------------------------------------------
  // Desc: Convert this value to a boolean
  // Retn: the value as a boolean
  // --------------------------------------------------------------------------
  operator bool() const           { return LexicalCast<bool,  String>(Value); }

  // --------------------------------------------------------------------------
  // Desc: Convert this value to a string
  // Retn: the value as a string
  // --------------------------------------------------------------------------
  operator const String &() const { return Value; }

  // --------------------------------------------------------------------------
  // breif Assign a string to this value
  // Parm: a_value the value to assign
  // --------------------------------------------------------------------------
  void operator=(const String &a_value)   { Value = a_value; }

  // --------------------------------------------------------------------------
  // breif Assign a float to this value
  // Parm: a_value the value to assign
  // --------------------------------------------------------------------------
  void operator=(float a_value)   { Value = ToString(a_value); }

  // --------------------------------------------------------------------------
  // breif Assign an integer to this value
  // Parm: a_value the value to assign
  // --------------------------------------------------------------------------
  void operator=(int a_value)     { Value = ToString(a_value); }

  // --------------------------------------------------------------------------
  // breif Assign an integer to this value
  // Parm: a_value the value to assign
  // --------------------------------------------------------------------------
  void operator=(uint a_value)    { Value = ToString(a_value); }

  // --------------------------------------------------------------------------
  // breif Assign an integer to this value
  // Parm: a_value the value to assign
  // --------------------------------------------------------------------------
  void operator=(DWORD a_value)   { Value = ToString(a_value); }

  // --------------------------------------------------------------------------
  // breif Assign a boolean to this value
  // Parm: a_value the value to assign
  // --------------------------------------------------------------------------
  void operator=(bool a_value)    { Value = ToString(a_value); }

  // --------------------------------------------------------------------------
  // Desc: Test if this value is equal to the given value
  // Parm: a_value the value to compare to
  // --------------------------------------------------------------------------
  bool operator==(const String &a_value)  { return Value == a_value; }

  // --------------------------------------------------------------------------
  // Desc: Test if this value is equal to the given value
  // Parm: a_value the value to compare to
  // --------------------------------------------------------------------------
  bool operator==(int a_value)            { return ToString(a_value) == Value; }

  // --------------------------------------------------------------------------
  // Desc: Test if this value is equal to the given value
  // Parm: a_value the value to compare to
  // --------------------------------------------------------------------------
  bool operator==(float a_value)          { return ToString(a_value) == Value; }

  // --------------------------------------------------------------------------
  // Desc: Test if this value is equal to the given value
  // Parm: a_value the value to compare to
  // --------------------------------------------------------------------------
  bool operator==(bool a_value)           { return ToString(a_value) == Value; }

};


// ----------------------------------------------------------------------------
// Name: ConfigSection
// Desc: An array of config values within a section.
// ----------------------------------------------------------------------------
struct ConfigSection
{
  String            Name;           // The section name
  String            Type;           // The section type
  ConfigValueMap    Items;          // The array of config values
  ConfigSectionMap  ChildSections;  // The array of nested sections

  // --------------------------------------------------------------------------
  // Desc: Default constructor
  // --------------------------------------------------------------------------
  ConfigSection()  {}

  // --------------------------------------------------------------------------
  // Desc: Copy constructor
  // Parm: a_other the object to copy
  // --------------------------------------------------------------------------
  ConfigSection(const ConfigSection &a_other) : Name(a_other.Name), Type(a_other.Type), 
    Items(a_other.Items), ChildSections(a_other.ChildSections) {}

  // --------------------------------------------------------------------------
  // Desc: Destructor
  // --------------------------------------------------------------------------
  ~ConfigSection() {}

  // --------------------------------------------------------------------------
  // Desc: Test if the section is valid
  // --------------------------------------------------------------------------
  bool IsValid() const { return !(Name.empty()); }  

  // --------------------------------------------------------------------------
  // Desc: Add or set a ConfigValue in this section
  // Parm: a_key the key to set
  // Parm: a_value the value to set 
  // --------------------------------------------------------------------------
  void Set(const String &a_key, const String &a_value);

  // --------------------------------------------------------------------------
  // Desc: Add or set a ConfigValue in this section
  // Parm: a_key the key to set
  // Parm: a_value the value to set 
  // --------------------------------------------------------------------------
  void Set(const String &a_key, int a_value);

  // --------------------------------------------------------------------------
  // Desc: Add or set a ConfigValue in this section
  // Parm: a_key the key to set
  // Parm: a_value the value to set 
  // --------------------------------------------------------------------------
  void Set(const String &a_key, uint a_value);

  // --------------------------------------------------------------------------
  // Desc: Add or set a ConfigValue in this section
  // Parm: a_key the key to set
  // Parm: a_value the value to set 
  // --------------------------------------------------------------------------
  void Set(const String &a_key, DWORD a_value);

  // --------------------------------------------------------------------------
  // Desc: Add or set a ConfigValue in this section
  // Parm: a_key the key to set
  // Parm: a_value the value to set 
  // --------------------------------------------------------------------------
  void Set(const String &a_key, float a_value);

  // --------------------------------------------------------------------------
  // Desc: Add or set a ConfigValue in this section
  // Parm: a_key the key to set
  // Parm: a_value the value to set 
  // --------------------------------------------------------------------------
  void Set(const String &a_key, bool a_value);

  // --------------------------------------------------------------------------
  // Desc: Remove a ConfigValue from this section
  // Parm: a_key the key of the ConfigValue to remove
  // --------------------------------------------------------------------------
  void Remove(const String &a_key);

  // --------------------------------------------------------------------------
  // Desc: Brackets operator for accessing values by reference
  // Parm: a_key the key of the ConfigValue to get
  // Retn: the ConfigValue corrosponding the the supplied key.
  //
  // If the returned ConfigValue.Name is empty, then no ConfigValue
  // was found for the specified key.
  // --------------------------------------------------------------------------
  ConfigValue &operator()(const String &a_key);

  // --------------------------------------------------------------------------
  // Desc: Brackets operator for accessing values by reference
  // Parm: a_key the key of the ConfigValue to get
  // Retn: the ConfigValue corrosponding the the supplied key.
  //
  // If the returned ConfigValue.Name is empty, then no ConfigValue
  // was found for the specified key.
  // --------------------------------------------------------------------------
  const ConfigValue &operator()(const String &a_key) const;

  // --------------------------------------------------------------------------
  // Desc: Get a sub-section by reference
  // Parm: a_name the name of the ConfigSection to get
  // Retn: the ConfigSection corrosponding the the supplied name.
  //
  // If the returned ConfigSection.Name is empty, then no ConfigSection
  // was found for the specified name.
  // --------------------------------------------------------------------------
  const ConfigSection &SubSection(const String &a_name) const;

  // --------------------------------------------------------------------------
  // Desc: Get a sub-section by reference
  // Parm: a_name the name of the ConfigSection to get
  // Retn: the ConfigSection corrosponding the the supplied name.
  //
  // If the returned ConfigSection.Name is empty, then no ConfigSection
  // was found for the specified name.
  // --------------------------------------------------------------------------
  ConfigSection &SubSection(const String &a_name);

  // --------------------------------------------------------------------------
  // Desc: Add a sub-section to this section
  // Parm: a_type the nype of the ConfigSection
  // Parm: a_name the name of the sub section
  // Retn: the new ConfigSection 
  // --------------------------------------------------------------------------
  ConfigSection &AddSection(const String &a_type, const String &a_name);

  // --------------------------------------------------------------------------
  // Desc: Append the given config section to this section using this section as  
  //       the base. Any value in this section will be overridden by the value in
  //       the supplied section, and any new value from the supplied section will 
  //       be added.
  // --------------------------------------------------------------------------
  bool Append(const ConfigSection &a_other);

};


// --------------------------------------------------------------------------
// Name: ConfigFile
// Desc: Class to load and save a config file, holding a tree of sections.
// --------------------------------------------------------------------------
class ConfigFile
{
public:
  // --------------------------------------------------------------------------
  // Desc: Constructor
  // --------------------------------------------------------------------------
  ConfigFile()  {}

  // --------------------------------------------------------------------------
  // Desc: Destructor
  // --------------------------------------------------------------------------
  ~ConfigFile() {}

  // --------------------------------------------------------------------------
  // Clear the contents in memory
  // --------------------------------------------------------------------------
  void Clear() { m_sections.clear(); }

  // --------------------------------------------------------------------------
  // Desc: Load the config file
  // Parm: a_filename the filename of the config file to open
  // Retn: true if the file was loaded
  // --------------------------------------------------------------------------
  bool Load(const String &a_filename);

  // --------------------------------------------------------------------------
  // Desc: Reload the config file
  // Retn: true if the file was loaded
  // --------------------------------------------------------------------------
  bool ReLoad() { return Load(m_filename); }

  // --------------------------------------------------------------------------
  // Desc: Save the config file to a new filename
  // Parm: a_filename the filename to save the file to
  // Retn: true if the file saved sucessfully, otherwise false
  // --------------------------------------------------------------------------
  bool SaveAs(const String &a_filename);

  // --------------------------------------------------------------------------
  // Desc: Save the config file
  // Parm: a_filename the filename to save the file to
  // Retn: true if the file saved sucessfully, otherwise false
  // --------------------------------------------------------------------------
  bool Save() { return SaveAs(m_filename); }

  // --------------------------------------------------------------------------
  // Desc: Append the given config file to this file using this file as the 
  //       base. Any value in this file will be overridden by the value in
  //       the supplied file, and any new value from the supplied file will 
  //       be added.
  // --------------------------------------------------------------------------
  bool Append(const ConfigFile &a_other);

  // --------------------------------------------------------------------------
  // Desc: Get the array of sections
  // Retn: the array of sections
  // --------------------------------------------------------------------------
  ConfigSectionMap &GetSections()             { return m_sections; }

  // --------------------------------------------------------------------------
  // Desc: Get the array of sections
  // Retn: the array of sections
  // --------------------------------------------------------------------------
  const ConfigSectionMap &GetSections() const { return m_sections; }

  // --------------------------------------------------------------------------
  // Desc: Add a section to the file
  // Parm: a_type the new section type
  // Parm: a_name the new section name
  // --------------------------------------------------------------------------
  ConfigSection &AddSection(const String &a_type, const String &a_name);

  // --------------------------------------------------------------------------
  // Desc: Operator to access a section by reference
  // Parm: the name of the ConfigSection to get
  // Retn: the ConfigSection for the corrosponding name
  //
  // If the returned ConfigSection.Name is empty, then no ConfigSection
  // was found for the specified name.
  // --------------------------------------------------------------------------
  const ConfigSection &operator()(const String &a_name) const;

  // --------------------------------------------------------------------------
  // Desc: Operator to access a section by reference
  // Parm: the name of the ConfigSection to get
  // Retn: the ConfigSection for the corrosponding name
  //
  // If the returned ConfigSection.Name is empty, then no ConfigSection
  // was found for the specified name.
  // --------------------------------------------------------------------------
  ConfigSection &operator()(const String &a_name);

  // --------------------------------------------------------------------------
  // Desc: Get the current indentation while saving a file
  // Retn: the indentation level
  // --------------------------------------------------------------------------
  static uint GetTabOffset()  { return s_tabOffset; }

  // --------------------------------------------------------------------------
  // Desc: Increase the indentation while saving a file
  // --------------------------------------------------------------------------
  static void PushTab()       { s_tabOffset += CONFIG_FILE_INDENT_SIZE; }

  // --------------------------------------------------------------------------
  // Desc: Decreease the indentation while saving a file
  // --------------------------------------------------------------------------
  static void PopTab()        { s_tabOffset -= CONFIG_FILE_INDENT_SIZE; }

private:
  // --------------------------------------------------------------------------
  // Desc: Load the given section from disk
  // --------------------------------------------------------------------------
  bool LoadSection(ConfigSection &section, std::fstream &file);

  // --------------------------------------------------------------------------
  // Desc: Read the data from the given line
  // Parm: a_in the input string
  // Parm: a_name [out] the name to assign
  // Parm: a_type [out] the type to asssign
  // Retn: true if the input string was correctly split into a name and type
  // --------------------------------------------------------------------------
  bool ReadSectionData(const String &a_in, String &a_name, String &a_type);

  // --------------------------------------------------------------------------
  // Desc: Read the data from the given line
  // Parm: a_in the input string
  // Parm: a_key [out] the key to assign
  // Parm: a_value [out] the value to asssign
  // Retn: true if the input string was correctly split into a key and value
  // --------------------------------------------------------------------------
  bool ReadSectionValue(const String &a_in, String &a_key, String &a_value);

  // --------------------------------------------------------------------------
  // Desc: Tests if the given line is a section start '{'
  // Parm: a_in the input string
  // Retn: true if the input string is a section start
  // --------------------------------------------------------------------------
  bool IsSectionStart(const String &a_in);

  // --------------------------------------------------------------------------
  // Desc: Tests if the given line is a section end '}'
  // Parm: a_in the input string
  // Retn: true if the input string is a section end
  // --------------------------------------------------------------------------
  bool IsSectionEnd(const String &a_in);

  // --------------------------------------------------------------------------
  // Desc: Generates a unique key
  // Parm: a_key the string to set
  // --------------------------------------------------------------------------
  void GenerateUniqueKey(String &a_key);

  // --------------------------------------------------------------------------
  // Private mebers
  // --------------------------------------------------------------------------
  ConfigSectionMap    m_sections;   // The map of root level config sections
  String              m_filename;   // The filename of the config file
  static uint         s_tabOffset;  // The current indentation

};


// ----------------------------------------------------------------------------
// Desc: Insertion operator for writing a ConfigValue to an output stream
// Parm: a_os the output stream
// Parm: a_ the ConfigValue
// Retn: a reference to the output stream
// ----------------------------------------------------------------------------
OutputStream &operator<<(OutputStream &a_os, const ConfigValue &a_val);

// ----------------------------------------------------------------------------
// Desc: Insertion operator for writing a ConfigSection to an output stream
// Parm: a_os the output stream
// Parm: a_ the ConfigSection
// Retn: a reference to the output stream
// ----------------------------------------------------------------------------
OutputStream &operator<<(OutputStream &a_os, const ConfigSection &a_section);

// ----------------------------------------------------------------------------
// Desc: Insertion operator for writing a ConfigFile to an output stream
// Parm: a_os the output stream
// Parm: a_ the ConfigFile
// Retn: a reference to the output stream
// ----------------------------------------------------------------------------
OutputStream &operator<<(OutputStream &a_os, const ConfigFile &a_file);

// ----------------------------------------------------------------------------
// Desc: Extract the config value and insert it into a string
// Parm: a_str [out] the argument to set (and return)
// Parm: a_val the config value to extract into input argument
// Retn: a reference to the input argument
// ----------------------------------------------------------------------------
String &operator<<(String &a_str, const ConfigValue &a_val);

// ----------------------------------------------------------------------------
// Desc: Extract the config value and insert it into an integer
// Parm: a_str [out] the argument to set (and return)
// Parm: a_val the config value to extract into input argument
// Retn: a reference to the input argument
// ----------------------------------------------------------------------------
int    &operator<<(int &a_i, const ConfigValue &a_val);

// ----------------------------------------------------------------------------
// Desc: Extract the config value and insert it into a float
// Parm: a_str [out] the argument to set (and return)
// Parm: a_val the config value to extract into input argument
// Retn: a reference to the input argument
// ----------------------------------------------------------------------------
float  &operator<<(float &a_f, const ConfigValue &a_val);

// ----------------------------------------------------------------------------
// Desc: Extract the config value and insert it into a boolean
// Parm: a_str [out] the argument to set (and return)
// Parm: a_val the config value to extract into input argument
// Retn: a reference to the input argument
// ----------------------------------------------------------------------------
bool   &operator<<(bool &a_b, const ConfigValue &a_val);


#endif // __CONFIG_H_




