// ----------------------------------------------------------------------------
// File: wxDirectXContext.cpp
// Desc: The WX context base class for directX
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#include "wxWindows/wxDirectXContext.h"
#include "wxWindows/wxDirectXCanvas.h"


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
wxDirectXContext::wxDirectXContext(wxDirectXCanvas *win)
{
  REF_COUNT_CTOR(wxDirectXContext);

  m_window = win;
  m_hDC = win->GetHDC();
}


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
wxDirectXContext::~wxDirectXContext()
{
  REF_COUNT_DTOR(wxDirectXContext);
}


// -- EOF

