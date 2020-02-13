// ----------------------------------------------------------------------------
// File: Logging.h
// Desc: Flexible logging class that provides logging to file, console, or the 
//       CRT window in VS .NET
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef LOGGING_H
#define LOGGING_H


// ----------------------------------------------------------------------------
// Do we want verbose logging, that is to know the filename and the line info, 
// and the date / time of the log (comment out to disable)
// ----------------------------------------------------------------------------
// #define VERBOSE_LOGGING


// ----------------------------------------------------------------------------
// Logging include files
// ----------------------------------------------------------------------------
#include "Kernel/Types.h"
#include "Kernel/StdMemory.h"
#include "Kernel/StdFunctional.h"
#include "Kernel/StdStr.h"
#include <sstream>


// ----------------------------------------------------------------------------
// Fucntions to get the time and the file / line stamp for the start of log 
// statements
// ----------------------------------------------------------------------------
String LoggerTime();
String LoggerStamp(const char *file, const int line);
String LoggerException(const GeneralException &e, const char *file, const int line);


#ifdef _DEBUG

// ----------------------------------------------------------------------------
// Convert the HRESULT to a string explaining the error
// ----------------------------------------------------------------------------
char *ConvertDxErrorToString(HRESULT hr);

#ifdef DX_DETAIL_LOGGING

// ----------------------------------------------------------------------------
// Name: DxLogInit
// Desc: Initialise the log file to capture all directx commands
// ----------------------------------------------------------------------------
inline void DxLogInit()
{
  static bool init = false;
  if (init)
    return;

  init = true;

  char buffer[256];
  sprintf(buffer, "Log Started at %s\n\n", LoggerTime().c_str());

  FILE *f = fopen("dx.log", "w");
  fwrite (buffer, strlen(buffer), 1, f);
  fwrite("\n", 1, 1, f);
  fclose(f);
  fflush(f);
} // DxLogInit

// ----------------------------------------------------------------------------
// Name: DxLog
// Desc: Write the command to the log file
// Parm: const char *file - the file that the command came from
// Parm: int line         - the line number of the file
// Parm: const char *msg  - the command
// ----------------------------------------------------------------------------
inline void DxLog(const char *file, int line, const char *msg)
{
  char buffer[256];
  sprintf(buffer, "%s (%d)\n", file, line);

  FILE *f = fopen("dx.log", "a+");
  fwrite (buffer, strlen(buffer), 1, f);
  fwrite(msg, strlen(msg), 1, f);
  fwrite("\n", 1, 1, f);
  fclose(f);
  fflush(f);
} // DxLog

// ----------------------------------------------------------------------------
// Name: DxLog
// Desc: Write the command to the log file
// Parm: const char *msg  - the command
// ----------------------------------------------------------------------------
inline void DxLog(const char *msg)
{
  FILE *f = fopen("dx.log", "a+");
  fwrite(msg, strlen(msg), 1, f);
  fwrite("\n\n", 2, 1, f);
  fclose(f);
  fflush(f);
} // DxLog

// ----------------------------------------------------------------------------
// Macro to check that a directx command succeeded.  If it failed, then the 
// error message is printed to the log using long format.
// ----------------------------------------------------------------------------
#define D3DCheck(x) { DxLogInit(); DxLog(__FILE__, __LINE__, #x); HRESULT hr = x; if (FAILED(hr)) DxLog(ConvertDxErrorToString(hr)); else DxLog("OK"); }

#else // !DX_DETAIL_LOGGING

// ----------------------------------------------------------------------------
// Macro to check that a directx command succeeded.  If it failed, then the 
// error message is printed to the log using short format.
// ----------------------------------------------------------------------------
#define D3DCheck(x) { HRESULT hr = x; if (FAILED(hr)) LOG_ERROR << ConvertDxErrorToString(hr) << ENDLOG; }

#endif // !DX_DETAIL_LOGGING

#else // !_DEBUG

// ----------------------------------------------------------------------------
// In release, we disable the directx command checking / logging.
// ----------------------------------------------------------------------------
#define D3DCheck(x) x;

#endif // !_DEBUG


// ----------------------------------------------------------------------------
// Check that the return code of a command is true. If it fails in debug mode an
// assertion is generated.  In release, the return code is ignored
// ----------------------------------------------------------------------------
#ifdef _DEBUG
# define Check(x,s) { bool res = (x); ASSERT(x,s); }
#else
# define Check(x,s) { x; }
#endif



// ----------------------------------------------------------------------------
// Name: Logger (class)
// Desc: The gneric logger class
// ----------------------------------------------------------------------------
class Logger
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  inline Logger();
  inline ~Logger();

  // --------------------------------------------------------------------------
  // Close off a line of the log
  // --------------------------------------------------------------------------
  struct EndLog { };
  inline Logger &operator<<(EndLog endlog);
  
  // --------------------------------------------------------------------------
  // Add a message or an exception to the log
  // --------------------------------------------------------------------------
  inline Logger &operator<<(const char *msg);
  inline Logger &LogException(const GeneralException &e, const char *file, const int line);

  // --------------------------------------------------------------------------
  // Insert any type that supports the extraction operator to the log
  // --------------------------------------------------------------------------
  template <typename T> 
  inline Logger &operator<<(const T &in);

  // --------------------------------------------------------------------------
  // Add a callback to the logger which is called for each line of text to be 
  // logged.
  // --------------------------------------------------------------------------
  inline void AddLoggerCB(const Callback<void, const char *> &cb);

  // --------------------------------------------------------------------------
  // Print hte string to the log
  // --------------------------------------------------------------------------
  void Out(const char *message);

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  StringStream                            message;    // Current line
  Array<Callback<void, const char *> *>   callbacks;  // The callbacks

}; // class Logger


// ----------------------------------------------------------------------------
// Name: Logger::Logger
// Desc: Constructor
// ----------------------------------------------------------------------------
inline Logger::Logger()
{
} // Logger


// ----------------------------------------------------------------------------
// Name: Logger::~Logger
// Desc: Destructor
// ----------------------------------------------------------------------------
inline Logger::~Logger()
{
  for (uint i = 0; i < callbacks.size(); i++)
    delete callbacks[i];
} // Logger


// ----------------------------------------------------------------------------
// Name: Logger::operator<<
// Temp: The type of the object to log
// Desc: write the object to the log using it's extraction operator
// Parm: const T &in - the object to log
// Retn: Logger &    - a reference to the logger
// ----------------------------------------------------------------------------
template <typename T> 
inline Logger &Logger::operator<<(const T &in)
{
  message << in;
  return *this;
} // operator<<


// ----------------------------------------------------------------------------
// Name: Logger::operator<<
// Desc: Write the string to the log
// Parm: const char *msg - the string
// Retn: Logger &        - a reference to the logger
// ----------------------------------------------------------------------------
inline Logger &Logger::operator<<(const char *msg)
{
  message << msg;
  return *this;
} // operator<<


// ----------------------------------------------------------------------------
// Name: Logger::LogException
// Desc: Write the exception to the log
// Parm: const GeneralException &e - the exception
// Parm: const char *file          - the file that the log was generated
// Parm: const int line            - the line that the log was generated
// Retn: Logger &                  - a reference to the logger
// ----------------------------------------------------------------------------
inline Logger &Logger::LogException(const GeneralException &e, const char *file, const int line)
{
  // Add the exception message
  message << "** ERROR **   " << e.what();

  // Check if we have a trace. Don't add it if we don't have one
  String str = e.GetTrace();
  if (!str.empty())
      message << std::endl << str;

  Out(message.str().c_str());
  message.str("");
  return *this;
} // LogException


// ----------------------------------------------------------------------------
// Name: Logger::operator<<
// Desc: Wrtite the end of the log
// Parm: EndLog endlog - the endlog
// Retn: Logger &      - a reference to the logger
// ----------------------------------------------------------------------------
inline Logger &Logger::operator<<(EndLog endlog)
{
  Out(message.str().c_str());
  message.str("");
  return *this;
} // operator<<


// ----------------------------------------------------------------------------
// Name: Logger::AddLoggerCB
// Desc: Add a callback to the logger
// Parm: const Callback<void, const char *> &cb - the callback
// ----------------------------------------------------------------------------
inline void Logger::AddLoggerCB(const Callback<void, const char *> &cb)
{
  callbacks.push_back(cb.Clone());
} // AddLoggerCB


// ----------------------------------------------------------------------------
// Name: Log (namespace)
// Desc: Logger namespace
// ----------------------------------------------------------------------------
namespace Log
{
  extern Logger *g_plogger;         // The global logger
  static Logger::EndLog g_end_log;  // The global endlog
}; // namespace Log


// ----------------------------------------------------------------------------
// Handy macros for using the logger
// ----------------------------------------------------------------------------
#define LOG               (*Log::g_plogger)
#define LOG_INFO          (*Log::g_plogger) << "** INFO  **   "
#define LOG_WARNING       (*Log::g_plogger) << "** WARN  **   "
#define LOG_ERROR         (*Log::g_plogger) << "** ERROR **   "
#define LOG_EXCEPTION(x)  Log::g_plogger->LogException(x,__FILE__,__LINE__)
#define LOG_CALLBACK(x)   Log::g_plogger->AddLoggerCB(MakeCallback(x))
#define ENDLOG            Log::g_end_log;


// ----------------------------------------------------------------------------
// Object Reference Counter
//
// Usage Notes:
//
// This reference counter only operates in debug mode (when _DEBUG is defined), 
// all other times all macros are replaced by no-ops.
//
// In the constructor of any object that you want to reference count, place the
// following code (where "ClassName" is the name of the class:
// 
//      REF_COUNT_CTOR(ClassName);
//
// And in the destructor place hte following code:
//
//      REF_COUNT_DTOR(ClassName);
//
// When the program is finished, the ReferenceCounter will display both a log of
// the order of creation and deletion of the objects, and the current status of
// all objects it was counting.
//
// From your main() method right at the start, you should setup the reference 
// counter if the defaults do not suit you. By default no incremental logging 
// will occur, just at the end of the application, a printout of the log and 
// status will be streamed to the logger.
//
// The following macros can be used to provide specific functions:
//
// REF_COUNT_PRINT;                 - Will print the current status of all 
//                                    registered objects.
//
// REF_COUNT_LOG                    - Will print a log of all object 
//                                    creations and deletions.
//
// REF_COUNT_ENABLE_ALL(bool)       - Toggle weather or not you want all objects
//                                    automatically registered (obviously you need
//                                    the CTOR and DTOR macros in those objects).
//
// REF_COUNT_ENABLE                 - Only used when REF_COUNT_ENABLE_ALL = false, to
//                                    specify which classes to care about.
//
// REF_COUNT_NO_LOG                 - Disables an object from the log, although it
//                                    will still reference count it and print it's totals.
//
// REF_COUNT_LOG_INCREMENTAL(bool)  - Toggle weather or not you want a debug message 
//                                    each time the constructor or destructor of a  
//                                    registered class is called.
//
// REF_COUNT_LOG_DETAIL(bool)       - Do we want to log in detail every time a class
//                                    is created or destroyd?
//
// REF_COUNT_HALT_ON_FINISH(bool)   - Toggle weather to halt the console window at the
//                                    end of the application after the log and status 
//                                    is printed (if true, calls getch()).
//
// REF_COUNT_TURN_OFF               - Turn the reference counter off
//
// REF_COUNT_CTOR(ClassName)        - Stick this in the constructor of any class
//
// REF_COUNT_DTOR(ClassName)        - Stick this in the destructor of any class
//
// The defaults are:
//
// REF_COUNT_ENABLE_ALL(true);
// REF_COUNT_LOG_INCREMENTAL(false);
// REF_COUNT_HALT_ON_FINISH(true);
//
// ----------------------------------------------------------------------------
#ifdef _DEBUG
#  define REF_COUNT_CTOR(x)             ReferenceCounterSingleton::Instance().AddInstance(#x)
#  define REF_COUNT_DTOR(x)             ReferenceCounterSingleton::Instance().RemoveInstance(#x)
#  define REF_COUNT_PRINT               ReferenceCounterSingleton::Instance().Debug()
#  define REF_COUNT_LOG                 ReferenceCounterSingleton::Instance().Log()
#  define REF_COUNT_ENABLE_ALL(x)       ReferenceCounterSingleton::Instance().SetEnableAll(x)
#  define REF_COUNT_ENABLE(x)           ReferenceCounterSingleton::Instance().Enable(#x)
#  define REF_COUNT_NO_LOG(x)           ReferenceCounterSingleton::Instance().DisableForLog(#x)
#  define REF_COUNT_LOG_INCREMENTAL(x)  ReferenceCounterSingleton::Instance().SetEnableIncrementalLog(x)
#  define REF_COUNT_LOG_DETAIL(x)       ReferenceCounterSingleton::Instance().SetFinalDetailLog(x)
#  define REF_COUNT_HALT_ON_FINISH(x)   ReferenceCounterSingleton::Instance().SetHaltOnFinish(x)
#  define REF_COUNT_TURN_OFF            ReferenceCounterSingleton::Instance().Disable();
#else
#  define REF_COUNT_CTOR(x)             ;
#  define REF_COUNT_DTOR(x)             ;
#  define REF_COUNT_PRINT               ;
#  define REF_COUNT_LOG                 ;
#  define REF_COUNT_ENABLE_ALL(x)       ;
#  define REF_COUNT_ENABLE(x)           ;
#  define REF_COUNT_NO_LOG(x)           ;
#  define REF_COUNT_LOG_INCREMENTAL(x)  ;
#  define REF_COUNT_LOG_DETAIL(x)       ;
#  define REF_COUNT_HALT_ON_FINISH(x)   ;
#  define REF_COUNT_TURN_OFF            ;
#endif


// ----------------------------------------------------------------------------
// We only use the refernce counter in debug
// ----------------------------------------------------------------------------
#ifdef _DEBUG

// ----------------------------------------------------------------------------
// Forward declaration
// ----------------------------------------------------------------------------
class ReferenceCounter;

// ----------------------------------------------------------------------------
// Typedef the SingletonHolder for the factory for easy access
// ----------------------------------------------------------------------------
typedef SingletonHolder<ReferenceCounter, 
CreateStatic<ReferenceCounter> > ReferenceCounterSingleton;

// ----------------------------------------------------------------------------
// Name: ReferenceCounter (class)
// Desc: Used for debug purposes only to help aid in finding where access 
//       violations are occurring.
// ----------------------------------------------------------------------------
class ReferenceCounter
{
public:
  // --------------------------------------------------------------------------
  // Name: AddInstance
  // Desc: Adds an instance to the refernece counter
  // Parm: const String &name - the name of the class
  // --------------------------------------------------------------------------
  void AddInstance(const String &name)
  {
    Map<String, void *>::iterator enable_iter = m_enabled_list.find(name);
    if (m_enable_all || enable_iter != m_enabled_list.end())
    {
      Map<String, int>::iterator iter = m_instances.find(name);
      if (iter == m_instances.end())
      {
        m_instances[name] = 1;
        m_max_instances[name] = 1;
        m_total_new[name] = 1;
      } // if
      else
      {
        m_instances[name] = iter->second + 1;
        m_max_instances[name] = std::max<int>(m_max_instances[name], m_instances[name]);
        m_total_new[name] += 1;
      } // else
      if (CanLog(name))
      {
        m_log.push_back(String("new:    ") + name);
      } // if
      if (m_enable_incremental_log && CanLog(name))
      {
        LOG << "** DEBUG ** - Reference Counter - " << "new:    " << name << ENDLOG;
      } // if
    } // if
  } // AddInstance


  // --------------------------------------------------------------------------
  // Name: RemoveInstance
  // Desc: Removes a instance from the reference counter
  // Parm: const String &name - the name of the class
  // --------------------------------------------------------------------------
  void RemoveInstance(const String &name)
  {
    Map<String, void *>::iterator enable_iter = m_enabled_list.find(name);
    if (m_enable_all || enable_iter != m_enabled_list.end())
    {
      Map<String, int>::iterator iter = m_instances.find(name);
      if (iter == m_instances.end())
      {
        m_instances[name] = -1;
        m_total_delete[name] = 1;
      } // if
      else
      {
        m_instances[name] = iter->second - 1;
        m_total_delete[name] += 1;
      } // else
      if (CanLog(name))
      {
        m_log.push_back(String("delete: ") + name);
      } // if
      if (m_enable_incremental_log && CanLog(name))
      {
        LOG << "** DEBUG ** - Reference Counter - " << "delete: " << name << ENDLOG;
      } // if
    } // if
  } // RemoveInstance


  // --------------------------------------------------------------------------
  // Name: Debug
  // Desc: Debugs the current state of the object managed by the reference 
  //       counter
  // --------------------------------------------------------------------------
  void Debug()
  {
    LOG << "** DEBUG ** - Reference Counter - " << "Object                               New    Del    Max    Now" << ENDLOG;
    LOG << "** DEBUG ** - Reference Counter - " << "---------------------------          ----   ----   ----   ----" << ENDLOG;
    Map<String, int>::iterator iter;
    for (iter = m_instances.begin(); iter != m_instances.end(); ++iter)
    {
      String ref_count = iter->first;
      int max_instances = m_max_instances[ref_count];
      int tot_new = m_total_new[ref_count];
      int tot_del = m_total_delete[ref_count];
      ref_count.push_back(':');
      const int padding = 7;
      while (ref_count.size() < 29)
      {
        ref_count.push_back(' ');
      } // while
      LOG << "** DEBUG ** - Reference Counter - " << "Object: " << 
        ref_count << PadInt(tot_new, padding) << PadInt(tot_del, padding) << 
        PadInt(max_instances, padding) << PadInt(iter->second, padding) << ENDLOG;
    } // for
  } // Debug


  // --------------------------------------------------------------------------
  // Name: Log
  // Desc: Displays a log of the history and order that objects are created and 
  //       deleted
  // --------------------------------------------------------------------------
  void Log()
  {
    List<String>::iterator iter;
    for (iter = m_log.begin(); iter != m_log.end(); ++iter)
    {
      LOG << "** DEBUG ** - Reference Counter - " << *iter << ENDLOG;
    } // for
  } // Log


  // --------------------------------------------------------------------------
  // Name: Disable
  // Desc: Disable the reference counter
  // --------------------------------------------------------------------------
  void Disable()
  {
    m_enabled = false; 
  } // Disable


  // --------------------------------------------------------------------------
  // Name: SetEnableAll
  // Desc: Do we enable all objects (defaults to true)
  // Parm: bool enable_all - if true, then all objects that implement the 
  //                         macros will be added to the reference counter
  // --------------------------------------------------------------------------
  void SetEnableAll(bool enable_all)
  {
    m_enable_all = enable_all; 
  } // SetEnableAll


  // --------------------------------------------------------------------------
  // Name: Enable
  // Desc: Enable a specific object
  // Parm: const String &name - the name of the object to enable
  // Note: Use when SetEnableAll is set to false to specify a select number 
  //       of objects to monitor
  // --------------------------------------------------------------------------
  void Enable(const String &name)
  {
    m_enabled_list[name] = 0; 
  } // Enable


  // --------------------------------------------------------------------------
  // Name: SetEnableIncrementalLog
  // Desc: Enable incremental logging
  // Parm: bool enable_log - If true, then a log is printed each time an object 
  //                         is added or removed from the reference counter
  // --------------------------------------------------------------------------
  void SetEnableIncrementalLog(bool enable_log)
  {
    m_enable_incremental_log = enable_log; 
  } // SetEnableIncrementalLog


  // --------------------------------------------------------------------------
  // Name: SetHaltOnFinish
  // Desc: Enable halting on finish (requires you to press a key before the 
  //       application console window dissapears).  This allows you to see the 
  //       log and status before the console dissapears when running through 
  //       VisualStudio.
  // Parm: bool halt_on_finish - if true then getch() is called
  // --------------------------------------------------------------------------
  void SetHaltOnFinish(bool halt_on_finish)
  {
    m_halt_on_finish = halt_on_finish; 
  } // SetHaltOnFinish


  // --------------------------------------------------------------------------
  // Name: SetFinalDetailLog
  // Desc: De we display the final detail log
  // Parm: bool log_detail - if true then the final detail log is displayed
  // --------------------------------------------------------------------------
  void SetFinalDetailLog(bool log_detail)
  {
    m_final_detail_log = log_detail; 
  } // SetFinalDetailLog


  // --------------------------------------------------------------------------
  // Name: DisableForLog
  // Desc: Disables an object from the log, but retains it's reference count
  // Parm: const String &name - the class name
  // --------------------------------------------------------------------------
  void DisableForLog(const String &name) { m_disabled_log_list[name] = 0; }

private:
  // --------------------------------------------------------------------------
  // Only the CreateUsingNew struct on the SingeltonHolder has access to 
  // call the constructor
  // --------------------------------------------------------------------------
  friend struct CreateStatic<ReferenceCounter>;

  // --------------------------------------------------------------------------
  // Default constructor
  // --------------------------------------------------------------------------
  ReferenceCounter() 
  : m_enabled                 (true),
    m_enable_all              (true),
    m_enable_incremental_log  (false), 
    m_halt_on_finish          (true),
    m_final_detail_log        (false)
  {}

  // --------------------------------------------------------------------------
  // Default destructor
  // --------------------------------------------------------------------------
  ~ReferenceCounter() 
  {
    if (!m_enabled)
      return;

    if (m_final_detail_log)
    {
      LOG << "** DEBUG ** - Reference Counter - " << "*************** Log Of Object Creation and Deletion **************" << ENDLOG;
      Log();
    } // if
    LOG << "** DEBUG ** - Reference Counter - " << "********************** Current Object Status *********************" << ENDLOG;
    Debug();
    LOG << "** DEBUG ** - Reference Counter - " << "******************************************************************" << ENDLOG;

    if (m_halt_on_finish)
    {
      LOG << "** DEBUG ** - Reference Counter - " << "The Reference Counter has paused the application, press any key to exit..." << ENDLOG;
      getch();
    } // if
  } // ~ReferenceCounter


  // --------------------------------------------------------------------------
  // Name: CanLog
  // Desc: Determine if the given class name can write to the log
  // Parm: const String &name - the class name
  // Retn: bool             - true if the classname is allowed to log
  // --------------------------------------------------------------------------
  bool CanLog(const String &name)
  {
    return (m_disabled_log_list.find(name) == m_disabled_log_list.end());
  } // CanLog


  // --------------------------------------------------------------------------
  // Name: PadInt
  // Desc: Write the integer and add trailing whitespace
  // Parm: int num           - the number
  // Parm: unsigned int width - the width of the string
  // Retn: String            - the string
  // --------------------------------------------------------------------------
  String PadInt(int num, unsigned int width)
  {
    String str;
    AppendInt(str, num);

    while (str.length() < width)
      str += " ";

    return str;
  } // PadInt


  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  Map<String, int>      m_instances;              // Instance data
  Map<String, int>      m_max_instances;          // Max Instance data
  Map<String, int>      m_total_new;              // Total news
  Map<String, int>      m_total_delete;           // Total deletes
  List<String>          m_log;                    // Log in order
  Map<String, void *>   m_enabled_list;           // List of enabled objects
  Map<String, void *>   m_disabled_log_list;      // List of disabled log objects
  bool                  m_enable_all;             // Are all objects enabled?
  bool                  m_enable_incremental_log; // Do we incrementally log?
  bool                  m_halt_on_finish;         // Do we halt on finish?
  bool                  m_final_detail_log;       // Do we want a detailed log at the end?
  bool                  m_enabled;                // Is the whole thing enabled?

}; // class ReferenceCounter

#endif // _DEBUG


#endif // LOGGING_H

// -- EOF
