// ----------------------------------------------------------------------------
// File: Mesh.h
// Desc: Manages an object that can be rendered.
// Auth: Michael Petrou
// (C) Copyright: 2005
// ----------------------------------------------------------------------------
#ifndef _BASE_MESH_H
#define _BASE_MESH_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "libStandard.h"
#include "libRenderCore.h"
#include "libMaths.h"
#include "Material.h"


// ----------------------------------------------------------------------------
// Enable the mesh logging
// ----------------------------------------------------------------------------
//#ifdef TOOLS
#define __MESH_LOGGING
//#endif


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Mesh;
class MeshInstance;
class VertexType;


// ----------------------------------------------------------------------------
// Typedefs
// ----------------------------------------------------------------------------
typedef Array<MeshInstance *> MeshInstanceArray;


// ----------------------------------------------------------------------------
// Name: MeshInstance  (class)
// Desc: Provides a instance or a handle to a mesh.
// ----------------------------------------------------------------------------
class MeshInstance : private Unique, public RefCounted
{
public:
  // --------------------------------------------------------------------------
  // Name: MeshInstance
  // Desc: Constructor
  // Parm: Mesh *pparent - the parent mesh for this instance
  // Parm: const String &name   - the name of the new object instance
  // --------------------------------------------------------------------------
  MeshInstance(Mesh *pparent, const String &name, const Matrix &matrix = MatrixIdentity);

  // --------------------------------------------------------------------------
  // Name: ~MeshInstance
  // Desc: Destructor
  // --------------------------------------------------------------------------
  ~MeshInstance();

  // --------------------------------------------------------------------------
  // Name: Clone
  // Desc: Clones this mesh instance and creates a new copy with the 
  //       given name
  // Parm: const String &name  - the name of the new instance
  // Retn: MeshInstance * - the new instance
  // --------------------------------------------------------------------------
  inline MeshInstance *Clone(const String &name);

  // --------------------------------------------------------------------------
  // Name: GetName
  // Desc: Get the name of the instance
  // Retn: const String & - the name
  // --------------------------------------------------------------------------
  inline const String &GetName() const;

  // --------------------------------------------------------------------------
  // Name: SetName
  // Desc: Set the name of the instance
  // Parm: const String &name - the name
  // --------------------------------------------------------------------------
  inline void SetName(const String &name);

  // --------------------------------------------------------------------------
  // Name: GetMesh
  // Desc: Get the mesh
  // Retn: Mesh * - the mesh
  // --------------------------------------------------------------------------
  inline Mesh *GetMesh();

  // --------------------------------------------------------------------------
  // Name: SetMatrix
  // Desc: Set teh matrix
  // Parm: const Matrix &matrix - the matrix
  // --------------------------------------------------------------------------
  inline void SetMatrix(const Matrix &matrix);
  
  // --------------------------------------------------------------------------
  // Name: GetMatrix
  // Desc: Get the matrix
  // Retn: Matrix & - the matrix
  // --------------------------------------------------------------------------
  inline Matrix &GetMatrix();
  inline const Matrix &GetMatrix() const;

  // --------------------------------------------------------------------------
  // Name: SetLastFrameCulled
  // Desc: Set the last frame number when this instance was culled
  // Parm: uqword frameNumber - the frame number
  // --------------------------------------------------------------------------
  inline void SetLastFrameCulled(uqword frameNumber);
  
  // --------------------------------------------------------------------------
  // Name: GetLastFrameCulled
  // Desc: Get the last frame number when this instance was culled
  // Retn: uqword - the frame number
  // --------------------------------------------------------------------------
  inline uqword GetLastFrameCulled() const;

private:
  // --------------------------------------------------------------------------
  // Make this class non-copyable
  // --------------------------------------------------------------------------
  MeshInstance &operator=(const MeshInstance &other);
  MeshInstance(const MeshInstance &other);

  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  String              m_name;           // The instance name
  Matrix              m_world_matrix;   // The world matrix
  mutable Mesh       *m_pobject;        // The mesh we are instancing
  uqword              m_last_frame;     // The last frame when this instance was culled

}; // class MeshInstance


// ----------------------------------------------------------------------------
// Name: MeshSubset (class)
// Desc: A subset of a mesh
// ----------------------------------------------------------------------------
class MeshSubset
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  explicit MeshSubset(uint index);
  ~MeshSubset();

  // --------------------------------------------------------------------------
  // Get the subset index within the mesh
  // --------------------------------------------------------------------------
  uint GetIndex() const { return m_Index; }

  // --------------------------------------------------------------------------
  // Name: GetMaterial
  // Desc: Gets the material for this mesh
  // Retn: Material * - the material
  // --------------------------------------------------------------------------
  inline const Material *GetMaterial() const;

  // --------------------------------------------------------------------------
  // Name: SetMaterial
  // Desc: Sets the material for this mesh
  // Parm: Material *pMaterial - the material
  // --------------------------------------------------------------------------
  inline void SetMaterial(const Material *pMaterial);

  // --------------------------------------------------------------------------
  // Name: GetColorMaterial
  // Desc: Get the color material
  // Retn: D3DMATERIAL & - the material
  // --------------------------------------------------------------------------
  inline const D3DMATERIAL &GetColorMaterial() const;
  inline void SetColorMaterial(const D3DMATERIAL &m);

  // --------------------------------------------------------------------------
  // Name: GetTextureArray
  // Desc: Get the texture array
  // Retn: TextureArray & - the texture array
  // --------------------------------------------------------------------------
  inline TextureArray &GetTextureArray();
  inline const TextureArray &GetTextureArray() const;

  // --------------------------------------------------------------------------
  // Manage the faces that we render
  // --------------------------------------------------------------------------
  inline uint GetFaceStart()            const { return m_FaceStart;    }
  inline uint GetFaceCount()            const { return m_FaceCount;    }
  inline uint GetVertexStart()          const { return m_VertexStart;  }
  inline uint GetVertexCount()          const { return m_VertexCount;  }
  inline void SetFaceStart(uint index)        { m_FaceStart = index;   }
  inline void SetFaceCount(uint index)        { m_FaceCount = index;   }
  inline void SetVertexStart(uint index)      { m_VertexStart = index; }
  inline void SetVertexCount(uint index)      { m_VertexCount = index; }

  // --------------------------------------------------------------------------
  // The file header
  // --------------------------------------------------------------------------
  struct FileHeader
  {
    D3DMATERIAL     ColorMaterial;    // The color material
    uint            FaceStart;        // The first face to render
    uint            FaceCount;        // The number of faces to render
    uint            VertexStart;      // The start vertex
    uint            VertexCount;      // The number of vertices
    FileString<256> Tex0;             // The diffuse texture
    FileString<256> Tex1;             // The alpha texture
    FileString<256> Tex2;             // The normal texture
    FileString<256> Tex3;             // Extra texture slot
    FileString<256> MaterialName;     // The material name
  }; // FileHeader

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  uint            m_Index;            // The index within the mesh
  D3DMATERIAL     m_ColorMaterial;    // The color material
  TextureArray    m_TextureArray;     // The textures
  uint            m_FaceStart;        // The first face to render
  uint            m_FaceCount;        // The number of faces to render
  uint            m_VertexStart;      // The start vertex
  uint            m_VertexCount;      // The number of vertices
  const Material *m_pMaterial;        // The material (effect) to use

}; // MeshSubset


// ----------------------------------------------------------------------------
// Name: Mesh  (class)
// Desc: A renderable mesh
// ----------------------------------------------------------------------------
class Mesh : public DeviceObject, public RefCounted, private Unique
{
public:
  // --------------------------------------------------------------------------
  // Name: Mesh
  // Desc: Constructor
  // Parm: const String &name - the name of the mesh
  // --------------------------------------------------------------------------
  Mesh(const String &name);
  
  // --------------------------------------------------------------------------
  // Name: ~Mesh
  // Desc: Destructor
  // --------------------------------------------------------------------------
  virtual ~Mesh();

  // --------------------------------------------------------------------------
  // Name: GetId
  // Desc: Get the unique Id for this mesh
  // Retn: ulong - the id
  // --------------------------------------------------------------------------
  inline ulong GetId() const;

  // --------------------------------------------------------------------------
  // Name: GetName
  // Desc: Get the name
  // --------------------------------------------------------------------------
  inline const String &GetName() const   { return m_name; }

  // --------------------------------------------------------------------------
  // Name: SetName
  // Desc: Set the name
  // Parm: const String &str - the name
  // --------------------------------------------------------------------------
  inline void SetName(const String &str) { m_name = str;  }

  // --------------------------------------------------------------------------
  // Enabled flag
  // --------------------------------------------------------------------------
  void SetEnabled(bool enabled) { m_Enabled = enabled; }
  bool IsEnabled() const        { return m_Enabled;    }

  // --------------------------------------------------------------------------
  // Casting Shadows
  // --------------------------------------------------------------------------
  void SetCastShadow(bool castShadow) { m_CastShadow = castShadow; }
  bool GetCastShadow() const           { return m_CastShadow;  }

  // --------------------------------------------------------------------------
  // Name: Mesh::Load
  // Desc: Load the mesh's data from the given file
  // Parm: const String &filename - the filename of the file that holds the 
  //                                objects geometry
  // Retn: bool                   - true if the mesh loaded it's geometry 
  //                                successfully
  // --------------------------------------------------------------------------
  virtual bool Load(FileHandle handle);
  virtual bool Save(FileHandle handle);
  const FileHandle &GetFileHandle() const { return m_FileHandle; }

  // --------------------------------------------------------------------------
  // Name: CreateInstance
  // Desc: Creates an instance for this object
  // Parm: const String &name  - the name of the instance
  // Retn: MeshInstance * - the instance
  // --------------------------------------------------------------------------
  virtual MeshInstance *CreateInstance(const String &name);

  // --------------------------------------------------------------------------
  // Name: CreateInstance
  // Desc: Creates an instance for this object
  // Parm: const String &name  - the name of the instance
  // Retn: MeshInstance * - the instance
  // --------------------------------------------------------------------------
  virtual MeshInstance *CreateInstance(const String &name, const Matrix &matrix);

  // --------------------------------------------------------------------------
  // Name: GetBSphere
  // Desc: Gets the bounding sphere of this mesh
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
  // Name: IsBoundsDirty
  // Desc: Test if the mesh bounds needs to be updated
  // --------------------------------------------------------------------------
  virtual bool IsBoundsDirty() const  { return m_bounds_dirty; }

  // --------------------------------------------------------------------------
  // Name: GetSubset
  // Desc: Get a subset
  // Parm: uint index - the subset index
  // Retn: MeshSubset & - the subset
  // --------------------------------------------------------------------------
  inline MeshSubset *GetSubset(uint index);
  
  // --------------------------------------------------------------------------
  // Name: GetSubset
  // Desc: Get a subset
  // Parm: uint index       - the index
  // Retn: const MeshSubset & - the subset
  // --------------------------------------------------------------------------
  inline const MeshSubset *GetSubset(uint index) const;
  
  // --------------------------------------------------------------------------
  // Name: AddSubset
  // Desc: Add a subset
  // Retn: MeshSubset & - the subset
  // --------------------------------------------------------------------------
  inline MeshSubset *AddSubset();

  // --------------------------------------------------------------------------
  // Name: PrintSubsets
  // Desc: Print the subsets
  // --------------------------------------------------------------------------
  void PrintSubsets();
  
  // --------------------------------------------------------------------------
  // Name: RemoveSubset
  // Desc: Remove a subset
  // Parm: uint index - the index
  // --------------------------------------------------------------------------
  inline void RemoveSubset(uint index);
  
  // --------------------------------------------------------------------------
  // Name: GetNumSubsets
  // Desc: Get the number of subsets
  // Retn: uint - the number
  // --------------------------------------------------------------------------
  inline uint GetNumSubsets() const;

  // --------------------------------------------------------------------------
  // Name: IntersectsBSphere
  // Desc: Tests for a collision between the provided ray (which must be already
  //       transformed into model space) and this object's bounding sphere.
  // Parm: const Ray &ray - the ray in object space
  // Retn: bool           - true if the ray intersects with the bounding sphere
  // --------------------------------------------------------------------------
  virtual bool IntersectsBSphere(const Ray &ray) const;

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
  virtual bool Intersects(const Ray &ray) const = 0;

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
  virtual bool Intersects(const Ray &ray, Vec3 &intersectPt, float &distance) const = 0;

  // --------------------------------------------------------------------------
  // Name: Render
  // Desc: Render the mesh for the given material pass
  // Parm: uint pass    - the pass
  // --------------------------------------------------------------------------
  virtual void Render(uint pass = 0) const = 0;

  // --------------------------------------------------------------------------
  // Name: RenderSubset
  // Desc: Render the mesh for the given subset and material pass
  // Parm: uint pass    - the pass
  // --------------------------------------------------------------------------
  virtual void RenderSubset(uint subset, uint pass = 0) const = 0;

  // --------------------------------------------------------------------------
  // Name: GetVertexType
  // Desc: Get the vertex type
  // Retn: const VertexType * - the vertex type
  // --------------------------------------------------------------------------
  virtual const VertexType *GetVertexType() const = 0;

  // --------------------------------------------------------------------------
  // Set the pre-render callback (after the material has been prepared but 
  // before the render.
  // --------------------------------------------------------------------------
  void SetPreRenderCallback(const Callback<void, MeshSubset *> &cb);

  // --------------------------------------------------------------------------
  // Name: IsVisible
  // Desc: Tests if the object is within the frustum
  // Parm: const Matrix &world_matrix - the world matrix
  // Parm: const Frustum &frustum   - the view frustum
  // Retn: bool                     - true if the object is within the frustum 
  // --------------------------------------------------------------------------
  inline bool IsVisible(const Matrix &world_matrix, const Frustum &frustum) const;

  // --------------------------------------------------------------------------
  // Name: MeshLog
  // Desc: Log mesh operations
  // Parm: const char *format - the format of the log
  // Parm: ...                - the arguments
  // --------------------------------------------------------------------------
  inline void MeshLog(const char *format, ...);

protected:
  // --------------------------------------------------------------------------
  // Manage device memory
  // --------------------------------------------------------------------------
  virtual bool AllocateDeviceMemory() = 0;
  virtual bool ReleaseDeviceMemory() = 0;

  // --------------------------------------------------------------------------
  // Sub classes Load and Save functions
  // --------------------------------------------------------------------------
  virtual bool Load(FILE *pFile);
  virtual bool Save(FILE *pFile);

protected:
  // --------------------------------------------------------------------------
  // Protected members
  // --------------------------------------------------------------------------
  Callback<void, MeshSubset *> *m_pPreRenderCB;   // The pre-render callback
  String                        m_name;           // The mesh name
  FileHandle                    m_FileHandle;     // The mesh file handle
  Array<MeshSubset *>           m_SubsetArray;    // The array of subsets
  Sphere                        m_sphere;         // The mesh's bounding sphere
  Box                           m_box;            // The mesh's bounding box
  bool                          m_bounds_dirty;   // Does the bounding volume need to be updated
  const ulong                   m_id;             // The unique id of this mesh
  static ulong                  s_id_counter;     // The static id counter
  bool                          m_Enabled;        // The enabled flag
  bool                          m_CastShadow;     // The cast shadow flag

}; // class Mesh


// ----------------------------------------------------------------------------
// Array of mesh pointers
// ----------------------------------------------------------------------------
typedef Array<Mesh *> MeshPtrArray;


// ----------------------------------------------------------------------------
// Get the unique mesh Id
// ----------------------------------------------------------------------------
inline ulong Mesh::GetId() const
{
  return m_id;
} // GetId


// ----------------------------------------------------------------------------
// Clone a mesh instance
// ----------------------------------------------------------------------------
inline MeshInstance *MeshInstance::Clone(const String &name)
{
  return new MeshInstance(m_pobject, name, m_world_matrix);
} // Clone


// ----------------------------------------------------------------------------
// Get the name of a mesh instance
// ----------------------------------------------------------------------------
inline const String &MeshInstance::GetName() const
{
  return m_name;
} // GetName


// ----------------------------------------------------------------------------
// Set the name of a mesh instance
// ----------------------------------------------------------------------------
inline void MeshInstance::SetName(const String &name)
{
  m_name = name;
} // SetName


// ----------------------------------------------------------------------------
// Set the matrix
// ----------------------------------------------------------------------------
inline void MeshInstance::SetMatrix(const Matrix &matrix)
{
  m_world_matrix = matrix;
} // SetMatrix


// ----------------------------------------------------------------------------
// Get the matrix
// ----------------------------------------------------------------------------
inline Matrix &MeshInstance::GetMatrix()
{
  return m_world_matrix;
} // GetMatrix


// ----------------------------------------------------------------------------
// Get the matrix
// ----------------------------------------------------------------------------
inline const Matrix &MeshInstance::GetMatrix() const
{
  return m_world_matrix;
} // GetMatrix


// ----------------------------------------------------------------------------
// Get the mesh
// ----------------------------------------------------------------------------
inline Mesh *MeshInstance::GetMesh()
{
  return m_pobject;
} // GetMesh


// ----------------------------------------------------------------------------
// Set the last culled frame number
// ----------------------------------------------------------------------------
inline void MeshInstance::SetLastFrameCulled(uqword frameNumber)
{
  m_last_frame = frameNumber;
} // SetLastFrameCulled


// ----------------------------------------------------------------------------
// Get the last culled frame number
// ----------------------------------------------------------------------------
inline uqword MeshInstance::GetLastFrameCulled() const
{
  return m_last_frame;
} // GetLastFrameCulled


// ----------------------------------------------------------------------------
// Test if the mesh is within the frustum
// ----------------------------------------------------------------------------
inline bool Mesh::IsVisible(const Matrix &world_matrix, const Frustum &frustum) const
{
  if (!m_Enabled)
    return false;

  if (frustum.Intersects(GetBSphere(), world_matrix) != Frustum::OUT_FRUSTUM)
    return true;

  return false;
} // IsVisible


// ----------------------------------------------------------------------------
// Get the subset
// ----------------------------------------------------------------------------
inline MeshSubset *Mesh::GetSubset(uint index)
{
  return m_SubsetArray[index];
} // GetSubSet


// ----------------------------------------------------------------------------
// Get the subset
// ----------------------------------------------------------------------------
inline const MeshSubset *Mesh::GetSubset(uint index) const
{
  return m_SubsetArray[index];
} // GetSubSet


// ----------------------------------------------------------------------------
// Add a subset
// ----------------------------------------------------------------------------
inline MeshSubset *Mesh::AddSubset()
{
  MeshSubset *s = new MeshSubset(m_SubsetArray.size());
  m_SubsetArray.insert(m_SubsetArray.end(), s);
  return s;
} // AddSubset


// ----------------------------------------------------------------------------
// Remove a subset
// ----------------------------------------------------------------------------
inline void Mesh::RemoveSubset(uint index)
{
  Array<MeshSubset *>::iterator iter = m_SubsetArray.begin();
  iter += index;
  delete (*iter);
  m_SubsetArray.erase(iter);
} // RemoveSubset


// ----------------------------------------------------------------------------
// Get the number of subsets
// ----------------------------------------------------------------------------
inline uint Mesh::GetNumSubsets() const
{
  return m_SubsetArray.size();
} // GetNumSubsets


// --------------------------------------------------------------------------
// Set the color material
// --------------------------------------------------------------------------
inline void MeshSubset::SetColorMaterial(const D3DMATERIAL &m)
{
  m_ColorMaterial = m;
} // GetColorMaterial


// --------------------------------------------------------------------------
// Get the color material
// --------------------------------------------------------------------------
inline const D3DMATERIAL &MeshSubset::GetColorMaterial() const
{
  return m_ColorMaterial;
} // GetColorMaterial


// --------------------------------------------------------------------------
// Get the texture array
// --------------------------------------------------------------------------
inline TextureArray &MeshSubset::GetTextureArray()
{
  return m_TextureArray;
} // GetTextureArray


// --------------------------------------------------------------------------
// Get the texture array
// --------------------------------------------------------------------------
inline const TextureArray &MeshSubset::GetTextureArray() const
{
  return m_TextureArray;
} // GetTextureArray


// ----------------------------------------------------------------------------
// Get the material
// ----------------------------------------------------------------------------
inline const Material *MeshSubset::GetMaterial() const
{
  return m_pMaterial;
} // GetMaterial


// ----------------------------------------------------------------------------
// Set the material
// ----------------------------------------------------------------------------
inline void MeshSubset::SetMaterial(const Material *pMaterial)
{
  m_pMaterial = pMaterial;
} // SetMaterial


// ----------------------------------------------------------------------------
// Log any mesh operation
// ----------------------------------------------------------------------------
inline void Mesh::MeshLog(const char *format, ...)
{
#ifdef __MESH_LOGGING

  char buffer[1024];
  
  va_list argList;
  va_start(argList, format);
  vsprintf(buffer, format, argList);
  va_end(argList);

  LOG_INFO << buffer << ENDLOG;

#endif // __MESH_LOGGING
} // MeshLog


#endif // _BASE_MESH_H

// -- EOF

