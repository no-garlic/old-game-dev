// ----------------------------------------------------------------------------
// File: MeshMaterialDialog.cpp
// Desc: Dialog for modifying the material properties of a mesh
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#include "MeshEditor/MeshMaterialDialog.h"
#include "MeshEditor/Resource.h"


// ----------------------------------------------------------------------------
// The Frame Window Message Map
// ----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(MeshMaterialDialog, CDialog)
  ON_CBN_SELCHANGE(IDC_COMBO_SUBSET,        OnSubsetSelect)
  ON_CBN_SELCHANGE(IDC_COMBO_EFFECT,        OnEffectSelect)
  ON_CBN_SELCHANGE(IDC_COMBO_DIFFUSE_TEX,   OnDiffuseTexSelect)
  ON_CBN_SELCHANGE(IDC_COMBO_ALPHA_TEX,     OnAlphaTexSelect)
  ON_CBN_SELCHANGE(IDC_COMBO_NORMAL_TEX,    OnNormalTexSelect)
  ON_CBN_SELCHANGE(IDC_COMBO_TEX0,          OnTex0Select)
  ON_CBN_SELCHANGE(IDC_COMBO_TEX1,          OnTex1Select)
  ON_BN_CLICKED(IDC_BUTTON_COLOR_AMBIENT,   OnColorAmbient)
  ON_BN_CLICKED(IDC_BUTTON_COLOR_DIFFUSE,   OnColorDiffuse)
  ON_BN_CLICKED(IDC_BUTTON_COLOR_SPECULAR,  OnColorSpecular)
  ON_BN_CLICKED(IDC_BUTTON_COLOR_EMISSIVE,  OnColorEmissive)
  ON_WM_CTLCOLOR()
  ON_WM_HSCROLL()
END_MESSAGE_MAP()


// ----------------------------------------------------------------------------
// Return from a function and show an error message
// ----------------------------------------------------------------------------
#define RETURN_ERRMSG(x) \
{ ::MessageBox(NULL, x, "Error", MB_OK | MB_ICONERROR); return; }
#define RETURN_ERRMSG2(x,y) \
{ String str(x); str.append(y); ::MessageBox(NULL, y.c_str(), "Error", MB_OK | MB_ICONERROR); return; }


// ----------------------------------------------------------------------------
// Show an error message
// ----------------------------------------------------------------------------
#define ERRMSG(x) \
{ ::MessageBox(NULL, x, "Error", MB_OK | MB_ICONERROR); }
#define ERRMSG2(x,y) \
{ String str(x); str.append(y); ::MessageBox(NULL, y.c_str(), "Error", MB_OK | MB_ICONERROR); }


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::MeshMaterialDialog
// Desc: Constructor
// Parm: CWnd *pParentWnd - the parent window
// ----------------------------------------------------------------------------
MeshMaterialDialog::MeshMaterialDialog()
: CDialog             (IDD_MATERIAL_EDITOR, AfxGetMainWnd()),
  m_DiffuseColor      (RGB(0, 0, 0)),
  m_AmbientColor      (RGB(0, 0, 0)),
  m_SpecularColor     (RGB(0, 0, 0)),
  m_EmissiveColor     (RGB(0, 0, 0)),
  m_PowerColor        (RGB(0, 0, 0))
{
  m_pDiffuseBrush  = new CBrush(m_DiffuseColor);
  m_pAmbientBrush  = new CBrush(m_AmbientColor);
  m_pSpecularBrush = new CBrush(m_SpecularColor);
  m_pEmissiveBrush = new CBrush(m_EmissiveColor);
  m_pPowerBrush    = new CBrush(m_PowerColor);
} // MeshMaterialDialog


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::~MeshMaterialDialog
// Desc: Destructor
// ----------------------------------------------------------------------------
MeshMaterialDialog::~MeshMaterialDialog()
{
  Release();

  delete m_pDiffuseBrush;
  delete m_pAmbientBrush;
  delete m_pSpecularBrush;
  delete m_pEmissiveBrush;
  delete m_pPowerBrush;
} // ~MeshMaterialDialog


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::OnInitDialog
// Desc: Called at dialog initialisation
// Retn: BOOL - true if the dialog is valid
// ----------------------------------------------------------------------------
BOOL MeshMaterialDialog::OnInitDialog()
{
  if (CDialog::OnInitDialog() == FALSE)
    return FALSE;

  // Load all lookup data into the combo's
  PreLoadData();

  return TRUE;
} // OnInitDialog


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::Init
// Desc: Initialise the dialog
// Parm: Mesh *pMesh - the mesh
// ----------------------------------------------------------------------------
void MeshMaterialDialog::Init(Mesh *pMesh)
{
  Release();

  // Set the range of the slider
  m_PowerSlider.SetRange(0, 255, true);

  if (pMesh)
  {
    // Add the null item
    int nullId = m_SubsetCombo.AddString("");
    m_SubsetCombo.SetItemDataPtr(nullId, NULL);
    m_SubsetCombo.SetCurSel(nullId);

    // Add all subsets to the combo box
    for (uint i = 0; i < pMesh->GetNumSubsets(); i++)
    {
      // Get the subset
      MeshSubset *pSubset = pMesh->GetSubset(i);

      // Make the subset name
      String name = "Subset ";
      AppendInt(name, (int) i);
      name += " [Start: ";
      AppendInt(name, (int) pSubset->GetFaceStart());
      name += " Count: ";
      AppendInt(name, (int) pSubset->GetFaceCount());
      name += "]";

      //  Add the subset to the combo box
      int index = m_SubsetCombo.AddString(name.c_str());
      m_SubsetCombo.SetItemDataPtr(index, pSubset);
    } // for
  } // if

  // Get the rect of the dialog and the parent window
  RECT parentRect, rect;
  ::GetWindowRect(ApplicationCentral.GetHWND(), &parentRect);
  this->GetWindowRect(&rect);

  // Create a new rect at the top right of the parent window
  const int borderOffset = 2;
  int width   = rect.right - rect.left;
  int height  = rect.bottom - rect.top;
  rect.top    = parentRect.top + borderOffset;
  rect.bottom = rect.top + height;
  rect.right  = parentRect.right - borderOffset;
  rect.left   = rect.right - width;

  // Move the dialog window
  MoveWindow(&rect);

  // Select the first subset
  if (m_SubsetCombo.GetCount() > 1)
    m_SubsetCombo.SetCurSel(1);

  // Update all subset items
  OnSubsetSelect();
} // Init


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::Release
// Desc: Release the allocated data
// ----------------------------------------------------------------------------
void MeshMaterialDialog::Release()
{
  if (GetSafeHwnd())
  {
    Clear(true);
    SetEnabled(false);
  } // if
} // Release


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::DoDataExchange
// Desc: Data Exchange
// Parm: CDataExchange *pDX - the data exchange context
// ----------------------------------------------------------------------------
void MeshMaterialDialog::DoDataExchange(CDataExchange *pDX)
{
  CDialog::DoDataExchange(pDX);

  DDX_Control(pDX, IDC_COMBO_SUBSET,      m_SubsetCombo);
  DDX_Control(pDX, IDC_COMBO_EFFECT,      m_EffectCombo);
  DDX_Control(pDX, IDC_COMBO_DIFFUSE_TEX, m_DiffuseTexCombo);
  DDX_Control(pDX, IDC_COMBO_ALPHA_TEX,   m_AlphaTexCombo);
  DDX_Control(pDX, IDC_COMBO_NORMAL_TEX,  m_NormalTexCombo);
  DDX_Control(pDX, IDC_COMBO_TEX0,        m_Tex0Combo);
  DDX_Control(pDX, IDC_COMBO_TEX1,        m_Tex1Combo);
  DDX_Control(pDX, IDC_SLIDER_POWER,      m_PowerSlider);
  DDX_Control(pDX, IDC_DIFFUSE_COLOR,     m_DiffuseStatic);
  DDX_Control(pDX, IDC_AMBIENT_COLOR,     m_AmbientStatic);
  DDX_Control(pDX, IDC_SPECULAR_COLOR,    m_SpecularStatic);
  DDX_Control(pDX, IDC_EMISSIVE_COLOR,    m_EmissiveStatic);
  DDX_Control(pDX, IDC_POWER_COLOR,       m_PowerStatic);
} // DoDataExchange


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::OnCtlColor
// Desc: Callback for setting the control color
// Parm: CDC *pDC        - the device context
// Parm: CWnd *pWnd      - the window
// Parm: UINT nCtlColor  - the control color
// Retn: HBRUSH          - teh brush to craw with
// ----------------------------------------------------------------------------
HBRUSH MeshMaterialDialog::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
  // If this is the static control
  switch (pWnd->GetDlgCtrlID())
  {
    case IDC_AMBIENT_COLOR:  return (HBRUSH) m_pAmbientBrush->GetSafeHandle();
    case IDC_DIFFUSE_COLOR:  return (HBRUSH) m_pDiffuseBrush->GetSafeHandle();
    case IDC_SPECULAR_COLOR: return (HBRUSH) m_pSpecularBrush->GetSafeHandle();
    case IDC_EMISSIVE_COLOR: return (HBRUSH) m_pEmissiveBrush->GetSafeHandle();
    case IDC_POWER_COLOR:    return (HBRUSH) m_pPowerBrush->GetSafeHandle();
  }

  // Call the parent function
  return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
} // OnCtlColor


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::PreLoadData
// Desc: Pre load all combo data
// ----------------------------------------------------------------------------
void MeshMaterialDialog::PreLoadData()
{
  FileDatabase *pMaterialDB = FileSystem("Material");
  if (pMaterialDB)
  {
    // Get all effect files
    FileHandleArray allEffects(pMaterialDB->ListFiles("*.fx"));

    // Add an empty string
    m_EffectCombo.AddString("");

    // Add all effect files
    FileHandleArray::iterator iter(allEffects.begin()), end(allEffects.end());
    for ( ;iter != end; ++iter)
    {
      FileHandle &handle = *iter;
      m_EffectCombo.AddString(handle.GetFilename().c_str());
    } // for
  } // if

  FileDatabase *pTextureDB = FileSystem("Texture");
  if (pTextureDB)
  {
    // Find all textures
    StringArray textureTypes;
    textureTypes.push_back("*.bmp");
    textureTypes.push_back("*.jpg");
    textureTypes.push_back("*.dds");
    FileHandleArray allTextures(pTextureDB->ListFiles(textureTypes));

    // Add an empty string
    m_DiffuseTexCombo.AddString("");
    m_AlphaTexCombo.AddString("");
    m_NormalTexCombo.AddString("");
    m_Tex0Combo.AddString("");
    m_Tex1Combo.AddString("");

    // Add all textures to the combos
    FileHandleArray::iterator iter(allTextures.begin()), end(allTextures.end());
    for ( ;iter != end; ++iter)
    {
      FileHandle &handle = *iter;

      m_DiffuseTexCombo.AddString(handle.GetFilename().c_str());
      m_AlphaTexCombo.AddString(handle.GetFilename().c_str());
      m_NormalTexCombo.AddString(handle.GetFilename().c_str());
      m_Tex0Combo.AddString(handle.GetFilename().c_str());
      m_Tex1Combo.AddString(handle.GetFilename().c_str());
    } // for
  } // if
} // PreLoadData


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::SelectComboItem
// Desc: Select the item in the combo box that matches the given string
// Parm: CComboBox *pCombo   - the combo box
// Parm: const String &item  - the string
// Retn: int                 - the selected item index, or CB_ERR if not found
// ----------------------------------------------------------------------------
int MeshMaterialDialog::SelectComboItem(CComboBox *pCombo, const String &item)
{
  // Get the number of items in the combo
  int count = pCombo->GetCount();

  // If the combo is empty, return CB_ERR
  if (count == 0)
  {
    pCombo->SetCurSel(-1);
    return CB_ERR;
  } // if

  // Search for the string in the combo item list
  for (int i = 0; i < count; i++)
  {
    // Get the item string
    CString str;
    pCombo->GetLBText(i, str);

    // Compare the strings
    if (String(str) == item)
    {
      // Select the item
      pCombo->SetCurSel(i);
      return i;
    } // if
  } // for

  // Select the 0th item (blank)
  pCombo->SetCurSel(0);
  return 0;
} // SelectComboItem


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::GetSelectedItem
// Desc: Get the  selected combo box text
// Parm: CComboBox *pCombo - the combo box
// Retn: String            - the text
// ----------------------------------------------------------------------------
String MeshMaterialDialog::GetSelectedItem(CComboBox *pCombo)
{
  // Get the selected index
  int selected = pCombo->GetCurSel();
  if (selected == -1)
    return "";

  // Get the combo text
  CString str;
  pCombo->GetLBText(selected, str);

  // Return the text
  return String(str);
} // GetSelectedItem


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::OnSubsetSelect
// Desc: Callback for selecting a mesh subset
// ----------------------------------------------------------------------------
void MeshMaterialDialog::OnSubsetSelect()
{
  // Check we have some subsets
  if (m_SubsetCombo.GetCount() == 0)
  {
    Clear();
    SetEnabled(false);
    return;
  } // if

  // Get the selected index
  int selected = m_SubsetCombo.GetCurSel();
  if (selected == CB_ERR)
  {
    Clear();
    SetEnabled(false);
    return;
  } // if

  // Get the selected mesh subset
  MeshSubset *pSubset = (MeshSubset *) m_SubsetCombo.GetItemDataPtr(selected);
  if (!pSubset)
  {
    Clear();
    SetEnabled(false);
    return;
  } // if

  // Enable the controls
  SetEnabled(true);

  // Select the effect
  Material *pMaterial = pSubset->GetMaterial();
  if (pMaterial)
    SelectComboItem(&m_EffectCombo, pMaterial->GetFileHandle().GetFilename());

  // Get the texture array
  const TextureArray &textureArray = pSubset->GetTextureArray();

  // Select the diffuse texture
  if (textureArray.GetDiffuse())
    SelectComboItem(&m_DiffuseTexCombo, textureArray.GetDiffuse()->GetFileHandle().GetFilename());
  else
    SelectComboItem(&m_DiffuseTexCombo, "");

  // Select the alpha texture
  if (textureArray.GetAlpha())
    SelectComboItem(&m_AlphaTexCombo, textureArray.GetAlpha()->GetFileHandle().GetFilename());
  else
    SelectComboItem(&m_AlphaTexCombo, "");

  // Select the normal texture
  if (textureArray.GetNormal())
    SelectComboItem(&m_NormalTexCombo, textureArray.GetNormal()->GetFileHandle().GetFilename());
  else
    SelectComboItem(&m_NormalTexCombo, "");

  // Select the tex0
  if (textureArray.GetTex0())
    SelectComboItem(&m_Tex0Combo, textureArray.GetTex0()->GetFileHandle().GetFilename());
  else
    SelectComboItem(&m_Tex0Combo, "");

  // Select the tex1
  if (textureArray.GetTex1())
    SelectComboItem(&m_Tex1Combo, textureArray.GetTex1()->GetFileHandle().GetFilename());
  else
    SelectComboItem(&m_Tex1Combo, "");

  // Set the diffuse color
  m_DiffuseColor = MakeColorRef(pSubset->GetColorMaterial().Diffuse);
  SetBrushColor(&m_pDiffuseBrush, m_DiffuseColor);

  // Set the ambient color
  m_AmbientColor = MakeColorRef(pSubset->GetColorMaterial().Ambient);
  SetBrushColor(&m_pAmbientBrush, m_AmbientColor);

  // Set the specular color
  m_SpecularColor = MakeColorRef(pSubset->GetColorMaterial().Specular);
  SetBrushColor(&m_pSpecularBrush, m_SpecularColor);

  // Set the emissive color
  m_EmissiveColor = MakeColorRef(pSubset->GetColorMaterial().Emissive);
  SetBrushColor(&m_pEmissiveBrush, m_EmissiveColor);

  // Set the power color
  m_PowerColor = MakeColorRef(pSubset->GetColorMaterial().Power);
  SetBrushColor(&m_pPowerBrush, m_PowerColor);

  // Set the slider value
  int sliderValue = static_cast<int>(pSubset->GetColorMaterial().Power);
  Clamp(sliderValue, 0, 255);
  m_PowerSlider.SetPos(sliderValue);

  // Repaint the window
  Invalidate();
} // OnSubsetSelect


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::Clear
// Desc: Clear all GUI controls
// ----------------------------------------------------------------------------
void MeshMaterialDialog::Clear(bool clearSubsets)
{
  if (clearSubsets)
  {
    // Clear the combo textbox
    m_SubsetCombo.SetEditSel(0, -1);
    m_SubsetCombo.Clear();

    // Clear the combo list
    while (m_SubsetCombo.GetCount() != 0)
      m_SubsetCombo.DeleteString(0);
  } // if

  // Select the unselected item
  SelectComboItem(&m_EffectCombo, "");
  SelectComboItem(&m_DiffuseTexCombo, "");
  SelectComboItem(&m_AlphaTexCombo, "");
  SelectComboItem(&m_NormalTexCombo, "");
  SelectComboItem(&m_Tex0Combo, "");
  SelectComboItem(&m_Tex1Combo, "");

  // Reset the colors
  m_DiffuseColor = RGB(0, 0, 0);
  SetBrushColor(&m_pDiffuseBrush, m_DiffuseColor);
  m_AmbientColor = RGB(0, 0, 0);
  SetBrushColor(&m_pAmbientBrush, m_AmbientColor);
  m_SpecularColor = RGB(0, 0, 0);
  SetBrushColor(&m_pSpecularBrush, m_SpecularColor);
  m_EmissiveColor = RGB(0, 0, 0);
  SetBrushColor(&m_pEmissiveBrush, m_EmissiveColor);
  m_PowerColor = RGB(0, 0, 0);
  SetBrushColor(&m_pPowerBrush, m_PowerColor);
  
  // Reset the slider
  m_PowerSlider.SetPos(0);

  // Repaint the window
  Invalidate();
} // Clear


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::SetEnabled
// Desc: Enable or disable all GUI controls
// Parm: bool enable - enable or disable
// ----------------------------------------------------------------------------
void MeshMaterialDialog::SetEnabled(bool enable)
{
  m_EffectCombo.EnableWindow(enable ? TRUE : FALSE);
  m_DiffuseTexCombo.EnableWindow(enable ? TRUE : FALSE);
  m_AlphaTexCombo.EnableWindow(enable ? TRUE : FALSE);
  m_NormalTexCombo.EnableWindow(enable ? TRUE : FALSE);
  m_Tex0Combo.EnableWindow(enable ? TRUE : FALSE);
  m_Tex1Combo.EnableWindow(enable ? TRUE : FALSE);
  m_PowerSlider.EnableWindow(enable ? TRUE : FALSE);
} // SetEnabled


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::OnEffectSelect
// Desc: Callback for selecting an effect
// ----------------------------------------------------------------------------
void MeshMaterialDialog::OnEffectSelect()
{
  // Check we have some subsets
  if (m_SubsetCombo.GetCount() == 0)
    RETURN_ERRMSG("No subset selected");

  // Get the selected index
  int selected = m_SubsetCombo.GetCurSel();
  if (selected == CB_ERR)
    RETURN_ERRMSG("No subset selected");

  // Get the selected mesh subset
  MeshSubset *pSubset = (MeshSubset *) m_SubsetCombo.GetItemDataPtr(selected);
  if (!pSubset)
    RETURN_ERRMSG("No subset selected");

  // Get the effect name to load
  String effectName = GetSelectedItem(&m_EffectCombo);
  if (effectName.empty())
    RETURN_ERRMSG("No effect selected");

  // Get the effect file handle
  FileDatabase *pMaterialDB = FileSystem("Material");
  if (!pMaterialDB)
    RETURN_ERRMSG("Failed to find the material database");
  FileHandle handle = pMaterialDB->MakeFileHandle(effectName);

  // Load the effect
  Material *pNewMaterial = MaterialLoader::LoadEffect(handle);
  if (!pNewMaterial)
    RETURN_ERRMSG2("Failed to load the material: ", effectName);

  // Set the new material
  pSubset->SetMaterial(pNewMaterial);
} // OnEffectSelect


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::OnTextureSelect
// Desc: Callback when a texture has been selected
// Parm: uint id - the control id that caused this event
// ----------------------------------------------------------------------------
void MeshMaterialDialog::OnTextureSelect(uint id)
{
  // Check we have some subsets
  if (m_SubsetCombo.GetCount() == 0)
    RETURN_ERRMSG("No subset selected");

  // Get the selected index
  int selected = m_SubsetCombo.GetCurSel();
  if (selected == CB_ERR)
    RETURN_ERRMSG("No subset selected");

  // Get the selected mesh subset
  MeshSubset *pSubset = (MeshSubset *) m_SubsetCombo.GetItemDataPtr(selected);
  if (!pSubset)
    RETURN_ERRMSG("No subset selected");

  // Get the texture array
  TextureArray &textureArray = pSubset->GetTextureArray();

  // Get the combo box
  CComboBox *pCombo = NULL;
  switch (id)
  {
    case IDC_COMBO_DIFFUSE_TEX: pCombo = &m_DiffuseTexCombo;  break;
    case IDC_COMBO_ALPHA_TEX:   pCombo = &m_AlphaTexCombo;    break;
    case IDC_COMBO_NORMAL_TEX:  pCombo = &m_NormalTexCombo;   break;
    case IDC_COMBO_TEX0:        pCombo = &m_Tex0Combo;        break;
    case IDC_COMBO_TEX1:        pCombo = &m_Tex1Combo;        break;
  }
  ASSERT(pCombo, "Invalid texture control ID specified");

  // Get the texture name to load
  String textureName   = GetSelectedItem(pCombo);
  Texture *pNewTexture = NULL;
  if (!textureName.empty())
  {
    // Get the effect file handle
    FileDatabase *pTextureDB = FileSystem("Texture");
    if (!pTextureDB)
      RETURN_ERRMSG("Failed to find the texture database");
    FileHandle handle = pTextureDB->MakeFileHandle(textureName);

    // Load the texture
    pNewTexture = TextureLoader::LoadTexture(handle);
    if (!pNewTexture)
      RETURN_ERRMSG2("Failed to load the texture: ", textureName);
  } // if

  // Set the texture
  switch (id)
  {
    case IDC_COMBO_DIFFUSE_TEX: textureArray.SetDiffuse(pNewTexture);  break;
    case IDC_COMBO_ALPHA_TEX:   textureArray.SetAlpha(pNewTexture);    break;
    case IDC_COMBO_NORMAL_TEX:  textureArray.SetNormal(pNewTexture);   break;
    case IDC_COMBO_TEX0:        textureArray.SetTex0(pNewTexture);     break;
    case IDC_COMBO_TEX1:        textureArray.SetTex1(pNewTexture);     break;
  }
} // OnTextureSelect


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::OnDiffuseTexSelect
// Desc: Callback for selecting a texture
// ----------------------------------------------------------------------------
void MeshMaterialDialog::OnDiffuseTexSelect()
{
  OnTextureSelect(IDC_COMBO_DIFFUSE_TEX);
} // OnDiffuseTexSelect


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::OnAlphaTexSelect
// Desc: Callback for selecting a texture
// ----------------------------------------------------------------------------
void MeshMaterialDialog::OnAlphaTexSelect()
{
  OnTextureSelect(IDC_COMBO_ALPHA_TEX);
} // OnAlphaTexSelect


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::OnNormalTexSelect
// Desc: Callback for selecting a texture
// ----------------------------------------------------------------------------
void MeshMaterialDialog::OnNormalTexSelect()
{
  OnTextureSelect(IDC_COMBO_NORMAL_TEX);
} // OnNormalTexSelect


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::OnTex0Select
// Desc: Callback for selecting a texture
// ----------------------------------------------------------------------------
void MeshMaterialDialog::OnTex0Select()
{
  OnTextureSelect(IDC_COMBO_TEX0);
} // OnTex0Select


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::OnTex1Select
// Desc: Callback for selecting a texture
// ----------------------------------------------------------------------------
void MeshMaterialDialog::OnTex1Select()
{
  OnTextureSelect(IDC_COMBO_TEX1);
} // OnTex1Select


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::OnColorDiffuse
// Desc: Callback for selecting a color button
// ----------------------------------------------------------------------------
void MeshMaterialDialog::OnColorDiffuse()
{
  CColorDialog dlg(m_DiffuseColor, CC_FULLOPEN, this);
  if (dlg.DoModal() == IDOK)
  {
    // Update the dialog
    m_DiffuseColor = dlg.GetColor();
    SetBrushColor(&m_pDiffuseBrush, m_DiffuseColor);
    m_DiffuseStatic.Invalidate();

    // Check we have some subsets
    if (m_SubsetCombo.GetCount() == 0)
      RETURN_ERRMSG("No subset selected");

    // Get the selected index
    int selected = m_SubsetCombo.GetCurSel();
    if (selected == CB_ERR)
      RETURN_ERRMSG("No subset selected");

    // Get the selected mesh subset
    MeshSubset *pSubset = (MeshSubset *) m_SubsetCombo.GetItemDataPtr(selected);
    if (!pSubset)
      RETURN_ERRMSG("No subset selected");

    // Set the material color
    pSubset->GetColorMaterial().Diffuse = MakeColorValue(m_DiffuseColor);
  } // if
} // OnColorDiffuse


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::OnColorAmbient
// Desc: Callback for selecting a color button
// ----------------------------------------------------------------------------
void MeshMaterialDialog::OnColorAmbient()
{
  CColorDialog dlg(m_AmbientColor, CC_FULLOPEN, this);
  if (dlg.DoModal() == IDOK)
  {
    m_AmbientColor = dlg.GetColor();
    SetBrushColor(&m_pAmbientBrush, m_AmbientColor);
    m_AmbientStatic.Invalidate();

    // Check we have some subsets
    if (m_SubsetCombo.GetCount() == 0)
      RETURN_ERRMSG("No subset selected");

    // Get the selected index
    int selected = m_SubsetCombo.GetCurSel();
    if (selected == CB_ERR)
      RETURN_ERRMSG("No subset selected");

    // Get the selected mesh subset
    MeshSubset *pSubset = (MeshSubset *) m_SubsetCombo.GetItemDataPtr(selected);
    if (!pSubset)
      RETURN_ERRMSG("No subset selected");

    // Set the material color
    pSubset->GetColorMaterial().Ambient = MakeColorValue(m_AmbientColor);
  } // if
} // OnColorAmbient


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::OnColorEmissive
// Desc: Callback for selecting a color button
// ----------------------------------------------------------------------------
void MeshMaterialDialog::OnColorEmissive()
{
  CColorDialog dlg(m_EmissiveColor, CC_FULLOPEN, this);
  if (dlg.DoModal() == IDOK)
  {
    m_EmissiveColor = dlg.GetColor();
    SetBrushColor(&m_pEmissiveBrush, m_EmissiveColor);
    m_EmissiveStatic.Invalidate();

    // Check we have some subsets
    if (m_SubsetCombo.GetCount() == 0)
      RETURN_ERRMSG("No subset selected");

    // Get the selected index
    int selected = m_SubsetCombo.GetCurSel();
    if (selected == CB_ERR)
      RETURN_ERRMSG("No subset selected");

    // Get the selected mesh subset
    MeshSubset *pSubset = (MeshSubset *) m_SubsetCombo.GetItemDataPtr(selected);
    if (!pSubset)
      RETURN_ERRMSG("No subset selected");

    // Set the material color
    pSubset->GetColorMaterial().Emissive = MakeColorValue(m_EmissiveColor);
  } // if
} // OnColorEmissive


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::OnColorSpecular
// Desc: Callback for selecting a color button
// ----------------------------------------------------------------------------
void MeshMaterialDialog::OnColorSpecular()
{
  CColorDialog dlg(m_SpecularColor, CC_FULLOPEN, this);
  if (dlg.DoModal() == IDOK)
  {
    m_SpecularColor = dlg.GetColor();
    SetBrushColor(&m_pSpecularBrush, m_SpecularColor);
    m_SpecularStatic.Invalidate();

    // Check we have some subsets
    if (m_SubsetCombo.GetCount() == 0)
      RETURN_ERRMSG("No subset selected");

    // Get the selected index
    int selected = m_SubsetCombo.GetCurSel();
    if (selected == CB_ERR)
      RETURN_ERRMSG("No subset selected");

    // Get the selected mesh subset
    MeshSubset *pSubset = (MeshSubset *) m_SubsetCombo.GetItemDataPtr(selected);
    if (!pSubset)
      RETURN_ERRMSG("No subset selected");

    // Set the material color
    pSubset->GetColorMaterial().Specular = MakeColorValue(m_SpecularColor);
  } // if
} // OnColorSpecular


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::OnPowerChange
// Desc: Callback for when the power slider changes
// ----------------------------------------------------------------------------
void MeshMaterialDialog::OnPowerChange()
{
  // Check we have some subsets
  if (m_SubsetCombo.GetCount() == 0)
    RETURN_ERRMSG("No subset selected");

  // Get the selected index
  int selected = m_SubsetCombo.GetCurSel();
  if (selected == CB_ERR)
    RETURN_ERRMSG("No subset selected");

  // Get the selected mesh subset
  MeshSubset *pSubset = (MeshSubset *) m_SubsetCombo.GetItemDataPtr(selected);
  if (!pSubset)
    RETURN_ERRMSG("No subset selected");

  // Get the slider value
  int sliderValue = m_PowerSlider.GetPos();
  Clamp<int>(sliderValue, 0, 255);

  // Set the material power
  pSubset->GetColorMaterial().Power = static_cast<float>(sliderValue);

  // Set the power color
  m_PowerColor = MakeColorRef(pSubset->GetColorMaterial().Power);
  SetBrushColor(&m_pPowerBrush, m_PowerColor);

  // Repaint the control
  m_PowerStatic.Invalidate();
} // OnPowerChange


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::OnHScroll
// Desc: Called when a horizontal scroll message is sent
// Parm: UINT nSBCode            - the code
// Parm: UINT nPos               - the postion
// Parm: CScrollBar *pScrollBar  - the scrollbar
// ----------------------------------------------------------------------------
void MeshMaterialDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
  // Get the address of the power slider
  CWnd *pSlider = &m_PowerSlider;

  // If the event is for the slider then call the power change function
  if (pSlider == reinterpret_cast<CWnd *>(pScrollBar))
    OnPowerChange();

  // Call the parent method
  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
} // OnHScroll


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::SetBrushColor
// Desc: Set the color of the given brush
// Parm: CBrush *pBrush  - the brush
// Parm: COLORREF color  - the color
// ----------------------------------------------------------------------------
void MeshMaterialDialog::SetBrushColor(CBrush **ppBrush, COLORREF color)
{
  delete *ppBrush;
  *ppBrush = new CBrush(color);
} // SetBrushColor


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::MakeColorValue
// Desc: Convert a COLORREF to a D3DCOLORVALUE
// Parm: COLORREF color - the color ref
// Retn: D3DCOLORVALUE  - the color value
// ----------------------------------------------------------------------------
D3DCOLORVALUE MeshMaterialDialog::MakeColorValue(COLORREF color)
{
  // Convert from 8 bit to float
  static const float convert = 1.0f / 255.0f;

  // The color value
  D3DCOLORVALUE d3dColor;

  // Convert the colors
  d3dColor.r = convert * GetRValue(color);
  d3dColor.g = convert * GetGValue(color);
  d3dColor.b = convert * GetBValue(color);
  d3dColor.a = 1.0f;

  // Return the color value
  return d3dColor;
} // MakeColorValue


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::MakeColorRef
// Desc: Convert a D3DCOLORVALUE to a COLORREF
// Parm: D3DCOLORVALUE color - the color value
// Retn: COLORREF            - the color ref
// ----------------------------------------------------------------------------
COLORREF MeshMaterialDialog::MakeColorRef(D3DCOLORVALUE colorValue)
{
  return RGB(
    static_cast<int>(255 * colorValue.r), 
    static_cast<int>(255 * colorValue.g), 
    static_cast<int>(255 * colorValue.b));
} // MakeColorRef


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog::MakeColorRef
// Desc: Convert a power value to a COLORREF
// Parm: float power - the power (0 - 255)
// Retn: COLORREF    - the color ref
// ----------------------------------------------------------------------------
COLORREF MeshMaterialDialog::MakeColorRef(float power)
{
  return RGB(
    static_cast<int>(power), 
    static_cast<int>(power), 
    static_cast<int>(power));
} // MakeColorRef


// -- EOF

