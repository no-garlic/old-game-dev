
#ifndef __PHYSICS_SCENE_H_
#define __PHYSICS_SCENE_H_


#include "libEngine.h"


class PhysicsScene : private Unique
{
public:
  PhysicsScene();
  ~PhysicsScene();

  bool Init();

  void SetRenderState();
  void Resize();

  void Update(float deltaTime);
  void Cull();
  void Render();

private:
  bool CreateScene();
  bool CreateObject(const String &name, const String &mesh, const Vec3 &startPos);
  void PreUpdateScene();
  void PostUpdateScene();

  void UpdateCamera();

private:
  struct PhysicalObject
  {
    IndexedMesh   *m_pMesh;           // The mesh
    RigidBody     *m_pBody;           // The body
    Matrix         m_Matrix;          // The matrix
    MeshNode      *m_pMeshNode;       // The mesh node
    TransformNode *m_pTransformNode;  // The transform node
  };

  Map<String, PhysicalObject> m_Objects;
  SceneNode                  *m_pSceneNode;
  RenderList                  m_RenderList;
  LightArray                  m_Lights;
  float                       m_CameraDist;
  float                       m_CameraPitch;

};


#endif // __PHYSICS_SCENE_H_

// -- EOF


