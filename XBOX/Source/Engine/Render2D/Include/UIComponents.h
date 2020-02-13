// ----------------------------------------------------------------------------
// File: UIComponents.h
// Desc: User interface conponents
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __UI_COMPONENTS_H_
#define __UI_COMPONENTS_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "UI.h"


// ----------------------------------------------------------------------------
// The group component
// ----------------------------------------------------------------------------
class UIGroup : public UIComponent
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  UIGroup(const String &name);
  virtual ~UIGroup();

  // --------------------------------------------------------------------------
  // The component type
  // --------------------------------------------------------------------------
  static UIComponentType Type() { return UI_Group; }

  // --------------------------------------------------------------------------
  // Render the component
  // --------------------------------------------------------------------------
  virtual void RenderInternal(UI *pUI, int x, int y);

};


// ----------------------------------------------------------------------------
// The image component
// ----------------------------------------------------------------------------
class UIImage : public UIComponent
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  UIImage(const String &name);
  virtual ~UIImage();

  // --------------------------------------------------------------------------
  // The component type
  // --------------------------------------------------------------------------
  static UIComponentType Type() { return UI_Image; }

  // --------------------------------------------------------------------------
  // Set the texture for the component
  // --------------------------------------------------------------------------
  void SetTexture(Texture *pTexture, const Rect &rect);
  void SetTextureRect(const Rect &rect);
  void SetColor(const Color &color);

  // --------------------------------------------------------------------------
  // Render the component
  // --------------------------------------------------------------------------
  virtual void RenderInternal(UI *pUI, int x, int y);

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  Texture    *m_pTexture;     // The texture
  Rect        m_TextureRect;  // The texture rect
  Color       m_Color;        // The background color

};


// ----------------------------------------------------------------------------
// The text component
// ----------------------------------------------------------------------------
class UIText : public UIComponent
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  UIText(const String &name);
  virtual ~UIText();

  // --------------------------------------------------------------------------
  // The component type
  // --------------------------------------------------------------------------
  static UIComponentType Type() { return UI_Text; }

  // --------------------------------------------------------------------------
  // Set the text
  // --------------------------------------------------------------------------
  void SetText(const String &text);
  const String &GetText();

  // --------------------------------------------------------------------------
  // Set the font style
  // --------------------------------------------------------------------------
  void SetFont(UIFontID fontId);
  void SetFormat(int format);
  void SetColor(const Color &color);
  void SetHeight(float height);

  // --------------------------------------------------------------------------
  // Render the component
  // --------------------------------------------------------------------------
  virtual void RenderInternal(UI *pUI, int x, int y);

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  String      m_Text;     // The text
  UIFontID    m_FontId;   // The font
  int         m_Format;   // The text format
  Color       m_Color;    // The text color
  float       m_Height;   // The font height

};


#endif // __UI_COMPONENTS_H_

// -- EOF

