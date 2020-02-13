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
#include "Kernel/Types.h"
#include "Kernel/StdMath.h"
#include "Kernel/Exceptions.h"
#include <string>


// ----------------------------------------------------------------------------
// String and StringStream defines
// ----------------------------------------------------------------------------
typedef std::string String;
typedef std::stringstream StringStream;


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


// --------------------------------------------------------------------
// Name: Space
// Desc: Create a string with the specified number of spaces in it
// Parm: size_t num  - the number of spaces
// Retn: String - the string
// --------------------------------------------------------------------
inline String Space(size_t num)
{
  String str;
  for (size_t i = 0; i < num; i++)
    str += " ";

  return str;
} // Space


// --------------------------------------------------------------------
// Name: AppendInt
// Desc: Append an integer at the end of a string
// Parm: String &str - the string to append the integer to
// Parm: int i         - the integer
// Retn: String & - the in string so this function can be chained
// --------------------------------------------------------------------
inline String &AppendInt(String &str, int i)
{
  char buffer[32];
  sprintf(buffer, "%d", i);
  str += buffer;
  return str;
} // AppendInt


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
  static const std::basic_string <char>::size_type npos = -1;

  std::basic_string<char>::size_type pos1;
  std::basic_string<char>::size_type pos2;

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

  int last = std::max<int>(fs, bs);
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
    throw InvalidParameterException(FLSTAMP) 
    << "Error casting the input '" << in 
    << "' to the desired type!";

  return result;
} // LexicalCast


// ----------------------------------------------------------------------------
// Name: String>
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
// Name: ToString
// Desc: Convert the value to a string
// Parm: int value - the value
// Retn: String    - the string
// ----------------------------------------------------------------------------
inline String ToString(int value)
{
  char buffer[32];
  if (sprintf(buffer, "%d", value) == -1)
    throw InvalidParameterException(FLSTAMP, "Failed to convert ") << value << " to a String";

  return buffer;
} // FromInt


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
    throw InvalidParameterException(FLSTAMP, "Failed to convert ") << value << " to a String";

  return buffer;
} // FromFloat


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
    throw InvalidParameterException(FLSTAMP, "Failed to convert ") << (value ? "true" : "false") << " to a String";

  return buffer;
} // FromBool


// ----------------------------------------------------------------------------
// Name: PadStr
// Desc: Create a string with the given number of whitespace
// Parm: unsigned int width - the number of blenk characters
// Retn: String             - the string
// ----------------------------------------------------------------------------
inline String PadStr(unsigned int width)
{
  String str;

  while (str.length() < width)
    str += " ";

  return str;
} // PadStr


// --------------------------------------------------------------------
// Name: WriteBinaryString
// Desc: Write a String to a binary file
// Parm: FILE *file              - the file
// Parm: const String &text - the string
// Retn: bool                    - true if successful
// --------------------------------------------------------------------
inline bool WriteBinaryString(FILE *file, const String &text)
{
  size_t written = 0;
  for (size_t i = 0; i < text.size(); i++)
    written += fwrite(&text[i], sizeof(char), 1, file);

  char zero = 0;
  written += fwrite(&zero, sizeof(char), 1, file);

  return (written == text.size() + 1);
} // WriteBinaryString


// --------------------------------------------------------------------
// Name: ReadBinaryString
// Desc: Read a String from a binary file
// Parm: FILE *file        - the file
// Parm: String &text - a reference to the string
// Retn: bool              - true if successful
// --------------------------------------------------------------------
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
  inline operator std::string() const;
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

}; // FileStrig


// ----------------------------------------------------------------------------
// Name: operator<<
// Desc: Write the string to the stream
// Parm: std::ostream &os     - the stream
// Parm: const FileString &s  - the string
// Retn: std::ostream &       - the stream
// ----------------------------------------------------------------------------
template <int Size>
inline std::ostream &operator<<(std::ostream &os, const FileString<Size> &s)
{
  os << s.operator String();
  return os;
} // operator <<


// ----------------------------------------------------------------------------
// Name: operator<<
// Desc: read the string from the stream
// Parm: std::istream &is - the stream
// Parm: FileString &s    - the string
// Retn: std::istream &   - the stream
// ----------------------------------------------------------------------------
template <int Size>
inline std::istream &operator<<(std::istream &is, FileString<Size> &s)
{
  std::string str;
  is >> str;
  s.Set(str.c_str());
  return is;
} // operator <<


template <int Size>
inline FileString<Size>::FileString()
{
  m_Buffer[0] = '\0';
} // FileString


template <int Size>
inline FileString<Size>::FileString(const FileString &source)
{
  (*this) = source;
} // FileString


template <int Size>
inline FileString<Size>::FileString(const String &source)
{
  (*this) = source;
} // FileString


template <int Size>
inline FileString<Size>::FileString(const char *pSource)
{
  (*this) = pSource;
} // FileString


template <int Size>
inline FileString<Size>::operator std::string() const
{
  return m_Buffer;
} // operator std::string


template <int Size>
inline FileString<Size>::operator bool() const
{
  return (m_Buffer[0] != '\0');
} // operator bool()


template <int Size>
inline bool FileString<Size>::operator==(const char *pString) const
{
  return (strcmp(m_Buffer, pString) == 0);
} // operator==


template <int Size>
inline bool FileString<Size>::operator==(const String &string) const
{
  return (strcmp(m_Buffer, string.c_str()) == 0);
} // operator==


template <int Size>
inline bool FileString<Size>::operator==(const FileString &string) const
{
  return (strcmp(m_Buffer, string.m_Buffer) == 0);
} // operator==


template <int Size>
inline FileString<Size> &FileString<Size>::operator=(const char *pString)
{
  strcpy(m_Buffer, pString);
  return *this;
} // operator=


template <int Size>
inline FileString<Size> &FileString<Size>::operator=(const String &string)
{
  strcpy(m_Buffer, string.c_str());
  return *this;
} // operator=


template <int Size>
inline FileString<Size> &FileString<Size>::operator=(const FileString &string)
{
  strcpy(m_Buffer, string.m_Buffer);
  return *this;
} // operator=


template <int Size>
inline void FileString<Size>::Set(const char *pString)
{
  strcmp(m_Buffer, pString);
} // Set


template <int Size>
inline const char *FileString<Size>::Get() const
{
  return m_Buffer;
} // Get



#endif // STD_STR_H

// -- EOF

