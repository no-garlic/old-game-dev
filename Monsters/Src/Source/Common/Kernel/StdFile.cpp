// ----------------------------------------------------------------------------
// File: StdFile.cpp
// Desc: Standard file functions
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Kernel/StdFile.h"
#include "Kernel/Logging.h"
#include <direct.h>
#include <stack>


// ----------------------------------------------------------------------------
// The file seperator we use
// ----------------------------------------------------------------------------
#define FILE_SEPERATOR "/"


// ----------------------------------------------------------------------------
// Name: FileHandle::FileHandle
// Desc: Constructor
// ----------------------------------------------------------------------------
FileHandle::FileHandle()
: m_pDatabase(NULL)
{
  REF_COUNT_CTOR(FileHandle);
} // FileHandle


// ----------------------------------------------------------------------------
// Name: FileHandle::FileHandle
// Desc: Constructor
// Parm: const String &filename            - the filename
// Parm: const FileDatabase &fileDatabase  - the database
// ----------------------------------------------------------------------------
FileHandle::FileHandle(const String &filename, const FileDatabase &fileDatabase)
: m_Filename (filename),
  m_pDatabase(&fileDatabase)
{
  REF_COUNT_CTOR(FileHandle);

  m_AbsoluteFilename = fileDatabase.GetAbsolutePath() + FILE_SEPERATOR + filename;
} // FileHandle


// ----------------------------------------------------------------------------
// Name: FileHandle::FileHandle
// Desc: Constructor
// Parm: const FileHandle &other - the handle to copy
// ----------------------------------------------------------------------------
FileHandle::FileHandle(const FileHandle &other)
{
  REF_COUNT_CTOR(FileHandle);

  m_Filename          = other.m_Filename;
  m_AbsoluteFilename  = other.m_AbsoluteFilename;
  m_pDatabase         = other.m_pDatabase;
} // FileHandle


// ----------------------------------------------------------------------------
// Name: FileHandle::~FileHandle
// Desc: Destructor
// ----------------------------------------------------------------------------
FileHandle::~FileHandle()
{
  REF_COUNT_DTOR(FileHandle);
} // ~FileHandle


// ----------------------------------------------------------------------------
// Name: FileHandle::operator=
// Desc: Assignment
// Parm: const FileHandle &other - the file handle to copy
// Retn: FileHandle &            - a reference to this
// ----------------------------------------------------------------------------
FileHandle &FileHandle::operator=(const FileHandle &other)
{
  m_Filename          = other.m_Filename;
  m_AbsoluteFilename  = other.m_AbsoluteFilename;
  m_pDatabase         = other.m_pDatabase;

  return *this;
} // operator=


// ----------------------------------------------------------------------------
// Name: FileHandle::GetFilename
// Desc: Get the filename
// Retn: const String & - the filename
// ----------------------------------------------------------------------------
const String &FileHandle::GetFilename() const
{
  return m_Filename;
} // GetFilename


// ----------------------------------------------------------------------------
// Name: FileHandle::GetAbsoluteFilename
// Desc: Get the absolute filename
// Retn: const String & - the filename
// ----------------------------------------------------------------------------
const String &FileHandle::GetAbsoluteFilename() const
{
  return m_AbsoluteFilename;
} // GetAbsoluteFilename


// ----------------------------------------------------------------------------
// Name: FileHandle::SetFilename
// Desc: Set the filename
// Parm: const String &filename - the filename
// ----------------------------------------------------------------------------
void FileHandle::SetFilename(const String &filename)
{
  m_Filename         = filename;
  m_AbsoluteFilename = m_pDatabase->GetAbsolutePath() + FILE_SEPERATOR + filename;
} // SetFilename


// ----------------------------------------------------------------------------
// Name: FileHandle::SetFileDatbase
// Desc: Set the database
// Parm: const FileDatabase &fileDatabase - the database
// ----------------------------------------------------------------------------
void FileHandle::SetFileDatbase(const FileDatabase &fileDatabase)
{
  m_AbsoluteFilename = m_pDatabase->GetAbsolutePath() + FILE_SEPERATOR + m_Filename;
} // SetFileDatbase


// ----------------------------------------------------------------------------
// Name: FileHandle::GetFileDatabase
// Desc: Get the database
// ----------------------------------------------------------------------------
const FileDatabase &FileHandle::GetFileDatabase() const
{
  return *m_pDatabase;
} // GetFileDatabase


// ----------------------------------------------------------------------------
// Name: FileHandle::Exists
// Desc: Check if the file exists
// Retn: bool - true if it does
// ----------------------------------------------------------------------------
bool FileHandle::Exists() const
{
  int fd = _open(m_AbsoluteFilename.c_str(), _O_RDONLY|_O_BINARY, _S_IREAD);
  if (fd == -1)
    return false;

  _close(fd);
  return true;
} // Exists


// ----------------------------------------------------------------------------
// Name: FileDatabase::FileDatabase
// Desc: Constructor
// Parm: const String &path - the path
// ----------------------------------------------------------------------------
FileDatabase::FileDatabase(const String &path)
: m_Path(path)
{
  REF_COUNT_CTOR(FileDatabase);

  m_AbsolutePath = FileSystem.GetBasePath();
  
  if (!m_Path.empty())
    m_AbsolutePath += (FILE_SEPERATOR + m_Path);
} // FileDatabase


// ----------------------------------------------------------------------------
// Name: FileDatabase::~FileDatabase
// Desc: Destructor
// ----------------------------------------------------------------------------
FileDatabase::~FileDatabase()
{
  REF_COUNT_DTOR(FileDatabase);
} // ~FileDatabase


// ----------------------------------------------------------------------------
// Name: FileDatabase::ListFiles
// Desc: List all files in the database that match teh wildcard
// Parm: const String &wildcard - the windcard
// Retn: FileHandleArray - the array of file handles
// ----------------------------------------------------------------------------
FileHandleArray FileDatabase::ListFiles(const String &wildcard) const
{
  FileHandleArray allFiles;
  StringArray     allPaths;

  if (!FindFiles(m_AbsolutePath, wildcard, allFiles, allPaths))
  {
    LOG_ERROR << "Failed to find files in path: " << m_AbsolutePath << ENDLOG;
    return allFiles;
  } // if

  return allFiles;
} // ListFiles


// ----------------------------------------------------------------------------
// Name: FileDatabase::ListFiles
// Desc: List all files for the given wildcard array
// Parm: const StringArray &wildcardArray - the wildcard array
// Retn: FileHandleArray                  - the files
// ----------------------------------------------------------------------------
FileHandleArray FileDatabase::ListFiles(const StringArray &wildcardArray) const
{
  FileHandleArray allFiles;
  StringArray     allPaths;

  StringArray::const_iterator iter(wildcardArray.begin()), end(wildcardArray.end());
  for (; iter != end; ++iter)
  {
    if (!FindFiles(m_AbsolutePath, (*iter), allFiles, allPaths))
      LOG_ERROR << "Failed to find " << (*iter) << " files in path: " << m_AbsolutePath << ENDLOG;
  } // for

  return allFiles;
} // ListFiles


bool FileDatabase::FindFiles(const String     &path, 
                             const String     &wildcard, 
                             FileHandleArray  &files, 
                             StringArray      &paths) const
{
  char currDir[_MAX_PATH];
  if (_getcwd(currDir, _MAX_PATH) == NULL)
    return false;

  if (chdir(path.c_str()) != 0)
    return false;

  _finddata_t fileInfo;
  long hFile;

  if ((hFile = _findfirst(wildcard.c_str(), &fileInfo)) == -1L)
    return false;

  if (fileInfo.attrib & _A_SUBDIR)
  {
    if (String(fileInfo.name) != "." && String(fileInfo.name) != "..")
      paths.push_back(path + FILE_SEPERATOR + fileInfo.name);
  } // if
  else
  {
    files.push_back(FileHandle(fileInfo.name, *this));
  } // else

  while (_findnext(hFile, &fileInfo) == 0)
  {
    if (fileInfo.attrib & _A_SUBDIR)
    {
      if (String(fileInfo.name) != "." && String(fileInfo.name) != "..")
        paths.push_back(path + FILE_SEPERATOR + fileInfo.name);
    } // if
    else
    {
      files.push_back(FileHandle(fileInfo.name, *this));
    } // else
  } // while

  if (_findclose(hFile) != 0)
    return false;

  if (chdir(currDir) != 0)
    return false;

  return true;
} // FindFiles


// ----------------------------------------------------------------------------
// Name: FileDatabase::MakeFileHandle
// Desc: Make a new file handle
// Parm: const String &filename - the filename
// Retn: FileHandle             - the handle
// ----------------------------------------------------------------------------
FileHandle FileDatabase::MakeFileHandle(const String &filename)
{
  return FileHandle(filename, *this);
} // MakeFileHandle


// ----------------------------------------------------------------------------
// Name: FileDatabase::GetPath
// Desc: Get the path
// ----------------------------------------------------------------------------
const String &FileDatabase::GetPath() const
{
  return m_Path;
} // GetPath


// ----------------------------------------------------------------------------
// Name: FileDatabase::GetAbsolutePath
// Desc: Get the absolute path
// ----------------------------------------------------------------------------
const String &FileDatabase::GetAbsolutePath() const
{
  return m_AbsolutePath;
} // GetAbsolutePath


// ----------------------------------------------------------------------------
// Name: FileSystemManager::FileSystemManager
// Desc: Constructor
// ----------------------------------------------------------------------------
FileSystemManager::FileSystemManager()
{
} // FileSystemManager


// ----------------------------------------------------------------------------
// Name: FileSystemManager::~FileSystemManager
// Desc: Destructor
// ----------------------------------------------------------------------------
FileSystemManager::~FileSystemManager()
{
} // ~FileSystemManager


// ----------------------------------------------------------------------------
// Name: FileSystemManager::SetBasePath
// Desc: Set the base path
// Parm: const String &basePath - the base path
// Parm: bool fromCurrDir       - is the base path absolute or relative to the 
//       current directory
// ----------------------------------------------------------------------------
void FileSystemManager::SetBasePath(const String &basePath, bool fromCurrDir)
{
  m_Path = basePath;

  if (fromCurrDir)
  {
    char currDir[_MAX_PATH];
    if (_getcwd(currDir, _MAX_PATH) != NULL)
      m_Path = String(currDir) + "/" + basePath;
  } // if

  // Substitite forward slashes for back slashes
  int pos = m_Path.find_first_of("\\");
  while (pos != -1)
  {
    m_Path[pos] = '/';
    pos = m_Path.find_first_of("\\");
  } // while

  // Get the absoute path
  std::stack<String> fileStack;
  pos = m_Path.find_first_of("/");
  while (pos != -1)
  {
    String path = m_Path.substr(0, pos);
    if (path == "..")
    {
      if (!fileStack.empty())
        fileStack.pop();
    } // if
    else
    {
      fileStack.push(path);
    } // else

    m_Path = m_Path.substr(pos);
    if (m_Path.length() != 0 && m_Path[0] == '/')
      m_Path = m_Path.substr(1);

    pos = m_Path.find_first_of("/");
  } // while

  if (!m_Path.empty())
    fileStack.push(m_Path);

  m_Path.clear();
  while (!fileStack.empty())
  {
    m_Path = fileStack.top() + "/" + m_Path;
    fileStack.pop();
  } // while

  if (m_Path[m_Path.length() - 1] == '/')
    m_Path = m_Path.substr(0, m_Path.length() - 1);
} // SetBasePath


// ----------------------------------------------------------------------------
// Name: FileSystemManager::GetBasePath
// Desc: Get the base path
// ----------------------------------------------------------------------------
const String &FileSystemManager::GetBasePath() const
{
  return m_Path;
} // GetBasePath


// ----------------------------------------------------------------------------
// Name: FileSystemManager::AddDatabase
// Desc: Add a file database
// Parm: const String &name  - the name for the database
// Parm: const String &path  - the path of the database
// ----------------------------------------------------------------------------
FileDatabase *FileSystemManager::AddDatabase(const String &name, const String &path)
{
  String newPath = path;

  // Substitite back slashes for forward slashes
  int pos = newPath.find_first_of("\\");
  while (pos != -1)
  {
    newPath[pos] = '/';
    pos = newPath.find_first_of("\\");
  } // while

  // Remove any trailing slash
  if (newPath[newPath.length() - 1] == '/')
    newPath = newPath.substr(0, newPath.length() - 1);

  // Add the database
  FileDatabase *pDatabase = new FileDatabase(newPath);
  m_DatabaseArray.insert(MakePair(name, pDatabase));
  return pDatabase;
} // AddDatabase


// ----------------------------------------------------------------------------
// Name: FileSystemManager::operator
// Desc: Get a file database
// Retn: FileDatabase * - the datbase
// ----------------------------------------------------------------------------
FileDatabase *FileSystemManager::operator()(const String &name)
{
  Map<String, FileDatabase *>::iterator findIter = m_DatabaseArray.find(name);
  if (findIter == m_DatabaseArray.end())
    return NULL;

  return findIter->second;
} // operator()


// -- EOF
