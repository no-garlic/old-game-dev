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
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Common/Utilities.h"
#include "Common/Exceptions.h"


// ----------------------------------------------------------------------------
// Fucntions to get the time and the file / line stamp for the start of log 
// statements
// ----------------------------------------------------------------------------
std::string LoggerTime();
std::string LoggerStamp(const char *file, const int line);
std::string LoggerException(const GeneralException &e, const char *file, const int line);


// ----------------------------------------------------------------------------
// Automatically log to the console if it is available, otherwise log tothe cRT 
// by default.  if LOG_TO_FILE is defined, then the log will go to file rather 
// than to the CRT.
// ----------------------------------------------------------------------------
#ifdef _CONSOLE
# define LOG_TO_CONSOLE
#else
# ifndef LOG_TO_FILE
#  define LOG_TO_CRT
# endif
#endif


// ----------------------------------------------------------------------------
// Console logging uses std::cout and does normal stream insertion
// ----------------------------------------------------------------------------
#ifdef LOG_TO_CONSOLE

#ifdef VERBOSE_LOGGING
# define LOG_INFO            std::cout << "** INFO **    " << LoggerTime() << LoggerStamp(__FILE__, __LINE__)
# define LOG_WARNING         std::cout << "** WARNING ** " << LoggerTime() << LoggerStamp(__FILE__, __LINE__)
# define LOG_ERROR           std::cout << "** ERROR **   " << LoggerTime() << LoggerStamp(__FILE__, __LINE__)
#else
# define LOG_INFO            std::cout << "** INFO **    " 
# define LOG_WARNING         std::cout << "** WARNING ** " 
# define LOG_ERROR           std::cout << "** ERROR **   " 
#endif
#define LOG_EXCEPTION(x)    std::cout << LoggerException(x,__FILE__, __LINE__)
#define LOG                 std::cout
#define ENDLOG              std::endl

#endif


// ----------------------------------------------------------------------------
// Logger class implementation for file logging using the file log.txt in the 
// current directory
// ----------------------------------------------------------------------------
#ifdef LOG_TO_FILE


// ----------------------------------------------------------------------------
// Name: Logging (namespace)
// Desc: Holds the log file refernce
// ----------------------------------------------------------------------------
namespace Logging
{
    std::fstream &LogFileRef(); // Object to do the file logging
}; // namespace Logging


#ifdef VERBOSE_LOGGING
# define LOG_INFO            Logging::LogFileRef() << "** INFO **    " << LoggerTime() << LoggerStamp(__FILE__, __LINE__)
# define LOG_WARNING         Logging::LogFileRef() << "** WARNING ** " << LoggerTime() << LoggerStamp(__FILE__, __LINE__)
# define LOG_ERROR           Logging::LogFileRef() << "** ERROR **   " << LoggerTime() << LoggerStamp(__FILE__, __LINE__)
#else
# define LOG_INFO            Logging::LogFileRef() << "** INFO **    "
# define LOG_WARNING         Logging::LogFileRef() << "** WARNING ** "
# define LOG_ERROR           Logging::LogFileRef() << "** ERROR **   "
#endif
#define LOG_EXCEPTION(x)    Logging::LogFileRef() << LoggerException(x,__FILE__, __LINE__)
#define LOG                 Logging::LogFileRef()
#define ENDLOG              std::endl

#endif


// ----------------------------------------------------------------------------
// Windows CRT debug logging uses _RPT as the destination to forward the log 
// statements to.
// ----------------------------------------------------------------------------
#ifdef LOG_TO_CRT


// ----------------------------------------------------------------------------
// Name: Logger  (class)
// Desc: Logger class for the CRT logger
// ----------------------------------------------------------------------------
class Logger : private Utility::Unique
{
public:
    // ------------------------------------------------------------------------
    // Start and end a log
    // ------------------------------------------------------------------------
    Logger              &StartLog();
    Logger              &LogException(const GeneralException &e, const char *file, const int line);
    const std::string   &EndLog();
    
    
    // ------------------------------------------------------------------------
    // Add a log message
    // ------------------------------------------------------------------------
    Logger &operator<<(const std::string &input) throw();
    Logger &operator<<(const double &input) throw();
    Logger &operator<<(const int &input) throw();
    Logger &operator<<(const unsigned long &input) throw();
    Logger &operator<<(const size_t &input) throw();
}; // class Logger


// ----------------------------------------------------------------------------
// Singleton accessor for the logger
// ----------------------------------------------------------------------------
typedef Singleton::SingletonHolder<Logger, Singleton::CreateStatic<Logger> > LoggerSingleton;

#ifdef VERBOSE_LOGGING
# define LOG_INFO            LoggerSingleton::Instance().StartLog() << "** INFO **    " << LoggerTime() << LoggerStamp(__FILE__, __LINE__)
# define LOG_WARNING         LoggerSingleton::Instance().StartLog() << "** WARNING ** " << LoggerTime() << LoggerStamp(__FILE__, __LINE__)
# define LOG_ERROR           LoggerSingleton::Instance().StartLog() << "** ERROR **   " << LoggerTime() << LoggerStamp(__FILE__, __LINE__)
#else
# define LOG_INFO            LoggerSingleton::Instance().StartLog()
# define LOG_WARNING         LoggerSingleton::Instance().StartLog()
# define LOG_ERROR           LoggerSingleton::Instance().StartLog()
#endif
#define LOG_EXCEPTION(x)    LoggerSingleton::Instance().LogException(x,__FILE__, __LINE__)
#define LOG                 LoggerSingleton::Instance().StartLog()
#define ENDLOG              LoggerSingleton::Instance().EndLog()

#endif


#endif // LOGGING_H

// -- EOF
