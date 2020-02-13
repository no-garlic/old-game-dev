using System;
using System.Collections.Generic;
using System.Text;

using Common;


namespace Freeworld3D
{
  public class Parser
  {
    // ------------------------------------------------------------------------
    // Private Members
    //
    private List<TokenItem> m_tokenItems;


    // ------------------------------------------------------------------------
    // Publkic Properties
    //
    public List<TokenItem> TokenItems   { get { return m_tokenItems; } }


    // ------------------------------------------------------------------------
    // The item representing a line of the loaded file
    //
    public class TokenItem
    {
      public int          Indent;
      public List<String> Tokens;
    }

    
    // ------------------------------------------------------------------------
    // Constructor
    //
    public Parser()
    {
      m_tokenItems = new List<TokenItem>();
    }


    // ------------------------------------------------------------------------
    // Create the metadata from the string
    //
    public void Create(String a_str)
    {
      // Clear the items array
      m_tokenItems.RemoveRange(0, m_tokenItems.Count);

      // Split the string into a list of strings, each representing a seperate line.
      List<String> stringArray = StringUtil.TokenizeString(a_str, '\n', '\r');

      // Iterate over all strings and convert them into tokenized structs
      for (int i = 0; i < stringArray.Count; i++)
      {
        TokenItem item = new TokenItem();

        String str  = StringUtil.RemoveLeadingCharacter(stringArray[i], '\t', out item.Indent);
        item.Tokens = StringUtil.TokenizeString(str, ',');

        m_tokenItems.Add(item);
      }
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF

