// ----------------------------------------------------------------------------
// File: MeshLightDialog.h
// Desc: Dialog for modifying the lighting properties
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __MESH_LIGHT_DIALOG_H_
#define __MESH_LIGHT_DIALOG_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Engine/EngineInc.h"
#include "Render/RenderInc.h"


// ----------------------------------------------------------------------------
// Name: MeshLightDialog  (class)
// Desc: A dialog for editing the subset materials of a mesh
// ----------------------------------------------------------------------------
class MeshLightDialog : public CDialog
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  MeshLightDialog();
  virtual ~MeshLightDialog();

  // --------------------------------------------------------------------------
  // Called upon dialog initialisation
  // --------------------------------------------------------------------------
  virtual BOOL OnInitDialog();
  virtual HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
  virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
  virtual void DoDataExchange(CDataExchange *pDX);

  // --------------------------------------------------------------------------
  // Initialise the data for the given mesh
  // --------------------------------------------------------------------------
  void Init();

protected:
  // --------------------------------------------------------------------------
  // Protected functions
  // --------------------------------------------------------------------------
  afx_msg void OnColorGlobal();
  afx_msg void OnColorDiffuse();
  afx_msg void OnColorAmbient();
  afx_msg void OnColorSpecular();
  afx_msg void OnPowerChange();
  afx_msg void OnHeadingChange();
  afx_msg void OnPitchChange();

  // --------------------------------------------------------------------------
  // Message map
  // --------------------------------------------------------------------------
  DECLARE_MESSAGE_MAP()

private:
  // --------------------------------------------------------------------------
  // Set a brush color
  // --------------------------------------------------------------------------
  void SetBrushColor(CBrush **ppBrush, COLORREF color);

  // --------------------------------------------------------------------------
  // Convert from heading and pitch to a direction vector
  // --------------------------------------------------------------------------
  void SetLightDirection(float heading, float pitch);
  void GetLightDirection(float &heading, float &pitch);
  void SetDirectionSliders(float heading, float pitch);
  void GetDirectionSliders(float &heading, float &pitch);

  // --------------------------------------------------------------------------
  // Convert a color ref to a color value
  // --------------------------------------------------------------------------
  D3DCOLORVALUE MakeColorValue(COLORREF color);
  COLORREF MakeColorRef(D3DCOLORVALUE colorValue);
  COLORREF MakeColorRef(float power);

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  CSliderCtrl    m_PowerSlider;       // The power slider control
  CSliderCtrl    m_HeadingSlider;     // The heading slider
  CSliderCtrl    m_PitchSlider;       // The pitch slider
  CStatic        m_GlobalStatic;      // The global ambient static
  CStatic        m_DiffuseStatic;     // The diffuse color static
  CStatic        m_AmbientStatic;     // The ambient static
  CStatic        m_SpecularStatic;    // The specular static
  CStatic        m_PowerStatic;       // The power static
  COLORREF       m_GlobalColor;       // The global ambient color
  COLORREF       m_DiffuseColor;      // The diffuse color
  COLORREF       m_AmbientColor;      // The ambient color
  COLORREF       m_SpecularColor;     // The specular color
  COLORREF       m_PowerColor;        // The power color
  CBrush        *m_pGlobalBrush;      // Brush for global ambient control
  CBrush        *m_pDiffuseBrush;     // Brush for diffuse control
  CBrush        *m_pAmbientBrush;     // Brush for ambient control
  CBrush        *m_pSpecularBrush;    // Brush for specular control
  CBrush        *m_pPowerBrush;       // The power brush

}; // MeshLightDialog


#endif // __MESH_LIGHT_DIALOG_H_

// -- EOF
