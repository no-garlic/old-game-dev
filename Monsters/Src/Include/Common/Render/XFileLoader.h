// ----------------------------------------------------------------------------
// File: XFileLoader.h
// Desc: Loads X files and creates an array of indexed meshes
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __X_FILE_LOADER_H_
#define __X_FILE_LOADER_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"
#include "Engine/EngineInc.h"
#include "Maths/MathInc.h"
#include "Render/Mesh.h"
#include "Render/VertexType.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class XFileLoader;


//-----------------------------------------------------------------------------
// Derived frame, stores an additional 'combined' matrix
//-----------------------------------------------------------------------------
struct D3DXFRAME_MATRIX : public D3DXFRAME  
{
  D3DXMATRIX mtxCombined;
}; // struct D3DXFRAME_MATRIX


//-----------------------------------------------------------------------------
// Derived Mesh Container, stores our wrapper mesh.
//-----------------------------------------------------------------------------
struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
  Mesh *pMesh;
}; // struct D3DXMESHCONTAINER_DERIVED


// ----------------------------------------------------------------------------
// Name: CAllocateHierarchy (class)
// Desc: A custom, derived, version of ID3DXAllocateHeirarchy. This class 
//       contains custom methods that will be called by D3DX during the loading 
//       of any mesh heirarchy.
// ----------------------------------------------------------------------------
class CAllocateHierarchy: public ID3DXAllocateHierarchy
{
public:
  //-------------------------------------------------------------------------
  // Constructors & Destructors for This Class.
  //-------------------------------------------------------------------------
  CAllocateHierarchy(XFileLoader *pActor) : m_pActor(pActor) {}

  //-------------------------------------------------------------------------
  // Public Functions for This Class
  //-------------------------------------------------------------------------
  STDMETHOD(CreateFrame)          (THIS_ LPCTSTR Name, LPD3DXFRAME *ppNewFrame);    
  STDMETHOD(CreateMeshContainer)  (THIS_ LPCTSTR Name, CONST D3DXMESHDATA * pMeshData,
    CONST D3DXMATERIAL * pMaterials, CONST D3DXEFFECTINSTANCE * pEffectInstances,
    DWORD NumMaterials, CONST DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo, 
    LPD3DXMESHCONTAINER *ppNewMeshContainer);
  STDMETHOD(DestroyFrame)         (THIS_ LPD3DXFRAME pFrameToFree);
  STDMETHOD(DestroyMeshContainer) (THIS_ LPD3DXMESHCONTAINER pMeshContainerBase);

  //-------------------------------------------------------------------------
  // Public Variables for This Class
  //-------------------------------------------------------------------------
  XFileLoader *m_pActor;

}; // CAllocateHierarchy


// ----------------------------------------------------------------------------
// Name: XFileLoader (class)
// Desc: Loads an X file
// ----------------------------------------------------------------------------
class XFileLoader
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  XFileLoader();
  ~XFileLoader();

  // --------------------------------------------------------------------------
  // Load the file
  // --------------------------------------------------------------------------
  bool Load(const String &filename);

  struct Frame
  {
    Matrix   TransformMatrix;
    Mesh    *pMesh;
  };

  Array<Frame> GetFrames();

  LPD3DXFRAME GetRootFrame() { return m_pFrameRoot; }

private:
  void XFileLoader::FindFrames(LPD3DXFRAME pFrame, Array<Frame> &frames);

  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  LPD3DXFRAME     m_pFrameRoot;     // The root frame

}; // class XFileLoader


#endif // __X_FILE_LOADER_H_

// -- EOF

