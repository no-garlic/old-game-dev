// ----------------------------------------------------------------------------
// File: StdStr.h
// Desc: Common string operations
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef STD_STR_H
#define STD_STR_H


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "stdType.h"
#include <string>
#include <sstream>


// ----------------------------------------------------------------------------
// String and StringStream defines
// ----------------------------------------------------------------------------
typedef std::string         String;
typedef std::stringstream   StringStream;
typedef Array<std::string>  StringArray;


// ----------------------------------------------------------------------------
// Name: ToUpper
// Desc: Convert the string to uppercase
// Parm: String &str - the string
// ----------------------------------------------------------------------------
inline void ToUpper(String &str)
{
  strupr((char *) &str[0]);
} // ToUpper


// ----------------------------------------------------------------------------
// Name: ToUpper
// Desc: Convert the string to uppercase
// Parm: const String &str - the incoming string
// Retn: String            - the converted string
// ----------------------------------------------------------------------------
inline String ToUpper(const String &str)
{
  String s = str;
  ToUpper(s);
  return s;
} // ToUpper


// ----------------------------------------------------------------------------
// Name: ToLower
// Desc: Convert the string to lowercase
// Parm: String &str - the string
// ----------------------------------------------------------------------------
inline void ToLower(String &str)
{
  strlwr((char *) &str[0]);
} // ToLower


// ----------------------------------------------------------------------------
// Name: ToLower
// Desc: Convert the string to lowercase
// Parm: const String &str - the incoming string
// Retn: String            - the converted string
// ----------------------------------------------------------------------------
inline String ToLower(const String &str)
{
  String s = str;
  ToLower(s);
  return s;
} // ToLower


// ----------------------------------------------------------------------------
// Name: ToString
// Desc: Convert the value to a string
// Parm: int value - the value
// Retn: String    - the string
// ----------------------------------------------------------------------------
inline String ToString(int value)
{
  char buffer[32];
  if (sprintf(buffer, "%d", value) == -1)
    return "#ERROR#";

  return buffer;
} // ToString


// ----------------------------------------------------------------------------
// Name: ToString
// Desc: Convert the value to a string
// Parm: int value - the value
// Retn: String    - the string
// ----------------------------------------------------------------------------
inline String ToString(uint value)
{
  char buffer[32];
  if (sprintf(buffer, "%u", value) == -1)
    return "#ERROR#";

  return buffer;
} // ToString


// ----------------------------------------------------------------------------
// Name: ToString
// Desc: Convert the value to a string
// Parm: float value - the value
// Retn: String      - the string
// ----------------------------------------------------------------------------
inline String ToString(float value)
{
  char buffer[32];
  if (sprintf(buffer, "%f", value) == -1)
    return "#ERROR#";

  return buffer;
} // ToString


// ----------------------------------------------------------------------------
// Name: ToString
// Desc: Convert the value to a string
// Parm: bool value - the value
// Retn: String     - the string
// ----------------------------------------------------------------------------
inline String ToString(bool value)
{
  char buffer[32];
  if (sprintf(buffer, "%d", (value ? 1 : 0)) == -1)
    return "#ERROR#";

  return buffer;
} // ToString


// ----------------------------------------------------------------------------
// Name: PaddingType (enum)
// Desc: Enumeration of padding values
// ----------------------------------------------------------------------------
enum PaddingType
{
  PT_Left     = 1,          // Add padding to the left of the string
  PT_Right    = 2,          // Add padding to the right of the string
  PT_Default  = PT_Right    // The default padding type
};


// ----------------------------------------------------------------------------
// Name: PadString
// Desc: Make a padding string of the specified width
// Parm: uint width     - the size of the required string
// Parm: char character - the character to fill the string with
// Retn: The new string
// ----------------------------------------------------------------------------
inline String PadString(uint width, char character)
{
  String str;

  while (str.length() < width)
    str += character;

  return str;
}


// ----------------------------------------------------------------------------
// Name: PadString
// Desc: Pad the given string to the specified length (or truncate it)
// Parm: str the string to pad or truncate
// Parm: newSize the new size that the string will be made
// Parm: paddingType add padding to the left or the right of the string
// Retn: A reference to the input str argument
// ----------------------------------------------------------------------------
inline String &PadString(String &str, uint newSize, PaddingType paddingType)
{
  if (str.length() < newSize)
  {
    // The string is shorter than the new size, so add whitespace
    switch (paddingType)
    {
    case PT_Left:
      // Padding before the string (for right justified text)
      str = PadString(newSize - str.length(), ' ') + str;
      break;

    case PT_Right:
      // Padding after the string (for left justified text)
      str.append(newSize - str.length(), ' ');
      break;
    }
  }
  else
  {
    // The string is already longer than the padding, so truncate it
    str = str.substr(0, newSize);
  }

  return str;
}


// ----------------------------------------------------------------------------
// Desc: Pad the given string to the specified length (or truncate it)
// Parm: const String &str        - the string to pad or truncate
// Parm: uint newSize             - the new size that the string will be made
// Parm: PaddingType paddingType  - add padding to the left or the right of the string
// Retn: A reference to the input str argument
// ----------------------------------------------------------------------------
inline String PadString(const String &str, uint newSize, PaddingType paddingType)
{
  String outString = str;
  PadString(outString, newSize, paddingType);
  return outString;
}


// --------------------------------------------------------------------
// Name: StrSpace
// Desc: Create a string with the specified number of spaces in it
// Parm: uint width - the number of spaces
// Retn: String     - the string
// --------------------------------------------------------------------
inline String StrSpace(uint width)
{
  return PadString(width, ' ');
} // StrSpace


// --------------------------------------------------------------------
// Name: AppendInt
// Desc: Append an integer at the end of a string
// Parm: String &str - the string to append the integer to
// Parm: int i       - the integer
// Retn: String &    - the in string so this function can be chained
// --------------------------------------------------------------------
inline String &AppendInt(String &str, int i)
{
  char buffer[32];
  sprintf(buffer, "%d", i);
  str += buffer;
  return str;
} // AppendInt


// --------------------------------------------------------------------
// Name: AppendUInt
// Desc: Append an unsigned integer at the end of a string
// Parm: String &str - the string to append the integer to
// Parm: uint i      - the unsigned integer
// Retn: String &    - the in string so this function can be chained
// --------------------------------------------------------------------
inline String &AppendUInt(String &str, uint i)
{
  char buffer[32];
  sprintf(buffer, "%u", i);
  str += buffer;
  return str;
} // AppendUInt


// --------------------------------------------------------------------
// Name: TrimString
// Desc: Trims the leading and trailing whitespace from a string
// Parm: String &str - the string to trim
// Retn: String & - the in string so this function can be chained
// --------------------------------------------------------------------
inline String &TrimString(String &str)
{
  // Bail out if the string is empty
  if (str.empty())
    return str;

  // Erase leading whitespace
  while (!str.empty() && str.at(0) == ' ')
    str.erase(str.begin());

  // Bail out if the string is empty
  if (str.empty())
    return str;

  // Erase trailing whitespace
  while (str.at(str.size() - 1) == ' ')
    str = str.substr(0, str.size() - 1);

  // return trh string
  return str;
} // TrimString


// --------------------------------------------------------------------
// Name: TrimQuotes
// Desc: Trims the leading and trailing quotes from a string
// Parm: String &str - the string to trim
// Retn: String & - the in string so this function can be chained
// --------------------------------------------------------------------
inline String &TrimQuotes(String &str)
{
  // Bail out if the string is empty
  if (str.empty())
    return str;

  // Erase leading whitespace
  while (str.at(0) == '"')
    str.erase(str.begin());

  // Bail out if the string is empty
  if (str.empty())
    return str;

  // Erase trailing whitespace
  while (str.at(str.size() - 1) == '"')
    str = str.substr(0, str.size() - 1);

  // return trh string
  return str;
} // TrimQuotes


// --------------------------------------------------------------------
// Name: GetQuotedString
// Desc: Searhes through the given string to find the quoted string
// Parm: const String &str - the string to search
// Retn: String            - the text inside of the first pair of 
//       quotes, or an empty string if there is not at least one set 
//       of quotes.
// --------------------------------------------------------------------
inline String GetQuotedString(const String &str)
{
  static const String::size_type npos = -1;

  String::size_type pos1;
  String::size_type pos2;

  // Find the first quote
  pos1 = str.find_first_of("\"", 0);
  if (pos1 == npos)
    return "";

  // Find the second quote
  pos2 = str.find_first_of("\"", pos1 + 1);
  if (pos2 == npos)
    return "";

  // Return the string between the quotes
  return str.substr(pos1 + 1, pos2 - (pos1 + 1));
} // GetQuotedString


// ----------------------------------------------------------------------------
// Name: SplitString
// Desc: Split the string at the first instance of the token 
// Parm: const String &str - the string to split
// Parm: char token = ' '  - the token
// Parm: String &left      - [out] the left part of the string
// Parm: String &right     - [out] the right part of the string
// ----------------------------------------------------------------------------
inline void SplitString(const String &str, char token, String &left, String &right)
{
  size_t pos = str.find_first_of(token);

  if (pos == String::npos)
  {
    left = str;
    right = "";
    return;
  } // if

  left  = str.substr(0, pos);
  right = str.substr(pos + 1);
}


// ----------------------------------------------------------------------------
// Name: Tokenize
// Desc: Split the string into an array of tokens
// Parm: const String &str - the string
// Parm: char token = ' '  - the token
// Retn: StringArray       - the array of tokens
// ----------------------------------------------------------------------------
inline StringArray Tokenize(const String &str, char token = ' ')
{
  StringArray tokens;
  String tmp(str);

  size_t pos = tmp.find_first_of(token);
  while (pos != String::npos)
  {
    String token_str = tmp.substr(0, pos);
    tmp = tmp.substr(pos + 1);

    if (token_str.size())
      tokens.push_back(token_str);

    pos = tmp.find_first_of(token);
  } // while

  if (tmp.size())
    tokens.push_back(tmp);

  return tokens;
} // Tokenize


// ----------------------------------------------------------------------------
// Name: GetStringArrayStrings
// Desc: Get all of the strings from the array in the format { x, y, z }
// Parm: stringArray the string array to expand into a string.
// Retn: A string containing the string array values
// ----------------------------------------------------------------------------
inline String GetStringArrayStrings(const StringArray &stringArray)
{
  StringStream str;
  str << "{ ";

  StringArray::const_iterator iter(stringArray.begin()), first(iter), end(stringArray.end());
  for (; iter != end; ++iter)
  {
    if (iter != first)
    {
      str << ", ";
    }

    str << *iter;
  }

  str << " }";
  return str.str();
}


// ----------------------------------------------------------------------------
// Name: TrimStringsInArray
// Desc: Trim all strings in the array
// Parm: stringArray the array of strings to trim
// Retn: A reference to the input stringArray argument
// ----------------------------------------------------------------------------
inline StringArray &TrimStringsInArray(StringArray &stringArray)
{
  StringArray::iterator iter(stringArray.begin()), end(stringArray.end());
  for (; iter != end; ++iter)
  {
    TrimString(*iter);
  }

  return stringArray;
}


// ----------------------------------------------------------------------------
// Name: SplitFilename
// Desc: Split a filename into a name and extension
// Parm: const String &str  - the filename
// Parm: String &filename   - the name of the file without the extension
// Parm: String &extension  - the extension
// ----------------------------------------------------------------------------
inline void SplitFilename(const String &str, String &filename, String &extension)
{
  // See if the string has a . in it
  int pos = (int) str.find_last_of('.', str.length());
  if (pos == -1)
    return;

  filename  = str.substr(0, pos);
  extension = str.substr(pos + 1);
} // SplitFilename


// --------------------------------------------------------------------
// Name: SplitPath
// Desc: Split a string that contains a path and a name into two 
//       seperate strings.  The name is the text after the final slash, 
//       and the path is everythjing before (which may contain other 
//       slashes)
// Parm: const String &str - the string to decompose
// Parm: String &path - the path
// Parm: String &name - the name
// --------------------------------------------------------------------
inline void SplitPath(const String &str, String &path, String &name)
{
  path = "";
  name = "";

  // Check we have some text
  if (str.empty())
    return;

  // See if the string has a slash in it
  int fs = (int) str.find_last_of('/', str.size());
  int bs = (int) str.find_last_of('\\', str.size());

  int last = Max<int>(fs, bs);
  if (last == -1)
  {
    // No slash, name is str
    name = str;
  } // if
  else
  {
    // Extract the name and path
    path = str.substr(0, last);
    name = str.substr(last + 1, str.size());
  } // else
} // SplitPath


// ----------------------------------------------------------------------------
// Name: LexicalCast
// Temp: Target - the target value type
// Temp: Source - the source value type
// Desc: Casts a value from one type to another, performing the conversion 
//       textually - that is, it is written out as text, and then interpreted, 
//       equivalent to printing it and then scanning it.  If the conversion is 
//       not possible, or fails for some reason, an InvalidParameterException 
//       will be thrown.  The template arguments specify the type of the source
//       infromation, and the type that we want to cast it to. The source type
//       can be automaticallly determined from the input parameter, but the 
//       return type needs to be specified as a template parameter.
// Parm: Source in - The value to convert. This is done by value, not by 
//       reference, to allow casting to also be performed on the function call
// Retn: Target    - The converted value
// ----------------------------------------------------------------------------
template <typename Target, typename Source>
Target LexicalCast(Source in)
{
  // Create our string stream, which we will use to perform the conversion
  // for us
  StringStream interpreter;
  interpreter.unsetf(std::ios::skipws);

  Target result;

  // Now perform the conversion
  if (!(interpreter << in) || !(interpreter >> result) || !(interpreter >> std::ws).eof())
  {
    // LOG_ERROR << "Error casting the input '" << value << "' to the desired type!" << ENDLOG;
  }  

  return result;
} // LexicalCast


// ----------------------------------------------------------------------------
// Name: LexicalCast
// Desc: Strings are a special case. In general, we want to use partial 
//       specialization to form a special case when the source and target types 
//       for the lexical cast are automatically convertible, or the same, but we
//       can't do this using MSVC yet
// Parm: String in                       - the source string
// Retn: String LexicalCast<String, - the target string
// ----------------------------------------------------------------------------
template <>
inline String LexicalCast<String, String>(String in)
{
  return in;
} // LexicalCast


// ----------------------------------------------------------------------------
// Name: PrintF
// Desc: Prints the given format and args to a String
// Parm: const char *format - the format 
// Parm: ...                - the var args
// Retn: The formatted string
// ----------------------------------------------------------------------------
inline String &PrintF(String &str, const char *format, ...)
{
  va_list args;
  int     len;
  char   *buffer;

  va_start(args, format);
  len = _vscprintf(format, args) + 1;
  buffer = new char[len * sizeof(char)];
  vsprintf(buffer, format, args);

  str = String(buffer);
  delete[] buffer;

  return str;
} // PrintF


// ----------------------------------------------------------------------------
// Name: PrintF
// Desc: Prints the given format and args to a String
// Parm: const char *format - the format 
// Parm: ...                - the var args
// Retn: The formatted string
// ----------------------------------------------------------------------------
inline String PrintF(const char *format, ...)
{
  va_list args;
  int     len;
  char   *buffer;

  va_start(args, format);
  len = _vscprintf(format, args) + 1;
  buffer = new char[len * sizeof(char)];
  vsprintf(buffer, format, args);

  String str = String(buffer);
  delete[] buffer;

  return str;
} // PrintF


// ----------------------------------------------------------------------------
// Name: StrICmp
// Desc: Compare 2 strings ignoring case
// ----------------------------------------------------------------------------
inline bool StrICmp(const String &a, const String &b)
{
  return (_stricmp(a.c_str(), b.c_str()) == 0);
}


// ----------------------------------------------------------------------------
// Test if a string starts with the given token
// ----------------------------------------------------------------------------
inline bool StartsWith(const String &str, const String &token)
{
  if (token.length() > str.length())
    return false;

  return (_strnicmp(str.c_str(), token.c_str(), token.length()) == 0);
}


// ----------------------------------------------------------------------------
// Test if a string ends with the given token
// ----------------------------------------------------------------------------
inline bool EndsWith(const String &str, const String &token)
{
  if (token.length() > str.length())
    return false;

  const char *pSrc1 = str.c_str();
  const char *pSrc2 = token.c_str();

  pSrc1 += (str.length() - token.length());

  return (_stricmp(pSrc1, pSrc2) == 0);
}


// ----------------------------------------------------------------------------
// Get a substring from the middle of a string
// ----------------------------------------------------------------------------
inline String StrMid(const String &str, int start, int length)
{
  return str.substr(start, length);
}


// ----------------------------------------------------------------------------
// Generate a case insensitive hash of the given string
// ----------------------------------------------------------------------------
inline uint HashCStr(const char *pStr)
{
  uint i;
  for (i = 0; *pStr; pStr++) 
  {
    char c = *pStr;
    c = (char)(c - (c & (c>>1) & 0x20));
    i = 131 * i + c;
  }
  return i;
}


// ----------------------------------------------------------------------------
// Generate a case insensitive hash of the given string
// ----------------------------------------------------------------------------
inline uint HashStr(const String &str)
{
  return HashCStr(str.c_str());
}


// ----------------------------------------------------------------------------
// Name: WriteBinaryString
// Desc: Write a String to a binary file
// Parm: FILE *file              - the file
// Parm: const String &text - the string
// Retn: bool                    - true if successful
// ----------------------------------------------------------------------------
inline bool WriteBinaryString(FILE *file, const String &text)
{
  size_t written = 0;
  for (size_t i = 0; i < text.size(); i++)
    written += fwrite(&text[i], sizeof(char), 1, file);

  char zero = 0;
  written += fwrite(&zero, sizeof(char), 1, file);

  return (written == text.size() + 1);
} // WriteBinaryString


// ----------------------------------------------------------------------------
// Name: ReadBinaryString
// Desc: Read a String from a binary file
// Parm: FILE *file        - the file
// Parm: String &text - a reference to the string
// Retn: bool              - true if successful
// ----------------------------------------------------------------------------
inline bool ReadBinaryString(FILE *file, String &text)
{
  text.clear();
  size_t read = 0, size = 0;

  char character;
  read += fread(&character, sizeof(char), 1, file);
  size++;

  while (character != 0)
  {
    text += character;
    read += fread(&character, sizeof(char), 1, file);
    size++;
  } // while

  return (read == size);
} // ReadBinaryString


// ----------------------------------------------------------------------------
// Name: FileString (class)
// Desc: A string class that can be directly read and written to a file
// ----------------------------------------------------------------------------
template <int Size>
class FileString
{
public:
  // --------------------------------------------------------------------------
  // Constructors
  // --------------------------------------------------------------------------
  inline FileString();
  inline FileString(const FileString &source);
  inline FileString(const String &source);
  inline FileString(const char *pSource);

  // --------------------------------------------------------------------------
  // Cast operators
  // --------------------------------------------------------------------------
  //operator const char*() const;
  inline operator String() const;
  inline operator bool() const;

  // --------------------------------------------------------------------------
  // Equality operators
  // --------------------------------------------------------------------------
  inline bool operator==(const char *pString) const;
  inline bool operator==(const String &string) const;
  inline bool operator==(const FileString &string) const;

  // --------------------------------------------------------------------------
  // Assignment
  // --------------------------------------------------------------------------
  inline FileString &operator=(const char *pString);
  inline FileString &operator=(const String &string);
  inline FileString &operator=(const FileString &string);

  // --------------------------------------------------------------------------
  // Get and Set the string
  // --------------------------------------------------------------------------
  inline void Set(const char *pString);
  inline const char *Get() const;

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  char m_Buffer[Size];

}; // FileString


// ----------------------------------------------------------------------------
// Name: operator<<
// Desc: Write the string to the stream
// Parm: OutputStream &os     - the stream
// Parm: const FileString &s  - the string
// Retn: OutputStream &       - the stream
// ----------------------------------------------------------------------------
template <int Size>
inline OutputStream &operator<<(OutputStream &os, const FileString<Size> &s)
{
  os << s.operator String();
  return os;
} // operator <<


// ----------------------------------------------------------------------------
// Name: operator<<
// Desc: read the string from the stream
// Parm: InputStream &is - the stream
// Parm: FileString &s    - the string
// Retn: InputStream &   - the stream
// ----------------------------------------------------------------------------
template <int Size>
inline InputStream &operator<<(InputStream &is, FileString<Size> &s)
{
  String str;
  is >> str;
  s.Set(str.c_str());
  return is;
} // operator <<


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
template <int Size>
inline FileString<Size>::FileString()
{
  m_Buffer[0] = '\0';
} // FileString


// ----------------------------------------------------------------------------
// Copy constructor
// ----------------------------------------------------------------------------
template <int Size>
inline FileString<Size>::FileString(const FileString &source)
{
  (*this) = source;
} // FileString


// ----------------------------------------------------------------------------
// Constructor from a String
// ----------------------------------------------------------------------------
template <int Size>
inline FileString<Size>::FileString(const String &source)
{
  (*this) = source;
} // FileString


// ----------------------------------------------------------------------------
// Constructor from a char pointer
// ----------------------------------------------------------------------------
template <int Size>
inline FileString<Size>::FileString(const char *pSource)
{
  (*this) = pSource;
} // FileString


// ----------------------------------------------------------------------------
// Cast operator to a String
// ----------------------------------------------------------------------------
template <int Size>
inline FileString<Size>::operator String() const
{
  return m_Buffer;
} // operator String


// ----------------------------------------------------------------------------
// Cast operator to a bool, returns true if the string is not empty
// ----------------------------------------------------------------------------
template <int Size>
inline FileString<Size>::operator bool() const
{
  return (m_Buffer[0] != '\0');
} // operator bool()


// ----------------------------------------------------------------------------
// Equality operator to compare to a char pointer
// ----------------------------------------------------------------------------
template <int Size>
inline bool FileString<Size>::operator==(const char *pString) const
{
  return (strcmp(m_Buffer, pString) == 0);
} // operator==


// ----------------------------------------------------------------------------
// Equality operator to compare to a String
// ----------------------------------------------------------------------------
template <int Size>
inline bool FileString<Size>::operator==(const String &string) const
{
  return (strcmp(m_Buffer, string.c_str()) == 0);
} // operator==


// ----------------------------------------------------------------------------
// Equality operator to compare to a FileString
// ----------------------------------------------------------------------------
template <int Size>
inline bool FileString<Size>::operator==(const FileString &string) const
{
  return (strcmp(m_Buffer, string.m_Buffer) == 0);
} // operator==


// ----------------------------------------------------------------------------
// Assignment operator to assign to a char pointer
// ----------------------------------------------------------------------------
template <int Size>
inline FileString<Size> &FileString<Size>::operator=(const char *pString)
{
  strcpy(m_Buffer, pString);
  return *this;
} // operator=


// ----------------------------------------------------------------------------
// Assignment operator to assign to a String
// ----------------------------------------------------------------------------
template <int Size>
inline FileString<Size> &FileString<Size>::operator=(const String &string)
{
  strcpy(m_Buffer, string.c_str());
  return *this;
} // operator=


// ----------------------------------------------------------------------------
// Assignment operator to assign to a FileString
// ----------------------------------------------------------------------------
template <int Size>
inline FileString<Size> &FileString<Size>::operator=(const FileString &string)
{
  strcpy(m_Buffer, string.m_Buffer);
  return *this;
} // operator=


// ----------------------------------------------------------------------------
// Set the string
// ----------------------------------------------------------------------------
template <int Size>
inline void FileString<Size>::Set(const char *pString)
{
  strcmp(m_Buffer, pString);
} // Set


// ----------------------------------------------------------------------------
// Get the string
// ----------------------------------------------------------------------------
template <int Size>
inline const char *FileString<Size>::Get() const
{
  return m_Buffer;
} // Get


#endif // STD_STR_H

// -- EOF

