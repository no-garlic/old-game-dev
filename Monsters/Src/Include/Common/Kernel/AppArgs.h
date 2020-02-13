// ----------------------------------------------------------------------------
// File: AppArgs.h
// Desc: Extracts the arguments and optios passed to the application
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __APP_ARGS_H_
#define __APP_ARGS_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Kernel/Types.h"
#include "Kernel/StdMemory.h"
#include "Kernel/StdStr.h"
#include "Kernel/Logging.h"


// ----------------------------------------------------------------------------
// Singleton Accessor
// ----------------------------------------------------------------------------
class   AppArgsCache;
typedef SingletonHolder<AppArgsCache, CreateUsingNew<AppArgsCache> > AppArgsSingleton;
#define AppArgs AppArgsSingleton::Instance()


// ----------------------------------------------------------------------------
// Name: AppArgsCache  (class)
// Desc: Extracts the arguments and optios passed to the application
// ----------------------------------------------------------------------------
class AppArgsCache : private Unique
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  AppArgsCache()  { REF_COUNT_CTOR(AppArgs); }
  ~AppArgsCache() { REF_COUNT_DTOR(AppArgs); }

  // --------------------------------------------------------------------------
  // Append the args and optins form the given string
  // --------------------------------------------------------------------------
  void Append(const String &options);

  // --------------------------------------------------------------------------
  // Checks if an option exists
  // --------------------------------------------------------------------------
  bool HasOption(const char *option);
  bool operator()(const char *option) { return HasOption(option); }

  // --------------------------------------------------------------------------
  // Get the args and options
  // --------------------------------------------------------------------------
  const StringArray &GetOptionArgs(const char *option);
  const StringArray &GetDefaultArgs() { return m_default_args; }

  // --------------------------------------------------------------------------
  // List the options
  // --------------------------------------------------------------------------
  bool IsEmpty() const  { return m_options.empty() && m_default_args.empty(); }
  StringArray ListOptions();

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  Map<String, StringArray>    m_options;
  StringArray                 m_default_args;

}; // class AppArgsCache


#endif // __APP_ARGS_H_

// -- EOF
