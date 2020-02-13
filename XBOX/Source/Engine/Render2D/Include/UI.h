// ----------------------------------------------------------------------------
// File: UI.h
// Desc: User interface
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __USER_INTERFACE_H_
#define __USER_INTERFACE_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "libStandard.h"
#include "libRenderCore.h"
#include "libRenderExt.h"
#include "libMaths.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class UILayer;
class UIComponent;
class UIFont;


// ----------------------------------------------------------------------------
// Typedefs
// ----------------------------------------------------------------------------
typedef Map<UINT, UILayer *> UILayerArray;
typedef Map<String, UIComponent *> UIComponentArray;


// ----------------------------------------------------------------------------
// Font identifier
// ----------------------------------------------------------------------------
typedef UINT UIFontID;
static const UIFontID InvalidFont = (UIFontID) -1;


// ----------------------------------------------------------------------------
// Font format flags
// ----------------------------------------------------------------------------
#define FMT_LEFT    0x0000  // The text is left of pos
#define FMT_RIGHT   0x0001  // The text is right of pos
#define FMT_TOP     0x0002  // The text is below pos
#define FMT_BOTTOM  0x0000  // The text is above pos
#define FMT_VCENTER 0x0004  // The text is vertically centered on pos
#define FMT_HCENTER 0x0008  // The text is horizontally centered on pos


// ----------------------------------------------------------------------------
// Component types
// ----------------------------------------------------------------------------
enum UIComponentType
{
  UI_Text       = 1,
  UI_Image      = 2,
  UI_Group      = 3
};


// ----------------------------------------------------------------------------
// Manage all user interface layers
// ----------------------------------------------------------------------------
class UI : public DeviceObject
{
public:
  // --------------------------------------------------------------------------
  // Constructor and desructor
  // --------------------------------------------------------------------------
  UI(float width, float height);
  virtual ~UI();

  // --------------------------------------------------------------------------
  // Get the user interface size
  // --------------------------------------------------------------------------
  virtual void GetSize(float &width, float &height);

  // --------------------------------------------------------------------------
  // Get the layer for the given name
  // --------------------------------------------------------------------------
  UILayer *GetLayer(const String &name);

  // --------------------------------------------------------------------------
  // Add a layer to the user interface
  // --------------------------------------------------------------------------
  UILayer *AddLayer(UINT depth, const String &name);

  // --------------------------------------------------------------------------
  // Add a font to the user interface
  // --------------------------------------------------------------------------
  UIFontID AddFont(const String &name, const String &textureFile, 
    const String &metricsFile);

  // --------------------------------------------------------------------------
  // Find a font by ID
  // --------------------------------------------------------------------------
  UIFontID FindFont(const String &name);

  // --------------------------------------------------------------------------
  // Draw text
  // --------------------------------------------------------------------------
  void DrawText(UIFontID fontId, const String &text, float x, float y, float h,
    const Color &color, uint format = 0);

  // --------------------------------------------------------------------------
  // Find a component
  // --------------------------------------------------------------------------
  UIComponent *FindComponent(UIComponentType type, const String &pathname);

  // --------------------------------------------------------------------------
  // Find a component (template cast)
  // --------------------------------------------------------------------------
  template <class T> T *FindComponent(const String &pathname)
  {
    return static_cast<T *>(FindComponent(T::Type(), pathname));
  }

  // --------------------------------------------------------------------------
  // Get the sprite
  // --------------------------------------------------------------------------
  LPD3DXSPRITE GetSprite();

  // --------------------------------------------------------------------------
  // Render the UI
  // --------------------------------------------------------------------------
  void Render();

protected:
  // --------------------------------------------------------------------------
  // Protected members
  // --------------------------------------------------------------------------
  virtual bool AllocateDeviceMemory();
  virtual bool ReleaseDeviceMemory();

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  Array<std::pair<String, UIFont *> > m_Fonts;    // The fonts
  LPD3DXSPRITE                        m_Sprite;   // The sprite
  UILayerArray                        m_Layers;   // The array of layers
  float                               m_Width;    // The virtual width
  float                               m_Height;   // The virtaul height

};


// ----------------------------------------------------------------------------
// Definition of a UI object that has components
// ----------------------------------------------------------------------------
class UIObject
{
public:
  // --------------------------------------------------------------------------
  // Add a component to this layer
  // --------------------------------------------------------------------------
  virtual bool AddComponent(UIComponent *pComponent) = 0;
};


// ----------------------------------------------------------------------------
// Manage a single user interface layer
// ----------------------------------------------------------------------------
class UILayer : public UIObject
{
public:
  // --------------------------------------------------------------------------
  // Get the name
  // --------------------------------------------------------------------------
  const String &GetName();

  // --------------------------------------------------------------------------
  // Set the visibility flag of this layer
  // --------------------------------------------------------------------------
  void SetVisible(bool visible);

  // --------------------------------------------------------------------------
  // Add a component to this layer
  // --------------------------------------------------------------------------
  virtual bool AddComponent(UIComponent *pComponent);

  // --------------------------------------------------------------------------
  // Find a component
  // --------------------------------------------------------------------------
  UIComponent *FindComponent(const String &pathname);
  
private:
  // --------------------------------------------------------------------------
  // Allow the UI class to access these functions
  // --------------------------------------------------------------------------
  friend class UI;

  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  UILayer(const String &name);
  ~UILayer();

  // --------------------------------------------------------------------------
  // Render the UI
  // --------------------------------------------------------------------------
  void Render(UI *pUI);

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  UIComponentArray    m_Components;   // The array of components
  String              m_Name;         // The name of the layer
  bool                m_Visible;      // Is this layer visible

};


// ----------------------------------------------------------------------------
// Base component object
// ----------------------------------------------------------------------------
class UIComponent : public UIObject
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  UIComponent(UIComponentType type, const String &name);
  virtual ~UIComponent();

  // --------------------------------------------------------------------------
  // Get the component name
  // --------------------------------------------------------------------------
  const String &GetName();

  // --------------------------------------------------------------------------
  // Get the component type
  // --------------------------------------------------------------------------
  UIComponentType GetType() { return m_Type; }
  bool IsOfType(UIComponentType type) { return m_Type == type; }

  // --------------------------------------------------------------------------
  // Render the component
  // --------------------------------------------------------------------------
  void Render(UI *pUI, int x, int y);

  // --------------------------------------------------------------------------
  // Set the alpha
  // --------------------------------------------------------------------------
  virtual void SetAlpha(float alpha);
  virtual void SetFadeColor(const Color &color);

  // --------------------------------------------------------------------------
  // Set the component size and position
  // --------------------------------------------------------------------------
  virtual void SetSize(float width, float height);
  virtual void SetPosition(float x, float y);

  // --------------------------------------------------------------------------
  // Get the component size and position
  // --------------------------------------------------------------------------
  virtual void GetSize(float &width, float &height);
  virtual void GetPosition(float &x, float &y);

  // --------------------------------------------------------------------------
  // Set the visibility flag of this component
  // --------------------------------------------------------------------------
  virtual void SetVisible(bool visible);
  virtual bool IsVisible();

  // --------------------------------------------------------------------------
  // Add a child component to this component
  // --------------------------------------------------------------------------
  virtual bool AddComponent(UIComponent *pComponent);

  // --------------------------------------------------------------------------
  // Find a child component in this component
  // --------------------------------------------------------------------------
  virtual UIComponent *FindComponent(const String &pathname);

protected:
  // --------------------------------------------------------------------------
  // Internal render funtion
  // --------------------------------------------------------------------------
  virtual void RenderInternal(UI *pUI, int x, int y) = 0;

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  UIComponentArray    m_Components;   // The array of components
  String              m_Name;         // The name of the component
  bool                m_Visible;      // The component visibility
  float               m_Width;        // The component width
  float               m_Height;       // The component height
  float               m_PositionX;    // The X position
  float               m_PositionY;    // The Y position
  float               m_Alpha;        // The alpha value
  Color               m_FadeColor;    // The color we fade to 
  UIComponentType     m_Type;         // The component type

};


#endif // __USER_INTERFACE_H_

// -- EOF



