// ----------------------------------------------------------------------------
// File: wxDirectXContext.cpp
// Desc: The WX module base class for directX
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#include "wxWindows/wxDirectXModule.h"


// ----------------------------------------------------------------------------
// Define the windows procedure to use
// ----------------------------------------------------------------------------
LRESULT WXDLLEXPORT APIENTRY _EXPORT wxWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


// ----------------------------------------------------------------------------
// Implement the module
// ----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC_CLASS(wxDirectXModule, wxModule)


// ----------------------------------------------------------------------------
// Static initialiser
// ----------------------------------------------------------------------------
bool wxDirectXModule::ms_registeredDirectXClasses = false;


// ----------------------------------------------------------------------------
// Register the windows classes
// ----------------------------------------------------------------------------
bool wxDirectXModule::RegisterClasses()
{
  if (ms_registeredDirectXClasses)
    return true;

  WNDCLASS wndclass;

  // the fields which are common to all classes
  wndclass.lpfnWndProc   = (WNDPROC)wxWndProc;
  wndclass.cbClsExtra    = 0;
  wndclass.cbWndExtra    = sizeof( DWORD );
  wndclass.hInstance     = wxhInstance;
  wndclass.hIcon         = (HICON) NULL;
  wndclass.hCursor       = ::LoadCursor((HINSTANCE)NULL, IDC_ARROW);
  wndclass.lpszMenuName  = NULL;

  // Register the Canvas class name
  wndclass.hbrBackground = CreateSolidBrush(0);
  wndclass.lpszClassName = wxDirectXCanvasClassName;
  wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_OWNDC | CS_BYTEALIGNCLIENT;

  if ( !::RegisterClass(&wndclass) )
  {
    wxLogLastError(wxT("RegisterClass(wxDirectXCanvasClass)"));
    return false;
  }

  wndclass.lpszClassName = wxDirectXCanvasClassNameNoRedraw;
  wndclass.style        &= ~(CS_HREDRAW | CS_VREDRAW);

  if ( !::RegisterClass(&wndclass) )
  {
    wxLogLastError(wxT("RegisterClass(wxDirectXCanvasClassNameNoRedraw)"));

    ::UnregisterClass(wxDirectXCanvasClassName, wxhInstance);

    return false;
  }

  ms_registeredDirectXClasses = true;

  return true;
}


// ----------------------------------------------------------------------------
// Unregister the windows classes
// ----------------------------------------------------------------------------
void wxDirectXModule::UnregisterClasses()
{
  if ( ms_registeredDirectXClasses )
  {
    ::UnregisterClass(wxDirectXCanvasClassName, wxhInstance);
    ::UnregisterClass(wxDirectXCanvasClassNameNoRedraw, wxhInstance);

    ms_registeredDirectXClasses = false;
  }
}


// -- EOF

