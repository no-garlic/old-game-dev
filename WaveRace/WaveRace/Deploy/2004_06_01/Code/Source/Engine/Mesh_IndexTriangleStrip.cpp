// ----------------------------------------------------------------------------
// File: Mesh_IndexTriangleStrip.cpp
// Desc: Mesh that uses an index array and vertex array
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes for the indexed vertex array mesh
// ----------------------------------------------------------------------------
#include "Engine/Mesh_IndexTriangleStrip.h"

#include "Common\Logging.h"
#include <exception>

// ----------------------------------------------------------------------------
// Type for the D3D flexible Vertex format
// ----------------------------------------------------------------------------
#define FVF_TYPE (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_TEX2)


// ----------------------------------------------------------------------------
// Name: Mesh_IndexTriangleStrip::Mesh_IndexTriangleStrip
// Desc: Constructor for the indexed vertex array mesh
// Parm: const char *name          - the name of the mesh
// Parm: LPDIRECT3DDEVICE9 device  - the device to use to allocate the index and
//       vertex buffers from
// Parm: const VertexVec &verts    - the array of verticies
// Parm: const FaceVec &faces      - the array of faces
// ----------------------------------------------------------------------------
Mesh_IndexTriangleStrip::Mesh_IndexTriangleStrip(const char *name, LPDIRECT3DDEVICE9 device, 
                                         const VertexVec &verts, const IndexVecVec &indicies, 
                                         bool dynamic) : Mesh(name, device)
{
    m_pd3d_vertex_buffer    = 0;
    m_vertex_read_array     = 0;
    m_dirty                 = true;
    m_dynamic               = dynamic;
    m_num_verts             = verts.size();

    BuildD3DBuffers(verts, indicies);
} // Mesh_IndexTriangleStrip


// ----------------------------------------------------------------------------
// Name: Mesh_IndexTriangleStrip::~Mesh_IndexTriangleStrip
// Desc: Destructor
// ----------------------------------------------------------------------------
Mesh_IndexTriangleStrip::~Mesh_IndexTriangleStrip()
{
    for (size_t i = 0; i < m_d3d_index_buffers.size(); i++)
        Memory::SafeRelease(m_d3d_index_buffers[i]);

    m_d3d_index_buffers.clear();    
    m_d3d_index_buffer_size.clear();

    Memory::SafeRelease(m_pd3d_vertex_buffer);
} // ~Mesh_IndexTriangleStrip


// ----------------------------------------------------------------------------
// Name: Mesh_IndexTriangleStrip::BuildD3DBuffers
// Desc: Build the D3D index and vertex buffers from the vertex and face 
//       vectors
// ----------------------------------------------------------------------------
void Mesh_IndexTriangleStrip::BuildD3DBuffers(const VertexVec &verts, const IndexVecVec &indicies)
{
    // Ensure we have verticies and faces
    if (verts.empty() || indicies.empty())
        return;

    // Create the vertex buffer
    m_pdevice->CreateVertexBuffer(
        verts.size() * sizeof(Vertex), 
        (m_dynamic) ? (D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY) : (0), 
        FVF_TYPE, 
        D3DPOOL_DEFAULT, 
        &m_pd3d_vertex_buffer, 
        0);

    // Ensure we succesfully created a vertex buffer
    if (!m_pd3d_vertex_buffer)
        return;

    // Create the index buffers
    for (size_t i = 0; i < indicies.size(); i++)
    {
        const IndexVec &index_vec = indicies[i];
        if (index_vec.empty())
            continue;

        // Create the index buffer
        IDirect3DIndexBuffer9 *pindex_buffer;
        m_pdevice->CreateIndexBuffer(
            index_vec.size() * sizeof(Index),
            0,
            D3DFMT_INDEX32,
            D3DPOOL_DEFAULT,
            &pindex_buffer,
            0);

        // Create a copy of the index data in system, memory
        Index *index_source = (Index *) malloc(sizeof(Index) * index_vec.size());
        for (size_t i = 0; i < index_vec.size(); i++)
            index_source[i] = index_vec[i];

        // Fill the index buffer
        void *pindex_ptr;
        pindex_buffer->Lock(0, 0, (void**) &pindex_ptr, D3DLOCK_DISCARD);
        memcpy(pindex_ptr, index_source, index_vec.size() * sizeof(Index));
        pindex_buffer->Unlock();

        // Free the copied data
        free(index_source);

        // Store the index buffer
        m_d3d_index_buffers.push_back(pindex_buffer);
        m_d3d_index_buffer_size.push_back(index_vec.size());
    } // for

    // Store a read only copy of the verticies in system memory
    m_vertex_read_array = (Vertex *) malloc(sizeof(Vertex) * verts.size());
    for (size_t i = 0; i < verts.size(); i++)
        m_vertex_read_array[i] = verts[i];

    // Fill the vertex buffer
    void *pvertex_ptr;
    m_pd3d_vertex_buffer->Lock(0, 0, (void**) &pvertex_ptr, D3DLOCK_DISCARD);
    memcpy(pvertex_ptr, m_vertex_read_array, m_num_verts * sizeof(Vertex));
    m_pd3d_vertex_buffer->Unlock();

    RecalculateBounds();
} // BuildD3DBuffers


// ----------------------------------------------------------------------------
// Name: Mesh_IndexTriangleStrip::Draw
// Desc: Draw the mesh at the current view matrix
// ----------------------------------------------------------------------------
void Mesh_IndexTriangleStrip::Draw()
{
    // Set the vertex type and the verticies.
    m_pdevice->SetFVF(FVF_TYPE);
    m_pdevice->SetStreamSource(0, m_pd3d_vertex_buffer, 0, sizeof(Vertex));

    // Draw each index buffer
    for (size_t i = 0; i < m_d3d_index_buffers.size(); i++)
    {
        m_pdevice->SetIndices(m_d3d_index_buffers[i]);
        m_pdevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_num_verts, 
            0, m_d3d_index_buffer_size[i] - 2);
    } // for
} // Draw


// ----------------------------------------------------------------------------
// Name: Mesh_IndexTriangleStrip::LockVertexBuffer
// Desc: Lock the vertex buffer for writing
// Parm: Mesh_IndexTriangleStrip::Vertex **verts - returns an array of verticies
// Parm: DWORD flags                         - the flags
// Retn: bool                                - true if the vertex read was 
//       successful
// ----------------------------------------------------------------------------
bool Mesh_IndexTriangleStrip::LockVertexBuffer(Mesh_IndexTriangleStrip::Vertex **verts, DWORD flags)
{
    if (!m_dynamic)
    {
        verts = 0;
        return false;
    } // if

    return (SUCCEEDED(m_pd3d_vertex_buffer->Lock(0, 0, (void**) verts, flags)));
} // LockVertexBuffer


// ----------------------------------------------------------------------------
// Name: Mesh_IndexTriangleStrip::LockVertexBuffer
// Desc: Lock the vertex buffer for writing
// Parm: uint offset                         - the start offset into the buffer
// Parm: uint size                           - the size of the buffer
// Parm: Mesh_IndexTriangleStrip::Vertex **verts - returns an array of verticies
// Parm: DWORD flags                         - the flags
// Retn: bool                                - true if the vertex read was 
//       successful
// ----------------------------------------------------------------------------
bool Mesh_IndexTriangleStrip::LockVertexBuffer(uint offset, uint size, Mesh_IndexTriangleStrip::Vertex **verts, DWORD flags)
{
    if (!m_dynamic)
    {
        verts = 0;
        return false;
    } // if

    return (SUCCEEDED(m_pd3d_vertex_buffer->Lock(offset, size, (void**) verts, flags)));
} // LockVertexBuffer


// ----------------------------------------------------------------------------
// Name: Mesh_IndexTriangleStrip::UnlockVertexBuffer
// Desc: Unlocks the index buffer and performs the write
// Parm: bool update_bounds - if true, the bounding sphere and box will be 
//       recalculated.
// Retn: bool               - true if successful
// ----------------------------------------------------------------------------
bool Mesh_IndexTriangleStrip::UnlockVertexBuffer(bool update_bounds)
{
    bool ok = SUCCEEDED(m_pd3d_vertex_buffer->Unlock());

    if (ok && update_bounds)
        m_dirty = true;

    return ok;
} // UnlockVertexBuffer


// ----------------------------------------------------------------------------
// Name: Mesh_IndexTriangleStrip::RecalculateBounds
// Desc: Recalculate the bounding sphere and box for the mesh
// ----------------------------------------------------------------------------
void Mesh_IndexTriangleStrip::RecalculateBounds()
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
    for (size_t i = 0; i < m_num_verts; i++)
    {
        Vec3 vec        = vertex_array[i].loc - m_sphere.center;
        m_sphere.radius = min(m_sphere.radius, vec.Length());
    } // for

    // Close the vertex data
    m_pd3d_vertex_buffer->Unlock();

    m_dirty = false;
} // RecalculateBounds


// ----------------------------------------------------------------------------
// Name: Mesh_IndexTriangleStrip::GetBounds
// Desc: Get an axis aligned bounding box containing the extents of the mesh. 
//       Note - this is recalculated each time.
// Parm: Box &box - the box to set the extents of
// ----------------------------------------------------------------------------
void Mesh_IndexTriangleStrip::GetBounds(Box &box)
{
    if (m_dirty)
        RecalculateBounds();

    box = m_box;
} // GetBounds


// ----------------------------------------------------------------------------
// Name: Mesh_IndexTriangleStrip::GetBounds
// Desc: Get a bounding sphere containing the extents of the mesh. Note - this 
//       is recalculated each time.
// Parm: Sphere &sphere - the sphere to set the extents of
// ----------------------------------------------------------------------------
void Mesh_IndexTriangleStrip::GetBounds(Sphere &sphere)
{
    if (m_dirty)
        RecalculateBounds();

    sphere = m_sphere;
} // GetBounds


// -- EOF

