// ----------------------------------------------------------------------------
// File: stdParser.h
// Desc: Basic parser that checks for #if XBOX and #if PC sections
// Auth: Michael Petrou
// (C) Copyright:   2007
// ----------------------------------------------------------------------------
#ifndef __STD_PARSER_H_
#define __STD_PARSER_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "stdType.h"
#include "stdStr.h"


// ----------------------------------------------------------------------------
// Max number of nested statements
// ----------------------------------------------------------------------------
#define MAX_PARSER_STATES 4


// ----------------------------------------------------------------------------
// Name: Parser (class)
// Desc: Copies from the input stream to the output stream but eliminates any
//       section that is not within the correct #if block for the compiled 
//       platform.
// ----------------------------------------------------------------------------
class Parser
{
public:
  // --------------------------------------------------------------------------
  // Constructor
  // --------------------------------------------------------------------------
  Parser(bool compileForPC = true);

  // --------------------------------------------------------------------------
  // Process the given input stream
  // --------------------------------------------------------------------------
  bool Process(InputStream &in, OutputStream &out);

private:
  // --------------------------------------------------------------------------
  // Record a syntax error
  // --------------------------------------------------------------------------
  void SyntaxError(const String &message, const String &context, int lineNumber);

  // --------------------------------------------------------------------------
  // Process the statement
  // --------------------------------------------------------------------------
  bool ProcessStatement(const String &line, OutputStream &out, int lineNumber);

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  bool  m_CompileForPC;                     // Do we compile for PC or XBOX
  bool  m_CurrentState[MAX_PARSER_STATES];  // The state array
  int   m_Index;                            // The current state index

};



#endif // __STD_PARSER_H_

// -- EOF

