// ----------------------------------------------------------------------------
// File: GeoSet.cpp
// Desc: Holds a set of mneshes
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Scenegraph/GeoSet.h"
#include "Engine/RenderBin.h"


// ----------------------------------------------------------------------------
// Name: GeoSet::GeoSet
// Desc: Constructor
// ----------------------------------------------------------------------------
GeoSet::GeoSet()
{
    m_last_frame    = 0;
    m_static        = 0;
} // GeoSet


// ----------------------------------------------------------------------------
// Name: GeoSet::~GeoSet
// Desc: Destructor
// ----------------------------------------------------------------------------
GeoSet::~GeoSet()
{
} // ~GeoSet


// ----------------------------------------------------------------------------
// Name: GeoSet::GetMeshVec
// Desc: Get the mesh vector
// Retn: std::vector<Mesh *> & - the mesh vector
// ----------------------------------------------------------------------------
std::vector<GeoSet::Record> &GeoSet::GetMeshVec()
{
    return m_mesh_vec;
} // GetMeshVec


// ----------------------------------------------------------------------------
// Name: GeoSet::LoadFromASE
// Desc: Load all of the meshes from the ASE file
// Parm: ASELoader::RecordSet &records - the ASE recordset
// ----------------------------------------------------------------------------
bool GeoSet::LoadFromASE(ASELoader::RecordSet &records, bool allow_duplicates)
{
    ASELoader::RecordSetIter iter = records.begin();
    for (; iter != records.end(); ++iter)
    {
        ASELoader::Record &record = *iter;
        if (record.type == ASELoader::MESH)
            if (!AddMesh(record.pmesh, record.material_id, allow_duplicates))
                return false;
    } // for
    return true;
} // LoadFromASE


// ----------------------------------------------------------------------------
// Name: GeoSet::AddMesh
// Desc: Add a mesh to the geoset
// Parm: Mesh *pmesh - the mesh
// Retn: bool        - true if it was added
// ----------------------------------------------------------------------------
bool GeoSet::AddMesh(Mesh *pmesh, uint material_id, bool allow_duplicates)
{
    if (FindMesh(pmesh->GetName()) && !allow_duplicates)
        return false;

    m_mesh_vec.push_back(GeoSet::Record(pmesh, material_id));
    return true;
} // AddMesh


// ----------------------------------------------------------------------------
// Name: GeoSet::RemoveMesh
// Desc: Remove a mesh from the geoset
// Parm: Mesh *pmesh - the mesh
// Retn: bool        - true if it was removed
// ----------------------------------------------------------------------------
bool GeoSet::RemoveMesh(Mesh *pmesh)
{
    std::vector<GeoSet::Record>::iterator iter = m_mesh_vec.begin();
    for (; iter != m_mesh_vec.end(); ++iter)
    {
        if ((*iter).pmesh == pmesh)
        {
            m_mesh_vec.erase(iter);
            return true;
        } // if
    } // for

    return false;
} // RemoveMesh


// ----------------------------------------------------------------------------
// Name: GeoSet::SetMeshMaterial
// Desc: Set the material for a mesh
// Parm: Mesh *pmesh       - the mesh
// Parm: uint material_id  - the material
// Retn: bool              - true if the material was updated
// ----------------------------------------------------------------------------
bool GeoSet::SetMeshMaterial(Mesh *pmesh, uint material_id)
{
    std::vector<GeoSet::Record>::iterator iter = m_mesh_vec.begin();
    for (; iter != m_mesh_vec.end(); ++iter)
    {
        if ((*iter).pmesh == pmesh)
        {
            (*iter).mat_id = material_id;
            return true;
        } // if
    } // for

    return false;
} // SetMeshMaterial


// ----------------------------------------------------------------------------
// Name: GeoSet::FindMesh
// Desc: Find a mesh from the geoset by name
// Parm: const std::string &name - the name of the mesh
// Retn: Mesh *                  - the mesh
// ----------------------------------------------------------------------------
Mesh *GeoSet::FindMesh(const std::string &name)
{
    for (size_t i = 0; i < m_mesh_vec.size(); i++)
    {
        Mesh *pmesh = (m_mesh_vec[i]).pmesh;

        if (pmesh->GetName() == name)
            return pmesh;
    } // for

    return 0;
} // FindMesh


// ----------------------------------------------------------------------------
// Name: GeoSet::FindMeshMaterial
// Desc: Find a mesh from the geoset by name
// Parm: const std::string &name - the name of the mesh
// Retn: Mesh *                  - the mesh
// ----------------------------------------------------------------------------
uint GeoSet::FindMeshMaterial(const std::string &name)
{
    for (size_t i = 0; i < m_mesh_vec.size(); i++)
    {
        Mesh *pmesh = (m_mesh_vec[i]).pmesh;

        if (pmesh->GetName() == name)
            return (m_mesh_vec[i]).mat_id;
    } // for

    return 0;
} // FindMesh


// ----------------------------------------------------------------------------
// Name: GeoSet::GetMesh
// Desc: Get a mesh from the geoset by index
// Parm: uint index - the index of the mesh
// Retn: Mesh *     - the mesh
// ----------------------------------------------------------------------------
Mesh *GeoSet::GetMesh(uint index)
{
    return m_mesh_vec[index].pmesh;
} // GetMesh


// ----------------------------------------------------------------------------
// Name: GeoSet::GetMeshMaterial
// Desc: Get a mesh from the geoset by index
// Parm: uint index - the index of the mesh
// Retn: uint - the material id
// ----------------------------------------------------------------------------
uint GeoSet::GetMeshMaterial(uint index)
{
    return m_mesh_vec[index].mat_id;
} // GetMeshMaterial


// ----------------------------------------------------------------------------
// Name: GeoSet::GetBSphere
// Desc: Get the bounding sphere
// Retn: const Sphere & - the sphere
// ----------------------------------------------------------------------------
const Sphere &GeoSet::GetBSphere()
{
    if (RenderBin::GetFrameCount() == m_last_frame)
        return m_sphere;
    
    if (!m_static)
    {
        m_sphere.Reset();

        for (size_t i = 0; i < m_mesh_vec.size(); i++)
        {
            Mesh *pmesh = (m_mesh_vec[i]).pmesh;

            if (i == 0)
                pmesh->GetBounds(m_sphere);
            else
            {
                Sphere s;
                pmesh->GetBounds(s);
                m_sphere.Calculate(m_sphere, s);
            } // else
        } // for
    } // if

    m_last_frame = RenderBin::GetFrameCount();
    return m_sphere;
} // GetBSphere


// ----------------------------------------------------------------------------
// Name: GeoSet::SetBSphereStatic
// Desc: Force the bounding sphere to be static and not recalculated
// ----------------------------------------------------------------------------
void GeoSet::SetBSphereStatic()
{
    m_static = false;
    GetBSphere();
    m_static = true;
} // SetBSphereStatic


// -- EOF


