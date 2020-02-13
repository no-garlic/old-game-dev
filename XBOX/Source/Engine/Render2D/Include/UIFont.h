
#ifndef __UI_FONT_H_
#define __UI_FONT_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libRenderExt.h"
#include "UI.h"


// ----------------------------------------------------------------------------
// Bitmap font class
// ----------------------------------------------------------------------------
class UIFont
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  UIFont(UI *pUI);
  virtual ~UIFont();

  // --------------------------------------------------------------------------
  // Load the font bitmap texture and the font metrics file(s)
  // --------------------------------------------------------------------------
  bool Load(FileHandle texture, FileHandle metrics);
  
  // --------------------------------------------------------------------------
  // Draw the text using the given forground color.
  // The position specifies the position within the virtual UI desktop.
  // The height specifies the height (in the virtual UI desktop coords) of the
  // text.
  // The format specifies the justification options.
  // --------------------------------------------------------------------------
  void DrawText(UI *pUI, const String &text, float x, float y, float h, 
    const Color &color, uint format = 0);
  
private:
  float RenderSingleCharacter(UI *pUI, float x, float y, float h, char c, const Color &color);

  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  UI           *m_pUI;              // The UI managing this font
  Texture      *m_pTexture;         // The font texture
  ushort        m_FontMetrics[256]; // The font metrics
  uint          m_Width;            // The texture width
  uint          m_Height;           // The texture height

};


#endif // __UI_FONT_H_

// -- EOF

