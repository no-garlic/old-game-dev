// ----------------------------------------------------------------------------
// File: WakeParticleEmitter.cpp
// Desc: Particle emitter type for the jet ski wake
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Texture file for our particle
// ----------------------------------------------------------------------------
#define PARTICLE_FILENAME   "splash.tga"


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "ParticleSystem/WakeParticleEmitter.h"
#include "Engine/Material.h"
#include "Engine/Camera.h"
#include "Common/Logging.h"


// ----------------------------------------------------------------------------
// Name: WakeParticleEmitter::WakeParticleEmitter
// Desc: Constructor
// ----------------------------------------------------------------------------
WakeParticleEmitter::WakeParticleEmitter() : ParticleEmitter("Wake")
{
    m_velocity.Set(0.0f, 0.0f, 0.0f);
    m_tex_id        = 0;
    m_speed         = 0.0f;
    m_material_id   = 0;
} // WakeParticleEmitter


// ----------------------------------------------------------------------------
// Name: WakeParticleEmitter::~WakeParticleEmitter
// Desc: Destructor
// ----------------------------------------------------------------------------
WakeParticleEmitter::~WakeParticleEmitter()
{
} // ~WakeParticleEmitter


// ----------------------------------------------------------------------------
// Name: WakeParticleEmitter::Create
// Desc: Create the particles for the device
// Parm: LPDIRECT3DDEVICE9 device - the device
// Parm: uint num_particles       - the max particles
// ----------------------------------------------------------------------------
bool WakeParticleEmitter::Create(LPDIRECT3DDEVICE9 device, uint num_particles)
{
    if (ParticleEmitter::Create(device, num_particles))
    {
        m_tex_id = TextureCache::CreateTexture(PARTICLE_FILENAME, m_device);
        if (m_tex_id == 0)
        {
            LOG_ERROR << "Failed to load the particle texture: " << PARTICLE_FILENAME << ENDLOG;
            return false;
        } // if

        m_material_id = MaterialCache::CreateMaterial(m_tex_id, 0, 0, "WakeEmitter.fx", FX_TEX0, false);
        return true;
    } // if
    
    return false;
} // Create


// ----------------------------------------------------------------------------
// Name: WakeParticleEmitter::Release
// Desc: Release the device
// ----------------------------------------------------------------------------
void WakeParticleEmitter::Release()
{
    ParticleEmitter::Release();
} // Release


// ----------------------------------------------------------------------------
// Name: WakeParticleEmitter::CreateParticle
// Desc: Create a particle
// Retn: ParticleEmitter::Particle * - the new particle
// ----------------------------------------------------------------------------
ParticleEmitter::Particle *WakeParticleEmitter::CreateParticle()
{
    return new WakeParticleEmitter::WakeParticle();
} // CreateParticle


// ----------------------------------------------------------------------------
// Name: WakeParticleEmitter::ReleaseParticle
// Desc: Release a particle - starts it's life
// Parm: Particle &particle    - the particle
// Parm: const Vec3 &position  - the position of the system in world space
// ----------------------------------------------------------------------------
void WakeParticleEmitter::ReleaseParticle(Particle &particle, const Vec3 &position)
{
    WakeParticleEmitter::WakeParticle &p = 
        *((WakeParticleEmitter::WakeParticle *) &particle);

    // Find the tangent to the boat 
    // heading using world space bearings
    float x = sinf(-m_heading);
    float y = cosf(-m_heading);
    float a = sinf(HALF_PI - m_heading) * 2.0f;
    float b = cosf(HALF_PI - m_heading) * 2.0f;

    // Move randomly up or down the tangent
    Vec3 offset(x + a, y + b, 0);
    offset.Scale(offset, Random::FloatRand(-0.35f, 0.35f));
    offset.Add(offset, Vec3(Random::FloatRand(-0.2f, 0.2f), Random::FloatRand(-0.2f, 0.2f), 0.0f));

    // Append the world position of the boat
    p.position.Add(position, offset);

    // Use the position as the baseline for 
    // the velocity vector
    p.velocity.Scale(offset, 0.5f);
    p.velocity[2] = -1.5f;
    p.speed = m_speed;

    // Default color, size, and age
    p.color = Color(1, 1, 1, 1);
    p.size  = 0.75f;
    p.age   = 0;
    
    // Random life
    p.life = 0.5f - m_speed;
    Utility::Clamp(p.life, 0.1f, 0.5f);
    p.alive = true;
} // ReleaseParticle


// ----------------------------------------------------------------------------
// Name: WakeParticleEmitter::WakeParticle::Update
// Desc: Update the particle system
// Parm: float dt - the frame time
// ----------------------------------------------------------------------------
bool WakeParticleEmitter::WakeParticle::Update(float dt)
{
    // Calculate the age
    age += dt;

    // See if the particle should die
    if (age > life)
    {
        alive = false;
        return false;
    } // if

    // Simulate the position based on the velocity vector
    position.Add(position, velocity * dt);

    // Change the size and alpha over time
    float lerp = (age / life) * 0.5f;
    size = 0.95f + lerp;
    color.operator FLOAT *()[3] = 1.0f - lerp;

    // Still alive
    return true;
} // Update


// ----------------------------------------------------------------------------
// Name: WakeParticleEmitter::WakeParticle::Reset
// Desc: Reset a particle
// Parm: const Vec3 &pos - the position
// ----------------------------------------------------------------------------
void WakeParticleEmitter::WakeParticle::Reset(const Vec3 &pos)
{
    position        = pos;
    velocity.Set(0.0f, 0.0f, 0.0f);
    color           = Color(1, 1, 1, 1);
    size            = 1.0f;
    age             = 0;
    life            = Random::FloatRand(0.25f, 0.35f);
    alive           = true;
} // Reset


// ----------------------------------------------------------------------------
// Name: WakeParticleEmitter::Render
// Desc: Render the particle system
// ----------------------------------------------------------------------------
void WakeParticleEmitter::Render()
{

    // Set the default material
    MaterialCache::Apply(0, Matrix::GetIdentityRef(), m_device);

    // Disable antiailasing
    m_device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
    m_device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);

    // Set the texture filter mode
    m_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    m_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    m_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
    m_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
    m_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

    // Get the texture
    LPDIRECT3DTEXTURE9 ptexture = TextureCache::GetTexture(m_tex_id).ptex_file->d3d_tex;

    // Set the texture
    m_device->SetTexture(0, ptexture);
    m_device->SetTexture(1, 0);

    // Modulate between the vertex colours and the texture colour
    m_device->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
    m_device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
    m_device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);

    // Disable material colours
    m_device->SetRenderState(D3DRS_COLORVERTEX, FALSE);

    // Enable alpha blend
    m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    m_device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
    m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    m_device->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
    m_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
    m_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

    // Disable the next stage
    m_device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
    m_device->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

    // Draw the mesh
    //MaterialCache::Apply(m_material_id, Matrix::GetIdentityRef(), m_device);
    Draw();
} // Render


// -- EOF
