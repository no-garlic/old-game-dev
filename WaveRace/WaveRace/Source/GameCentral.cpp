// ----------------------------------------------------------------------------
// File: GameCentral.cpp
// Desc: Central management for the game state and behaviour
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Defines (to be moved into configuration files)
// ----------------------------------------------------------------------------
#define MUSIC_FILE      "music.wav"
#define TERRAIN_FILE    "terrain.asb"
#define BUOY_POS_FILE   "buoys.pos"
#define MAX_PARTICLES   2000


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "GameCentral.h"
#include "Engine/Material.h"
#include "Engine/RenderBin.h"
#include "Engine/ASE.h"
#include "Engine/Camera.h"
#include "Math/Matrix.h"
#include "Math/Intersect.h"
#include "Res/resource.h"
#include "Common/Logging.h"
#include "Common/FilePath.h"
#include "GameObject/SkyBox.h"
#include "GameObject/Vessels.h"
#include "GameObject/Terrain.h"
#include "GameObject/CourseManager.h"
#include "GameObject/Wave.h"


// ----------------------------------------------------------------------------
// Name: GameCentral::GameCentral
// Desc: Constructor
// ----------------------------------------------------------------------------
GameCentral::GameCentral()
{
    m_device        = 0;
    m_pmusic        = 0;
    m_volume        = 0.5f;
} // GameCentral


// ----------------------------------------------------------------------------
// Name: GameCentral::~GameCentral
// Desc: Destructor
// ----------------------------------------------------------------------------
GameCentral::~GameCentral()
{
    Release();
    delete m_pmusic;
} // ~GameCentral


// ----------------------------------------------------------------------------
// Name: GameCentral::Init
// Desc: Initialise the game (once)
// ----------------------------------------------------------------------------
void GameCentral::Init()
{
    // Set the players position
    m_player.SetRotate(-90.0f, 0.0f, 0.0f);
    m_player.Move(Player::DIR_UP, 2.0f);

    // Set the camera projection
    CameraSingleton::Instance().SetProjPerspectiveLH(60, (4.0f / 3.0f), 1.0f, 950.0f);

    // Setup the file paths
    FilePathSingleton::MakeInstance();
    FilePathSingleton::Instance().Add(".");
    FilePathSingleton::Instance().Add("./Shaders");
    FilePathSingleton::Instance().Add("./Data");
    FilePathSingleton::Instance().Add("./Exported/Sound");
    FilePathSingleton::Instance().Add("./Exported/SkyBox");
    FilePathSingleton::Instance().Add("./Exported/Terrain");
    FilePathSingleton::Instance().Add("./Exported/Vessels");
    FilePathSingleton::Instance().Add("./Exported/Buoys");
    FilePathSingleton::Instance().Add("./Exported/Wave");
} // Init


SoundObject *g_psound5 = 0;

// ----------------------------------------------------------------------------
// Name: GameCentral::Create
// Desc: Create the game objects
// Parm: LPDIRECT3DDEVICE9 device - the device
// Retn: bool                     - true if all succeeded
// ----------------------------------------------------------------------------
bool GameCentral::Create(LPDIRECT3DDEVICE9 device)
{
    Release();
    m_device = device;

    // Start the sound engine
    if (!SoundEngineSingleton::Instance().Load())
    {
        LOG_ERROR << "Failed to load the sound engine" << ENDLOG;
        return false;
    } // if

    if (!MaterialCache::Create(m_device))
    {
        LOG_ERROR << "Failed to create the default materials" << ENDLOG;
        return false;
    } // if

    m_pmusic = SoundEngineSingleton::Instance().LoadSoundObject(MUSIC_FILE);
    if (!m_pmusic)
    {
        LOG_WARNING << "Failed to load the sound: " << MUSIC_FILE << ENDLOG;
    } // if
    else
    {
        m_pmusic->SetLoop(true);
        m_pmusic->SetGain(m_volume);
        m_pmusic->Play();
    } // else

    // Create the wave
    if (!CDAWaveSingleton::Instance().Create(m_device))
    {
        LOG_ERROR << "Failed to create the wave" << ENDLOG;
        return false;
    } // if
    CDAWaveSingleton::Instance().SetScrollEnabled(true);
    CDAWaveSingleton::Instance().SetSwellParams(2, 15, 0.55f, 1.5f, 0.175f, 0.075f);

    // Create the terrain
    if (!TerrainSingleton::Instance().Create(TERRAIN_FILE, m_device))
    {
        LOG_ERROR << "Failed to create the terrain" << ENDLOG;
        return false;
    } // if

    // Create the vessel manager
    if (!VesselsSingleton::Instance().Create(m_device))
    {
        LOG_ERROR << "Failed to create the vessels" << ENDLOG;
        return false;
    } // if

    // Add our main vessel
    if (!VesselsSingleton::Instance().Add("sea-doo", Vessels::SEA_DOO, -368.0f, 355.0f, 0.0f, &m_player))
    {
        LOG_ERROR << "Failed to create the sea-doo" << ENDLOG;
        return false;
    } // if

    // Create the sky box
    if (!SkyBoxSingleton::Instance().Create(m_device))
    {
        LOG_ERROR << "Failed to create the vessels" << ENDLOG;
        return false;
    } // if
    SkyBoxSingleton::Instance().Select(SkyBox::SKY_CLOUDY);

    // Create the particle systems
    if (!m_particle_emitter.Create(device, MAX_PARTICLES))
    {
        LOG_ERROR << "Failed to create the particle system" << ENDLOG;
        return false;
    } // if
    m_particle_emitter.SetReleaseRate(0);

    // Load the course
    if (!CourseManagerSingleton::Instance().Create(m_device, BUOY_POS_FILE))
    {
        LOG_ERROR << "Failed to create the buoys" << ENDLOG;
        return false;
    } // if

    // Done
    return true;
} // Create


// ----------------------------------------------------------------------------
// Name: GameCentral::Release
// Desc: Release all game objects
// ----------------------------------------------------------------------------
void GameCentral::Release()
{
    if (!m_device)
        return;

    // Release all game objects
    CDAWaveSingleton::Instance().Release();
    TerrainSingleton::Instance().Release();
    VesselsSingleton::Instance().Release();
    SkyBoxSingleton::Instance().Release();
    CourseManagerSingleton::Instance().Release();
    m_particle_emitter.Release();

    MaterialCache::Release();
    TextureCache::Clear();

    m_device = 0;
} // Release


// ----------------------------------------------------------------------------
// Name: GameCentral::SetGlobalState
// Desc: Set the global state (once per new device)
// ----------------------------------------------------------------------------
void GameCentral::SetGlobalState()
{
    if (!m_device)
        return;

    // Set the global render states
    m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    m_device->SetRenderState(D3DRS_LIGHTING, FALSE);
    m_device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
} // SetGlobalState


// ----------------------------------------------------------------------------
// Name: GameCentral::AnimateObjects
// Desc: Animate objects prior to rendering
// Parm: float run_time    - the engine running time
// Parm: float frame_time  - the time since the last frame
// ----------------------------------------------------------------------------
void GameCentral::AnimateObjects(float run_time, float frame_time)
{
    // Simulate the wave
    CDAWaveSingleton::Instance().Simulate(run_time);

    // Simulate the vessel
    VesselsSingleton::Instance().Simulate(frame_time);

    // Simulate the sky box
    SkyBoxSingleton::Instance().Simulate(run_time);

    // Simulate the particle system
    const Matrix &mat   = VesselsSingleton::Instance().GetMatrix("sea-doo");
    float heading       = VesselsSingleton::Instance().GetHeading("sea-doo");
    float speed         = VesselsSingleton::Instance().GetSpeed("sea-doo");
    bool  on_water      = VesselsSingleton::Instance().GetOnWater("sea-doo");

    // Set the particle system release rate based on the speed of the vessel
    uint  num_particles = static_cast<uint>(speed * 200);
    Utility::Clamp<uint>(num_particles, 10, 100);

    // Create a position vector for the particle system
    Vec3 pos_vec(mat._41, mat._42, mat._43 + 2.0f);
    Vec3 vel_vec(cosf(heading), sinf(heading), 0.0f);

    // Set the particle system's properties
    m_particle_emitter.SetPosition(pos_vec);
    m_particle_emitter.SetVelocity(vel_vec);
    m_particle_emitter.SetHeading(heading);
    m_particle_emitter.SetSpeed(speed);
    m_particle_emitter.SetReleaseRate(on_water ? num_particles : 0);
    m_particle_emitter.Simulate(frame_time);

    // Simulate the buoys
    CourseManagerSingleton::Instance().Simulate(run_time);

    // Update the music volume
    if (m_pmusic)
        if (GetAsyncKeyState(VK_ADD))
            m_pmusic->SetGain(m_volume += 0.05f);
        else if (GetAsyncKeyState(VK_SUBTRACT))
            m_pmusic->SetGain(m_volume -= 0.05f);

} // Simulate


// ----------------------------------------------------------------------------
// Name: GameCentral::RenderObjects
// Desc: Render the scene
// ----------------------------------------------------------------------------
void GameCentral::RenderObjects()
{
    // Disable z test and z write
    m_device->SetRenderState(D3DRS_ZENABLE, FALSE);
    m_device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

    // Render the sky box
    SkyBoxSingleton::Instance().Render();
    RenderBinSingleton::Instance().Render();

    // Enable z test and z write
    m_device->SetRenderState(D3DRS_ZENABLE, TRUE);
    m_device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

    // Render the sky, terrain, and wave
    TerrainSingleton::Instance().Render();
    VesselsSingleton::Instance().Render();
    RenderBinSingleton::Instance().Render();

    // Render the water
    CDAWaveSingleton::Instance().Render();

    // Render the buoys
    CourseManagerSingleton::Instance().Render();
    RenderBinSingleton::Instance().Render();

    // Disable z test
    m_device->SetRenderState(D3DRS_ZENABLE, FALSE);

    // Render the particle systems
    m_particle_emitter.Render();

    // Draw the vessel again with ZTest enabled
    m_device->SetRenderState(D3DRS_ZENABLE, TRUE);
    VesselsSingleton::Instance().Render();
    RenderBinSingleton::Instance().Render();
} // RenderObjects


// -- EOF

