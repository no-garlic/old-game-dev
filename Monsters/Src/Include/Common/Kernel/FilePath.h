// ----------------------------------------------------------------------------
// File: FilePathManager.h
// Desc: Manages file path searching and utility functions
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _FILE_PATH_H_
#define _FILE_PATH_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Kernel/Types.h"
#include "Kernel/StdMemory.h"
#include "Kernel/StdStr.h"
#include "Kernel/Config.h"
#include "Kernel/Logging.h"


// ----------------------------------------------------------------------------
// Singleton aqccessor
// ----------------------------------------------------------------------------
class   FilePathManager;
typedef SingletonHolder<FilePathManager, CreateUsingNew<FilePathManager> > FilePathManagerSingleton;
#define FilePath FilePathManagerSingleton::Instance()


// ----------------------------------------------------------------------------
// Name: FilePathManager  (class)
// Desc: Manages file paths searching and other utility functions
// ----------------------------------------------------------------------------
class FilePathManager : private Unique
{
private:
  // ------------------------------------------------------------------------
  // Allow the singleton holder to construct this class
  // ------------------------------------------------------------------------
  friend struct CreateUsingNew<FilePathManager>;

  // ------------------------------------------------------------------------
  // Private constructor and destructor
  // ------------------------------------------------------------------------
  FilePathManager()          { REF_COUNT_CTOR(FilePathManager); }
  virtual ~FilePathManager() { REF_COUNT_DTOR(FilePathManager); }

public:
  // ------------------------------------------------------------------------
  // Manage the file paths
  // ------------------------------------------------------------------------
  void Add(const String &path);
  void Remove(const String &path);
  void Clear();

  // ------------------------------------------------------------------------
  // Find a file in the path
  // ------------------------------------------------------------------------
  String FindFile(const String &filename);
  bool LocateFile(String &filename);

  // ------------------------------------------------------------------------
  // Static helper functions
  // ------------------------------------------------------------------------
  static void StripPath(String &path_and_filename);

private:
  // ------------------------------------------------------------------------
  // Private members
  // ------------------------------------------------------------------------
  StringArray m_paths;    

}; // class FilePathManager


#endif // _FILE_PATH_H_

// -- EOF

