// ----------------------------------------------------------------------------
// File: FilePathManager.cpp
// Desc: Manages file path searching and utility functions
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Kernel/Types.h"
#include "Kernel/FilePath.h"


// ----------------------------------------------------------------------------
// Name: FilePathManager::Add
// Desc: Add a path to the search path
// Parm: const String &path - the path to add
// ----------------------------------------------------------------------------
void FilePathManager::Add(const String &path)
{
  // Make sure the path is not empty
  if (path.empty())
    return;

  // Make sure the path ends in a slash
  String pathname = path;
  char last_ch = pathname[pathname.size() - 1];
  if (last_ch != '/' && last_ch != '\\')
    pathname += "\\";

  // Check that the path is not already in our vector
  StringArray::iterator iter = m_paths.begin();
  for (; iter != m_paths.end(); ++iter)
  {
    if (*iter == pathname)
      return;
  } // for

  // Add the path
  m_paths.push_back(pathname);
} // Add


// ----------------------------------------------------------------------------
// Name: FilePathManager::Remove
// Desc: Remove a path from the search path
// Parm: const String &path - the path to remove
// ----------------------------------------------------------------------------
void FilePathManager::Remove(const String &path)
{
  // Make sure the path is not empty
  if (path.empty())
    return;

  // Make sure the path ends in a slash
  String pathname = path;
  char last_ch = pathname[pathname.size() - 1];
  if (last_ch != '/' && last_ch != '\\')
    pathname += "\\";

  // Search for the path
  StringArray::iterator iter = m_paths.begin();
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
// Name: FilePathManager::Clear
// Desc: Clear the file path list
// ----------------------------------------------------------------------------
void FilePathManager::Clear()
{
  m_paths.clear();
} // Clear


// ----------------------------------------------------------------------------
// Name: FilePathManager::FindFile
// Desc: Find a file in the search path
// Parm: const String &filename - the filename of the file to find
// Retn: String                 - a string containing the file path and 
//       filename to use to open the file.  If the file was not found in any of 
//       the file paths, an empty string is returned.
// ----------------------------------------------------------------------------
String FilePathManager::FindFile(const String &filename)
{
  if (m_paths.empty())
    return filename;

  StringArray::iterator iter = m_paths.begin();
  for (; iter != m_paths.end(); ++iter)
  {
    // Get the path name
    String path = *iter;

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
// Name: FilePathManager::LocateFile
// Desc: Locate a file in the search path
// Parm: String &filename - [in/out] the filename - searches for ha filename and
//       then sets this to the absolute path and the filename
// Retn: bool             - true if the file was found and the filname was set
// ----------------------------------------------------------------------------
bool FilePathManager::LocateFile(String &filename)
{
  String found_file = filename;
  FilePathManager::StripPath(found_file);
  found_file = FindFile(found_file);
  if (found_file.empty())
    return false;

  filename = found_file;
  return true;
} // LocateFile


// ----------------------------------------------------------------------------
// Name: FilePathManager::StripPath
// Desc: Strip the pathname from a filename and pathname string
// Parm: String &path_and_filename - the string to strip the pathname from
// ----------------------------------------------------------------------------
void FilePathManager::StripPath(String &path_and_filename)
{
  int pos1 = (int) path_and_filename.find_last_of('/');
  int pos2 = (int) path_and_filename.find_last_of('\\');
  int pos  = Max<int>(pos1, pos2);

  if (pos < 0)
    return;

  path_and_filename = path_and_filename.substr(pos);
} // StripPath


// -- EOF

