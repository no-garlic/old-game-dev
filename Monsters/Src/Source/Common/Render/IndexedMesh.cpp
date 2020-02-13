
#include "Render/IndexedMesh.h"


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
  m_bounds_dirty          (true),
  m_dynamic_vertex_buffer (false),
  m_dynamic_index_buffer  (false)
{
  SetVertexBufferDynamic(false);
  SetIndexBufferDynamic(false);

  SafeRef(m_pvertex_type);

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
  m_bounds_dirty          (true),
  m_dynamic_vertex_buffer (false),
  m_dynamic_index_buffer  (false)
{
  SetVertexBufferDynamic(false);
  SetIndexBufferDynamic(false);

  m_pvertex_type = new CustomVertexType("UnAssigned");
  SafeRef(m_pvertex_type);

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

  SafeUnRef(m_pvertex_type);

  REF_COUNT_DTOR(IndexedMesh);
} // ~IndexedMesh


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
void IndexedMesh::Render(uint pass)
{
  // If we have nothing to draw, just return
  if (m_num_faces == 0 || m_num_verts == 0)
    return;

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

      D3DCheck(ApplicationCentral.GetDevice()->SetStreamSource(0, 0, 0, 0));
      D3DCheck(ApplicationCentral.GetDevice()->CreateVertexBuffer(m_num_verts_alloc * m_pvertex_type->GetSize(), usage, 
        NULL, D3DPOOL_DEFAULT, &m_pvertex_buffer, 0));

      m_rebuild_vertex_array = false;
    } // if
    
    // See if we need to write data into the vertex buffer
    if (m_vertex_dirty)
    {
      void *pvertex_ptr;
      D3DCheck(ApplicationCentral.GetDevice()->SetStreamSource(0, 0, 0, 0));

      if (m_dynamic_vertex_buffer)
      {
        D3DCheck((m_pvertex_buffer->Lock(0, 0, (void**) &pvertex_ptr, D3DLOCK_NOSYSLOCK | D3DLOCK_DISCARD)));
      } // if
      else
      {
        D3DCheck((m_pvertex_buffer->Lock(0, 0, (void**) &pvertex_ptr, D3DLOCK_NOSYSLOCK)));
      } // else

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

      D3DCheck(ApplicationCentral.GetDevice()->SetIndices(0));
      D3DCheck(ApplicationCentral.GetDevice()->CreateIndexBuffer(m_num_faces_alloc * sizeof(IndexedMesh::Face), usage, 
        D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pindex_buffer, 0));

      m_rebuild_index_array = false;
    } // if
    
    // See if we need to write data into the index buffer
    if (m_index_dirty)
    {
      void *pindex_ptr;
      D3DCheck(ApplicationCentral.GetDevice()->SetIndices(0));

      if (m_dynamic_index_buffer)
      {
        D3DCheck(m_pindex_buffer->Lock(0, 0, (void**) &pindex_ptr, D3DLOCK_NOSYSLOCK | D3DLOCK_DISCARD));
      } // if
      else
      {
        D3DCheck(m_pindex_buffer->Lock(0, 0, (void**) &pindex_ptr, D3DLOCK_NOSYSLOCK));
      } // else

      memcpy(pindex_ptr, m_pindex_data, m_num_faces * sizeof(IndexedMesh::Face));
      D3DCheck(m_pindex_buffer->Unlock());

      m_index_dirty = false;
    } // if

    // Draw the geometry
    ApplicationCentral.GetDevice()->SetVertexDeclaration(m_pvertex_type->GetVertexDeclaration());
    ApplicationCentral.GetDevice()->SetIndices(m_pindex_buffer);
    ApplicationCentral.GetDevice()->SetStreamSource(0, m_pvertex_buffer, 0, m_pvertex_type->GetSize());
  } // if

  // Add stats on this render
  // DisplayStats.AddDraw(m_num_faces, 1, (!(m_dynamic_index_buffer || m_dynamic_vertex_buffer)));

  // Render
  ApplicationCentral.GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_num_verts, 0, m_num_faces);
} // Render


// ----------------------------------------------------------------------------
// Render the mesh subset
// ----------------------------------------------------------------------------
void IndexedMesh::RenderSubset(uint subset, uint pass)
{
  // If we have nothing to draw, just return
  if (m_num_faces == 0 || m_num_verts == 0)
    return;

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

      D3DCheck(ApplicationCentral.GetDevice()->SetStreamSource(0, 0, 0, 0));
      D3DCheck(ApplicationCentral.GetDevice()->CreateVertexBuffer(m_num_verts_alloc * m_pvertex_type->GetSize(), usage, 
        NULL, D3DPOOL_DEFAULT, &m_pvertex_buffer, 0));

      m_rebuild_vertex_array = false;
    } // if
    
    // See if we need to write data into the vertex buffer
    if (m_vertex_dirty)
    {
      void *pvertex_ptr;
      D3DCheck(ApplicationCentral.GetDevice()->SetStreamSource(0, 0, 0, 0));

      if (m_dynamic_vertex_buffer)
      {
        D3DCheck((m_pvertex_buffer->Lock(0, 0, (void**) &pvertex_ptr, D3DLOCK_NOSYSLOCK | D3DLOCK_DISCARD)));
      } // if
      else
      {
        D3DCheck((m_pvertex_buffer->Lock(0, 0, (void**) &pvertex_ptr, D3DLOCK_NOSYSLOCK)));
      } // else

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

      D3DCheck(ApplicationCentral.GetDevice()->SetIndices(0));
      D3DCheck(ApplicationCentral.GetDevice()->CreateIndexBuffer(m_num_faces_alloc * sizeof(IndexedMesh::Face), usage, 
        D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pindex_buffer, 0));

      m_rebuild_index_array = false;
    } // if
    
    // See if we need to write data into the index buffer
    if (m_index_dirty)
    {
      void *pindex_ptr;
      D3DCheck(ApplicationCentral.GetDevice()->SetIndices(0));

      if (m_dynamic_index_buffer)
      {
        D3DCheck(m_pindex_buffer->Lock(0, 0, (void**) &pindex_ptr, D3DLOCK_NOSYSLOCK | D3DLOCK_DISCARD));
      } // if
      else
      {
        D3DCheck(m_pindex_buffer->Lock(0, 0, (void**) &pindex_ptr, D3DLOCK_NOSYSLOCK));
      } // else

      memcpy(pindex_ptr, m_pindex_data, m_num_faces * sizeof(IndexedMesh::Face));
      D3DCheck(m_pindex_buffer->Unlock());

      m_index_dirty = false;
    } // if

    // Draw the geometry
    ApplicationCentral.GetDevice()->SetVertexDeclaration(m_pvertex_type->GetVertexDeclaration());
    ApplicationCentral.GetDevice()->SetIndices(m_pindex_buffer);
    ApplicationCentral.GetDevice()->SetStreamSource(0, m_pvertex_buffer, 0, m_pvertex_type->GetSize());
  } // if

  // Add stats on this render
  // DisplayStats.AddDraw(m_num_faces, 1, (!(m_dynamic_index_buffer || m_dynamic_vertex_buffer)));

  // Render the Subset
  MeshSubset *pSubset = m_SubsetArray[subset];
  ApplicationCentral.GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_num_verts, pSubset->GetFaceStart() * 3, pSubset->GetFaceCount());
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

  // Remove the vertex type
  SafeUnRef(m_pvertex_type);

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
  
  // Build the vertex type
  if (!BuildVertexType(header.VertexTypeName, header.Declaration))
  {
    MeshLog("Failed to build the vertex type");
    MeshLog("--------------------------------------------------");
    return false;
  } // if

  // Check the vertex type is the same as in the file
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
    pSubset->GetColorMaterial() = subsetHeader.ColorMaterial;

    // Get the texture DB
    FileDatabase *pTextureDB = FileSystem("Texture");
    if (!pTextureDB)
      return false;

    // Set the diffuse texture
    if (subsetHeader.DiffuseTexture)
    {
      MeshLog("[%d] Loading the diffuse texture: %s", (int) i, subsetHeader.DiffuseTexture.Get());

      FileHandle handle = pTextureDB->MakeFileHandle(subsetHeader.DiffuseTexture);

      Texture *pTex = TextureLoader::LoadTexture(handle);
      if (!pTex)
      {
        MeshLog("[%d] Failed to load the diffuse texture: %s", (int) i, subsetHeader.DiffuseTexture.Get());
        MeshLog("--------------------------------------------------");
        return false;
      } // if

      pSubset->GetTextureArray().SetDiffuse(pTex);
    } // if
    else
    {
      MeshLog("[%d] No diffuse texture was found", (int) i);
    } // else

    // Set the alpha texture
    if (subsetHeader.AlphaTexture)
    {
      MeshLog("[%d] Loading the alpha texture: %s", (int) i, subsetHeader.AlphaTexture.Get());

      FileHandle handle = pTextureDB->MakeFileHandle(subsetHeader.AlphaTexture);

      Texture *pTex = TextureLoader::LoadTexture(handle);
      if (!pTex)
      {
        MeshLog("[%d] Failed to load the alpha texture: %s", (int) i, subsetHeader.AlphaTexture.Get());
        MeshLog("--------------------------------------------------");
        return false;
      } // if

      pSubset->GetTextureArray().SetAlpha(pTex);
    } // if
    else
    {
      MeshLog("[%d] No alpha texture was found", (int) i);
    } // else

    // Set the normal texture
    if (subsetHeader.NormalTexture)
    {
      MeshLog("[%d] Loading the normal texture: %s", (int) i, subsetHeader.NormalTexture.Get());

      FileHandle handle = pTextureDB->MakeFileHandle(subsetHeader.NormalTexture);

      Texture *pTex = TextureLoader::LoadTexture(handle);
      if (!pTex)
      {
        MeshLog("[%d] Failed to load the normal texture: %s", (int) i, subsetHeader.NormalTexture.Get());
        MeshLog("--------------------------------------------------");
        return false;
      } // if

      pSubset->GetTextureArray().SetNormal(pTex);
    } // if
    else
    {
      MeshLog("[%d] No normal texture was found", (int) i);
    } // else

    // Set the texture 0
    if (subsetHeader.Tex0)
    {
      MeshLog("[%d] Loading the texture 0: %s", (int) i, subsetHeader.Tex0.Get());

      FileHandle handle = pTextureDB->MakeFileHandle(subsetHeader.Tex0);

      Texture *pTex = TextureLoader::LoadTexture(handle);
      if (!pTex)
      {
        MeshLog("[%d] Failed to load the texture 0: %s", (int) i, subsetHeader.Tex0.Get());
        MeshLog("--------------------------------------------------");
        return false;
      } // if

      pSubset->GetTextureArray().SetTex0(pTex);
    } // if
    else
    {
      MeshLog("[%d] No texture 0 was found", (int) i);
    } // else

    // Set the texture 1
    if (subsetHeader.Tex1)
    {
      MeshLog("[%d] Loading the texture 1: %s", (int) i, subsetHeader.Tex1.Get());

      FileHandle handle = pTextureDB->MakeFileHandle(subsetHeader.Tex1);

      Texture *pTex = TextureLoader::LoadTexture(handle);
      if (!pTex)
      {
        MeshLog("[%d] Failed to load the texture 1: %s", (int) i, subsetHeader.Tex1.Get());
        MeshLog("--------------------------------------------------");
        return false;
      } // if

      pSubset->GetTextureArray().SetTex1(pTex);
    } // if
    else
    {
      MeshLog("[%d] No texture 1 was found", (int) i);
    } // else

    // Assign the effect if it exists
    if (subsetHeader.EffectFilename)
    {
      MeshLog("[%d] Loading the effect: %s", (int) i, subsetHeader.EffectFilename.Get());

      // Get the file handle
      FileDatabase *pMaterialDB = FileSystem("Material");
      if (!pMaterialDB)
        return false;

      FileHandle handle = pMaterialDB->MakeFileHandle(subsetHeader.EffectFilename);

      Material *pMat = MaterialLoader::LoadEffect(handle);
      if (!pMat)
      {
        MeshLog("[%d] Failed to load the effect: %s", (int) i, subsetHeader.EffectFilename.Get());
        MeshLog("--------------------------------------------------");
        return false;
      } // if

      pSubset->SetMaterial(pMat);
    } // if
    else
    {
      MeshLog("[%d] Invalid mesh, no Effect found", (int) i);
      MeshLog("--------------------------------------------------");
      return false;
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


// --------------------------------------------------------------------------
// Save the mesh to the given file
// --------------------------------------------------------------------------
bool IndexedMesh::Save(FILE *pFile)
{
  // Ensure we have some data to write
  if (m_num_verts == 0 || m_num_faces == 0)
    return false;

  // Create the header
  IndexedMesh::FileHeader header;

  // Get the vertex declaration
  LPDIRECT3DVERTEXDECLARATION9 pVertexDecl = m_pvertex_type->GetVertexDeclaration();
  pVertexDecl->GetDeclaration(header.Declaration, &header.NumDeclaration);

  // Set the common header attributes
  header.Name                 = m_name;
  header.MeshSubsetCount      = m_SubsetArray.size();
  header.VertexTypeName       = m_pvertex_type->GetName();
  header.NumVerts             = m_num_verts;
  header.NumFaces             = m_num_faces;
  header.DynamicVertexBuffer  = m_dynamic_vertex_buffer;
  header.DynamicIndexBuffer   = m_dynamic_index_buffer;
  header.VertexSize           = m_pvertex_type->GetSize();

  // Write the header to the file
  if (fwrite(&header, sizeof(IndexedMesh::FileHeader), 1, pFile) != 1)
    return false;

  // Write the vertex data to the file
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
    if (texArray.GetDiffuse())
      subsetHeader.DiffuseTexture   = texArray.GetDiffuse()->GetFileHandle().GetFilename();
    if (texArray.GetNormal())
      subsetHeader.NormalTexture    = texArray.GetNormal()->GetFileHandle().GetFilename();
    if (texArray.GetAlpha())
      subsetHeader.AlphaTexture     = texArray.GetAlpha()->GetFileHandle().GetFilename();
    if (texArray.GetTex0())
      subsetHeader.Tex0             = texArray.GetTex0()->GetFileHandle().GetFilename();
    if (texArray.GetTex1())
      subsetHeader.Tex1             = texArray.GetTex1()->GetFileHandle().GetFilename();

    // Set the effect filename
    if (pSubset->GetMaterial())
      subsetHeader.EffectFilename   = pSubset->GetMaterial()->GetFileHandle().GetFilename();

    // Write the subset to the file
    if (fwrite(&subsetHeader, sizeof(MeshSubset::FileHeader), 1, pFile) != 1)
      return false;
  } // for

  return true;
} // Save


// --------------------------------------------------------------------------
// Import the mesh from the X file
// --------------------------------------------------------------------------
bool IndexedMesh::ImportFromX(const String &filename)
{
  // The required variables
  LPDIRECT3DDEVICE9 device      = ApplicationCentral.GetDevice();
  LPD3DXMESH mesh               = NULL;
  LPD3DXBUFFER adjacent_buffer  = NULL;
  LPD3DXBUFFER material_buffer  = NULL;
  LPD3DXBUFFER effect_buffer    = NULL;
  ulong options                 = D3DXMESH_SYSTEMMEM;
  ulong attributes              = 0;
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
    device, 
    &adjacent_buffer, 
    &material_buffer, 
    &effect_buffer, 
    &attributes, 
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
  D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
  if (FAILED(mesh->GetDeclaration(decl)))
  {
    MeshLog("Failed to get the vertex declaration");
    MeshLog("--------------------------------------------------");
    return false;
  } // if

  // Build the vertex type
  if (!BuildVertexType("", decl))
  {
    MeshLog("Failed to build the vertex type");
    MeshLog("--------------------------------------------------");
    return false;
  } // if

  // Extract the data from the mesh
  uint vertex_size = mesh->GetNumBytesPerVertex();
  uint num_verts   = mesh->GetNumVertices();
  uint num_faces   = mesh->GetNumFaces();
  uint face_size   = sizeof(ushort) * 3;

  MeshLog("The vertex size is: %d", (int) vertex_size);
  MeshLog("The number of verts are: %d", (int) num_verts);
  MeshLog("The number of faces are: %d", (int) num_faces);

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
  mesh->GenerateAdjacency(EPSILON, pAdjacency);
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

  if (attributeCount != attributes)
  {
    MeshLog("The attribute tables are out of sync");
    MeshLog("--------------------------------------------------");
    return false;
  } // if

  // Get the attribute table
  D3DXATTRIBUTERANGE *pAttributeTable = new D3DXATTRIBUTERANGE[attributeCount];
  mesh->GetAttributeTable(pAttributeTable, &attributeCount);

  MeshLog("The number of attributes is: %d", (int) attributeCount);

  // Add all materials to the subset array
  for (uint i = 0; i < attributes; i++)
  {
    MeshLog("[%d] Loading the subset", (int) i);

    // Get the material and the effect
    D3DXMATERIAL &d3dmat = pmaterials[i];
    D3DXEFFECTINSTANCE &d3deffect = peffects[i];

    // Create the subset
    MeshSubset *pSubset = this->AddSubset();

    // Set the color material
    pSubset->GetColorMaterial() = d3dmat.MatD3D;

    // Set the diffuse texture
    if (d3dmat.pTextureFilename)
    {
      MeshLog("[%d] Loading the diffuse texture: %s", (int) i, d3dmat.pTextureFilename);

      // Get the file handle
      FileDatabase *pTextureDB = FileSystem("Texture");
      if (!pTextureDB)
        return false;

      FileHandle textureHandle = pTextureDB->MakeFileHandle(d3dmat.pTextureFilename);

      // Load the texture
      Texture *pTex = TextureLoader::LoadTexture(textureHandle);
      if (!pTex)
      {
        MeshLog("[%d] Failed to load the diffuse texture: %s", (int) i, d3dmat.pTextureFilename);
        MeshLog("--------------------------------------------------");
        return false;
      } // if

      pSubset->GetTextureArray().SetDiffuse(pTex);
    } // if
    else
    {
      MeshLog("[%d] No texture was found", (int) i);
    } // else

    // Assign the effect if it exists
    if (d3deffect.pEffectFilename)
    {
      MeshLog("[%d] Loading the effect: %s", (int) i, d3deffect.pEffectFilename);

      // Get the file handle
      FileDatabase *pMaterialDB = FileSystem("Material");
      if (!pMaterialDB)
        return false;

      FileHandle materialHandle = pMaterialDB->MakeFileHandle(d3deffect.pEffectFilename);

      // Load the material
      Material *pMat = MaterialLoader::LoadEffect(materialHandle);
      if (!pMat)
      {
        MeshLog("[%d] Failed to load the effect: %s", (int) i, d3deffect.pEffectFilename);
        MeshLog("--------------------------------------------------");
        return false;
      } // if

      pSubset->SetMaterial(pMat);
    } // if
    else
    {
      const char *pEffectFilename = "tex.fx";

      // Get the file handle
      FileDatabase *pMaterialDB = FileSystem("Material");
      if (!pMaterialDB)
        return false;

      FileHandle materialHandle = pMaterialDB->MakeFileHandle(pEffectFilename);

      // Load the material
      MeshLog("[%d] Loading the effect: %s", (int) i, pEffectFilename);
      Material *pMat = MaterialLoader::LoadEffect(materialHandle);

      if (!pMat)
      {
        MeshLog("[%d] Failed to load the effect: %s", (int) i, pEffectFilename);
        MeshLog("--------------------------------------------------");
        return false;
      } // if

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


// ----------------------------------------------------------------------------
// Build the vertex type based on the declaration given
// ----------------------------------------------------------------------------
bool IndexedMesh::BuildVertexType(const String &name, D3DVERTEXELEMENT9 *pDeclaration)
{
  // Release the old vertex type
  SafeUnRef(m_pvertex_type);

  // Create our vertex type
  CustomVertexType *pVertexType = new CustomVertexType(name.c_str());

  // Store and reference the new vertex type
  m_pvertex_type = pVertexType;
  SafeRef(m_pvertex_type);

  // Add the data to the vertex type
  bool declEnd = false;
  for (uint i = 0; i < MAX_FVF_DECL_SIZE && !declEnd; i++)
  {
    // Get the decl item
    D3DVERTEXELEMENT9 &declItem = pDeclaration[i];

    // Check for the end of the declaration
    if (declItem.Stream == 0xFF)
    {
      MeshLog("Found the end of the vertex declaration");
      declEnd = true;
      break;
    } // if

    bool declOk = true;
    switch (declItem.Usage)
    {
      case D3DDECLUSAGE_POSITION:
      {
        MeshLog("Found position information in the vertex declaration");
        if (declItem.UsageIndex == 0)
          pVertexType->AddItem(VI_Position, declItem);
        else if (declItem.UsageIndex == 1)
          pVertexType->AddItem(VI_Position2, declItem);
        else
          declOk = false;
        break;
      } // D3DDECLUSAGE_POSITION

      case D3DDECLUSAGE_TEXCOORD:
      {
        MeshLog("Found tex coord information in the vertex declaration");
        if (declItem.UsageIndex == 0)
          pVertexType->AddItem(VI_Texture, declItem);
        else if (declItem.UsageIndex == 1)
          pVertexType->AddItem(VI_Texture2, declItem);
        else
          declOk = false;
        break;
      } // D3DDECLUSAGE_TEXCOORD

      case D3DDECLUSAGE_NORMAL:
      {
        MeshLog("Found normal information in the vertex declaration");
        if (declItem.UsageIndex == 0)
          pVertexType->AddItem(VI_Normal, declItem);
        else if (declItem.UsageIndex == 1)
          pVertexType->AddItem(VI_Normal2, declItem);
        else
          declOk = false;
        break;
      } // D3DDECLUSAGE_NORMAL

      case D3DDECLUSAGE_COLOR:
      {
        MeshLog("Found color information in the vertex declaration");
        if (declItem.UsageIndex == 0)
          pVertexType->AddItem(VI_Color, declItem);
        else if (declItem.UsageIndex == 1)
          pVertexType->AddItem(VI_Color2, declItem);
        else
          declOk = false;
        break;
      } // D3DDECLUSAGE_COLOR
    } // switch

    // Make sure the declaration is ok
    if (!declOk)
    {
      return false;
      MeshLog("Unsupported vertex items found in the declaration");
      MeshLog("--------------------------------------------------");
    } // if
  } // for

  MeshLog("Successfully created the vertex type");
  return true;
} // BuildVertexType


// -- EOF