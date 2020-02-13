
#include "StaticMeshNode.h"
#include "Editor.h"


StaticMeshNode::StaticMeshNode(wxTreeItemId id)
: TreeNode(id, "StaticMeshNode")
{
  m_pMesh  = NULL;
  m_Matrix = MatrixIdentity;
  m_Pos    = Vec3(0.0f, 0.0f, 0.f);
  m_Rot    = Vec3(0.0f, 0.0f, 0.f);
  m_Scale  = Vec3(1.0f, 1.0f, 1.0f);

  m_BitField.Add(TREE_NODE_PICKABLE);
  m_BitField.Add(TREE_NODE_RENDERABLE);

  Editor.GetDocument()->SetDirty();
}


StaticMeshNode::~StaticMeshNode()
{
  Editor.GetDocument()->SetDirty();
}


void StaticMeshNode::OnEnter()
{
  if (m_pMesh)
  {
    Editor.GetLeftPanel()->GetScenePanel()->SetSelectedStaticMeshNode(this);
    TransformPanel *pTransformPanel = Editor.GetBottomPanel()->GetTransformPanel();
    pTransformPanel->SetPos(m_Pos.x, m_Pos.y, m_Pos.z);
    pTransformPanel->SetRot(m_Rot.x, m_Rot.y, m_Rot.z);
    pTransformPanel->SetScale(m_Scale.x, m_Scale.y, m_Scale.z);
  }
}


void StaticMeshNode::OnLeave()
{
  Editor.GetLeftPanel()->GetScenePanel()->SetSelectedStaticMeshNode(NULL);
  TransformPanel *pTransformPanel = Editor.GetBottomPanel()->GetTransformPanel();
  pTransformPanel->SetPos(0.0f, 0.0f, 0.0f);
  pTransformPanel->SetRot(0.0f, 0.0f, 0.0f);
  pTransformPanel->SetScale(1.0f, 1.0f, 1.0f);
}


void StaticMeshNode::SetRot(float h, float p, float r, bool updatePanel)
{
  if (m_pMesh)
  {
    m_Rot = Vec3(h, p, r);
    UpdateMatrix();

    Editor.GetDocument()->SetDirty();

    if (updatePanel)
    {
      TransformPanel *pTransformPanel = Editor.GetBottomPanel()->GetTransformPanel();
      pTransformPanel->SetRot(m_Rot.x, m_Rot.y, m_Rot.z);
    }
  }
}


void StaticMeshNode::SetPos(float x, float y, float z, bool updatePanel)
{
  if (m_pMesh)
  {
    m_Pos = Vec3(x, y, z);
    UpdateMatrix();

    Editor.GetDocument()->SetDirty();

    if (updatePanel)
    {
      TransformPanel *pTransformPanel = Editor.GetBottomPanel()->GetTransformPanel();
      pTransformPanel->SetPos(m_Pos.x, m_Pos.y, m_Pos.z);
    }
  }
}


void StaticMeshNode::SetScale(float x, float y, float z, bool updatePanel)
{
  if (m_pMesh)
  {
    m_Scale = Vec3(x, y, z);
    UpdateMatrix();

    Editor.GetDocument()->SetDirty();

    if (updatePanel)
    {
      TransformPanel *pTransformPanel = Editor.GetBottomPanel()->GetTransformPanel();
      pTransformPanel->SetScale(m_Scale.x, m_Scale.y, m_Scale.z);
    }
  }
}


void StaticMeshNode::UpdateMatrix()
{
  m_Matrix = Matrix::MakeNewPosRotScale(m_Pos, m_Rot, m_Scale);
}


void StaticMeshNode::Create(const String &meshName, const String &fileName)
{
  m_MeshName = meshName;
  m_FileName = fileName;

  ImageList *pImageList = Editor.GetImageList();
  SetIconId(pImageList->GetIndex("icon_package_open"), wxTreeItemIcon_Normal);
  SetText(m_MeshName);

  FileHandle handle = Application.GetModelDatabase()->FindFileHandle(m_FileName);
  m_pMesh = MeshLoader::LoadMesh(handle);
  if (!m_pMesh)
  {
    SetIconId(pImageList->GetIndex("action_stop"), wxTreeItemIcon_Normal);
    SetText(String("Error: " + m_MeshName));
  }
}


void StaticMeshNode::OnRightClick(const wxPoint &pos)
{
  wxMenu menu;

  wxMenuItem *pRenderItem   = menu.AppendCheckItem(MNU_RENDER_FLAG, "Render");
  wxMenuItem *pPickableItem = menu.AppendCheckItem(MNU_PICKABLE_FLAG, "Pick");
  wxMenuItem *pFrozenItem   = menu.AppendCheckItem(MNU_FROZEN_FLAG, "Frozen");

  pRenderItem->Check(GetBitField().Test(TREE_NODE_RENDERABLE));
  pPickableItem->Check(GetBitField().Test(TREE_NODE_PICKABLE));
  pFrozenItem->Check(GetBitField().Test(TREE_NODE_FROZEN));

  menu.AppendSeparator();
  menu.Append(MNU_DELETE_SELECTED, "Delete");

  PopupMenu(&menu, pos);
}


// -- EOF

