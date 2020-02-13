
#ifndef __EDITOR_DOCUMENT_H_
#define __EDITOR_DOCUMENT_H_


#include "libEngine.h"
#include "libEditor.h"
#include "OverrideRenderList.h"
#include "SelectedMeshMaterial.h"


class SceneGroupNode;
class StaticMeshNode;


class EditorDocument
{
public:
  // Constructor and destructor
  EditorDocument();
  ~EditorDocument();

  // Initialise the document
  bool Init();

  // File operations
  bool New();
  bool Open();
  bool Save();
  bool SaveAs();
  bool Close();

  // Rendering loop
  void App();
  void Cull();
  void Draw();
  void SetRenderState();

  // Get the object under the mouse
  TreeNode *Pick();
  bool Pick(String &path);

  // Get the document state
  void SetDirty(bool dirty = true);
  bool IsDirty() const { return m_Dirty; }
  bool Exists() const  { return m_FileExists; }

  // Get the cached bounding sphere from the scene
  void PreCacheSceneBounds();
  const Sphere &GetCachedSceneBounds() const { return m_BoundingSphere; }

  // Teh availabel view modes
  enum ViewMode
  {
    VIEW_NORMAL,              // Textures and Lighting
    VIEW_NORMAL_WIREOVER,     // Normal with wireframe over
    VIEW_NOTEX,               // Lit without textures
    VIEW_UNLIT,               // Textured without lighting
    VIEW_WIREFRAME            // Wireframe
  };

  // Manage the view mode
  ViewMode GetViewMode() const    { return m_ViewMode; }
  void SetViewMode(ViewMode mode) { m_ViewMode = mode; }

  // Settings for the environment
  struct Environment
  {
    Color       GlobalAmbient;    // Global ambient color
    DWORD       SpecularEnabled;  // Is specular enabled

    Color       LightDiffuse;     // Light difuse color
    Color       LightAmbient;     // Light ambient color
    Color       LightSpecular;    // Light specular color
    Vec3        LightDirection;   // Light direction

    DWORD       FogEnabled;       // Enable fog
    DWORD       FogMode;          // Fog mode (D3DFOGMODE)
    Color       FogColor;         // Fog color
    float       FogStart;         // Fog range start
    float       FogEnd;           // Fog range end
    float       FogDensity;       // Fog density

    float       NearPlane;        // Near plane distance
    float       FarPlane;         // Far plane distance
    float       FieldOfView;      // FOV in degrees
  };

  // Access the environment settings
  Environment &GetEnvironment() { return m_Environment; }

protected:
  // Data from a single raytest hit
  struct PickInfo
  {
    Mesh       *pMesh;
    Matrix      Transform;
    TreeNodeId  Id;    
  };

  // Calculate the scene bounding sphere
  void CalculateBoundingSphere(TreeNode *pNode);

  // Recursive cull function
  void CullNode(TreeNode *pNode);
  void AddToRenderList(StaticMeshNode *pNode);

  // Picking functions
  bool TestPick(TreeNodeId &id);
  void TestPickNode(TreeNode *pNode, const Ray &ray, Array<PickInfo> &pickInfo);

  // Save and load functions
  bool SaveToConfig(ConfigFile &cfg);
  bool LoadFromConfig(ConfigFile &cfg);
  bool SaveNodeToConfig(TreeNode *pNode, ConfigSection &cfg);
  bool LoadNodeFromConfig(SceneGroupNode *pNode, const ConfigSection &cfg);

  // Show file dialogs
  bool GetOpenFileHandle(FileHandle &handle);
  bool GetSaveFileHandle(FileHandle &handle);

  // Result from the generic save operation
  enum SaveResult
  {
    RES_OK,
    RES_FAIL,
    RES_CANCEL
  };

  // Attempt to save
  SaveResult DoSave(bool showPrompt);

  // Initialise the environment defaults
  void InitEnvironment();

  // Apply the environment settings
  void ApplyEnvironment();

  // Save and load the environment settings
  bool LoadEnvironmentFromConfig(const ConfigSection &cfg);
  bool SaveEnvironmentToConfig(ConfigSection &cfg);

protected:
  LightArray              m_Lights;
  RenderList              m_RenderList;
  OverrideRenderList      m_FrozenRenderList;
  OverrideRenderList      m_SelectedRenderList;
  OverrideRenderList      m_WireframeRenderList;
  OverrideRenderList      m_NoTexRenderList;

  SelectedMeshMaterial   *m_pSelectedMeshMaterial;
  SelectedMeshMaterial   *m_pFrozenMeshMaterial;
  SelectedMeshMaterial   *m_pWireframeMeshMaterial;
  SelectedMeshMaterial   *m_pNoTexMaterial;

  bool                    m_Dirty;
  bool                    m_FileExists;
  FileHandle              m_FileHandle;

  Sphere                  m_BoundingSphere;
  ViewMode                m_ViewMode;

  Environment             m_Environment;
  DirectionalLight        m_DirectionalLight;

};


#endif // __EDITOR_DOCUMENT_H_

// -- EOF

