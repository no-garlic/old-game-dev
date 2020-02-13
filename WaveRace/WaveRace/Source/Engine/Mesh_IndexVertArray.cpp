// ----------------------------------------------------------------------------
// File: Mesh_IndexVertArray.cpp
// Desc: Mesh that uses an index array and vertex array
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes for the indexed vertex array mesh
// ----------------------------------------------------------------------------
#include "Engine/Mesh_IndexVertArray.h"


// ----------------------------------------------------------------------------
// Type for the D3D flexible Vertex format
// ----------------------------------------------------------------------------
#define FVF_TYPE (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)


// ----------------------------------------------------------------------------
// Name: Mesh_IndexVertArray::Mesh_IndexVertArray
// Desc: Constructor for the indexed vertex array mesh
// Parm: const char *name          - the name of the mesh
// Parm: LPDIRECT3DDEVICE9 device  - the device to use to allocate the index and
//       vertex buffers from
// Parm: const VertexVec &verts    - the array of verticies
// Parm: const FaceVec &faces      - the array of faces
// ----------------------------------------------------------------------------
Mesh_IndexVertArray::Mesh_IndexVertArray(const char *name, LPDIRECT3DDEVICE9 device, 
                                         const VertexVec &verts, const FaceVec &faces,
                                         bool dynamic) : Mesh(name, device)
{
    m_pd3d_index_buffer     = 0;
    m_pd3d_vertex_buffer    = 0;
    m_vertex_read_array     = 0;
    m_face_read_array       = 0;
    m_dirty                 = true;
    m_dynamic               = dynamic;
    m_num_faces             = faces.size();
    m_num_verts             = verts.size();
    m_draw_verts            = m_num_verts;
    m_draw_faces            = m_num_faces;

    // TODO: Fix this
    m_dynamic               = true;

    BuildD3DBuffers(verts, faces);

    // We treat this as static for now.  It would not be
    // to difficult to store a copy of this data when the 
    // mesh is modified and access the triangles by pointer.
    uint num_triangles = faces.size();
    m_triangles.resize(num_triangles);
    for (uint i = 0; i < num_triangles; i++)
    {
        m_triangles[i].p0 = verts[ faces[i].v[0] ].loc;
        m_triangles[i].p1 = verts[ faces[i].v[1] ].loc;
        m_triangles[i].p2 = verts[ faces[i].v[2] ].loc;
    } // for
} // Mesh_IndexVertArray


// ----------------------------------------------------------------------------
// Name: Mesh_IndexVertArray::~Mesh_IndexVertArray
// Desc: Destructor
// ----------------------------------------------------------------------------
Mesh_IndexVertArray::~Mesh_IndexVertArray()
{
    Memory::SafeRelease(m_pd3d_index_buffer);
    Memory::SafeRelease(m_pd3d_vertex_buffer);
} // ~Mesh_IndexVertArray


// ----------------------------------------------------------------------------
// Name: Mesh_IndexVertArray::BuildD3DBuffers
// Desc: Build the D3D index and vertex buffers from the vertex and face 
//       vectors
// ----------------------------------------------------------------------------
void Mesh_IndexVertArray::BuildD3DBuffers(const VertexVec &verts, const FaceVec &faces)
{
    // Ensure we have verticies and faces
    if (verts.empty() || faces.empty())
        return;

    // Create the vertex buffer
    m_pdevice->CreateVertexBuffer(
        verts.size() * sizeof(Vertex), 
        (m_dynamic) ? (D3DUSAGE_DYNAMIC) : (0), 
        FVF_TYPE, 
        D3DPOOL_DEFAULT, 
        &m_pd3d_vertex_buffer, 
        0);

    // Create the index buffer
    m_pdevice->CreateIndexBuffer(
        faces.size() * sizeof(Face), 
        (m_dynamic) ? (D3DUSAGE_DYNAMIC) : (0), 
        D3DFMT_INDEX32,
        D3DPOOL_DEFAULT, 
        &m_pd3d_index_buffer, 
        0);

    // Ensure we succesfully created a vertex and index buffer
    if (!m_pd3d_vertex_buffer || !m_pd3d_index_buffer)
        return;

    // Store a read only copy of the verticies in system memory
    m_vertex_read_array = (Vertex *) malloc(sizeof(Vertex) * verts.size());
    for (size_t i = 0; i < verts.size(); i++)
        m_vertex_read_array[i] = verts[i];

    // Fill the vertex buffer
    void *pvertex_ptr;
    m_pd3d_vertex_buffer->Lock(0, 0, (void**) &pvertex_ptr, D3DLOCK_DISCARD);
    memcpy(pvertex_ptr, m_vertex_read_array, m_num_verts * sizeof(Vertex));
    m_pd3d_vertex_buffer->Unlock();

    // Store a read only copy of the indicies in system memory
    m_face_read_array = (Face *) malloc(sizeof(Face) * faces.size());
    for (size_t i = 0; i < faces.size(); i++)
        m_face_read_array[i] = faces[i];

    // Fill the index buffer
    void *pindex_ptr;
    m_pd3d_index_buffer->Lock(0, 0, (void**) &pindex_ptr, D3DLOCK_DISCARD);
    memcpy(pindex_ptr, m_face_read_array, m_num_faces * sizeof(Face));
    m_pd3d_index_buffer->Unlock();

    RecalculateBounds();
} // BuildD3DBuffers


// ----------------------------------------------------------------------------
// Name: Mesh_IndexVertArray::Draw
// Desc: Draw the mesh at the current view matrix
// ----------------------------------------------------------------------------
void Mesh_IndexVertArray::Draw()
{
    // Set the vertex type, the indicies, and the verticies.
    m_pdevice->SetFVF(FVF_TYPE);
    m_pdevice->SetIndices(m_pd3d_index_buffer);
    m_pdevice->SetStreamSource(0, m_pd3d_vertex_buffer, 0, sizeof(Vertex));
    m_pdevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_draw_verts, 0, m_draw_faces);
} // Draw


// ----------------------------------------------------------------------------
// Name: Mesh_IndexVertArray::LockVertexBuffer
// Desc: Lock the vertex buffer for writing
// Parm: Mesh_IndexVertArray::Vertex **verts - returns an array of verticies
// Parm: DWORD flags                         - the flags
// Retn: bool                                - true if the vertex read was 
//       successful
// ----------------------------------------------------------------------------
bool Mesh_IndexVertArray::LockVertexBuffer(Mesh_IndexVertArray::Vertex **verts, DWORD flags)
{
    if (!m_dynamic)
    {
        verts = 0;
        return false;
    } // if

    return (SUCCEEDED(m_pd3d_vertex_buffer->Lock(0, 0, (void**) verts, flags)));
} // LockVertexBuffer


// ----------------------------------------------------------------------------
// Name: Mesh_IndexVertArray::LockVertexBuffer
// Desc: Lock the vertex buffer for writing
// Parm: uint offset                         - the start offset into the buffer
// Parm: uint size                           - the size of the buffer
// Parm: Mesh_IndexVertArray::Vertex **verts - returns an array of verticies
// Parm: DWORD flags                         - the flags
// Retn: bool                                - true if the vertex read was 
//       successful
// ----------------------------------------------------------------------------
bool Mesh_IndexVertArray::LockVertexBuffer(uint offset, uint size, Mesh_IndexVertArray::Vertex **verts, DWORD flags)
{
    if (!m_dynamic)
    {
        verts = 0;
        return false;
    } // if

    return (SUCCEEDED(m_pd3d_vertex_buffer->Lock(offset, size, (void**) verts, flags)));
} // LockVertexBuffer


// ----------------------------------------------------------------------------
// Name: Mesh_IndexVertArray::LockIndexBuffer
// Desc: Locks the index buffer for writing
// Parm: Mesh_IndexVertArray::Face **faces - returns an array of faces
// Parm: DWORD flags                       - the flags
// Retn: bool                              - true if the index read was 
//       successful
// ----------------------------------------------------------------------------
bool Mesh_IndexVertArray::LockIndexBuffer(Mesh_IndexVertArray::Face **faces, DWORD flags)
{
    if (!m_dynamic)
    {
        faces = 0;
        return false;
    } // if

    return (SUCCEEDED(m_pd3d_index_buffer->Lock(0, 0, (void**) faces, flags)));
} // LockIndexBuffer


// ----------------------------------------------------------------------------
// Name: Mesh_IndexVertArray::LockIndexBuffer
// Desc: Locks the index buffer for writing
// Parm: uint offset                         - the start offset into the buffer
// Parm: uint size                           - the size of the buffer
// Parm: Mesh_IndexVertArray::Face **faces - returns an array of faces
// Parm: DWORD flags                       - the flags
// Retn: bool                              - true if the index read was 
//       successful
// ----------------------------------------------------------------------------
bool Mesh_IndexVertArray::LockIndexBuffer(uint offset, uint size, Mesh_IndexVertArray::Face **faces, DWORD flags)
{
    if (!m_dynamic)
    {
        faces = 0;
        return false;
    } // if

    return (SUCCEEDED(m_pd3d_index_buffer->Lock(offset, size, (void**) faces, flags)));
} // LockIndexBuffer


// ----------------------------------------------------------------------------
// Name: Mesh_IndexVertArray::UnlockIndexBuffer
// Desc: Unlocks the vertex buffer and performs the write
// Parm: bool update_bounds - if true, the bounding sphere and box will be 
//       recalculated.
// Retn: bool               - true if successful
// ----------------------------------------------------------------------------
bool Mesh_IndexVertArray::UnlockIndexBuffer(bool update_bounds)
{
    bool ok = SUCCEEDED(m_pd3d_index_buffer->Unlock());

    if (ok && update_bounds)
        m_dirty = true;

    return ok;
} // UnlockIndexBuffer


// ----------------------------------------------------------------------------
// Name: Mesh_IndexVertArray::UnlockVertexBuffer
// Desc: Unlocks the index buffer and performs the write
// Parm: bool update_bounds - if true, the bounding sphere and box will be 
//       recalculated.
// Retn: bool               - true if successful
// ----------------------------------------------------------------------------
bool Mesh_IndexVertArray::UnlockVertexBuffer(bool update_bounds)
{
    bool ok = SUCCEEDED(m_pd3d_vertex_buffer->Unlock());

    if (ok && update_bounds)
        m_dirty = true;

    return ok;
} // UnlockVertexBuffer


// ----------------------------------------------------------------------------
// Name: Mesh_IndexVertArray::RecalculateBounds
// Desc: Recalculate the bounding sphere and box for the mesh
// ----------------------------------------------------------------------------
void Mesh_IndexVertArray::RecalculateBounds()
{
    // Get the vertex data (read only)
    Vertex *vertex_array = 0;
    if (FAILED(m_pd3d_vertex_buffer->Lock(0, 0, (void**) &vertex_array, D3DLOCK_READONLY)))
        return;

    // Recalculate the aabb
    for (size_t i = 0; i < m_num_verts; i++)
    {
        if (i == 0)
        {
            m_box.Min[0]  = vertex_array[i].loc[0];
            m_box.Min[1]  = vertex_array[i].loc[1];
            m_box.Min[2]  = vertex_array[i].loc[2];
            m_box.Max[0]  = vertex_array[i].loc[0];
            m_box.Max[1]  = vertex_array[i].loc[1];
            m_box.Max[2]  = vertex_array[i].loc[2];
        } // if
        else
        {
            m_box.Min[0]  = min(m_box.Min[0], vertex_array[i].loc[0]);
            m_box.Min[1]  = min(m_box.Min[1], vertex_array[i].loc[1]);
            m_box.Min[2]  = min(m_box.Min[2], vertex_array[i].loc[2]);
            m_box.Max[0]  = max(m_box.Max[0], vertex_array[i].loc[0]);
            m_box.Max[1]  = max(m_box.Max[1], vertex_array[i].loc[1]);
            m_box.Max[2]  = max(m_box.Max[2], vertex_array[i].loc[2]);
        } // else
    } // for

    // The first guess radius of the sphere is half of the diagonal
    Vec3 diagonal     = m_box.Max - m_box.Min;
    m_sphere.radius   = diagonal.Length() / 2.0f;

    // The center point of the spehre is in the center of the box
    m_sphere.center   = m_box.Min + (diagonal / 2.0f);

    // Get a more accurate radius by measuring to each vertex from the 
    // known cerner point
    m_sphere.radius = 0.0f;
    for (size_t i = 0; i < m_num_verts; i++)
    {
        Vec3 vec        = vertex_array[i].loc - m_sphere.center;
        m_sphere.radius = max(m_sphere.radius, vec.LengthSq());
    } // for
    m_sphere.radius = sqrtf(m_sphere.radius);

    // Close the vertex data
    m_pd3d_vertex_buffer->Unlock();

    m_dirty = false;
} // RecalculateBounds


// ----------------------------------------------------------------------------
// Name: Mesh_IndexVertArray::GetBounds
// Desc: Get an axis aligned bounding box containing the extents of the mesh. 
//       Note - this is recalculated each time.
// Parm: Box &box - the box to set the extents of
// ----------------------------------------------------------------------------
void Mesh_IndexVertArray::GetBounds(Box &box)
{
    if (m_dirty)
        RecalculateBounds();

    box = m_box;
} // GetBounds


// ----------------------------------------------------------------------------
// Name: Mesh_IndexVertArray::GetBounds
// Desc: Get a bounding sphere containing the extents of the mesh. Note - this 
//       is recalculated each time.
// Parm: Sphere &sphere - the sphere to set the extents of
// ----------------------------------------------------------------------------
void Mesh_IndexVertArray::GetBounds(Sphere &sphere)
{
    if (m_dirty)
        RecalculateBounds();

    sphere = m_sphere;
} // GetBounds


// -- EOF

