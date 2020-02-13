// ----------------------------------------------------------------------------
// Copyright 2006 THQ Studio Australia P/L
// Author: Michael Petrou
// ----------------------------------------------------------------------------
#include "stdConfig.h"
#include "stdLog.h"


// ----------------------------------------------------------------------------
// Current tab offset while writing a file
// ----------------------------------------------------------------------------
uint ConfigFile::s_tabOffset = 0;


// ----------------------------------------------------------------------------
// Macro for reading the next non whitespace line from a file
// ----------------------------------------------------------------------------
#define READ_LINE(x)    std::getline(file, line);   \
  while (line.empty())                              \
{                                                   \
  std::getline(file, line);                         \
  if (file.eof() || file.bad() || file.fail())      \
  return true;                                      \
}                                                   \


// ----------------------------------------------------------------------------
// Get the config value from the config section for the given key.
// ----------------------------------------------------------------------------
ConfigValue &ConfigSection::operator()(const String &a_key)
{
  ConfigValueMap::iterator iter = Items.find(a_key);

  if (iter == Items.end())
  {
    //LOG_ERROR << "Failed to find the key in the config section (key = " << a_key << 
    //              ", section = " << Name << ENDLOG;

    static ConfigValue badValue;
    return badValue;
  }    

  return iter->second;
}


// ----------------------------------------------------------------------------
// Get the config value from the config section for the given key.
// ----------------------------------------------------------------------------
const ConfigValue &ConfigSection::operator()(const String &a_key) const
{
  ConfigValueMap::const_iterator iter = Items.find(a_key);

  if (iter == Items.end())
  {
    //LOG_ERROR << "Failed to find the key in the config section (key = " << a_key << 
    //             ", section = " << Name << ENDLOG;

    static ConfigValue badValue;
    return badValue;
  }

  return iter->second;
}



// ----------------------------------------------------------------------------
// Get the subsection from this section
// ----------------------------------------------------------------------------
const ConfigSection &ConfigSection::SubSection(const String &a_name) const
{
  ConfigSectionMap::const_iterator iter = ChildSections.find(a_name);
  
  if (iter == ChildSections.end())
  {
    //LOG_ERROR << "Failed to find the sub-section (key = " << a_name << 
    //             ", section = " << Name << ENDLOG;

    static ConfigSection badSection;
    return badSection;
  }

  return iter->second;
}


// ----------------------------------------------------------------------------
// Get the subsection from this section
// ----------------------------------------------------------------------------
ConfigSection &ConfigSection::SubSection(const String &a_name)
{
  ConfigSectionMap::iterator iter = ChildSections.find(a_name);

  if (iter == ChildSections.end())
  {
    //LOG_ERROR << "Failed to find the sub-section (key = " << a_name << 
    //  ", section = " << Name << ENDLOG;

    static ConfigSection badSection;
    return badSection;
  }

  return iter->second;
}


// ----------------------------------------------------------------------------
// Sets or creates the config value within the section
// ----------------------------------------------------------------------------
void ConfigSection::Set(const String &a_key, const String &a_value)
{
  ConfigValueMap::iterator iter = Items.find(a_key);

  if (iter != Items.end())
  {
    iter->second = a_value;
  }
  else
  {
    ConfigValue cfgval;
    cfgval.Key   = a_key;
    cfgval.Value = a_value;
    Items[a_key] = cfgval;
  }
}


// ----------------------------------------------------------------------------
// Sets or creates the config value within the section
// ----------------------------------------------------------------------------
void ConfigSection::Set(const String &a_key, int a_value)
{
  ConfigValueMap::iterator iter = Items.find(a_key);

  if (iter != Items.end())
  {
    iter->second = a_value;
  }
  else
  {
    ConfigValue cfgval;
    cfgval.Key   = a_key;
    cfgval.Value = ToString(a_value);
    Items[a_key] = cfgval;
  }
}


// ----------------------------------------------------------------------------
// Sets or creates the config value within the section
// ----------------------------------------------------------------------------
void ConfigSection::Set(const String &a_key, float a_value)
{
  ConfigValueMap::iterator iter = Items.find(a_key);

  if (iter != Items.end())
  {
    iter->second = a_value;
  }
  else
  {
    ConfigValue cfgval;
    cfgval.Key   = a_key;
    cfgval.Value = ToString(a_value);
    Items[a_key] = cfgval;
  }
}


// ----------------------------------------------------------------------------
// Sets or creates the config value within the section
// ----------------------------------------------------------------------------
void ConfigSection::Set(const String &a_key, bool a_value)
{
  ConfigValueMap::iterator iter = Items.find(a_key);

  if (iter != Items.end())
  {
    iter->second = a_value;
  }
  else
  {
    ConfigValue cfgval;
    cfgval.Key   = a_key;
    cfgval.Value = ToString(a_value);
    Items[a_key] = cfgval;
  }
}


// ----------------------------------------------------------------------------
// Remove the config value from the section
// ----------------------------------------------------------------------------
void ConfigSection::Remove(const String &a_key)
{
  ConfigValueMap::iterator iter = Items.find(a_key);
  if (iter != Items.end())
  {
    Items.erase(iter);
  }
}


// ----------------------------------------------------------------------------
// Add the given section to the section as a child
// ----------------------------------------------------------------------------
ConfigSection &ConfigSection::AddSection(const String &a_type, const String &a_name)
{
  ConfigSectionMap::iterator iter = ChildSections.find(a_name);
  if (iter != ChildSections.end())
  {
    LOG_ERROR <<  "The section: " << a_name << " already exists in this scope" << ENDLOG;

    static ConfigSection badSection;
    return badSection;
  }

  ConfigSection section;
  section.Type   = a_type;
  section.Name   = a_name;
  ChildSections.insert(std::make_pair(a_name, section));

  iter = ChildSections.find(a_name);
  ConfigSection &result = iter->second;
  return result;
}


// ----------------------------------------------------------------------------
// Add the given section to the file
// ----------------------------------------------------------------------------
ConfigSection &ConfigFile::AddSection(const String &a_type, const String &a_name)
{
  ConfigSectionMap::iterator iter = m_sections.find(a_name);
  if (iter != m_sections.end())
  {
    LOG_ERROR << "The section: " << a_name << " already exists in this scope" << ENDLOG;

    static ConfigSection badSection;
    return badSection;
  }

  ConfigSection section;
  section.Type   = a_type;
  section.Name   = a_name;
  m_sections.insert(std::make_pair(a_name, section));

  iter = m_sections.find(a_name);
  ConfigSection &result = iter->second;
  return result;
}


// ----------------------------------------------------------------------------
// Get the section from the file for the given name.
// ----------------------------------------------------------------------------
const ConfigSection &ConfigFile::operator()(const String &a_name) const
{
  ConfigSectionMap::const_iterator iter = m_sections.find(a_name);
  if (iter == m_sections.end())
  {
    LOG_ERROR << "The section: " << a_name << " does not exist" << ENDLOG;

    static ConfigSection badSection;
    return badSection;
  }

  return iter->second;
}


// ----------------------------------------------------------------------------
// Get the section from the file for the given name.
// ----------------------------------------------------------------------------
ConfigSection &ConfigFile::operator()(const String &a_name)
{
  ConfigSectionMap::iterator iter = m_sections.find(a_name);
  if (iter == m_sections.end())
  {
    LOG_ERROR << "The section: " << a_name << " does not exist" << ENDLOG;

    static ConfigSection badSection;
    return badSection;
  }

  return iter->second;
}


// ----------------------------------------------------------------------------
// Save the file with the given filename
// ----------------------------------------------------------------------------
bool ConfigFile::SaveAs(const String &a_filename)
{
  if (a_filename.empty())
    return false;

  m_filename = a_filename;
  s_tabOffset = 0;

  std::fstream file;
  file.open(a_filename.c_str(), std::ios_base::out);
  if (!file.is_open())
    return false;

  file << (*this);

  file << std::endl;
  file.close();
  return true;
}


// ----------------------------------------------------------------------------
// Load the file with the given filename
// ----------------------------------------------------------------------------
bool ConfigFile::Load(const String &a_filename)
{
  if (a_filename.empty())
    return false;

  s_tabOffset = 0;
  m_filename = a_filename;
  m_sections.clear();

  std::fstream file;
  file.open(a_filename.c_str(), std::ios_base::in);
  if (!file.is_open())
    return false;

  while (!file.eof())
  {
    String line;
    READ_LINE(line);

    TrimString(line);
    if (line.empty())
      continue;

    if (line.at(0) == '#')
      continue;

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
  }

  file.close();
  return true;
}


// ----------------------------------------------------------------------------
// Load the section from the given open file
// ----------------------------------------------------------------------------
bool ConfigFile::LoadSection(ConfigSection &a_section, std::fstream &a_file)
{
  std::fstream &file = a_file;

  while (!a_file.eof())
  {
    String line;
    READ_LINE(line);

    TrimString(line);
    if (line.empty())
      continue;

    if (line.at(0) == '#')
      continue;

    if (IsSectionEnd(line))
      return true;

    String key, value;
    if (ReadSectionValue(line, key, value))
    {
      a_section.Set(key, value);
      continue;
    }

    String name, type;
    if (ReadSectionData(line, name, type))
    {
      READ_LINE(line);
      if (!IsSectionStart(line))
        return false;

      ConfigSection &child = a_section.AddSection(type, name);
      if (!LoadSection(child, file))
        return false;
    }
    else
    {
      return false;
    }

    if (file.fail() || file.bad())
      return false;
  }

  return true;
}


// ----------------------------------------------------------------------------
// Append a config file
// ----------------------------------------------------------------------------
bool ConfigFile::Append(const ConfigFile &a_other)
{
  ConfigSectionMap::const_iterator other_iter(a_other.m_sections.begin()), other_end(a_other.m_sections.end());
  for (; other_iter != other_end; ++other_iter)
  {
    const ConfigSection &other_section = other_iter->second;

    bool found = false;
    ConfigSectionMap::iterator this_iter(m_sections.begin()), this_end(m_sections.end());
    for (; this_iter != this_end && !found; ++this_iter)
    {
      ConfigSection &this_section = this_iter->second;

      if (this_section.Name == other_section.Name)
      {
        if (this_section.Type != other_section.Type)
          return false;

        if (!this_section.Append(other_section))
          return false;

        found = true;
      }
    }

    if (!found)
      m_sections.insert(std::make_pair(other_section.Name, other_section));
  }
  return true;
}


// ----------------------------------------------------------------------------
// Append a config section
// ----------------------------------------------------------------------------
bool ConfigSection::Append(const ConfigSection &a_other)
{
  // Set all values from the supplied section
  ConfigValueMap::const_iterator iter(a_other.Items.begin()), end(a_other.Items.end());
  for (; iter != end; ++iter)
  {
    const ConfigValue &val = iter->second;
    Set(val.Key, val.Value);
  }

  // Process all child sections
  ConfigSectionMap::const_iterator other_iter(a_other.ChildSections.begin()), other_end(a_other.ChildSections.end());
  for (; other_iter != other_end; ++other_iter)
  {
    const ConfigSection &other_section = other_iter->second;

    bool found = false;
    ConfigSectionMap::iterator this_iter(ChildSections.begin()), this_end(ChildSections.end());
    for (; this_iter != this_end; ++this_iter)
    {
      ConfigSection &this_section = this_iter->second;

      if (this_section.Name == other_section.Name)
      {
        if (this_section.Type != other_section.Type)
          return false;

        if (!this_section.Append(other_section))
          return false;

        found = true;
      }
    }

    if (!found)
      ChildSections.insert(std::make_pair(other_section.Name, other_section));
  }
  return true;
}


// --------------------------------------------------------------------------
// Generates a unique key
// --------------------------------------------------------------------------
void ConfigFile::GenerateUniqueKey(String &a_key)
{
  static int uniqueKey = 10000;

  a_key = "AutoId:";
  AppendInt(a_key, uniqueKey);

  uniqueKey++;
}


// ----------------------------------------------------------------------------
// Read the line and extract the key and value
// ----------------------------------------------------------------------------
bool ConfigFile::ReadSectionValue(const String &a_in, String &a_key, String &a_value)
{
  String s = a_in;
  TrimString(s);

  int pos1 = (int) s.find_first_of("=");
  int pos2 = (int) s.find_first_of(";");

  // Read the key / value
  if (pos1 >= 0 && pos2 >= 0)
  {
    a_key   = s.substr(0, pos1);
    a_value = s.substr(pos1 + 1, pos2 - (pos1 + 1));

    TrimString(a_key);
    TrimString(a_value);

    return true;
  }

  // read the value and auto generate teh key
  else if (pos1 < 0 && pos2 >= 0)
  {
    GenerateUniqueKey(a_key);
    a_value = s.substr(0, s.length() - 1);

    TrimString(a_value);
    return true;
  }

  return false;
}


// ----------------------------------------------------------------------------
// Read the line and extract the name and type
// ----------------------------------------------------------------------------
bool ConfigFile::ReadSectionData(const String &a_in, String &a_name, String &a_type)
{
  String s = a_in;
  TrimString(s);

  int pos1 = (int) s.find_first_of("(");
  int pos2 = (int) s.find_first_of(")");

  if (pos1 < 0 && pos2 < 0)
    return false;

  a_type = s.substr(0, pos1);
  a_name = s.substr(pos1 + 1, pos2 - (pos1 + 1));

  TrimString(a_type);
  TrimString(a_name);

  if (a_name.empty())
    GenerateUniqueKey(a_name);

  return true;
}


// ----------------------------------------------------------------------------
// Is the given line a section start
// ----------------------------------------------------------------------------
bool ConfigFile::IsSectionStart(const String &a_in)
{
  String s = a_in;
  TrimString(s);
  return (s == "{");
}


// ----------------------------------------------------------------------------
// Is the given line a section end
// ----------------------------------------------------------------------------
bool ConfigFile::IsSectionEnd(const String &a_in)
{
  String s = a_in;
  TrimString(s);
  return (s == "}");
}


// ----------------------------------------------------------------------------
// Write the config value to the given output stream
// ----------------------------------------------------------------------------
OutputStream &operator<<(OutputStream &a_os, const ConfigValue &a_val)
{
  a_os << PadString(CONFIG_FILE_INDENT_SIZE, ' ') << a_val.Key << 
    " = " << a_val.Value << ";" << std::endl;
  return a_os;
}


// ----------------------------------------------------------------------------
// Insert the value to the given string
// ----------------------------------------------------------------------------
String &operator<<(String &a_str, const ConfigValue &a_val)
{
  a_str = a_val;
  return a_str;
}


// ----------------------------------------------------------------------------
// Insert the value into the given integer
// ----------------------------------------------------------------------------
int &operator<<(int &a_i, const ConfigValue &a_val)
{
  a_i = a_val;
  return a_i;
}


// ----------------------------------------------------------------------------
// Insert the value into the given the
// ----------------------------------------------------------------------------
float &operator<<(float &a_f, const ConfigValue &a_val)
{
  a_f = a_val;
  return a_f;
}


// ----------------------------------------------------------------------------
// Insert the value into the given boolean
// ----------------------------------------------------------------------------
bool &operator<<(bool &a_b, const ConfigValue &a_val)
{
  a_b = a_val;
  return a_b;
}


// ----------------------------------------------------------------------------
// Write the section to the output stream
// ----------------------------------------------------------------------------
OutputStream &operator<<(OutputStream &a_os, const ConfigSection &a_section)
{
  String offset = PadString(ConfigFile::GetTabOffset(), ' ');

  a_os << offset << a_section.Type << "(" << a_section.Name << ")" << std::endl;
  a_os << offset << "{" << std::endl;

  ConfigValueMap::const_iterator iter(a_section.Items.begin()), end(a_section.Items.end());
  for (; iter != end; ++iter)
    a_os << offset << iter->second;

  const ConfigSectionMap &sections = a_section.ChildSections;
  if (!sections.empty())
  {
    a_os << std::endl;

    ConfigFile::PushTab();

    ConfigSectionMap::const_iterator iter(sections.begin()), end(sections.end());
    for (; iter != end; ++iter)
      a_os << iter->second;

    ConfigFile::PopTab();
  }

  a_os << offset << "}" << std::endl;

  return a_os;
}


// ----------------------------------------------------------------------------
// Write the file to the given output stream
// ----------------------------------------------------------------------------
OutputStream &operator<<(OutputStream &a_os, const ConfigFile &a_file)
{
  const ConfigSectionMap &sections = a_file.GetSections();

  ConfigSectionMap::const_iterator iter(sections.begin()), end(sections.end());
  for (; iter != end; ++iter)
  {
    a_os << std::endl;
    a_os << iter->second;
  }

  return a_os;
}


// -- EOF

