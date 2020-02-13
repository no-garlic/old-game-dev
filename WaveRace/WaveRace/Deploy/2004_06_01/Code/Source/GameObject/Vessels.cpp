// ----------------------------------------------------------------------------
// File: Vessels.cpp
// Desc: Manages the ocean
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "GameObject/Vessels.h"
#include "Common/Logging.h"
#include "Common/FilePath.h"
#include "SceneGraph/Node.h"
#include "SceneGraph/DCS.h"
#include "SceneGraph/Geode.h"
#include "SceneGraph/GeoSet.h"
#include "SceneGraph/IntersectionTraverser.h"
#include "Physics/MovingVessel.h"
#include "Math/Intersect.h"
#include "Engine/RenderBin.h"
#include "Engine/Camera.h"


// ----------------------------------------------------------------------------
// Name of boat types
// ----------------------------------------------------------------------------
#define VESSEL_NAME_CANNOE      "boat.asb"
#define VESSEL_NAME_YACHT       "yacht.asb"
#define VESSEL_NAME_SEA_DOO     "sea-doo.asb"
#define SEA_DOO_SHADER          "SeaDoo.fx"

// ----------------------------------------------------------------------------
// Name: Vessels::Vessels
// Desc: Constructor
// ----------------------------------------------------------------------------
Vessels::Vessels()
{
    m_device        = 0;
    m_pgroup_node   = 0;
    m_material_id   = 0;
} // Vessels


// ----------------------------------------------------------------------------
// Name: Vessels::~Vessels
// Desc: Destructor
// ----------------------------------------------------------------------------
Vessels::~Vessels()
{
    Release();
} // ~Vessels


// ----------------------------------------------------------------------------
// Name: Vessels::Create
// Desc: Create the environment objects
// Parm: LPDIRECT3DDEVICE9 device - the device to load the skyboxes with
// Retn: bool                     - true if all loaded successfully
// ----------------------------------------------------------------------------
bool Vessels::Create(LPDIRECT3DDEVICE9 device)
{
    Release();
    m_device = device;
    
    m_pgroup_node = new Group("Vessels");

    return true;
} // Create


// ----------------------------------------------------------------------------
// Name: Vessels::Release
// Desc: Release the sky boxes from the device used to create them
// Retn: bool - true if released successfully
// ----------------------------------------------------------------------------
bool Vessels::Release()
{
    if (!m_device)
        return true;

    if (m_pgroup_node)
    {
        for (uint i = 0; i < m_pgroup_node->GetNumChildren(); i++)
            delete m_pgroup_node->GetChild(i)->GetUserData();

        delete m_pgroup_node;
    } // if

    m_device = 0;
    return true;
} // Release


// ----------------------------------------------------------------------------
// Name: Vessels::Simulate
// Desc: Simulate the vessels
// Parm: float dt - the delta time
// ----------------------------------------------------------------------------
void Vessels::Simulate(float dt)
{
    if (!m_pgroup_node)
        return;

    for (uint i = 0; i < m_pgroup_node->GetNumChildren(); i++)
    {
        Node *pnode         = m_pgroup_node->GetChild(i);
        MovingVessel *psim  = static_cast<MovingVessel *>(pnode->GetUserData());

        if (i == 0)
        {
            if (GetAsyncKeyState(VK_UP))
                psim->SetThrottle(1);
            else
                psim->SetThrottle(0);

            if (GetAsyncKeyState(VK_LEFT))
                psim->SetSteer(1);
            else if (GetAsyncKeyState(VK_RIGHT))
                psim->SetSteer(-1);
            else
                psim->SetSteer(0);
        } // if

        psim->Simulate(dt, static_cast<DCS *>(pnode)->GetMatrix());
        static_cast<DCS *>(pnode)->GetMatrix()._43 -= 2.0f;
    } // for
} // Simluate


// ----------------------------------------------------------------------------
// Name: Vessels::AddToRenderBin
// Desc: Render the ocean
// ----------------------------------------------------------------------------
void Vessels::Render()
{
    if (m_pgroup_node)
    {
        m_cull_trav.Reset();
        m_cull_trav.Traverse(m_pgroup_node);
    } // if
} // Render


// ----------------------------------------------------------------------------
// Name: Vessels::Add
// Desc: Add a vessel to the list
// Parm: VesselType type - the vessel type
// Parm: float x         - the x position
// Parm: float y         - the y position
// Parm: float h         - the heading
// ----------------------------------------------------------------------------
bool Vessels::Add(const char *name, VesselType type, float x, float y, float h, Player *pplayer)
{
    if (!m_pgroup_node)
        return false;

    std::string filename = "";
    switch (type)
    {
        case Vessels::WOODEN_CANNOE: filename = VESSEL_NAME_CANNOE;  break;
        case Vessels::YACHT:         filename = VESSEL_NAME_YACHT;   break;
        case Vessels::SEA_DOO:       filename = VESSEL_NAME_SEA_DOO; break;
        default: return false;
    } // switch

    // Load the ASE file
    ASELoader::RecordSet records;
    if (!ASELoader::LoadFile(filename.c_str(), records, ASELoader::PROJ_LH, ASELoader::WIND_CW, m_device))
        return false;

    // Create the geoset
    GeoSet *pgeoset = new GeoSet();
    if (!pgeoset->LoadFromASE(records, true))
    {
        delete pgeoset;
        return false;
    } // if

    // Apply a new shader to the sea-doo object from the geoset
    Mesh *pmesh = pgeoset->FindMesh("Sea_Doo_Me");
    if (pmesh)
    {
        uint curr_id = pgeoset->FindMeshMaterial("Sea_Doo_Me");
        MaterialCache::Record rec = MaterialCache::GetMaterial(curr_id);

        uint new_id  = MaterialCache::CreateMaterial(
            rec.tex_map0, rec.tex_map1, rec.tex_map2, SEA_DOO_SHADER, FX_TEX0, true);
        
        pgeoset->SetMeshMaterial(pmesh, new_id);
    } // if

    // Create the geode
    Geode *pgeode = new Geode(name);
    pgeode->AddGeoSet(pgeoset);

    // Create the physics sim
    MovingVessel *psim = new MovingVessel();
    psim->SetHull(Vec2(-0.5, -1), Vec2(0.5, -1), Vec2(-0.5, 1), Vec2(0.5, 1));
    psim->Initialise(x, y, h);
    psim->SetPlayer(pplayer);

    // Create the DCS
    DCS *pdcs_node = new DCS(name);
    pdcs_node->GetMatrix().Identity();
    pdcs_node->AddChild(pgeode);
    pdcs_node->SetUserData(psim);
    
    // Add the DCS to the scene
    m_pgroup_node->AddChild(pdcs_node);

    // Done
    return true;
} // Add


const Matrix &Vessels::GetMatrix(const char *name)
{
    std::string vessel_name = name;
    for (uint i = 0; i < m_pgroup_node->GetNumChildren(); i++)
    {
        Node *pnode = m_pgroup_node->GetChild(i);

        if (pnode->GetName() == vessel_name)
            return (static_cast<DCS *>(pnode))->GetMatrix();
    } // for

    return Matrix::GetIdentityRef();
} // GetMatirx


float Vessels::GetHeading(const char *name)
{
    std::string vessel_name = name;
    for (uint i = 0; i < m_pgroup_node->GetNumChildren(); i++)
    {
        Node *pnode = m_pgroup_node->GetChild(i);

        if (pnode->GetName() == vessel_name)
        {
            MovingVessel *psim  = static_cast<MovingVessel *>(pnode->GetUserData());
            return psim->GetHeading();
        } // if
    } // for

    return 0.0f;
} // GetMatirx


float Vessels::GetSpeed(const char *name)
{
    std::string vessel_name = name;
    for (uint i = 0; i < m_pgroup_node->GetNumChildren(); i++)
    {
        Node *pnode = m_pgroup_node->GetChild(i);

        if (pnode->GetName() == vessel_name)
        {
            MovingVessel *psim  = static_cast<MovingVessel *>(pnode->GetUserData());
            return psim->GetSpeed();
        } // if
    } // for

    return 0.0f;
} // GetSpeed



bool Vessels::GetOnWater(const char *name)
{
    std::string vessel_name = name;
    for (uint i = 0; i < m_pgroup_node->GetNumChildren(); i++)
    {
        Node *pnode = m_pgroup_node->GetChild(i);

        if (pnode->GetName() == vessel_name)
        {
            MovingVessel *psim  = static_cast<MovingVessel *>(pnode->GetUserData());
            return psim->GetOnWater();
        } // if
    } // for

    return false;
} // GetOnWater


// -- EOF

