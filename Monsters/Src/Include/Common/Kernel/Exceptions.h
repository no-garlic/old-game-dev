// ----------------------------------------------------------------------------
// File: Exceptions.h
// Desc: Standard exception classes
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


// ----------------------------------------------------------------------------
// Exception includes
// ----------------------------------------------------------------------------
#include <deque>
#include <exception>
#include <string>
#include <sstream>


// ----------------------------------------------------------------------------
// Handy macro for the file and line stamp
// ----------------------------------------------------------------------------
#define FLSTAMP __FILE__,__LINE__


// ----------------------------------------------------------------------------
// Name: GeneralException  (class)
// Desc: Base exception class that all exceptions code should derive from. 
//       Implements key base functionality such as insertion, description 
//       retrieval, file/line stamping , and stack tracing. Note: This is not a 
//       thread safe class, as all functions here are throw(). Please don't 
//       contrive a situation where you wan't multiple threads to concurrently 
//       access the same exception object!
// ----------------------------------------------------------------------------
class GeneralException : public std::exception
{
public:
    // ------------------------------------------------------------------------
    // A variety of constructors. Missing copy constructor and assignment 
    // because default implementation is good
    // ------------------------------------------------------------------------
    GeneralException() throw()
        : m_pfile(0), m_line(0) {}
    explicit GeneralException(const char *pdesc) throw()
        : m_pfile(0), m_line(0), m_what(pdesc) {}
    GeneralException(const char *pfile, int line) throw()
        : m_pfile(pfile), m_line(line) {}
    GeneralException(const char *pfile, int line, const char *pdesc) throw()
        : m_pfile(pfile), m_line(line), m_what(pdesc) {}
    virtual ~GeneralException() throw() {}

    
    // ------------------------------------------------------------------------
    // Name: operator<<
    // Temp: The type of object being inserted
    // Desc: Insertion operator used to add text to the description string that 
    //       was initialised during construction. This is particularly useful 
    //       for adding numbers to the string (not easy to do with const char * 
    //       or String), or generating the error string based on some 
    //       logical conditions.  Note - std::ostream must understand how to 
    //       insert the object of type T, otherwise this will fail to compile.
    // Parm: const T &in        - the object to be inserted
    // Retn: GeneralException & - a reference to the exception, for furthur 
    //       inserting or throwing.
    // ------------------------------------------------------------------------
    template <typename T>
    GeneralException &operator<<(const T &in)
    {
        std::ostringstream oss;
        oss << in;
        m_what += oss.str();

        return *this;
    } // operator<<


    // ------------------------------------------------------------------------
    // Name: AddStackTrace
    // Desc: Adds a stack trace to the stack trace string (optional). Note: It 
    //       might be easier to use FLSTAMP instead of __FILE__, __LINE__
    // Parm: const char *pfile  - the filename
    // Parm: int line           - the line number of the file
    // Parm: const char *pdesc = 0 - the optional description for the stack
    // ------------------------------------------------------------------------
    void AddStackTrace(const char *pfile, int line, const char *pdesc = 0) throw()
    {
        // Format the trace, and add it to the string
        m_stack_trace.push_back(FormatTrace(pfile, line, pdesc));
    } // AddStackTrace

    
    // ------------------------------------------------------------------------
    // Name: CopyStackTrace
    // Desc: Given another exception, this copies the stack trace from that 
    //       exception, including the initial file and line , so that it can be 
    //       thrown as a different type of exception.
    // Parm: const GeneralException &e - the exception to copy from
    // ------------------------------------------------------------------------
    void CopyStackTrace(const GeneralException &e) throw()
    {
        // Add the stack trace of the supplied exception at the front of
        // our stack trace queue (so the exception we are copying appeared
        // to come before us.
        m_stack_trace.insert(m_stack_trace.begin(), e.m_stack_trace.begin(), e.m_stack_trace.end());

        // Add a stack trace for the file and line at which this exception
        // was created
        AddStackTrace(m_pfile, m_line);

        // Give us the same starting file and line as this exception
        m_pfile = e.m_pfile ;
        m_line  = e.m_line;
    } // CopyStackTrace


    // ------------------------------------------------------------------------
    // Name: what
    // Desc: Retrieves the description of the exception. Base functionality 
    //       defined in std::exception.  Note: The pointer returned is only 
    //       valid until the error string is changed, such as through 
    //       destruction of the exception, or insertion.
    // Retn: const char * - the pointer to the error string
    // ------------------------------------------------------------------------
    virtual const char *what() const throw()
    {
        GetDescription();
        return m_what_ret.c_str();
    } // what


    // ------------------------------------------------------------------------
    // Retrieval functions - fairly obvious usage
    // ------------------------------------------------------------------------
    virtual std::string GetDescription() const throw() { return m_what_ret = m_what; }
    const char         *GetFileStamp  () const throw() { return m_pfile;             }
    int                 GetLineStamp  () const throw() { return m_line;              }


    // ------------------------------------------------------------------------
    // Name: GetTrace
    // Desc: Get the stack trace from the exception
    // Retn: String - the stack trace in a printable form
    // ------------------------------------------------------------------------
    std::string GetTrace() const throw()
    {
        std::string ret = "";

        // Iterate through the queue and construct the trace string
        std::deque<std::string>::const_iterator iter;
        for (iter = m_stack_trace.begin(); iter != m_stack_trace.end(); ++iter)
            ret += *iter;

        return ret;
    } // GetTrace


    // ------------------------------------------------------------------------
    // Name: ExceptionCast
    // Temp: R - the type of the exception to return.
    // Temp: A - the current exception we want to cast from.
    // Desc: Casts from one type of exception to another, maintaining the 
    //       description and the stack trace.
    // Parm: const GeneralException &old - The exception to cast from
    // Parm: const char *pfile = 0   - the filename
    // Parm: int line = 0            - the line number
    // Retn: R                       - The new exception, of type R. This is 
    //       returned by value so that it is on the stack and can easily be 
    //       thrown.
    // ------------------------------------------------------------------------
    template <class R>
    static R ExceptionCast(const GeneralException &old, const char *pfile = 0, int line = 0)
    {
        // Create the new exception, and copy the stack trace
        // Use the file and line supplied, if they were
        R new_exception(pfile ? pfile : old.m_pfile, (line != 0) ? line : old.m_line);

        // Copy the description and stack trace
        new_exception.m_what = old.GetDescription();
        new_exception.CopyStackTrace(old);

        return new_exception;
    } // ExceptionCast


private:
    // ------------------------------------------------------------------------
    // Name: FormatTrace
    // Desc: Function to format a stack trace
    // Parm: const char *pfile  - the filename
    // Parm: int line           - the line
    // Parm: const char *pdesc = 0 - the description
    // Retn: String        - the formatted trace
    // ------------------------------------------------------------------------
  static std::string FormatTrace(const char *pfile, int line, const char *pdesc = 0)
    {
        // Location (get the filename from the path)
        // Add two characters to ensure this algorithm works
        std::string file_str(pfile);
        file_str = file_str.substr(file_str.insert(std::string::size_type(0), std::string::size_type(1), '\\').find_last_of('\\'));
        file_str = file_str.substr(file_str.insert(std::string::size_type(0), std::string::size_type(1), '/').find_last_of('/'));

        // Now format this entry, and add this entry to our member string
        std::ostringstream out;
        out << "    -> caught at line " << line << " in " << file_str.substr(2);
        if (pdesc)
            out << ": "<< pdesc;
        out << std::endl;

        return out.str();
    } // FormatTrace


protected:
    // ------------------------------------------------------------------------
    // A string to contain the description of the exception. Derived classes may
    // like to access this directly.
    // ------------------------------------------------------------------------
    std::string             m_what;
    mutable std::string     m_what_ret;


private:
    // ------------------------------------------------------------------------
    // Private variables for storing the initial location and the stack trace
    // ------------------------------------------------------------------------
    const char                 *m_pfile;
    int                         m_line;
    std::deque<std::string>     m_stack_trace;
}; // GeneralException


// ----------------------------------------------------------------------------
// Name: OSException  (class)
// Desc: Used in the exception hierarchy to denote all exceptions caused at the 
//       OS level.
// ----------------------------------------------------------------------------
class OSException : public GeneralException
{
public:
    // ------------------------------------------------------------------------
    // Constructors
    // ------------------------------------------------------------------------
    OSException() throw()
        : GeneralException() {}
    explicit OSException(const char *pdesc) throw()
        : GeneralException(pdesc) {}
    OSException(const char *pfile, int line) throw()
        : GeneralException(pfile, line) {}
    OSException(const char *pfile, int line, const char *pdesc) throw()
        : GeneralException(pfile, line, pdesc) {}
    
    
    // ------------------------------------------------------------------------
    // Name: operator<<
    // Temp: The type of object being inserted
    // Desc: Insertion operator used to add text to the description string that 
    //       was initialised during construction. This is particularly useful 
    //       for adding numbers to the string (not easy to do with const char * 
    //       or String), or generating the error string based on some 
    //       logical conditions.  Note - std::ostream must understand how to 
    //       insert the object of type T, otherwise this will fail to compile.
    // Parm: const T &in   - the object to be inserted
    // Retn: OSException & - a reference to the exception, for furthur 
    //       inserting or throwing.
    // ------------------------------------------------------------------------
    template <typename T>
    OSException &operator<<(const T &in)
    {        
        static_cast<GeneralException &> (*this) << in;
        return *this;
    } // operator<<
}; // class OSException


// ----------------------------------------------------------------------------
// Name: CommonException  (class)
// Desc: This is the common exception base class for all other exceptions other 
//       than OSExceptions.
// ----------------------------------------------------------------------------
class CommonException : public GeneralException
{
public:
    // ------------------------------------------------------------------------
    // Constructors
    // ------------------------------------------------------------------------
    CommonException() throw()
        : GeneralException() {}
    explicit CommonException(const char *pdesc) throw()
        : GeneralException(pdesc) {}
    CommonException(const char *pfile, int line) throw()
        : GeneralException(pfile, line) {}
    CommonException(const char *pfile, int line, const char *pdesc) throw()
        : GeneralException(pfile, line, pdesc) {}


    // ------------------------------------------------------------------------
    // Name: operator<<
    // Temp: The type of object being inserted
    // Desc: Insertion operator used to add text to the description string that 
    //       was initialised during construction. This is particularly useful 
    //       for adding numbers to the string (not easy to do with const char * 
    //       or String), or generating the error string based on some 
    //       logical conditions.  Note - std::ostream must understand how to 
    //       insert the object of type T, otherwise this will fail to compile.
    // Parm: const T &in       - the object to be inserted
    // Retn: CommonException & - a reference to the exception, for furthur 
    //       inserting or throwing.
    // ------------------------------------------------------------------------
    template <typename T>
    CommonException &operator<<(const T &in)
    {        
        static_cast<GeneralException &> (*this) << in;
        return *this;
    } // operator<<
}; // class CommonException


// ----------------------------------------------------------------------------
// Name: InvalidParameterException  (class)
// Desc: Denotes an error that occurred through an invalid parameter being 
//       supplied to a function.
// ----------------------------------------------------------------------------
class InvalidParameterException : public CommonException
{
public:
    // ------------------------------------------------------------------------
    // Constructors
    // ------------------------------------------------------------------------
    InvalidParameterException() throw()
        : CommonException("Invalid parameter supplied - ") {}
    explicit InvalidParameterException(const char *pdesc) throw()
        : CommonException((std::string("Invalid parameter supplied - ") + pdesc).c_str()) {}
    InvalidParameterException(const char *pfile, int line) throw()
        : CommonException(pfile, line, "Invalid parameter supplied - ") {}
    InvalidParameterException(const char *pfile, int line, const char *pdesc) throw()
        : CommonException(pfile, line, (std::string("Invalid parameter supplied - ") + pdesc).c_str()) {}


    // ------------------------------------------------------------------------
    // Name: operator<<
    // Temp: The type of object being inserted
    // Desc: Insertion operator used to add text to the description string that 
    //       was initialised during construction. This is particularly useful 
    //       for adding numbers to the string (not easy to do with const char * 
    //       or String), or generating the error string based on some 
    //       logical conditions.  Note - std::ostream must understand how to 
    //       insert the object of type T, otherwise this will fail to compile.
    // Parm: const T &in                 - the object to be inserted
    // Retn: InvalidParameterException & - a reference to the exception, for  
    //       furthur inserting or throwing.
    // ------------------------------------------------------------------------
    template <typename T>
    InvalidParameterException &operator<<(const T &in)
    {        
        static_cast<GeneralException &> (*this) << in;
        return *this;
    } // operator<<
}; // class InvalidParameterException


// ----------------------------------------------------------------------------
// Name: ObjectNotFoundException  (class)
// Desc: Denotes an error that occurred through attempting to locate an object 
//       by name where no object by that name exists.
// ----------------------------------------------------------------------------
class ObjectNotFoundException : public CommonException
{
public:
    // ------------------------------------------------------------------------
    // Constructors
    // ------------------------------------------------------------------------
    ObjectNotFoundException() throw()
        : CommonException("Object not found - ") {}
    explicit ObjectNotFoundException(const char *pdesc) throw()
        : CommonException((std::string("Object not found - ") + pdesc).c_str()) {}
    ObjectNotFoundException(const char *pfile, int line) throw()
        : CommonException(pfile, line, "Object not found - ") {}
    ObjectNotFoundException(const char *pfile, int line, const char *pdesc) throw()
        : CommonException(pfile, line, (std::string("Object not found - ") + pdesc).c_str()) {}


    // ------------------------------------------------------------------------
    // Name: operator<<
    // Temp: The type of object being inserted
    // Desc: Insertion operator used to add text to the description string that 
    //       was initialised during construction. This is particularly useful 
    //       for adding numbers to the string (not easy to do with const char * 
    //       or String), or generating the error string based on some 
    //       logical conditions.  Note - std::ostream must understand how to 
    //       insert the object of type T, otherwise this will fail to compile.
    // Parm: const T &in               - the object to be inserted
    // Retn: ObjectNotFoundException & - a reference to the exception, for  
    //       furthur inserting or throwing.
    // ------------------------------------------------------------------------
    template <typename T>
    ObjectNotFoundException &operator<<(const T &in)
    {        
        static_cast<GeneralException &> (*this) << in;
        return *this;
    } // operator<<
}; // class ObjectNotFoundException


// ----------------------------------------------------------------------------
// Name: DuplicateObjectException  (class)
// Desc: Denotes an error that occurred through attempting to locate an object 
//       by name where no object by that name exists.
// ----------------------------------------------------------------------------
class DuplicateObjectException : public CommonException
{
public:
    // ------------------------------------------------------------------------
    // Constructors
    // ------------------------------------------------------------------------
    DuplicateObjectException() throw()
        : CommonException("Duplicate object - ") {}
    explicit DuplicateObjectException(const char *pdesc) throw()
        : CommonException((std::string("Duplicate object - ") + pdesc).c_str()) {}
    DuplicateObjectException(const char *pfile, int line) throw()
        : CommonException(pfile, line, "Duplicate object - ") {}
    DuplicateObjectException(const char *pfile, int line, const char *pdesc) throw()
        : CommonException(pfile, line, (std::string("Duplicate object - ") + pdesc).c_str()) {}


    // ------------------------------------------------------------------------
    // Name: operator<<
    // Temp: The type of object being inserted
    // Desc: Insertion operator used to add text to the description string that 
    //       was initialised during construction. This is particularly useful 
    //       for adding numbers to the string (not easy to do with const char * 
    //       or String), or generating the error string based on some 
    //       logical conditions.  Note - std::ostream must understand how to 
    //       insert the object of type T, otherwise this will fail to compile.
    // Parm: const T &in                - the object to be inserted
    // Retn: DuplicateObjectException & - a reference to the exception, for 
    //       furthur inserting or throwing.
    // ------------------------------------------------------------------------
    template <typename T>
    DuplicateObjectException &operator<<(const T &in)
    {        
        static_cast<GeneralException &> (*this) << in;
        return *this;
    } // operator<<
}; // class DuplicateObjectException


// ----------------------------------------------------------------------------
// Name: PathNotFoundException  (class)
// Desc: Denotes an error that occurred through attempting to locate an object 
//       from a path that does not exist.
// ----------------------------------------------------------------------------
class PathNotFoundException : public CommonException
{
public:
    // ------------------------------------------------------------------------
    // Constructors
    // ------------------------------------------------------------------------
    PathNotFoundException() throw()
        : CommonException("Path not found - ") {}
    explicit PathNotFoundException(const char *pdesc) throw()
        : CommonException((std::string("Path not found - ") + pdesc).c_str()) {}
    PathNotFoundException(const char *pfile, int line) throw()
        : CommonException(pfile, line, "Path not found - ") {}
    PathNotFoundException(const char *pfile, int line, const char *pdesc) throw()
        : CommonException(pfile, line, (std::string("Path not found - ") + pdesc).c_str()) {}


    // ------------------------------------------------------------------------
    // Name: operator<<
    // Temp: The type of object being inserted
    // Desc: Insertion operator used to add text to the description string that 
    //       was initialised during construction. This is particularly useful 
    //       for adding numbers to the string (not easy to do with const char * 
    //       or String), or generating the error string based on some 
    //       logical conditions.  Note - std::ostream must understand how to 
    //       insert the object of type T, otherwise this will fail to compile.
    // Parm: const T &in             - the object to be inserted
    // Retn: PathNotFoundException & - a reference to the exception, for 
    //       furthur inserting or throwing.
    // ------------------------------------------------------------------------
    template <typename T>
    PathNotFoundException &operator<<(const T &in)
    {        
        static_cast<GeneralException &> (*this) << in;
        return *this;
    } // operator<<
}; // class PathNotFoundException


// ----------------------------------------------------------------------------
// Name: InvlaidCastException  (class)
// Desc: Denotes an error that occurred through attempting to cast an object to 
//       an invalid type.
// ----------------------------------------------------------------------------
class InvlaidCastException : public CommonException
{
public:
    // ------------------------------------------------------------------------
    // Constructors
    // ------------------------------------------------------------------------
    InvlaidCastException() throw()
        : CommonException("Invalid cast - ") {}
    explicit InvlaidCastException(const char *pdesc) throw()
        : CommonException((std::string("Invalid cast - ") + pdesc).c_str()) {}
    InvlaidCastException(const char *pfile, int line) throw()
        : CommonException(pfile, line, "Invalid cast - ") {}
    InvlaidCastException(const char *pfile, int line, const char *pdesc) throw()
        : CommonException(pfile, line, (std::string("Invalid cast - ") + pdesc).c_str()) {}


    // ------------------------------------------------------------------------
    // Name: operator<<
    // Temp: The type of object being inserted
    // Desc: Insertion operator used to add text to the description string that 
    //       was initialised during construction. This is particularly useful 
    //       for adding numbers to the string (not easy to do with const char * 
    //       or String), or generating the error string based on some 
    //       logical conditions.  Note - std::ostream must understand how to 
    //       insert the object of type T, otherwise this will fail to compile.
    // Parm: const T &in            - the object to be inserted
    // Retn: InvlaidCastException & - a reference to the exception, for furthur 
    //       inserting or throwing.
    // ------------------------------------------------------------------------
    template <typename T>
    InvlaidCastException &operator<<(const T &in)
    {        
        static_cast<GeneralException &> (*this) << in;
        return *this;
    } // operator<<
}; // class InvlaidCastException


// ----------------------------------------------------------------------------
// Name: SecurityException  (class)
// Desc: Exception used when illegal access is attempted
// ----------------------------------------------------------------------------
class SecurityException : public CommonException
{
public:
    // ------------------------------------------------------------------------
    // Constructors
    // ------------------------------------------------------------------------
    SecurityException() throw()
        : CommonException("Object Locked (readonly) - ") {}
    explicit SecurityException(const char *pdesc) throw()
        : CommonException((std::string("Object Locked (readonly) - ") + pdesc).c_str()) {}
    SecurityException(const char *pfile, int line) throw()
        : CommonException(pfile, line, "Object Locked (readonly) - ") {}
    SecurityException(const char *pfile, int line, const char *pdesc) throw()
        : CommonException(pfile, line, (std::string("Object Locked (readonly) - ") + pdesc).c_str()) {}


    // ------------------------------------------------------------------------
    // Name: operator<<
    // Temp: The type of object being inserted
    // Desc: Insertion operator used to add text to the description string that 
    //       was initialised during construction. This is particularly useful 
    //       for adding numbers to the string (not easy to do with const char * 
    //       or String), or generating the error string based on some 
    //       logical conditions.  Note - std::ostream must understand how to 
    //       insert the object of type T, otherwise this will fail to compile.
    // Parm: const T &in         - the object to be inserted
    // Retn: SecurityException & - a reference to the exception, for furthur 
    //       inserting or throwing.
    // ------------------------------------------------------------------------
    template <typename T>
    SecurityException &operator<<(const T &in)
    {        
        static_cast<GeneralException &> (*this) << in;
        return *this;
    } // operator<<
}; // class SecurityException


#endif // EXCEPTIONS_H

// -- EOF
