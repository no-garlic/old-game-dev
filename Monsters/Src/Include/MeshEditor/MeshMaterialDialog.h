// ----------------------------------------------------------------------------
// File: MeshMaterialDialog.h
// Desc: Dialog for modifying the material properties of a mesh
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __MESH_MATERIAL_DIALOG_H_
#define __MESH_MATERIAL_DIALOG_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Engine/EngineInc.h"
#include "Render/RenderInc.h"


// ----------------------------------------------------------------------------
// Name: MeshMaterialDialog  (class)
// Desc: A dialog for editing the subset materials of a mesh
// ----------------------------------------------------------------------------
class MeshMaterialDialog : public CDialog
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  MeshMaterialDialog();
  virtual ~MeshMaterialDialog();

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
  void Init(Mesh *pMesh);
  void Release();

protected:
  // --------------------------------------------------------------------------
  // Protected functions
  // --------------------------------------------------------------------------
  afx_msg void OnSubsetSelect();
  afx_msg void OnEffectSelect();
  afx_msg void OnDiffuseTexSelect();
  afx_msg void OnAlphaTexSelect();
  afx_msg void OnNormalTexSelect();
  afx_msg void OnTex0Select();
  afx_msg void OnTex1Select();
  afx_msg void OnColorDiffuse();
  afx_msg void OnColorAmbient();
  afx_msg void OnColorEmissive();
  afx_msg void OnColorSpecular();
  afx_msg void OnPowerChange();

  // --------------------------------------------------------------------------
  // Message map
  // --------------------------------------------------------------------------
  DECLARE_MESSAGE_MAP()

private:
  // --------------------------------------------------------------------------
  // Preload all data for the combo boxes
  // --------------------------------------------------------------------------
  void PreLoadData();

  // --------------------------------------------------------------------------
  // Clear all controls
  // --------------------------------------------------------------------------
  void Clear(bool clearSubsets = false);

  // --------------------------------------------------------------------------
  // Enable the GUI controls
  // --------------------------------------------------------------------------
  void SetEnabled(bool enable);

  // --------------------------------------------------------------------------
  // Select a combo box item
  // --------------------------------------------------------------------------
  int SelectComboItem(CComboBox *pCombo, const String &item);

  // --------------------------------------------------------------------------
  // Find the selected combo box item
  // --------------------------------------------------------------------------
  String GetSelectedItem(CComboBox *pCombo);

  // --------------------------------------------------------------------------
  // Generic texture callback
  // --------------------------------------------------------------------------
  void OnTextureSelect(uint id);

  // --------------------------------------------------------------------------
  // Set a brush color
  // --------------------------------------------------------------------------
  void SetBrushColor(CBrush **ppBrush, COLORREF color);

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
  CComboBox      m_SubsetCombo;       // The subset combo
  CComboBox      m_EffectCombo;       // The effect combo
  CComboBox      m_DiffuseTexCombo;   // The diffuse texture combo
  CComboBox      m_AlphaTexCombo;     // The alpha texture combo
  CComboBox      m_NormalTexCombo;    // The normal texture combo
  CComboBox      m_Tex0Combo;         // The tex0 combo
  CComboBox      m_Tex1Combo;         // The tex1 combo
  CSliderCtrl    m_PowerSlider;       // The power slider control
  CStatic        m_DiffuseStatic;     // The diffuse color static
  CStatic        m_AmbientStatic;     // The ambient static
  CStatic        m_SpecularStatic;    // The specular static
  CStatic        m_EmissiveStatic;    // The emissive static
  CStatic        m_PowerStatic;       // The power static
  COLORREF       m_DiffuseColor;      // The diffuse color
  COLORREF       m_AmbientColor;      // The ambient color
  COLORREF       m_SpecularColor;     // The specular color
  COLORREF       m_EmissiveColor;     // The emissive color
  COLORREF       m_PowerColor;        // The power color
  CBrush        *m_pDiffuseBrush;     // Brush for diffuse control
  CBrush        *m_pAmbientBrush;     // Brush for ambient control
  CBrush        *m_pSpecularBrush;    // Brush for specular control
  CBrush        *m_pEmissiveBrush;    // Brush for emissive control
  CBrush        *m_pPowerBrush;       // The power brush

}; // MeshMaterialDialog


#endif // __MESH_MATERIAL_DIALOG_H_

// -- EOF
