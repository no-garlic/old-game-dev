// ----------------------------------------------------------------------------
// File: FilePath.cpp
// Desc: Manages file path searching and utility functions
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/FilePath.h"
#include <fstream>
#include <algorithm>


// ----------------------------------------------------------------------------
// Name: FilePath::Add
// Desc: Add a path to the search path
// Parm: const std::string &path - the path to add
// ----------------------------------------------------------------------------
void FilePath::Add(const std::string &path)
{
    // Make sure the path is not empty
    if (path.empty())
        return;

    // Make sure the path ends in a slash
    std::string pathname = path;
    char last_ch = pathname[pathname.size() - 1];
    if (last_ch != '/' && last_ch != '\\')
        pathname += "\\";

    // Check that the path is not already in our vector
    std::vector<std::string>::iterator iter = m_paths.begin();
    for (; iter != m_paths.end(); ++iter)
    {
        if (*iter == pathname)
            return;
    } // for

    // Add the path
    m_paths.push_back(pathname);
} // Add


// ----------------------------------------------------------------------------
// Name: FilePath::Remove
// Desc: Remove a path from the search path
// Parm: const std::string &path - the path to remove
// ----------------------------------------------------------------------------
void FilePath::Remove(const std::string &path)
{
    // Make sure the path is not empty
    if (path.empty())
        return;

    // Make sure the path ends in a slash
    std::string pathname = path;
    char last_ch = pathname[pathname.size() - 1];
    if (last_ch != '/' && last_ch != '\\')
        pathname += "\\";

    // Search for the path
    std::vector<std::string>::iterator iter = m_paths.begin();
    for (; iter != m_paths.end(); ++iter)
    {
        if (*iter == pathname)
        {
            m_paths.erase(iter);
            return;
        } // if
    } // for
} // Remove


// ----------------------------------------------------------------------------
// Name: FilePath::Clear
// Desc: Clear the file path list
// ----------------------------------------------------------------------------
void FilePath::Clear()
{
    m_paths.clear();
} // Clear


// ----------------------------------------------------------------------------
// Name: FilePath::FindFile
// Desc: Find a file in the search path
// Parm: const std::string &filename - the filename of the file to find
// Retn: std::string                 - a string containing the file path and 
//       filename to use to open the file.  If the file was not found in any of 
//       the file paths, an empty string is returned.
// ----------------------------------------------------------------------------
std::string FilePath::FindFile(const std::string &filename)
{
    std::vector<std::string>::iterator iter = m_paths.begin();
    for (; iter != m_paths.end(); ++iter)
    {
        // Get the path name
        std::string path = *iter;

        // Append the filename
        path += filename;

        // Attepmt to open the file
        std::fstream f;
        f.open(path.c_str(), std::ios_base::in);
        if (f.is_open())
        {
            f.close();
            return path;
        } // if
    } // for

    return "";
} // FindFile


// ----------------------------------------------------------------------------
// Name: FilePath::StripPath
// Desc: Strip the pathname from a filename and pathname string
// Parm: std::string &path_and_filename - the string to strip the pathname from
// ----------------------------------------------------------------------------
void FilePath::StripPath(std::string &path_and_filename)
{
    int pos1 = path_and_filename.find_last_of('/');
    int pos2 = path_and_filename.find_last_of('\\');
    int pos  = std::max<int>(pos1, pos2);

    if (pos < 0)
        return;

    path_and_filename = path_and_filename.substr(pos);
} // StripPath


// -- EOF

