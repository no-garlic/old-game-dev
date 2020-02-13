// ----------------------------------------------------------------------------
// File: IndexedMesh.h
// Desc: Manages an object that can be rendered and edited.
// Auth: Michael Petrou
// (C) Copyright: 2005
// ----------------------------------------------------------------------------
#ifndef _INDEXED_MESH_H_
#define _INDEXED_MESH_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "libStandard.h"
#include "libRenderCore.h"
#include "libMaths.h"
#include "Mesh.h"
#include "VertexType.h"


// ----------------------------------------------------------------------------
// Name: IndexedMesh  (class)
// Desc: A renderable scene object
// ----------------------------------------------------------------------------
class IndexedMesh : public Mesh
{
public:
  // --------------------------------------------------------------------------
  // Name: IndexedMesh
  // Desc: Constructor
  // Parm: const String &name - the name of the mesh
  // --------------------------------------------------------------------------
  IndexedMesh(const String &name, const VertexType *pvertex_type);
  IndexedMesh(const String &name = "");
  
  // --------------------------------------------------------------------------
  // Name: ~IndexedMesh
  // Desc: Destructor
  // --------------------------------------------------------------------------
  virtual ~IndexedMesh();

  // ------------------------------------------------------------------------
  // Name: Face (class)
  // Desc: Defines a face for our indexed geometry
  // ------------------------------------------------------------------------
  struct Face
  {
    ushort a;
    ushort b;
    ushort c;

    // --------------------------------------------------------------------
    // Set the face indecies
    // --------------------------------------------------------------------
    void Assign(ushort v0, ushort v1, ushort v2)
    {
      a = v0;
      b = v1;
      c = v2;
    } // Assign
  }; // struct Face

  // --------------------------------------------------------------------------
  // Name: GetVertexType
  // Desc: Get the vertex type
  // Retn: const VertexType * - the vertex type
  // --------------------------------------------------------------------------
  inline const VertexType *GetVertexType() const;

  // --------------------------------------------------------------------------
  // Name: SetVertexType
  // Desc: Set the vertex type
  // Parm: const VertexType *pVertexType - the vertex type
  // --------------------------------------------------------------------------
  inline void SetVertexType(const VertexType *pVertexType);

  // --------------------------------------------------------------------------
  // Name: GetVertexData
  // Desc: Get the vertex data
  // Retn: void * - the vertex data pointer
  // --------------------------------------------------------------------------
  inline void *GetVertexData();

  // --------------------------------------------------------------------------
  // Name: GetFaceData
  // Desc: Get the face data
  // Retn: IndexedMesh::Face * - the face data pointer
  // --------------------------------------------------------------------------
  inline IndexedMesh::Face *GetFaceData();
  inline const IndexedMesh::Face *GetFaceData() const;

  // --------------------------------------------------------------------------
  // Name: SetVertexBufferDynamic
  // Desc: Set the vertex buffer to be dynamic
  // Parm: bool dynamic - true if dynamic
  // --------------------------------------------------------------------------
  inline void SetVertexBufferDynamic(bool dynamic);
  
  // --------------------------------------------------------------------------
  // Name: SetIndexBufferDynamic
  // Desc: Set the index buffer to be dynamic
  // Parm: bool dynamic - true if dynamic
  // --------------------------------------------------------------------------
  inline void SetIndexBufferDynamic(bool dynamic);
  
  // --------------------------------------------------------------------------
  // Name: SetNumVerts
  // Desc: Set the number of vertices used
  // Parm: uint num_verts - the number of vertices
  // --------------------------------------------------------------------------
  inline void SetNumVerts(uint num_verts);
  
  // --------------------------------------------------------------------------
  // Name: SetNumFaces
  // Desc: Set the number of faces used
  // Parm: uint num_faces - the number of faces
  // --------------------------------------------------------------------------
  inline void SetNumFaces(uint num_faces);
  
  // --------------------------------------------------------------------------
  // Name: GetNumVerts
  // Desc: Get the number of vertices used
  // Retn: uint - the number of vertices
  // --------------------------------------------------------------------------
  inline uint GetNumVerts();
  
  // --------------------------------------------------------------------------
  // Name: GetNumFaces
  // Desc: Get the number of faces used
  // Retn: uint - the number of faces
  // --------------------------------------------------------------------------
  inline uint GetNumFaces();
  
  // --------------------------------------------------------------------------
  // Name: SetMaxVerts
  // Desc: Set the maximum nomber of vertices allocated
  // Parm: uint max_verts - the maximum number of vertices
  // --------------------------------------------------------------------------
  void SetMaxVerts(uint max_verts);
  
  // --------------------------------------------------------------------------
  // Name: SetMaxFaces
  // Desc: Set the maximum number of faces allocated
  // Parm: uint max_faces - the maximum number of faces
  // --------------------------------------------------------------------------
  void SetMaxFaces(uint max_faces);
  
  // --------------------------------------------------------------------------
  // Name: GetMaxVerts
  // Desc: Get the maximum number of vertices allocated
  // Retn: uint - the number
  // --------------------------------------------------------------------------
  inline uint GetMaxVerts();
  
  // --------------------------------------------------------------------------
  // Name: GetMaxFaces
  // Desc: Get the maximum number of faces allocated
  // Retn: uint - the number
  // --------------------------------------------------------------------------
  inline uint GetMaxFaces();

  // --------------------------------------------------------------------------
  // Name: GetVec3Ptr
  // Desc: Get an interleaved Vec3 pointer
  // Parm: VertexItem item - the vertex item to get a pointer for
  // Retn: Vec3GeomPtr     - the pointer
  // --------------------------------------------------------------------------
  inline Vec3GeomPtr GetVec3Ptr(VertexItem item);
  inline const Vec3GeomPtr GetVec3Ptr(VertexItem item) const;
  
  // --------------------------------------------------------------------------
  // Name: GetVec2Ptr
  // Desc: Get an interleaved Vec2 pointer
  // Parm: VertexItem item - the vertex item to get a pointer for
  // Retn: Vec2GeomPtr     - the pointer
  // --------------------------------------------------------------------------
  inline Vec2GeomPtr GetVec2Ptr(VertexItem item);
  inline const Vec2GeomPtr GetVec2Ptr(VertexItem item) const;

  // --------------------------------------------------------------------------
  // Name: GetULongPtr
  // Desc: Get an interleaved ulong pointer
  // Parm: VertexItem item - the vertex item to get a pointer for
  // Retn: ULongGeomPtr    - the pointer
  // --------------------------------------------------------------------------
  inline ULongGeomPtr GetULongPtr(VertexItem item);
  inline const ULongGeomPtr GetULongPtr(VertexItem item) const;

  // --------------------------------------------------------------------------
  // Name: SetVertexDataDirty
  // Desc: Flag the vertex data as dirty
  // Parm: bool dirty - the dirty state
  // --------------------------------------------------------------------------
  inline void SetVertexDataDirty(bool dirty = true);
  
  // --------------------------------------------------------------------------
  // Name: SetIndexDataDirty
  // Desc: Flag the index data as dirty
  // Parm: bool dirty - the dirty state
  // --------------------------------------------------------------------------
  inline void SetIndexDataDirty(bool dirty = true);

  // --------------------------------------------------------------------------
  // Name: SetDirty
  // Desc: Flag the vertex and index data as dirty
  // Parm: bool vertex_data - the vertex data dirty state
  // Parm: bool index_data  - the index data dirty state
  // --------------------------------------------------------------------------
  inline void SetDirty(bool vertex_data = true, bool index_data = true);

  // --------------------------------------------------------------------------
  // Name: Render
  // Desc: Render the mesh for the given material pass
  // Parm: uint pass    - the pass
  // --------------------------------------------------------------------------
  virtual void Render(uint pass = 0) const;

  // --------------------------------------------------------------------------
  // Name: RenderSubset
  // Desc: Render the mesh for the given subset and pass
  // Parm: uint pass    - the pass
  // --------------------------------------------------------------------------
  virtual void RenderSubset(uint subset, uint pass = 0) const;

  // --------------------------------------------------------------------------
  // Name: GetBSphere
  // Desc: Gets the bounding sphere of this object
  // Retn: const Sphere & - the sphere
  // --------------------------------------------------------------------------
  virtual const Sphere &GetBSphere() const;

  // --------------------------------------------------------------------------
  // Name: GetBBox
  // Desc: Gets the bounding box of this mesh
  // Retn: const Box & - the axis aligned box
  // --------------------------------------------------------------------------
  virtual const Box &GetBBox() const;

  // --------------------------------------------------------------------------
  // Name: Intersects
  // Desc: Tests for a collision between the provided ray (which must be already
  //       transformed into model space) and this object's geometry. Note - this
  //       is a faster test than the Intersects function below as it returns 
  //       true as soon as a hit is found, whereas the following Intersects 
  //       function will test every face to find the closest intersection point.
  // Parm: const Ray &ray - the ray in object space
  // Retn: bool           - true if the ray intersects with the object's geometry
  // --------------------------------------------------------------------------
  virtual bool Intersects(const Ray &ray) const;

  // --------------------------------------------------------------------------
  // Name: Intersects
  // Desc: Tests for a collision between the provided ray (which must be already
  //       transformed into model space) and this object's geometry. Note - this
  //       function will test every face to find the closest intersection point.
  // Parm: const Ray &ray - the ray in object space
  // Parm: Vec3 &hit      - [out] the hit position
  // Parm: float &dist    - [out] the distance from the ray point to the intersection point.
  // Retn: bool           - true if the ray intersects with the object's 
  //                        geometry
  // --------------------------------------------------------------------------
  virtual bool Intersects(const Ray &ray, Vec3 &intersectPt, float &distance) const;

  // --------------------------------------------------------------------------
  // Name: Load
  // Desc: Load the mesh from the given file
  // Parm: FILE *pFile - the file to load from
  // Retn: bool      - true if loaded
  // --------------------------------------------------------------------------
  virtual bool Load(FileHandle handle) { return Mesh::Load(handle); }

#if PC
  // --------------------------------------------------------------------------
  // Name: Save
  // Desc: Save the mesh to the given file
  // Parm: FILE *pFile - the file to save to
  // Retn: bool      - true if saved
  // --------------------------------------------------------------------------
  virtual bool Save(FileHandle handle) { return Mesh::Save(handle); }
#endif

#if PC
  // --------------------------------------------------------------------------
  // Name: ImportFromX
  // Desc: Import the mesh from the X file
  // Parm: const String &filename - the X file to import
  // Retn: bool                 - true if imported
  // --------------------------------------------------------------------------
  bool ImportFromX(const String &filename);
#endif

  // --------------------------------------------------------------------------
  // Name: SertVertexTypeByName
  // Desc: Sets the vertex type of this mesh to the vertex type registered for
  //       the supplied name.
  // Parm: name  - the name of the vertex type
  // Retn: bool  - true if the vertex type was found for the supplied name
  // --------------------------------------------------------------------------
  bool SetVertexTypeByName(const String &name);

#if PC
  // --------------------------------------------------------------------------
  // Name: SetVertexTypeByDeclaration
  // Desc: Sets the vertex type of this mesh to the closest match for the 
  //       supplied vertex declaration.
  // Parm: pDeclaration - the vertex type declaration.
  // Retn: bool - true if a vertex type was found that supports the declaration.
  // --------------------------------------------------------------------------
  bool SetVertexTypeByDeclaration(D3DVERTEXELEMENT9 *pDeclaration);

  // --------------------------------------------------------------------------
  // Name: GetFixedFunctionMaterialByDeclaration
  // Desc: Gets the material for that is the closest match for the supplied 
  //       vertex declaration.
  // Parm: pDeclaration - the vertex type declaration.
  // Retn: The closest matched basic material, or the default material if no
  //       match could be made.
  // --------------------------------------------------------------------------
  const Material *GetFixedFunctionMaterialByDeclaration(D3DVERTEXELEMENT9 *pDeclaration);
#endif

  // --------------------------------------------------------------------------
  // The file header
  // --------------------------------------------------------------------------
  struct FileHeader
  {
    FileString<256>       Name;                           // The mesh name
    uint                  MeshSubsetCount;                // The number of subsets
    FileString<256>       VertexTypeName;                 // The vertex type name
    uint                  NumVerts;                       // The number of vertices
    uint                  NumFaces;                       // The number of faces
    bool                  DynamicVertexBuffer;            // Is the vertex buffer dynamic?
    bool                  DynamicIndexBuffer;             // Is the index buffer dynamic?
    uint                  VertexSize;                     // The size of the vertex
    bool                  CastShadow;                     // Does the mesh cast shadow
    uint                  Reserved0;                      // Reserved for later use
    uint                  Reserved1;                      // Reserved for later use
    uint                  Reserved2;                      // Reserved for later use
    uint                  Reserved3;                      // Reserved for later use
    uint                  Reserved4;                      // Reserved for later use
  }; // FileHeader

protected:
  // --------------------------------------------------------------------------
  // Manage device memory
  // --------------------------------------------------------------------------
  virtual bool AllocateDeviceMemory();
  virtual bool ReleaseDeviceMemory();

  // --------------------------------------------------------------------------
  // Name: Load
  // Desc: Load the mesh from the given file
  // Parm: FILE *pFile - the file to load from
  // Retn: bool      - true if loaded
  // --------------------------------------------------------------------------
  virtual bool Load(FILE *pFile);

#if PC
  // --------------------------------------------------------------------------
  // Name: Save
  // Desc: Save the mesh to the given file
  // Parm: FILE *pFile - the file to save to
  // Retn: bool      - true if saved
  // --------------------------------------------------------------------------
  virtual bool Save(FILE *pFile);
#endif

private:
  // --------------------------------------------------------------------------
  // Name: RecalculateBounds
  // Desc: Recalculate the bounding sphere for the mesh
  // --------------------------------------------------------------------------
  void RecalculateBounds();

  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  mutable VERTEXBUFFER            m_pvertex_buffer;         // The direct 3D vertex buffer
  mutable INDEXBUFFER             m_pindex_buffer;          // The direct 3D index buffer
  const VertexType               *m_pvertex_type;           // The vertex type
  void                           *m_pvertex_data;           // The vertex data (system memory)
  IndexedMesh::Face              *m_pindex_data;            // The index data (system memory)
  uint                            m_num_verts;              // The number of vertices
  uint                            m_num_faces;              // The number of faces
  uint                            m_num_verts_alloc;        // The space allocated for vertices
  uint                            m_num_faces_alloc;        // The space allocated for faces
  bool                            m_dynamic_vertex_buffer;  // Is the vertex buffer dynamic?
  bool                            m_dynamic_index_buffer;   // Is the index buffer dynamic?
  mutable bool                    m_vertex_dirty;           // Is the D3D vertex data dirty
  mutable bool                    m_index_dirty;            // Is the D3D index data dirty
  mutable bool                    m_rebuild_vertex_array;   // Does the D3D vertex buffer need to be recreated
  mutable bool                    m_rebuild_index_array;    // Does the D3D index buffer need to be recreated

}; // class IndexedMesh


// ----------------------------------------------------------------------------
// Get the vertex type
// ----------------------------------------------------------------------------
inline const VertexType *IndexedMesh::GetVertexType() const
{ 
  return m_pvertex_type;
} // GetVertexType


// ----------------------------------------------------------------------------
// Set the vertex type
// ----------------------------------------------------------------------------
inline void IndexedMesh::SetVertexType(const VertexType *pVertexType)
{
  m_pvertex_type = pVertexType;
} // SetVertexType


// ----------------------------------------------------------------------------
// Get a pointer to the vertex data
// ----------------------------------------------------------------------------
inline void *IndexedMesh::GetVertexData()
{
  return m_pvertex_data;
} // GetVertexData


// ----------------------------------------------------------------------------
// Get a pointer to the index data
// ----------------------------------------------------------------------------
inline IndexedMesh::Face *IndexedMesh::GetFaceData()
{ 
  return m_pindex_data; 
} // GetFaceData


// ----------------------------------------------------------------------------
// Get a pointer to the index data
// ----------------------------------------------------------------------------
inline const IndexedMesh::Face *IndexedMesh::GetFaceData() const
{ 
  return m_pindex_data; 
} // GetFaceData


// ----------------------------------------------------------------------------
// Mark the vertex buffer dirty
// ----------------------------------------------------------------------------
inline void IndexedMesh::SetVertexDataDirty(bool dirty)
{ 
  m_vertex_dirty = dirty;
  if (dirty)
    m_bounds_dirty = true;
} // SetVertexDataDirty


// ----------------------------------------------------------------------------
// Mark the index buffer dirty
// ----------------------------------------------------------------------------
inline void IndexedMesh::SetIndexDataDirty(bool dirty)
{ 
  m_index_dirty = dirty;
} // SetIndexDataDirty


// ----------------------------------------------------------------------------
// Mark the vertex and / or index buffers dirty
// ----------------------------------------------------------------------------
inline void IndexedMesh::SetDirty(bool vertex_data, bool index_data) 
{ 
  m_vertex_dirty = vertex_data; 
  m_index_dirty  = index_data; 
  if (vertex_data)
    m_bounds_dirty = true;
} // SetDirty


// ----------------------------------------------------------------------------
// Set the vertex buffer as dynamic or static
// ----------------------------------------------------------------------------
inline void IndexedMesh::SetVertexBufferDynamic(bool dynamic)
{
  if (m_dynamic_vertex_buffer == dynamic)
    return;

  m_dynamic_vertex_buffer = dynamic;
  m_rebuild_vertex_array  = true;
} // SetVertexBufferDynamic


// ----------------------------------------------------------------------------
// Set the index buffer as dynamic or static
// ----------------------------------------------------------------------------
inline void IndexedMesh::SetIndexBufferDynamic(bool dynamic)
{
  if (m_dynamic_index_buffer == dynamic)
    return;

  m_dynamic_index_buffer = dynamic;
  m_rebuild_index_array  = true;
} // SetIndexBufferDynamic


// ---------------------------------------------------------------------
// Get teh maximum vertices allocated in the mesh
// ---------------------------------------------------------------------
inline uint IndexedMesh::GetMaxVerts()
{
  return m_num_verts_alloc;
} // GetMaxVerts


// ----------------------------------------------------------------------------
// Get the maximum faces allocated in the mesh
// ----------------------------------------------------------------------------
inline uint IndexedMesh::GetMaxFaces()
{
  return m_num_faces_alloc;
} // GetMaxFaces


// ----------------------------------------------------------------------------
// Get the number of vertices in the mesh
// ----------------------------------------------------------------------------
inline uint IndexedMesh::GetNumVerts()
{
  return m_num_verts;
} // GetNumVerts


// ----------------------------------------------------------------------------
// Get the number of faces in the mesh
// ----------------------------------------------------------------------------
inline uint IndexedMesh::GetNumFaces()
{
  return m_num_faces;
} // GetNumFaces


// ----------------------------------------------------------------------------
// Set the number of vertices for the mesh
// ----------------------------------------------------------------------------
inline void IndexedMesh::SetNumVerts(uint num_verts)
{
  if (num_verts > m_num_verts_alloc)
    SetMaxVerts(num_verts);

  m_num_verts = num_verts;
} // SetNumVerts


// ----------------------------------------------------------------------------
// Set the number of faces for the mesh
// ----------------------------------------------------------------------------
inline void IndexedMesh::SetNumFaces(uint num_faces)
{
  if (num_faces > m_num_faces_alloc)
    SetMaxFaces(num_faces);

  m_num_faces = num_faces;
} // SetNumFaces


// ------------------------------------------------------------------------
// Get a Vec3 geom pointer to the vertex data
// ------------------------------------------------------------------------
inline Vec3GeomPtr IndexedMesh::GetVec3Ptr(VertexItem item)
{
  ubyte offset = m_pvertex_type->GetItemOffset(item);
  if (offset == 0xff)
    return Vec3GeomPtr();

  return Vec3GeomPtr(m_pvertex_type->GetSize(), offset, m_pvertex_data);
} // GetVec3Ptr


// ------------------------------------------------------------------------
// Get a Vec3 geom pointer to the vertex data
// ------------------------------------------------------------------------
inline const Vec3GeomPtr IndexedMesh::GetVec3Ptr(VertexItem item) const
{
  ubyte offset = m_pvertex_type->GetItemOffset(item);
  if (offset == 0xff)
    return Vec3GeomPtr();

  return Vec3GeomPtr(m_pvertex_type->GetSize(), offset, m_pvertex_data);
} // GetVec3Ptr


// ------------------------------------------------------------------------
// Get a Vec2 geom pointer to the vertex data
// ------------------------------------------------------------------------
inline Vec2GeomPtr IndexedMesh::GetVec2Ptr(VertexItem item)
{
  ubyte offset = m_pvertex_type->GetItemOffset(item);
  if (offset == 0xff)
    return Vec2GeomPtr();

  return Vec2GeomPtr(m_pvertex_type->GetSize(), offset, m_pvertex_data);
} // GetVec2Ptr


// ------------------------------------------------------------------------
// Get a Vec2 geom pointer to the vertex data
// ------------------------------------------------------------------------
inline const Vec2GeomPtr IndexedMesh::GetVec2Ptr(VertexItem item)const
{
  ubyte offset = m_pvertex_type->GetItemOffset(item);
  if (offset == 0xff)
    return Vec2GeomPtr();

  return Vec2GeomPtr(m_pvertex_type->GetSize(), offset, m_pvertex_data);
} // GetVec2Ptr


// ------------------------------------------------------------------------
// Get a ULong geom pointer to the vertex data
// ------------------------------------------------------------------------
inline ULongGeomPtr IndexedMesh::GetULongPtr(VertexItem item)
{
  ubyte offset = m_pvertex_type->GetItemOffset(item);
  if (offset == 0xff)
    return ULongGeomPtr();

  return ULongGeomPtr(m_pvertex_type->GetSize(), offset, m_pvertex_data);
} // GetULongPtr


// ------------------------------------------------------------------------
// Get a ULong geom pointer to the vertex data
// ------------------------------------------------------------------------
inline const ULongGeomPtr IndexedMesh::GetULongPtr(VertexItem item) const
{
  ubyte offset = m_pvertex_type->GetItemOffset(item);
  if (offset == 0xff)
    return ULongGeomPtr();

  return ULongGeomPtr(m_pvertex_type->GetSize(), offset, m_pvertex_data);
} // GetULongPtr


#endif // _INDEXED_MESH_H_

// -- EOF

