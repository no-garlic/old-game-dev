// ----------------------------------------------------------------------------
// File: Mesh_IndexVertArray.h
// Desc: Mesh that uses an index array and vertex array
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _MESH_INDEXEX_VERT_ARRAY_H
#define _MESH_INDEXEX_VERT_ARRAY_H


// ----------------------------------------------------------------------------
// Includes for the indexed vertex array mesh
// ----------------------------------------------------------------------------
#include "Engine/Mesh.h"
#include "Math/Color.h"


// ----------------------------------------------------------------------------
// Name: Mesh_IndexVertArray  (class)
// Desc: Mesh that uses an index array and vertex array
// ----------------------------------------------------------------------------
class Mesh_IndexVertArray : public Mesh
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
        Vertex(const Vec3 &_loc, const Vec3 &_norm, ulong _diff, float _u, float _v)
            : loc(_loc), norm(_norm), diff(_diff), u(_u), v(_v) {}


        // --------------------------------------------------------------------
        // Private members
        // --------------------------------------------------------------------
        Vec3    loc;    // Location of the vertex
        Vec3    norm;   // Normal of the vertex
        ulong   diff;   // Diffuse color
        float   u, v;   // Texture U & V co-ordinates
    }; // struct Vertex

    
    // ------------------------------------------------------------------------
    // Name: Face (struct)
    // Desc: Face (index) type for our mesh
    // ------------------------------------------------------------------------
    struct Face
    {
        // --------------------------------------------------------------------
        // Constructors
        // --------------------------------------------------------------------
        Face() { Assign(0, 0, 0); }
	    Face(uint v0, uint v1, uint v2) { Assign(v0, v1, v2); }


        // --------------------------------------------------------------------
        // The face array (indexes into the vertex array)
        // --------------------------------------------------------------------
        uint v[3];


        // --------------------------------------------------------------------
        // Set the face indecies
        // --------------------------------------------------------------------
        void Assign(uint v0, uint v1, uint v2)
        {
		    v[0] = v0;
		    v[1] = v1;
		    v[2] = v2;
        } // Assign
    }; // struct Face


    // ------------------------------------------------------------------------
    // Typedefs for the container types the mesh uses
    // ------------------------------------------------------------------------
    typedef std::vector<Mesh_IndexVertArray::Vertex>   VertexVec;
    typedef std::vector<Mesh_IndexVertArray::Face>     FaceVec;


public:
    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
                    Mesh_IndexVertArray(const char *name, LPDIRECT3DDEVICE9 device, 
                        const VertexVec &verts, const FaceVec &faces, bool dynamic = true);
    virtual        ~Mesh_IndexVertArray();


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
    // Read the vertex and index data that was specified in the constructor. 
    // This is the most efficient way to read the vertex and index information 
    // because it lies in system memory.  Reading from the vertex and index 
    // buffers requires the memory to be copied from AGP memory.
    // ------------------------------------------------------------------------
    const Vertex   *ReadOrigionalVertexData()   { return m_vertex_read_array; }
    const Face     *ReadOrigionalIndexData()    { return m_face_read_array;   }


    // ------------------------------------------------------------------------
    // Lock and unlock the vertex and index buffers
    // ------------------------------------------------------------------------
    bool            LockVertexBuffer(Vertex **verts, DWORD flags);
    bool            LockVertexBuffer(uint offset, uint size, Vertex **verts, DWORD flags);
    bool            LockIndexBuffer(Face **faces, DWORD flags);
    bool            LockIndexBuffer(uint offset, uint size, Face **faces, DWORD flags);
    bool            UnlockIndexBuffer(bool update_bounds);
    bool            UnlockVertexBuffer(bool update_bounds);


    // ------------------------------------------------------------------------
    // Set the range of verts and indexes to render
    // ------------------------------------------------------------------------
    void            SetDrawFaces(uint count)    { m_draw_faces = count; }
    void            SetDrawVerts(uint count)    { m_draw_verts = count; }


    // ------------------------------------------------------------------------
    // Get the size of the data
    // ------------------------------------------------------------------------
    uint            GetNumVerts()  { return m_num_verts; }
    uint            GetNumFaces()  { return m_num_faces; }

private:
    // ------------------------------------------------------------------------
    // Build the vertex and index buffers
    // ------------------------------------------------------------------------
    void            BuildD3DBuffers(const VertexVec &verts, const FaceVec &faces);
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
    uint            m_num_faces;
    uint            m_num_verts;    
    uint            m_draw_faces;
    uint            m_draw_verts;    

    
    // ------------------------------------------------------------------------
    // Index and vertex buffers created by the device
    // ------------------------------------------------------------------------
    IDirect3DVertexBuffer9      *m_pd3d_vertex_buffer;
    IDirect3DIndexBuffer9       *m_pd3d_index_buffer;


    // ------------------------------------------------------------------------
    // Local copy of the index and vertex buffer for reading (stored in system 
    // memory)
    // ------------------------------------------------------------------------
    Vertex                      *m_vertex_read_array;
    Face                        *m_face_read_array;

}; // class Mesh_IndexVertArray


#endif // _MESH_INDEXEX_VERT_ARRAY_H

// -- EOF
