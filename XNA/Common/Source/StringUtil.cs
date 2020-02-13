using System;
using System.Collections.Generic;
using System.Text;

using Microsoft.Xna.Framework;


namespace Common
{
  public class StringUtil
  {
    // ------------------------------------------------------------------------
    // Tokenize the string
    //
    public static List<String> TokenizeString(String a_str, char a_token)
    {
      List<String> stringArray = new List<String>();
      String s = String.Empty;

      for (int i = 0; i < a_str.Length; i++)
      {
        char c = a_str[i];

        if (c == a_token)
        {
          if (s.Length > 0)
          {
            stringArray.Add(s);
            s = String.Empty;
            continue;
          }
        }
        else
        {
          s += c;      
        }
      }

      if (s.Length > 0)
      {
        stringArray.Add(s);
      }

      return stringArray;
    }
    

    // ------------------------------------------------------------------------
    // Tokenize the string
    //
    public static List<String> TokenizeString(String a_str, char a_token1, char a_token2)
    {
      List<String> stringArray = new List<String>();
      String s = String.Empty;

      for (int i = 0; i < a_str.Length; i++)
      {
        char c = a_str[i];

        if (c == a_token1 || c == a_token2)
        {
          if (s.Length > 0)
          {
            stringArray.Add(s);
            s = String.Empty;
            continue;
          }
        }
        else
        {
          s += c;      
        }
      }

      if (s.Length > 0)
      {
        stringArray.Add(s);
      }

      return stringArray;
    }


    // ------------------------------------------------------------------------
    // Removes the leading character from the string and counts them
    //
    public static String RemoveLeadingCharacter(String a_str, char a_char, out int a_count)
    {
      String str = a_str;
      a_count = 0;

      for (int i = 0; i < str.Length; i++)
      {
        if (str[0] == a_char)
        {
          a_count++;
          str = str.Remove(0, 1);
        }
        else
        {
          return str;
        }
      }
      return str;
    }


    // ------------------------------------------------------------------------
    // Removes the file extension from the string
    //
    public static String RemoveFileExtension(String a_str)
    {
      List<String> stringArray = TokenizeString(a_str, '.');

      if (stringArray.Count > 0)
      {
        return stringArray[0];
      }

      return a_str;
    }


    // ------------------------------------------------------------------------
    // Removes the file path and extension from the string
    //
    public static String RemoveFilePathAndExtension(String a_str)
    {
      String str = RemoveFileExtension(a_str);

      List<String> stringArray = TokenizeString(str, '/', '\\');

      if (stringArray.Count > 0)
      {
        return stringArray[stringArray.Count - 1];
      }

      return a_str;
    }


    //
    // ------------------------------------------------------------------------
  }
}



