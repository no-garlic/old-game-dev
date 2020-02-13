// ----------------------------------------------------------------------------
// File: WakeParticleEmitter.h
// Desc: Particle emitter type for the jet ski wake
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _WAKE_PARTICLE_EMITTER_H_
#define _WAKE_PARTICLE_EMITTER_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "ParticleSystem/ParticleEmitter.h"


// ----------------------------------------------------------------------------
// Name: WakeParticleEmitter  (class)
// Desc: Particle emitter for the wake of the boat
// ----------------------------------------------------------------------------
class WakeParticleEmitter : public ParticleEmitter
{
public:
    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
             WakeParticleEmitter();
    virtual ~WakeParticleEmitter();


    // ------------------------------------------------------------------------
    // Memory functions
    // ------------------------------------------------------------------------
    virtual bool    Create(LPDIRECT3DDEVICE9 device, uint num_particles);
    virtual void    Release();


    // ------------------------------------------------------------------------
    // Public functions
    // ------------------------------------------------------------------------
    void            SetVelocity(const Vec3 &vel) { m_velocity = vel;    }
    void            SetSpeed(float speed)        { m_speed = speed;     }
    void            SetHeading(float heading)    { m_heading = heading; }
    virtual void    Render();


protected:
    struct WakeParticle : public ParticleEmitter::Particle
    {
        // --------------------------------------------------------------------
        // Constructor and destructor
        // --------------------------------------------------------------------
                    WakeParticle() {}
        virtual    ~WakeParticle() {}


        // --------------------------------------------------------------------
        // Particle functions
        // --------------------------------------------------------------------
        virtual bool Update(float dt);
        virtual void Reset(const Vec3 &pos = Vec3());


        // --------------------------------------------------------------------
        // Members
        // --------------------------------------------------------------------
        Vec3        velocity;
        float       speed;

    }; // struct WakeParticle


    // ------------------------------------------------------------------------
    // Protected functions
    // ------------------------------------------------------------------------
    virtual void        ReleaseParticle(Particle &particle, const Vec3 &position);
    virtual Particle   *CreateParticle();


private:
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    uint        m_material_id;
    Vec3        m_velocity;
    Matrix      m_matrix;
    float       m_speed;
    uint        m_tex_id;
    float       m_heading;


}; // class WakeParticleEmitter


#endif // _WAKE_PARTICLE_EMITTER_H_

// -- EOF

