// ----------------------------------------------------------------------------
// File: Application.cpp
// Desc: Main application class that controls the entire application
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Application specific includes
// ----------------------------------------------------------------------------
#include "Application.h"
#include "Engine/Material.h"
#include "Engine/RenderBin.h"
#include "Engine/ASE.h"
#include "Engine/Camera.h"
#include "Math/Matrix.h"
#include "Math/Intersect.h"
#include "Res/resource.h"

#include "GameCentral.h"

#include "Common/Logging.h"
#include "Common/FilePath.h"

#include "GameObject/SkyBox.h"
#include "GameObject/Vessels.h"
#include "GameObject/Terrain.h"
#include "GameObject/Wave.h"


// ----------------------------------------------------------------------------
// Window size
// ----------------------------------------------------------------------------
#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600
#define FULLSCREEN      true
#define LOCK_VSYNC      true


// ----------------------------------------------------------------------------
// Mouse button states
// ----------------------------------------------------------------------------
#define MOUSE_NONE      0x0
#define MOUSE_LEFT      0x1
#define MOUSE_MIDDLE    0x2
#define MOUSE_RIGHT     0x4


// ----------------------------------------------------------------------------
// Name: Application::SetupRenderStates
// Desc: Sets up all the initial states required by the renderer.
// ----------------------------------------------------------------------------
void Application::SetupRenderStates()
{
    GameCentralSingleton::Instance().SetGlobalState();
} // SetupRenderStates


// ----------------------------------------------------------------------------
// Name: Application::BuildObjects
// Desc: Build all of our objects
// Retn: bool - true if all succeeded
// ----------------------------------------------------------------------------
bool Application::BuildObjects()
{
    // Release previously built objects
    ReleaseObjects();

    // Create the camera
    if (!CameraSingleton::Instance().Create(m_pD3DDevice))
    {
        LOG_ERROR << "Failed to create the camera" << ENDLOG;
        return false;
    } // if

    // Create the render bin
    if (!RenderBinSingleton::Instance().Create(m_pD3DDevice))
    {
        LOG_ERROR << "Failed to create the render bin" << ENDLOG;
        return false;
    } // if

    return GameCentralSingleton::Instance().Create(m_pD3DDevice);
} // BuildObjects


// ----------------------------------------------------------------------------
// Name: Application::ReleaseObjects
// Desc: Releases our objects and their associated memory so that we can rebuild
//       them, if required, during our applications life-time.
// ----------------------------------------------------------------------------
void Application::ReleaseObjects()
{
    if (m_pD3DDevice)
    {
        GameCentralSingleton::Instance().Release();
        RenderBinSingleton::Instance().Release();
        CameraSingleton::Instance().Release();

        // De-reference device objects stream (just in case any remain set)
        m_pD3DDevice->SetStreamSource(0, 0, 0, 0);
        m_pD3DDevice->SetIndices(0);
        m_pD3DDevice->SetTexture(0, 0);
        m_pD3DDevice->SetTexture(1, 0);

        // Clear out the texture and material caches
        MaterialCache::Clear();
        TextureCache::Clear();
    } // if
} // ReleaseObjects


// ----------------------------------------------------------------------------
// Name : Application::AnimateObjects
// Desc : Animates the objects we currently have loaded.
// ----------------------------------------------------------------------------
void Application::AnimateObjects()
{
    GameCentralSingleton::Instance().AnimateObjects((float) GetRunTime(), (float) GetFrameTime());
} // AnimateObjects


// ----------------------------------------------------------------------------
// Name : Application::RenderScene
// Desc : Render the scene
// ----------------------------------------------------------------------------
void Application::RenderScene()
{
    GameCentralSingleton::Instance().RenderObjects();
} // RenderScene


// ----------------------------------------------------------------------------
// Name: Application::Application
// Desc: Constructor
// ----------------------------------------------------------------------------
Application::Application()
{
    m_hWnd              = 0;
    m_pD3D              = 0;
    m_pD3DDevice        = 0;
    m_hIcon             = 0;
    m_hMenu             = 0;
    m_lost_device       = false;
    m_frame_time        = 0.0;
    m_run_time          = 0.0;
    m_frame_count       = 0;
    m_frame_rate        = 0;
    m_mouse_button      = MOUSE_NONE;

    GameCentralSingleton::MakeInstance();
    GameCentralSingleton::Instance().Init();

    // Reset the timer
    m_timer.Reset();

} // Application


// ----------------------------------------------------------------------------
// Name: Application::~Application
// Desc: Destructor
// ----------------------------------------------------------------------------
Application::~Application()
{
    ShutDown();
} // ~Application


// ----------------------------------------------------------------------------
// Name: Application::InitInstance
// Desc: Initialises the entire Engine here.
// Parm: HANDLE hInstance   - the application instance
// Parm: LPCTSTR lpCmdLine  - the command line params
// Parm: int iCmdShow       - the show status
// Retn: bool               - true if the initialisatiasion succeeded
// ----------------------------------------------------------------------------
bool Application::InitInstance(HANDLE hInstance, LPCTSTR lpCmdLine, int iCmdShow)
{
    // Create the primary display device
    if (!CreateDisplay())
    { 
        ShutDown();
        return false; 
    } // if

    // Build Objects
    if (!BuildObjects())
    { 
        ShutDown();
        return false; 
    } // if

    // Set up all required game states
    SetupInitialState();

    // Setup our rendering environment
    SetupRenderStates();

    // Store new viewport sizes
    RECT rc;
    ::GetClientRect(m_hWnd, &rc);
    m_view_width  = rc.right - rc.left;
    m_view_height = rc.bottom - rc.top;

    // Success!
	return true;
}

// ----------------------------------------------------------------------------
// Name: Application::CreateDisplay
// Desc: Create the display window
// Retn: bool - true if successful
// ----------------------------------------------------------------------------
bool Application::CreateDisplay()
{
    D3DDISPLAYMODE          MatchMode;
    D3DSettingsDlg          SettingsDlg;
    ApplicationInitialize   Initialize;
    LPTSTR                  WindowTitle     = _T("DX Water");
    USHORT                  Width           = WINDOW_WIDTH;
    USHORT                  Height          = WINDOW_HEIGHT;
    RECT                    rc;

    // First of all create our D3D Object (This is needed by the enumeration etc)
    m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (!m_pD3D) 
    {
        MessageBox(m_hWnd, 
            _T("No compatible Direct3D object could be created."), 
            _T("Fatal Error!"), MB_OK | MB_ICONSTOP | MB_APPLMODAL);
        return false;    
    } // if

    // Enumerate the system graphics adapters    
    if (FAILED(Initialize.Enumerate(m_pD3D, LOCK_VSYNC)))
    {
        MessageBox(m_hWnd, 
            _T("Device enumeration failed. The application will now exit."), 
            _T("Fatal Error!"), MB_OK | MB_ICONSTOP | MB_APPLMODAL);
        return false;
    } // if

    // Attempt to find a good default fullscreen set
    MatchMode.Width       = WINDOW_WIDTH;
    MatchMode.Height      = WINDOW_HEIGHT;
    MatchMode.Format      = D3DFMT_UNKNOWN;
    MatchMode.RefreshRate = 0;
    Initialize.FindBestFullscreenMode(m_D3DSettings, &MatchMode);
    
    // Attempt to find a good default windowed set
    if (!FULLSCREEN)
        Initialize.FindBestWindowedMode(m_D3DSettings);

    // Create the direct 3d device etc.
    if (FAILED(Initialize.CreateDisplay(m_D3DSettings, 0, 
        0, StaticWndProc, WindowTitle, Width, Height, this)))
    {
        MessageBox(m_hWnd, 
            _T("Device creation failed. The application will now exit."), 
            _T("Fatal Error!"), MB_OK | MB_ICONSTOP | MB_APPLMODAL);
        return false;    
    } // if
    
    // Retrieve created items
    m_pD3DDevice = Initialize.GetDirect3DDevice();
    m_hWnd       = Initialize.GetHWND();

    // Load icon and menu
    m_hIcon = LoadIcon((HINSTANCE)GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON));
    m_hMenu = LoadMenu((HINSTANCE)GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU));

    // Set application icon
    SetClassLong(m_hWnd, GCL_HICON, (long) m_hIcon);

    // Set menu only in windowed mode
    if (m_D3DSettings.Windowed)
        SetMenu(m_hWnd, m_hMenu);

    // Retrieve the final client size of the window
    ::GetClientRect(m_hWnd, &rc);
    m_view_x      = rc.left;
    m_view_y      = rc.top;
    m_view_width  = rc.right - rc.left;
    m_view_height = rc.bottom - rc.top;

    // Show the window
	ShowWindow(m_hWnd, SW_SHOW);
    ShowCursor(FALSE);

    // Success!!
    return true;
} // CreateDisplay


// ----------------------------------------------------------------------------
// Name: Application::SetupInitialState
// Desc: Sets up all the initial states required by the game.
// ----------------------------------------------------------------------------
void Application::SetupInitialState()
{
    // App is active
    m_active = true;
} // SetupInitialState


// ----------------------------------------------------------------------------
// Name: Application::Begin
// Desc: Signals the beginning of the physical post-initialisation stage. From 
//       here on, the game engine has control over processing.
// Retn: int - the application return code
// ----------------------------------------------------------------------------
int Application::Begin()
{
    m_timer.Start();
    MSG	msg;

    // Start main loop
	while (1) 
    {
        // Did we recieve a message, or are we idling
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) 
        {
			if (msg.message == WM_QUIT)
                break;

            // Process the message
			TranslateMessage(&msg);
			DispatchMessage (&msg);
		}  // if
        else 
        {
            // Update the run time and delta frame time
            m_run_time = m_timer.GetTime(&m_frame_time);

            // Advance the frame rate counter
            m_frame_counter.Tick();
            m_frame_rate = m_frame_counter.GetFrameRate();

            // Perform tFhis frame
            FrameAdvance();

            // Increment the frame counter
            m_frame_count++;
		} // else
    } // while

    return EXIT_SUCCESS;
} // Begin


// ----------------------------------------------------------------------------
// Name: Application::ShutDown
// Desc: Shuts down the game engine, and frees up all resources.
// Retn: bool - true if successful
// ----------------------------------------------------------------------------
bool Application::ShutDown()
{
    // Release any previously built objects
    ReleaseObjects ();

    // Destroy the device
    if (m_pD3DDevice) 
        m_pD3DDevice->Release();

    // Destroy the D3D layer
    if (m_pD3D) 
        m_pD3D->Release();

    // Reset the pointers
    m_pD3D          = 0;
    m_pD3DDevice    = 0;

    // Destroy the menu
    if (m_hMenu)
        DestroyMenu(m_hMenu);
    SetMenu(m_hWnd, 0);

    // Destroy the render window
    if (m_hWnd)
        DestroyWindow(m_hWnd);

    // Reset the pointers
    m_hMenu         = 0;
    m_hWnd          = 0;
    
    // Shutdown Success
    return true;
} // Shutdown


// ----------------------------------------------------------------------------
// Name: Application::StaticWndProc
// Desc: This is the main messge pump for ALL display devices, it captures the 
//       appropriate messages, and routes them through to the application class 
//       for which it was intended, therefore giving full class access. Note : 
//       It is VITALLY important that you should pass your 'this' pointer to the
//       lpParam parameter of the CreateWindow function if you wish to be able 
//       to pass messages back to that app object.
// Parm: HWND hWnd        - the window handle
// Parm: UINT Message     - the message
// Parm: WPARAM wParam    - the message param 1
// Parm: LPARAM lParam    - the message param 2
// Retn: LRESULT CALLBACK - the result
// ----------------------------------------------------------------------------
LRESULT CALLBACK Application::StaticWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    // If this is a create message, trap the 'this' pointer passed in and store it within the window.
    if (Message == WM_CREATE) 
        SetWindowLong(hWnd, GWL_USERDATA, (LONG)((CREATESTRUCT FAR *) lParam)->lpCreateParams);

    // Obtain the correct destination for this message
    Application *Destination = (Application *) GetWindowLong(hWnd, GWL_USERDATA);
    
    // If the hWnd has a related class, pass it through
    if (Destination)
        return Destination->DisplayWndProc(hWnd, Message, wParam, lParam);
    
    // No destination found, defer to system...
    return DefWindowProc(hWnd, Message, wParam, lParam);
} // StaticWndProc


// ----------------------------------------------------------------------------
// Name: Application::DisplayWndProc
// Desc: The display devices internal WndProc function. All messages being 
//       passed to this function are relative to the window it owns.
// Parm: HWND hWnd        - the window handle
// Parm: UINT Message     - the message
// Parm: WPARAM wParam    - the message param 1
// Parm: LPARAM lParam    - the message param 2
// Retn: LRESULT CALLBACK - the result
// ----------------------------------------------------------------------------
LRESULT Application::DisplayWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    // Determine message type
	switch (Message)
    {
		case WM_CREATE:
            break;
		
        case WM_CLOSE:
			PostQuitMessage(0);
			break;
		
        case WM_DESTROY:
			PostQuitMessage(0);
			break;
		
        case WM_SIZE:
            if (wParam == SIZE_MINIMIZED)
            {
                // App has been minimized
                m_active = false;
            } // else
            else
            {
                // App is active
                m_active = true;

                // Store new viewport sizes
                m_view_width  = LOWORD(lParam);
                m_view_height = HIWORD(lParam);
        
                // Reset the device
                if (m_pD3DDevice) 
                {
                    SetupRenderStates();

                    // Store new viewport sizes
                    RECT rc;
                    ::GetClientRect(m_hWnd, &rc);
                    m_view_width  = rc.right - rc.left;
                    m_view_height = rc.bottom - rc.top;
                } // if
            } // else
			break;

        case WM_LBUTTONDOWN:
            GetCursorPos(&m_old_cursor_pos);
            m_mouse_button |= MOUSE_LEFT;
            break;

        case WM_LBUTTONUP:
            m_mouse_button &= ~MOUSE_LEFT;
            break;

        case WM_RBUTTONDOWN:
            GetCursorPos(&m_old_cursor_pos);
            m_mouse_button |= MOUSE_RIGHT;
            break;

        case WM_RBUTTONUP:
            m_mouse_button &= ~MOUSE_RIGHT;
            break;

        case WM_MBUTTONDOWN:
            GetCursorPos(&m_old_cursor_pos);
            m_mouse_button |= MOUSE_MIDDLE;
            break;

        case WM_MBUTTONUP:
            m_mouse_button &= ~MOUSE_MIDDLE;
            break;

        case WM_KEYDOWN:
            // Which key was pressed
			switch (wParam) 
            {
				case VK_ESCAPE:
					PostQuitMessage(0);
					return 0;

                case VK_RETURN:
                    if (GetKeyState(VK_SHIFT) & 0xFF00)
                    {
                        // Toggle fullscreen / windowed
                        m_D3DSettings.Windowed = !m_D3DSettings.Windowed;
                        
                        // Reset the display into teh default fullscreen mode
                        ApplicationInitialize Initialize;
                        Initialize.ResetDisplay(m_pD3DDevice, m_D3DSettings, m_hWnd);
                        SetupRenderStates();

                        // Store new viewport sizes
                        RECT rc;
                        ::GetClientRect(m_hWnd, &rc);
                        m_view_width  = rc.right - rc.left;
                        m_view_height = rc.bottom - rc.top;

                        // Set menu only in windowed mode
                        // (Removed by ResetDisplay automatically in fullscreen)
                        if (m_D3DSettings.Windowed)
                            SetMenu(m_hWnd, m_hMenu);

                    } // if
                    break;
			} // switch
			break;

        case WM_COMMAND:
            // Process Menu Items
            switch(LOWORD(wParam))
            {
                case ID_FILE_CHANGEDEVICE:
                    ChangeDevice();
                    break;
                
                case ID_EXIT:
                    SendMessage(m_hWnd, WM_CLOSE, 0, 0);
                    return 0;
            } // switch

		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);

    } // switch
    
    return 0;
} // DisplayWndProc


// ----------------------------------------------------------------------------
// Name: Application::ChangeDevice
// Desc: The user requested a change of device. This function displays the 
//       dialog, and also reinitializes any device as required.
// ----------------------------------------------------------------------------
void Application::ChangeDevice()
{
    ApplicationInitialize   Initialize;
    D3DSettingsDlg          SettingsDlg;

    // Enumerate the system graphics adapters    
    if (FAILED(Initialize.Enumerate(m_pD3D, LOCK_VSYNC)))
    {
        MessageBox(m_hWnd, 
            _T("Device enumeration failed. The application will now exit."), 
            _T("Fatal Error!"), MB_OK | MB_ICONSTOP | MB_APPLMODAL);
        PostQuitMessage(0);
        return;
    } // if

    // Display the settings dialog
    if (SettingsDlg.ShowDialog(&Initialize, &m_D3DSettings) != IDOK)
        return;

    // Get the new settings
    m_D3DSettings = SettingsDlg.GetD3DSettings();

    // Lets Destroy our objects and restart
    if (m_pD3DDevice)
        m_pD3DDevice->Release();
    m_pD3DDevice = 0;

    // Create the direct 3d device etc.
    if (FAILED (Initialize.CreateDisplay(m_D3DSettings, 0, m_hWnd)))
    {
        MessageBox(m_hWnd, 
            _T("Device creation failed. The application will now exit."), 
            _T("Fatal Error!"), MB_OK | MB_ICONSTOP | MB_APPLMODAL);
        PostQuitMessage(0);
        return;
    } // if

    // Retrieve our new device
    m_pD3DDevice = Initialize.GetDirect3DDevice();

    // Set menu only in windowed mode
    // (Removed by CreateDisplay automatically in fullscreen)
    if (m_D3DSettings.Windowed)
        SetMenu(m_hWnd, m_hMenu);

    // Rebuild our objects
    if (!BuildObjects())
    { 
        ShutDown();
        return; 
    } // if

    // Setup our render states
    SetupRenderStates();

    // Store new viewport sizes
    RECT rc;
    ::GetClientRect(m_hWnd, &rc);
    m_view_width  = rc.right - rc.left;
    m_view_height = rc.bottom - rc.top;
} // ChangeDevice



Timer g_timer;


// ----------------------------------------------------------------------------
// Name: Application::FrameAdvance
// Desc: Called to signal that we are now rendering the next frame.
// ----------------------------------------------------------------------------
void Application::FrameAdvance()
{
    // Skip if app is inactive
    if (!m_active)
    {
        // TODO: Busted I think!!
        Sleep(10);
        return;
    } // if
    
    static TCHAR FrameRate[50];
    static TCHAR TitleBuffer[255];
    static ulong last_frame_rate = 0;

    if (last_frame_rate != m_frame_rate)
    {
        // Get / Display the framerate
        _stprintf(TitleBuffer, _T("Application: %d"), m_frame_rate);
        SetWindowText(m_hWnd, TitleBuffer);
        last_frame_rate = m_frame_rate;
    } // if

    // Recover lost device if required
    if (m_lost_device)
    {
        // Can we reset the device yet ?
        HRESULT hRet = m_pD3DDevice->TestCooperativeLevel();
        if (hRet == D3DERR_DEVICENOTRESET)
        {
            // Restore the device
            ApplicationInitialize Initialize;
            Initialize.ResetDisplay(m_pD3DDevice, m_D3DSettings, m_hWnd);
            SetupRenderStates();

            // Store new viewport sizes
            RECT rc;
            ::GetClientRect(m_hWnd, &rc);
            m_view_width  = rc.right - rc.left;
            m_view_height = rc.bottom - rc.top;

            m_lost_device = false;
        } // if
        else
        {
            return;
        } // else
    } // if

    // Poll & Process input devices
    ProcessInput();

    // Animate the game objects
    AnimateObjects();

    // Clear the frame & depth buffer ready for drawing
    m_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, Color::White, 1.0f, 0);
    
    // Begin Scene Rendering
    m_pD3DDevice->BeginScene();

    // Sky box must be rendered first
    RenderScene();

    // End Scene Rendering
    m_pD3DDevice->EndScene();

    // Wait to ensure we lock to 30fps
    float t = g_timer.GetTime(0);
    if (t < 0.02f)
        Sleep((unsigned long)(1000.0f * (0.02f - t)));
    
    // Present the buffer
    if (FAILED(m_pD3DDevice->Present(0, 0, 0, 0))) 
        m_lost_device = true;

    g_timer.Reset();
    g_timer.Start();
} // FrameAdvance


// ----------------------------------------------------------------------------
// Name: Application::ProcessInput
// Desc: Simply polls the input devices and performs basic input operations
// ----------------------------------------------------------------------------
void Application::ProcessInput()
{
    POINT   CursorPos;
    float   X = 0.0f, Y = 0.0f;

    if (m_mouse_button & MOUSE_RIGHT)
    {
        // Hide the mouse pointer
        SetCursor(NULL);

        // Retrieve the cursor position
        GetCursorPos(&CursorPos);

        // Calculate mouse values
        X = (float)(CursorPos.x - m_old_cursor_pos.x);
        Y = (float)(CursorPos.y - m_old_cursor_pos.y);

        // Reset our cursor position so we can keep going forever :)
        SetCursorPos(m_old_cursor_pos.x, m_old_cursor_pos.y);

        // Move the camera
//        if (Y) m_player.Move(Player::DIR_DOWN, Y * 0.025f);
    } // if

    // Now process the mouse (if the button is pressed)
    else if (m_mouse_button & MOUSE_MIDDLE)
    {
        // Hide the mouse pointer
        SetCursor(NULL);

        // Retrieve the cursor position
        GetCursorPos(&CursorPos);

        // Calculate mouse values
        X = (float)(CursorPos.x - m_old_cursor_pos.x);
        Y = (float)(CursorPos.y - m_old_cursor_pos.y);

        // Reset our cursor position so we can keep going forever :)
        SetCursorPos(m_old_cursor_pos.x, m_old_cursor_pos.y);

        // Move the camera
//        if (X || Y) m_player.Rotate(Y * 0.125f, X * 0.125f, 0.0f);
    } // if

    else if (m_mouse_button & MOUSE_LEFT)
    {
        // Hide the mouse pointer
        SetCursor(NULL);

        // Retrieve the cursor position
        GetCursorPos(&CursorPos);

        // Calculate mouse values
        X = (float)(CursorPos.x - m_old_cursor_pos.x);
        Y = (float)(CursorPos.y - m_old_cursor_pos.y);

        // Reset our cursor position so we can keep going forever :)
        SetCursorPos(m_old_cursor_pos.x, m_old_cursor_pos.y);

        // Move the camera
//        if (X) m_player.Move(Player::DIR_RIGHT, X * 0.025f);
//        if (Y) m_player.Move(Player::DIR_BACKWARD,  Y * 0.025f);
    } // else if
} // ProcessInput


// ----------------------------------------------------------------------------
// Name: ApplicationInitialize::ValidateDisplayMode
// Desc: Allows us to validate and reject any adapter display modes.
// Parm: const D3DDISPLAYMODE &Mode - the display mode
// Retn: bool                       - true if the mode is supported
// ----------------------------------------------------------------------------
bool ApplicationInitialize::ValidateDisplayMode(const D3DDISPLAYMODE &Mode)
{
    // Test display mode
    if (Mode.Width < 640 || Mode.Height < 480 || Mode.RefreshRate < 60) 
        return false;
    
    // Supported
    return true;
} // ValidateDisplayMode


// ----------------------------------------------------------------------------
// Name: ApplicationInitialize::ValidateDevice
// Desc: Allows us to validate and reject any devices that do not have certain 
//       capabilities, or does not allow hardware rendering etc.
// Parm: const D3DDEVTYPE &Type - the device type
// Parm: const D3DCAPS9 &Caps   - the caps
// Retn: bool                   - true if supported
// ----------------------------------------------------------------------------
bool ApplicationInitialize::ValidateDevice(const D3DDEVTYPE &Type, const D3DCAPS9 &Caps)
{
    // Test Capabilities (All device types supported)
    return ((Caps.RasterCaps        & D3DPRASTERCAPS_DITHER         ) &&
            (Caps.ShadeCaps         & D3DPSHADECAPS_COLORGOURAUDRGB ) &&
            (Caps.PrimitiveMiscCaps & D3DPMISCCAPS_CULLCCW          ) &&
            (Caps.ZCmpCaps          & D3DPCMPCAPS_LESSEQUAL         ) &&
            (Caps.TextureOpCaps     & D3DTEXOPCAPS_SELECTARG1       ));
} // ValidateDevice


// ----------------------------------------------------------------------------
// Name: ApplicationInitialize::ValidateVertexProcessingType
// Desc: Allows us to validate and reject any vertex processing types we do not 
//       wish to allow access to.
// Parm: const VERTEXPROCESSING_TYPE &Type - the vertex processing type
// Retn: bool                              - true if supported
// ----------------------------------------------------------------------------
bool ApplicationInitialize::ValidateVertexProcessingType(const VERTEXPROCESSING_TYPE &Type)
{
    // Test Type (We don't need mixed )
    if (Type == MIXED_VP) 
        return false;

    // Supported
    return true;
} // ValidateVertexProcessingType


// -- EOF


