
#ifndef __STATIC_MESH_NODE_H_
#define __STATIC_MESH_NODE_H_


#include "libEngine.h"
#include "libEditor.h"


class StaticMeshNode : public TreeNode
{
public:
  explicit StaticMeshNode(wxTreeItemId id);
  virtual ~StaticMeshNode();

  // Create the tree of content
  void Create(const String &meshName, const String &fileName);

  // Called when the node is selected and deselected
  virtual void OnEnter();
  virtual void OnLeave();

  // Get the matrix and mesh
  Mesh *GetMesh() { return m_pMesh;  }
  const Matrix &GetMatrix() { return m_Matrix; }

  // Set the matrix position and rotation
  void SetRot(float h, float p, float r, bool updatePanel = true);
  void SetPos(float x, float y, float z, bool updatePanel = true);
  void SetScale(float x, float y, float z, bool updatePanel = true);

  // Set the matrix position and rotation
  const Vec3 &GetPos()   const { return m_Pos; }
  const Vec3 &GetRot()   const { return m_Rot; }
  const Vec3 &GetScale() const { return m_Scale; }

  // Called when the node is right clicked
  virtual void OnRightClick(const wxPoint &pos);

private:
  void UpdateMatrix();

  String       m_MeshName;
  String       m_FileName;
  Mesh        *m_pMesh;
  Matrix       m_Matrix;
  Vec3         m_Pos;
  Vec3         m_Rot;
  Vec3         m_Scale;

};


#endif // __STATIC_MESH_NODE_H_

// -- EOF

