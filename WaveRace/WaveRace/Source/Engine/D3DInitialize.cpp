// ----------------------------------------------------------------------------
// File: D3DInitialize.cpp
// Desc: Direct3D Enumeration and initialization classes.
// Auth: Michael Petrou
// Note: Thanks to Adam Hoult & Gary Simmons from GameInstitute.com for the 
//       great code that was so easily adapted to work in my application.
//
// Adapters (Array)
//    |
//    |---- Adapter Ordinal
//    |
//    |---- Adapter Identifier
//    |
//    |---- Display Modes (Array)
//    |           |
//    |           |------- Resolution
//    |           |
//    |           |------- Format / ColorDepth
//    |           |
//    |           |------- Refresh Rate
//    |           
//    |           
//    |---- Device Types (Array)
//                |
//                |------- Device Type - HAL / SW / REF
//                |
//                |------- Device Capabilities
//                |
//                |------- Device Options (Array)
//                               |
//                               |------- Adapter Format
//                               |
//                               |------- Back Buffer Format
//                               |
//                               |------- Is Windowed Mode
//                               |
//                               |------- Depth / Stencil Formats (Array)
//                               |
//                               |------- Multi-Sample Types (Array)   <--\
//                               |                                         > Linked
//                               |------- Multi-Sample Quality (Array) <--/
//                               |
//                               |------- Vertex Processing Types (Array)
//                               |
//                               |------- Presentation Intervals (Array)
//           
// (C) Copyright:   2004
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// D3DInitialize specific includes
// ----------------------------------------------------------------------------
#include "Engine/D3DInitialize.h"


// ----------------------------------------------------------------------------
// D3DInitialize specific constants
// ----------------------------------------------------------------------------
const ULONG                 ValidAdapterFormatCount = 3;
const ULONG                 BackBufferFormatCount   = 11;
const ULONG                 DeviceTypeCount         = 3;
const ULONG                 MultiSampleTypeCount    = 17;
const ULONG                 DepthStencilFormatCount = 6;
const ULONG                 PresentIntervalCount    = 6;
const D3DFORMAT             ValidAdapterFormats[3]  = { D3DFMT_X8R8G8B8, D3DFMT_X1R5G5B5, D3DFMT_R5G6B5 };
const D3DDEVTYPE            DeviceTypes[3]          = { D3DDEVTYPE_HAL, D3DDEVTYPE_SW, D3DDEVTYPE_REF };
const D3DFORMAT             BackBufferFormats[11]   = { D3DFMT_R8G8B8, D3DFMT_A8R8G8B8, D3DFMT_X8R8G8B8, 
                                                        D3DFMT_R5G6B5, D3DFMT_A1R5G5B5, D3DFMT_X1R5G5B5,
                                                        D3DFMT_R3G3B2, D3DFMT_A8R3G3B2, D3DFMT_X4R4G4B4, 
                                                        D3DFMT_A4R4G4B4, D3DFMT_A2B10G10R10 };
const D3DMULTISAMPLE_TYPE   MultiSampleTypes[17]    = { D3DMULTISAMPLE_NONE      , D3DMULTISAMPLE_NONMASKABLE,
                                                        D3DMULTISAMPLE_2_SAMPLES , D3DMULTISAMPLE_3_SAMPLES,
                                                        D3DMULTISAMPLE_4_SAMPLES , D3DMULTISAMPLE_5_SAMPLES,
                                                        D3DMULTISAMPLE_6_SAMPLES , D3DMULTISAMPLE_7_SAMPLES,
                                                        D3DMULTISAMPLE_8_SAMPLES , D3DMULTISAMPLE_9_SAMPLES,
                                                        D3DMULTISAMPLE_10_SAMPLES, D3DMULTISAMPLE_11_SAMPLES,
                                                        D3DMULTISAMPLE_12_SAMPLES, D3DMULTISAMPLE_13_SAMPLES,
                                                        D3DMULTISAMPLE_14_SAMPLES, D3DMULTISAMPLE_15_SAMPLES,
                                                        D3DMULTISAMPLE_16_SAMPLES };
const D3DFORMAT             DepthStencilFormats[6]  = { D3DFMT_D32, D3DFMT_D24X4S4, D3DFMT_D24X8, 
                                                        D3DFMT_D24S8, D3DFMT_D16, D3DFMT_D15S1 };
const ULONG                 PresentIntervals[6]     = { D3DPRESENT_INTERVAL_IMMEDIATE, D3DPRESENT_INTERVAL_DEFAULT,
                                                        D3DPRESENT_INTERVAL_ONE, D3DPRESENT_INTERVAL_TWO,
                                                        D3DPRESENT_INTERVAL_THREE, D3DPRESENT_INTERVAL_FOUR };


// ----------------------------------------------------------------------------
// Name: D3DEnumAdapter::~D3DEnumAdapter
// Desc: Destructor
// ----------------------------------------------------------------------------
D3DEnumAdapter::~D3DEnumAdapter()
{
    // Release all devices
    for (ULONG i = 0; i < Devices.size(); i++)
    {
        // Release Device
        if (Devices[i])
            delete Devices[i];
    } // for

    // Clear Vectors
    Modes.clear();
    Devices.clear();
} // ~D3DEnumAdapter


// ----------------------------------------------------------------------------
// Name: D3DEnumDevice::~D3DEnumDevice
// Desc: Destructor
// ----------------------------------------------------------------------------
D3DEnumDevice::~D3DEnumDevice()
{
    for (ULONG i = 0; i < Options.size(); i++)
    {
        // Release Options
        if (Options[i]) 
            delete Options[i];
    } // for

    // Clear Vectors
    Options.clear();
} // ~D3DEnumDevice


// ----------------------------------------------------------------------------
// Name: D3DEnumDeviceOptions::~D3DEnumDeviceOptions
// Desc: Destructor
// ----------------------------------------------------------------------------
D3DEnumDeviceOptions::~D3DEnumDeviceOptions()
{
    // Clear Vectors
    DepthFormats.clear();
    MultiSampleTypes.clear();
    PresentIntervals.clear();
    VertexProcessingTypes.clear();
} // ~D3DEnumDeviceOptions


// ----------------------------------------------------------------------------
// Name: D3DInitialize::D3DInitialize
// Desc: Constructor
// ----------------------------------------------------------------------------
D3DInitialize::D3DInitialize()
{
	// Reset / Clear all required values
    m_pD3D          = 0;
    m_pD3DDevice    = 0;
    m_lock_vsync    = false;
} // D3DInitialize


// ----------------------------------------------------------------------------
// Name: D3DInitialize::~D3DInitialize
// Desc: Destructor
// ----------------------------------------------------------------------------
D3DInitialize::~D3DInitialize()
{
	// Clean up D3D Objects
    if (m_pD3D) m_pD3D->Release();
    if (m_pD3DDevice) 
        m_pD3DDevice->Release();

    // Reset the pointers
    m_pD3D          = 0;
    m_pD3DDevice    = 0;

    // Release all enumerated adapters
    for (ULONG i = 0; i < m_vpAdapters.size(); i++)
    {
        // Release Adapter
        if (m_vpAdapters[i])
            delete m_vpAdapters[i];
    } // for

    // Clear Vectors
    m_vpAdapters.clear();
} // ~D3DInitialize


// ----------------------------------------------------------------------------
// Name: D3DInitialize::Enumerate
// Desc: This function must be called first to enumerate all available devices, 
//       adapters, modes and formats, prior to initialization.
// Parm: LPDIRECT3D9 pD3D - the device
// Retn: HRESULT          - the result of enumeration
// ----------------------------------------------------------------------------
HRESULT D3DInitialize::Enumerate(LPDIRECT3D9 pD3D, bool lock_vsync)
{
    HRESULT hRet;
 
    // Store the D3D Object
    m_pD3D = pD3D;
    if (!m_pD3D)
        return E_FAIL;

    m_lock_vsync = lock_vsync;

    // AddRef on the D3D9 Object so we can auto cleanup
    m_pD3D->AddRef();

    // Enumerate the adapters
    if (FAILED(hRet = EnumerateAdapters())) 
        return hRet;

    // Success
    return S_OK;
} // Enumerate


// ----------------------------------------------------------------------------
// Name: D3DInitialize::CreateDisplay
// Desc: Creates the display devices ready for rendering.
// Parm: D3DSettings& D3DSettings - the settings
// Parm: ULONG Flags              - the flags
// Parm: HWND hWnd                - the window
// Parm: WNDPROC pWndProc         - the windows procedure
// Parm: LPCTSTR Title            - the application title
// Parm: ULONG Width              - the window width
// Parm: ULONG Height             - the window height
// Parm: LPVOID lParam            - the param 1
// Retn: HRESULT                  - S_OK if successful
// ----------------------------------------------------------------------------
HRESULT D3DInitialize::CreateDisplay(D3DSettings& D3DSettings, ULONG Flags, HWND hWnd, WNDPROC pWndProc, 
                                     LPCTSTR Title, ULONG Width, ULONG Height, LPVOID lParam)
{
    ULONG CreateFlags                   = 0;
    D3DSettings::Settings *pSettings    = D3DSettings.GetSettings();
    
    if (!hWnd)
    {
        // Register the new windows window class.
        WNDCLASS			wc;	
	    wc.style			= CS_BYTEALIGNCLIENT | CS_HREDRAW | CS_VREDRAW;
	    wc.lpfnWndProc		= pWndProc;
	    wc.cbClsExtra		= 0;
	    wc.cbWndExtra		= 0;
	    wc.hInstance		= (HINSTANCE)GetModuleHandle(0);
        wc.hIcon			= 0;
	    wc.hCursor			= LoadCursor(0, IDC_ARROW);
	    wc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	    wc.lpszMenuName		= 0;
	    wc.lpszClassName	= Title;
	    RegisterClass(&wc);

        ULONG Left  = CW_USEDEFAULT, Top = CW_USEDEFAULT;
        ULONG Style = WS_OVERLAPPEDWINDOW;

        // Create the rendering window
        if (!D3DSettings.Windowed)
        {
            Left   = 0; Top = 0;
            Width  = pSettings->DisplayMode.Width;
            Height = pSettings->DisplayMode.Height;
            Style  = WS_VISIBLE | WS_POPUP;
        } // if

        // Create the window
        m_hWnd = CreateWindow(Title, Title, Style, Left, Top, Width, Height, 0, 0, wc.hInstance, lParam);

        // Bail on error
        if (!m_hWnd)
            return E_FAIL;

    } // if
    else
    {
        // Store HWND
        m_hWnd = hWnd;
        
        // Setup styles based on windowed / fullscreen mode
        if (!D3DSettings.Windowed)
        {
            SetMenu(m_hWnd, 0);
            SetWindowLong(m_hWnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);
            SetWindowPos(m_hWnd, 0, 0, 0, pSettings->DisplayMode.Width, pSettings->DisplayMode.Height, SWP_NOZORDER);
        } // if
        else
        {
            // Get the windows client rectangle
            RECT rc;
            GetWindowRect(hWnd, &rc);

            // Setup the window properties
            SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
            SetWindowPos(hWnd, HWND_NOTOPMOST, rc.left, rc.top, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOACTIVATE | SWP_SHOWWINDOW);
        } // if
    } // else

    // Build our present parameters
    D3DPRESENT_PARAMETERS d3dpp = BuildPresentParameters(D3DSettings);
    
    // Build our creation flags
    CreateFlags = Flags;
    if (pSettings->VertexProcessingType == PURE_HARDWARE_VP)
        CreateFlags |= D3DCREATE_PUREDEVICE | D3DCREATE_HARDWARE_VERTEXPROCESSING;
    else if (pSettings->VertexProcessingType == HARDWARE_VP)
        CreateFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
    else if (pSettings->VertexProcessingType == MIXED_VP)
        CreateFlags |= D3DCREATE_MIXED_VERTEXPROCESSING;
    else if (pSettings->VertexProcessingType == SOFTWARE_VP)
        CreateFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

    // Create the device
    m_pD3DDevice = 0;
    HRESULT hRet = m_pD3D->CreateDevice(pSettings->AdapterOrdinal, pSettings->DeviceType,
                                         m_hWnd, CreateFlags, &d3dpp, &m_pD3DDevice);
    // Did the creation fail
    if (FAILED(hRet)) 
    {
        if (m_pD3DDevice) m_pD3DDevice->Release();
        m_pD3DDevice = 0;
        return hRet;
    } // if

    // Success
    return S_OK;
} // CreateDisplay


// ----------------------------------------------------------------------------
// Name: D3DInitialize::ResetDisplay
// Desc: Reset the display device, and optionally the window etc.
// Parm: LPDIRECT3DDEVICE9 pD3DDevice - the device
// Parm: D3DSettings& D3DSettings     - the settings
// Parm: HWND hWnd                    - the window
// Retn: HRESULT                      - S_OK if successful
// ----------------------------------------------------------------------------
HRESULT D3DInitialize::ResetDisplay(LPDIRECT3DDEVICE9 pD3DDevice, D3DSettings& D3DSettings, HWND hWnd)
{   
    D3DPRESENT_PARAMETERS d3dpp         = BuildPresentParameters(D3DSettings);
    D3DSettings::Settings *pSettings    = D3DSettings.GetSettings();

    if (hWnd)
    {
        // Setup styles based on windowed / fullscreen mode
        if (!D3DSettings.Windowed)
        {
            SetMenu(hWnd, 0);
            SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);
            SetWindowPos(hWnd, 0, 0, 0, pSettings->DisplayMode.Width, pSettings->DisplayMode.Height, SWP_NOZORDER);
        } // if
        else
        {
            SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
            SetWindowPos(hWnd, HWND_NOTOPMOST, 50, 50, 400, 400, SWP_NOACTIVATE | SWP_SHOWWINDOW);
        } // else
    } // if

    // Reset the device
    HRESULT hRet = pD3DDevice->Reset(&d3dpp);
    if (FAILED(hRet)) 
        return hRet;

    // Success
    return S_OK;
} // ResetDisplay


// ----------------------------------------------------------------------------
// Name: D3DInitialize::EnumerateAdapters
// Desc: Enumerates the individual adapters contained within the user machine.
// Retn: HRESULT - true if succeeded
// ----------------------------------------------------------------------------
HRESULT D3DInitialize::EnumerateAdapters()
{
    HRESULT hRet;

    // Store the number of available adapters
    ULONG nAdapterCount = m_pD3D->GetAdapterCount();

    // Loop through each adapter
    for (ULONG i = 0; i < nAdapterCount; i++)
    {
        D3DEnumAdapter * pAdapter = new D3DEnumAdapter;
        if (!pAdapter) 
            return E_OUTOFMEMORY;

        // Store adapter ordinal
        pAdapter->Ordinal = i;

        // Retrieve adapter identifier
        m_pD3D->GetAdapterIdentifier(i, 0, &pAdapter->Identifier);

        // Enumerate all display modes for this adapter
        if (FAILED(hRet = EnumerateDisplayModes(pAdapter)) ||
            FAILED(hRet = EnumerateDevices(pAdapter))) 
        {
            delete pAdapter;
            if (hRet == E_ABORT) continue; else return hRet;
        } // if

        // Add this adapter the list
        try 
        {
            m_vpAdapters.push_back(pAdapter);
        } // try
        catch (...)
        {
            delete pAdapter;
            return E_OUTOFMEMORY;
        } // catch
    } // for

    // Success
    return S_OK;
} // EnumerateAdapters


// ----------------------------------------------------------------------------
// Name: D3DInitialize::EnumerateDisplayModes
// Desc: Enumerates all of the display modes for the adapter specified.
// Parm: D3DEnumAdapter * pAdapter - the adapter enumerator
// Retn: HRESULT                   - S_OK if successful
// ----------------------------------------------------------------------------
HRESULT D3DInitialize::EnumerateDisplayModes(D3DEnumAdapter * pAdapter)
{
    HRESULT         hRet;
    ULONG           i, j;
    D3DDISPLAYMODE  Mode;
   
    // Loop through each valid 'Adapter' format.
    for (i = 0; i < ValidAdapterFormatCount; i++)
    {
        // Retrieve the number of valid modes for this format
        ULONG nModeCount = m_pD3D->GetAdapterModeCount(pAdapter->Ordinal, ValidAdapterFormats[i]);
        if (nModeCount == 0)
            continue;

        // Loop through each display mode for this format
        for (j = 0; j < nModeCount; j++)
        {
            // Retrieve the display mode
            hRet = m_pD3D->EnumAdapterModes(pAdapter->Ordinal, ValidAdapterFormats[i], j, &Mode);
            if (FAILED(hRet))
                return hRet;

            // Is supported by user ?
            if (!ValidateDisplayMode(Mode))
                continue;

            // Add this mode to the adapter
            try 
            { 
                pAdapter->Modes.push_back(Mode); 
            } // try
            catch(...) 
            { 
                return E_OUTOFMEMORY;
            } // catch
        } // for
    } // for

    // Success
    return (pAdapter->Modes.size() == 0) ? E_ABORT : S_OK;
} // EnumerateDisplayModes

  
// ----------------------------------------------------------------------------
// Name: D3DInitialize::EnumerateDevices
// Desc: Enumerates the valid device types for the specified adapter.
// Parm: D3DEnumAdapter * pAdapter - the adapter enumerator
// Retn: HRESULT                   - S_OK if successful
// ----------------------------------------------------------------------------
HRESULT D3DInitialize::EnumerateDevices(D3DEnumAdapter * pAdapter)
{
    ULONG    i;
    HRESULT  hRet;
    D3DCAPS9 Caps;

    // Loop through each device type (HAL, SW, REF)
    for (i = 0; i < DeviceTypeCount; i++)
    {
        // Retrieve device caps (on failure, device not generally available)
        if (FAILED(m_pD3D->GetDeviceCaps(pAdapter->Ordinal, DeviceTypes[i], &Caps)))
            continue;

        // Supported by user ?
        if (!ValidateDevice(DeviceTypes[ i ], Caps))
            continue;

        // Allocate a new device
        D3DEnumDevice * pDevice = new D3DEnumDevice;
        if (!pDevice)
            return E_OUTOFMEMORY;

        // Store device information
        pDevice->DeviceType = DeviceTypes[i];
        pDevice->Caps       = Caps;

        // Retrieve various init options for this device
        if (FAILED(hRet = EnumerateDeviceOptions(pDevice, pAdapter))) 
        { 
            delete pDevice; 
            if (hRet == E_ABORT)
                continue; 
            else 
                return hRet; 
        } // if

        // Add it to our adapter list
        try 
        { 
            pAdapter->Devices.push_back(pDevice);
        } // try
        catch (...)
        {
            delete pDevice;
            return E_OUTOFMEMORY;
        } // catch
    } // for

    // Success
    return (pAdapter->Devices.size() == 0) ? E_ABORT : S_OK;
} // EnumerateDevices


// ----------------------------------------------------------------------------
// Name: D3DInitialize::EnumerateDeviceOptions
// Desc: Enumerates the various initialization options available for the device 
//       specified, such as back buffer formats etc.
// Parm: D3DEnumDevice * pDevice    - the device enumerator
// Parm: D3DEnumAdapter * pAdapter  - the adapter enaumerator
// Retn: HRESULT                    - S_OK if successful
// ----------------------------------------------------------------------------
HRESULT D3DInitialize::EnumerateDeviceOptions(D3DEnumDevice * pDevice, D3DEnumAdapter * pAdapter)
{
    HRESULT     hRet;
    ULONG       i, j, k;
    bool        Windowed;
    D3DFORMAT   AdapterFormats[ValidAdapterFormatCount];
    ULONG       AdapterFormatCount = 0;
    D3DFORMAT   AdapterFormat, BackBufferFormat;

    // Build a list of all the formats used by the adapter
    for (i = 0; i < pAdapter->Modes.size(); i++)
    {
        // Already added to the list ?
        for (j = 0; j < AdapterFormatCount; j++) 
            if (pAdapter->Modes[i].Format == AdapterFormats[j]) 
                break;

        // Add it to the list if not existing.
        if (j == AdapterFormatCount)
            AdapterFormats[AdapterFormatCount++] = pAdapter->Modes[i].Format;
    } // for

    // Loop through each adapter format available
    for (i = 0; i < AdapterFormatCount; i++)
    {
        // Store Adapter Format 
        AdapterFormat = AdapterFormats[i];

        // Loop through all valid back buffer formats
        for (j = 0; j < BackBufferFormatCount; j++)
        {
            // Store Back Buffer Format 
            BackBufferFormat = BackBufferFormats[j];

            // Test Windowed / Fullscreen Modes
            for (k = 0; k < 2; k++)
            {
                // Select windowed / fullscreen
                if (k == 0)
                    Windowed = false; 
                else 
                    Windowed = true;

                // Skip if this is not a valid device type
                if (FAILED(m_pD3D->CheckDeviceType(pAdapter->Ordinal, pDevice->DeviceType, 
                    AdapterFormat, BackBufferFormat, Windowed)))
                    continue;

                // Allocate a new device options set
                D3DEnumDeviceOptions * pDeviceOptions = new D3DEnumDeviceOptions;
                if (!pDeviceOptions) 
                    return E_OUTOFMEMORY;

                // Store device option details
                pDeviceOptions->AdapterOrdinal   = pAdapter->Ordinal;
                pDeviceOptions->DeviceType       = pDevice->DeviceType;
                pDeviceOptions->AdapterFormat    = AdapterFormat;
                pDeviceOptions->BackBufferFormat = BackBufferFormat;
                pDeviceOptions->Caps             = pDevice->Caps;
                pDeviceOptions->Windowed         = Windowed;

                // Is this option set supported by the user ?
                if (!ValidateDeviceOptions(BackBufferFormat, Windowed))
                {
                    delete pDeviceOptions;
                    continue;
                } // if

                // Enumerate the various options components
                if (FAILED(hRet = EnumerateDepthStencilFormats  (pDeviceOptions)) ||
                    FAILED(hRet = EnumerateMultiSampleTypes     (pDeviceOptions)) ||
                    FAILED(hRet = EnumerateVertexProcessingTypes(pDeviceOptions)) ||
                    FAILED(hRet = EnumeratePresentIntervals     (pDeviceOptions)))
                {
                    // Release our invalid options
                    delete pDeviceOptions;

                    // If returned anything other than abort, this is fatal
                    if (hRet == E_ABORT)
                        continue; 
                    else 
                        return hRet;
                } // if

                // Add this to our device
                try 
                { 
                    pDevice->Options.push_back(pDeviceOptions); 
                } // try
                catch (...)
                {
                    delete pDeviceOptions;
                    return E_OUTOFMEMORY;
                } // catch
            } // for
        } // for
    } // for
        
    // Success
    return (pDevice->Options.size() == 0) ? E_ABORT : S_OK;
} // EnumerateDeviceOptions


// ----------------------------------------------------------------------------
// Name: D3DInitialize::EnumerateDepthStencilFormats
// Desc: Enumerates all the valid depth / stencil formats for this device set.
// Parm: D3DEnumDeviceOptions * pDeviceOptions - the device options
// Retn: HRESULT                               - S_OK if successful
// ----------------------------------------------------------------------------
HRESULT D3DInitialize::EnumerateDepthStencilFormats(D3DEnumDeviceOptions * pDeviceOptions)
{
    ULONG i;

    try
    {
        // Loop through each depth stencil format
        for (i = 0; i < DepthStencilFormatCount; i++)
        {
            // Test to see if this is a valid depth surface format
            if (SUCCEEDED(m_pD3D->CheckDeviceFormat(pDeviceOptions->AdapterOrdinal, pDeviceOptions->DeviceType, 
                pDeviceOptions->AdapterFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, DepthStencilFormats[ i ])))
            {
                // Test to see if this is a valid depth / stencil format for this mode
                if (SUCCEEDED(m_pD3D->CheckDepthStencilMatch(pDeviceOptions->AdapterOrdinal, pDeviceOptions->DeviceType, 
                    pDeviceOptions->AdapterFormat, pDeviceOptions->BackBufferFormat, DepthStencilFormats[ i ])))
                {
                    // Is this supported by the user ?
                    if (ValidateDepthStencilFormat(DepthStencilFormats[ i ]))
                    {
                        // Add this as a valid depthstencil format
                        pDeviceOptions->DepthFormats.push_back(DepthStencilFormats[ i ]);
                    } // if
                } // if
            } // if
        } // for

    } // try
    catch (...)
    {
        return E_OUTOFMEMORY; 
    } // catch

    // Success
    return (pDeviceOptions->DepthFormats.size() == 0) ? E_ABORT : S_OK;
} // EnumerateDepthStencilFormats


// ----------------------------------------------------------------------------
// Name: D3DInitialize::EnumerateMultiSampleTypes
// Desc: Enumerates multi-sample types available for this device set.
// Parm: D3DEnumDeviceOptions * pDeviceOptions - the device options
// Retn: HRESULT                               - true if succeeded
// ----------------------------------------------------------------------------
HRESULT D3DInitialize::EnumerateMultiSampleTypes(D3DEnumDeviceOptions * pDeviceOptions)
{
    ULONG i, Quality;

    try
    {
        // Loop through each multi-sample type
        for (i = 0; i < MultiSampleTypeCount; i++)
        {
            // Check if this multi-sample type is supported
            if (SUCCEEDED(m_pD3D->CheckDeviceMultiSampleType(pDeviceOptions->AdapterOrdinal, pDeviceOptions->DeviceType,
                pDeviceOptions->BackBufferFormat, pDeviceOptions->Windowed, MultiSampleTypes[ i ], &Quality)))
            {
                // Is this supported by the user ?
                if (ValidateMultiSampleType(MultiSampleTypes[ i ]))
                {
                    // Supported, add these to our list
                    pDeviceOptions->MultiSampleTypes.push_back(MultiSampleTypes[i]);
                    pDeviceOptions->MultiSampleQuality.push_back(Quality);
                } // if
            } // if
        } // for
    } // try
    catch (...)
    { 
        return E_OUTOFMEMORY; 
    } // catch

    // Success
    return (pDeviceOptions->MultiSampleTypes.size() == 0) ? E_ABORT : S_OK;
} // EnumerateMultiSampleTypes


// ----------------------------------------------------------------------------
// Name: D3DInitialize::EnumerateVertexProcessingTypes
// Desc: Enumerates all the types of vertex processing available.
// Parm: D3DEnumDeviceOptions * pDeviceOptions - the device options
// Retn: HRESULT                               - S_OK if successful
// ----------------------------------------------------------------------------
HRESULT D3DInitialize::EnumerateVertexProcessingTypes(D3DEnumDeviceOptions * pDeviceOptions)
{
    try
    {
        // If the device supports Hardware T&L
        if (pDeviceOptions->Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
        {
            // If the device can be created as 'Pure'
            if (pDeviceOptions->Caps.DevCaps & D3DDEVCAPS_PUREDEVICE)
            {
                // Supports Pure hardware device ?
                if (ValidateVertexProcessingType(PURE_HARDWARE_VP))
                    pDeviceOptions->VertexProcessingTypes.push_back(PURE_HARDWARE_VP);
            } // if

            // Supports hardware T&L and Mixed by definitiion ?
            if (ValidateVertexProcessingType(HARDWARE_VP))
                pDeviceOptions->VertexProcessingTypes.push_back(HARDWARE_VP);

            if (ValidateVertexProcessingType(MIXED_VP))
                pDeviceOptions->VertexProcessingTypes.push_back(MIXED_VP);

        } // if

        // Always supports software
        if (ValidateVertexProcessingType(SOFTWARE_VP))
            pDeviceOptions->VertexProcessingTypes.push_back(SOFTWARE_VP);

    } // try
    catch (...)
    { 
        return E_OUTOFMEMORY; 
    } // catch

    // Success
    return (pDeviceOptions->VertexProcessingTypes.size() == 0) ? E_ABORT : S_OK;
} // EnumerateVertexProcessingTypes


// ----------------------------------------------------------------------------
// Name: D3DInitialize::EnumeratePresentIntervals
// Desc: Enumerates all the valid present intervals available for this set.
// Parm: D3DEnumDeviceOptions * pDeviceOptions - the device options
// Retn: HRESULT                               - S_OK if successful
// ----------------------------------------------------------------------------
HRESULT D3DInitialize::EnumeratePresentIntervals(D3DEnumDeviceOptions * pDeviceOptions)
{
    ULONG i, Interval;

    try
    {
        // Loop through each presentation interval
        for (i = 0; i < PresentIntervalCount; i++)
        {
            // Store for easy access
            Interval = PresentIntervals[i];

            // If device is windowed, skip anything above ONE
            if (pDeviceOptions->Windowed)
            {
                if (Interval == D3DPRESENT_INTERVAL_TWO   ||
                    Interval == D3DPRESENT_INTERVAL_THREE ||
                    Interval == D3DPRESENT_INTERVAL_FOUR) 
                    continue;
            } // if 

            // DEFAULT is always available, others must be tested
            if (Interval == D3DPRESENT_INTERVAL_DEFAULT)
            {
                pDeviceOptions->PresentIntervals.push_back(Interval);
                continue;
            } // if

            // Supported by the device
            if (pDeviceOptions->Caps.PresentationIntervals & Interval)
            {
                if (ValidatePresentInterval(Interval))
                {
                    if (m_lock_vsync && Interval == D3DPRESENT_INTERVAL_ONE || Interval == D3DPRESENT_INTERVAL_TWO)
                        pDeviceOptions->PresentIntervals.insert(pDeviceOptions->PresentIntervals.begin(), Interval);
                    else
                        pDeviceOptions->PresentIntervals.push_back(Interval);
                } // if
            } // if
        } // for
    } // try 
    catch (...)
    { 
        return E_OUTOFMEMORY; 
    } // catch

    // Success
    return (pDeviceOptions->PresentIntervals.size() == 0) ? E_ABORT : S_OK;
} // EnumeratePresentIntervals


// ----------------------------------------------------------------------------
// Name: D3DInitialize::BuildPresentParameters
// Desc: Builds a set of present parameters from the Settings passed.
// Parm: D3DSettings& D3DSettings - the settings
// Parm: ULONG Flags              - the flags
// Retn: D3DPRESENT_PARAMETERS    - the present params
// ----------------------------------------------------------------------------
D3DPRESENT_PARAMETERS D3DInitialize::BuildPresentParameters(D3DSettings& D3DSettings, ULONG Flags)
{
    D3DPRESENT_PARAMETERS  d3dpp;
    D3DSettings::Settings *pSettings = D3DSettings.GetSettings();
    
    ZeroMemory (&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

    // Fill out our common present parameters
    d3dpp.BackBufferCount           = 1;
    d3dpp.BackBufferFormat          = pSettings->BackBufferFormat;
    d3dpp.Windowed                  = D3DSettings.Windowed;
    d3dpp.MultiSampleType           = pSettings->MultisampleType;
    d3dpp.MultiSampleQuality        = pSettings->MultisampleQuality;
    d3dpp.EnableAutoDepthStencil    = TRUE;
    d3dpp.AutoDepthStencilFormat    = pSettings->DepthStencilFormat;
    d3dpp.PresentationInterval      = pSettings->PresentInterval;
    d3dpp.Flags                     = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL | Flags;
    d3dpp.SwapEffect                = D3DSWAPEFFECT_DISCARD;

    // Is this fullscreen
    if (!d3dpp.Windowed)
    {
        d3dpp.FullScreen_RefreshRateInHz = pSettings->DisplayMode.RefreshRate;
        d3dpp.BackBufferWidth            = pSettings->DisplayMode.Width;
        d3dpp.BackBufferHeight           = pSettings->DisplayMode.Height;
    } // if
    
    // Success
    return d3dpp;
} // BuildPresentParameters


// ----------------------------------------------------------------------------
// Name: D3DInitialize::FindBestWindowedMode
// Desc: Find the best windowed mode, and fill out our D3DSettings structure.
// Parm: D3DSettings & D3DSettings - the settings
// Parm: bool bRequireHAL          - do we require hardware support
// Parm: bool bRequireREF          - do we require the reference dirver
// Retn: bool                      - true if found
// ----------------------------------------------------------------------------
bool D3DInitialize::FindBestWindowedMode(D3DSettings &D3DSettings, bool bRequireHAL, bool bRequireREF)
{
    ULONG                    i, j, k;
    D3DDISPLAYMODE           DisplayMode;
    D3DEnumAdapter          *pBestAdapter   = 0;
    D3DEnumDevice           *pBestDevice    = 0;
    D3DEnumDeviceOptions    *pBestOptions   = 0;
    D3DSettings::Settings   *pSettings      = 0;

    // Retrieve the primary adapters display mode.
    m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DisplayMode);

    // Loop through each adapter
    for (i = 0; i < GetAdapterCount(); i++)
    {
        D3DEnumAdapter * pAdapter = m_vpAdapters[ i ];
        
        // Loop through each device
        for (j = 0; j < pAdapter->Devices.size(); j++)
        {
            D3DEnumDevice * pDevice = pAdapter->Devices[ j ];

            // Skip if this is not of the required type
            if (bRequireHAL && pDevice->DeviceType != D3DDEVTYPE_HAL)
                continue;
            if (bRequireREF && pDevice->DeviceType != D3DDEVTYPE_REF)
                continue;
            
            // Loop through each option set
            for (k = 0; k < pDevice->Options.size(); k++)
            {
                D3DEnumDeviceOptions * pOptions = pDevice->Options[ k ];

                // Determine if back buffer format matches adapter 
                bool MatchedBB = (pOptions->BackBufferFormat == pOptions->AdapterFormat);

                // Skip if this is not windowed, and formats don't match
                if (!pOptions->Windowed) 
                    continue;
                if (pOptions->AdapterFormat != DisplayMode.Format) 
                    continue;

                // If we haven't found a compatible option set yet, or if this set
                // is better (because it's HAL / formats match better) then save it.
                if (pBestOptions == 0 || 
                    (pOptions->DeviceType == D3DDEVTYPE_HAL && MatchedBB) ||
                    (pBestOptions->DeviceType != D3DDEVTYPE_HAL && pOptions->DeviceType == D3DDEVTYPE_HAL))
                {
                    // Store best so far
                    pBestAdapter = pAdapter;
                    pBestDevice  = pDevice;
                    pBestOptions = pOptions;
                    
                    // This windowed device option looks great -- take it
                    if (pOptions->DeviceType == D3DDEVTYPE_HAL && MatchedBB)
                        goto EndWindowedDeviceOptionSearch;
                    
                } // if
            } // for
        } // for
    } // for

    // Used by goto - I don't like this!
    EndWindowedDeviceOptionSearch:
    
    if (pBestOptions == 0)
        return false;

    // Fill out passed settings details
    D3DSettings.Windowed               = true;
    pSettings                          = D3DSettings.GetSettings();
    pSettings->AdapterOrdinal          = pBestOptions->AdapterOrdinal;
    pSettings->DisplayMode             = DisplayMode;
    pSettings->DeviceType              = pBestOptions->DeviceType;
    pSettings->BackBufferFormat        = pBestOptions->BackBufferFormat;
    pSettings->DepthStencilFormat      = pBestOptions->DepthFormats[ 0 ];
    pSettings->MultisampleType         = pBestOptions->MultiSampleTypes[ 0 ];
    pSettings->MultisampleQuality      = 0;
    pSettings->VertexProcessingType    = pBestOptions->VertexProcessingTypes[ 0 ];
    pSettings->PresentInterval         = pBestOptions->PresentIntervals[ 0 ];

    // We found a mode
    return true;
} // FindBestWindowedMode


// ----------------------------------------------------------------------------
// Name: D3DInitialize::FindBestFullscreenMode
// Desc: Find the best fullscreen mode, and fill out our D3DSettings structure.
// Parm: D3DSettings &D3DSettings   - the settings
// Parm: D3DDISPLAYMODE *pMatchMode - the mode to match
// Parm: bool bRequireHAL           - do we require hardware support
// Parm: bool bRequireREF           - do we require the reference dirver
// Retn: bool                       - true if found
// ----------------------------------------------------------------------------
bool D3DInitialize::FindBestFullscreenMode(D3DSettings &D3DSettings, D3DDISPLAYMODE * pMatchMode, bool bRequireHAL, bool bRequireREF)
{
    // For fullscreen, default to first HAL option that supports the current desktop 
    // display mode, or any display mode if HAL is not compatible with the desktop mode, or 
    // non-HAL if no HAL is available
    
    ULONG                    i, j, k;
    D3DDISPLAYMODE           AdapterDisplayMode;
    D3DDISPLAYMODE           BestAdapterDisplayMode;
    D3DDISPLAYMODE           BestDisplayMode;
    D3DEnumAdapter          *pBestAdapter   = 0;
    D3DEnumDevice           *pBestDevice    = 0;
    D3DEnumDeviceOptions    *pBestOptions   = 0;
    D3DSettings::Settings   *pSettings      = 0;
    
    BestAdapterDisplayMode.Width            = 0;
    BestAdapterDisplayMode.Height           = 0;
    BestAdapterDisplayMode.Format           = D3DFMT_UNKNOWN;
    BestAdapterDisplayMode.RefreshRate      = 0;

    // Loop through each adapter
    for (i = 0; i < GetAdapterCount(); i++)
    {
        D3DEnumAdapter * pAdapter = m_vpAdapters[ i ];
        
        // Retrieve the desktop display mode
        m_pD3D->GetAdapterDisplayMode(pAdapter->Ordinal, &AdapterDisplayMode);

        // If any settings were passed, overwrite to test for matches
        if (pMatchMode) 
        {
            if (pMatchMode->Width  != 0) 
                AdapterDisplayMode.Width  = pMatchMode->Width;
            if (pMatchMode->Height != 0) 
                AdapterDisplayMode.Height = pMatchMode->Height;
            if (pMatchMode->Format != D3DFMT_UNKNOWN) 
                AdapterDisplayMode.Format = pMatchMode->Format;
            if (pMatchMode->RefreshRate != 0) 
                AdapterDisplayMode.RefreshRate = pMatchMode->RefreshRate;
        } // if

        // Loop through each device
        for (j = 0; j < pAdapter->Devices.size(); j++)
        {
            D3DEnumDevice * pDevice = pAdapter->Devices[ j ];
            
            // Skip if this is not of the required type
            if (bRequireHAL && pDevice->DeviceType != D3DDEVTYPE_HAL)
                continue;
            if (bRequireREF && pDevice->DeviceType != D3DDEVTYPE_REF) 
                continue;
            
            // Loop through each option set
            for (k = 0; k < pDevice->Options.size(); k++)
            {
                D3DEnumDeviceOptions * pOptions = pDevice->Options[ k ];

                // Determine if back buffer format matches adapter 
                bool MatchedBB = (pOptions->BackBufferFormat == pOptions->AdapterFormat);
                bool MatchedDesktop = (pOptions->AdapterFormat == AdapterDisplayMode.Format);
                
                // Skip if this is not fullscreen
                if (pOptions->Windowed) 
                    continue;

                // If we haven't found a compatible option set yet, or if this set
                // is better (because it's HAL / formats match better) then save it.
                if (pBestOptions == 0 ||
                   (pBestOptions->DeviceType != D3DDEVTYPE_HAL && pDevice->DeviceType == D3DDEVTYPE_HAL) ||
                   (pOptions->DeviceType == D3DDEVTYPE_HAL && pBestOptions->AdapterFormat != AdapterDisplayMode.Format && MatchedDesktop) ||
                   (pOptions->DeviceType == D3DDEVTYPE_HAL && MatchedDesktop && MatchedBB))
                {
                    // Store best so far
                    BestAdapterDisplayMode  = AdapterDisplayMode;
                    pBestAdapter            = pAdapter;
                    pBestDevice             = pDevice;
                    pBestOptions            = pOptions;
                    
                    // This fullscreen device option looks great -- take it
                    if (pOptions->DeviceType == D3DDEVTYPE_HAL && MatchedDesktop && MatchedBB)
                        goto EndFullscreenDeviceOptionSearch;

                } // if
            } // for
        } // for
    } // for

    // Used by goto - I don't like this!
    EndFullscreenDeviceOptionSearch:
    
    if (pBestOptions == 0) 
        return false;

    // Need to find a display mode on the best adapter that uses pBestOptions->AdapterFormat
    // and is as close to BestAdapterDisplayMode's res as possible
    BestDisplayMode.Width       = 0;
    BestDisplayMode.Height      = 0;
    BestDisplayMode.Format      = D3DFMT_UNKNOWN;
    BestDisplayMode.RefreshRate = 0;

    // Loop through valid display modes
    for (i = 0; i < pBestAdapter->Modes.size(); i++)
    {
        D3DDISPLAYMODE Mode = pBestAdapter->Modes[ i ];
        
        // Skip if it doesn't match our best format
        if (Mode.Format != pBestOptions->AdapterFormat) continue;

        // Determine how good a match this is
        if (Mode.Width          == BestAdapterDisplayMode.Width &&
            Mode.Height         == BestAdapterDisplayMode.Height && 
            Mode.RefreshRate    == BestAdapterDisplayMode.RefreshRate)
        {
            // Found a perfect match, so stop
            BestDisplayMode = Mode;
            break;
        } // if
        else if (Mode.Width         == BestAdapterDisplayMode.Width &&
                 Mode.Height        == BestAdapterDisplayMode.Height && 
                 Mode.RefreshRate   > BestDisplayMode.RefreshRate)
        {
            // Refresh rate doesn't match, but width/height match, so keep this
            // and keep looking
            BestDisplayMode = Mode;
        } // else if
        else if (Mode.Width == BestAdapterDisplayMode.Width)
        {
            // Width matches, so keep this and keep looking
            BestDisplayMode = Mode;
        } // else if
        else if (BestDisplayMode.Width == 0)
        {
            // We don't have anything better yet, so keep this and keep looking
            BestDisplayMode = Mode;        
        } // else if
    } // for

    // Fill out passed settings details
    D3DSettings.Windowed               = false;
    pSettings                          = D3DSettings.GetSettings();
    pSettings->AdapterOrdinal          = pBestOptions->AdapterOrdinal;
    pSettings->DisplayMode             = BestDisplayMode;
    pSettings->DeviceType              = pBestOptions->DeviceType;
    pSettings->BackBufferFormat        = pBestOptions->BackBufferFormat;
    pSettings->DepthStencilFormat      = pBestOptions->DepthFormats[ 0 ];
    pSettings->MultisampleType         = pBestOptions->MultiSampleTypes[ 0 ];
    pSettings->MultisampleQuality      = 0;
    pSettings->VertexProcessingType    = pBestOptions->VertexProcessingTypes[ 0 ];
    pSettings->PresentInterval         = pBestOptions->PresentIntervals[ 0 ];

    // Success!
    return true;
} // FindBestFullscreenMode


// ----------------------------------------------------------------------------
// Name: D3DInitialize::GetDirect3DDevice
// Desc: Return a copy of the Direct3DDevice pointer (adds ref on that iface)
// Retn: LPDIRECT3DDEVICE9 - the device pointer
// ----------------------------------------------------------------------------
LPDIRECT3DDEVICE9 D3DInitialize::GetDirect3DDevice()
{ 
    // Bail if not created yet
    if (!m_pD3DDevice) 
        return 0;

    // AddRef on the device
    m_pD3DDevice->AddRef();

    // we've duplicated the pointer
    return m_pD3DDevice; 
} // GetDirect3DDevice


// -- EOF

