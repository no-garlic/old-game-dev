// ----------------------------------------------------------------------------
// File: UIConfig.h
// Desc: User interface configuration file parser
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __UI_CONFIG_H_
#define __UI_CONFIG_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "libStandard.h"
#include "UI.h"


// ----------------------------------------------------------------------------
// User interface configuration file parser
// ----------------------------------------------------------------------------
class UIConfig
{
public:
  // --------------------------------------------------------------------------
  // Create a UI from the given file
  // --------------------------------------------------------------------------
  static UI *Create(FileHandle handle);

private:
  // --------------------------------------------------------------------------
  // Parsing functions
  // --------------------------------------------------------------------------
  static bool ProcessFontSection(UI *pUI, const ConfigSection &section);
  static bool ProcessLayerSection(UI *pUI, const ConfigSection &section);
  static bool LoadLayer(UI *pUI, uint depth, bool visible, const String &name, FileHandle handle);
  static bool AddComponent(UI *pUI, UIObject *pObject, const ConfigSection &section);

  // --------------------------------------------------------------------------
  // Add components
  // --------------------------------------------------------------------------
  static UIComponent *AddImage(UI *pUI, UIObject *pObject, const ConfigSection &section);
  static UIComponent *AddGroup(UI *pUI, UIObject *pObject, const ConfigSection &section);
  static UIComponent *AddText(UI *pUI, UIObject *pObject, const ConfigSection &section);

};


#endif // __UI_CONFIG_H_

// -- EOF

