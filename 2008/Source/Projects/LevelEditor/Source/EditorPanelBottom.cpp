
#include "EditorPanelBottom.h"
#include "EditorResource.h"


EditorPanelBottom::EditorPanelBottom(EditorFrame *pParent)
: EditorPanel (pParent, EDT_BOTTOM_PANEL, "BOTTOM")
{
  m_pTransformPanel = new TransformPanel(this);
}


EditorPanelBottom::~EditorPanelBottom()
{
}


void EditorPanelBottom::UpdateControlLayout()
{
  const int offset = 2;

  wxSize size = GetSize();
  size.x -= (offset * 2);
  size.y -= (offset * 2);

  m_pTransformPanel->SetPosition(wxPoint(offset, offset));
  m_pTransformPanel->SetSize(size);
}


void EditorPanelBottom::App()
{
  static wxWindow *pWnd = NULL;

  if (!pWnd)
  {
    pWnd = wxWindow::FindFocus();
  }
  else
  {
    wxWindow *pThisWnd = wxWindow::FindFocus();

    if (pThisWnd != pWnd)
    {
      switch (pWnd->GetId())
      {
        case CTL_TRASNFORM_XPOS:
        case CTL_TRASNFORM_YPOS:
        case CTL_TRASNFORM_ZPOS:
        {
          wxCommandEvent e;
          m_pTransformPanel->OnPosChanged(e);
          break;
        }

        case CTL_TRASNFORM_XROT:
        case CTL_TRASNFORM_YROT:
        case CTL_TRASNFORM_ZROT:
        {
          wxCommandEvent e;
          m_pTransformPanel->OnRotChanged(e);
          break;
        }

        case CTL_TRASNFORM_XSCL:
        case CTL_TRASNFORM_YSCL:
        case CTL_TRASNFORM_ZSCL:
        {
          wxCommandEvent e;
          m_pTransformPanel->OnScaleChanged(e);
          break;
        }
      }

      pWnd = pThisWnd;
    }

  }
}


// -- EOF


