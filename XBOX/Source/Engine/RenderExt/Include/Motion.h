
#ifndef __MOTION_H_
#define __MOTION_H_


#include "libRenderCore.h"
#include "libCal3D.h"
#include "AnimationMixer.h"
#include "IndexedMesh.h"
#include "Material_PNT_ANIM.h"


class Animation;


class Motion : private Unique
{
public:
  Motion();
  virtual ~Motion();

  bool Load(FileHandle handle);

  void Update(float deltaTime);

  AnimationMixer *GetMixer();
  const AnimationMixer *GetMixer() const;

  const Mesh *GetMesh() const { return m_pIndexedMesh; }

  void MeshSubsetPreRenderCallback(MeshSubset *pSubset);

private:
  bool CreateMaterials();
  bool CreateMesh();

private:
  const Material   *m_pMaterial;            // The render material
  IndexedMesh      *m_pIndexedMesh;         // The indexed mesh to hold the render data
  CalHardwareModel *m_pCalHardwareModel;    // The hardware model
  CalCoreModel     *m_pCalCoreModel;        // The core model
  CalModel         *m_pCalModel;            // The instance model
  AnimationMixer   *m_pMixer;

};


#endif // __MOTION_H_


// -- EOF


