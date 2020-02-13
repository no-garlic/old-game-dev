// ----------------------------------------------------------------------------
// File: MeshLightDialog.cpp
// Desc: Dialog for modifying the lighting properties
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#include "MeshEditor/MeshLightDialog.h"
#include "MeshEditor/Resource.h"


// ----------------------------------------------------------------------------
// The Frame Window Message Map
// ----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(MeshLightDialog, CDialog)
  ON_BN_CLICKED(IDC_BUTTON_COLOR_GLOBAL,    OnColorGlobal)
  ON_BN_CLICKED(IDC_BUTTON_COLOR_AMBIENT,   OnColorAmbient)
  ON_BN_CLICKED(IDC_BUTTON_COLOR_DIFFUSE,   OnColorDiffuse)
  ON_BN_CLICKED(IDC_BUTTON_COLOR_SPECULAR,  OnColorSpecular)
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
// Name: MeshLightDialog::MeshLightDialog
// Desc: Constructor
// Parm: CWnd *pParentWnd - the parent window
// ----------------------------------------------------------------------------
MeshLightDialog::MeshLightDialog()
: CDialog             (IDD_LIGHT_EDITOR, AfxGetMainWnd()),
  m_GlobalColor       (RGB(0, 0, 0)),
  m_DiffuseColor      (RGB(0, 0, 0)),
  m_AmbientColor      (RGB(0, 0, 0)),
  m_SpecularColor     (RGB(0, 0, 0)),
  m_PowerColor        (RGB(0, 0, 0))
{
  m_pGlobalBrush   = new CBrush(m_GlobalColor);
  m_pDiffuseBrush  = new CBrush(m_DiffuseColor);
  m_pAmbientBrush  = new CBrush(m_AmbientColor);
  m_pSpecularBrush = new CBrush(m_SpecularColor);
  m_pPowerBrush    = new CBrush(m_PowerColor);

  // Enable lighting
  ApplicationCentral.GetDirectionalLight().enabled = true;
} // MeshLightDialog


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::~MeshLightDialog
// Desc: Destructor
// ----------------------------------------------------------------------------
MeshLightDialog::~MeshLightDialog()
{
  delete m_pGlobalBrush;
  delete m_pDiffuseBrush;
  delete m_pAmbientBrush;
  delete m_pSpecularBrush;
  delete m_pPowerBrush;
} // ~MeshLightDialog


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::OnInitDialog
// Desc: Called at dialog initialisation
// Retn: BOOL - true if the dialog is valid
// ----------------------------------------------------------------------------
BOOL MeshLightDialog::OnInitDialog()
{
  if (CDialog::OnInitDialog() == FALSE)
    return FALSE;

  return TRUE;
} // OnInitDialog


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::Init
// Desc: Initialise the dialog
// ----------------------------------------------------------------------------
void MeshLightDialog::Init()
{
  // Set the range of the sliders
  m_PowerSlider.SetRange(0, 255, true);
  m_HeadingSlider.SetRange(0, 360, true);
  m_PitchSlider.SetRange(0, 360, true);

  // Set the global ambient
  m_GlobalColor = MakeColorRef(ApplicationCentral.GetGlobalAmbient());
  SetBrushColor(&m_pGlobalBrush, m_GlobalColor);

  // Set the diffuse
  m_DiffuseColor = MakeColorRef(ApplicationCentral.GetDirectionalLight().diffuse);
  SetBrushColor(&m_pDiffuseBrush, m_DiffuseColor);

  // Set the ambient
  m_AmbientColor = MakeColorRef(ApplicationCentral.GetDirectionalLight().ambient);
  SetBrushColor(&m_pAmbientBrush, m_AmbientColor);

  // Set the specular
  m_SpecularColor = MakeColorRef(ApplicationCentral.GetDirectionalLight().specular);
  SetBrushColor(&m_pSpecularBrush, m_SpecularColor);

  // Set the power
  int powerValue = static_cast<int>(ApplicationCentral.GetDirectionalLight().power);
  Clamp(powerValue, 0, 255);
  m_PowerSlider.SetPos(powerValue);

  // Set the light direction
  float heading, pitch;
  GetLightDirection(heading, pitch);
  SetDirectionSliders(heading, pitch);

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

  // Repaint the window
  Invalidate();
} // Init


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::DoDataExchange
// Desc: Data Exchange
// Parm: CDataExchange *pDX - the data exchange context
// ----------------------------------------------------------------------------
void MeshLightDialog::DoDataExchange(CDataExchange *pDX)
{
  CDialog::DoDataExchange(pDX);

  DDX_Control(pDX, IDC_SLIDER_POWER,      m_PowerSlider);
  DDX_Control(pDX, IDC_HEADING,           m_HeadingSlider);
  DDX_Control(pDX, IDC_PITCH,             m_PitchSlider);
  DDX_Control(pDX, IDC_GLOBAL_COLOR,      m_GlobalStatic);
  DDX_Control(pDX, IDC_DIFFUSE_COLOR,     m_DiffuseStatic);
  DDX_Control(pDX, IDC_AMBIENT_COLOR,     m_AmbientStatic);
  DDX_Control(pDX, IDC_SPECULAR_COLOR,    m_SpecularStatic);
  DDX_Control(pDX, IDC_POWER_COLOR,       m_PowerStatic);
} // DoDataExchange


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::OnCtlColor
// Desc: Callback for setting the control color
// Parm: CDC *pDC        - the device context
// Parm: CWnd *pWnd      - the window
// Parm: UINT nCtlColor  - the control color
// Retn: HBRUSH          - teh brush to craw with
// ----------------------------------------------------------------------------
HBRUSH MeshLightDialog::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
  // If this is the static control
  switch (pWnd->GetDlgCtrlID())
  {
    case IDC_GLOBAL_COLOR:   return (HBRUSH) m_pGlobalBrush->GetSafeHandle();
    case IDC_AMBIENT_COLOR:  return (HBRUSH) m_pAmbientBrush->GetSafeHandle();
    case IDC_DIFFUSE_COLOR:  return (HBRUSH) m_pDiffuseBrush->GetSafeHandle();
    case IDC_SPECULAR_COLOR: return (HBRUSH) m_pSpecularBrush->GetSafeHandle();
    case IDC_POWER_COLOR:    return (HBRUSH) m_pPowerBrush->GetSafeHandle();
  }

  // Call the parent function
  return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
} // OnCtlColor


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::OnColorGlobal
// Desc: Callback for selecting a color button
// ----------------------------------------------------------------------------
void MeshLightDialog::OnColorGlobal()
{
  CColorDialog dlg(m_GlobalColor, CC_FULLOPEN, this);
  if (dlg.DoModal() == IDOK)
  {
    m_GlobalColor = dlg.GetColor();
    SetBrushColor(&m_pGlobalBrush, m_GlobalColor);
    m_GlobalStatic.Invalidate();

    // Set the global ambient
    ApplicationCentral.GetGlobalAmbient() = Color(MakeColorValue(m_GlobalColor));
  } // if
} // OnColorGlobal


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::OnColorDiffuse
// Desc: Callback for selecting a color button
// ----------------------------------------------------------------------------
void MeshLightDialog::OnColorDiffuse()
{
  CColorDialog dlg(m_DiffuseColor, CC_FULLOPEN, this);
  if (dlg.DoModal() == IDOK)
  {
    // Update the dialog
    m_DiffuseColor = dlg.GetColor();
    SetBrushColor(&m_pDiffuseBrush, m_DiffuseColor);
    m_DiffuseStatic.Invalidate();

    // Set the light color
    ApplicationCentral.GetDirectionalLight().diffuse = Color(MakeColorValue(m_DiffuseColor));
  } // if
} // OnColorDiffuse


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::OnColorAmbient
// Desc: Callback for selecting a color button
// ----------------------------------------------------------------------------
void MeshLightDialog::OnColorAmbient()
{
  CColorDialog dlg(m_AmbientColor, CC_FULLOPEN, this);
  if (dlg.DoModal() == IDOK)
  {
    m_AmbientColor = dlg.GetColor();
    SetBrushColor(&m_pAmbientBrush, m_AmbientColor);
    m_AmbientStatic.Invalidate();

    // Set the light color
    ApplicationCentral.GetDirectionalLight().ambient = Color(MakeColorValue(m_AmbientColor));
  } // if
} // OnColorAmbient


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::OnColorSpecular
// Desc: Callback for selecting a color button
// ----------------------------------------------------------------------------
void MeshLightDialog::OnColorSpecular()
{
  CColorDialog dlg(m_SpecularColor, CC_FULLOPEN, this);
  if (dlg.DoModal() == IDOK)
  {
    m_SpecularColor = dlg.GetColor();
    SetBrushColor(&m_pSpecularBrush, m_SpecularColor);
    m_SpecularStatic.Invalidate();

    // Set the light color
    ApplicationCentral.GetDirectionalLight().specular = Color(MakeColorValue(m_SpecularColor));
  } // if
} // OnColorSpecular


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::OnPowerChange
// Desc: Callback for when the power slider changes
// ----------------------------------------------------------------------------
void MeshLightDialog::OnPowerChange()
{
  // Get the slider value
  int sliderValue = m_PowerSlider.GetPos();
  Clamp<int>(sliderValue, 0, 255);

  // Set the light power
  ApplicationCentral.GetDirectionalLight().power = static_cast<float>(sliderValue);

  // Set the power color
  m_PowerColor = MakeColorRef(static_cast<float>(sliderValue));
  SetBrushColor(&m_pPowerBrush, m_PowerColor);

  // Repaint the control
  m_PowerStatic.Invalidate();
} // OnPowerChange


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::OnHeadingChange
// Desc: Callback for when the heading slider changes
// ----------------------------------------------------------------------------
void MeshLightDialog::OnHeadingChange()
{
  float heading, pitch;
  GetDirectionSliders(heading, pitch);
  SetLightDirection(heading, pitch);
} // OnHeadingChange


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::OnPitchChange
// Desc: Callback for when the pitch slider changes
// ----------------------------------------------------------------------------
void MeshLightDialog::OnPitchChange()
{
  float heading, pitch;
  GetDirectionSliders(heading, pitch);
  SetLightDirection(heading, pitch);
} // OnPitchChange


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::OnHScroll
// Desc: Called when a horizontal scroll message is sent
// Parm: UINT nSBCode            - the code
// Parm: UINT nPos               - the postion
// Parm: CScrollBar *pScrollBar  - the scrollbar
// ----------------------------------------------------------------------------
void MeshLightDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
  // Get the address of the sliders
  CWnd *pPowerSlider    = &m_PowerSlider;
  CWnd *pHeadingSlider  = &m_HeadingSlider;
  CWnd *pPitchSlider    = &m_PitchSlider;

  // If the event is for the slider then call the power change function
  if (pPowerSlider == reinterpret_cast<CWnd *>(pScrollBar))
    OnPowerChange();
  else if (pHeadingSlider == reinterpret_cast<CWnd *>(pScrollBar))
    OnHeadingChange();
  else if (pPitchSlider == reinterpret_cast<CWnd *>(pScrollBar))
    OnPitchChange();

  // Call the parent method
  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
} // OnHScroll


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::SetBrushColor
// Desc: Set the color of the given brush
// Parm: CBrush *pBrush  - the brush
// Parm: COLORREF color  - the color
// ----------------------------------------------------------------------------
void MeshLightDialog::SetBrushColor(CBrush **ppBrush, COLORREF color)
{
  delete *ppBrush;
  *ppBrush = new CBrush(color);
} // SetBrushColor


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::MakeColorValue
// Desc: Convert a COLORREF to a D3DCOLORVALUE
// Parm: COLORREF color - the color ref
// Retn: D3DCOLORVALUE  - the color value
// ----------------------------------------------------------------------------
D3DCOLORVALUE MeshLightDialog::MakeColorValue(COLORREF color)
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
// Name: MeshLightDialog::MakeColorRef
// Desc: Convert a D3DCOLORVALUE to a COLORREF
// Parm: D3DCOLORVALUE color - the color value
// Retn: COLORREF            - the color ref
// ----------------------------------------------------------------------------
COLORREF MeshLightDialog::MakeColorRef(D3DCOLORVALUE colorValue)
{
  return RGB(
    static_cast<int>(255 * colorValue.r), 
    static_cast<int>(255 * colorValue.g), 
    static_cast<int>(255 * colorValue.b));
} // MakeColorRef


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::MakeColorRef
// Desc: Convert a power value to a COLORREF
// Parm: float power - the power (0 - 255)
// Retn: COLORREF    - the color ref
// ----------------------------------------------------------------------------
COLORREF MeshLightDialog::MakeColorRef(float power)
{
  return RGB(
    static_cast<int>(power), 
    static_cast<int>(power), 
    static_cast<int>(power));
} // MakeColorRef


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::SetDirectionSliders
// Desc: Set the sliders
// Parm: float heading - the heading
// Parm: float pitch   - the pitch
// ----------------------------------------------------------------------------
void MeshLightDialog::SetDirectionSliders(float heading, float pitch)
{
  int h = static_cast<int>(heading) + 3600;
  int p = static_cast<int>(pitch) + 3600;

  h = h % 360;
  p = p % 360;

  m_HeadingSlider.SetPos(h);
  m_PitchSlider.SetPos(p);
} // SetDirectionSliders


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::GetDirectionSliders
// Desc: Get the direction from the sliders
// Parm: float &heading - the heading
// Parm: float &pitch   - the pitch
// ----------------------------------------------------------------------------
void MeshLightDialog::GetDirectionSliders(float &heading, float &pitch)
{
  heading = static_cast<float>(m_HeadingSlider.GetPos());
  pitch   = static_cast<float>(m_PitchSlider.GetPos());
} // GetDirectionSliders


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::SetLightDirection
// Desc: Set the light direction
// Parm: float heading - the heading
// Parm: float pitch   - the pitch
// ----------------------------------------------------------------------------
void MeshLightDialog::SetLightDirection(float heading, float pitch)
{
  float x = sinf(D3DXToRadian(heading));
  float y = cosf(D3DXToRadian(heading));
  float z = sinf(D3DXToRadian(pitch));

  ApplicationCentral.GetDirectionalLight().direction.Set(x, y, z);
} // SetLightDirection


// ----------------------------------------------------------------------------
// Name: MeshLightDialog::GetLightDirection
// Desc: Get the light direction
// Parm: float &heading - the heading
// Parm: float &pitch   - the pitch
// ----------------------------------------------------------------------------
void MeshLightDialog::GetLightDirection(float &heading, float &pitch)
{
  Vec3 dir = ApplicationCentral.GetDirectionalLight().direction;

  heading = D3DXToDegree(atan2f(dir.x, dir.y));
  pitch   = D3DXToDegree(asinf(dir.z));
} // GetLightDirection


// -- EOF

