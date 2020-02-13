// ----------------------------------------------------------------------------
// File: Mesh.h
// Desc: Base class for a mesh, that allows basic generic behaviour
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _MESH_H
#define _MESH_H


// ----------------------------------------------------------------------------
// Includes for the mesh class
// ----------------------------------------------------------------------------
#include <string>
#include "Math/Types.h"
#include "Math/Sphere.h"
#include "Math/Box.h"
#include "Math/Intersect.h"
#include "Common/Utilities.h"


// ----------------------------------------------------------------------------
// Name: Mesh  (class)
// Desc: Base class for a mesh, that allows basic generic behaviour
// ----------------------------------------------------------------------------
class Mesh : public Memory::RefCounted, private Utility::Unique
{
public:
    // ------------------------------------------------------------------------
    // Constructor & destructor
    // ------------------------------------------------------------------------
    Mesh(const char *name, LPDIRECT3DDEVICE9 device);
    virtual ~Mesh();


    // ------------------------------------------------------------------------
    // Draw the mesh at the current world matrix
    // ------------------------------------------------------------------------
    virtual void Draw() = 0;


    // ------------------------------------------------------------------------
    // Get the name of the mesh
    // ------------------------------------------------------------------------
    const char  *GetName() { return m_name.c_str(); }


    // ------------------------------------------------------------------------
    // Get the bounds of the mesh
    // ------------------------------------------------------------------------
    virtual void GetBounds(Sphere &sphere)  = 0;
    virtual void GetBounds(Box &box)        = 0;


    // ------------------------------------------------------------------------
    // Get the triangles of the mesh for ray testing
    // ------------------------------------------------------------------------
    virtual const std::vector<Triangle> &GetMeshTriangles() { return m_triangles; }


protected:
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    std::string             m_name;         // Name of the mesh
    LPDIRECT3DDEVICE9       m_pdevice;      // Device
    std::vector<Triangle>   m_triangles;    // Triangles for ray testing


}; // class Mesh


#endif // _MESH_H

// -- EOF
