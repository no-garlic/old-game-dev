// ----------------------------------------------------------------------------
// File: D3DSettingsDlg.h
// Desc: Direct3D device settings dialog. Allows a user to select the various 
//       device initialization options.
// Auth: Michael Petrou
// Note: Thanks to Adam Hoult & Gary Simmons from GameInstitute.com for the 
//       great code that was so easily adapted to work in my application.
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _D3DSETTINGSDLG_H_
#define _D3DSETTINGSDLG_H_


// ----------------------------------------------------------------------------
// D3DSettingsDlg specific includes
// ----------------------------------------------------------------------------
#include "Engine/D3DInitialize.h"
#include <tchar.h>


// ----------------------------------------------------------------------------
// Name: D3DSettingsDlg (class)
// Desc: Creates and controls a settings dialog for the d3d devices.
// ----------------------------------------------------------------------------
class D3DSettingsDlg
{
public:
    // ------------------------------------------------------------------------
    // Constructors & destructors for this class.
    // ------------------------------------------------------------------------
             D3DSettingsDlg();
    virtual ~D3DSettingsDlg();


    // ------------------------------------------------------------------------
    // Public functions for this class
    // ------------------------------------------------------------------------
    int            ShowDialog                (D3DInitialize * pInitialize, D3DSettings *pSettings = 0, HWND hWndParent = 0);
    D3DSettings    GetD3DSettings            () const { return m_D3DSettings; }
    

private:
    // ------------------------------------------------------------------------
    // Private functions for this class
    // ------------------------------------------------------------------------
    BOOL            SettingsDlgProc           (HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
    void            AdapterChanged            ();
    void            DeviceChanged             ();
    void            WindowedFullscreenChanged ();
    void            AdapterFormatChanged      ();
    void            ResolutionChanged         ();
    void            RefreshRateChanged        ();
    void            BackBufferFormatChanged   ();
    void            DepthStencilFormatChanged ();
    void            MultisampleTypeChanged    ();
    void            MultisampleQualityChanged ();
    void            VertexProcessingChanged   ();
    void            PresentIntervalChanged    ();

    void            Combo_ItemAdd             (ULONG ComboID, LPVOID pData, LPCTSTR pStrDesc);
    LPVOID          Combo_GetSelectedItemData (ULONG ComboID);
    ULONG           Combo_GetItemCount        (ULONG ComboID);
    void            Combo_SelectItem          (ULONG ComboID, ULONG Index);
    void            Combo_SelectItemData      (ULONG ComboID, LPVOID pData);
    void            Combo_Clear               (ULONG ComboID);
    bool            Combo_FindText            (ULONG ComboID, LPCTSTR pStrText);


    // ------------------------------------------------------------------------
    // Get the settings
    // ------------------------------------------------------------------------
    D3DSettings::Settings * GetSettings ()  { return m_D3DSettings.GetSettings(); }


    // ------------------------------------------------------------------------
    // Private static functions for this class
    // ------------------------------------------------------------------------
    static BOOL CALLBACK StaticDlgProc        (HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);


    // ------------------------------------------------------------------------
    // Private variables for this class
    // ------------------------------------------------------------------------
    D3DInitialize   *m_pInitialize;         // The class which stores enum objects
    HWND             m_hWndDlg;             // The main dialog window handle 
    D3DSettings      m_D3DSettings;         // The settings we are currently using
}; // D3DSettingsDlg


#endif // _D3DSETTINGSDLG_H_

// -- EOF

