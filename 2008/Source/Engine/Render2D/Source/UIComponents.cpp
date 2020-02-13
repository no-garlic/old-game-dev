// ----------------------------------------------------------------------------
// File: UIComponents.cpp
// Desc: User interface conponents
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#include "UIComponents.h"


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
UIGroup::UIGroup(const String &name)
: UIComponent (UIGroup::Type(), name)
{
  REF_COUNT_CTOR(UIGroup);
}


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
UIGroup::~UIGroup()
{
  REF_COUNT_DTOR(UIGroup);
}


// ----------------------------------------------------------------------------
// Render the component
// ----------------------------------------------------------------------------
void UIGroup::RenderInternal(UI *pUI, int x, int y)
{
}


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
UIImage::UIImage(const String &name)
: UIComponent   (UIImage::Type(), name),
  m_pTexture    (NULL),
  m_TextureRect (Rect(0,0,1,1)),
  m_Color       (Color::White)
{
  REF_COUNT_CTOR(UIImage);
}


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
UIImage::~UIImage()
{
  REF_COUNT_DTOR(UIImage);
  SafeUnRef(m_pTexture);
}


// ----------------------------------------------------------------------------
// Set the image texture
// ----------------------------------------------------------------------------
void UIImage::SetTexture(Texture *pTexture, const Rect &rect)
{
  m_TextureRect = rect;

  SafeUnRef(m_pTexture);
  m_pTexture = pTexture;
  SafeRef(m_pTexture);
}


// ----------------------------------------------------------------------------
// Set the texture rect
// ----------------------------------------------------------------------------
void UIImage::SetTextureRect(const Rect &rect)
{
  m_TextureRect = rect;
}


// ----------------------------------------------------------------------------
// Set the default color
// ----------------------------------------------------------------------------
void UIImage::SetColor(const Color &color)
{
  m_Color = color;
}


// ----------------------------------------------------------------------------
// Render the component
// ----------------------------------------------------------------------------
void UIImage::RenderInternal(UI *pUI, int x, int y)
{
  // Get the viewport
  VIEWPORT viewport;
  Device->GetViewport(&viewport);

  // Get the viewport size
  float viewW = (float) viewport.Width;
  float viewH = (float) viewport.Height;

  // Get the UI size
  float uiW, uiH;
  pUI->GetSize(uiW, uiH);

  // Get the image size
  float imgW, imgH;
  GetSize(imgW, imgH);

  // Get the texture size
  float texW = (float) (m_TextureRect.right - m_TextureRect.left);
  float texH = (float) (m_TextureRect.bottom - m_TextureRect.top);

  // Calculate the scale
  float scaleW = (viewW / uiW) * (imgW / texW);
  float scaleH = (viewH / uiH) * (imgH / texH);

  // Make a scale matrix
  Matrix scaleMatrix = Matrix::MakeNewScaling(scaleW, scaleH, 1.0f);

  // Get the position of the text
  float posX = x * (viewW / uiW);
  float posY = y * (viewH / uiH);

  // Apply the scale to the matrix
  scaleMatrix._41 = posX;
  scaleMatrix._42 = posY;

  // The texture rect
  RECT *pRect = (RECT *) &m_TextureRect;

  // Draw the sprite
#if XBOX
  pUI->GetSprite()->DrawTransform(m_pTexture->GetPtr(), pRect, &scaleMatrix, m_Color);

#else
  Color c = m_Color;
  c.a     = GetAlpha();

  pUI->GetSprite()->SetTransform(&scaleMatrix);
  pUI->GetSprite()->Draw(m_pTexture->GetPtr(), pRect, NULL, NULL, c);
#endif
}


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
UIText::UIText(const String &name)
: UIComponent   (UIText::Type(), name),
  m_FontId      (InvalidFont),
  m_Format      (0),
  m_Height      (1.0f),
  m_Color       (Color::White)
{
  REF_COUNT_CTOR(UIText);
}


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
UIText::~UIText()
{
  REF_COUNT_DTOR(UIText);
}


// ----------------------------------------------------------------------------
// Set the text
// ----------------------------------------------------------------------------
void UIText::SetText(const String &text)
{
  m_Text = text;
}


// ----------------------------------------------------------------------------
// Get the text
// ----------------------------------------------------------------------------
const String &UIText::GetText()
{
  return m_Text;
}


// ----------------------------------------------------------------------------
// Set the font
// ----------------------------------------------------------------------------
void UIText::SetFont(UIFontID fontId)
{
  m_FontId = fontId;
}


// ----------------------------------------------------------------------------
// Set the text format
// ----------------------------------------------------------------------------
void UIText::SetFormat(int format)
{
  m_Format = format;
}


// ----------------------------------------------------------------------------
// Set the text color
// ----------------------------------------------------------------------------
void UIText::SetColor(const Color &color)
{
  m_Color = color;
}


// ----------------------------------------------------------------------------
// Set the font height
// ----------------------------------------------------------------------------
void UIText::SetHeight(float height)
{
  m_Height = height;
}


// ----------------------------------------------------------------------------
// Render the component
// ----------------------------------------------------------------------------
void UIText::RenderInternal(UI *pUI, int x, int y)
{
  pUI->DrawText(m_FontId, m_Text, x, y, m_Height, m_Color, m_Format);
}


// -- EOF

