// ----------------------------------------------------------------------------
// File: UI.cpp
// Desc: User interface
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#include "UI.h"
#include "UIFont.h"


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
UI::UI(float width, float height)
: m_Width   (width),
  m_Height  (height),
  m_Sprite  (NULL)
{
  REF_COUNT_CTOR(UI);
  AllocateDeviceMemory();
}


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
UI::~UI()
{
  REF_COUNT_DTOR(UI);

  // Delete all layers
  UILayerArray::iterator iter(m_Layers.begin()), end(m_Layers.end());
  for(; iter != end; ++iter)
    delete (iter->second);

  // Delete all fonts
  for (uint i = 0; i < m_Fonts.size(); i++)
    delete m_Fonts[i].second;

  ReleaseDeviceMemory();
}


// ----------------------------------------------------------------------------
// Get the user interface size
// ----------------------------------------------------------------------------
void UI::GetSize(float &width, float &height)
{
  width  = m_Width;
  height = m_Height;
}


// ----------------------------------------------------------------------------
// Get the layer for the given name
// ----------------------------------------------------------------------------
UILayer *UI::GetLayer(const String &name)
{
  UILayerArray::iterator iter(m_Layers.begin()), end(m_Layers.end());
  for(; iter != end; ++iter)
  {
    if (iter->second->GetName() == name)
      return iter->second;
  }

  return NULL;
}


// ----------------------------------------------------------------------------
// Add a layer to the user interface
// ----------------------------------------------------------------------------
UILayer *UI::AddLayer(UINT depth, const String &name)
{
  // Check for a unique name
  if (GetLayer(name))
  {
    LOG_ERROR << "A layer named: " << name << " already exists." << ENDLOG;
    return NULL;
  }

  // Check for a unique depth
  if (m_Layers.find(depth) != m_Layers.end())
  {
    LOG_ERROR << "A layer at depth: " << depth << " already exists." << ENDLOG;
    return NULL;
  }

  // Create the new layer
  UILayer *pLayer = new UILayer(name);
  m_Layers[depth] = pLayer;
  return pLayer;
}


// ----------------------------------------------------------------------------
// Render the UI
// ----------------------------------------------------------------------------
void UI::Render()
{
  if (!m_Sprite)
    return;

#if XBOX
  m_Sprite->Begin();
#else
  m_Sprite->Begin(D3DXSPRITE_ALPHABLEND);
#endif

  // Iterate all layers in depth order
  UILayerArray::iterator iter(m_Layers.begin()), end(m_Layers.end());
  for(; iter != end; ++iter)
  {
    if (iter->second->m_Visible)
      iter->second->Render(this);
  }

  m_Sprite->End();
}


// ----------------------------------------------------------------------------
// Get the sprite
// ----------------------------------------------------------------------------
LPD3DXSPRITE UI::GetSprite()
{
  return m_Sprite;
}


// ----------------------------------------------------------------------------
// Add a font to the user interface
// ----------------------------------------------------------------------------
UIFontID UI::AddFont(const String &name, const String &textureFile, const String &metricsFile)
{
  // Check if we have already added a font of this name
  UIFontID id = FindFont(name);
  if (id != InvalidFont)
    return InvalidFont;

  // Make the file handles
  FileHandle texHandle = Application.GetTextureDatabase()->FindFileHandle(textureFile);
  FileHandle metHandle = Application.GetUIDatabase()->FindFileHandle(metricsFile);

  // Create and load the font
  UIFont *pFont = new UIFont(this);
  if (!pFont->Load(texHandle, metHandle))
  {
    LOG_ERROR << "Failed to load the font: " << name << ENDLOG;
    delete pFont;
    return InvalidFont;
  }

  // Get the new ID
  id = m_Fonts.size();

  // Add the font to the array
  std::pair<String, UIFont *> fontPair(name, pFont);
  m_Fonts.push_back(fontPair);
  return id;
}


// ----------------------------------------------------------------------------
// Find a font by ID
// ----------------------------------------------------------------------------
UIFontID UI::FindFont(const String &name)
{
  for (uint i = 0; i < m_Fonts.size(); i++)
  {
    if ((m_Fonts[i]).first == name)
      return i;
  }

  return InvalidFont;
}


// ----------------------------------------------------------------------------
// Draw text
// ----------------------------------------------------------------------------
void UI::DrawText(UIFontID fontId, const String &text, float x, float y, float h,
    const Color &color, uint format)
{
  UIFont *pFont = m_Fonts[fontId].second;
  NULL_ASSERT(pFont);
  pFont->DrawText(this, text, x, y, h, color, format);
}


// ----------------------------------------------------------------------------
// Find a component
// ----------------------------------------------------------------------------
UIComponent *UI::FindComponent(UIComponentType type, const String &pathname)
{
  String head, tail;
  SplitString(pathname, '/', head, tail);

  UILayer *pLayer = GetLayer(head);
  if (!pLayer)
    return NULL;

  UIComponent *pComponent = pLayer->FindComponent(tail);
  if (!pComponent)
    return NULL;

  if (pComponent->IsOfType(type))
    return pComponent;

  return NULL;
}


// ----------------------------------------------------------------------------
// Allocate the device objects
// ----------------------------------------------------------------------------
bool UI::AllocateDeviceMemory()
{
  if (FAILED(D3DXCreateSprite(Device, &m_Sprite)))
  {
    LOG_ERROR << "Failed to create the sprite" << ENDLOG;
    m_Sprite = NULL;
    return false;
  }

  return true;
}


// ----------------------------------------------------------------------------
// Release the device objects
// ----------------------------------------------------------------------------
bool UI::ReleaseDeviceMemory()
{
  SafeRelease(m_Sprite);
  m_Sprite = NULL;

  return true;
}


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
UILayer::UILayer(const String &name)
: m_Name    (name),
  m_Visible (true)
{
  REF_COUNT_CTOR(UILayer);
}


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
UILayer::~UILayer()
{
  REF_COUNT_DTOR(UILayer);

  // Delete all components
  UIComponentArray::iterator iter(m_Components.begin()), end(m_Components.end());
  for (; iter != end; ++iter)
    delete iter->second;
}


// ----------------------------------------------------------------------------
// Get the name
// ----------------------------------------------------------------------------
const String &UILayer::GetName()
{
  return m_Name;
}


// ----------------------------------------------------------------------------
// Set the visibility flag of this layer
// ----------------------------------------------------------------------------
void UILayer::SetVisible(bool visible)
{
  m_Visible = visible;
}


// ----------------------------------------------------------------------------
// Add a component to this layer
// ----------------------------------------------------------------------------
bool UILayer::AddComponent(UIComponent *pComponent)
{
  if (m_Components.find(pComponent->GetName()) != m_Components.end())
  {
    LOG_ERROR << "A component named: " << pComponent->GetName() << " already exists in this layer" << ENDLOG;
    return false;
  }

  m_Components[pComponent->GetName()] = pComponent;
  return true;
}


// ----------------------------------------------------------------------------
// Find a component
// ----------------------------------------------------------------------------
UIComponent *UILayer::FindComponent(const String &pathname)
{
  String head, tail;
  SplitString(pathname, '/', head, tail);

  // Find the component with the first part of the string
  UIComponentArray::iterator iter = m_Components.find(head);

  // If the component was not found, return NULL
  if (iter == m_Components.end())
    return NULL;

  // If there is no tail, then return the component
  if (tail.empty())
    return iter->second;

  // The tail is not empty, so search the component for a child
  return iter->second->FindComponent(tail);
}


// ----------------------------------------------------------------------------
// Render the UI
// ----------------------------------------------------------------------------
void UILayer::Render(UI *pUI)
{
  UIComponentArray::iterator iter(m_Components.begin()), end(m_Components.end());
  for (; iter != end; ++iter)
    iter->second->Render(pUI, 0, 0);
}


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
UIComponent::UIComponent(UIComponentType type, const String &name)
: m_Name      (name),
  m_Type      (type),
  m_Visible   (true),
  m_Width     (100.0f),
  m_Height    (100.0f),
  m_PositionX (0.0f),
  m_PositionY (0.0f),
  m_Alpha     (1.0f)
{
  REF_COUNT_CTOR(UIComponent);
}


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
UIComponent::~UIComponent()
{
  REF_COUNT_DTOR(UIComponent);

  // Delete all components
  UIComponentArray::iterator iter(m_Components.begin()), end(m_Components.end());
  for (; iter != end; ++iter)
    delete iter->second;
}


// ----------------------------------------------------------------------------
// Get the component name
// ----------------------------------------------------------------------------
const String &UIComponent::GetName()
{
  return m_Name;
}


// ----------------------------------------------------------------------------
// Render the component
// ----------------------------------------------------------------------------
void UIComponent::Render(UI *pUI, int x, int y)
{
  // Exit if not visible
  if (!m_Visible)
    return;

  // Translate the position to the parents position
  float xPos = m_PositionX + x;
  float yPos = m_PositionY + y;

  // Sprite stuff
  RenderInternal(pUI, (int)xPos, (int)yPos);

  // Render the children at the parents position offset
  UIComponentArray::iterator iter(m_Components.begin()), end(m_Components.end());
  for (; iter != end; ++iter)
  {
    iter->second->Render(pUI, (int)xPos, (int)yPos);
  }
}


// ----------------------------------------------------------------------------
// Set the alpha
// ----------------------------------------------------------------------------
void UIComponent::SetAlpha(float alpha)
{
  m_Alpha = alpha;
}


// ----------------------------------------------------------------------------
// Set the component size
// ----------------------------------------------------------------------------
void UIComponent::SetSize(float width, float height)
{
  m_Width  = width;
  m_Height = height;
}


// ----------------------------------------------------------------------------
// Set the component position
// ----------------------------------------------------------------------------
void UIComponent::SetPosition(float x, float y)
{
  m_PositionX = x;
  m_PositionY = y;
}


// ----------------------------------------------------------------------------
// Get the component size
// ----------------------------------------------------------------------------
void UIComponent::GetSize(float &width, float &height)
{
  width  = m_Width;
  height = m_Height;
}


// ----------------------------------------------------------------------------
// Get the component position
// ----------------------------------------------------------------------------
void UIComponent::GetPosition(float &x, float &y)
{
  x = m_PositionX;
  y = m_PositionY;
}


// ----------------------------------------------------------------------------
// Set the visibility flag of this component
// ----------------------------------------------------------------------------
void UIComponent::SetVisible(bool visible)
{
  m_Visible = visible;
}


// ----------------------------------------------------------------------------
// Get the visibility flag of this component
// ----------------------------------------------------------------------------
bool UIComponent::IsVisible()
{
  return m_Visible;
}


// ----------------------------------------------------------------------------
// Add a child component to this component
// ----------------------------------------------------------------------------
bool UIComponent::AddComponent(UIComponent *pComponent)
{
  if (m_Components.find(pComponent->GetName()) != m_Components.end())
  {
    LOG_ERROR << "A component named: " << pComponent->GetName() << " already exists in this layer" << ENDLOG;
    return false;
  }

  m_Components[pComponent->GetName()] = pComponent;
  return true;
}


// ----------------------------------------------------------------------------
// Find a child component in this component
// ----------------------------------------------------------------------------
UIComponent *UIComponent::FindComponent(const String &pathname)
{
  String head, tail;
  SplitString(pathname, '/', head, tail);

  // Find the component with the first part of the string
  UIComponentArray::iterator iter = m_Components.find(head);

  // If the component was not found, return NULL
  if (iter == m_Components.end())
    return NULL;

  // If there is no tail, then return the component
  if (tail.empty())
    return iter->second;

  // The tail is not empty, so search the component for a child
  return iter->second->FindComponent(tail);
}


// -- EOF



