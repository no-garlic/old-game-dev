// ----------------------------------------------------------------------------
// File: Config.h
// Desc: Class to load and save a config file, holding a tree of sections
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __CONFIG_H_
#define __CONFIG_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Kernel/Types.h"
#include "Kernel/Logging.h"
#include "Kernel/StdStr.h"


// ----------------------------------------------------------------------------
// Number of characters for each indent level ued in the config file
// ----------------------------------------------------------------------------
#define CONFIG_FILE_INDENT_SIZE   2


// ----------------------------------------------------------------------------
// Forward declarations for the config file classes and structures
// ----------------------------------------------------------------------------
struct ConfigValue;
struct ConfigSection;
class  ConfigFile;


// ----------------------------------------------------------------------------
// Typedefs for the config file types
// ----------------------------------------------------------------------------
typedef Map<String, ConfigValue> ConfigValueMap;
typedef Map<String, ConfigSection> ConfigSectionMap;


// ----------------------------------------------------------------------------
// Name: ConfigValue (struct)
// Desc: A key and value for a configuration item
// ----------------------------------------------------------------------------
struct ConfigValue
{
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  ConfigValue()  { REF_COUNT_CTOR(ConfigValue); }
  ConfigValue(const ConfigValue &other) : Key(other.Key), Value(other.Value) { REF_COUNT_CTOR(ConfigValue); }
  ~ConfigValue() { REF_COUNT_DTOR(ConfigValue); }

  // --------------------------------------------------------------------------
  // Public members
  // --------------------------------------------------------------------------
  String  Key;    // The key
  String  Value;  // The value

  // --------------------------------------------------------------------------
  // Conversion operators
  // --------------------------------------------------------------------------
  operator float() const                { return LexicalCast<float, String>(Value); }
  operator int() const                  { return LexicalCast<int,   String>(Value); }
  operator bool() const                 { return LexicalCast<bool,  String>(Value); }
  operator const String &() const       { return Value; }

  // --------------------------------------------------------------------------
  // Assignment operators
  // --------------------------------------------------------------------------
  void operator=(const String &value)   { Value = value; }
  void operator=(float value)           { Value = ToString(value); }
  void operator=(int value)             { Value = ToString(value); }
  void operator=(bool value)            { Value = ToString(value); }

  // --------------------------------------------------------------------------
  // Equality operators
  // --------------------------------------------------------------------------
  bool operator==(const String &value)  { return Value == value; }
  bool operator==(int value)            { return ToString(value) == Value; }
  bool operator==(float value)          { return ToString(value) == Value; }
  bool operator==(bool value)           { return ToString(value) == Value; }

}; // struct ConfigValue


// ----------------------------------------------------------------------------
// Name: ConfigSection (struct)
// Desc: An array of config values within a section. Also has an array of nested
//       sections to provide a hierarchial tree.
// ----------------------------------------------------------------------------
struct ConfigSection
{
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  ConfigSection()  { REF_COUNT_CTOR(ConfigSection); }
  ConfigSection(const ConfigSection &other) : Name(other.Name), Type(other.Type), 
    Items(other.Items), ChildSections(other.ChildSections) 
  { REF_COUNT_CTOR(ConfigSection); }
  ~ConfigSection() { REF_COUNT_DTOR(ConfigSection); }

  // --------------------------------------------------------------------------
  // Public members
  // --------------------------------------------------------------------------
  String            Name;           // The section name
  String            Type;           // The section type
  ConfigValueMap    Items;          // The array of config values
  ConfigSectionMap  ChildSections;  // The array of nested sections

  // --------------------------------------------------------------------------
  // Add or set a key value in this section
  // --------------------------------------------------------------------------
  void Set(const String &key, const String &value);
  void Set(const String &key, int value);
  void Set(const String &key, float value);
  void Set(const String &key, bool value);

  // --------------------------------------------------------------------------
  // Remove a key value from this section
  // --------------------------------------------------------------------------
  void Remove(const String &key);

  // --------------------------------------------------------------------------
  // Brackets operator for accessing values by reference
  // --------------------------------------------------------------------------
  ConfigValue &operator()(const String &key);
  const ConfigValue &operator()(const String &key) const;
  
  // --------------------------------------------------------------------------
  // Add a section as a child to this section
  // --------------------------------------------------------------------------
  ConfigSection &AddSection(const String &type, const String &name);

}; // struct ConfigSection


// ----------------------------------------------------------------------------
// Name: ConfigFile (class)
// Desc: Class to load and save a config file, holding a tree of sections
// ----------------------------------------------------------------------------
class ConfigFile
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  ConfigFile()  { REF_COUNT_CTOR(ConfigFile); }
  ~ConfigFile() { REF_COUNT_DTOR(ConfigFile); }

  // --------------------------------------------------------------------------
  // Load the config file
  // --------------------------------------------------------------------------
  bool Load(const String &filename);
  bool ReLoad() { return Load(m_filename); }

  // --------------------------------------------------------------------------
  // Save the config file
  // --------------------------------------------------------------------------
  bool SaveAs(const String &filename);
  bool Save() { return SaveAs(m_filename); }

  // --------------------------------------------------------------------------
  // Get the array of sections
  // --------------------------------------------------------------------------
  ConfigSectionMap &GetSections()             { return m_sections; }
  const ConfigSectionMap &GetSections() const { return m_sections; }

  // --------------------------------------------------------------------------
  // Add a section to the file
  // --------------------------------------------------------------------------
  ConfigSection &AddSection(const String &type, const String &name);

  // --------------------------------------------------------------------------
  // Brackets operator to access a section by reference
  // --------------------------------------------------------------------------
  const ConfigSection &operator()(const String &name) const;
  ConfigSection &operator()(const String &name);

  // --------------------------------------------------------------------------
  // Manage the tab offset while saving a file
  // --------------------------------------------------------------------------
  static uint GetTabOffset()  { return s_tab_offset; }
  static void PushTab()       { s_tab_offset += CONFIG_FILE_INDENT_SIZE; }
  static void PopTab()        { s_tab_offset -= CONFIG_FILE_INDENT_SIZE; }

private:
  // --------------------------------------------------------------------------
  // Load the given section from disk
  // --------------------------------------------------------------------------
  bool LoadSection(ConfigSection &section, std::fstream &file);

  // --------------------------------------------------------------------------
  // Read the data from the given line
  // --------------------------------------------------------------------------
  bool ReadSectionData(const String &in, String &name, String &type);
  bool ReadSectionValue(const String &in, String &key, String &value);
  bool IsSectionStart(const String &in);
  bool IsSectionEnd(const String &in);

  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  ConfigSectionMap    m_sections;
  String              m_filename;
  static uint         s_tab_offset;

}; // class ConfigFile


// ----------------------------------------------------------------------------
// Insertion operator for writing a config data to an output stream
// ----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const ConfigValue &val);
std::ostream &operator<<(std::ostream &os, const ConfigSection &section);
std::ostream &operator<<(std::ostream &os, const ConfigFile &file);

// ----------------------------------------------------------------------------
// Extract the config value and insert it into the given datatype
// ----------------------------------------------------------------------------
String &operator<<(String &str, const ConfigValue &val);
int    &operator<<(int &i, const ConfigValue &val);
float  &operator<<(float &f, const ConfigValue &val);
bool   &operator<<(bool &b, const ConfigValue &val);


#endif // __CONFIG_H_

// -- EOF


