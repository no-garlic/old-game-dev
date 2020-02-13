// ----------------------------------------------------------------------------
// File: Logging.cpp
// Desc: Flexible logging class that provides logging to file,console, or the 
//       CRT window in VS .NET
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Logging include files
// ----------------------------------------------------------------------------
#include "Common/Logging.h"
#include <string>
#include <sstream>
#include <time.h>
#include <crtdbg.h>


// ----------------------------------------------------------------------------
// Name: LoggerTime
// Desc: Gets the current time as a string
// Retn: std::string - the time
// ----------------------------------------------------------------------------
std::string LoggerTime()
{
    char ptime_str[128];
    time_t m_time_stamp = time(0);
    strftime(ptime_str, sizeof(ptime_str), "%d/%m/%y %H:%M:%S", localtime(&m_time_stamp));
    return ptime_str;
} // LoggerTime


// ----------------------------------------------------------------------------
// Name: LoggerStamp
// Desc: Get the file and line stamp as a string, and remove the path from the 
//       file.
// Parm: const char *file - the file (use __FILE__)
// Parm: const int line   - the line (use __LINE__)
// Retn: std::string      - the file and line as a string
// ----------------------------------------------------------------------------
std::string LoggerStamp(const char *file, const int line)
{
    std::string m_file = file;
    std::string out;
    std::string file_str;

    // Remove the path from the filename
    file_str = m_file.substr(m_file.insert(
        std::string::size_type(0), 1, '\\').find_last_of('\\'));
    file_str = file_str.substr(file_str.insert(
        std::string::size_type(0), 1, '/').find_last_of('/'));

    // Add a comma
    out.append(", ");
    out.append(file_str.substr(file_str.find_first_not_of("\\/")));
    
    // Add the line
    out.append(" [");
    char str_line[32];
    sprintf(str_line, "%d", line);
    out.append(str_line);
    out.append("] - ");

    // Return the string
    return out;
} // LoggerStamp


// ----------------------------------------------------------------------------
// Name: LoggerException
// Desc: Create a string containing a formatted exception log
// Parm: const GeneralException &e - the exception to log
// Parm: const char *file          - the filename
// Parm: const int line            - the line
// Retn: std::string               - the string
// ----------------------------------------------------------------------------
std::string LoggerException(const GeneralException &e, const char *file, const int line)
{
    std::stringstream ss;

    // Add the exception message
    ss << "** ERROR **   " << LoggerTime() << LoggerStamp(file, line);
    ss << e.what();

    // Check if we have a trace. Don't add it if we don't have one
    std::string str = e.GetTrace();
    if (!str.empty())
        ss << std::endl << str;
    
    ss << std::endl;

    return ss.str();
} // LoggerException


// ----------------------------------------------------------------------------
// Logger class implementation for CRT debug in windows, using _RPT as the 
// destination
// ----------------------------------------------------------------------------
#ifdef LOG_TO_CRT


// ----------------------------------------------------------------------------
// Name: Logger::StartLog
// Desc: Start a log statement
// Retn: Logger & - a reference to the logger
// ----------------------------------------------------------------------------
Logger &Logger::StartLog()
{
    return *this;
} // StartLog


// ----------------------------------------------------------------------------
// Name: Logger::LogException
// Desc: Log an exception to the CRT
// Parm: const GeneralException &e - the exception to log
// Parm: const char *file          - the filename
// Parm: const int line            - the line
// Retn: Logger &                  - the logger
// ----------------------------------------------------------------------------
Logger &Logger::LogException(const GeneralException &e, const char *file, const int line)
{
    _RPT1(0, "%s", LoggerException(e, file, line));
    return *this;
} // LogException


// ----------------------------------------------------------------------------
// Name: Logger::operator<<
// Desc: Insert a string into the logger
// Parm: const std::string &input - the string to insert
// Retn: Logger &                 - a reference to the logger
// ----------------------------------------------------------------------------
Logger &Logger::operator<<(const std::string &input) throw()
{
    _RPT1(0, "%s", input.c_str());
    return *this;
} // operator<<


// ----------------------------------------------------------------------------
// Name: Logger::operator<<
// Desc: Insert a double into the logger
// Parm: const double &input - the value
// Retn: Logger &            - a reference to the logger
// ----------------------------------------------------------------------------
Logger &Logger::operator<<(const double &input) throw()
{
    _RPT1(0, "%02.02f", input);
    return *this;
} // operator<<


// ----------------------------------------------------------------------------
// Name: Logger::operator<<
// Desc: Insert an integer into the logger
// Parm: const int &input - the value
// Retn: Logger &         - a reference to the logger
// ----------------------------------------------------------------------------
Logger &Logger::operator<<(const int &input) throw()
{
    _RPT1(0, "%d", input);
    return *this;
} // operator<<


// ----------------------------------------------------------------------------
// Name: Logger::operator<<
// Desc: Insert an unsigned long into the logger
// Parm: const unsigned long &input - the value
// Retn: Logger &                   - a reference to the logger
// ----------------------------------------------------------------------------
Logger &Logger::operator<<(const unsigned long &input) throw()
{
    _RPT1(0, "%ul", input);
    return *this;
} // operator<<


// ----------------------------------------------------------------------------
// Name: Logger::operator<<
// Desc: Insert a sze_t into the logger
// Parm: const size_t &input - the value
// Retn: Logger &            - a reference to the logger
// ----------------------------------------------------------------------------
Logger &Logger::operator<<(const size_t &input) throw()
{
    _RPT1(0, "%d", (int) input);
    return *this;
} // operator<<


// ----------------------------------------------------------------------------
// Name: Logger::EndLog
// Desc: End the log statement
// Retn: const std::string & - a reference to a null string
// ----------------------------------------------------------------------------
const std::string &Logger::EndLog()
{
    _RPT0(0, "\n");

    static std::string null_string;
    return null_string;    
} // EndLog


#endif // LOG_TO_CRT


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
    // ------------------------------------------------------------------------
    // Name: FileWatcher (class)
    // Desc: Opens and closes a file by holding it on the stack
    // ------------------------------------------------------------------------
    class FileWatcher
    {
    public:
        // --------------------------------------------------------------------
        // Name: GetFile
        // Desc: Get teh file from the wrapper class
        // Retn: std::fstream & - the file stream
        // --------------------------------------------------------------------
        std::fstream &GetFile()
        { 
            return m_file;
        } // GetFile

        
        // --------------------------------------------------------------------
        // Name: FileWatcher
        // Desc: Constructor
        // --------------------------------------------------------------------
        FileWatcher()
        {
            m_file.open("log.txt", std::ios_base::out);
        } // FileWatcher

        
        // --------------------------------------------------------------------
        // Name: ~FileWatcher
        // Desc: Destructor
        // --------------------------------------------------------------------
        ~FileWatcher()
        {
            m_file.close();
        } // ~FileWatcher


    private:
        // The log file
        std::fstream m_file;
    }; // FileWatcher

    
    // ------------------------------------------------------------------------
    // The global file instance
    // ------------------------------------------------------------------------
    FileWatcher g_file;


    // ------------------------------------------------------------------------
    // Name: LogFileRef
    // Desc: Get the file pointer
    // Retn: std::fstream & - the file stream
    // ------------------------------------------------------------------------
    std::fstream &LogFileRef()
    {
        return g_file.GetFile();
    } // LogFileRef


}; // namespace Logging


#endif // LOG_TO_FILE

// -- EOF
