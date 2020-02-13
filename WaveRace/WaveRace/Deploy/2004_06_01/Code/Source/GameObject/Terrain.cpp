// ----------------------------------------------------------------------------
// File: Terrain.cpp
// Desc: Terrain renderer
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "GameObject/Terrain.h"
#include "Engine/RenderBin.h"
#include "Engine/ASE.h"
#include "Common/Logging.h"
#include "Math/Intersect.h"
#include "Scenegraph/CleanupTraverser.h"



Geode *MakeSpatial(ASELoader::RecordSet &records, float cell_size)
{
    Geode *pgeode = new Geode();

    std::map<std::string, ASELoader::RecordSet> spatial_records;
    for (uint i = 0; i < records.size(); i++)
    {
        ASELoader::Record &record = records[i];

        if (record.type == ASELoader::MESH)
        {
            Sphere s;
            record.pmesh->GetBounds(s);

            float x = s.center[0] / cell_size;
            float y = s.center[1] / cell_size;

            uint cell_x = static_cast<uint>(x);
            uint cell_y = static_cast<uint>(y);

            std::string cell_name = "Trees_";
            String::AppendInt(cell_name, cell_x);
            cell_name += "_";
            String::AppendInt(cell_name, cell_y);

            spatial_records[cell_name].push_back(record);
        } // if
    } // for

    std::map<std::string, ASELoader::RecordSet>::iterator iter = spatial_records.begin();
    for (; iter != spatial_records.end(); ++iter)
    {
        GeoSet *pgeoset = new GeoSet();
        if (!pgeoset->LoadFromASE(iter->second, true))
        {
            LOG_ERROR << "Failed to load the geoset from the ASE records" << ENDLOG;
            delete pgeoset;
            return 0;
        } // if

        LOG_INFO << "Creating Spatial Cell: " << iter->first << ENDLOG;
        pgeoset->SetBSphereStatic();
        pgeode->AddGeoSet(pgeoset);
    } // for

    // Stop recalculation of bounds
    pgeode->SetBSphereStatic();
    return pgeode;
} // MakeSpatial


// ----------------------------------------------------------------------------
// Name: Terrain::Terrain
// Desc: Constructor
// ----------------------------------------------------------------------------
Terrain::Terrain()
{
    m_device = 0;
    m_pterrain  = 0;
    m_ptrees    = 0;
    m_pprops    = 0;
} // Terrain


// ----------------------------------------------------------------------------
// Name: Terrain::~Terrain
// Desc: Destructor
// ----------------------------------------------------------------------------
Terrain::~Terrain()
{
    Release();
} // ~Terrain


// ----------------------------------------------------------------------------
// Name: Terrain::Create
// Desc: Create a terrain set
// Parm: const char *filename      - the filename of the terrain object
// Parm: LPDIRECT3DDEVICE9 device  - the device
// ----------------------------------------------------------------------------
bool Terrain::Create(const char *filename, LPDIRECT3DDEVICE9 device)
{
    Release();
    m_device = device;

    // Load the terrain object
    {
        ASELoader::RecordSet records;
        if (!ASELoader::LoadFile(filename, records, ASELoader::PROJ_LH, ASELoader::WIND_CW, m_device))
        {
            LOG_ERROR << "Failed to load the terrain file: " << filename << ENDLOG;
            return false;
        } // if

        // Create the geoset
        GeoSet *pgeoset = new GeoSet();
        if (!pgeoset->LoadFromASE(records, true))
        {
            LOG_ERROR << "Failed to load the terrain geoset from the ASE records" << ENDLOG;
            delete pgeoset;
            return false;
        } // if
        
        // Create the node
        pgeoset->SetBSphereStatic();
        m_pterrain = new Geode("Terrain");
        m_pterrain->AddGeoSet(pgeoset);
        m_pterrain->SetBSphereStatic();
    }

    // Load the trees
    {
        ASELoader::RecordSet records;
        if (!ASELoader::LoadFile("trees.asb", records, ASELoader::PROJ_LH, ASELoader::WIND_CW, m_device))
        {
            LOG_ERROR << "Failed to load the trees file: trees.asb" << ENDLOG;
            return false;
        } // if

        // Create the node
        m_ptrees = MakeSpatial(records, 100.0f);
    }

    // Load the props
    {
        ASELoader::RecordSet records;
        if (!ASELoader::LoadFile("props.asb", records, ASELoader::PROJ_LH, ASELoader::WIND_CW, m_device))
        {
            LOG_ERROR << "Failed to load the trees file: props.asb" << ENDLOG;
            return false;
        } // if

        // Create the node
        m_pprops = MakeSpatial(records, 100.0f);
    }

    return true;
} // Create


// ----------------------------------------------------------------------------
// Name: Terrain::Release
// Desc: Release the terrain from the device
// ----------------------------------------------------------------------------
void Terrain::Release()
{
    if (!m_device)
        return;

    // Delete the scenegraph
    CleanupTraverser trav;
    trav.Traverse(m_pterrain);
//    trav.Traverse(m_ptrees);
//    trav.Traverse(m_pprops);
    m_pterrain  = 0;
    m_ptrees    = 0;
    m_pprops    = 0;

    // Reset the device pointer
    m_device = 0;
} // Release


// ----------------------------------------------------------------------------
// Name: Terrain::Render
// Desc: Render the terrain
// ----------------------------------------------------------------------------
void Terrain::Render()
{
    if (m_pterrain)
    {
        m_cull_trav.Reset();
        m_cull_trav.Traverse(m_pterrain);
        m_cull_trav.Traverse(m_ptrees);
        m_cull_trav.Traverse(m_pprops);
    } // if
} // GetRootNode


// ----------------------------------------------------------------------------
// Name: Terrain::GetTerrainHeight
// Desc: Ray test to get the terrain height and normal
// Parm: float x   - the x position (in)
// Parm: float y   - the y position (in)
// Parm: float &z  - the z position (out)
// Parm: Vec3 &n   - the normal (out)
// Retn: bool      - true if an intersection occurred
// ----------------------------------------------------------------------------
bool Terrain::GetTerrainHeight(float x, float y, float &z, Vec3 &n)
{
    if (!m_pterrain)
        return false;

    m_isect_trav.Reset();

    Ray ray;
    ray.position.Set(x, y, -1000.0f);
    ray.direction.Set(0.0f, 0.0f, 1.0f);

    HitInfo hit_info;

    if (m_isect_trav.Traverse(m_pterrain, ray, hit_info))
    {
        for (uint i = 0; i < hit_info.size(); i++)
        {
            RayHit &hit = hit_info[i];
            Vec3 isect  = (ray.direction * hit.distance) + ray.position;

            if (i == 0)
            {
                z = isect[2];
                n = hit.normal_w;
            } // if
            else
            {
                if (isect[2] < z)
                {
                    z = isect[2];
                    n = hit.normal_w;
                } // if
            } // else
        } // for
        return true;
    } // if
    else
    {
        return false;
    } // else
} // GetTerrainHeight


// -- EOF

