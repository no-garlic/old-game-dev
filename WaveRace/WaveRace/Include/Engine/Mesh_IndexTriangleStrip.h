// ----------------------------------------------------------------------------
// File: Mesh_IndexTriangleStrip.h
// Desc: Mesh that uses an index array and vertex array
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _MESH_INDEXEX_TRIANGLE_STRIP_H
#define _MESH_INDEXEX_TRIANGLE_STRIP_H


// ----------------------------------------------------------------------------
// Includes for the indexed vertex array mesh
// ----------------------------------------------------------------------------
#include "Engine/Mesh.h"
#include "Math/Color.h"


// ----------------------------------------------------------------------------
// Name: Mesh_IndexTriangleStrip  (class)
// Desc: Mesh that uses an index array and vertex array
// ----------------------------------------------------------------------------
class Mesh_IndexTriangleStrip : public Mesh
{
public:
    // ------------------------------------------------------------------------
    // Name: Vertex (struct)
    // Desc: Vertex type ofr our mesh
    // ------------------------------------------------------------------------
    struct Vertex
    {
        // --------------------------------------------------------------------
        // Constructors
        // --------------------------------------------------------------------
        Vertex() : u(0), v(0), diff(Color::White) {}
        Vertex(const Vec3 &_loc, const Vec3 &_norm, ulong _diff, float _u, float _v, float _u2, float _v2)
            : loc(_loc), norm(_norm), diff(_diff), u(_u), v(_v), u2(_u2), v2(_v2) {}


        // --------------------------------------------------------------------
        // Private members
        // --------------------------------------------------------------------
        Vec3    loc;    // Location of the vertex
        Vec3    norm;   // Normal of the vertex
        ulong   diff;   // Diffuse color
        float   u, v;   // Texture U & V co-ordinates
        float   u2, v2; // Texture U & V co-ordinates
    }; // struct Vertex

    
    // ------------------------------------------------------------------------
    // Our index type
    // ------------------------------------------------------------------------
    typedef int Index;


    // ------------------------------------------------------------------------
    // Typedefs for the container types the mesh uses
    // ------------------------------------------------------------------------
    typedef std::vector<Mesh_IndexTriangleStrip::Vertex>    VertexVec;
    typedef std::vector<Mesh_IndexTriangleStrip::Index>     IndexVec;
    typedef std::vector<Mesh_IndexTriangleStrip::IndexVec>  IndexVecVec;


public:
    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
                    Mesh_IndexTriangleStrip(const char *name, LPDIRECT3DDEVICE9 device, 
                        const VertexVec &verts, const IndexVecVec &indicies, bool dynamic = true);
    virtual        ~Mesh_IndexTriangleStrip();


    // ------------------------------------------------------------------------
    // Draw the mesh at the current world matrix
    // ------------------------------------------------------------------------
    virtual void    Draw();


    // ------------------------------------------------------------------------
    // Get the bounds of the mesh
    // ------------------------------------------------------------------------
    virtual void    GetBounds(Sphere &sphere);
    virtual void    GetBounds(Box &box);


    // ------------------------------------------------------------------------
    // Read the vertex data that was specified in the constructor. 
    // This is the most efficient way to read the vertex information 
    // because it lies in system memory.  Reading from the vertex 
    // buffers requires the memory to be copied from AGP memory.
    // ------------------------------------------------------------------------
    const Vertex   *ReadOrigionalVertexData()   { return m_vertex_read_array; }


    // ------------------------------------------------------------------------
    // Lock and unlock the vertex and index buffers
    // ------------------------------------------------------------------------
    bool            LockVertexBuffer(Vertex **verts, DWORD flags);
    bool            LockVertexBuffer(uint offset, uint size, Vertex **verts, DWORD flags);
    bool            UnlockVertexBuffer(bool update_bounds);


    // ------------------------------------------------------------------------
    // Get the size of the data
    // ------------------------------------------------------------------------
    uint            GetNumVerts()  { return m_num_verts; }

private:
    // ------------------------------------------------------------------------
    // Build the vertex and index buffers
    // ------------------------------------------------------------------------
    void            BuildD3DBuffers(const VertexVec &verts, const IndexVecVec &indicies);
    void            RecalculateBounds();

    
    // ------------------------------------------------------------------------
    // Bounding box and sphere
    // ------------------------------------------------------------------------
    bool            m_dirty;
    bool            m_dynamic;
    Box             m_box;
    Sphere          m_sphere;


    // ------------------------------------------------------------------------
    // Model faces and verticies as supplied in the constructor
    // ------------------------------------------------------------------------
    uint            m_num_verts;    

    
    // ------------------------------------------------------------------------
    // Index and vertex buffers created by the device
    // ------------------------------------------------------------------------
    IDirect3DVertexBuffer9                  *m_pd3d_vertex_buffer;
    std::vector<IDirect3DIndexBuffer9 *>     m_d3d_index_buffers;
    std::vector<size_t>                      m_d3d_index_buffer_size;


    // ------------------------------------------------------------------------
    // Local copy of the index and vertex buffer for reading (stored in system 
    // memory)
    // ------------------------------------------------------------------------
    Vertex                                 *m_vertex_read_array;

}; // class Mesh_IndexTriangleStrip


#endif // _MESH_INDEXEX_TRIANGLE_STRIP_H

// -- EOF
