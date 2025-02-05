// ----------------------------------------------------------------------------
// File: D3DSettingsDlg.cpp
// Desc: Direct3D device settings dialog. Allows a user to select the various 
//       device initialization options.
// Auth: Michael Petrou
// Note: Thanks to Adam Hoult & Gary Simmons from GameInstitute.com for the 
//       great code that was so easily adapted to work in my application.
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// D3DSettingsDlg specific includes
// ----------------------------------------------------------------------------
#include "Engine/D3DSettingsDlg.h"
#include "Res/resource.h"
#include <windows.h>
#include <windowsx.h>


// ----------------------------------------------------------------------------
// Local module function declarations
// ----------------------------------------------------------------------------
LPCTSTR D3DDevTypeToString           (D3DDEVTYPE devType);
LPCTSTR MultisampleTypeToString      (D3DMULTISAMPLE_TYPE MultiSampleType);
LPCTSTR VertexProcessingTypeToString (VERTEXPROCESSING_TYPE vpt);
LPCTSTR D3DFormatToString            (D3DFORMAT format, bool bWithPrefix = true);
LPCTSTR PresentIntervalToString      (UINT pi);


// ----------------------------------------------------------------------------
// Name: D3DDevTypeToString
// Desc: Returns the string for the given D3DDEVTYPE.
// ----------------------------------------------------------------------------
LPCTSTR D3DDevTypeToString(D3DDEVTYPE devType)
{
    switch (devType)
    {
    case D3DDEVTYPE_HAL:        return _T("D3DDEVTYPE_HAL");
    case D3DDEVTYPE_SW:         return _T("D3DDEVTYPE_SW");
    case D3DDEVTYPE_REF:        return _T("D3DDEVTYPE_REF");
    default:                    return _T("Unknown D3DDEVTYPE");
    } // switch
} // D3DDevTypeToString


// ----------------------------------------------------------------------------
// Name: MultisampleTypeToString
// Desc: Returns the string for the given D3DMULTISAMPLE_TYPE.
// ----------------------------------------------------------------------------
LPCTSTR MultisampleTypeToString(D3DMULTISAMPLE_TYPE MultiSampleType)
{
    switch (MultiSampleType)
    {
    case D3DMULTISAMPLE_NONE:           return _T("D3DMULTISAMPLE_NONE");
    case D3DMULTISAMPLE_NONMASKABLE:    return _T("D3DMULTISAMPLE_NONMASKABLE");
    case D3DMULTISAMPLE_2_SAMPLES:      return _T("D3DMULTISAMPLE_2_SAMPLES");
    case D3DMULTISAMPLE_3_SAMPLES:      return _T("D3DMULTISAMPLE_3_SAMPLES");
    case D3DMULTISAMPLE_4_SAMPLES:      return _T("D3DMULTISAMPLE_4_SAMPLES");
    case D3DMULTISAMPLE_5_SAMPLES:      return _T("D3DMULTISAMPLE_5_SAMPLES");
    case D3DMULTISAMPLE_6_SAMPLES:      return _T("D3DMULTISAMPLE_6_SAMPLES");
    case D3DMULTISAMPLE_7_SAMPLES:      return _T("D3DMULTISAMPLE_7_SAMPLES");
    case D3DMULTISAMPLE_8_SAMPLES:      return _T("D3DMULTISAMPLE_8_SAMPLES");
    case D3DMULTISAMPLE_9_SAMPLES:      return _T("D3DMULTISAMPLE_9_SAMPLES");
    case D3DMULTISAMPLE_10_SAMPLES:     return _T("D3DMULTISAMPLE_10_SAMPLES");
    case D3DMULTISAMPLE_11_SAMPLES:     return _T("D3DMULTISAMPLE_11_SAMPLES");
    case D3DMULTISAMPLE_12_SAMPLES:     return _T("D3DMULTISAMPLE_12_SAMPLES");
    case D3DMULTISAMPLE_13_SAMPLES:     return _T("D3DMULTISAMPLE_13_SAMPLES");
    case D3DMULTISAMPLE_14_SAMPLES:     return _T("D3DMULTISAMPLE_14_SAMPLES");
    case D3DMULTISAMPLE_15_SAMPLES:     return _T("D3DMULTISAMPLE_15_SAMPLES");
    case D3DMULTISAMPLE_16_SAMPLES:     return _T("D3DMULTISAMPLE_16_SAMPLES");
    default:                            return _T("Unknown D3DMULTISAMPLE_TYPE");
    } // switch
} // MultisampleTypeToString


// ----------------------------------------------------------------------------
// Name: VertexProcessingTypeToString
// Desc: Returns the string for the given VertexProcessingType.
// ----------------------------------------------------------------------------
LPCTSTR VertexProcessingTypeToString(VERTEXPROCESSING_TYPE vpt)
{
    switch (vpt)
    {
    case SOFTWARE_VP:      return _T("SOFTWARE_VP");
    case MIXED_VP:         return _T("MIXED_VP");
    case HARDWARE_VP:      return _T("HARDWARE_VP");
    case PURE_HARDWARE_VP: return _T("PURE_HARDWARE_VP");
    default:               return _T("Unknown VERTEXPROCESSING_TYPE");
    } // switch
} // VertexProcessingTypeToString


// ----------------------------------------------------------------------------
// Name: PresentIntervalToString
// Desc: Returns the string for the given present interval.
// ----------------------------------------------------------------------------
LPCTSTR PresentIntervalToString(UINT pi)
{
    switch(pi)
    {
    case D3DPRESENT_INTERVAL_IMMEDIATE: return _T("D3DPRESENT_INTERVAL_IMMEDIATE");
    case D3DPRESENT_INTERVAL_DEFAULT:   return _T("D3DPRESENT_INTERVAL_DEFAULT");
    case D3DPRESENT_INTERVAL_ONE:       return _T("D3DPRESENT_INTERVAL_ONE");
    case D3DPRESENT_INTERVAL_TWO:       return _T("D3DPRESENT_INTERVAL_TWO");
    case D3DPRESENT_INTERVAL_THREE:     return _T("D3DPRESENT_INTERVAL_THREE");
    case D3DPRESENT_INTERVAL_FOUR:      return _T("D3DPRESENT_INTERVAL_FOUR");
    default:                            return _T("Unknown Present-Interval");
    } // switch
} // PresentIntervalToString


// ----------------------------------------------------------------------------
// Name: D3DFormatToString
// Desc: Returns the string for the given D3DFORMAT.
// ----------------------------------------------------------------------------
LPCTSTR D3DFormatToString(D3DFORMAT format, bool bWithPrefix)
{
    LPTSTR pstr = 0;
    
    switch(format)
    {
    case D3DFMT_UNKNOWN:         pstr = _T("D3DFMT_UNKNOWN");       break;
    case D3DFMT_R8G8B8:          pstr = _T("D3DFMT_R8G8B8");        break;
    case D3DFMT_A8R8G8B8:        pstr = _T("D3DFMT_A8R8G8B8");      break;
    case D3DFMT_X8R8G8B8:        pstr = _T("D3DFMT_X8R8G8B8");      break;
    case D3DFMT_R5G6B5:          pstr = _T("D3DFMT_R5G6B5");        break;
    case D3DFMT_X1R5G5B5:        pstr = _T("D3DFMT_X1R5G5B5");      break;
    case D3DFMT_A1R5G5B5:        pstr = _T("D3DFMT_A1R5G5B5");      break;
    case D3DFMT_A4R4G4B4:        pstr = _T("D3DFMT_A4R4G4B4");      break;
    case D3DFMT_R3G3B2:          pstr = _T("D3DFMT_R3G3B2");        break;
    case D3DFMT_A8:              pstr = _T("D3DFMT_A8");            break;
    case D3DFMT_A8R3G3B2:        pstr = _T("D3DFMT_A8R3G3B2");      break;
    case D3DFMT_X4R4G4B4:        pstr = _T("D3DFMT_X4R4G4B4");      break;
    case D3DFMT_A2B10G10R10:     pstr = _T("D3DFMT_A2B10G10R10");   break;
    case D3DFMT_A8B8G8R8:        pstr = _T("D3DFMT_A8B8G8R8");      break;
    case D3DFMT_X8B8G8R8:        pstr = _T("D3DFMT_X8B8G8R8");      break;
    case D3DFMT_G16R16:          pstr = _T("D3DFMT_G16R16");        break;
    case D3DFMT_A2R10G10B10:     pstr = _T("D3DFMT_A2R10G10B10");   break;
    case D3DFMT_A16B16G16R16:    pstr = _T("D3DFMT_A16B16G16R16");  break;
    case D3DFMT_A8P8:            pstr = _T("D3DFMT_A8P8");          break;
    case D3DFMT_P8:              pstr = _T("D3DFMT_P8");            break;
    case D3DFMT_L8:              pstr = _T("D3DFMT_L8");            break;
    case D3DFMT_A8L8:            pstr = _T("D3DFMT_A8L8");          break;
    case D3DFMT_A4L4:            pstr = _T("D3DFMT_A4L4");          break;
    case D3DFMT_V8U8:            pstr = _T("D3DFMT_V8U8");          break;
    case D3DFMT_L6V5U5:          pstr = _T("D3DFMT_L6V5U5");        break;
    case D3DFMT_X8L8V8U8:        pstr = _T("D3DFMT_X8L8V8U8");      break;
    case D3DFMT_Q8W8V8U8:        pstr = _T("D3DFMT_Q8W8V8U8");      break;
    case D3DFMT_V16U16:          pstr = _T("D3DFMT_V16U16");        break;
    case D3DFMT_A2W10V10U10:     pstr = _T("D3DFMT_A2W10V10U10");   break;
    case D3DFMT_UYVY:            pstr = _T("D3DFMT_UYVY");          break;
    case D3DFMT_YUY2:            pstr = _T("D3DFMT_YUY2");          break;
    case D3DFMT_DXT1:            pstr = _T("D3DFMT_DXT1");          break;
    case D3DFMT_DXT2:            pstr = _T("D3DFMT_DXT2");          break;
    case D3DFMT_DXT3:            pstr = _T("D3DFMT_DXT3");          break;
    case D3DFMT_DXT4:            pstr = _T("D3DFMT_DXT4");          break;
    case D3DFMT_DXT5:            pstr = _T("D3DFMT_DXT5");          break;
    case D3DFMT_D16_LOCKABLE:    pstr = _T("D3DFMT_D16_LOCKABLE");  break;
    case D3DFMT_D32:             pstr = _T("D3DFMT_D32");           break;
    case D3DFMT_D15S1:           pstr = _T("D3DFMT_D15S1");         break;
    case D3DFMT_D24S8:           pstr = _T("D3DFMT_D24S8");         break;
    case D3DFMT_D24X8:           pstr = _T("D3DFMT_D24X8");         break;
    case D3DFMT_D24X4S4:         pstr = _T("D3DFMT_D24X4S4");       break;
    case D3DFMT_D16:             pstr = _T("D3DFMT_D16");           break;
    case D3DFMT_L16:             pstr = _T("D3DFMT_L16");           break;
    case D3DFMT_VERTEXDATA:      pstr = _T("D3DFMT_VERTEXDATA");    break;
    case D3DFMT_INDEX16:         pstr = _T("D3DFMT_INDEX16");       break;
    case D3DFMT_INDEX32:         pstr = _T("D3DFMT_INDEX32");       break;
    case D3DFMT_Q16W16V16U16:    pstr = _T("D3DFMT_Q16W16V16U16");  break;
    case D3DFMT_MULTI2_ARGB8:    pstr = _T("D3DFMT_MULTI2_ARGB8");  break;
    case D3DFMT_R16F:            pstr = _T("D3DFMT_R16F");          break;
    case D3DFMT_G16R16F:         pstr = _T("D3DFMT_G16R16F");       break;
    case D3DFMT_A16B16G16R16F:   pstr = _T("D3DFMT_A16B16G16R16F"); break;
    case D3DFMT_R32F:            pstr = _T("D3DFMT_R32F");          break;
    case D3DFMT_G32R32F:         pstr = _T("D3DFMT_G32R32F");       break;
    case D3DFMT_A32B32G32R32F:   pstr = _T("D3DFMT_A32B32G32R32F"); break;
    case D3DFMT_CxV8U8:          pstr = _T("D3DFMT_CxV8U8");        break;
    default:                     pstr = _T("Unknown format");       break;
    } // switch
    
    if (bWithPrefix || _tcsstr(pstr, _T("D3DFMT_"))== 0)
        return pstr;
    else
        return pstr + lstrlen(_T("D3DFMT_"));
} // D3DFormatToString


// ----------------------------------------------------------------------------
// Name : D3DSettingsDlg::D3DSettingsDlg
// Desc : Constructor
// ----------------------------------------------------------------------------
D3DSettingsDlg::D3DSettingsDlg()
{
    // Reset / Clear all required values
    m_hWndDlg      = 0;
    m_pInitialize  = 0;
} // D3DSettingsDlg


// ----------------------------------------------------------------------------
// Name : D3DSettingsDlg::~D3DSettingsDlg
// Desc : Destructor
// ----------------------------------------------------------------------------
D3DSettingsDlg::~D3DSettingsDlg()
{
} // ~D3DSettingsDlg


// ----------------------------------------------------------------------------
// Name: D3DSettingsDlg::ShowDialog
// Desc: Displays the settings dialog box.
// Parm: D3DInitialize * pInitialize - the initialize class
// Parm: D3DSettings *pSettings      - the settings
// Parm: HWND hWndParent             - the window parent
// Retn: int                         - the result code (OK, Cancel)
// ----------------------------------------------------------------------------
int D3DSettingsDlg::ShowDialog(D3DInitialize * pInitialize, D3DSettings *pSettings, HWND hWndParent)
{
    // Store the initialize object that stores our enumerated objects
    m_pInitialize = pInitialize;

    // Store the settings passed in
    if (pSettings) 
    {
        m_D3DSettings = *pSettings;
    } // if
    else
    {
        // No settings passed in, create a default set
        ZeroMemory(&m_D3DSettings, sizeof(D3DSettings));
        m_D3DSettings.Windowed = true;

        // Setup windowed mode defaults
        D3DDISPLAYMODE DisplayMode;
        m_pInitialize->GetDirect3D()->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DisplayMode);

        GetSettings()->AdapterOrdinal = D3DADAPTER_DEFAULT;
        GetSettings()->DisplayMode    = DisplayMode;
    } // else
    
    // Create the dialog box
    return DialogBoxParam(0, MAKEINTRESOURCE(IDD_D3DSETTINGS) , hWndParent, StaticDlgProc, (LPARAM)this);
} // ShowDialog


// ----------------------------------------------------------------------------
// Name: D3DSettingsDlg::StaticDlgProc
// Desc: This is the main messge pump for all settings dialogs, it captures the 
//       appropriate messages, and routes them through to the settings class for
//       which it was intended, therefore giving full class access. Note : It is
//       VITALLY important that you should pass your 'this' pointer to the 
//       lpParam parameter of the CreateDialogParam function if you wish to be 
//       able to pass messages back to that settings object.
// Parm: HWND hWnd      - the window
// Parm: UINT Message   - the message
// Parm: WPARAM wParam  - the param 1
// Parm: LPARAM lParam  - the param 2
// Retn: BOOL CALLBACK  - the result
// ----------------------------------------------------------------------------
BOOL CALLBACK D3DSettingsDlg::StaticDlgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    // If this is a create message, trap the 'this' pointer passed in and store it within the window.
    if (Message == WM_INITDIALOG) 
        SetWindowLong(hWnd, GWL_USERDATA, lParam);

    // Obtain the correct destination for this message
    D3DSettingsDlg *Destination = (D3DSettingsDlg *) GetWindowLong(hWnd, GWL_USERDATA);
    
    // If the hWnd has a related class, pass it through
    if (Destination) 
        return Destination->SettingsDlgProc(hWnd, Message, wParam, lParam);
    
    // No destination found, defer to system...
    return FALSE;
} // StaticDlgProc


// ----------------------------------------------------------------------------
// Name: D3DSettingsDlg::SettingsDlgProc
// Desc: This is the main messge pump for this settings dialog.
// Parm: HWND hWnd      - the window
// Parm: UINT Message   - the message
// Parm: WPARAM wParam  - the param 1
// Parm: LPARAM lParam  - the param 2
// Retn: BOOL           - the result
// ----------------------------------------------------------------------------
BOOL D3DSettingsDlg::SettingsDlgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    ULONG i;

    switch (Message)
    {
    case WM_INITDIALOG:
        // Store the handle to our dialog
        m_hWndDlg = hWnd;

        // Fill the adapter combo box
        for (i = 0; i < m_pInitialize->GetAdapterCount(); i++)
        {
            const D3DEnumAdapter *pAdapter = m_pInitialize->GetAdapter(i);
            Combo_ItemAdd(IDC_COMBO_ADAPTER, (LPVOID)pAdapter, pAdapter->Identifier.Description);

            // If this is a setting we already have set, select it in the combo
            if (pAdapter->Ordinal == GetSettings()->AdapterOrdinal)
                Combo_SelectItemData(IDC_COMBO_ADAPTER, (LPVOID)pAdapter);
        } // for

        // If nothing is already selected, select the first item
        if (Combo_GetSelectedItemData(IDC_COMBO_ADAPTER) == 0 && Combo_GetItemCount(IDC_COMBO_ADAPTER) > 0)
            Combo_SelectItem(IDC_COMBO_ADAPTER, 0);

        // Set focus for us.
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            // OK was triggered
            EndDialog(hWnd, IDOK);
            break;

        case IDCANCEL:
            // Cancel was triggered
            EndDialog(hWnd, IDCANCEL);
            break;

        case IDC_COMBO_ADAPTER:
            if (CBN_SELCHANGE == HIWORD(wParam))
                AdapterChanged();
            break;

        case IDC_COMBO_DEVICE:
            if (CBN_SELCHANGE == HIWORD(wParam))
                DeviceChanged();
            break;

        case IDC_COMBO_AFORMAT:
            if (CBN_SELCHANGE == HIWORD(wParam))
                AdapterFormatChanged();
            break;

        case IDC_COMBO_RESOLUTION:
            if (CBN_SELCHANGE == HIWORD(wParam)) 
                ResolutionChanged();
            break;

        case IDC_COMBO_REFRESH:
            if (CBN_SELCHANGE == HIWORD(wParam))
                RefreshRateChanged();
            break;

        case IDC_COMBO_BBFORMAT:
            if (CBN_SELCHANGE == HIWORD(wParam))
                BackBufferFormatChanged();
            break;

        case IDC_COMBO_DSFORMAT:
            if (CBN_SELCHANGE == HIWORD(wParam))
                DepthStencilFormatChanged();
            break;

        case IDC_COMBO_MSTYPE:
            if (CBN_SELCHANGE == HIWORD(wParam))
                MultisampleTypeChanged();
            break;

        case IDC_COMBO_MSQUALITY:
            if (CBN_SELCHANGE == HIWORD(wParam))
                MultisampleQualityChanged();
            break;

        case IDC_COMBO_VPTYPE:
            if (CBN_SELCHANGE == HIWORD(wParam))
                VertexProcessingChanged();
            break;

        case IDC_COMBO_PINTERVAL:
            if (CBN_SELCHANGE == HIWORD(wParam))
                PresentIntervalChanged();
            break;

        case IDC_RADIO_WINDOWED:
        case IDC_RADIO_FULLSCREEN:
            WindowedFullscreenChanged();
            break;

        } // switch
        break;

    default:
        // Not Processed!
        return FALSE;

    } // switch

    return TRUE;
} // SettingsDlgProc


// ----------------------------------------------------------------------------
// Name: D3DSettingsDlg::AdapterChanged
// Desc: Triggered when a change of selected adapter is posted.
// ----------------------------------------------------------------------------
void D3DSettingsDlg::AdapterChanged()
{
    D3DEnumAdapter * pAdapter = (D3DEnumAdapter*)Combo_GetSelectedItemData(IDC_COMBO_ADAPTER);
    if (pAdapter == 0)
        return;
    
    // Set the current adapter information
    GetSettings()->AdapterOrdinal = pAdapter->Ordinal;

    // Update windowed display mode settings
    if (m_D3DSettings.Windowed == true)
    {
        D3DDISPLAYMODE DisplayMode;
        m_pInitialize->GetDirect3D()->GetAdapterDisplayMode(pAdapter->Ordinal, &DisplayMode);
        GetSettings()->DisplayMode = DisplayMode;
    } // if

    // Update device combo box
    Combo_Clear(IDC_COMBO_DEVICE);
    for (ULONG i = 0; i < pAdapter->Devices.size(); i++)
    {
        D3DEnumDevice *pDevice = pAdapter->Devices[i];
        Combo_ItemAdd(IDC_COMBO_DEVICE, pDevice, D3DDevTypeToString(pDevice->DeviceType));

        // If this is a setting we already have set, select it in the combo
        if (pDevice->DeviceType == GetSettings()->DeviceType)
            Combo_SelectItemData(IDC_COMBO_DEVICE, pDevice);
    } // for
    
    // If nothing is already selected, select the first item
    if (Combo_GetSelectedItemData(IDC_COMBO_DEVICE) == 0 && Combo_GetItemCount(IDC_COMBO_DEVICE) > 0)
        Combo_SelectItem(IDC_COMBO_DEVICE, 0);
} // AdapterChanged


// ----------------------------------------------------------------------------
// Name: D3DSettingsDlg::DeviceChanged
// Desc: Triggered when a change of selected device is posted.
// ----------------------------------------------------------------------------
void D3DSettingsDlg::DeviceChanged()
{
    D3DEnumDevice *pDevice = (D3DEnumDevice *) Combo_GetSelectedItemData(IDC_COMBO_DEVICE);
    if (pDevice == 0) 
        return;
    
    // Set the current device information
    GetSettings()->DeviceType = pDevice->DeviceType;

    // Update fullscreen/windowed radio buttons
    bool HasWindowedDeviceOption   = false;
    bool HasFullscreenDeviceOption = false;

    // Loop through each device option
    for (ULONG i = 0; i < pDevice->Options.size(); i++)
    {
        D3DEnumDeviceOptions * pDeviceOptions = (D3DEnumDeviceOptions*)pDevice->Options[ i ];
        if (pDeviceOptions->Windowed) 
            HasWindowedDeviceOption = true; 
        else 
            HasFullscreenDeviceOption = true;
    } // for

    // Enable / disable radio buttons
    EnableWindow(GetDlgItem(m_hWndDlg, IDC_RADIO_WINDOWED  ), HasWindowedDeviceOption);
    EnableWindow(GetDlgItem(m_hWndDlg, IDC_RADIO_FULLSCREEN), HasFullscreenDeviceOption);
    
    // If this is a setting we already have set, set the radio button 
    if (m_D3DSettings.Windowed && HasWindowedDeviceOption)
        CheckRadioButton(m_hWndDlg, IDC_RADIO_WINDOWED, IDC_RADIO_FULLSCREEN, IDC_RADIO_WINDOWED);
    else
        CheckRadioButton(m_hWndDlg, IDC_RADIO_WINDOWED, IDC_RADIO_FULLSCREEN, IDC_RADIO_FULLSCREEN);

    // Trigger the change
    WindowedFullscreenChanged();
} // DeviceChanged


// ----------------------------------------------------------------------------
// Name: D3DSettingsDlg::WindowedFullscreenChanged
// Desc: Triggered when a change of windowed / fullscreen mode is posted.
// ----------------------------------------------------------------------------
void D3DSettingsDlg::WindowedFullscreenChanged()
{
    D3DEnumAdapter * pAdapter = (D3DEnumAdapter*)Combo_GetSelectedItemData(IDC_COMBO_ADAPTER);
    D3DEnumDevice  * pDevice  = (D3DEnumDevice *)Combo_GetSelectedItemData(IDC_COMBO_DEVICE);
    if (pAdapter == 0 || pDevice == 0) return;
    
    // Which mode is selected
    if (IsDlgButtonChecked(m_hWndDlg, IDC_RADIO_WINDOWED))
    {
        // Set the current device information
        m_D3DSettings.Windowed          = true;
        GetSettings()->AdapterOrdinal   = pAdapter->Ordinal;
        GetSettings()->DeviceType       = pDevice->DeviceType;
        
        // Update adapter format combo box
        D3DFORMAT Format = GetSettings()->DisplayMode.Format;
        Combo_Clear(IDC_COMBO_AFORMAT);
        Combo_ItemAdd(IDC_COMBO_AFORMAT, (LPVOID)Format, D3DFormatToString(Format));
        Combo_SelectItem(IDC_COMBO_AFORMAT, 0);
        EnableWindow(GetDlgItem(m_hWndDlg, IDC_COMBO_AFORMAT), false);

        // Update resolution combo box
        ULONG ulResolutionData, Width, Height;
        TCHAR strResolution[50];

        Width  = GetSettings()->DisplayMode.Width;
        Height = GetSettings()->DisplayMode.Height;
        ulResolutionData = MAKELONG(Width, Height);
        _sntprintf(strResolution, 50, _T("%d x %d"), Width, Height);
        strResolution[49] = 0;

        Combo_Clear(IDC_COMBO_RESOLUTION);
        Combo_ItemAdd(IDC_COMBO_RESOLUTION, (LPVOID)ulResolutionData, strResolution);
        Combo_SelectItem(IDC_COMBO_RESOLUTION, 0);
        EnableWindow(GetDlgItem(m_hWndDlg, IDC_COMBO_RESOLUTION), false);

        // Update refresh rate combo box
        TCHAR strRefreshRate[50];
        ULONG ulRefreshRate = GetSettings()->DisplayMode.RefreshRate;

        _sntprintf(strRefreshRate, 50, _T("%d Hz"), ulRefreshRate);
        strRefreshRate[49] = 0;

        Combo_Clear(IDC_COMBO_REFRESH);
        Combo_ItemAdd(IDC_COMBO_REFRESH, (LPVOID)ulRefreshRate, strRefreshRate);
        Combo_SelectItem(IDC_COMBO_REFRESH, 0);
        EnableWindow(GetDlgItem(m_hWndDlg, IDC_COMBO_REFRESH), false);

    } // if
    else
    {
        // Set the current device information
        m_D3DSettings.Windowed = false;
        GetSettings()->AdapterOrdinal = pAdapter->Ordinal;
        GetSettings()->DeviceType     = pDevice->DeviceType;

        // Update Adapter Format Combo Box
        Combo_Clear(IDC_COMBO_AFORMAT);
        for (ULONG i = 0; i < pDevice->Options.size(); i++)
        {
            D3DEnumDeviceOptions * pDeviceOptions = pDevice->Options[ i ];
            D3DFORMAT AFormat = pDeviceOptions->AdapterFormat;
            
            // Determine if this has already been added
            if (!Combo_FindText(IDC_COMBO_AFORMAT, D3DFormatToString(AFormat)))
            {
                Combo_ItemAdd(IDC_COMBO_AFORMAT, (LPVOID)AFormat, D3DFormatToString(AFormat));
                if (AFormat == GetSettings()->DisplayMode.Format)
                    Combo_SelectItemData(IDC_COMBO_AFORMAT, (LPVOID)AFormat);
            } // if
        } // for

        // If nothing is already selected, select the first item
        if (Combo_GetSelectedItemData(IDC_COMBO_AFORMAT) == 0 && Combo_GetItemCount(IDC_COMBO_AFORMAT) > 0)
            Combo_SelectItem(IDC_COMBO_AFORMAT, 0);

        // Enable relevant combo boxes
        EnableWindow(GetDlgItem(m_hWndDlg, IDC_COMBO_AFORMAT), true);
        EnableWindow(GetDlgItem(m_hWndDlg, IDC_COMBO_RESOLUTION), true);
        EnableWindow(GetDlgItem(m_hWndDlg, IDC_COMBO_REFRESH), true);
    } // else
} // WindowedFullscreenChanged


// ----------------------------------------------------------------------------
// Name: D3DSettingsDlg::AdapterFormatChanged
// Desc: Triggered when a change of adapter format is posted.
// ----------------------------------------------------------------------------
void D3DSettingsDlg::AdapterFormatChanged()
{
    ULONG     i;
    D3DFORMAT AFormat;
    
    // Is fullscreen selected ?
    if (m_D3DSettings.Windowed == false)
    {
        D3DEnumAdapter * pAdapter = (D3DEnumAdapter*)Combo_GetSelectedItemData(IDC_COMBO_ADAPTER);
        if (pAdapter == 0) 
            return;

        AFormat = (D3DFORMAT)((ULONG)Combo_GetSelectedItemData(IDC_COMBO_AFORMAT));

        // Set the current device information
        GetSettings()->DisplayMode.Format = AFormat;

        // Update resolution combo box
        Combo_Clear(IDC_COMBO_RESOLUTION);
        for (i = 0; i < pAdapter->Modes.size(); i++)
        {
            D3DDISPLAYMODE Mode = pAdapter->Modes[ i ];
            
            // If the formats match
            if (Mode.Format == AFormat)
            {
                // Build Resolution Data
                ULONG ulResolutionData;
                TCHAR strResolution[50];

                ulResolutionData = MAKELONG(Mode.Width, Mode.Height);
                _sntprintf(strResolution, 50, _T("%d x %d"), Mode.Width, Mode.Height);
                strResolution[49] = 0;

                // Determine if this item already exists.
                if (!Combo_FindText(IDC_COMBO_RESOLUTION, strResolution))
                {
                    // Add the resolution item
                    Combo_ItemAdd(IDC_COMBO_RESOLUTION, (LPVOID)ulResolutionData, strResolution);
                    
                    // If this is a setting we already have set, select it in the combo
                    if (GetSettings()->DisplayMode.Width == Mode.Width && GetSettings()->DisplayMode.Height == Mode.Height)
                        Combo_SelectItemData(IDC_COMBO_RESOLUTION, (LPVOID)ulResolutionData);
                } // if
            } // if
        } // for

        // If nothing is already selected, select the first item
        if (Combo_GetSelectedItemData(IDC_COMBO_RESOLUTION) == 0 && Combo_GetItemCount(IDC_COMBO_RESOLUTION) > 0)
            Combo_SelectItem(IDC_COMBO_RESOLUTION, 0);
    } // if

    // Update BackBuffer format Combo Box
    D3DEnumDevice * pDevice  = (D3DEnumDevice *)Combo_GetSelectedItemData(IDC_COMBO_DEVICE);
    if (pDevice == 0)
        return;

    Combo_Clear(IDC_COMBO_BBFORMAT);
    for (i = 0; i < pDevice->Options.size(); i++)
    {
        D3DEnumDeviceOptions * pDeviceOptions = pDevice->Options[ i ];
        if (pDeviceOptions->Windowed == m_D3DSettings.Windowed && pDeviceOptions->AdapterFormat == GetSettings()->DisplayMode.Format)
        {
            // Already contains this format ?
            if (!Combo_FindText(IDC_COMBO_BBFORMAT, D3DFormatToString(pDeviceOptions->BackBufferFormat)))
            {
                // Add the format
                Combo_ItemAdd(IDC_COMBO_BBFORMAT, (LPVOID)pDeviceOptions->BackBufferFormat, D3DFormatToString(pDeviceOptions->BackBufferFormat));
                if (GetSettings()->BackBufferFormat == pDeviceOptions->BackBufferFormat)
                    Combo_SelectItemData(IDC_COMBO_BBFORMAT, (LPVOID)pDeviceOptions->BackBufferFormat);
            } // if
        } // if
    } // for

    // If nothing is already selected, select the first item
    if (Combo_GetSelectedItemData(IDC_COMBO_BBFORMAT) == 0 && Combo_GetItemCount(IDC_COMBO_BBFORMAT) > 0)
        Combo_SelectItem(IDC_COMBO_BBFORMAT, 0);
} // AdapterFormatChanged


// ----------------------------------------------------------------------------
// Name : D3DSettingsDlg::ResolutionChanged
// Desc : Triggered when a change of resolution is posted.
// ----------------------------------------------------------------------------
void D3DSettingsDlg::ResolutionChanged()
{
    ULONG i;

    if (m_D3DSettings.Windowed) return;

    // Retrieve the selected adapter
    D3DEnumAdapter * pAdapter = (D3DEnumAdapter*)Combo_GetSelectedItemData(IDC_COMBO_ADAPTER);
    if (pAdapter == 0) 
        return;

    // Update settings with new resolution
    ULONG ulResolutionData = (ULONG)Combo_GetSelectedItemData(IDC_COMBO_RESOLUTION);
    ULONG Width  = LOWORD(ulResolutionData);
    ULONG Height = HIWORD(ulResolutionData);
    GetSettings()->DisplayMode.Width  = Width;
    GetSettings()->DisplayMode.Height = Height;

    // Update refresg rate list based on new resolution
    D3DFORMAT AFormat = (D3DFORMAT)((ULONG)Combo_GetSelectedItemData(IDC_COMBO_AFORMAT));
    Combo_Clear(IDC_COMBO_REFRESH);
    for (i = 0; i < pAdapter->Modes.size(); i++)
    {
        D3DDISPLAYMODE Mode = pAdapter->Modes[ i ];
        // Does the mode match ?
        if (Mode.Format == AFormat && Mode.Width == Width && Mode.Height == Height)
        {
            TCHAR strRefreshRate[50];
            _sntprintf(strRefreshRate, 50, _T("%d Hz"), Mode.RefreshRate);
            strRefreshRate[49] = 0;

            // Is this already in the list ?
            if (!Combo_FindText(IDC_COMBO_REFRESH, strRefreshRate))
            {
                Combo_ItemAdd(IDC_COMBO_REFRESH, (LPVOID)Mode.RefreshRate, strRefreshRate);
                if (GetSettings()->DisplayMode.RefreshRate == Mode.RefreshRate)
                    Combo_SelectItemData(IDC_COMBO_REFRESH, (LPVOID)Mode.RefreshRate);
            } // if
        } // if
    } // for

    // If nothing is already selected, select the first item
    if (Combo_GetSelectedItemData(IDC_COMBO_REFRESH) == 0 && Combo_GetItemCount(IDC_COMBO_REFRESH) > 0)
        Combo_SelectItem(IDC_COMBO_REFRESH, 0);
} // ResolutionChanged


// ----------------------------------------------------------------------------
// Name : D3DSettingsDlg::RefreshRateChanged
// Desc : Triggered when a change of refresh rate is posted.
// ----------------------------------------------------------------------------
void D3DSettingsDlg::RefreshRateChanged()
{
    if (m_D3DSettings.Windowed) 
        return;

    // Update settings with new refresh rate
    GetSettings()->DisplayMode.RefreshRate = (ULONG)Combo_GetSelectedItemData(IDC_COMBO_REFRESH);
} // RefreshRateChanged


// ----------------------------------------------------------------------------
// Name : D3DSettingsDlg::BackBufferFormatChanged
// Desc : Triggered when a change of backbuffer format is posted.
// ----------------------------------------------------------------------------
void D3DSettingsDlg::BackBufferFormatChanged()
{
    ULONG i, j;

    D3DEnumDevice * pDevice = (D3DEnumDevice*)Combo_GetSelectedItemData(IDC_COMBO_DEVICE);
    if (!pDevice) 
        return;

    // Get selected formats
    D3DFORMAT AFormat  = (D3DFORMAT)((ULONG)Combo_GetSelectedItemData(IDC_COMBO_AFORMAT ));
    D3DFORMAT BBFormat = (D3DFORMAT)((ULONG)Combo_GetSelectedItemData(IDC_COMBO_BBFORMAT));

    // Loop through each option and update remaining list items.
    for (i = 0; i < pDevice->Options.size(); i++)
    {
        D3DEnumDeviceOptions * pDeviceOptions = pDevice->Options[ i ];

        // Is this our selected mode ?
        if (pDeviceOptions->Windowed         == m_D3DSettings.Windowed &&
             pDeviceOptions->AdapterFormat    == AFormat &&
             pDeviceOptions->BackBufferFormat == BBFormat)
        {
            // Update settings with new options details
            GetSettings()->BackBufferFormat = BBFormat;
            
            // Update depth format combo box
            Combo_Clear(IDC_COMBO_DSFORMAT);
            for (j = 0; j < pDeviceOptions->DepthFormats.size(); j++)
            {
                D3DFORMAT Format = pDeviceOptions->DepthFormats[ j ];
                Combo_ItemAdd(IDC_COMBO_DSFORMAT, (LPVOID)Format, D3DFormatToString(Format));

                // If this is a setting we already have set, select it in the combo
                if (Format == GetSettings()->DepthStencilFormat)
                    Combo_SelectItemData(IDC_COMBO_DSFORMAT, (LPVOID)Format);
            } // for

            // If nothing is already selected, select the first item
            if (Combo_GetSelectedItemData(IDC_COMBO_DSFORMAT) == 0 && Combo_GetItemCount(IDC_COMBO_DSFORMAT) > 0)
                Combo_SelectItem(IDC_COMBO_DSFORMAT, 0);

            // Update MultiSample type combo
            Combo_Clear(IDC_COMBO_MSTYPE);
            for (j = 0; j < pDeviceOptions->MultiSampleTypes.size(); j++)
            {
                D3DMULTISAMPLE_TYPE Type = pDeviceOptions->MultiSampleTypes[ j ];
                Combo_ItemAdd(IDC_COMBO_MSTYPE, (LPVOID)Type, MultisampleTypeToString(Type));

                // If this is a setting we already have set, select it in the combo
                if (Type == GetSettings()->MultisampleType)
                    Combo_SelectItemData(IDC_COMBO_MSTYPE, (LPVOID)Type);
            } // for

            // If nothing is already selected, select the first item
            if (Combo_GetSelectedItemData(IDC_COMBO_MSTYPE) == 0 && Combo_GetItemCount(IDC_COMBO_MSTYPE) > 0)
                Combo_SelectItem(IDC_COMBO_MSTYPE, 0);

            // Update VertexProcessing type combo
            Combo_Clear(IDC_COMBO_VPTYPE);
            for (j = 0; j < pDeviceOptions->VertexProcessingTypes.size(); j++)
            {
                VERTEXPROCESSING_TYPE Type = pDeviceOptions->VertexProcessingTypes[ j ];
                Combo_ItemAdd(IDC_COMBO_VPTYPE, (LPVOID)Type, VertexProcessingTypeToString(Type));

                // If this is a setting we already have set, select it in the combo
                if (Type == GetSettings()->VertexProcessingType)
                    Combo_SelectItemData(IDC_COMBO_VPTYPE, (LPVOID)Type);
            } // for

            // If nothing is already selected, select the first item
            if (Combo_GetSelectedItemData(IDC_COMBO_VPTYPE) == 0 && Combo_GetItemCount(IDC_COMBO_VPTYPE) > 0)
                Combo_SelectItem(IDC_COMBO_VPTYPE, 0);

            // Update PresentInterval combo
            Combo_Clear(IDC_COMBO_PINTERVAL);
            for (j = 0; j < pDeviceOptions->PresentIntervals.size(); j++)
            {
                ULONG Interval = pDeviceOptions->PresentIntervals[ j ];
                Combo_ItemAdd(IDC_COMBO_PINTERVAL, (LPVOID)Interval, PresentIntervalToString(Interval));

                // If this is a setting we already have set, select it in the combo
                if (Interval == GetSettings()->PresentInterval)
                    Combo_SelectItemData(IDC_COMBO_PINTERVAL, (LPVOID)Interval);
            } // for

            // If nothing is already selected, select the first item
            if (Combo_GetSelectedItemData(IDC_COMBO_PINTERVAL) == 0 && Combo_GetItemCount(IDC_COMBO_PINTERVAL) > 0)
                Combo_SelectItem(IDC_COMBO_PINTERVAL, 0);

            // No need to process further
            break;
        } // if
    } // for
} // BackBufferFormatChanged


// ----------------------------------------------------------------------------
// Name : D3DSettingsDlg::DepthStencilFormatChanged
// Desc : Triggered when a change of depth stencil buffer format is posted.
// ----------------------------------------------------------------------------
void D3DSettingsDlg::DepthStencilFormatChanged()
{
    D3DFORMAT Format = (D3DFORMAT)((ULONG)Combo_GetSelectedItemData(IDC_COMBO_DSFORMAT));

    // Update settings with new format
    GetSettings()->DepthStencilFormat = Format;
} // DepthStencilFormatChanged


// ----------------------------------------------------------------------------
// Name : D3DSettingsDlg::MultisampleTypeChanged
// Desc : Triggered when a change of multisample type is posted.
// ----------------------------------------------------------------------------
void D3DSettingsDlg::MultisampleTypeChanged()
{
    ULONG                   i;
    D3DMULTISAMPLE_TYPE     MSType;
    MSType = (D3DMULTISAMPLE_TYPE)((ULONG)Combo_GetSelectedItemData(IDC_COMBO_MSTYPE));

    // Update settings with new type
    GetSettings()->MultisampleType = MSType;

    // Find our selected device options
    D3DEnumDevice * pDevice = (D3DEnumDevice*)Combo_GetSelectedItemData(IDC_COMBO_DEVICE);
    if (!pDevice) 
        return;

    D3DEnumDeviceOptions * pDeviceOptions = 0;
    for (i = 0; i < pDevice->Options.size(); i++)
    {
        pDeviceOptions = pDevice->Options[ i ];

        // Is this our selected mode ?
        if (pDeviceOptions->Windowed         == m_D3DSettings.Windowed &&
            pDeviceOptions->AdapterFormat    == GetSettings()->DisplayMode.Format &&
            pDeviceOptions->BackBufferFormat == GetSettings()->BackBufferFormat) break;
        
        // Reset to 0 (used to determine if none was found)
        pDeviceOptions = 0;
    } //for

    // Was any option set found ?
    if (!pDeviceOptions) 
        return;

    // Find the maximum quality for this type
    ULONG MaxQuality = 0;
    for (i = 0; i < pDeviceOptions->MultiSampleTypes.size(); i++)
    {
        D3DMULTISAMPLE_TYPE Type = pDeviceOptions->MultiSampleTypes[ i ];
        if (Type == MSType) 
        {
            MaxQuality = pDeviceOptions->MultiSampleQuality[ i ];
            break;
        } // if
    } // for

    // Update multi-sample quality combo
    Combo_Clear(IDC_COMBO_MSQUALITY);
    for (i = 0; i < MaxQuality; i++)
    {
        TCHAR strQuality[50];
        _sntprintf(strQuality, 50, _T("%d"), i);
        strQuality[49] = 0;

        // Add it to the combo
        Combo_ItemAdd(IDC_COMBO_MSQUALITY, (LPVOID)i, strQuality);

        // If this is a setting we already have set, select it in the combo
        if (i == GetSettings()->MultisampleQuality)
            Combo_SelectItemData(IDC_COMBO_MSQUALITY, (LPVOID)i);
    } // for

    // If nothing is already selected, select the first item
    if (Combo_GetSelectedItemData(IDC_COMBO_MSQUALITY) == 0 && Combo_GetItemCount(IDC_COMBO_MSQUALITY) > 0)
        Combo_SelectItem(IDC_COMBO_MSQUALITY, 0);
} // MultisampleTypeChanged


// ----------------------------------------------------------------------------
// Name : D3DSettingsDlg::MultisampleQualityChanged
// Desc : Triggered when a change of multisample quality is posted.
// ----------------------------------------------------------------------------
void D3DSettingsDlg::MultisampleQualityChanged()
{
    ULONG MSQuality = (ULONG)Combo_GetSelectedItemData(IDC_COMBO_MSQUALITY);

    // Update settings with new quality
    GetSettings()->MultisampleQuality = MSQuality;
} // MultisampleQualityChanged


// ----------------------------------------------------------------------------
// Name : D3DSettingsDlg::VertexProcessingChanged
// Desc : Triggered when a change of vertex processing type is posted.
// ----------------------------------------------------------------------------
void D3DSettingsDlg::VertexProcessingChanged()
{
    VERTEXPROCESSING_TYPE VPType;
    VPType = (VERTEXPROCESSING_TYPE)((ULONG)Combo_GetSelectedItemData(IDC_COMBO_VPTYPE));

    // Update settings with new type
    GetSettings()->VertexProcessingType = VPType;
} // VertexProcessingChanged


// ----------------------------------------------------------------------------
// Name : D3DSettingsDlg::PresentIntervalChanged
// Desc : Triggered when a change of presentation interval is posted.
// ----------------------------------------------------------------------------
void D3DSettingsDlg::PresentIntervalChanged()
{
    ULONG Interval = (ULONG)Combo_GetSelectedItemData(IDC_COMBO_PINTERVAL);

    // Update settings with new interval
    GetSettings()->PresentInterval = Interval;
} // PresentIntervalChanged


// ----------------------------------------------------------------------------
// Name : D3DSettingsDlg::Combo_ItemAdd
// Desc : Adds the specified item to the combo box passed.
// ----------------------------------------------------------------------------
void D3DSettingsDlg::Combo_ItemAdd(ULONG ComboID, LPVOID pData, LPCTSTR pStrDesc)
{
    // Get the control handle
    HWND hwndCtrl = GetDlgItem(m_hWndDlg, ComboID);

    // Add a new 'String' item to the combo box
    DWORD dwItem  = ComboBox_AddString(hwndCtrl, pStrDesc);

    // Set it's additional data
    ComboBox_SetItemData(hwndCtrl, dwItem, pData);
} // Combo_ItemAdd


// ----------------------------------------------------------------------------
// Name : D3DSettingsDlg::Combo_GetSelectedItemData
// Desc : Returns the item data of the selected item in the combo box passed.
// ----------------------------------------------------------------------------
LPVOID D3DSettingsDlg::Combo_GetSelectedItemData(ULONG ComboID)
{
    // Get the control handle
    HWND hwndCtrl = GetDlgItem(m_hWndDlg, ComboID);

    // Retrieve the currently selected item
    int iItem  = ComboBox_GetCurSel(hwndCtrl);
    
    // Validate
    if (iItem < 0) 
        return 0;
    
    // Return the data pointer
    return (LPVOID)ComboBox_GetItemData(hwndCtrl, iItem);
} // Combo_GetSelectedItemData


// ----------------------------------------------------------------------------
// Name : D3DSettingsDlg::Combo_GetItemCount 
// Desc : Returns the number of items contained in the combo box passed.
// ----------------------------------------------------------------------------
ULONG D3DSettingsDlg::Combo_GetItemCount(ULONG ComboID)
{
    // Get the control handle
    HWND hwndCtrl = GetDlgItem(m_hWndDlg, ComboID);

    // Return the number of items
    return ComboBox_GetCount(hwndCtrl);
} // Combo_GetItemCount


// ----------------------------------------------------------------------------
// Name : D3DSettingsDlg::Combo_SelectItem 
// Desc : Selects the item based on it's position within the combo array.
// ----------------------------------------------------------------------------
void D3DSettingsDlg::Combo_SelectItem(ULONG ComboID, ULONG Index)
{
    // Get the control handle
    HWND hwndCtrl = GetDlgItem(m_hWndDlg, ComboID);

    // Set the current selection
    ComboBox_SetCurSel(hwndCtrl, Index);

    // Trigger a combo box selection change message
    PostMessage(m_hWndDlg, WM_COMMAND, MAKEWPARAM(ComboID, CBN_SELCHANGE), (LPARAM)hwndCtrl);
} // Combo_SelectItem


// ----------------------------------------------------------------------------
// Name : D3DSettingsDlg::Combo_SelectItemData 
// Desc : Selects the item based on it's data within the combo array.
// ----------------------------------------------------------------------------
void D3DSettingsDlg::Combo_SelectItemData(ULONG ComboID, LPVOID pData)
{
    // Get the control handle
    HWND hwndCtrl = GetDlgItem(m_hWndDlg, ComboID);

    // Loop through each item.
    ULONG Count = ComboBox_GetCount(hwndCtrl);
    for (ULONG i = 0; i < Count; i++)
    {
        // Does it match
        if ((LPVOID)ComboBox_GetItemData(hwndCtrl, i) == pData)
        {
            // Set the current selection
            ComboBox_SetCurSel(hwndCtrl, i);

            // Trigger a combo box selection change message
            PostMessage(m_hWndDlg, WM_COMMAND, MAKEWPARAM(ComboID, CBN_SELCHANGE), (LPARAM)hwndCtrl);

            // Bail
            return;
        } // if
    } // for
} // Combo_SelectItemData


// ----------------------------------------------------------------------------
// Name : D3DSettingsDlg::Combo_Clear 
// Desc : Clear the contents of the combo box passed.
// ----------------------------------------------------------------------------
void D3DSettingsDlg::Combo_Clear(ULONG ComboID)
{
    // Get the control handle
    HWND hwndCtrl = GetDlgItem(m_hWndDlg, ComboID);

    // Reset the combo
    ComboBox_ResetContent(hwndCtrl);
} // Combo_Clear


// ----------------------------------------------------------------------------
// Name: D3DSettingsDlg::Combo_FindText 
// Desc: Searches through the combo box to see if the text exists.
// ----------------------------------------------------------------------------
bool D3DSettingsDlg::Combo_FindText(ULONG ComboID, LPCTSTR pStrText)
{
    TCHAR strItem[255];
    
    // Get the control handle
    HWND hwndCtrl = GetDlgItem(m_hWndDlg, ComboID);

    // Loop through each item.
    ULONG Count = ComboBox_GetCount(hwndCtrl);
    for (ULONG i = 0; i < Count; i++)
    {
        // Skip if greater than max size
        if (ComboBox_GetLBTextLen(hwndCtrl, i) >= 255) 
            continue;

        // Retrieve the text
        ComboBox_GetLBText(hwndCtrl, i, strItem);
        
        // Does it match ?
        if (lstrcmp(strItem, pStrText) == 0) 
            return true;
    
    } // for

    // No match found
    return false;
} // Combo_FindText


// -- EOF
