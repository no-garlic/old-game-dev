// ----------------------------------------------------------------------------
// File: ParticleEmitter.cpp
// Desc: Generic particle system
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "ParticleSystem/ParticleEmitter.h"
#include "Engine/Camera.h"
#include "Engine/Material.h"
#include "Math/Matrix.h"
#include "Math/Color.h"
#include "Common/Logging.h"


// ----------------------------------------------------------------------------
// Name: ParticleEmitter::ParticleEmitter
// Desc: Default constructor
// Parm: const char *name - the name of the emitter
// ----------------------------------------------------------------------------
ParticleEmitter::ParticleEmitter(const std::string &name)
{
    m_name          = name;
    m_device        = 0;
    m_max_particles = 0;
    m_release_rate  = 0;
    m_position      = Vec3(0.0f, 0.0f, 0.0f);
} // ParticleEmitter


// ----------------------------------------------------------------------------
// Name: ParticleEmitter::~ParticleEmitter
// Desc: Destructor
// ----------------------------------------------------------------------------
ParticleEmitter::~ParticleEmitter()
{
    Release();
} // ~ParticleEmitter


// ----------------------------------------------------------------------------
// Name: ParticleEmitter::Create
// Desc: Create the particles
// Parm: LPDIRECT3DDEVICE9 device - the device
// Parm: uint max_particles       - the number of particles
// Retn: bool                     - true if successful
// ----------------------------------------------------------------------------
bool ParticleEmitter::Create(LPDIRECT3DDEVICE9 device, uint max_particles)
{
    Release();

    m_device        = device;
    m_max_particles = max_particles;

    m_particles.resize(max_particles);
    m_verticies.resize(max_particles * 4);

    Mesh_IndexVertArray::FaceVec faces;
    faces.resize(max_particles * 2);

    for (uint i = 0; i < max_particles; i++)
    {
        m_verticies[(i * 4) + 0].loc.Set(0.0f, 0.0f, 0.0f);
        m_verticies[(i * 4) + 0].norm.Set(0.0f, 0.0f, 1.0f);
        m_verticies[(i * 4) + 0].diff = Color::White;
        m_verticies[(i * 4) + 0].u    = 0.98f;
        m_verticies[(i * 4) + 0].v    = 0.98f;

        m_verticies[(i * 4) + 1].loc.Set(0.0f, 0.0f, 0.0f);
        m_verticies[(i * 4) + 1].norm.Set(0.0f, 0.0f, 1.0f);
        m_verticies[(i * 4) + 1].diff = Color::White;
        m_verticies[(i * 4) + 1].u    = 0.98f;
        m_verticies[(i * 4) + 1].v    = 0.02f;

        m_verticies[(i * 4) + 2].loc.Set(0.0f, 0.0f, 0.0f);
        m_verticies[(i * 4) + 2].norm.Set(0.0f, 0.0f, 1.0f);
        m_verticies[(i * 4) + 2].diff = Color::White;
        m_verticies[(i * 4) + 2].u    = 0.02f;
        m_verticies[(i * 4) + 2].v    = 0.02f;

        m_verticies[(i * 4) + 3].loc.Set(0.0f, 0.0f, 0.0f);
        m_verticies[(i * 4) + 3].norm.Set(0.0f, 0.0f, 1.0f);
        m_verticies[(i * 4) + 3].diff = Color::White;
        m_verticies[(i * 4) + 3].u    = 0.02f;
        m_verticies[(i * 4) + 3].v    = 0.98f;

        faces[(i * 2) + 0].Assign((i * 4) + 0, (i * 4) + 1, (i * 4) + 3);
        faces[(i * 2) + 1].Assign((i * 4) + 1, (i * 4) + 2, (i * 4) + 3);

        m_particles[i] = CreateParticle();
        m_particles[i]->Reset();
    } // for

    m_pmesh = new Mesh_IndexVertArray(m_name.c_str(), device, m_verticies, faces, true);
    return true;
} // Create


// ----------------------------------------------------------------------------
// Name: ParticleEmitter::Release
// Desc: Release the particles
// ----------------------------------------------------------------------------
void ParticleEmitter::Release()
{
    if (!m_device)
        return;

    delete m_pmesh;
    m_pmesh = 0;

    for (uint i = 0; i < m_particles.size(); i++)
        delete m_particles[i];
    m_particles.clear();    

    m_device = 0;
} // Release


// ----------------------------------------------------------------------------
// Name: ParticleEmitter::Simulate
// Desc: Simulate the particles
// Parm: float dt - the frame time
// ----------------------------------------------------------------------------
void ParticleEmitter::Simulate(float dt)
{
    // Return if we dont have a valid mesh
    if (!m_pmesh)
        return;

    // Work out how many particles to release this frame
    uint num_to_release = static_cast<uint>(dt * m_release_rate);
    uint total_alive    = 0;

    // Get the look vector
    const Vec3 &look  = CameraSingleton::Instance().GetLook();

    // Calculate the view oriented co-ordinates    
    float theta = atan2f(look[1], look[0]);
    float x     = sinf(-theta);
    float y     = cosf(-theta);

    // Simulate all particles and update the vertex vector
    for (uint i = 0; i < m_max_particles; i++)
    {
        Particle &particle = *(m_particles[i]);

        // Update the particle for this frame time
        if (!particle.Update(dt))
        {
            // If the particle died, release it as a new
            // particle unless we have already released our quota for
            // this frame.
            if (num_to_release > 0)
            {
                // Bring the particle to life
                ReleaseParticle(particle, m_position);
                --num_to_release;
            } // if
            else
            {
                // Released our quota, this particle 
                // stays dead for now.
                continue;
            } // else
        } // if

        // Update the particles coordinates to 
        // orient it to the camera
        m_verticies[(total_alive * 4) + 0].loc  = Vec3(-x * particle.size, -y * particle.size, particle.size) + particle.position;
        m_verticies[(total_alive * 4) + 1].loc  = Vec3(-x * particle.size, -y * particle.size, -particle.size) + particle.position;
        m_verticies[(total_alive * 4) + 2].loc  = Vec3(x * particle.size, y * particle.size, -particle.size) + particle.position;
        m_verticies[(total_alive * 4) + 3].loc  = Vec3(x * particle.size, y * particle.size, particle.size) + particle.position;

        // Update the particles color
        m_verticies[(total_alive * 4) + 1].diff = particle.color;
        m_verticies[(total_alive * 4) + 0].diff = particle.color;
        m_verticies[(total_alive * 4) + 2].diff = particle.color;
        m_verticies[(total_alive * 4) + 3].diff = particle.color;

        ++total_alive;
    } // for

    // Update the vertex buffer in hardware
    Mesh_IndexVertArray::Vertex *verts;
    m_pmesh->LockVertexBuffer(&verts, D3DLOCK_DISCARD);
    memcpy(verts, &(m_verticies[0]), m_max_particles * sizeof(Mesh_IndexVertArray::Vertex) * 4);
    m_pmesh->UnlockVertexBuffer(false);
    m_pmesh->SetDrawFaces(total_alive * 2);
    m_pmesh->SetDrawVerts(total_alive * 4);
} // Simulate


// ----------------------------------------------------------------------------
// Name: ParticleEmitter::Render
// Desc: Render all particles
// Parm: const Matrix &world_matrix - the world matrix
// ----------------------------------------------------------------------------
void ParticleEmitter::Draw()
{
    // Reset the world matrix
    m_device->SetTransform(D3DTS_WORLD, &Matrix::GetIdentityRef());

    // Draw the mesh
    m_pmesh->Draw();
} // Draw


// -- EOF

