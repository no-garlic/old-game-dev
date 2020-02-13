// ----------------------------------------------------------------------------
// File: Application.h
// Desc: Main application class that controls the entire application
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _CGAMEAPP_H_
#define _CGAMEAPP_H_


// ----------------------------------------------------------------------------
// Application specific includes
// ----------------------------------------------------------------------------
#include "Main.h"
#include "Common/FrameCounter.h"
#include "Common/Timer.h"
#include "Engine/D3DSettingsDlg.h"
#include "Math/Types.h"


// ----------------------------------------------------------------------------
// Name:Application (class)
// Desc: Main application class that controls the entire application
// ----------------------------------------------------------------------------
class Application
{   
public:
    // ------------------------------------------------------------------------
    // Constructor and destructor for this class
    // ------------------------------------------------------------------------
             Application();
	virtual ~Application();


	// ------------------------------------------------------------------------
	// Public functions for this class
	// ------------------------------------------------------------------------
    LRESULT     DisplayWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
	bool        InitInstance(HANDLE hInstance, LPCTSTR lpCmdLine, int iCmdShow);
    int         Begin();
	bool        ShutDown();
	

    // ------------------------------------------------------------------------
    // Frame rate and timer functions
    // ------------------------------------------------------------------------
    float       GetRunTime()        { return m_run_time;    }
    float       GetFrameTime()      { return m_frame_time;  }
    ulong       GetFrameRate()      { return m_frame_rate;  }
    ulong       GetFrameCount()     { return m_frame_count; }


private:
    // ------------------------------------------------------------------------
	// Private functions for this class
	// ------------------------------------------------------------------------
    bool        BuildObjects      ();
    void        ReleaseObjects    ();
    void        FrameAdvance      ();
    bool        CreateDisplay     ();
    void        ChangeDevice      ();
    void        SetupInitialState ();
    void        SetupRenderStates ();
    void        AnimateObjects    ();
    void        ProcessInput      ();
    void        RenderScene       ();


    // ------------------------------------------------------------------------
	// Private static functions for this class
	// ------------------------------------------------------------------------
    static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);


    // ------------------------------------------------------------------------
	// Private variables for this class
	// ------------------------------------------------------------------------
    FrameCounter            m_frame_counter;        // Frame counter
    Timer                   m_timer;                // Engine timer
    float                   m_frame_time;           // The last frame's time
    float                   m_run_time;             // The total running time
    ulong                   m_frame_rate;           // The current framew rate
    ulong                   m_frame_count;          // The total number of frames
    
    HWND                    m_hWnd;                 // Main window HWND
    HICON                   m_hIcon;                // Window Icon
    HMENU                   m_hMenu;                // Window Menu
    
    bool                    m_lost_device;          // Is the 3d device currently lost ?
    bool                    m_active;               // Is the application active ?

    LPDIRECT3D9             m_pD3D;                 // Direct3D Object
    LPDIRECT3DDEVICE9       m_pD3DDevice;           // Direct3D Device Object
    D3DSettings             m_D3DSettings;          // The settings used to initialize D3D

    ULONG                   m_view_x;               // X Position of render viewport
    ULONG                   m_view_y;               // Y Position of render viewport
    ULONG                   m_view_width;           // Width of render viewport
    ULONG                   m_view_height;          // Height of render viewport

    POINT                   m_old_cursor_pos;       // Old cursor position for tracking
    int                     m_mouse_button;         // Mouse button state

//  Matrix                  m_translation_matrix;   // The world translation matrix
//  Matrix                  m_rotation_matrix;      // The world rotation matrix
//  Player                  m_player;               // The player
//  Sphere                  m_sphere;               // The scene bounding sphere

}; // class Application


// ----------------------------------------------------------------------------
// Name: ApplicationInitialize  (class)
// Desc: Initialization class, derived from D3DInitialize to supply any 
//       validation of device settings that are deemed applicable by this 
//       application.
// ----------------------------------------------------------------------------
class ApplicationInitialize : public D3DInitialize
{
private:
    // ------------------------------------------------------------------------
	// Private virtual functions for this class
	// ------------------------------------------------------------------------
    virtual bool        ValidateDisplayMode          (const D3DDISPLAYMODE& Mode);
    virtual bool        ValidateDevice               (const D3DDEVTYPE& Type, const D3DCAPS9& Caps);
    virtual bool        ValidateVertexProcessingType (const VERTEXPROCESSING_TYPE& Type);

}; // class ApplicationInitialize

#endif // _CGAMEAPP_H_