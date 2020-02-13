// ----------------------------------------------------------------------------
// File: SkyBox.cpp
// Desc: Manages a number of sky boxes
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "GameObject/SkyBox.h"
#include "Engine/Mesh_IndexVertArray.h"
#include "Engine/Camera.h"
#include "Engine/RenderBin.h"
#include "Engine/ASE.h"


// ----------------------------------------------------------------------------
// Skybox names
// ----------------------------------------------------------------------------
#define  SKYBOX_NAME_SUNNY      "new_sky.asb"
#define  SKYBOX_NAME_CLOUDY     "new_sky.asb"
#define  SKYBOX_NAME_STORMY     "new_sky.asb"


// ----------------------------------------------------------------------------
// Name: SkyBox::SkyBox
// Desc: Constructor
// ----------------------------------------------------------------------------
SkyBox::SkyBox()
{
    m_type      = SKY_NONE;
    m_device    = 0;

    m_psunny    = 0;
    m_pcloudy   = 0;
    m_pstormy   = 0;
} // SkyBox


// ----------------------------------------------------------------------------
// Name: SkyBox::~SkyBox
// Desc: Destructor
// ----------------------------------------------------------------------------
SkyBox::~SkyBox()
{
    Release();
} // ~SkyBox


// ----------------------------------------------------------------------------
// Name: SkyBox::Create
// Desc: Create the sky boxes
// Parm: LPDIRECT3DDEVICE9 device - the device to load the skyboxes with
// Retn: bool                     - true if all loaded successfully
// ----------------------------------------------------------------------------
bool SkyBox::Create(LPDIRECT3DDEVICE9 device)
{
    Release();
    m_device = device;

    ASELoader::RecordSet records;
    if (!ASELoader::LoadFile(SKYBOX_NAME_SUNNY, records, ASELoader::PROJ_LH, ASELoader::WIND_CW, device))
        return false;
    m_psunny = new Object(device, records);
    records.clear();

    if (!ASELoader::LoadFile(SKYBOX_NAME_CLOUDY, records, ASELoader::PROJ_LH, ASELoader::WIND_CW, device))
        return false;
    m_pcloudy= new Object(device, records);
    records.clear();

    if (!ASELoader::LoadFile(SKYBOX_NAME_STORMY, records, ASELoader::PROJ_LH, ASELoader::WIND_CW, device))
        return false;
    m_pstormy = new Object(device, records);
    records.clear();

    return true;
} // Create


// ----------------------------------------------------------------------------
// Name: SkyBox::Release
// Desc: Release the sky boxes from the device used to create them
// Retn: bool - true if released successfully
// ----------------------------------------------------------------------------
void SkyBox::Release()
{
    if (!m_device)
        return;

    delete m_psunny;
    m_psunny = 0;

    delete m_pcloudy;
    m_pcloudy = 0;

    delete m_pstormy;
    m_pstormy = 0;

    m_device = 0;
} // Release


// ----------------------------------------------------------------------------
// Name: SkyBox::Select
// Desc: Select a particular sky box to be rendered
// Parm: SkyBox::SkyBoxType type - the sky box to select
// ----------------------------------------------------------------------------
void SkyBox::Select(SkyBox::SkyBoxType type)
{
    m_type = type;
} // Select


// ----------------------------------------------------------------------------
// Name: SkyBox::Simulate
// Desc: Animate the sky box
// Parm: float run_time - the time
// ----------------------------------------------------------------------------
void SkyBox::Simulate(float run_time)
{
    m_heading = run_time * 0.015f;
} // Simulate


// ----------------------------------------------------------------------------
// Name: SkyBox::Render
// Desc: Render the sky box
// ----------------------------------------------------------------------------
void SkyBox::Render()
{
    Object *pobject = 0;

    switch (m_type)
    {
    case SKY_SUNNY:
        pobject = m_psunny;
        break;
    case SKY_CLOUDY:
        pobject = m_pcloudy;
        break;
    case SKY_STORMY:
        pobject = m_pstormy;
        break;
    default:
        return;
    } // switch


    Matrix m;
    m.Translation(CameraSingleton::Instance().GetPosition());
    m.PostMultiply(Matrix::MakeNewRotationYawPitchRoll(0.0f, 0.0f, m_heading));
    pobject->AddToRenderBin(m);    
} // Render


// -- EOF

