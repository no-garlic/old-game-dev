// ----------------------------------------------------------------------------
// File: MovingVessel.h
// Desc: Models the movement of a moving vessel
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _MOVING_VESSEL_H_
#define _MOVING_VESSEL_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include "GameObject/Player.h"
#include "Sound/SoundEngine.h"
#include "Math/Types.h"
#include "Math/Vec2.h"
#include "Math/Vec3.h"


// ----------------------------------------------------------------------------
// Name: MovingVessel (class)
// Desc: Models the movement of a moving vessel
// ----------------------------------------------------------------------------
class MovingVessel
{
public:
    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
     MovingVessel();
    ~MovingVessel();


    // ------------------------------------------------------------------------
    // Setup functions
    // ------------------------------------------------------------------------
    void    SetHull(const Vec2 &v1, const Vec2 &v2, const Vec2 &v3, const Vec2 &v4);
    void    Initialise(float x, float y, float heading);
    void    Simulate(float dt, Matrix &m);


    // ------------------------------------------------------------------------
    // Reporting
    // ------------------------------------------------------------------------
    float   GetHeading() { return m_curr_heading; }
    float   GetSpeed()   { return m_velocity;     }
    bool    GetOnWater() { return m_on_water;     }


    // ------------------------------------------------------------------------
    // Drive the vessel
    // ------------------------------------------------------------------------
    void    SetThrottle(int throttle);  // 0 == off, -ve == rev,  +ve == fwd
    void    SetSteer(int steer);        // 0 == off, -ve == left, +ve == right
    void    SetPlayer(Player *pplayer);


private:
    // ------------------------------------------------------------------------
    // Private functions
    // ------------------------------------------------------------------------
    void    InternalSimulateWave(float dt);
    void    InternalSimulateDrift(float dt);
    void    InternalSimulateMotion(float dt);


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    SoundObject    *m_psound_stop;      // Sound for stopping
    SoundObject    *m_psound_idle;      // Sound for idle engine
    SoundObject    *m_psound_drive;     // Sound for driving

    Vec2            m_hull_v1;          // hull intersection point 1
    Vec2            m_hull_v2;          // hull intersection point 2
    Vec2            m_hull_v3;          // hull intersection point 3
    Vec2            m_hull_v4;          // hull intersection point 4

    Vec2            m_position;         // (x, y) position of vessel
    float           m_curr_zval;        // z position of vessel
    float           m_curr_buoyency;    // Current bouyency (z axis)
    Vec3            m_curr_normal;      // Current orientation of vessel
    Vec2            m_curr_momentum;    // Current momentum vector of vessel

    float           m_pitch;            // Current pitch of vessel
    float           m_curr_heading;     // Current heading of vessel
    float           m_curr_steer;       // Current steering amount
    int             m_throttle;         // Current throttle position
    int             m_steer;            // Current steering position
    float           m_velocity;         // Current velocity (true heading)

    Player         *m_pplayer;          // Player that attaches the camera
    float           m_camera_heading;   // Current camera heading
    bool            m_heading_update;   // Are we updating the camera

    bool            m_on_water;         // Are we on water, or on land
    uint            m_frame;            // What is the current frame number

}; // class MovingVessel


#endif // _MOVING_VESSEL_H_

// -- EOF
