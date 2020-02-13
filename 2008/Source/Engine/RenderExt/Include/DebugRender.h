// ----------------------------------------------------------------------------
// File: DebugRender.h
// Desc: Provides some debugging functions to easily draw 3d primatives
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __RENDER_DEBUG_H_
#define __RENDER_DEBUG_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libRenderCore.h"
#include "IndexedMesh.h"
#include "Material.h"


// ----------------------------------------------------------------------------
// Global accessor
// ----------------------------------------------------------------------------
#define DebugRender DebugRenderManager::GetInstance()


// ----------------------------------------------------------------------------
// Macros for debug only usage
// ----------------------------------------------------------------------------
#define DEBUG_SPHERE(sphere, color, frames)                         DebugRender.AddSphere(sphere, color, frames);
#define DEBUG_BOX(box, color, frames)                               DebugRender.AddBox(box, color, frames);
#define DEBUG_LINE(line, color, frames)                             DebugRender.AddLine(line, color, frames);
#define DEBUG_CYLINDER(matrix, cylinder, color, frames)             DebugRender.AddCylinder(matrix, cylinder, color, frames);
#define DEBUG_PLANE(plane, color, frames)                           DebugRender.AddPlane(plane, color, frames);
#define DEBUG_MESH(matrix, vtx, numvtx, idx, numidx, color, frames) DebugRender.AddMesh(matrix, vtx, numvtx, idx, numidx, color, frames);

// ----------------------------------------------------------------------------
// Manager class for storing and rendering primatives
// ----------------------------------------------------------------------------
class DebugRenderManager
{
public:
  // --------------------------------------------------------------------------
  // Singleton accessors
  // --------------------------------------------------------------------------
  static DebugRenderManager &GetInstance();
  static void DestroyInstance();

  // --------------------------------------------------------------------------
  // Initialise the debug render system
  // --------------------------------------------------------------------------
  bool Init();

  // --------------------------------------------------------------------------
  // Render all primatives
  // --------------------------------------------------------------------------
  void Render();

  // --------------------------------------------------------------------------
  // Add to the debug render list
  // --------------------------------------------------------------------------
  void AddSphere(const Sphere &sphere, const Color &color, int frames = 1);
  void AddBox(const Box &box, const Color &color, int frames = 1);
  void AddLine(const LineSegment &lineSegment, const Color &color, int frames = 1);
  void AddCylinder(const Matrix &m, const Cylinder &cylinder, const Color &color, int frames = 1);
  void AddPlane(const Plane &plane, const Color &color, int frames = 1);
  void AddMesh(const Matrix &m, VT_PN *pVertexData, uint numVertex, ushort *pIndexData, uint numIndex, const Color &color, uint frames = 1);

private:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  DebugRenderManager();
  ~DebugRenderManager();

  // --------------------------------------------------------------------------
  // Render the specific mesh types
  // --------------------------------------------------------------------------
  void RenderSpheres();
  void RenderBoxes();
  void RenderLines();
  void RenderCylinders();
  void RenderPlanes();
  void RenderMeshes();

  // --------------------------------------------------------------------------
  // Holds the debug mesh data
  // --------------------------------------------------------------------------
  struct DebugMesh
  {
    Matrix   m_Matrix;
    VT_PN   *m_pVertex;
    ushort  *m_pIndex;
    uint     m_NumIndex;
    uint     m_NumVertex;
  };

  // --------------------------------------------------------------------------
  // Holds the debug cylinder data
  // --------------------------------------------------------------------------
  struct DebugCylinder
  {
    Matrix    m_Matrix;
    Cylinder  m_Cylinder;
  };

  // --------------------------------------------------------------------------
  // Holds a list of the items to render
  // --------------------------------------------------------------------------
  template <class DebugItemType>
  struct DebugItemInfo
  {
    DebugItemType item;     // The item to draw
    Color         color;    // The item color
    int           frames;   // number of frames to draw for
  };

private:
  // --------------------------------------------------------------------------
  // Static members
  // --------------------------------------------------------------------------
  static DebugRenderManager          *s_pInstance;      // Singleton instance
  bool                                m_Initialised;    // Is the class initialised
  uint                                m_Count;          // Number of items to render (stored for speed)
  const Material                     *m_pMaterial;      // Material

  ID3DXMesh                          *m_pSphere;        // Sphere mesh
  ID3DXMesh                          *m_pBox;           // Box mesh
  ID3DXMesh                          *m_pCylinder;      // Cylinder mesh
  IndexedMesh                        *m_pQuad;          // Line drawing mesh

  List<DebugItemInfo<Sphere> >        m_SphereInfo;     // All spheres to draw
  List<DebugItemInfo<Box> >           m_BoxInfo;        // All boxes to draw
  List<DebugItemInfo<LineSegment> >   m_LineInfo;       // All lines to draw
  List<DebugItemInfo<DebugCylinder> > m_CylinderInfo;   // All cylinders to draw
  List<DebugItemInfo<Plane> >         m_PlaneInfo;      // All planes to draw
  List<DebugItemInfo<DebugMesh> >     m_MeshInfo;       // All user meshes to draw


};


#endif // __RENDER_DEBUG_H_

// -- EOF

