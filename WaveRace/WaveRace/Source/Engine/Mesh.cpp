// ----------------------------------------------------------------------------
// File: Mesh.h
// Desc: Base class for a mesh, that allows basic generic behaviour
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes for the mesh class
// ----------------------------------------------------------------------------
#include <vector>
#include <string>
#include "Engine/Mesh.h"


// ----------------------------------------------------------------------------
// Name: Mesh::Mesh
// Desc: Constructor
// Parm: const char *name          - the mesh name
// Parm: LPDIRECT3DDEVICE9 device  - the device to use to create the mesh (
//       allocates memory from the devices managed pool)
// ----------------------------------------------------------------------------
Mesh::Mesh(const char *name, LPDIRECT3DDEVICE9 device) : RefCounted()
{
    m_name      = name;
    m_pdevice   = device;
} // Mesh


// ----------------------------------------------------------------------------
// Name: Mesh::~Mesh
// Desc: Destructor (virtual)
// ----------------------------------------------------------------------------
Mesh::~Mesh()
{
} // ~Mesh


// -- EOF

