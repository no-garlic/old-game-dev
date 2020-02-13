
#include "UIConfig.h"
#include "UI.h"
#include "UIComponents.h"
#include "libRenderExt.h"


// ----------------------------------------------------------------------------
// Create a UI from the given config file
// ----------------------------------------------------------------------------
UI *UIConfig::Create(FileHandle handle)
{
  // Open the config file
  ConfigFile config;
  if (!config.Load(handle.GetAbsoluteFilename()))
  {
    LOG_ERROR << "Failed to open the UI config file: " << handle.GetAbsoluteFilename() << ENDLOG;
    return NULL;
  }

  // Get all sections in the file
  ConfigSectionMap allSections = config.GetSections();
  if (allSections.size() != 1)
  {
    LOG_ERROR << "The UI file must contain 1 UI section: " << handle.GetAbsoluteFilename() << ENDLOG;
    return false;
  }

  // Find the UI section
  ConfigSection uiSection = allSections.begin()->second;
  if (!uiSection.IsValid())
  {
    LOG_ERROR << "Failed to find the UI section in the UI config file: " << handle.GetAbsoluteFilename() << ENDLOG;
    return NULL;
  }

  // Get the width and height of the UI
  float width  = uiSection("Width");
  float height = uiSection("Height");

  // Create the new UI
  UI *pUI = new UI(width, height);

  // Process all fonts
  ConfigSectionMap &uiChildSections = uiSection.ChildSections;
  ConfigSectionMap::iterator iter(uiChildSections.begin()), end(uiChildSections.end());
  for (; iter != end; ++iter)
  {
    if (!ProcessFontSection(pUI, iter->second))
    {
      delete pUI;
      return NULL;
    }
  }

  // Process all layers
  iter = uiChildSections.begin();
  for (; iter != end; ++iter)
  {
    if (!ProcessLayerSection(pUI, iter->second))
    {
      delete pUI;
      return NULL;
    }
  }

  return pUI;
}


// ----------------------------------------------------------------------------
// Parse the config file and read the font section
// ----------------------------------------------------------------------------
bool UIConfig::ProcessFontSection(UI *pUI, const ConfigSection &section)
{
  if (StrICmp(section.Type, "Font"))
  {
    String textureName = section("Texture");
    String metricsName = section("Metrics");

    if (pUI->AddFont(section.Name, textureName, metricsName) == InvalidFont)
    {
      LOG_ERROR << "Failed to add the UI font: " << section.Name << ENDLOG;
      return false;
    }

    LOG_INFO << "Created the font: " << section.Name << ENDLOG;
    return true;
  }

  return true;
}


// ----------------------------------------------------------------------------
// Parse the config file and read the layer section
// ----------------------------------------------------------------------------
bool UIConfig::ProcessLayerSection(UI *pUI, const ConfigSection &section)
{
  if (StrICmp(section.Type, "Layer"))
  {
    String filename = section("File");

    FileHandle handle = Application.GetUIDatabase()->FindFileHandle(filename);
    if (!handle.Exists())
      return false;

    uint depth    = section("Depth");
    bool visible  = section("Visible");

    return LoadLayer(pUI, depth, visible, section.Name, handle);
  }

  return true;
}


// ----------------------------------------------------------------------------
// Load the layer from the config file specified
// ----------------------------------------------------------------------------
bool UIConfig::LoadLayer(UI *pUI, uint depth, bool visible, const String &name, FileHandle handle)
{
  // Open the config file
  ConfigFile config;
  if (!config.Load(handle.GetAbsoluteFilename()))
  {
    LOG_ERROR << "Failed to open the UI config file: " << handle.GetAbsoluteFilename() << ENDLOG;
    return NULL;
  }

  // Create the layer
  UILayer *pLayer = pUI->AddLayer(depth, name);
  if (!pLayer)
  {
    LOG_ERROR << "Failed to create the UI Layer: " << name << ENDLOG;
    return false;
  }

  // Set the visibility
  pLayer->SetVisible(visible);

  // Process all child sections
  ConfigSectionMap &componentSections = config.GetSections();
  ConfigSectionMap::iterator iter(componentSections.begin()), end(componentSections.end());
  for (; iter != end; ++iter)
  {
    const ConfigSection &section = iter->second;

    if (!AddComponent(pUI, pLayer, section))
      return false;
  }

  return true;
}


// ----------------------------------------------------------------------------
// Add a component to the UI
// ----------------------------------------------------------------------------
bool UIConfig::AddComponent(UI *pUI, UIObject *pObject, const ConfigSection &section)
{
  UIComponent *pComponent = NULL;

  // Determine the component type
  if (StrICmp(section.Type, "Image"))
  {
    pComponent = AddImage(pUI, pObject, section);
  }
  else if (StrICmp(section.Type, "Group"))
  {
    pComponent = AddGroup(pUI, pObject, section);
  }
  else if (StrICmp(section.Type, "Text"))
  {
    pComponent = AddText(pUI, pObject, section);
  }
  else
  {
    LOG_ERROR << "Unknown UI component type found: " << section.Type << ENDLOG;
    return false;
  }

  // Check that the component was created
  if (!pComponent)
  {
    LOG_ERROR << "Failed to create the UI component: " << section.Name << ENDLOG;
    return false;
  }

  // Process all child components
  const ConfigSectionMap &componentSections = section.ChildSections;
  ConfigSectionMap::const_iterator iter(componentSections.begin()), end(componentSections.end());
  for (; iter != end; ++iter)
  {
    const ConfigSection &section = iter->second;

    // Add the child component
    if (!AddComponent(pUI, pComponent, section))
      return false;
  }

  return true;
}


// ----------------------------------------------------------------------------
// Add an image to the UI
// ----------------------------------------------------------------------------
UIComponent *UIConfig::AddImage(UI *pUI, UIObject *pObject, const ConfigSection &section)
{
  // Get the properties from the config
  float   xPos    = section("XPos");
  float   yPos    = section("YPos");
  float   width   = section("Width");
  float   height  = section("Height");
  String  texture = section("Texture");
  uint    texX1   = section("TexX1");
  uint    texX2   = section("TexX2");
  uint    texY1   = section("TexY1");
  uint    texY2   = section("TexY2");
  bool    visible = section("Visible");

  // Load the texture
  Texture *pTexture = TextureLoader::LoadTexture(Application.GetTextureDatabase()->FindFileHandle(texture));
  if (!pTexture)
  {
    LOG_ERROR << "Failed to load the texture: " << texture << ENDLOG;
    return NULL;
  } // if

  // Create the component
  UIImage *pComponent = new UIImage(section.Name);
  pObject->AddComponent(pComponent);

  // Set the imate properties
  pComponent->SetSize(width, height);
  pComponent->SetPosition(xPos, yPos);
  pComponent->SetTexture(pTexture, Rect(texX1, texY1, texX2, texY2));
  pComponent->SetVisible(visible);

  // Return the component
  LOG_INFO << "Created the image: " << section.Name << ENDLOG;
  return pComponent;
}


// ----------------------------------------------------------------------------
// Add a text label to the UI
// ----------------------------------------------------------------------------
UIComponent *UIConfig::AddText(UI *pUI, UIObject *pObject, const ConfigSection &section)
{
  // Get the properties from the config
  float   xPos    = section("XPos");
  float   yPos    = section("YPos");
  float   height  = section("Height");
  String  font    = section("Font");
  String  text    = section("Text");
  String  color   = section("Color");
  bool    visible = section("Visible");

  // Find the font
  UIFontID id = pUI->FindFont(font);
  if (id == InvalidFont)
  {
    LOG_ERROR << "Failed to find the font: " << font << ENDLOG;
    return false;
  }

  UIText *pComponent = new UIText(section.Name);
  pObject->AddComponent(pComponent);

  pComponent->SetPosition(xPos, yPos);
  pComponent->SetText(text);
  pComponent->SetFont(id);
  pComponent->SetHeight(height);
  pComponent->SetVisible(visible);

  if (!color.empty())
    pComponent->SetColor(Color(color));

  // Return the component
  LOG_INFO << "Created the text: " << section.Name << ENDLOG;
  return pComponent;
}


// ----------------------------------------------------------------------------
// Add a group to the UI
// ----------------------------------------------------------------------------
UIComponent *UIConfig::AddGroup(UI *pUI, UIObject *pObject, const ConfigSection &section)
{
  // Get the properties from the config
  float   xPos    = section("XPos");
  float   yPos    = section("YPos");
  bool    visible = section("Visible");

  UIGroup *pComponent = new UIGroup(section.Name);
  pObject->AddComponent(pComponent);

  pComponent->SetPosition(xPos, yPos);
  pComponent->SetVisible(visible);

  // Return the component
  LOG_INFO << "Created the group: " << section.Name << ENDLOG;
  return pComponent;
}


// -- EOF

