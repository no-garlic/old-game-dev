// ----------------------------------------------------------------------------
// File: Object.h
// Desc: Object to wrap up a number of meshes
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _OBJECT_H_
#define _OBJECT_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Engine/Mesh.h"
#include "Engine/ASE.h"
#include "Math/Types.h"
#include "Math/Matrix.h"


// ----------------------------------------------------------------------------
// Name: Object  (class)
// Desc: Object class to wrap up a number of meshes
// ----------------------------------------------------------------------------
class Object : private Utility::Unique
{
public:
    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
             Object(LPDIRECT3DDEVICE9 device);
             Object(LPDIRECT3DDEVICE9 device, ASELoader::RecordSet &records);
    virtual ~Object();


    // ------------------------------------------------------------------------
    // Public methods
    // ------------------------------------------------------------------------
    void            LoadFromASE(ASELoader::RecordSet &records);
    void            AddMesh(Mesh *pm, uint mat);
    void            AddToRenderBin(const Matrix &world_matrix = Matrix::GetIdentityRef());
    void            SetEnabled(bool enabled)    { m_enabled = enabled;  }
    const Sphere   &GetBounds()                 { return m_sphere;      }


private:
    // ------------------------------------------------------------------------
    // A record holds a single textured side of the box
    // ------------------------------------------------------------------------
    struct Record
    {
        Record(Mesh *pm, uint mat) : pmesh(pm), mat_id(mat) {}
        Mesh    *pmesh;
        uint     mat_id;
    }; // struct Record


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    LPDIRECT3DDEVICE9               m_device;   // The device
    bool                            m_enabled;  // Is the object enabled
    std::vector<Object::Record>     m_records;  // The records to render
    Sphere                          m_sphere;   // The bounding sphere

}; // class Object


#endif // _OBJECT_H_

// -- EOF

