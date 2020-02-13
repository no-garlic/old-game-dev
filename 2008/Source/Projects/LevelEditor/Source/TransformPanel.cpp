
#include "TransformPanel.h"
#include "EditorResource.h"
#include "StaticMeshNode.h"
#include "Editor.h"
#include <wx\spinctrl.h>


BEGIN_EVENT_TABLE(TransformPanel, wxPanel)
  EVT_TEXT_ENTER      (CTL_TRASNFORM_XPOS, TransformPanel::OnPosChanged)
  EVT_TEXT_ENTER      (CTL_TRASNFORM_YPOS, TransformPanel::OnPosChanged)
  EVT_TEXT_ENTER      (CTL_TRASNFORM_ZPOS, TransformPanel::OnPosChanged)
  EVT_TEXT_ENTER      (CTL_TRASNFORM_XROT, TransformPanel::OnRotChanged)
  EVT_TEXT_ENTER      (CTL_TRASNFORM_YROT, TransformPanel::OnRotChanged)
  EVT_TEXT_ENTER      (CTL_TRASNFORM_ZROT, TransformPanel::OnRotChanged)
  EVT_TEXT_ENTER      (CTL_TRASNFORM_XSCL, TransformPanel::OnScaleChanged)
  EVT_TEXT_ENTER      (CTL_TRASNFORM_YSCL, TransformPanel::OnScaleChanged)
  EVT_TEXT_ENTER      (CTL_TRASNFORM_ZSCL, TransformPanel::OnScaleChanged)
END_EVENT_TABLE()


TransformPanel::TransformPanel(EditorPanel *pParent)
: wxPanel(pParent, EDT_TRANSFORM_PANEL)
{
  const int txtOffset  = 5;
  const int spinOffset = 3;
  const int txtWidth   = 50;

  m_AllowEvents = false;

  WX_STATIC(wxID_ANY, "Pos:", 8, txtOffset, -1, -1);

  WX_STATIC(wxID_ANY, "X", 40, txtOffset, -1, -1);
  WX_TEXT(CTL_TRASNFORM_XPOS, "0.0", 50, spinOffset, txtWidth, -1, wxTextValidator(wxFILTER_NUMERIC));

  WX_STATIC(wxID_ANY, "Y", 110, txtOffset, -1, -1);
  WX_TEXT(CTL_TRASNFORM_YPOS, "0.0", 120, spinOffset, txtWidth, -1, wxTextValidator(wxFILTER_NUMERIC));

  WX_STATIC(wxID_ANY, "Z", 180, txtOffset, -1, -1);
  WX_TEXT(CTL_TRASNFORM_ZPOS, "0.0", 190, spinOffset, txtWidth, -1, wxTextValidator(wxFILTER_NUMERIC));

  WX_STATIC(wxID_ANY, "Rot:", 258, txtOffset, -1, -1);

  WX_STATIC(wxID_ANY, "Y", 290, txtOffset, -1, -1);
  WX_TEXT(CTL_TRASNFORM_XROT, "0.0", 300, spinOffset, txtWidth, -1, wxTextValidator(wxFILTER_NUMERIC));

  WX_STATIC(wxID_ANY, "P", 360, txtOffset, -1, -1);
  WX_TEXT(CTL_TRASNFORM_YROT, "0.0", 370, spinOffset, txtWidth, -1, wxTextValidator(wxFILTER_NUMERIC));

  WX_STATIC(wxID_ANY, "R", 430, txtOffset, -1, -1);
  WX_TEXT(CTL_TRASNFORM_ZROT, "0.0", 440, spinOffset, txtWidth, -1, wxTextValidator(wxFILTER_NUMERIC));

  WX_STATIC(wxID_ANY, "Scale:", 508, txtOffset, -1, -1);

  WX_STATIC(wxID_ANY, "X", 540, txtOffset, -1, -1);
  WX_TEXT(CTL_TRASNFORM_XSCL, "1.0", 550, spinOffset, txtWidth, -1, wxTextValidator(wxFILTER_NUMERIC));

  WX_STATIC(wxID_ANY, "Y", 610, txtOffset, -1, -1);
  WX_TEXT(CTL_TRASNFORM_YSCL, "1.0", 620, spinOffset, txtWidth, -1, wxTextValidator(wxFILTER_NUMERIC));

  WX_STATIC(wxID_ANY, "Z", 680, txtOffset, -1, -1);
  WX_TEXT(CTL_TRASNFORM_ZSCL, "1.0", 690, spinOffset, txtWidth, -1, wxTextValidator(wxFILTER_NUMERIC));

  m_PosX = m_PosY = m_PosZ = m_RotX = m_RotY = m_RotZ = m_ScaleX = m_ScaleY = m_ScaleZ = 0.0f;

  m_AllowEvents = true;
}


TransformPanel::~TransformPanel()
{
}


void TransformPanel::GetPos(float &x, float &y, float &z) const
{
  x = m_PosX;
  y = m_PosY;
  z = m_PosZ;
}


void TransformPanel::SetPos(float x, float y, float z)
{
  m_PosX = x;
  m_PosY = y;
  m_PosZ = z;

  wxTextCtrl *pX = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_XPOS);
  wxTextCtrl *pY = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_YPOS);
  wxTextCtrl *pZ = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_ZPOS);
  NULL_ASSERT(pX && pY && pZ);

  pX->SetValue(wxFloatToStr(x));
  pY->SetValue(wxFloatToStr(y));
  pZ->SetValue(wxFloatToStr(z));
}


void TransformPanel::GetRot(float &x, float &y, float &z) const
{
  x = m_RotX;
  y = m_RotY;
  z = m_RotZ;
}


void TransformPanel::SetRot(float x, float y, float z)
{
  m_RotX = x;
  m_RotY = y;
  m_RotZ = z;

  wxTextCtrl *pX = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_XROT);
  wxTextCtrl *pY = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_YROT);
  wxTextCtrl *pZ = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_ZROT);
  NULL_ASSERT(pX && pY && pZ);

  pX->SetValue(wxFloatToStr(x));
  pY->SetValue(wxFloatToStr(y));
  pZ->SetValue(wxFloatToStr(z));
}


void TransformPanel::GetScale(float &x, float &y, float &z) const
{
  x = m_ScaleX;
  y = m_ScaleY;
  z = m_ScaleZ;
}


void TransformPanel::SetScale(float x, float y, float z)
{
  m_ScaleX = x;
  m_ScaleY = y;
  m_ScaleZ = z;

  wxTextCtrl *pX = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_XSCL);
  wxTextCtrl *pY = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_YSCL);
  wxTextCtrl *pZ = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_ZSCL);
  NULL_ASSERT(pX && pY && pZ);

  pX->SetValue(wxFloatToStr(x));
  pY->SetValue(wxFloatToStr(y));
  pZ->SetValue(wxFloatToStr(z));
}


void TransformPanel::OnPosChanged(wxCommandEvent& event)
{
  if (m_AllowEvents)
  {
    wxTextCtrl *pX = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_XPOS);
    wxTextCtrl *pY = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_YPOS);
    wxTextCtrl *pZ = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_ZPOS);
    NULL_ASSERT(pX && pY && pZ);

    float x = wxStrToFloat(pX->GetValue());
    float y = wxStrToFloat(pY->GetValue());
    float z = wxStrToFloat(pZ->GetValue());

    if (x != m_PosX || y != m_PosY || z != m_PosZ)
    {
      m_PosX = x;
      m_PosY = y;
      m_PosZ = z;

      LOG_INFO << "Pos Changed: " << x << ", " << y << ", " << z << ENDLOG;

      StaticMeshNode *pMeshNode = Editor.GetLeftPanel()->GetScenePanel()->GetSelectedStaticMeshNode();
      if (pMeshNode)
      {
        String path;
        pMeshNode->GetPath(path);

        m_AllowEvents = false;
        if (!Editor.GetActionManager()->CreateAction(ActionManager::ACTION_STATIC_MESH_TRANSFORM, path))
        {
          // Failed

          Editor.GetActionManager()->DiscardAction();
          m_AllowEvents = true;
        }

        Editor.GetActionManager()->SetActionParameter("Pos", Vec3(m_PosX, m_PosY, m_PosZ));
        Editor.GetActionManager()->CompleteAction();
        m_AllowEvents = true;
      }
    }
  }
}


void TransformPanel::OnRotChanged(wxCommandEvent& event)
{
  if (m_AllowEvents)
  {
    wxTextCtrl *pX = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_XROT);
    wxTextCtrl *pY = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_YROT);
    wxTextCtrl *pZ = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_ZROT);
    NULL_ASSERT(pX && pY && pZ);

    float x = wxStrToFloat(pX->GetValue());
    float y = wxStrToFloat(pY->GetValue());
    float z = wxStrToFloat(pZ->GetValue());

    if (x != m_RotX || y != m_RotY || z != m_RotZ)
    {
      m_RotX = x;
      m_RotY = y;
      m_RotZ = z;

      LOG_INFO << "Rot Changed: " << x << ", " << y << ", " << z << ENDLOG;

      StaticMeshNode *pMeshNode = Editor.GetLeftPanel()->GetScenePanel()->GetSelectedStaticMeshNode();
      if (pMeshNode)
      {
        String path;
        pMeshNode->GetPath(path);

        m_AllowEvents = false;
        if (!Editor.GetActionManager()->CreateAction(ActionManager::ACTION_STATIC_MESH_TRANSFORM, path))
        {
          // Failed

          Editor.GetActionManager()->DiscardAction();
          m_AllowEvents = true;
        }

        Editor.GetActionManager()->SetActionParameter("Rot", Vec3(m_RotX, m_RotY, m_RotZ));
        Editor.GetActionManager()->CompleteAction();
        m_AllowEvents = true;
      }
    }
  }
}


void TransformPanel::OnScaleChanged(wxCommandEvent& event)
{
  if (m_AllowEvents)
  {
    wxTextCtrl *pX = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_XSCL);
    wxTextCtrl *pY = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_YSCL);
    wxTextCtrl *pZ = (wxTextCtrl *) this->FindItem(CTL_TRASNFORM_ZSCL);
    NULL_ASSERT(pX && pY && pZ);

    wxString val1 = pX->GetValue();
    wxString val2 = pY->GetValue();
    wxString val3 = pZ->GetValue();

    float x = wxStrToFloat(pX->GetValue());
    float y = wxStrToFloat(pY->GetValue());
    float z = wxStrToFloat(pZ->GetValue());

    if (x != m_ScaleX || y != m_ScaleY || z != m_ScaleZ)
    {
      m_ScaleX = x;
      m_ScaleY = y;
      m_ScaleZ = z;

      LOG_INFO << "Scale Changed: " << x << ", " << y << ", " << z << ENDLOG;

      StaticMeshNode *pMeshNode = Editor.GetLeftPanel()->GetScenePanel()->GetSelectedStaticMeshNode();
      if (pMeshNode)
      {
        String path;
        pMeshNode->GetPath(path);

        m_AllowEvents = false;
        if (!Editor.GetActionManager()->CreateAction(ActionManager::ACTION_STATIC_MESH_TRANSFORM, path))
        {
          // Failed

          Editor.GetActionManager()->DiscardAction();
          m_AllowEvents = true;
        }

        Editor.GetActionManager()->SetActionParameter("Scale", Vec3(m_ScaleX, m_ScaleY, m_ScaleZ));
        Editor.GetActionManager()->CompleteAction();
        m_AllowEvents = true;
      }
    }
  }
}


// -- EOF

