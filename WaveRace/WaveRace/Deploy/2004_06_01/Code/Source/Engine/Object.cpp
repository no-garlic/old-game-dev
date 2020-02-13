// ----------------------------------------------------------------------------
// File: Object.cpp
// Desc: Object to wrap up a number of meshes
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Engine/Object.h"
#include "Engine/RenderBin.h"


// ----------------------------------------------------------------------------
// Name: Object::Object
// Desc: Constructor
// ----------------------------------------------------------------------------
Object::Object(LPDIRECT3DDEVICE9 device)
{
    m_enabled   = true;
    m_device    = device;
} // Object


// ----------------------------------------------------------------------------
// Name: Object::Object
// Desc: Constructor that loads all records from the ASE loader
// Parm: ASELoader::RecordSet &records - the records
// ----------------------------------------------------------------------------
Object::Object(LPDIRECT3DDEVICE9 device, ASELoader::RecordSet &records)
{
    m_enabled = true;
    m_device    = device;

    LoadFromASE(records);
} // Object


// ----------------------------------------------------------------------------
// Name: Object::~Object
// Desc: Destructor
// ----------------------------------------------------------------------------
Object::~Object()
{
    typedef Object::Record rec_type;
    std::vector<rec_type>::iterator iter;

    for (iter = m_records.begin(); iter != m_records.end(); ++iter)
        delete (*iter).pmesh;

    m_records.clear();
} // ~Object


// ----------------------------------------------------------------------------
// Name: Object::LoadFromASE
// Desc: Load all of the meshes from the ASE file
// Parm: ASELoader::RecordSet &records - the ASE recordset
// ----------------------------------------------------------------------------
void Object::LoadFromASE(ASELoader::RecordSet &records)
{
    ASELoader::RecordSetIter iter = records.begin();
    for (; iter != records.end(); ++iter)
    {
        ASELoader::Record &record = *iter;
        if (record.type == ASELoader::MESH)
            AddMesh(record.pmesh, record.material_id);
    } // for
} // LoadFromASE


// ----------------------------------------------------------------------------
// Name: Object::AddMesh
// Desc: Add a mesh to the object
// Parm: Mesh *pm  - the mesh
// Parm: uint mat  - the material id
// ----------------------------------------------------------------------------
void Object::AddMesh(Mesh *pm, uint mat)
{
    // Update the bounding sphere
    Sphere sphere;
    pm->GetBounds(sphere);
    if (m_records.empty())
        m_sphere = sphere;
    else
        m_sphere.Calculate(m_sphere, sphere);

    // Add the mesh to the vector
    m_records.push_back(Object::Record(pm, mat));
} // AddMesh


// ----------------------------------------------------------------------------
// Name: Object::AddToRenderBin
// Desc: Render all meshes in the object
// ----------------------------------------------------------------------------
void Object::AddToRenderBin(const Matrix &world_matrix)
{
    typedef Object::Record rec_type;
    std::vector<rec_type>::iterator iter = m_records.begin();
    for (; iter != m_records.end(); ++iter)
    {
        rec_type &record = *iter;
        RenderBinSingleton::Instance().AddRenderTarget(record.pmesh, record.mat_id, world_matrix);
    } // for
} // Render


// -- EOF
