// ----------------------------------------------------------------------------
// File: FilePath.h
// Desc: Manages file path searching and utility functions
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _FILE_PATH_H_
#define _FILE_PATH_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include <string>
#include <vector>


// ----------------------------------------------------------------------------
// Singleton typedefs
// ----------------------------------------------------------------------------
class FilePath;
typedef Singleton::SingletonHolder<FilePath, 
        Singleton::CreateUsingNew<FilePath> > FilePathSingleton;


// ----------------------------------------------------------------------------
// Name: FilePath  (class)
// Desc: Manages file paths searching and other utility functions
// ----------------------------------------------------------------------------
class FilePath : private Utility::Unique
{
private:
    // ------------------------------------------------------------------------
    // Allow the singleton holder to construct this class
    // ------------------------------------------------------------------------
    friend struct Singleton::CreateUsingNew<FilePath>;


    // ------------------------------------------------------------------------
    // Private constructor and destructor
    // ------------------------------------------------------------------------
                    FilePath() {}
    virtual        ~FilePath() {}


public:
    // ------------------------------------------------------------------------
    // Manage the file paths
    // ------------------------------------------------------------------------
    void            Add(const std::string &path);
    void            Remove(const std::string &path);
    void            Clear();


    // ------------------------------------------------------------------------
    // Find a file in the path
    // ------------------------------------------------------------------------
    std::string     FindFile(const std::string &filename);


    // ------------------------------------------------------------------------
    // Static helper functions
    // ------------------------------------------------------------------------
    static void     StripPath(std::string &path_and_filename);


private:
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    std::vector<std::string> m_paths;    


}; // class FilePath


#endif // _FILE_PATH_H_

// -- EOF

