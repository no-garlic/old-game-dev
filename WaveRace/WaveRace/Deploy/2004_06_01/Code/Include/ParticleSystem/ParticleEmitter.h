// ----------------------------------------------------------------------------
// File: ParticleEmitter.h
// Desc: Generic particle system
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _PARTICLE_SYSTEM_H
#define _PARTICLE_SYSTEM_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Types.h"
#include "Engine/Mesh_IndexVertArray.h"


// ----------------------------------------------------------------------------
// Name: ParticleEmitter (class)
// Desc: Generic particle system
// ----------------------------------------------------------------------------
class ParticleEmitter
{
public:
    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
             ParticleEmitter(const std::string &name = "");
    virtual ~ParticleEmitter();


    // ------------------------------------------------------------------------
    // Memory functions
    // ------------------------------------------------------------------------
    virtual bool    Create(LPDIRECT3DDEVICE9 device, uint max_particles);
    virtual void    Release();


    // ------------------------------------------------------------------------
    // Public interface
    // ------------------------------------------------------------------------
    void            SetReleaseRate(uint rate)     { m_release_rate = rate; }
    void            SetPosition(const Vec3 &pos)  { m_position    = pos;   }
    void            Simulate(float dt);
    virtual void    Render() = 0;


protected:
    // ------------------------------------------------------------------------
    // Name: Particle (struct)
    // Desc: Our particle
    // ------------------------------------------------------------------------
    struct Particle
    {
        // --------------------------------------------------------------------
        // Constructor and destructor
        // --------------------------------------------------------------------
                 Particle() {}
        virtual ~Particle() {}


        // --------------------------------------------------------------------
        // Particle functions
        // --------------------------------------------------------------------
        virtual bool Update(float dt) = 0;
        virtual void Reset(const Vec3 &pos = Vec3()) = 0;


        // --------------------------------------------------------------------
        // Public interface to update the verticies
        // --------------------------------------------------------------------
        Vec3    position;
        Color   color;
        float   size;


        // --------------------------------------------------------------------
        // Life information
        // --------------------------------------------------------------------
        float   age;
        float   life;
        bool    alive;

    }; // struct Particle


    // ------------------------------------------------------------------------
    // Protected functions
    // ------------------------------------------------------------------------
    void Draw();


    // ------------------------------------------------------------------------
    // Virtual functions
    // ------------------------------------------------------------------------
    virtual void        ReleaseParticle(Particle &particle, const Vec3 &position) = 0;
    virtual Particle   *CreateParticle() = 0;


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    LPDIRECT3DDEVICE9               m_device;
    std::string                     m_name;
    uint                            m_max_particles;
    uint                            m_release_rate;
    Mesh_IndexVertArray            *m_pmesh;
    std::vector<Particle *>         m_particles;
    Mesh_IndexVertArray::VertexVec  m_verticies;
    Vec3                            m_position;


}; // class ParticleEmitter


#endif // _PARTICLE_SYSTEM_H

// -- EOF

