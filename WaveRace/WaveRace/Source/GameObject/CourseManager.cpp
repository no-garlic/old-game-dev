// ----------------------------------------------------------------------------
// File: CourseManager.cpp
// Desc: Manages the course, the buoys, etc..
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Shader define
// ----------------------------------------------------------------------------
#define BUOY_SHADER "Buoy.fx"


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "GameObject/CourseManager.h"
#include "GameObject/Wave.h"
#include "Common/FilePath.h"
#include "Engine/RenderBin.h"
#include "SceneGraph/Node.h"
#include "SceneGraph/DCS.h"
#include "SceneGraph/Geode.h"
#include "SceneGraph/GeoSet.h"
#include "SceneGraph/IntersectionTraverser.h"
#include "SceneGraph/CleanupTraverser.h"


// ----------------------------------------------------------------------------
// Name: CourseManager::CourseManager
// Desc: Constructor
// ----------------------------------------------------------------------------
CourseManager::CourseManager()
{
    m_pgroup_node = 0;
} // CourseManager


// ----------------------------------------------------------------------------
// Name: CourseManager::~CourseManager
// Desc: Destructor
// ----------------------------------------------------------------------------
CourseManager::~CourseManager()
{
    Release();
} // ~CourseManager


// ----------------------------------------------------------------------------
// Name: CourseManager::Create
// Desc: Create the course
// Parm: LPDIRECT3DDEVICE9 device - the device
// Parm: const char *filename     - the pos file name
// ----------------------------------------------------------------------------
bool CourseManager::Create(LPDIRECT3DDEVICE9 device, const char *filename)
{
    Release();

    m_device = device;

    std::string fn = FilePathSingleton::Instance().FindFile(filename);
    if (fn.empty())
    {
        LOG_ERROR << "Failed to find the buoy pos file: " << filename << ENDLOG;
        return false;
    } // if

    // Load the position file
    if (!m_pos_reader.Load(fn.c_str()))
        return false;

    // Load the buoys
    ASELoader::RecordSet records_l;
    if (!ASELoader::LoadFile("buoy_l.asb", records_l, ASELoader::PROJ_LH, ASELoader::WIND_CW, device))
    {
        LOG_ERROR << "Failed to load the buoy_l" << ENDLOG;
        return false;
    } // if

    ASELoader::RecordSet records_r;
    if (!ASELoader::LoadFile("buoy_r.asb", records_r, ASELoader::PROJ_LH, ASELoader::WIND_CW, device))
    {
        LOG_ERROR << "Failed to load the buoy_r" << ENDLOG;
        return false;
    } // if

    // Create the root node
    m_pgroup_node = new Group("Buoys");

    // Create a buoy for each position
    typedef std::map<std::string, PositionReader::Pos> PosData;
    const PosData &pos_data = m_pos_reader.GetData();
    for (PosData::const_iterator iter = pos_data.begin(); iter != pos_data.end(); ++iter)
    {
        const std::string name            = iter->first;
        const PositionReader::Pos &pos    = iter->second;

        DCS    *pdcs    = new DCS(name);
        Geode  *pgeode  = new Geode(name);
        GeoSet *pgeoset = new GeoSet();

        // Load the meshs into the geoset for the buoy
        if (name[0] == 'L')
            pgeoset->LoadFromASE(records_l, false);
        else
            pgeoset->LoadFromASE(records_r, false);

        // Apply a new shader to the sea-doo object from the geoset
        Mesh *pmesh = pgeoset->GetMesh(0);
        if (pmesh)
        {
            uint curr_id = pgeoset->GetMeshMaterial(0);
            MaterialCache::Record rec = MaterialCache::GetMaterial(curr_id);

            uint new_id  = MaterialCache::CreateMaterial(
                rec.tex_map0, rec.tex_map1, rec.tex_map2, BUOY_SHADER, FX_TEX0, true);
            
            pgeoset->SetMeshMaterial(pmesh, new_id);
        } // if

        // Create the DCS position matrix
        Matrix *pmatrix = pdcs->GetMatrixPtr();
        pmatrix->Translation(pos.x, pos.y, -3.0f);
        pmatrix->PostMultiply(Matrix::MakeNewRotationYawPitchRoll(0.0f, 0.0f, pos.h));

        const float DEG2RAD = 2.0f*D3DX_PI/360.0f;
        const float RAD2DEG = 1.0f/DEG2RAD;

        // Store the position data
        CourseManager::PosData pos_data;
        pos_data.x = pos.x;
        pos_data.y = pos.y;
        pos_data.z = 0;
        pos_data.h = pos.h * DEG2RAD;
        pos_data.normal.Set(0.0f, 0.0f, 0.0f);
        pos_data.pmatrix = pmatrix;
        m_buoys.push_back(pos_data);

        // Setup the scenegraph hierarchy
        m_pgroup_node->AddChild(pdcs);
        pdcs->AddChild(pgeode);
        pgeode->AddGeoSet(pgeoset);
    } // for

    return true;
} // Create


// ----------------------------------------------------------------------------
// Name: CourseManager::Release
// Desc: Release the objects created with the d3d device
// ----------------------------------------------------------------------------
void CourseManager::Release()
{
    if (!m_device)
        return;

    m_pos_reader.Clear();
    m_buoys.clear();

//    CleanupTraverser trav;
//    trav.Traverse(m_pgroup_node);

    m_pgroup_node = 0;
} // Release


// ----------------------------------------------------------------------------
// Name: CourseManager::Render
// Desc: Render the buoys
// ----------------------------------------------------------------------------
void CourseManager::Render()
{
    if (m_pgroup_node)
    {
        m_cull_trav.Reset();
        m_cull_trav.Traverse(m_pgroup_node);
    } // if
} // Render


void CourseManager::Simulate(float run_time)
{
    float p = sin(run_time * 0.3f) * 0.05f;
    float r = (cos(run_time + 0.25f) + sin(run_time * 1.5f)) * 0.05f;

    for (uint i = 0; i < m_buoys.size(); i++)
    {
        CourseManager::PosData &pd = m_buoys[i];
        pd.pmatrix->Translation(pd.x, pd.y, -0.25f + p);
        pd.pmatrix->PostMultiply(Matrix::MakeNewRotationYawPitchRoll(p, r, pd.h));
    } // for
} // Simluate


// -- EOF

