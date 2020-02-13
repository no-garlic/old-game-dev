
#include "EditorDocument.h"
#include "StaticMeshNode.h"
#include "SceneGroupNode.h"
#include "Editor.h"


#define DEBUG_PICKING 0
#define HACK_COLOR_MATERIAL 1


// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
EditorDocument::EditorDocument()
{
  m_BoundingSphere.Reset();

  m_Dirty           = false;
  m_FileExists      = false;

  m_ViewMode        = VIEW_NORMAL;

  m_pSelectedMeshMaterial   = NULL;
  m_pFrozenMeshMaterial     = NULL;
  m_pWireframeMeshMaterial  = NULL;
  m_pNoTexMaterial          = NULL;
}



// --------------------------------------------------------------------------
// Destructor
// --------------------------------------------------------------------------
EditorDocument::~EditorDocument()
{
  delete m_pSelectedMeshMaterial;
  delete m_pFrozenMeshMaterial;
  delete m_pWireframeMeshMaterial;
  delete m_pNoTexMaterial;
}


// --------------------------------------------------------------------------
// Initialise the document
// --------------------------------------------------------------------------
bool EditorDocument::Init()
{
  // Create the materials
  m_pSelectedMeshMaterial   = new SelectedMeshMaterial();
  m_pFrozenMeshMaterial     = new SelectedMeshMaterial();
  m_pWireframeMeshMaterial  = new SelectedMeshMaterial();
  m_pNoTexMaterial          = new SelectedMeshMaterial();

  // Set the selected and frozen colors
  m_pSelectedMeshMaterial->ForceColor(Color(0.35f, 0.0f, 0.0f), Color(0.35f, 0.15f, 0.15f));
  m_pFrozenMeshMaterial->ForceColor(Color(0.45f, 0.45f, 0.75f), Color(0.15f, 0.15f, 0.35f));
  m_pWireframeMeshMaterial->ForceColor(Color::White, Color::White);
  m_pNoTexMaterial->ForceColor(Color(0.6f, 0.6f, 0.9f), Color(0.3f, 0.3f, 0.9f));

  // Set the override materials
  m_SelectedRenderList.SetGlobalOverrideMaterial(m_pSelectedMeshMaterial);
  m_FrozenRenderList.SetGlobalOverrideMaterial(m_pFrozenMeshMaterial);
  m_WireframeRenderList.SetGlobalOverrideMaterial(m_pWireframeMeshMaterial);
  m_NoTexRenderList.SetGlobalOverrideMaterial(m_pNoTexMaterial);

  // Initialise the environment
  InitEnvironment();
  m_Lights.clear();
  m_Lights.push_back(&m_DirectionalLight);

  return true;
}


// --------------------------------------------------------------------------
// Set the document's dirty state
// --------------------------------------------------------------------------
void EditorDocument::SetDirty(bool dirty)
{
  // Flag the document as dirty
  m_Dirty = dirty;
}


// --------------------------------------------------------------------------
// Set the device render states
// --------------------------------------------------------------------------
void EditorDocument::SetRenderState()
{
  // Set the render states
  RenderState.Set(D3DRS_CULLMODE, D3DCULL_CCW);

  // Set the sampler states
  Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

  // Set Antialias
  if (Application.IsAntialias())
  {
    RenderState.Set(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
  }

  // Enable the lights
  for (uint i = 0; i < m_Lights.size(); i++)
  {
    Device->SetLight(i, m_Lights[i]);
    Device->LightEnable(i, TRUE);
  }

  ApplyEnvironment();
}


// --------------------------------------------------------------------------
// Update the document
// --------------------------------------------------------------------------
void EditorDocument::App()
{
  SetRenderState();
}


// --------------------------------------------------------------------------
// Cull the scene
// --------------------------------------------------------------------------
void EditorDocument::Cull()
{
  // Cull the entire tree view against the camera frustum
  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
  TreeNode *pRootNode = pTreeView->GetRootNode();
  CullNode(pRootNode);
}


// --------------------------------------------------------------------------
// Cull the specified node (recursive)
// --------------------------------------------------------------------------
void EditorDocument::CullNode(TreeNode *pNode)
{
  for (uint i = 0; i < pNode->GetChildrenCount(); i++)
  {
    TreeNode *pChild = pNode->GetChild(i);

    // Check that the node is flagged as renderable
    if (pChild->GetBitField().Test(TREE_NODE_RENDERABLE) == false)
    {
      continue;
    }

    if (pChild->GetType() == "StaticMeshNode")
    {
      StaticMeshNode *pMeshNode = (StaticMeshNode *) pChild;
      if (pMeshNode->GetMesh())
      {
        Sphere s = pMeshNode->GetMesh()->GetBSphere();
        s.center += pMeshNode->GetMatrix().GetTAxis();
        if (Camera.GetFrustum().Intersects(s) != Frustum::OUT_FRUSTUM)
        {
#if HACK_COLOR_MATERIAL
          uint numSubsets = pMeshNode->GetMesh()->GetNumSubsets();
          for (uint j = 0; j < numSubsets; j++)
          {
            MeshSubset *pSubset = pMeshNode->GetMesh()->GetSubset(j);
            
            D3DCOLORVALUE v;
            D3DMATERIAL material = pSubset->GetColorMaterial();

            v.a = v.r = v.g = v.b = 1.0f;
            material.Diffuse  = v;
            material.Specular = v;

            v.r = v.g = v.b = 0.5f;
            material.Ambient  = v;

            pSubset->SetColorMaterial(material);
          }
#endif
          AddToRenderList(pMeshNode);
        }
      }
    }
    else if (pChild->GetType() == "SceneGroupNode")
    {
      CullNode(pChild);
    }
  }
}


// --------------------------------------------------------------------------
// Add a static mesh node to the correct render list
// --------------------------------------------------------------------------
void EditorDocument::AddToRenderList(StaticMeshNode *pNode)
{
  if (m_ViewMode == VIEW_WIREFRAME)
  {
    // If the node is selected, add it to the selected render list
    StaticMeshNode *pSelectedNode = Editor.GetLeftPanel()->GetScenePanel()->GetSelectedStaticMeshNode();
    if (pSelectedNode == pNode)
    {
      m_SelectedRenderList.Add(pNode->GetMesh(), pNode->GetMatrix());
      return;
    }

    // Otherwise add it to the general render list
    m_WireframeRenderList.Add(pNode->GetMesh(), pNode->GetMatrix());
    return;
  }

  // If the node is frozen then add it to the frozen render list (alpha sorted)
  if (pNode->GetBitField().Test(TREE_NODE_FROZEN))
  {
    m_FrozenRenderList.Add(pNode->GetMesh(), pNode->GetMatrix());

    if (m_ViewMode == VIEW_NORMAL_WIREOVER)
    {
      m_WireframeRenderList.Add(pNode->GetMesh(), pNode->GetMatrix());
    }
    return;
  }

  // If the node is selected, add it to the selected render list
  StaticMeshNode *pSelectedNode = Editor.GetLeftPanel()->GetScenePanel()->GetSelectedStaticMeshNode();
  if (pSelectedNode == pNode)
  {
    m_SelectedRenderList.Add(pNode->GetMesh(), pNode->GetMatrix());

    if (m_ViewMode == VIEW_NORMAL_WIREOVER)
    {
      m_WireframeRenderList.Add(pNode->GetMesh(), pNode->GetMatrix());
    }
    return;
  }

  // Add it to the general or no tex render list
  if (m_ViewMode == VIEW_NOTEX)
  {
    m_NoTexRenderList.Add(pNode->GetMesh(), pNode->GetMatrix());
  }
  else
  {
    m_RenderList.Add(pNode->GetMesh(), pNode->GetMatrix());

    if (m_ViewMode == VIEW_NORMAL_WIREOVER)
    {
      // If the node is selected, add it to the selected render list
      StaticMeshNode *pSelectedNode = Editor.GetLeftPanel()->GetScenePanel()->GetSelectedStaticMeshNode();
      if (pSelectedNode == pNode)
      {
        m_SelectedRenderList.Add(pNode->GetMesh(), pNode->GetMatrix());
      }

      // Otherwise add it to the general render list
      else
      {
        m_WireframeRenderList.Add(pNode->GetMesh(), pNode->GetMatrix());
      }
    }
  }  
}


// --------------------------------------------------------------------------
// Render the document
// --------------------------------------------------------------------------
void EditorDocument::Draw()
{
  // Wireframe
  if (m_ViewMode == VIEW_WIREFRAME)
  {
    RenderState.Set(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
    RenderState.Set(D3DRS_LIGHTING, FALSE);

    m_WireframeRenderList.Render(m_Lights);
    m_SelectedRenderList.Render(m_Lights);

    RenderState.SetDefault(D3DRS_FILLMODE);
    RenderState.SetDefault(D3DRS_LIGHTING);
    return;
  }

  // Unlit
  else if (m_ViewMode == VIEW_UNLIT)
  {
    m_pSelectedMeshMaterial->SetLightingMode(false);
    m_pFrozenMeshMaterial->SetLightingMode(false);

    RenderState.Set(D3DRS_LIGHTING, FALSE);
    m_RenderList.Render(m_Lights);

    RenderState.Set(D3DRS_LIGHTING, TRUE);
    m_SelectedRenderList.Render(m_Lights);
    m_FrozenRenderList.Render(m_Lights);

    m_pSelectedMeshMaterial->SetLightingMode(true);
    m_pFrozenMeshMaterial->SetLightingMode(true);
  }

  // No Textures
  else if (m_ViewMode == VIEW_NOTEX)
  {
    RenderState.Set(D3DRS_LIGHTING, TRUE);

    m_NoTexRenderList.Render(m_Lights);
    m_SelectedRenderList.Render(m_Lights);
    m_FrozenRenderList.Render(m_Lights);
  }

  // Normal
  else if (m_ViewMode == VIEW_NORMAL)
  {
    RenderState.Set(D3DRS_LIGHTING, TRUE);

    m_RenderList.Render(m_Lights);
    m_SelectedRenderList.Render(m_Lights);
    m_FrozenRenderList.Render(m_Lights);
  }

  // Normal with Wire Over
  else if (m_ViewMode == VIEW_NORMAL_WIREOVER)
  {
    RenderState.Set(D3DRS_LIGHTING, TRUE);

    m_RenderList.Render(m_Lights);
    m_SelectedRenderList.Render(m_Lights);
    m_FrozenRenderList.Render(m_Lights);

    float fDepthBias = -1.0f;
    ulong depthBias = FLOAT_TO_DWORD(fDepthBias);
    RenderState.Set(D3DRS_SLOPESCALEDEPTHBIAS, depthBias);
    RenderState.Set(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
    RenderState.Set(D3DRS_LIGHTING, FALSE);

    m_WireframeRenderList.Render(m_Lights);
    m_SelectedRenderList.Render(m_Lights);

    RenderState.SetDefault(D3DRS_SLOPESCALEDEPTHBIAS);
    RenderState.SetDefault(D3DRS_FILLMODE);
    RenderState.SetDefault(D3DRS_LIGHTING);
  }

  // Reset lighting
  RenderState.SetDefault(D3DRS_LIGHTING);
}


// --------------------------------------------------------------------------
// Close a file and reset the document
// --------------------------------------------------------------------------
bool EditorDocument::New()
{
  if (m_Dirty)
  {
    DoSave(true);
  }

  Editor.GetLeftPanel()->GetScenePanel()->Clear();
  Editor.ResetNameCounters();
  InitEnvironment();

  m_FileExists = false;
  m_Dirty = false;

  return true;
}


// --------------------------------------------------------------------------
// Close a file and reset the document
// --------------------------------------------------------------------------
bool EditorDocument::Close()
{
  if (m_Dirty)
  {
    DoSave(true);
  }

  Editor.GetLeftPanel()->GetScenePanel()->Clear();
  Editor.ResetNameCounters();
  InitEnvironment();

  m_FileExists = false;
  m_Dirty = false;

  return true;
}


// --------------------------------------------------------------------------
// Load a level file
// --------------------------------------------------------------------------
bool EditorDocument::Open()
{
  if (m_Dirty)
  {
    DoSave(true);
  }

  FileHandle handle;
  if (!GetOpenFileHandle(handle))
  {
    return false;
  }

  ConfigFile cfg;
  cfg.Load(handle.GetAbsoluteFilename());

  bool active = Editor.GetUndoManager()->IsActive();
  Editor.GetUndoManager()->SetActive(false);
  bool loaded = LoadFromConfig(cfg);
  Editor.GetUndoManager()->SetActive(active);

  if (!loaded)
  {
    Editor.GetLeftPanel()->GetScenePanel()->Clear();
    Editor.ResetNameCounters();
    wxMessageBox("Load Failed!!!", "Error", wxCANCEL | wxCENTRE);
    m_FileExists = false;
    m_Dirty = false;
    return false;
  }

  m_FileHandle = handle;
  m_FileExists = true;
  m_Dirty      = false;

  // Expand the root node of the tree view
  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
  pTreeView->UnSelect();
  TreeNode *pRootNode = pTreeView->GetRootNode();
  pRootNode->Expand();

  // Focus the camera on the entire scene
  PreCacheSceneBounds();
  Editor.GetCameraManager()->SetCurrentCamera(CAM_PERSPECTIVE);
  Editor.GetCameraManager()->Focus();

  return true;
}


// --------------------------------------------------------------------------
// Save to an existing file if exists, otherwise calls save as
// --------------------------------------------------------------------------
bool EditorDocument::Save()
{
  if (m_Dirty)
  {
    if (!m_FileExists)
    {
      return SaveAs();
    }
    else if (DoSave(false) != RES_OK)
    {
      return false;
    }
  }

  m_Dirty = false;
  m_FileExists = true;

  return true;
}


// --------------------------------------------------------------------------
// Save to a new file
// --------------------------------------------------------------------------
bool EditorDocument::SaveAs()
{
  bool fileExists = m_FileExists;
  m_FileExists = false;

  if (DoSave(false) != RES_OK)
  {
    m_FileExists = fileExists;
    return false;
  }

  m_Dirty = false;
  m_FileExists = true;

  return true;
}


// --------------------------------------------------------------------------
// Generic save function that handles save / save as depeiding if the file exists
// --------------------------------------------------------------------------
EditorDocument::SaveResult EditorDocument::DoSave(bool showPrompt)
{
  if (showPrompt)
  {
    if (wxMessageBox("Save?", "Question", wxYES | wxNO | wxCENTRE) == wxNO)
    {
      return EditorDocument::RES_CANCEL;
    }
  }

  if (!m_FileExists)
  {
    if (!GetSaveFileHandle(m_FileHandle))
    {
      return EditorDocument::RES_CANCEL;
    }
  }

  ConfigFile cfg;
  if (!SaveToConfig(cfg))
  {
    return EditorDocument::RES_FAIL;
  }

  if (!cfg.SaveAs(m_FileHandle.GetAbsoluteFilename()))
  {
    return EditorDocument::RES_FAIL;
  }

  m_FileExists = true;
  m_Dirty      = false;

  return EditorDocument::RES_OK;
}


// --------------------------------------------------------------------------
// Show a dialog for the user to select a file to load
// --------------------------------------------------------------------------
bool EditorDocument::GetOpenFileHandle(FileHandle &handle)
{
  const String &defaultDir = Application.GetLevelDatabase()->GetAbsolutePath();

  long style = wxOPEN;
  wxFileDialog dialog(WxDisplay::GetFrame(), wxString("Open File"), wxString(defaultDir.c_str()), wxEmptyString, "*.lev", style);

  if (dialog.ShowModal() && dialog.GetFilename().Length() > 0)
  {
    handle = Application.GetLevelDatabase()->MakeFileHandle(dialog.GetFilename().wx_str());
    if (handle.Exists())
    {
      return true;
    }
  }

  return false;
}


// --------------------------------------------------------------------------
// Show a dialog for the user to select a file to save to
// --------------------------------------------------------------------------
bool EditorDocument::GetSaveFileHandle(FileHandle &handle)
{
  const String &defaultDir = Application.GetLevelDatabase()->GetAbsolutePath();

  long style = wxSAVE | wxOVERWRITE_PROMPT;
  wxFileDialog dialog(WxDisplay::GetFrame(), wxString("Save File"), wxString(defaultDir.c_str()), wxEmptyString, "*.lev", style);

  if (dialog.ShowModal() && dialog.GetFilename().Length() > 0)
  {
    handle = Application.GetLevelDatabase()->MakeFileHandle(dialog.GetFilename().wx_str());
    return true;
  }

  return false;
}


// --------------------------------------------------------------------------
// See if the camera - mouse ray intersects any obejct
// --------------------------------------------------------------------------
TreeNode *EditorDocument::Pick()
{
  TreeNodeId id;
  if (TestPick(id))
  {
    TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
    TreeNode *pNode = pTreeView->FindTreeNode(id);

    return pNode;
  }

  return NULL;
}


// --------------------------------------------------------------------------
// See if the camera - mouse ray intersects any object
// --------------------------------------------------------------------------
bool EditorDocument::Pick(String &path)
{
  TreeNode *pNode = Pick();

  if (!pNode)
  {
    return false;
  }

  pNode->GetPath(path);
  return true;
}


// --------------------------------------------------------------------------
// Test if the mouse - camera ray intersects the specified node
// --------------------------------------------------------------------------
bool EditorDocument::TestPick(TreeNodeId &id)
{
  // Get the mouse ray into the scene
  Ray ray = Camera.GetMouseRay3D();

  // Get the root node
  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
  TreeNode *pRootNode = pTreeView->GetRootNode();

  // Test against all bounding spheres
  Array<PickInfo> pickInfo;
  TestPickNode(pRootNode, ray, pickInfo);

  // Return if no objects hit
  if (pickInfo.empty())
  {
    return false;
  }

  // Get the closest hit
  float closestDist  = 0.0f;
  uint  closestIndex = 0xffffffff;

  // Find closest geometry hit
  for (uint i = 0; i < pickInfo.size(); i++)
  {
    // Get the pick info for each hit
    EditorDocument::PickInfo &info = pickInfo[i];

    // Transform the ray into model space
    Matrix invMat = info.Transform;
    invMat.Inverse();
    Ray transformedRay(ray, invMat); 

#if DEBUG_PICKING

    Sphere meshSphere = info.pMesh->GetBSphere();
    meshSphere.center += info.Transform.GetTAxis();
    meshSphere.radius *= info.Transform.GetScaleMax();

    DEBUG_SPHERE(meshSphere, Color::Yellow, 1000);

#endif

    // Get the closest geometry intersection
    Vec3  hitPt;
    float dist;

    // See if the ray intersects the geometry within the bounding sphere
    if (info.pMesh->Intersects(transformedRay, hitPt, dist))
    {
      // Record this hit as the closest hit if it is the first hit, or the closest hit to the camera eye
      if (closestIndex == 0xffffffff || dist < closestDist)
      {
        closestDist  = dist;
        closestIndex = i;
      }
    }
  }

  // Check if we actually intersected geometry
  if (closestIndex == 0xffffffff)
  {
    return false;
  }

  // Assign the id of the mesh tree node
  id = pickInfo[closestIndex].Id;
  return true;
}


// --------------------------------------------------------------------------
// Find all objects that the camer - mouse ray is intersecting
// --------------------------------------------------------------------------
void EditorDocument::TestPickNode(TreeNode *pNode, const Ray &ray, Array<PickInfo> &pickInfo)
{
  for (uint i = 0; i < pNode->GetChildrenCount(); i++)
  {
    TreeNode *pChild = pNode->GetChild(i);

    // Check that the node is flagged as pickable and not frozen
    if (pChild->GetBitField().Test(TREE_NODE_PICKABLE) == false || 
        pChild->GetBitField().Test(TREE_NODE_FROZEN) == true    ||
        pChild->GetBitField().Test(TREE_NODE_RENDERABLE) == false)
    {
      continue;
    }

    if (pChild->GetType() == "StaticMeshNode")
    {
      StaticMeshNode *pMeshNode = (StaticMeshNode *) pChild;
      if (pMeshNode->GetMesh())
      {
        Sphere s = pMeshNode->GetMesh()->GetBSphere();
        s.center += pMeshNode->GetMatrix().GetTAxis();
        s.radius *= pMeshNode->GetMatrix().GetScaleMax();

        if (ray.TestCollision(s))
        {
          EditorDocument::PickInfo info;
          info.pMesh      = pMeshNode->GetMesh();
          info.Transform  = pMeshNode->GetMatrix();
          info.Id         = pMeshNode->GetId();
          pickInfo.push_back(info);

#if DEBUG_PICKING

          Sphere dbgSphere = info.pMesh->GetBSphere();
          dbgSphere.center += info.Transform.GetTAxis();
          dbgSphere.radius = 2.0f;
          DEBUG_SPHERE(dbgSphere, Color::Red, 1000);

#endif
        }
      }
    }
    else if (pChild->GetType() == "SceneGroupNode")
    {
      TestPickNode(pChild, ray, pickInfo);
    }
  }
}


// --------------------------------------------------------------------------
// Save the level to the config file
// --------------------------------------------------------------------------
bool EditorDocument::SaveToConfig(ConfigFile &cfg)
{
  // Get the root node
  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
  TreeNode *pRootNode = pTreeView->GetRootNode();

  // Save the root node (and all children) to the config file
  SceneGroupNode *pGroupNode = (SceneGroupNode *) pRootNode;
  ConfigSection &rootSection = cfg.AddSection("Scene", pRootNode->GetText());

  for (uint i = 0; i < pGroupNode->GetChildrenCount(); i++)
  {
    TreeNode *pChild = pGroupNode->GetChild(i);
    if (!SaveNodeToConfig(pChild, rootSection))
      return false;
  }

  // Save the environment settings to the file
  ConfigSection &envSection = cfg.AddSection("Environment", "Global");
  if (!SaveEnvironmentToConfig(envSection))
  {
    return false;
  }

  // Save the name counters to the file
  ConfigSection &namesSection = cfg.AddSection("Editor", "Names");
  Editor.SaveNameCountersToConfig(namesSection);

  return true;
}


// --------------------------------------------------------------------------
// Save a particular node to the config section
// --------------------------------------------------------------------------
bool EditorDocument::SaveNodeToConfig(TreeNode *pNode, ConfigSection &cfg)
{
  // Save the group node
  if (pNode->GetType() == "SceneGroupNode")
  {
    SceneGroupNode *pGroupNode = (SceneGroupNode *) pNode;
    ConfigSection &section = cfg.AddSection("Group", pGroupNode->GetText());

    for (uint i = 0; i < pNode->GetChildrenCount(); i++)
    {
      TreeNode *pChild = pNode->GetChild(i);
      if (!SaveNodeToConfig(pChild, section))
        return false;
    }

    return true;
  }

  // Save the static mesh node
  else if (pNode->GetType() == "StaticMeshNode")
  {
    StaticMeshNode *pMeshNode = (StaticMeshNode *) pNode;
    ConfigSection &section = cfg.AddSection("Mesh", pMeshNode->GetText());

    section.Set("File", pMeshNode->GetMesh()->GetFileHandle().GetFilename());
    section.Set("Flags", pMeshNode->GetBitField().Get());
    section.Set("Pos",  pMeshNode->GetPos().ToString());
    section.Set("Rot",  pMeshNode->GetRot().ToString());
    section.Set("Scl",  pMeshNode->GetScale().ToString());
    return true;
  }

  // Save the light node
  else if (pNode->GetType() == "LightNode")
  {
    // TODO
    DEBUG_BREAK;
  }

  return false;
}


// --------------------------------------------------------------------------
// Load the level from the config file
// --------------------------------------------------------------------------
bool EditorDocument::LoadFromConfig(ConfigFile &cfg)
{
  // Clear the tree
  Editor.GetLeftPanel()->GetScenePanel()->Clear();

  // Get the root node
  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
  TreeNode *pRootNode = pTreeView->GetRootNode();

  const ConfigSectionMap &sections = cfg.GetSections();

  bool sceneLoaded = false;
  bool sceneAttempted = false;

  Editor.ResetNameCounters();

  ConfigSectionMap::const_iterator iter(sections.begin()), end(sections.end());
  for (; iter != end; ++iter)
  {
    const ConfigSection &section = iter->second;

    if (StrICmp(section.Type, "Scene"))
    {
      if (sceneAttempted)
      {
        LOG_ERROR << "Multiple scene sections found" << ENDLOG;
        return false;
      }

      pRootNode->SetText(section.Name);
      sceneLoaded = LoadNodeFromConfig((SceneGroupNode*) pRootNode, section);
      sceneAttempted = true;
    }
    else if (StrICmp(section.Type, "Editor"))
    {
      if (StrICmp(section.Name, "Names"))
      {
        Editor.LoadNameCountersFromConfig(section);
      }
    }
    else if (StrICmp(section.Type, "Environment"))
    {
      if (!LoadEnvironmentFromConfig(section))
      {
        LOG_WARNING << "Failed to load the environment settings from the level file" << ENDLOG;
        InitEnvironment();

        // TODO: Show a message box
      }
    }
  }

  if (!sceneAttempted || !sceneLoaded)
  {
    return false;
  }

  return true;
}


// --------------------------------------------------------------------------
// Load a particular node from a config section
// --------------------------------------------------------------------------
bool EditorDocument::LoadNodeFromConfig(SceneGroupNode *pNode, const ConfigSection &cfg)
{
  ConfigSectionMap::const_iterator iter(cfg.ChildSections.begin()), end(cfg.ChildSections.end());
  for (; iter != end; ++iter)
  {
    const ConfigSection &childSection = iter->second;

    if (StrICmp(childSection.Type, "Group"))
    {
      SceneGroupNode *pGroupNode = pNode->AddChild<SceneGroupNode>(childSection.Name);
      pGroupNode->Create();

      if (!LoadNodeFromConfig(pGroupNode, childSection))
        return false;
    }

    else if (StrICmp(childSection.Type, "Mesh"))
    {
      StaticMeshNode *pMeshNode = pNode->AddChild<StaticMeshNode>(childSection.Name);

      String fileName = childSection("File");
      pMeshNode->Create(childSection.Name, fileName);

      if (!pMeshNode->GetMesh())
        return false;

      String flagsStr = childSection("Flags").Value;
      if (flagsStr.size())
      {
        uint flags = LexicalCast<uint>(flagsStr);
        pMeshNode->GetBitField().Set(flags);
      }

      Vec3 v;
      if (!v.FromString(childSection("Pos")))
        return false;
      pMeshNode->SetPos(v.x, v.y, v.z, false);

      if (!v.FromString(childSection("Rot")))
        return false;
      pMeshNode->SetRot(v.x, v.y, v.z, false);

      if (!v.FromString(childSection("Scl")))
        return false;
      pMeshNode->SetScale(v.x, v.y, v.z, false);
    }
  }
  return true;
}


// --------------------------------------------------------------------------
// Calculate the bounding sphere for the entire scene
// --------------------------------------------------------------------------
void EditorDocument::PreCacheSceneBounds()
{
  m_BoundingSphere.Reset();

  TreeView *pTreeView = Editor.GetLeftPanel()->GetScenePanel()->GetTreeView();
  pTreeView->AddressAllNodes(MakeCallback<void, EditorDocument, TreeNode *>(&EditorDocument::CalculateBoundingSphere, this));
}


// --------------------------------------------------------------------------
// Calculate the bounding sphere for the given node and all children
// --------------------------------------------------------------------------
void EditorDocument::CalculateBoundingSphere(TreeNode *pNode)
{
  NULL_ASSERT(pNode);

  if (pNode && pNode->GetType() == "StaticMeshNode")
  {
    StaticMeshNode *pStaticMeshNode = (StaticMeshNode *) pNode;

    if (pStaticMeshNode->GetBitField().Test(TREE_NODE_RENDERABLE))
    {
      Sphere sphere = pStaticMeshNode->GetMesh()->GetBSphere();
      sphere.TransformAndScale(pStaticMeshNode->GetMatrix());

      if (m_BoundingSphere.radius == 0.0f)
      {
        m_BoundingSphere = sphere;
      }
      else
      {
        m_BoundingSphere.Maximize(sphere);
      }
    }
  }
}



// --------------------------------------------------------------------------
// Initialise the environment defaults
// --------------------------------------------------------------------------
void EditorDocument::InitEnvironment()
{
  // Set the environment settings
  m_Environment.GlobalAmbient    = Color(0.2f, 0.2f, 0.2f);
  m_Environment.SpecularEnabled  = 0;
  m_Environment.LightDiffuse     = Color::White;
  m_Environment.LightAmbient     = Color::White;
  m_Environment.LightSpecular    = Color::White;
  m_Environment.LightDirection   = Vec3N(0.0f, -0.9f, -0.2f);
  m_Environment.FogEnabled       = 0;
  m_Environment.FogMode          = D3DFOG_NONE;
  m_Environment.FogColor         = Color::White;
  m_Environment.FogStart         = 1.0f;
  m_Environment.FogEnd           = 1000.0f;
  m_Environment.FogDensity       = 1.0f;
  m_Environment.NearPlane        = 1.0f;
  m_Environment.FarPlane         = 10000.0f;
  m_Environment.FieldOfView      = 45.0f;

  ApplyEnvironment();
}


// --------------------------------------------------------------------------
// Apply the environment settings to the device
// --------------------------------------------------------------------------
void EditorDocument::ApplyEnvironment()
{
  // Set teh global ambient and specular
  RenderState.Set(D3DRS_AMBIENT, (DWORD) m_Environment.GlobalAmbient);
  RenderState.Set(D3DRS_SPECULARENABLE, m_Environment.SpecularEnabled);

  // Initalise the light
  m_DirectionalLight = DirectionalLight(
    m_Environment.LightDirection, 
    m_Environment.LightAmbient, 
    m_Environment.LightDiffuse, 
    m_Environment.LightSpecular);

  // Set the fog
  RenderState.Set(D3DRS_FOGENABLE, m_Environment.FogEnabled);
  RenderState.Set(D3DRS_FOGTABLEMODE, m_Environment.FogMode);
  RenderState.Set(D3DRS_FOGCOLOR, m_Environment.FogColor);
  RenderState.Set(D3DRS_FOGSTART, m_Environment.FogStart);
  RenderState.Set(D3DRS_FOGEND, m_Environment.FogEnd);
  RenderState.Set(D3DRS_FOGDENSITY, m_Environment.FogDensity);

  // Set the camera settings
  Editor.GetCameraManager()->SetNearFarFOV(m_Environment.NearPlane, m_Environment.FarPlane, m_Environment.FieldOfView);
}


// --------------------------------------------------------------------------
// Save the environment settings
// --------------------------------------------------------------------------
bool EditorDocument::LoadEnvironmentFromConfig(const ConfigSection &cfg)
{
  // Global ambient
  if (!m_Environment.GlobalAmbient.FromString(cfg("GlobalAmbient")))
    return false;

  // Specular
  m_Environment.SpecularEnabled = cfg("SpecularEnabled");

  // Light
  if (!m_Environment.LightDiffuse.FromString(cfg("LightDiffuse")))
    return false;
  if (!m_Environment.LightAmbient.FromString(cfg("LightAmbeint")))
    return false;
  if (!m_Environment.LightSpecular.FromString(cfg("LightSpecular")))
    return false;
  if (!m_Environment.LightDirection.FromString(cfg("LightDirection")))
    return false;

  // Fog
  m_Environment.FogEnabled = cfg("FogEnabled");
  m_Environment.FogMode = cfg("FogMode");
  if (!m_Environment.FogColor.FromString(cfg("FogColor")))
    return false;
  m_Environment.FogStart = cfg("FogStart");
  m_Environment.FogEnd = cfg("FogEnd");
  m_Environment.FogDensity = cfg("FogDensity");

  // Camera
  m_Environment.NearPlane = cfg("NearPlane");
  m_Environment.FarPlane = cfg("FarPlane");
  m_Environment.FieldOfView = cfg("FieldOfView");
  
  return true;
}


// --------------------------------------------------------------------------
// Load the environment settings
// --------------------------------------------------------------------------
bool EditorDocument::SaveEnvironmentToConfig(ConfigSection &cfg)
{
  cfg.Set("GlobalAmbient",    m_Environment.GlobalAmbient.ToString());
  cfg.Set("SpecularEnabled",  m_Environment.SpecularEnabled);
  cfg.Set("LightDiffuse",     m_Environment.LightDiffuse.ToString());
  cfg.Set("LightAmbeint",     m_Environment.LightAmbient.ToString());
  cfg.Set("LightSpecular",    m_Environment.LightSpecular.ToString());
  cfg.Set("LightDirection",   m_Environment.LightDirection.ToString());
  cfg.Set("FogEnabled",       m_Environment.FogEnabled);
  cfg.Set("FogMode",          m_Environment.FogMode);
  cfg.Set("FogColor",         m_Environment.FogColor.ToString());
  cfg.Set("FogStart",         m_Environment.FogStart);
  cfg.Set("FogEnd",           m_Environment.FogEnd);
  cfg.Set("FogDensity",       m_Environment.FogDensity);
  cfg.Set("NearPlane",        m_Environment.NearPlane);
  cfg.Set("FarPlane",         m_Environment.FarPlane);
  cfg.Set("FieldOfView",      m_Environment.FieldOfView);

  return true;
}


// -- EOF

