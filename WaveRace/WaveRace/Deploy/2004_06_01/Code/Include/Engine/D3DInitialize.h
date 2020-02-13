// ----------------------------------------------------------------------------
// File: D3DInitialize.h
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
#ifndef _D3DINITIALIZE_H_
#define _D3DINITIALIZE_H_


// ----------------------------------------------------------------------------
// D3DInitialize specific includes
// ----------------------------------------------------------------------------
#include <D3DX9.h>
#include <vector>


// ----------------------------------------------------------------------------
// Name: VERTEXPROCESSING_TYPE (enum)
// Desc: Enumeration of all possible D3D vertex processing types.
// ----------------------------------------------------------------------------
enum VERTEXPROCESSING_TYPE
{
    SOFTWARE_VP         = 1,        // Software Vertex Processing
    MIXED_VP            = 2,        // Mixed Vertex Processing
    HARDWARE_VP         = 3,        // Hardware Vertex Processing
    PURE_HARDWARE_VP    = 4         // Pure Hardware Vertex Processing
}; // VERTEXPROCESSING_TYPE


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class D3DEnumDeviceOptions;
class D3DEnumDevice;
class D3DEnumAdapter;


// ----------------------------------------------------------------------------
// STL Vector typedefs for easy access
// ----------------------------------------------------------------------------
typedef std::vector<D3DMULTISAMPLE_TYPE>    VectorMSType;
typedef std::vector<D3DFORMAT>              VectorFormat;
typedef std::vector<ULONG>                  VectorULONG;
typedef std::vector<VERTEXPROCESSING_TYPE>  VectorVPType;
typedef std::vector<D3DDISPLAYMODE>         VectorDisplayMode;
typedef std::vector<D3DEnumDeviceOptions*>  VectorDeviceOptions;
typedef std::vector<D3DEnumDevice*>         VectorDevice;
typedef std::vector<D3DEnumAdapter*>        VectorAdapter;


// ----------------------------------------------------------------------------
// Name: D3DEnumDeviceOptions (class)
// Desc: Stores the various device options available for any device.
// ----------------------------------------------------------------------------
class D3DEnumDeviceOptions
{
public:
    // ------------------------------------------------------------------------
    // Constructor
    // ------------------------------------------------------------------------
    ~D3DEnumDeviceOptions();


    // ------------------------------------------------------------------------
    // Device option attributes
    // ------------------------------------------------------------------------
    ULONG                   AdapterOrdinal;
    D3DDEVTYPE              DeviceType;
    D3DCAPS9                Caps;
    D3DFORMAT               AdapterFormat;
    D3DFORMAT               BackBufferFormat;
    bool                    Windowed;
    VectorMSType            MultiSampleTypes;
    VectorULONG             MultiSampleQuality;
    VectorFormat            DepthFormats;
    VectorVPType            VertexProcessingTypes;
    VectorULONG             PresentIntervals;
}; // class D3DEnumDeviceOptions


// ----------------------------------------------------------------------------
// Name: D3DEnumDevice (class)
// Desc: Stores the various capabilities etc for an individual device type.
// ----------------------------------------------------------------------------
class D3DEnumDevice
{
public:
    // ------------------------------------------------------------------------
    // Constructor
    // ------------------------------------------------------------------------
    ~D3DEnumDevice();


    // ------------------------------------------------------------------------
    // Device attributes
    // ------------------------------------------------------------------------
    D3DDEVTYPE              DeviceType;
    D3DCAPS9                Caps;
    VectorDeviceOptions     Options;
}; // class D3DEnumDevice


// ----------------------------------------------------------------------------
// Name : D3DEnumAdapter (class)
// Desc : Stores the various adapter modes for a single enumerated adapter.
// ----------------------------------------------------------------------------
class D3DEnumAdapter
{
public:
    // ------------------------------------------------------------------------
    // Constructor
    // ------------------------------------------------------------------------
    ~D3DEnumAdapter();


    // ------------------------------------------------------------------------
    // Adapter attributes
    // ------------------------------------------------------------------------
    ULONG                   Ordinal;
    D3DADAPTER_IDENTIFIER9  Identifier;
    VectorDisplayMode       Modes;
    VectorDevice            Devices;
 }; // class D3DEnumAdapter


// ----------------------------------------------------------------------------
// Name: D3DSettings  (class)
// Desc: Allows us to set up the various options we will be using.  Note : Also 
//       used internally by D3DSettingsDlg.
// ----------------------------------------------------------------------------
class D3DSettings 
{
public:
    // ------------------------------------------------------------------------
    // Name: Settings (struct)
    // Desc: Display settings
    // ------------------------------------------------------------------------
    struct Settings
    {
        ULONG                   AdapterOrdinal;
        D3DDISPLAYMODE          DisplayMode;
        D3DDEVTYPE              DeviceType;
        D3DFORMAT               BackBufferFormat;
        D3DFORMAT               DepthStencilFormat;
        D3DMULTISAMPLE_TYPE     MultisampleType;
        ULONG                   MultisampleQuality;
        VERTEXPROCESSING_TYPE   VertexProcessingType;
        ULONG                   PresentInterval;
    }; // Settings


    // ------------------------------------------------------------------------
    // Settings attributes
    // ------------------------------------------------------------------------
    bool        Windowed;
    Settings    Windowed_Settings;
    Settings    Fullscreen_Settings;


    // ------------------------------------------------------------------------
    // Get the settings
    // ------------------------------------------------------------------------
    Settings*   GetSettings() { return (Windowed) ? &Windowed_Settings : &Fullscreen_Settings; }
}; // class D3DSettings


// ----------------------------------------------------------------------------
// Name: D3DInitialize (class)
// Desc: Direct3D Initialization class. Detects supported formats, modes and 
//       capabilities, and initializes the devices based on the chosen details
// ----------------------------------------------------------------------------
class D3DInitialize
{
public:
    // ------------------------------------------------------------------------
	// Constructors & destructors for this class.
	// ------------------------------------------------------------------------
	         D3DInitialize();
	virtual ~D3DInitialize();


	// ------------------------------------------------------------------------
	// Enumerate the device to fina all caps
	// ------------------------------------------------------------------------
    HRESULT                 Enumerate               (LPDIRECT3D9 pD3D, bool lock_vsync);
    

    // ------------------------------------------------------------------------
    // Create and reset the display with the given settings
    // ------------------------------------------------------------------------
    HRESULT                 CreateDisplay           (D3DSettings& D3DSettings, ULONG Flags = 0, HWND hWnd = 0, WNDPROC pWndProc = 0,
                                                        LPCTSTR Title = 0, ULONG Width = CW_USEDEFAULT, ULONG Height = CW_USEDEFAULT, 
                                                        LPVOID lParam = 0);
    HRESULT                 ResetDisplay            (LPDIRECT3DDEVICE9 pD3DDevice, D3DSettings& D3DSettings, HWND hWnd = 0);
    
    
    // ------------------------------------------------------------------------
    // Find the best windowed and fullscreen mode based on the caps
    // ------------------------------------------------------------------------
    bool                    FindBestWindowedMode    (D3DSettings & D3DSettings, bool bRequireHAL = false, bool bRequireREF = false);
    bool                    FindBestFullscreenMode  (D3DSettings & D3DSettings, D3DDISPLAYMODE * pMatchMode = 0, bool bRequireHAL = false, bool bRequireREF = false);


    // ------------------------------------------------------------------------
    // Build the present-params struct
    // ------------------------------------------------------------------------
    D3DPRESENT_PARAMETERS   BuildPresentParameters  (D3DSettings& D3DSettings, ULONG Flags = 0);


    // ------------------------------------------------------------------------
    // Public accessor functions for this class
    // ------------------------------------------------------------------------
    ULONG                   GetAdapterCount() const     { return m_vpAdapters.size(); }
    const D3DEnumAdapter   *GetAdapter(ULONG Index)     { return (Index > GetAdapterCount()) ? 0 : m_vpAdapters[Index]; }
    HWND                    GetHWND()                   { return m_hWnd; }
    const LPDIRECT3D9       GetDirect3D()               { return m_pD3D; }
    LPDIRECT3DDEVICE9       GetDirect3DDevice();
    
private:
    // ------------------------------------------------------------------------
	// Private functions for this class
	// ------------------------------------------------------------------------
    HRESULT             EnumerateAdapters               ();
    HRESULT             EnumerateDisplayModes           (D3DEnumAdapter * pAdapter);
    HRESULT             EnumerateDevices                (D3DEnumAdapter * pAdapter);
    HRESULT             EnumerateDeviceOptions          (D3DEnumDevice  * pDevice, D3DEnumAdapter * pAdapter);
    HRESULT             EnumerateDepthStencilFormats    (D3DEnumDeviceOptions * pDeviceOptions);
    HRESULT             EnumerateMultiSampleTypes       (D3DEnumDeviceOptions * pDeviceOptions);
    HRESULT             EnumerateVertexProcessingTypes  (D3DEnumDeviceOptions * pDeviceOptions);
    HRESULT             EnumeratePresentIntervals       (D3DEnumDeviceOptions * pDeviceOptions);


    // ------------------------------------------------------------------------
	// Private virtual functions for this class
	// ------------------------------------------------------------------------
    virtual bool        ValidateDisplayMode          (const D3DDISPLAYMODE& Mode)                         { return true; }
    virtual bool        ValidateDevice               (const D3DDEVTYPE& Type, const D3DCAPS9& Caps)       { return true; }
    virtual bool        ValidateDeviceOptions        (const D3DFORMAT& BackBufferFormat, bool IsWindowed) { return true; }
    virtual bool        ValidateDepthStencilFormat   (const D3DFORMAT& DepthStencilFormat)                { return true; }
    virtual bool        ValidateMultiSampleType      (const D3DMULTISAMPLE_TYPE& Type)                    { return true; }
    virtual bool        ValidateVertexProcessingType (const VERTEXPROCESSING_TYPE& Type)                  { return true; }
    virtual bool        ValidatePresentInterval      (const ULONG& Interval)                              { return true; }
    

    // ------------------------------------------------------------------------
	// Private variables for this class
	// ------------------------------------------------------------------------
	LPDIRECT3D9		    m_pD3D;			    // Primary Direct3D Object.
    LPDIRECT3DDEVICE9   m_pD3DDevice;       // Created Direct3D Device.
    HWND                m_hWnd;             // Created window handle
    VectorAdapter       m_vpAdapters;       // Enumerated Adapters
    bool                m_lock_vsync;       // Lock to VSYNC as default
    
}; // class D3DInitialize


#endif // _D3DINITIALIZE_H_

// -- EOF

