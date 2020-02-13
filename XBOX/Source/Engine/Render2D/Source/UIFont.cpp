
// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "UIFont.h"


// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
UIFont::UIFont(UI *pUI)
: m_pUI     (pUI),
  m_Height  (0),
  m_Width   (0)
{
  REF_COUNT_CTOR(UIFont);
  memset(m_FontMetrics, 0, 256 * sizeof(ushort));
}


// --------------------------------------------------------------------------
// Destructor
// --------------------------------------------------------------------------
UIFont::~UIFont()
{
  REF_COUNT_DTOR(UIFont);
}


// --------------------------------------------------------------------------
// Load the font bitmap texture and the font metrics file(s)
// --------------------------------------------------------------------------
bool UIFont::Load(FileHandle texture, FileHandle metrics)
{
  // Load the bitmap font texture
  m_pTexture = TextureLoader::LoadTexture(texture);
  if (!m_pTexture)
  {
    LOG_ERROR << "Failed to load the font texture: " << texture.GetAbsoluteFilename() << ENDLOG;
    return false;
  }

  // Open the font metrics file
  FILE *pFile = fopen(metrics.GetAbsoluteFilename().c_str(), "rb");
  if (!pFile)
  {
    LOG_ERROR << "Failed to load the font metrics file: " << metrics.GetAbsoluteFilename() << ENDLOG;
    return false;
  }

  // Read the font metrics from the file
  if (fread(m_FontMetrics, 2, 256, pFile) != 256)
  {
    LOG_ERROR << "Failed to read the font metrics file: " << metrics.GetAbsoluteFilename() << ENDLOG;
    return false;    
  }

  // Get the texture size
  if (!m_pTexture->GetSize(m_Width, m_Height))
  {
    LOG_ERROR << "Failed to get the texture size of: " << texture.GetAbsoluteFilename() << ENDLOG;
    return false;    
  }

  // Close the file
  fclose(pFile);
  return true;
}


float UIFont::RenderSingleCharacter(UI *pUI, float x, float y, float h, char c, const Color &color)
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

  // Get the texture size
  float texW = m_Width  / 16.0f;
  float texH = m_Height / 16.0f;

  // Calculate the font metrics
  float charMetric = (float) m_FontMetrics[c];
  float startPixelOffset = (texW - charMetric) / 2;

  // Calculate the scale
  float scaleW = (viewW / uiW) * (h / texW);
  float scaleH = (viewH / uiH) * (h / texH);

  // Make a scale matrix
  Matrix scaleMatrix = Matrix::MakeNewScaling(scaleW, scaleH, 1.0f);

  // Get the position of the text
  float posX = x * (viewW / uiW);
  float posY = y * (viewH / uiH);

  // Apply the scale to the matrix
  scaleMatrix._41 = posX;
  scaleMatrix._42 = posY;

  // Get the x and y index
  ubyte xIdx = ((ubyte) c) % 16;
  ubyte yIdx = (ubyte) (c / 16);

  // Get the x and y positions
  uint x1 = (xIdx * texW) + startPixelOffset;
  uint x2 = x1 + charMetric;
  uint y1 = yIdx * texH;
  uint y2 = (yIdx + 1) * texH;

  // The texture rect
  RECT rect;
  SetRect(&rect, x1, y1 + 1, x2, y2 - 1);

  // Draw the sprite
#if XBOX
  pUI->GetSprite()->DrawTransform(m_pTexture->GetPtr(), &rect, &scaleMatrix, color);

#else
  pUI->GetSprite()->SetTransform(&scaleMatrix);
  pUI->GetSprite()->Draw(m_pTexture->GetPtr(), &rect, NULL, NULL, color);
#endif

  // Calculate the ui space width of this character
  return h * (static_cast<float>(charMetric) / static_cast<float>(texW));  
}


// --------------------------------------------------------------------------
// Draw the text using the given forground color.
// The position specifies the position within the virtual UI desktop.
// The height specifies the height (in the virtual UI desktop coords) of the
// text.
// The format specifies the justification options.
// --------------------------------------------------------------------------
void UIFont::DrawText(UI *pUI, const String &text, float x, float y, float h, 
  const Color &color, uint format)
{
  float offset = 0.0f;
  for (uint i = 0; i < text.length(); i++)
  {
    float thisOffset = offset;
    offset += RenderSingleCharacter(pUI, x + thisOffset, y, h, text[i], color);
  }
}


// -- EOF

