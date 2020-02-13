// ----------------------------------------------------------------------------
// File: StdFile.h
// Desc: Standard file functions
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __STD_FILE_H_
#define __STD_FILE_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "stdType.h"
#include "stdStr.h"
#include "stdMem.h"


// ----------------------------------------------------------------------------
// Xbox time type
// ----------------------------------------------------------------------------
#if XBOX
#define __time32_t time_t
#endif


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class FileHandle;
class FileDatabase;
class FileSystemManager;


// ----------------------------------------------------------------------------
// Singleton accessor
// ----------------------------------------------------------------------------
typedef SingletonHolder<FileSystemManager, CreateUsingNew<FileSystemManager> > FileSystemManagerSingleton;
#define FileSystem FileSystemManagerSingleton::Instance()


// ----------------------------------------------------------------------------
// Name: FileHandle (class)
// Desc: A handle to a file within a file database
// ----------------------------------------------------------------------------
class FileHandle
{
public:
  // --------------------------------------------------------------------------
  // Constructors and destructor
  // --------------------------------------------------------------------------
  FileHandle();
  FileHandle(const String &filename, const FileDatabase &fileDatabase);
  FileHandle(const FileHandle &other);
  ~FileHandle();

  // --------------------------------------------------------------------------
  // Check if the file handle is valid (checks that it has a database and 
  // filename - does not check if the file exists or not.
  // --------------------------------------------------------------------------
  bool IsValid() const;

  // --------------------------------------------------------------------------
  // Assignment operator
  // --------------------------------------------------------------------------
  FileHandle &operator=(const FileHandle &other);

  // --------------------------------------------------------------------------
  // Get the filename and the absolute filename
  // --------------------------------------------------------------------------
  const String &GetFilename() const;
  const String &GetAbsoluteFilename() const;

  // --------------------------------------------------------------------------
  // Set the filename and the database
  // --------------------------------------------------------------------------
  void SetFilename(const String &filename);
  void SetFileDatbase(FileDatabase *pFileDatabase);

  // --------------------------------------------------------------------------
  // Get the database
  // --------------------------------------------------------------------------
  const FileDatabase &GetFileDatabase() const;

  // --------------------------------------------------------------------------
  // Does the file exist
  // --------------------------------------------------------------------------
  bool Exists() const;

  // --------------------------------------------------------------------------
  // Timestamp info
  // --------------------------------------------------------------------------
  __time32_t GetTimestamp() const;

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  const FileDatabase *m_pDatabase;          // The file database
  String              m_Filename;           // The filename
  String              m_AbsoluteFilename;   // The absolute filename

}; // class FileHandle


// ----------------------------------------------------------------------------
// Stream conversion function for logging file handles
// ----------------------------------------------------------------------------
inline std::ostream &operator<<(std::ostream &stream, const FileHandle &handle)
{
  stream << handle.GetAbsoluteFilename();
  return stream;
}


// ----------------------------------------------------------------------------
// An array of file handles
// ----------------------------------------------------------------------------
typedef Array<FileHandle> FileHandleArray;


// ----------------------------------------------------------------------------
// Checks if the dest file is up-to-date compared to the src file
// ----------------------------------------------------------------------------
bool FileIsUpToDate(FileHandle src, FileHandle dest);
bool FindFileInPath(const String &basePath, const String &filename, 
                    String &absoluteFilename, String &relativePath);

// ----------------------------------------------------------------------------
// Name: FileDatabase (class)
// Desc: A database that manages a directory
// ----------------------------------------------------------------------------
class FileDatabase
{
private:
  // --------------------------------------------------------------------------
  // Only teh file system manager can create databases
  // --------------------------------------------------------------------------
  friend class FileSystemManager;

  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  FileDatabase(const String &path);
  virtual ~FileDatabase();

public:
  // --------------------------------------------------------------------------
  // List all file handles in the database
  // --------------------------------------------------------------------------
  FileHandleArray ListFiles(const String &wildcard = "*.*") const;
  FileHandleArray ListFiles(const StringArray &wildcardArray) const;
  StringArray     ListPaths(bool recursive) const;

  // --------------------------------------------------------------------------
  // Get the path of the database
  // --------------------------------------------------------------------------
  const String &GetPath() const;
  const String &GetAbsolutePath() const;

  // --------------------------------------------------------------------------
  // Make a file handle for this database (find searches recursively)
  // --------------------------------------------------------------------------
  FileHandle MakeFileHandle(const String &filename) const;
  FileHandle FindFileHandle(const String &filename) const;

private:
  // --------------------------------------------------------------------------
  // Private methods
  // --------------------------------------------------------------------------
  bool FindFiles(const String &path, const String &wildcard, 
    FileHandleArray &files, StringArray &paths) const;
  bool FindPaths(const String &path, StringArray &paths, bool recursive) const;

  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  String  m_Path;
  String  m_AbsolutePath;

}; // class FileDatabase


// ----------------------------------------------------------------------------
// Name: FileSystemManager (class)
// Desc: Manages all file databases
// ----------------------------------------------------------------------------
class FileSystemManager
{
private:
  // --------------------------------------------------------------------------
  // Allow the singleton to create an instance of this class
  // --------------------------------------------------------------------------
  friend struct CreateUsingNew<FileSystemManager>;

  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  FileSystemManager();
  ~FileSystemManager();

public:
  // --------------------------------------------------------------------------
  // Set the base path for all databases
  // --------------------------------------------------------------------------
  void SetBasePath(const String &basePath, bool fromCurrDir = true);
  const String &GetBasePath() const;
  
  // --------------------------------------------------------------------------
  // Add and find databases
  // --------------------------------------------------------------------------
  FileDatabase *AddDatabase(const String &name, const String &path);
  FileDatabase *operator()(const String &name);

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  String                      m_Path;
  Map<String, FileDatabase *> m_DatabaseArray;

}; // class FileSystemManager


#endif // __STD_FILE_H_