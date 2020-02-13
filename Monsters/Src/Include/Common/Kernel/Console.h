// ----------------------------------------------------------------------------
// File: Console.h
// Desc: ANSI console mode, allowing console IO with colors
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef CONSOLE_COL_H
#define CONSOLE_COL_H


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Kernel/Types.h"


// ----------------------------------------------------------------------------
// Console functions
// ----------------------------------------------------------------------------
namespace Console
{
  // --------------------------------------------------------------------------
  // Foreground colors
  // --------------------------------------------------------------------------
  static const unsigned short FG_BLUE      = 0x0001;
  static const unsigned short FG_GREEN     = 0x0002;
  static const unsigned short FG_RED       = 0x0004;
  static const unsigned short FG_WHITE     = 0x0007;
  static const unsigned short FG_BLACK     = 0x0000;
  static const unsigned short FG_INTENSITY = 0x0008;

  // --------------------------------------------------------------------------
  // Background colors
  // --------------------------------------------------------------------------
  static const unsigned short BG_BLUE      = 0x0010;
  static const unsigned short BG_GREEN     = 0x0020;
  static const unsigned short BG_RED       = 0x0040;
  static const unsigned short BG_WHITE     = 0x0070;
  static const unsigned short BG_BLACK     = 0x0000;
  static const unsigned short BG_INTENSITY = 0x0080;

  // --------------------------------------------------------------------------
  // Initrialise and close the console mode
  // --------------------------------------------------------------------------
  bool Init();
  bool Close();

  // --------------------------------------------------------------------------
  // Set the colors
  // --------------------------------------------------------------------------
  void SetAttributes(unsigned short attrib);

  // --------------------------------------------------------------------------
  // Clear the screen
  // --------------------------------------------------------------------------
  void Clear();
  
  // --------------------------------------------------------------------------
  // Set and get texr
  // --------------------------------------------------------------------------
  void Print(const char *str, ...);
  String GetText();

}; // namespace Console


#endif // CONSOLE_COL_H

// -- EOF

