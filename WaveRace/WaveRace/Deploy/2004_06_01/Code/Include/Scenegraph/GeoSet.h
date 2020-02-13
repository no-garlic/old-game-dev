// ----------------------------------------------------------------------------
// File: GeoSet.h
// Desc: Holds a set of meshes
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _GEOSET_H
#define _GEOSET_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include <vector>
#include "Common/Utilities.h"
#include "Math/Types.h"
#include "Engine/Mesh.h"
#include "Engine/ASE.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class CullTraverser;
class IntersectionTraverser;
class CleanupTraverser;


// ----------------------------------------------------------------------------
// Name: GeoSet  (class)
// Desc: Holds a set of meshes
// ----------------------------------------------------------------------------
class GeoSet : private Utility::Unique
{
public:
    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
             GeoSet();
    virtual ~GeoSet();


    // ------------------------------------------------------------------------
    // Public functions
    // ------------------------------------------------------------------------
    bool            LoadFromASE(ASELoader::RecordSet &records, bool allow_duplicates = false);
    bool            AddMesh(Mesh *pmesh, uint material_id, bool allow_duplicates = false);
    bool            SetMeshMaterial(Mesh *pmesh, uint material_id);
    bool            RemoveMesh(Mesh *pmesh);
    uint            GetNumMesh() { return m_mesh_vec.size(); }
    Mesh           *GetMesh(uint idx);
    uint            GetMeshMaterial(uint index);
    Mesh           *FindMesh(const std::string &name);
    uint            FindMeshMaterial(const std::string &name);

    void            SetBSphereStatic();
    const Sphere   &GetBSphere();


private:
    // ------------------------------------------------------------------------
    // Friend classes
    // ------------------------------------------------------------------------
    friend class CullTraverser;
    friend class IntersectionTraverser;
    friend class CleanupTraverser;

    
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
    // Friend accessed functions
    // ------------------------------------------------------------------------
    std::vector<GeoSet::Record> &GetMeshVec();


private:
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    std::vector<GeoSet::Record>     m_mesh_vec;     // All meshes
    Sphere                          m_sphere;       // The bounding sphere
    bool                            m_static;       // Static bsphere
    ulong                           m_last_frame;   // Frame num when last bsphere calc


}; // class GeoSet


#endif // _GEOSET_H

// -- EOF

