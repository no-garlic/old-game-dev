// ----------------------------------------------------------------------------
// File: Kernel_Config.cpp
// Desc: Configuration file utility
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Kernel/Config.h"


// ----------------------------------------------------------------------------
// Current tab offset while writing a file
// ----------------------------------------------------------------------------
uint ConfigFile::s_tab_offset = 0;


// ----------------------------------------------------------------------------
// Macro for reading the next non whitespace line from a file
// ----------------------------------------------------------------------------
#define READ_LINE(x)    std::getline(file, line);                       \
                        while (line.empty())                            \
                        {                                               \
                          std::getline(file, line);                     \
                          if (file.eof() || file.bad() || file.fail())  \
                            return true;                                \
                        }                                               \


// ----------------------------------------------------------------------------
// Name: ConfigSection::operator
// Desc: Get the config value from the config section for the given key. Throws 
//       an exception of the key does not exist
// Retn: ConfigValue & - the value
// ----------------------------------------------------------------------------
ConfigValue &ConfigSection::operator()(const String &key)
{
  ConfigValueMap::iterator iter = Items.find(key);

  if (iter == Items.end())
    throw InvalidParameterException(FLSTAMP, 
    "Failed to find the key in the config section (key = ") << 
    key << ", section = " << Name;

  return iter->second;
} // Get


// ----------------------------------------------------------------------------
// Name: ConfigSection::operator
// Desc: Get the config value from the config section for the given key. Throws 
//       an exception of the key does not exist
// Retn: const ConfigValue & - the value
// ----------------------------------------------------------------------------
const ConfigValue &ConfigSection::operator()(const String &key) const
{
  ConfigValueMap::const_iterator iter = Items.find(key);

  if (iter == Items.end())
    throw InvalidParameterException(FLSTAMP, 
    "Failed to find the key in the config section (key = ") << 
    key << ", section = " << Name;

  return iter->second;
} // Get


// ----------------------------------------------------------------------------
// Name: ConfigSection::Set
// Desc: Sets or creates the config value within the section
// Parm: const String &key    - the key
// Parm: const String &value  - the value
// ----------------------------------------------------------------------------
void ConfigSection::Set(const String &key, const String &value)
{
  ConfigValueMap::iterator iter = Items.find(key);

  if (iter != Items.end())
  {
    iter->second = value;
  } // if
  else
  {
    ConfigValue cfgval;
    cfgval.Key   = key;
    cfgval.Value = value;
    Items[key] = cfgval;
  } // else
} // Set


// ----------------------------------------------------------------------------
// Name: ConfigSection::Set
// Desc: Sets or creates the config value within the section
// Parm: const String &key    - the key
// Parm: int value  - the value
// ----------------------------------------------------------------------------
void ConfigSection::Set(const String &key, int value)
{
  ConfigValueMap::iterator iter = Items.find(key);

  if (iter != Items.end())
  {
    iter->second = value;
  } // if
  else
  {
    ConfigValue cfgval;
    cfgval.Key   = key;
    cfgval.Value = ToString(value);
    Items[key] = cfgval;
  } // else
} // Set


// ----------------------------------------------------------------------------
// Name: ConfigSection::Set
// Desc: Sets or creates the config value within the section
// Parm: const String &key    - the key
// Parm: float value  - the value
// ----------------------------------------------------------------------------
void ConfigSection::Set(const String &key, float value)
{
  ConfigValueMap::iterator iter = Items.find(key);

  if (iter != Items.end())
  {
    iter->second = value;
  } // if
  else
  {
    ConfigValue cfgval;
    cfgval.Key   = key;
    cfgval.Value = ToString(value);
    Items[key] = cfgval;
  } // else
} // Set


// ----------------------------------------------------------------------------
// Name: ConfigSection::Set
// Desc: Sets or creates the config value within the section
// Parm: const String &key    - the key
// Parm: bool value  - the value
// ----------------------------------------------------------------------------
void ConfigSection::Set(const String &key, bool value)
{
  ConfigValueMap::iterator iter = Items.find(key);

  if (iter != Items.end())
  {
    iter->second = value;
  } // if
  else
  {
    ConfigValue cfgval;
    cfgval.Key   = key;
    cfgval.Value = ToString(value);
    Items[key] = cfgval;
  } // else
} // Set


// ----------------------------------------------------------------------------
// Name: ConfigSection::Remove
// Desc: Remove the config value from the section
// Parm: const String &key - the key to remove
// ----------------------------------------------------------------------------
void ConfigSection::Remove(const String &key)
{
  ConfigValueMap::iterator iter = Items.find(key);
  if (iter != Items.end())
    Items.erase(iter);
} // Remove


// ----------------------------------------------------------------------------
// Name: ConfigSection::AddSection
// Desc: Add the given section to the section as a child
// Parm: const String &type  - the section type
// Parm: const String &name  - the section name
// Retn: ConfigSection &     - the child section
// ----------------------------------------------------------------------------
ConfigSection &ConfigSection::AddSection(const String &type, const String &name)
{
  ConfigSectionMap::iterator iter = ChildSections.find(name);
  if (iter != ChildSections.end())
    throw InvalidParameterException(FLSTAMP, "The section: ") << 
    name << " already exists in this scope";

  ConfigSection section;
  section.Type   = type;
  section.Name   = name;
  ChildSections.insert(MakePair(name, section));

  iter = ChildSections.find(name);
  ConfigSection &result = iter->second;
  return result;
} // AddSection


// ----------------------------------------------------------------------------
// Name: ConfigFile::AddSection
// Desc: Add the given section to the file
// Parm: const String &type  - the section type
// Parm: const String &name  - the section name
// Retn: ConfigSection &     - the child section
// ----------------------------------------------------------------------------
ConfigSection &ConfigFile::AddSection(const String &type, const String &name)
{
  ConfigSectionMap::iterator iter = m_sections.find(name);
  if (iter != m_sections.end())
    throw InvalidParameterException(FLSTAMP, "The section: ") << 
    name << " already exists in this scope";

  ConfigSection section;
  section.Type   = type;
  section.Name   = name;
  m_sections.insert(MakePair(name, section));

  iter = m_sections.find(name);
  ConfigSection &result = iter->second;
  return result;
} // AddSection


// ----------------------------------------------------------------------------
// Name: ConfigFile::operator
// Desc: Get the section from the file for the given name. Throws an exception
//       if no section withthe given name exists.
// Retn: const ConfigSection & - the section
// ----------------------------------------------------------------------------
const ConfigSection &ConfigFile::operator()(const String &name) const
{
  ConfigSectionMap::const_iterator iter = m_sections.find(name);
  if (iter == m_sections.end())
    throw InvalidParameterException(FLSTAMP, "The section: ") << 
    name << " does not exist";

  return iter->second;
} // operator()


// ----------------------------------------------------------------------------
// Name: ConfigFile::operator
// Desc: Get the section from the file for the given name. Throws an exception
//       if no section withthe given name exists.
// Retn: ConfigSection & - the section
// ----------------------------------------------------------------------------
ConfigSection &ConfigFile::operator()(const String &name)
{
  ConfigSectionMap::iterator iter = m_sections.find(name);
  if (iter == m_sections.end())
    throw InvalidParameterException(FLSTAMP, "The section: ") << 
    name << " does not exist";

  return iter->second;
} // operator()


// ----------------------------------------------------------------------------
// Name: ConfigFile::SaveAs
// Desc: Save the file with the given filename
// Parm: const String &filename - the filename
// Retn: bool                   - true if saved
// ----------------------------------------------------------------------------
bool ConfigFile::SaveAs(const String &filename)
{
  if (filename.empty())
    return false;

  m_filename = filename;
  s_tab_offset = 0;

  std::fstream file;
  file.open(filename.c_str(), std::ios_base::out);
  if (!file.is_open())
    return false;

  file << (*this);

  file << std::endl;
  file.close();
  return true;
} // SaveAs


// ----------------------------------------------------------------------------
// Name: ConfigFile::Load
// Desc: Load the file with the given filename
// Parm: const String &filename - the filename
// Retn: bool                   - true if loaded
// ----------------------------------------------------------------------------
bool ConfigFile::Load(const String &filename)
{
  if (filename.empty())
    return false;

  s_tab_offset = 0;
  m_filename = filename;
  m_sections.clear();

  std::fstream file;
  file.open(filename.c_str(), std::ios_base::in);
  if (!file.is_open())
    return false;

  while (!file.eof())
  {
    String line;
    READ_LINE(line);

    String name, type;
    if (!ReadSectionData(line, name, type))
      return false;

    READ_LINE(line);
    if (!IsSectionStart(line))
      return false;

    ConfigSection &section = AddSection(type, name);
    if (!LoadSection(section, file))
      return false;

    if (file.fail() || file.bad())
      return false;
  } // while

  file.close();
  return true;
} // Load


// ----------------------------------------------------------------------------
// Name: ConfigFile::LoadSection
// Desc: Load the section from the given open file
// Parm: ConfigSection &section - the section to load
// Parm: std::fstream &file     - the file
// Retn: bool                   - true if loaded
// ----------------------------------------------------------------------------
bool ConfigFile::LoadSection(ConfigSection &section, std::fstream &file)
{
  while (!file.eof())
  {
    String line;
    READ_LINE(line);

    TrimString(line);
    if (line.length() == 0)
      continue;

    if (IsSectionEnd(line))
      return true;

    String key, value;
    if (ReadSectionValue(line, key, value))
    {
      section.Set(key, value);
      continue;
    } // if

    String name, type;
    if (ReadSectionData(line, name, type))
    {
      READ_LINE(line);
      if (!IsSectionStart(line))
        return false;

      ConfigSection &child = section.AddSection(type, name);
      if (!LoadSection(child, file))
        return false;
    } // if
    else
    {
      return false;
    } // else

    if (file.fail() || file.bad())
      return false;
  } // while

  return true;
} // LoadSection


// ----------------------------------------------------------------------------
// Name: ConfigFile::ReadSectionValue
// Desc: Read the line and extract the key and value
// Parm: const String &in - the input string
// Parm: String &key      - the key to set
// Parm: String &value    - the value to set
// Retn: bool             - true if the key and value were found and set
// ----------------------------------------------------------------------------
bool ConfigFile::ReadSectionValue(const String &in, String &key, String &value)
{
  String s = in;
  TrimString(s);

  int pos1 = (int) s.find_first_of("=");
  int pos2 = (int) s.find_first_of(";");

  if (pos1 < 0 && pos2 < 0)
    return false;

  key   = s.substr(0, pos1);
  value = s.substr(pos1 + 1, pos2 - (pos1 + 1));

  TrimString(key);
  TrimString(value);

  return true;
} // ReadSectionValue


// ----------------------------------------------------------------------------
// Name: ConfigFile::ReadSectionData
// Desc: Read the line and extract the name and type
// Parm: const String &in - the input string
// Parm: String &name     - the name to set
// Parm: String &type     - the type to set
// Retn: bool             - true if the name and type were found and set
// ----------------------------------------------------------------------------
bool ConfigFile::ReadSectionData(const String &in, String &name, String &type)
{
  String s = in;
  TrimString(s);

  int pos1 = (int) s.find_first_of("(");
  int pos2 = (int) s.find_first_of(")");

  if (pos1 < 0 && pos2 < 0)
    return false;

  type = s.substr(0, pos1);
  name = s.substr(pos1 + 1, pos2 - (pos1 + 1));

  TrimString(type);
  TrimString(name);

  return true;
} // ReadSectionData


// ----------------------------------------------------------------------------
// Name: ConfigFile::IsSectionStart
// Desc: Is the given line a section start
// Parm: const String &in - the input string
// Retn: bool             - true if it is a section start
// ----------------------------------------------------------------------------
bool ConfigFile::IsSectionStart(const String &in)
{
  String s = in;
  TrimString(s);
  return (s == "{");
} // IsSectionStart


// ----------------------------------------------------------------------------
// Name: ConfigFile::IsSectionEnd
// Desc: Is the given line a section end
// Parm: const String &in - the input string
// Retn: bool             - true if it is a section end
// ----------------------------------------------------------------------------
bool ConfigFile::IsSectionEnd(const String &in)
{
  String s = in;
  TrimString(s);
  return (s == "}");
} // IsSectionEnd


// ----------------------------------------------------------------------------
// Name: operator<<
// Desc: Write the config value to the given output stream
// Parm: std::ostream &os        - the stream
// Parm: const ConfigValue &val  - the value
// Retn: std::ostream &          - the stream
// ----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const ConfigValue &val)
{
  os << PadStr(CONFIG_FILE_INDENT_SIZE) << val.Key << 
    " = " << val.Value << ";" << std::endl;
  return os;
} // operator <<


// ----------------------------------------------------------------------------
// Name: operator<<
// Desc: Insert the value to the given string
// Parm: String &str             - the string
// Parm: const ConfigValue &val  - the value
// Retn: String &                - the string
// ----------------------------------------------------------------------------
String &operator<<(String &str, const ConfigValue &val)
{
  str = val;
  return str;
} // operator<<


// ----------------------------------------------------------------------------
// Name: operator<<
// Desc: Insert the value into the given integer
// Parm: int &i                  - the int
// Parm: const ConfigValue &val  - the value
// Retn: int &                   - the int
// ----------------------------------------------------------------------------
int &operator<<(int &i, const ConfigValue &val)
{
  i = val;
  return i;
} // operator<<


// ----------------------------------------------------------------------------
// Name: operator<<
// Desc: Insert the value into the given the
// Parm: float &f                - the the
// Parm: const ConfigValue &val  - the value
// Retn: float &                 - the the
// ----------------------------------------------------------------------------
float &operator<<(float &f, const ConfigValue &val)
{
  f = val;
  return f;
} // operator<<


// ----------------------------------------------------------------------------
// Name: operator<<
// Desc: Insert the value into the given boolean
// Parm: bool &b                 - the bool
// Parm: const ConfigValue &val  - the value
// Retn: bool &                  - the bool
// ----------------------------------------------------------------------------
bool &operator<<(bool &b, const ConfigValue &val)
{
  b = val;
  return b;
} // operator<<


// ----------------------------------------------------------------------------
// Name: operator<<
// Desc: Write the section to the output stream
// Parm: std::ostream &os              - the stream
// Parm: const ConfigSection &section  - the section
// Retn: std::ostream &                - the stream
// ----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const ConfigSection &section)
{
  String offset = PadStr(ConfigFile::GetTabOffset());

  os << offset << section.Type << "(" << section.Name << ")" << std::endl;
  os << offset << "{" << std::endl;

  ConfigValueMap::const_iterator iter(section.Items.begin()), end(section.Items.end());
  for (; iter != end; ++iter)
    os << offset << iter->second;

  const ConfigSectionMap &sections = section.ChildSections;
  if (!sections.empty())
  {
    os << std::endl;

    ConfigFile::PushTab();

    ConfigSectionMap::const_iterator iter(sections.begin()), end(sections.end());
    for (; iter != end; ++iter)
      os << iter->second;

    ConfigFile::PopTab();
  } // if

  os << offset << "}" << std::endl;

  return os;
} // operator <<


// ----------------------------------------------------------------------------
// Name: operator<<
// Desc: Write the file to the given output stream
// Parm: std::ostream &os        - the stream
// Parm: const ConfigFile &file  - the file
// Retn: std::ostream &          - the stream
// ----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const ConfigFile &file)
{
  const ConfigSectionMap &sections = file.GetSections();

  ConfigSectionMap::const_iterator iter(sections.begin()), end(sections.end());
  for (; iter != end; ++iter)
  {
    os << std::endl;
    os << iter->second;
  } // for

  return os;
} // operator<<


// -- EOF

