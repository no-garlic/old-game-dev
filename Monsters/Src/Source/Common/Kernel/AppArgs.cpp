// ----------------------------------------------------------------------------
// File: AppArgs.cpp
// Desc: Extracts the arguments and optios passed to the application
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Kernel/AppArgs.h"


// ----------------------------------------------------------------------------
// Name: AppArgsCache::Append
// Desc: Append the aopions and args from hte supplied string to the cache
// Parm: const String &options - the options string
// ----------------------------------------------------------------------------
void AppArgsCache::Append(const String &options)
{
  // Seperate the string into tokens
  StringArray tokens = Tokenize(options);

  // Find all options and args
  StringArray args;
  String option;
  StringArray::iterator iter = tokens.begin();
  for (; iter != tokens.end(); ++iter)
  {
    const String &token = *iter;

    if (token[0] == '-')
    {
      // This is an option
      if (option.empty())
      {
        // This is the first option
        option = token;
      } // if
      else
      {
        // Time to store the current option and start a new one
        Map<String, StringArray >::iterator iter = m_options.find(option);
        if (iter == m_options.end())
          m_options.insert(MakePair(option, args));
        else
          iter->second.insert(iter->second.end(), args.begin(), args.end());

        option = token;
        args.clear();
      } // else
    } // if
    else
    {
      // This is an arg
      if (option.empty())
      {
        // We dont have an option (before the first option), so this is a default arg
        m_default_args.push_back(token);
      } // if
      else
      {
        // We have an option, so this is an arg
        args.push_back(token);
      } // else
    } // else
  } // for

  // Store the last option
  if (!option.empty())
  {
    Map<String, StringArray >::iterator iter = m_options.find(option);
    if (iter == m_options.end())
      m_options.insert(MakePair(option, args));
    else
      iter->second.insert(iter->second.end(), args.begin(), args.end());
  } // if
} // Append


// ----------------------------------------------------------------------------
// Name: AppArgsCache::HasOption
// Desc: Check if the given option exists in the cache
// Parm: const char *option - the option
// Retn: bool               - true if it exists
// ----------------------------------------------------------------------------
bool AppArgsCache::HasOption(const char *option)
{
  String search(option);
  ToUpper(search);

  Map<String, StringArray>::iterator iter(m_options.begin()), end(m_options.end());
  for (; iter != end; ++iter)
  {
    String opt = iter->first;
    ToUpper(opt);

    if (opt == search)
      return true;
  } // for

  return false;
} // HasOption


// ----------------------------------------------------------------------------
// Name: AppArgsCache::GetOptionArgs
// Desc: Get the array of arguments for the given option
// Parm: const char *option  - the option
// Retn: const StringArray & - the arraay of args
// ----------------------------------------------------------------------------
const StringArray &AppArgsCache::GetOptionArgs(const char *option)
{
  String search(option);
  ToUpper(search);

  Map<String, StringArray>::iterator iter(m_options.begin()), end(m_options.end());
  for (; iter != end; ++iter)
  {
    String opt = iter->first;
    ToUpper(opt);

    if (opt == search)
      return iter->second;
  } // for

  static StringArray null_options;
  return null_options;    
} // GetOptionArgs


// ----------------------------------------------------------------------------
// Name: AppArgsCache::ListOptions
// Desc: List all options in the cache
// Retn: StringArray - the array of options
// ----------------------------------------------------------------------------
StringArray AppArgsCache::ListOptions()
{
  StringArray options;

  Map<String, StringArray>::iterator iter(m_options.begin()), end(m_options.end());
  for (; iter != end; ++iter)
    options.push_back(iter->first);

  return options;
} // ListOptions


// -- EOF

