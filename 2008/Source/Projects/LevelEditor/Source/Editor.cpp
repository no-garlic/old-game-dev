
#include "Editor.h"


// ----------------------------------------------------------------------------
// Static initialisers
// ----------------------------------------------------------------------------
EditorCentral *EditorCentral::s_pInstance = NULL;


// ----------------------------------------------------------------------------
// Dimensions of the sub frames
// ----------------------------------------------------------------------------
namespace EditorFrameDimensions
{
  static const int LeftFrameWidth     = 216;
  static const int RightFrameWidth    = 32;
  static const int TopFrameHeight     = 41;
  static const int BottomFrameHeight  = 30;
};


// ----------------------------------------------------------------------------
// Name: EditorCentral::GetInstance
// Desc: Get the singelton instance
// Retn: Application & - the instance
// ----------------------------------------------------------------------------
EditorCentral &EditorCentral::GetInstance()
{
  if (!s_pInstance)
  {
    s_pInstance = new EditorCentral();
    atexit(&EditorCentral::DestroyInstance);
  } // if

  return *s_pInstance;
} // GetInstance


// ----------------------------------------------------------------------------
// Name: EditorCentral::DestroyInstance
// Desc: Destroy the singleton instance
// ----------------------------------------------------------------------------
void EditorCentral::DestroyInstance()
{
  delete s_pInstance;
  s_pInstance = NULL;
} // DestroyInstance



// ----------------------------------------------------------------------------
// Name: EditorCentral::EditorCentral
// Desc: Constructor
// ----------------------------------------------------------------------------
EditorCentral::EditorCentral()
: m_pModule       (NULL),
  m_pLeftFrame    (NULL),
  m_pBottomFrame  (NULL),
  m_pLeftPanel    (NULL),
  m_pBottomPanel  (NULL),
  m_pToolBar      (NULL),
  m_pToolPanel    (NULL),
  m_pUndoManager  (NULL),
  m_pActionManager(NULL),
  m_pCameraManager(NULL),
  m_pKeyboardInput(NULL),
  m_pMouseInput   (NULL),
  m_pGrid         (NULL),
  m_Initialised   (false)
{
  m_pDocument = new EditorDocument();
  m_pContent  = new EditorContent();
  m_pUndoManager = new UndoManager();
  m_pActionManager = new ActionManager();
  m_pCameraManager = new EditorCameraManager();
  m_pMouseInput = new EditorInput_Mouse();
  m_pKeyboardInput = new EditorInput_Keyboard();
  m_pGrid = new Grid();
}


// ----------------------------------------------------------------------------
// Name: EditorCentral::~EditorCentral
// Desc: Destructor
// ----------------------------------------------------------------------------
EditorCentral::~EditorCentral()
{
  // TODO: Save first??
  delete m_pDocument;
  delete m_pContent;
  delete m_pUndoManager;
  delete m_pActionManager;
  delete m_pCameraManager;
  delete m_pMouseInput;
  delete m_pKeyboardInput;
  delete m_pGrid;
}


// ----------------------------------------------------------------------------
// Name: EditorCentral::SetRenderState
// Desc: Called when the device is reset so the render states can be set
// ----------------------------------------------------------------------------
void EditorCentral::SetRenderState()
{
  m_pDocument->SetRenderState();
  m_pCameraManager->GetCurrentCamera()->Activate();
}


// ----------------------------------------------------------------------------
// Name: EditorCentral::OnInit
// Desc: Initialise the game
// ----------------------------------------------------------------------------
bool EditorCentral::OnInit()
{
  // Create the database
  m_pDatabase = FileSystem.AddDatabase("Editor", "Data/Editor");

  // Add a PNG file handler
  wxImage::AddHandler(new wxPNGHandler);

  // Load the image list
  m_pImageList = new ImageList();
  FileHandle imgHandle = m_pDatabase->FindFileHandle("EditorImageList.cfg");
  if (!m_pImageList->Load(imgHandle))
  {
    LOG_ERROR << "Failed to load the image list: " << imgHandle << ENDLOG;
    return false;
  }

  // The default position and size of the frames - we update these by 
  // calling UpdateFrameDimensions() after we create them.
  wxPoint defaultPosition(0, 0);
  wxSize  defaultSize(32, 32);

  // Create all of the frames
  m_pLeftFrame    = new EditorFrame(defaultPosition, defaultSize, EDT_LEFT_FRAME);
  m_pToolBar      = new ToolBar(defaultPosition, defaultSize, EDT_RIGHT_FRAME);
  m_pToolPanel    = new ToolPanel(defaultPosition, defaultSize, EDT_TOP_FRAME);
  m_pBottomFrame  = new EditorFrame(defaultPosition, defaultSize, EDT_BOTTOM_FRAME);

  // Show the frames
  m_pLeftFrame->Show(true);
  m_pToolBar->Show(true);
  m_pToolPanel->Show(true);
  m_pBottomFrame->Show(true);

  // Create the panels
  m_pLeftPanel   = new EditorPanelLeft(m_pLeftFrame);
  m_pBottomPanel = new EditorPanelBottom(m_pBottomFrame);

  // Initialise the toolbar and tool panel
  m_pToolBar->Init();
  m_pToolPanel->Init();

  // Show the default panels
  if (!m_pLeftFrame->ShowPanel("LEFT"))     return false;
  if (!m_pBottomFrame->ShowPanel("BOTTOM")) return false;

  // Load the editor content
  FileHandle handle = m_pDatabase->FindFileHandle("EditorContent.cfg");
  if (!m_pContent->Load(handle))
  {
    LOG_ERROR << "Failed to load the editor content" << ENDLOG;
    return false;
  }

  // Build the content tree
  m_pLeftPanel->GetContentPanel()->RefreshData();

  // Completed
  m_Initialised = true;

  // Set the default menu options
  m_pDocument->Init();
  m_pDocument->SetDirty(false);

  // Enable the undo manager
  m_pUndoManager->SetActive(true);

  // Initialise the camera
  m_pCameraManager->Init();

  // Initialise the debug render manager
  if (!DebugRender.Init())
  {
    LOG_ERROR << "Failed to initialise the debug render manager" << ENDLOG;
    return false;
  }

  return true;
}


// ----------------------------------------------------------------------------
// Update the dimensions of the frame, which is called if the parent window 
// is resized or moved.
// ----------------------------------------------------------------------------
void EditorCentral::UpdateFrameDimensions()
{
  // Get our dimensions from the namespace
  using namespace EditorFrameDimensions;

  // Get the window info
  WINDOWINFO info;
  info.cbSize = sizeof(info);
  ::GetWindowInfo((HWND) WxDisplay::GetFrame()->GetHWND(), &info);

  // Get the client viewport
  int x = info.rcClient.left;
  int y = info.rcClient.top;
  int w = info.rcClient.right - info.rcClient.left;
  int h = info.rcClient.bottom - info.rcClient.top;

  // Deduct the status bar height
  wxStatusBar *pStatusBar = GetMainFrame()->GetStatusBar();
  if (pStatusBar)
  {
    h -= pStatusBar->GetSize().GetHeight();
  }

  // Top frame
  int top_x = x;
  int top_y = y;
  int top_w = w;
  int top_h = TopFrameHeight;

  // Left frame
  int left_x = x;
  int left_y = y + TopFrameHeight;
  int left_w = LeftFrameWidth;
  int left_h = h - TopFrameHeight;

  // Right frame
  int right_x = x + (w - RightFrameWidth);
  int right_y = y + TopFrameHeight;
  int right_w = RightFrameWidth;
  int right_h = h - TopFrameHeight;

  // Bottom frame
  int bottom_x = x + LeftFrameWidth;
  int bottom_y = (y + h) - BottomFrameHeight;
  int bottom_w = w - (LeftFrameWidth + RightFrameWidth);
  int bottom_h = BottomFrameHeight;

  // Reposition the frames
  if (m_pLeftFrame)
  {
    m_pLeftFrame->SetPosition(wxPoint(left_x, left_y));
    m_pLeftFrame->SetSize(wxSize(left_w, left_h));
  }
  if (m_pToolPanel)
  {
    m_pToolPanel->SetPosition(wxPoint(right_x, right_y));
    m_pToolPanel->SetSize(wxSize(right_w, right_h));
  }
  if (m_pBottomFrame)
  {
    m_pBottomFrame->SetPosition(wxPoint(bottom_x, bottom_y));
    m_pBottomFrame->SetSize(wxSize(bottom_w, bottom_h));
  }
  if (m_pToolBar)
  {
    m_pToolBar->SetPosition(wxPoint(top_x, top_y));
    m_pToolBar->SetSize(wxSize(top_w, top_h));
  }
}


// ----------------------------------------------------------------------------
// Name: EditorCentral::SetViewport
// Desc: Set the D3D viewport
// ----------------------------------------------------------------------------
void EditorCentral::SetViewport()
{
  // Get our dimensions from the namespace
  using namespace EditorFrameDimensions;

  // Get the window info
  WINDOWINFO info;
  info.cbSize = sizeof(info);
  ::GetWindowInfo((HWND) WxDisplay::GetFrame()->GetHWND(), &info);

  // Get the client viewport
  int x = 0;
  int y = 0;
  int w = info.rcClient.right - info.rcClient.left;
  int h = info.rcClient.bottom - info.rcClient.top;

  // Deduct the status bar height
  wxStatusBar *pStatusBar = GetMainFrame()->GetStatusBar();
  if (pStatusBar)
  {
    h -= pStatusBar->GetSize().GetHeight();
  }

  // Get the d3d viewport
  D3DVIEWPORT9 viewport;
  Device->GetViewport(&viewport);

  viewport.X      = x + LeftFrameWidth;
  viewport.Y      = y + TopFrameHeight;
  viewport.Width  = w - (LeftFrameWidth + RightFrameWidth);
  viewport.Height = h - (TopFrameHeight + BottomFrameHeight);

  // Set the d3d viewport
  Device->SetViewport(&viewport);
}


// ----------------------------------------------------------------------------
// Name: EditorCentral::IsMouseOverViewport
// Desc: Test if the mouse is over the viewport
// ----------------------------------------------------------------------------
bool EditorCentral::IsMouseOverViewport()
{
  POINT ptCursor; 
  GetCursorPos(&ptCursor); 
  ScreenToClient(Application.GetHWND(), &ptCursor);

  VIEWPORT viewport;
  Device->GetViewport(&viewport);

  ptCursor.x -= (LONG) viewport.X;
  ptCursor.y -= (LONG) viewport.Y;

  if (ptCursor.x < 0)
    return false;

  if (ptCursor.x > (LONG) viewport.Width)
    return false;

  if (ptCursor.y < 0)
    return false;

  if (ptCursor.y > (LONG) viewport.Height)
    return false;

  return true;
}


// ----------------------------------------------------------------------------
// Name: EditorCentral::OnShutdown
// Desc: Shutdown the game
// ----------------------------------------------------------------------------
void EditorCentral::OnShutdown()
{
}


// ----------------------------------------------------------------------------
// Name: EditorCentral::OnResize
// Desc: The game window has been resized
// ----------------------------------------------------------------------------
void EditorCentral::OnResize()
{
  if (m_Initialised)
    UpdateFrameDimensions();
}


// ----------------------------------------------------------------------------
// Name: EditorCentral::OnMove
// Desc: The game window has been moved
// ----------------------------------------------------------------------------
void EditorCentral::OnMove()
{
  if (m_Initialised)
    UpdateFrameDimensions();
}


// ----------------------------------------------------------------------------
// Name: EditorCentral::App
// Desc: Do the application processing
// ----------------------------------------------------------------------------
void EditorCentral::App()
{
  m_pKeyboardInput->Update();
  m_pMouseInput->Update();
  m_pCameraManager->Update();
  m_pActionManager->Update();
  m_pBottomPanel->App();
  m_pDocument->App();

  if (Editor.GetMainFrame())
  {
    Editor.GetMainFrame()->UpdateControls();
  }
} // App


// ----------------------------------------------------------------------------
// Name: EditorCentral::Cull
// Desc: Do the cull processing
// ----------------------------------------------------------------------------
void EditorCentral::Cull()
{
  m_pDocument->Cull();
} // Cull


// ----------------------------------------------------------------------------
// Name: EditorCentral::Draw
// Desc: Draw the scene
// ----------------------------------------------------------------------------
void EditorCentral::Draw()
{
  // Begin rendering
  Device->BeginScene();

  // Set the viewport for the editor
  SetViewport();

  // Clear the background
  Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, Color::Gray, 1.0f, 0);

  // Draw the document
  m_pDocument->Draw();

  // Render the debug info
  DebugRender.Render();

  // Present the scene
  Device->EndScene();
  Device->Present(0, 0, 0, 0);

  // Set the application window title
  Application.SetWindowTitle(String("Editor (") + ToString((int) Application.GetFrameRate()) + String("fps)"));
} // Draw


// --------------------------------------------------------------------------
// Set the state of a menu option
// --------------------------------------------------------------------------
void EditorCentral::SetMenuOptionEnabled(EditorResource option, bool isEnabled)
{
  EditorMainFrame *pMainFrame = GetMainFrame();
  if (pMainFrame)
  {
    pMainFrame->SetMenuOptionEnabled(option, isEnabled);
  }
}


// --------------------------------------------------------------------------
// Get the main frame
// --------------------------------------------------------------------------
EditorMainFrame *EditorCentral::GetMainFrame()
{
  if (!m_Initialised)
    return NULL;

  WxDisplayFrame *pFrame = WxDisplay::GetFrame();
  NULL_ASSERT(pFrame);

  EditorMainFrame *pMainFrame = safe_cast<EditorMainFrame *>(pFrame);
  NULL_ASSERT(pMainFrame);

  return pMainFrame;
}


// --------------------------------------------------------------------------
// Get unique names
// --------------------------------------------------------------------------
String EditorCentral::GetNextName(const String &baseName)
{
  String trueName = baseName;
  uint suffix = 0;

  char c = trueName[trueName.length() - 1];
  while (c >= '0' && c <= '9')
  {
    suffix = (suffix * 10) + (c - '0');

    trueName.erase(trueName.length() - 1, 1);
    c = trueName[trueName.length() - 1];
  }

  Map<String, uint>::iterator iter = m_Names.find(trueName);
  if (iter == m_Names.end())
  {
    String name = trueName;
    AppendUInt(name, suffix);

    m_Names[trueName] = suffix;
    return name;
  }
  else
  {
    uint val = iter->second;
    val++;

    String name = trueName;
    AppendUInt(name, val);

    iter->second = val;
    return name;
  }
}


// --------------------------------------------------------------------------
// Load the name counters from the config file
// --------------------------------------------------------------------------
void EditorCentral::LoadNameCountersFromConfig(const ConfigSection &config)
{
  ResetNameCounters();

  ConfigValueMap::const_iterator iter(config.Items.begin()), end(config.Items.end());
  for (; iter != end; ++iter)
  {
    const ConfigValue &v = iter->second;
    m_Names[v.Key] = LexicalCast<uint>(v.Value);
  }
}


// --------------------------------------------------------------------------
// Save the name counters to the config file
// --------------------------------------------------------------------------
void EditorCentral::SaveNameCountersToConfig(ConfigSection &config)
{
  config.Type = "Editor";
  config.Name = "Names";

  Map<String, uint>::iterator iter(m_Names.begin()), end(m_Names.end());
  for (; iter != end; ++iter)
  {
    config.Set(iter->first, (int) iter->second);
  }
}


// --------------------------------------------------------------------------
// Reset the name counters
// --------------------------------------------------------------------------
void EditorCentral::ResetNameCounters()
{
  m_Names.clear();
}


// -- EOF

