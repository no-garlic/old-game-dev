
#ifndef __STATIC_MESH_H_
#define __STATIC_MESH_H_


#include "libEngine.h"
#include "GameObject.h"


class StaticMesh : public GameObject, public RefCounted
{
public:
  DECLARE_TYPE_INFO(GameObject);

  // Constructor and destructor
  StaticMesh();
  virtual ~StaticMesh();

  // Set the mesh
  void SetMesh(IndexedMesh *pMesh);
  IndexedMesh *GetMesh();

private:
  IndexedMesh  *m_pMesh;        // Indexed mesh

};


#endif // __STATIC_MESH_H_

// -- EOF

