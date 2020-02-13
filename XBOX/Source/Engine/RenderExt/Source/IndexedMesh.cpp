
#include "IndexedMesh.h"


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
IndexedMesh::IndexedMesh(const String &name, const VertexType *pvertex_type)
: Mesh                    (name),
  m_pvertex_type          (pvertex_type),
  m_pvertex_buffer        (0),
  m_pindex_buffer         (0),
  m_pvertex_data          (0),
  m_pindex_data           (0),
  m_num_verts             (0),
  m_num_faces             (0),
  m_num_verts_alloc       (0),
  m_num_faces_alloc       (0),
  m_vertex_dirty          (false),
  m_index_dirty           (false),
  m_rebuild_vertex_array  (false),
  m_rebuild_index_array   (false),
  m_dynamic_vertex_buffer (false),
  m_dynamic_index_buffer  (false)
{
  SetVertexBufferDynamic(false);
  SetIndexBufferDynamic(false);

  REF_COUNT_CTOR(IndexedMesh);
} // IndexedMesh


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
IndexedMesh::IndexedMesh(const String &name)
: Mesh                    (name),
  m_pvertex_type          (NULL),
  m_pvertex_buffer        (0),
  m_pindex_buffer         (0),
  m_pvertex_data          (0),
  m_pindex_data           (0),
  m_num_verts             (0),
  m_num_faces             (0),
  m_num_verts_alloc       (0),
  m_num_faces_alloc       (0),
  m_vertex_dirty          (false),
  m_index_dirty           (false),
  m_rebuild_vertex_array  (false),
  m_rebuild_index_array   (false),
  m_dynamic_vertex_buffer (false),
  m_dynamic_index_buffer  (false)
{
  SetVertexBufferDynamic(false);
  SetIndexBufferDynamic(false);

  m_pvertex_type = NULL;

  REF_COUNT_CTOR(IndexedMesh);
} // IndexedMesh


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
IndexedMesh::~IndexedMesh()
{
  if (m_pindex_buffer)
    SafeRelease(m_pindex_buffer);

  if (m_pvertex_buffer)
    SafeRelease(m_pvertex_buffer);

  if (m_pvertex_data)
      delete[] m_pvertex_data;

  if (m_pindex_data)
      delete[] m_pindex_data;

  REF_COUNT_DTOR(IndexedMesh);
} // ~IndexedMesh


// ----------------------------------------------------------------------------
// Name: IndexedMesh::AllocateDeviceMemory
// Desc: Called when the device has been reset
// ----------------------------------------------------------------------------
bool IndexedMesh::AllocateDeviceMemory()
{
  // Flag the buffers to be recreated
  m_rebuild_index_array  = true;
  m_rebuild_vertex_array = true;
  m_index_dirty          = true;
  m_vertex_dirty         = true;

  return true;
} // AllocateDeviceMemory


// ----------------------------------------------------------------------------
// Name: IndexedMesh::ReleaseDeviceMemory
// Desc: Called before the device is reset
// ----------------------------------------------------------------------------
bool IndexedMesh::ReleaseDeviceMemory()
{
  // Release our index buffer
  if (m_pindex_buffer)
    SafeRelease(m_pindex_buffer);
  m_pindex_buffer = NULL;

  // Release our vertex buffer
  if (m_pvertex_buffer)
    SafeRelease(m_pvertex_buffer);
  m_pvertex_buffer = NULL;

  // Flag the buffers to be recreated
  m_rebuild_index_array  = true;
  m_rebuild_vertex_array = true;
  m_index_dirty          = true;
  m_vertex_dirty         = true;

  return true;
} // ReleaseDeviceMemory


// ----------------------------------------------------------------------------
// Set the maximum number of allocated vertices
// ----------------------------------------------------------------------------
void IndexedMesh::SetMaxVerts(uint max_verts)
{
  uint num_to_allocate = max_verts;
  uint num_to_copy     = m_num_verts_alloc;

  // Check if we are shrinking the array rather
  // then growing it.
  if (max_verts < m_num_verts_alloc)
    num_to_copy = max_verts;

  // Store a pointer to the origional data
  ubyte *porig_data = (ubyte *) m_pvertex_data;

  // Create a new array
  NULL_ASSERT(m_pvertex_type);
  m_pvertex_data = new ubyte[num_to_allocate * m_pvertex_type->GetSize()];

  // Copy the old data into the new array
  if (num_to_copy > 0)
    memcpy(m_pvertex_data, porig_data, num_to_copy * m_pvertex_type->GetSize());

  // Clean up the old array
  if (porig_data)
    delete[] porig_data;

  // Update the number of verts
  m_num_verts_alloc = num_to_allocate;

  // Set the buffer as dirty
  m_rebuild_vertex_array  = true;
} // SetMaxVerts


// ----------------------------------------------------------------------------
// Set the maximum number of allocated faces
// ----------------------------------------------------------------------------
void IndexedMesh::SetMaxFaces(uint max_faces)
{
  uint num_to_allocate = max_faces;
  uint num_to_copy     = m_num_faces_alloc;

  // Check if we are shrinking the array rather
  // then growing it.
  if (max_faces < m_num_faces_alloc)
    num_to_copy = max_faces;

  // Store a pointer to the origional data
  IndexedMesh::Face *porig_data = m_pindex_data;

  // Create a new array
  m_pindex_data = (IndexedMesh::Face *) new ubyte[num_to_allocate * sizeof(IndexedMesh::Face)];

  // Copy the old data into the new array
  if (num_to_copy > 0)
    memcpy(m_pindex_data, porig_data, num_to_copy * sizeof(IndexedMesh::Face));

  // Clean up the old array
  if (porig_data)
    delete[] porig_data;

  // Update the number of faces
  m_num_faces_alloc = num_to_allocate;

  // Set the buffer as dirty
  m_rebuild_index_array = true;
} // SetMaxFaces


// ----------------------------------------------------------------------------
// Render the mesh
// ----------------------------------------------------------------------------
void IndexedMesh::Render(uint pass) const
{
  for (uint i = 0; i < m_SubsetArray.size(); i++)
    RenderSubset(i, pass);
} // Render


// ----------------------------------------------------------------------------
// Render the mesh subset
// ----------------------------------------------------------------------------
void IndexedMesh::RenderSubset(uint subset, uint pass) const
{
  // If we have nothing to draw, just return
  if (m_num_faces == 0 || m_num_verts == 0)
    return;

  // Get the Subset
  MeshSubset *pSubset = m_SubsetArray[subset];

  // Call the pre-render callback
  if (m_pPreRenderCB)
  {
    (*m_pPreRenderCB)(pSubset);
  }

  if (pass == 0)
  {
    // See if we need to rebuid the vertex buffer
    if (m_rebuild_vertex_array || !m_pvertex_buffer)
    {
      if (m_pvertex_buffer)
        SafeRelease(m_pvertex_buffer);

      DWORD usage = D3DUSAGE_WRITEONLY;
      if (m_dynamic_vertex_buffer)
        usage |= D3DUSAGE_DYNAMIC;

      NULL_ASSERT(m_pvertex_type);
#if XBOX
      D3DCheck(Device->SetStreamSource(0, 0, 0));
      D3DCheck(Device->CreateVertexBuffer(m_num_verts_alloc * m_pvertex_type->GetSize(), usage, 
        NULL, D3DPOOL_DEFAULT, &m_pvertex_buffer));
#else
      D3DCheck(Device->SetStreamSource(0, 0, 0, 0));
      D3DCheck(Device->CreateVertexBuffer(m_num_verts_alloc * m_pvertex_type->GetSize(), usage, 
        NULL, D3DPOOL_DEFAULT, &m_pvertex_buffer, 0));
#endif

      m_rebuild_vertex_array = false;
    } // if
    
    // See if we need to write data into the vertex buffer
    if (m_vertex_dirty)
    {
      void *pvertex_ptr;
#if XBOX
      D3DCheck(Device->SetStreamSource(0, 0, 0));
#else
      D3DCheck(Device->SetStreamSource(0, 0, 0, 0));
#endif

#if XBOX
      D3DCheck((m_pvertex_buffer->Lock(0, 0, (BYTE**) &pvertex_ptr, 0)));
#else
      if (m_dynamic_vertex_buffer)
      {
        D3DCheck((m_pvertex_buffer->Lock(0, 0, (void**) &pvertex_ptr, D3DLOCK_NOSYSLOCK | D3DLOCK_DISCARD)));
      } // if
      else
      {
        D3DCheck((m_pvertex_buffer->Lock(0, 0, (void**) &pvertex_ptr, D3DLOCK_NOSYSLOCK)));
      } // else
#endif
      NULL_ASSERT(m_pvertex_type);
      memcpy(pvertex_ptr, m_pvertex_data, m_num_verts * m_pvertex_type->GetSize());
      D3DCheck(m_pvertex_buffer->Unlock());

      m_vertex_dirty = false;
    } // if

    // See if we need to rebuid the index buffer
    if (m_rebuild_index_array || !m_pindex_buffer)
    {
      if (m_pindex_buffer)
        SafeRelease(m_pindex_buffer);

      DWORD usage = D3DUSAGE_WRITEONLY;
      if (m_dynamic_index_buffer)
        usage |= D3DUSAGE_DYNAMIC;

#if XBOX
      D3DCheck(Device->SetIndices(0, 0));
      D3DCheck(Device->CreateIndexBuffer(m_num_faces_alloc * sizeof(IndexedMesh::Face), usage, 
        D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pindex_buffer));
#else
      D3DCheck(Device->SetIndices(0));
      D3DCheck(Device->CreateIndexBuffer(m_num_faces_alloc * sizeof(IndexedMesh::Face), usage, 
        D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pindex_buffer, 0));
#endif

      m_rebuild_index_array = false;
    } // if
    
    // See if we need to write data into the index buffer
    if (m_index_dirty)
    {
      void *pindex_ptr;
#if XBOX
      D3DCheck(Device->SetIndices(0, 0));
#else
      D3DCheck(Device->SetIndices(0));
#endif

#if XBOX
      D3DCheck(m_pindex_buffer->Lock(0, 0, (BYTE**) &pindex_ptr, 0));
#else
      if (m_dynamic_index_buffer)
      {
        D3DCheck(m_pindex_buffer->Lock(0, 0, (void**) &pindex_ptr, D3DLOCK_NOSYSLOCK | D3DLOCK_DISCARD));
      } // if
      else
      {
        D3DCheck(m_pindex_buffer->Lock(0, 0, (void**) &pindex_ptr, D3DLOCK_NOSYSLOCK));
      } // else
#endif

      memcpy(pindex_ptr, m_pindex_data, m_num_faces * sizeof(IndexedMesh::Face));
      D3DCheck(m_pindex_buffer->Unlock());

      m_index_dirty = false;
    } // if

    // Draw the geometry
    NULL_ASSERT(m_pvertex_type);
#if XBOX
    Device->SetIndices(m_pindex_buffer, 0);
    Device->SetStreamSource(0, m_pvertex_buffer, m_pvertex_type->GetSize());
#else
    Device->SetIndices(m_pindex_buffer);
    Device->SetStreamSource(0, m_pvertex_buffer, 0, m_pvertex_type->GetSize());
#endif
  } // if

  // Get the number of verts
  uint numVertex = pSubset->GetVertexCount();
  if (numVertex == 0)
  {
    numVertex = m_num_verts;
  }

  PROFILE_RENDER_CALLS(1);
  PROFILE_VERTS(m_num_verts);
  PROFILE_FACES(pSubset->GetFaceCount());

#if XBOX
  Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, m_num_verts, pSubset->GetFaceStart() * 3, pSubset->GetFaceCount());
#else
  Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, pSubset->GetVertexStart(), 0, numVertex, pSubset->GetFaceStart() * 3, pSubset->GetFaceCount());
#endif
} // RenderSubset


// ----------------------------------------------------------------------------
// Recalculate the bounding sphere and bounding box
// ----------------------------------------------------------------------------
void IndexedMesh::RecalculateBounds()
{
  if (!m_bounds_dirty)
    return;

  // Get the position data
  Vec3GeomPtr vertex_pos = GetVec3Ptr(VI_Position);

  // Recalculate the aabb
  for (size_t i = 0; i < m_num_verts; i++)
  {
    Vec3 &pos = (*vertex_pos);

    if (i == 0)
    {
      m_box.MinPt[0] = pos[0];
      m_box.MinPt[1] = pos[1];
      m_box.MinPt[2] = pos[2];
      m_box.MaxPt[0] = pos[0];
      m_box.MaxPt[1] = pos[1];
      m_box.MaxPt[2] = pos[2];
    } // if
    else
    {
      m_box.MinPt[0] = min(m_box.MinPt[0], pos[0]);
      m_box.MinPt[1] = min(m_box.MinPt[1], pos[1]);
      m_box.MinPt[2] = min(m_box.MinPt[2], pos[2]);
      m_box.MaxPt[0] = max(m_box.MaxPt[0], pos[0]);
      m_box.MaxPt[1] = max(m_box.MaxPt[1], pos[1]);
      m_box.MaxPt[2] = max(m_box.MaxPt[2], pos[2]);
    } // else

    ++vertex_pos;
  } // for

  // The first guess radius of the sphere is half of the diagonal
  Vec3 diagonal   = m_box.MaxPt - m_box.MinPt;
  m_sphere.radius = diagonal.Length() / 2.0f;

  // The center point of the spehre is in the center of the m_box
  m_sphere.center   = m_box.MinPt + (diagonal / 2.0f);

  // Get the vertex data
  vertex_pos = GetVec3Ptr(VI_Position);

  // Get a more accurate radius by measuring to each vertex from the 
  // known cerner point
  m_sphere.radius = 0.0f;
  for (size_t i = 0; i < m_num_verts; i++)
  {
    Vec3 vec    = (*vertex_pos) - m_sphere.center;
    m_sphere.radius = max(m_sphere.radius, vec.LengthSq());

    ++vertex_pos;
  } // for
  m_sphere.radius = sqrtf(m_sphere.radius);

  m_bounds_dirty = false;
} // RecalculateBounds


// --------------------------------------------------------------------------
// Gets the bounding sphere of this object
// --------------------------------------------------------------------------
const Sphere &IndexedMesh::GetBSphere() const
{
  if (!m_bounds_dirty)
    return m_sphere;

  const_cast<IndexedMesh *>(this)->RecalculateBounds();
  return m_sphere;
} // GetBSphere


// --------------------------------------------------------------------------
// Gets the bounding box of this object
// --------------------------------------------------------------------------
const Box &IndexedMesh::GetBBox() const
{
  if (!m_bounds_dirty)
    return m_box;

  const_cast<IndexedMesh *>(this)->RecalculateBounds();
  return m_box;
} // GetBBox


// --------------------------------------------------------------------------
// Tests for a collision between the provided ray (which must be already
// transformed into model space) and this object's geometry.
// --------------------------------------------------------------------------
bool IndexedMesh::Intersects(const Ray &ray, Vec3 &intersectPt, float &distance) const
{
  // Test the bounding sphere
  if (!m_sphere.TestCollision(ray))
    return false;

  // Get the position and face data
  const Vec3GeomPtr positionArray = GetVec3Ptr(VI_Position);
  const IndexedMesh::Face *pFaceArray = GetFaceData();

  // Variables required for ray test
  Vec3  point, bary;
  float dist     = 0.0f;
  bool  foundHit = false;

  // Test every face
  for (uint i = 0; i < m_num_faces; i++)
  {
    if (ray.IntersectsTriangle(
      positionArray[pFaceArray->a], // [in]  First triangle vertex
      positionArray[pFaceArray->b], // [in]  Second triangle vertex
      positionArray[pFaceArray->c], // [in]  Third triangle vertex
      point,                        // [out] Intersection point
      bary,                         // [out] Triangle bary-centric coords
      dist))                        // [out] Distance to intersection
    {
      if (!foundHit)
      {
        foundHit    = true;
        intersectPt = point;
        distance    = dist;
      } // if
      else
      {
        if (dist < distance)
        {
          intersectPt = point;
          distance    = dist;
        } // if
      } // else
    } // if
  } // for

  return foundHit;
} // Intersects


// --------------------------------------------------------------------------
// Tests for a collision between the provided ray (which must be already
// transformed into model space) and this object's geometry.
// --------------------------------------------------------------------------
bool IndexedMesh::Intersects(const Ray &ray) const
{
  // Test the bounding sphere
  if (!m_sphere.TestCollision(ray))
    return false;

  // Get the position and face data
  Vec3GeomPtr positionArray = GetVec3Ptr(VI_Position);
  const IndexedMesh::Face *pFaceArray = GetFaceData();

  // Variables required for ray test
  Vec3  point, bary;
  float dist;

  // Test every face
  for (uint i = 0; i < m_num_faces; i++)
  {
    if (ray.IntersectsTriangle(
      positionArray[pFaceArray->a], // [in]  First triangle vertex
      positionArray[pFaceArray->b], // [in]  Second triangle vertex
      positionArray[pFaceArray->c], // [in]  Third triangle vertex
      point,                        // [out] Intersection point
      bary,                         // [out] Triangle bary-centric coords
      dist))                        // [out] Distance to intersection
    {
      return true;
    } // if

    ++pFaceArray;
  } // for

  return false;
} // Intersects


// --------------------------------------------------------------------------
// Load the mesh from the given file
// --------------------------------------------------------------------------
bool IndexedMesh::Load(FILE *pFile)
{
  // Cleanup the vertex buffer
  if (m_pvertex_buffer)
    SafeRelease(m_pvertex_buffer);

  // Cleanup the index buffer
  if (m_pindex_buffer)
    SafeRelease(m_pindex_buffer);

  // Cleanup the vertex data
  if (m_pvertex_data)
      delete[] m_pvertex_data;

  // Cleanup the index data
  if (m_pindex_data)
      delete[] m_pindex_data;

  // Remove the subsets
  for (uint i = 0; i < m_SubsetArray.size(); i++)
    delete m_SubsetArray[i];
  m_SubsetArray.clear();

  // Reset the member values
  m_name                  = "";
  m_pvertex_buffer        = 0;
  m_pindex_buffer         = 0;
  m_pvertex_data          = 0;
  m_pindex_data           = 0;
  m_pvertex_type          = 0;
  m_num_verts             = 0;
  m_num_faces             = 0;
  m_num_verts_alloc       = 0;
  m_num_faces_alloc       = 0;
  m_vertex_dirty          = true;
  m_index_dirty           = true;
  m_rebuild_vertex_array  = true;
  m_rebuild_index_array   = true;
  m_bounds_dirty          = true;
  m_dynamic_vertex_buffer = false;
  m_dynamic_index_buffer  = false;

  // Create the header
  IndexedMesh::FileHeader header;

  // Read the header from the file
  if (fread(&header, sizeof(IndexedMesh::FileHeader), 1, pFile) != 1)
    return false;

  // Set the mesh name
  m_name = header.Name;

  // Set the cast shadow flag
  m_CastShadow = header.CastShadow;

  // Set the vertex type
  if (!SetVertexTypeByName(String(header.VertexTypeName.Get())))
    return false;

  // Check the vertex type is the same as in the file
  NULL_ASSERT(m_pvertex_type);
  if (header.VertexSize != m_pvertex_type->GetSize())
    return false;

  // Set the data size and type
  SetNumVerts(header.NumVerts);
  SetNumFaces(header.NumFaces);
  SetVertexBufferDynamic(header.DynamicVertexBuffer);
  SetIndexBufferDynamic(header.DynamicIndexBuffer);
  
  // Read the vertex data from the file
  if (fread(m_pvertex_data, header.VertexSize * m_num_verts, 1, pFile) != 1)
    return false;

  // Read the index data from the file
  if (fread(m_pindex_data, sizeof(IndexedMesh::Face) * m_num_faces, 1, pFile) != 1)
    return false;

  // Read the subsets from the file
  for (uint i = 0; i < header.MeshSubsetCount; i++)
  {
    // Create the header
    MeshSubset::FileHeader subsetHeader;

    // Read the subset from the file
    if (fread(&subsetHeader, sizeof(MeshSubset::FileHeader), 1, pFile) != 1)
      return false;

    // Create a new subset
    MeshSubset *pSubset = AddSubset();

    // Set the color material
    pSubset->SetColorMaterial(subsetHeader.ColorMaterial);

    // Set the diffuse texture
    if (subsetHeader.Tex0)
    {
      MeshLog("[%d] Loading the diffuse texture: %s", (int) i, subsetHeader.Tex0.Get());

      FileHandle handle = Application.GetTextureDatabase()->FindFileHandle(subsetHeader.Tex0);

      Texture *pTex = TextureLoader::LoadTexture(handle);
      if (!pTex)
      {
        MeshLog("[%d] Failed to load the diffuse texture: %s", (int) i, subsetHeader.Tex0.Get());
        MeshLog("--------------------------------------------------");
        return false;
      } // if

      pSubset->GetTextureArray().SetTex0(pTex);
    } // if
    else
    {
      MeshLog("[%d] No diffuse texture was found", (int) i);
    } // else

    // Set the alpha texture
    if (subsetHeader.Tex1)
    {
      MeshLog("[%d] Loading the alpha texture: %s", (int) i, subsetHeader.Tex1.Get());

      FileHandle handle = Application.GetTextureDatabase()->FindFileHandle(subsetHeader.Tex1);

      Texture *pTex = TextureLoader::LoadTexture(handle);
      if (!pTex)
      {
        MeshLog("[%d] Failed to load the alpha texture: %s", (int) i, subsetHeader.Tex1.Get());
        MeshLog("--------------------------------------------------");
        return false;
      } // if

      pSubset->GetTextureArray().SetTex1(pTex);
    } // if
    else
    {
      MeshLog("[%d] No alpha texture was found", (int) i);
    } // else

    // Set the normal texture
    if (subsetHeader.Tex2)
    {
      MeshLog("[%d] Loading the normal texture: %s", (int) i, subsetHeader.Tex2.Get());

      FileHandle handle = Application.GetTextureDatabase()->FindFileHandle(subsetHeader.Tex2);

      Texture *pTex = TextureLoader::LoadTexture(handle);
      if (!pTex)
      {
        MeshLog("[%d] Failed to load the normal texture: %s", (int) i, subsetHeader.Tex2.Get());
        MeshLog("--------------------------------------------------");
        return false;
      } // if

      pSubset->GetTextureArray().SetTex2(pTex);
    } // if
    else
    {
      MeshLog("[%d] No normal texture was found", (int) i);
    } // else

    // Set the extra texture
    if (subsetHeader.Tex3)
    {
      MeshLog("[%d] Loading the texture 0: %s", (int) i, subsetHeader.Tex3.Get());

      FileHandle handle = Application.GetTextureDatabase()->FindFileHandle(subsetHeader.Tex3);

      Texture *pTex = TextureLoader::LoadTexture(handle);
      if (!pTex)
      {
        MeshLog("[%d] Failed to load the extra texture: %s", (int) i, subsetHeader.Tex3.Get());
        MeshLog("--------------------------------------------------");
        return false;
      } // if

      pSubset->GetTextureArray().SetTex3(pTex);
    } // if
    else
    {
      MeshLog("[%d] No extra texture was found", (int) i);
    } // else

    // Assign the effect if it exists
    if (subsetHeader.MaterialName)
    {
      MeshLog("[%d] Loading the material: %s", (int) i, subsetHeader.MaterialName.Get());

      const Material *pMat = MaterialCache::GetMaterial(subsetHeader.MaterialName);
      if (!pMat)
      {
        MeshLog("[%d] Failed to load the effect: %s", (int) i, subsetHeader.MaterialName.Get());
        MeshLog("--------------------------------------------------");
        return false;
      } // if

      pSubset->SetMaterial(pMat);
    } // if
    else
    {
      MeshLog("[%d] Using the default material", (int) i);

      const Material *pMat = MaterialCache::GetDefaultMaterial();
      if (!pMat)
      {
        MeshLog("[%d] No default material has been set", (int) i);
        MeshLog("--------------------------------------------------");
        return false;
      } // if

      pSubset->SetMaterial(pMat);
    } // else

    // Set the face range

    MeshLog("[%d] The start face is: %d", (int) i, (int) subsetHeader.FaceStart);
    MeshLog("[%d] The face count is: %d", (int) i, (int) subsetHeader.FaceCount);
    pSubset->SetFaceStart(subsetHeader.FaceStart);
    pSubset->SetFaceCount(subsetHeader.FaceCount);

    MeshLog("[%d] Successfully loaded the attribute", (int) i);
  } // for

  return true;
} // Load


#if PC
// --------------------------------------------------------------------------
// Save the mesh to the given file
// --------------------------------------------------------------------------
bool IndexedMesh::Save(FILE *pFile)
{
  // Ensure we have some data to write
  if (m_num_verts == 0 || m_num_faces == 0)
    return false;

  NULL_ASSERT(m_pvertex_type);

  // Create the header
  IndexedMesh::FileHeader header;

  // Set the common header attributes
  header.Name                 = m_name;
  header.MeshSubsetCount      = m_SubsetArray.size();
  header.VertexTypeName       = m_pvertex_type->GetName();
  header.NumVerts             = m_num_verts;
  header.NumFaces             = m_num_faces;
  header.DynamicVertexBuffer  = m_dynamic_vertex_buffer;
  header.DynamicIndexBuffer   = m_dynamic_index_buffer;
  header.VertexSize           = m_pvertex_type->GetSize();
  header.CastShadow           = m_CastShadow;
  header.Reserved0            = NULL;
  header.Reserved1            = NULL;
  header.Reserved2            = NULL;
  header.Reserved3            = NULL;
  header.Reserved4            = NULL;

  // Write the header to the file
  if (fwrite(&header, sizeof(IndexedMesh::FileHeader), 1, pFile) != 1)
    return false;

  // Write the vertex data to the file
  NULL_ASSERT(m_pvertex_type);
  if (fwrite(m_pvertex_data, m_pvertex_type->GetSize() * m_num_verts, 1, pFile) != 1)
    return false;

  // Write the index data to the file
  if (fwrite(m_pindex_data, sizeof(IndexedMesh::Face) * m_num_faces, 1, pFile) != 1)
    return false;

  // Write the subsets to the file
  for (uint i = 0; i < m_SubsetArray.size(); i++)
  {
    // Get the subset
    MeshSubset *pSubset = m_SubsetArray[i];

    // Get the texture array
    TextureArray &texArray = pSubset->GetTextureArray();

    // Create the header
    MeshSubset::FileHeader subsetHeader;

    // Set the common header attributes
    subsetHeader.ColorMaterial      = pSubset->GetColorMaterial();
    subsetHeader.FaceStart          = pSubset->GetFaceStart();
    subsetHeader.FaceCount          = pSubset->GetFaceCount();

    // Set the texture filenames
    if (texArray.GetTex0())
      subsetHeader.Tex0             = texArray.GetTex0()->GetFileHandle().GetFilename();
    if (texArray.GetTex1())
      subsetHeader.Tex1             = texArray.GetTex1()->GetFileHandle().GetFilename();
    if (texArray.GetTex2())
      subsetHeader.Tex2             = texArray.GetTex2()->GetFileHandle().GetFilename();
    if (texArray.GetTex3())
      subsetHeader.Tex3             = texArray.GetTex3()->GetFileHandle().GetFilename();

    // Set the effect filename
    if (pSubset->GetMaterial())
      subsetHeader.MaterialName     = pSubset->GetMaterial()->GetName();

    // Write the subset to the file
    if (fwrite(&subsetHeader, sizeof(MeshSubset::FileHeader), 1, pFile) != 1)
      return false;
  } // for

  return true;
} // Save
#endif


#if PC
// --------------------------------------------------------------------------
// Import the mesh from the X file
// --------------------------------------------------------------------------
bool IndexedMesh::ImportFromX(const String &filename)
{
  // The required variables
  LPD3DXMESH mesh               = NULL;
  LPD3DXBUFFER adjacent_buffer  = NULL;
  LPD3DXBUFFER material_buffer  = NULL;
  LPD3DXBUFFER effect_buffer    = NULL;
  ulong options                 = D3DXMESH_SYSTEMMEM;
  ulong numMaterials            = 0;
  HRESULT hr                    = S_OK;

  // Release all this whenever we leave the stack
  StackRelease r0(mesh);
  StackRelease r1(adjacent_buffer);
  StackRelease r2(material_buffer);
  StackRelease r3(effect_buffer);

  MeshLog("--------------------------------------------------");
  MeshLog("Loading the mesh from the file: %s", filename.c_str());

  // Load the mesh
  if (FAILED(D3DXLoadMeshFromX(
    filename.c_str(), 
    options, 
    Device, 
    &adjacent_buffer, 
    &material_buffer, 
    &effect_buffer, 
    &numMaterials, 
    &mesh)))
  {
    MeshLog("Failed to load the file: %s", filename.c_str());
    MeshLog("--------------------------------------------------");
    return false;
  } // if

  MeshLog("Successfully loaded the file: %s", filename.c_str());

  // Get the material and effect buffers
  D3DXMATERIAL *pmaterials = (D3DXMATERIAL*) material_buffer->GetBufferPointer();
  D3DXEFFECTINSTANCE *peffects = (D3DXEFFECTINSTANCE *) effect_buffer->GetBufferPointer();

  // Get the vertex declaration from the mesh
  D3DVERTEXELEMENT9 decl[MAXD3DDECLLENGTH];
  if (FAILED(mesh->GetDeclaration(decl)))
  {
    MeshLog("Failed to get the vertex declaration");
    MeshLog("--------------------------------------------------");
    return false;
  } // if

  // Build the vertex type
  if (!SetVertexTypeByDeclaration(decl))
  {
    MeshLog("Failed to set the vertex type");
    MeshLog("--------------------------------------------------");
    return false;
  } // if

  // Extract the data from the mesh
  uint vertex_size = mesh->GetNumBytesPerVertex();
  uint num_verts   = mesh->GetNumVertices();
  uint num_faces   = mesh->GetNumFaces();
  uint face_size   = sizeof(ushort) * 3;

  MeshLog("The vertex size is: %d", (int) vertex_size);
  MeshLog("The number of verts is: %d", (int) num_verts);
  MeshLog("The number of faces is: %d", (int) num_faces);

  // Lock the vertex buffer
  void *pvertex_data;
  if (FAILED(mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**) &pvertex_data)))
  {
    MeshLog("Failed to lock the vertex buffer");
    MeshLog("--------------------------------------------------");
    return false;
  } // if

  // Copy the vertex data into the mesh
  this->SetNumVerts(num_verts);
  MeshLog("Copying the vertex data");
  memcpy(this->GetVertexData(), pvertex_data, num_verts * vertex_size);

  // Unlock the vertex data
  if (FAILED(mesh->UnlockVertexBuffer()))
  {
    MeshLog("Failed to unlock the vertex buffer");
    MeshLog("--------------------------------------------------");
    return false;
  } // if

  // Lock the index buffer
  void *pface_data;
  if (FAILED(mesh->LockIndexBuffer(D3DLOCK_READONLY, (void**) &pface_data)))
  {
    MeshLog("Failed to lock the index buffer");
    MeshLog("--------------------------------------------------");
    return false;
  } // if

  // Copy the index data into system memory
  this->SetNumFaces(num_faces);
  MeshLog("Copying the face data");
  memcpy((void *) this->GetFaceData(), pface_data, num_faces * face_size);

  // Unlock the index data
  if (FAILED(mesh->UnlockIndexBuffer()))
  {
    MeshLog("Failed to unlock the index buffer");
    MeshLog("--------------------------------------------------");
    return false;
  } // if

  // Combine the meshes to generate the attribute table
  DWORD *pAdjacency = new DWORD[3 * num_faces * sizeof(DWORD)];
  mesh->GenerateAdjacency(FLOAT_EPSILON, pAdjacency);
  mesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT, pAdjacency, NULL, NULL, NULL);
  delete[] pAdjacency;

  // Make sure the number of subsets is the same as the number of attributes
  ulong attributeCount;
  hr = mesh->GetAttributeTable(NULL, &attributeCount);
  if (FAILED(hr))
  {
    MeshLog("Failed to get the attribute table");
    MeshLog("--------------------------------------------------");
    return false;
  } // if

  MeshLog("The number of attributes is : %d", (int) attributeCount);
  MeshLog("The number of materials is : %d", (int) numMaterials);

  // Get the attribute table
  D3DXATTRIBUTERANGE *pAttr = new D3DXATTRIBUTERANGE[attributeCount];
  mesh->GetAttributeTable(pAttr, &attributeCount);

  // Get the attribute table
  D3DXATTRIBUTERANGE *pAttributeTable = new D3DXATTRIBUTERANGE[attributeCount];
  mesh->GetAttributeTable(pAttributeTable, &attributeCount);

  // Add all materials to the subset array
  for (uint i = 0; i < attributeCount; i++)
  {
    int attributeId = pAttributeTable[i].AttribId;

    MeshLog("[%d] Loading the subset", (int) i);

    // Get the material and the effect
    D3DXMATERIAL &d3dmat = pmaterials[attributeId];
    D3DXEFFECTINSTANCE &d3deffect = peffects[attributeId];

    // Create the subset
    MeshSubset *pSubset = this->AddSubset();

    // Set the color material
    pSubset->SetColorMaterial(d3dmat.MatD3D);

    // Set the diffuse texture
    if (d3dmat.pTextureFilename)
    {
      MeshLog("[%d] Loading the diffuse texture: %s", (int) i, d3dmat.pTextureFilename);

      FileHandle textureHandle = Application.GetImportDatabase()->FindFileHandle(d3dmat.pTextureFilename);

      // Load the texture
      Texture *pTex = TextureLoader::LoadTexture(textureHandle);
      if (!pTex)
      {
        MeshLog("[%d] Failed to load the diffuse texture: %s", (int) i, d3dmat.pTextureFilename);
        MeshLog("--------------------------------------------------");
        return false;
      } // if

      pSubset->GetTextureArray().SetTex0(pTex);
    } // if
    else
    {
      MeshLog("[%d] No texture was found", (int) i);
    } // else

    // Assign the effect if it exists
    if (d3deffect.pEffectFilename)
    {
      MeshLog("[%d] Loading the material: %s", (int) i, d3deffect.pEffectFilename);

      // Load the material
      const Material *pMat = MaterialCache::GetMaterial(d3deffect.pEffectFilename);
      if (!pMat)
      {
        MeshLog("[%d] Failed to load the material: %s", (int) i, d3deffect.pEffectFilename);
        MeshLog("--------------------------------------------------");
        return false;
      } // if

      pSubset->SetMaterial(pMat);
    } // if
    else
    {
      const Material *pMat = GetFixedFunctionMaterialByDeclaration(decl);
      if (!pMat)
      {
        MeshLog("[%d] Failed to determine the material", (int) i);
        MeshLog("--------------------------------------------------");
        return false;
      } // if

      MeshLog("[%d] Using the basic material %s", (int) i, pMat->GetName().c_str());
      MeshLog("--------------------------------------------------");
      pSubset->SetMaterial(pMat);
    } // else

    // Set the face range

    MeshLog("[%d] The start face is: %d", (int) i, (int) pAttributeTable[i].FaceStart);
    MeshLog("[%d] The face count is: %d", (int) i, (int) pAttributeTable[i].FaceCount);
    pSubset->SetFaceStart(pAttributeTable[i].FaceStart);
    pSubset->SetFaceCount(pAttributeTable[i].FaceCount);

    MeshLog("[%d] Successfully loaded the attribute", (int) i);
  } // for

  // Delete the attribute table
  delete[] pAttributeTable;

  // Flag to mesh to be updated
  this->SetDirty();

  // Done

  MeshLog("Successfully loaded the mesh");
  MeshLog("--------------------------------------------------");
  return true;
} // ImportFromX
#endif


// --------------------------------------------------------------------------
// Name: IndexedMesh::SetVertexTypeByName
// Desc: Sets the vertex type of this mesh to the vertex type registered for
//       the supplied name.
// Parm: name  - the name of the vertex type
// Retn: bool  - true if the vertex type was found for the supplied name
// --------------------------------------------------------------------------
bool IndexedMesh::SetVertexTypeByName(const String &name)
{
  const VertexType *pVertexType = VertexTypeCache::GetVertexType(name);
  if (pVertexType)
  {
    m_pvertex_type = pVertexType;
    return true;
  }

  m_pvertex_type = NULL;
  return false;
}


#if PC
// --------------------------------------------------------------------------
// Name: IndexedMesh::SetVertexTypeByDeclaration
// Desc: Sets the vertex type of this mesh to the closest match for the 
//       supplied vertex declaration.
// Parm: pDeclaration - the vertex type declaration.
// Retn: bool - true if a vertex type was found that supports the declaration.
// --------------------------------------------------------------------------
bool IndexedMesh::SetVertexTypeByDeclaration(D3DVERTEXELEMENT9 *pDeclaration)
{
  String vertexTypeName = "VertexType_";

  // Add the data to the vertex type
  for (uint i = 0; i < MAXD3DDECLLENGTH; i++)
  {
    // Get the decl item
    D3DVERTEXELEMENT9 &declItem = pDeclaration[i];

    // The end of the stream (see D3DDECL_END())
    if (declItem.Stream == 0xFF && declItem.Type == D3DDECLTYPE_UNUSED)
      return SetVertexTypeByName(vertexTypeName);

    switch (declItem.Usage)
    {
      case D3DDECLUSAGE_POSITION:       vertexTypeName += "P";  break;
      case D3DDECLUSAGE_BLENDWEIGHT:    vertexTypeName += "W";  break;
      case D3DDECLUSAGE_BLENDINDICES:   vertexTypeName += "I";  break;
      case D3DDECLUSAGE_NORMAL:         vertexTypeName += "N";  break;
      case D3DDECLUSAGE_PSIZE:          vertexTypeName += "Z";  break;
      case D3DDECLUSAGE_TEXCOORD:       vertexTypeName += "T";  break;
      case D3DDECLUSAGE_TANGENT:        vertexTypeName += "G";  break;
      case D3DDECLUSAGE_BINORMAL:       vertexTypeName += "B";  break;
      case D3DDECLUSAGE_TESSFACTOR:     vertexTypeName += "R";  break;
      case D3DDECLUSAGE_POSITIONT:      vertexTypeName += "S";  break;
      case D3DDECLUSAGE_COLOR:          vertexTypeName += "C";  break;
      case D3DDECLUSAGE_FOG:            vertexTypeName += "F";  break;
      case D3DDECLUSAGE_DEPTH:          vertexTypeName += "D";  break;
      case D3DDECLUSAGE_SAMPLE:         vertexTypeName += "L";  break;
    };
  } // for

  return SetVertexTypeByName(vertexTypeName);
}


const Material *IndexedMesh::GetFixedFunctionMaterialByDeclaration(D3DVERTEXELEMENT9 *pDeclaration)
{
  String materialName = "FixedFunctionMaterial_";

  // Add the data to the vertex type
  for (uint i = 0; i < MAXD3DDECLLENGTH; i++)
  {
    // Get the decl item
    D3DVERTEXELEMENT9 &declItem = pDeclaration[i];

    // The end of the stream (see D3DDECL_END())
    if (declItem.Stream == 0xFF && declItem.Type == D3DDECLTYPE_UNUSED)
    {
      i = MAXD3DDECLLENGTH;
      break;
    }

    switch (declItem.Usage)
    {
      case D3DDECLUSAGE_POSITION:       materialName += "P";  break;
      case D3DDECLUSAGE_NORMAL:         materialName += "N";  break;
      case D3DDECLUSAGE_TEXCOORD:       materialName += "T";  break;
      case D3DDECLUSAGE_COLOR:          materialName += "C";  break;
      case D3DDECLUSAGE_BLENDWEIGHT:    return NULL;  // Not supported in FixedFunctionMaterial
      case D3DDECLUSAGE_BLENDINDICES:   return NULL;  // Not supported in FixedFunctionMaterial
      case D3DDECLUSAGE_PSIZE:          return NULL;  // Not supported in FixedFunctionMaterial
      case D3DDECLUSAGE_TANGENT:        return NULL;  // Not supported in FixedFunctionMaterial
      case D3DDECLUSAGE_BINORMAL:       return NULL;  // Not supported in FixedFunctionMaterial
      case D3DDECLUSAGE_TESSFACTOR:     return NULL;  // Not supported in FixedFunctionMaterial
      case D3DDECLUSAGE_POSITIONT:      return NULL;  // Not supported in FixedFunctionMaterial
      case D3DDECLUSAGE_FOG:            return NULL;  // Not supported in FixedFunctionMaterial
      case D3DDECLUSAGE_DEPTH:          return NULL;  // Not supported in FixedFunctionMaterial
      case D3DDECLUSAGE_SAMPLE:         return NULL;  // Not supported in FixedFunctionMaterial
    };
  } // for

  const Material *pMaterial = MaterialCache::GetMaterial(materialName);

  if (!pMaterial)
    pMaterial = MaterialCache::GetDefaultMaterial();

  return pMaterial;
}
#endif


// -- EOF