// ----------------------------------------------------------------------------
// File: MovingVessel.cpp
// Desc: Models the movement of a moving vessel
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Sound files
// ----------------------------------------------------------------------------
#define IDLE_SOUND_FILE     "idle.wav"
#define STOP_SOUND_FILE     "stop.wav"
#define DRIVE_SOUND_FILE    "drive.wav"


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/Logging.h"
#include "Physics/MovingVessel.h"
#include "GameObject/Wave.h"
#include "GameObject/Terrain.h"


// ----------------------------------------------------------------------------
// Name: MovingVessel::MovingVessel
// Desc: Constructor
// ----------------------------------------------------------------------------
MovingVessel::MovingVessel()
{
    // Initialise the members
    m_pplayer           = 0;
    m_curr_zval         = 0.0f;
    m_curr_buoyency     = 0.0f;
    m_curr_steer        = 0.0f;
    m_curr_heading      = 0.0f;
    m_pitch             = 0.0f;
    m_camera_heading    = 0.0f;
    m_heading_update    = true;
    m_throttle          = 0;
    m_steer             = 0;
    m_velocity          = 0.0f;
    m_on_water          = true;
    m_frame             = 0;

    // Default hull is 2 square meters
    m_hull_v1.Set(-1.0f, -1.0f);
    m_hull_v2.Set(-1.0f, 1.0f);
    m_hull_v3.Set(1.0f, -1.0f);
    m_hull_v4.Set(1.0f, 1.0f);

    // Set the defaults
    m_position.Set(0.0f, 0.0f);
    m_curr_normal.Set(0.0f, 0.0f, 0.0f);
    m_curr_momentum.Set(0.0f, 0.0f);

    // Initialise the sounds
    m_psound_idle = SoundEngineSingleton::Instance().LoadSoundObject(IDLE_SOUND_FILE);
    m_psound_idle->SetLoop(true);
    m_psound_idle->Play();
    m_psound_drive = SoundEngineSingleton::Instance().LoadSoundObject(DRIVE_SOUND_FILE);
    m_psound_drive->SetLoop(true);
    m_psound_drive->SetGain(0.0f);
    m_psound_drive->Play();
    m_psound_stop = SoundEngineSingleton::Instance().LoadSoundObject(STOP_SOUND_FILE);
    m_psound_stop->SetLoop(false);
} // MovingVessel


// ----------------------------------------------------------------------------
// Name: MovingVessel::~MovingVessel
// Desc: Destructor
// ----------------------------------------------------------------------------
MovingVessel::~MovingVessel()
{
    m_psound_drive->Stop();
    m_psound_idle->Stop();
    m_psound_stop->Stop();

    delete m_psound_drive;
    delete m_psound_idle;
    delete m_psound_stop;
} // ~MovingVessel


// ----------------------------------------------------------------------------
// Name: MovingVessel::SetPlayer
// Desc: Set the player that follows this vessel
// Parm: Player *pplayer - the player
// ----------------------------------------------------------------------------
void MovingVessel::SetPlayer(Player *pplayer)
{
    m_pplayer = pplayer;
} // SetPlayer


// ----------------------------------------------------------------------------
// Name: MovingVessel::SetHull
// Desc: Set the control points of the hull that are used to determine how the 
//       vessel floats on the water.  The points are x, y positions relative to 
//       the origin of the vessel's 3d model
// Parm: const Vec2 &v1  - the first point
// Parm: const Vec2 &v2  - the second point
// Parm: const Vec2 &v3  - the third point
// Parm: const Vec2 &v4  - the fourth point
// ----------------------------------------------------------------------------
void MovingVessel::SetHull(const Vec2 &v1, const Vec2 &v2, const Vec2 &v3, const Vec2 &v4)
{
    m_hull_v1   = v1;
    m_hull_v2   = v2;
    m_hull_v3   = v3;
    m_hull_v4   = v4;
} // SetHull


// ----------------------------------------------------------------------------
// Name: MovingVessel::Initialise
// Desc: Initialise the vessel
// Parm: float x        - the x position
// Parm: float y        - the y position
// Parm: float heading  - the heading
// ----------------------------------------------------------------------------
void MovingVessel::Initialise(float x, float y, float heading)
{
    m_curr_heading = heading;
    m_position.Set(x, y);
    m_frame = 0;
} // Initialise


// ----------------------------------------------------------------------------
// Name: MovingVessel::SetThrottle
// Desc: Set the throttle position
// Parm: int throttle - the throtle position
// ----------------------------------------------------------------------------
void MovingVessel::SetThrottle(int throttle)
{
    if (m_throttle != throttle)
    {
        m_throttle = throttle;

        if (!throttle)
        {
            m_psound_stop->SetGain(m_velocity);
            m_psound_stop->Play();
        } // if
        else
        {
            m_psound_stop->Stop();
        } // else

    } // if
        
} // SetThrottle


// ----------------------------------------------------------------------------
// Name: MovingVessel::SetSteer
// Desc: Set the steering position
// Parm: int steer - the steering amount (+ to left)
// ----------------------------------------------------------------------------
void MovingVessel::SetSteer(int steer)
{
    m_steer = steer;
} // SetSteer


// ----------------------------------------------------------------------------
// Name: MovingVessel::Simulate
// Desc: Simulate the vessel for this frame
// Parm: float dt   - the frame time
// Parm: Matrix &m  - the matrix to set at the vessel position
// ----------------------------------------------------------------------------
void MovingVessel::Simulate(float dt, Matrix &m)
{
    // Simulate the vessel's motion
    InternalSimulateWave(dt);
    InternalSimulateDrift(dt);
    InternalSimulateMotion(dt);

    // Set the vessels world matrix
    m.Identity();
    m.Translation(m_position[0], m_position[1], m_curr_zval + 0.25f + fabs(m_pitch * 0.35f));
    m.PostMultiply(Matrix::MakeNewRotationAxis(m_curr_normal, D3DX_PI));
    m.PostMultiply(Matrix::MakeNewRotationAxis(Vec3(0.0f, 0.0f, 1.0f), m_curr_heading - HALF_PI));
    m.PostMultiply(Matrix::MakeNewRotationAxis(Vec3(0.0f, 1.0f, 0.0f), m_pitch * 1.5f));
    m.PostMultiply(Matrix::MakeNewRotationAxis(Vec3(-1.0f, 0.0f, 0.0f), 
        (m_velocity * 0.135f) - fabs(m_curr_steer * 4.0f)));
    
    // If the player is set, update the players position
    if (m_pplayer)
    {
        const float distance_above          = 1.75f;
        const float angle_down              = 0.0f;
        const float camera_update_rate      = 8.5f;
        const float min_camera              = 2.0f;
        const float max_camera              = 10.0f;
        const float distance_behind_rate    = 5.0f;
        const float distance_behind_min     = 4.0f;
        const float min_injection           = 0.05f;
        const float injection_point         = 5.0f;
        const float injection_amount        = 0.25f;

        // Calculate the distance behind the vessel based on the 
        // speed of the vessel
        float distance_behind = distance_behind_rate * m_velocity;
        Utility::Clamp<float>(distance_behind, 0.0f, distance_behind_min);
        distance_behind += distance_behind_min;

        // Work out the heading difference between the camera
        // and the vessel (euler angles - yuk).
        float delta_heading = fmodf(m_curr_heading - m_camera_heading, 360.0f);

        // We only begin the move the camera once we have more than
        // 10 degrees between the heading of the camera and the heading 
        // of the vessel.
        if (delta_heading > max_camera && !m_heading_update)
            m_heading_update = true;

        // We stop moving the camera when the camera's heading is within 
        // 2 degrees of the vessel's heading
        if (delta_heading < min_camera && m_heading_update)
            m_heading_update = false;

        // We move the camera at a factor of time, so it is smooth
        m_camera_heading += (delta_heading * dt * camera_update_rate);

        // Update the camera position using x = d sin(theta), y = d cos(theta)
        // and always stay just above the vessel.
        m_pplayer->SetPosition(
            m_position[0] + (cosf(m_camera_heading) * distance_behind), 
            m_position[1] + (sinf(m_camera_heading) * distance_behind),
            (0.0f - distance_above) + m_curr_zval);

        // Rotate the camera (again, euler angles - yuk).
        m_pplayer->SetRotate(-90.0f + angle_down, -90.0f + D3DXToDegree(-m_camera_heading), 0.0f);

        // Inject some ripple into the water at the bow of the boat.
        CDAWaveSingleton::Instance().InjectRipple(
            m_position[0] - (cos(m_curr_heading) * 3.5f), 
            m_position[1] - (sin(m_curr_heading) * 3.5f),
            injection_amount + (injection_amount * m_velocity));

        // If we are moving we inject some ripple into the water at the
        // sides of the bow also so we get a nice bow wave.
        if (m_velocity > min_injection && m_on_water)
        {
            float delta_heading = D3DXToRadian(5.0f);

            CDAWaveSingleton::Instance().InjectRipple(
                m_position[0] - (cos(m_curr_heading - delta_heading) * injection_point), 
                m_position[1] - (sin(m_curr_heading - delta_heading) * injection_point),
                (injection_amount * m_velocity));

            CDAWaveSingleton::Instance().InjectRipple(
                m_position[0] - (cos(m_curr_heading + delta_heading) * injection_point), 
                m_position[1] - (sin(m_curr_heading + delta_heading) * injection_point),
                (injection_amount * m_velocity));
        } // if
    } // if

    // Sound gain params
    const float gain_max = 15.0f;
    const float drive_gain_min  = 0.2f;
    const float idle_gain_min   = 1.0f;

    // Update the sound's volume
    float steer_gain = fabs(m_curr_steer * gain_max);
    m_psound_drive->SetGain(drive_gain_min + m_velocity + steer_gain);
    m_psound_idle->SetGain(idle_gain_min + (steer_gain * m_velocity));
} // Simulate


// ----------------------------------------------------------------------------
// Name: MovingVessel::InternalSimulateWave
// Desc: Simulate the vessels position due to the wave height and normal, and 
//       the terrain height and normal
// Parm: float dt - the frame time
// ----------------------------------------------------------------------------
void MovingVessel::InternalSimulateWave(float dt)
{
    // Get the CDA wave instance
    CDAWave &wave = CDAWaveSingleton::Instance();

    // Hold the wave normal and height at the 4
    // defined hull positions.
    Vec3    normal[4];
    float   z_val[4];

    // Get the water normal and wave height
    Vec2 pos;
    pos.Add(m_position, m_hull_v1); wave.GetWaveHeight(pos[0], pos[1], z_val[0], normal[0]);
    pos.Add(m_position, m_hull_v2); wave.GetWaveHeight(pos[0], pos[1], z_val[1], normal[1]);    
    pos.Add(m_position, m_hull_v3); wave.GetWaveHeight(pos[0], pos[1], z_val[2], normal[2]);    
    pos.Add(m_position, m_hull_v4); wave.GetWaveHeight(pos[0], pos[1], z_val[3], normal[3]);

    // The ideal normal and wave height is the average of the 4 values returned
    Vec3  ideal_normal = (normal[0] + normal[1] + normal[2] + normal[3]) / 4.0f;
    float ideal_zval   = (z_val[0]  + z_val[1]  + z_val[2]  + z_val[3])  / 4.0f;

    // We test the terrain collision every second frame unless
    // we are not on the water (we are on the terrain)
    if (!m_on_water || m_frame % 2 == 0)
    {
        // Get the terrain normal and land height
        float terrain_z = ideal_zval;
        Vec3  terrain_normal;
        TerrainSingleton::Instance().GetTerrainHeight(
            m_position[0], m_position[1], terrain_z, terrain_normal);

        // If the terrain is higher than water, we have gone 
        // off-course and hit the land
        if (terrain_z < ideal_zval)
        {
            // Force us to follow the terrain height
            m_curr_zval     = terrain_z;

            // We are not on the water
            ideal_zval      = terrain_z;
            ideal_normal    = terrain_normal;
            m_on_water      = false;
        } // if
        else
        {
            // We are on the water
            m_on_water      = true;
        } // else
    } // else

    // At this point, we have the ideal z value, and the 
    // ideal normal.  We now use that data to perform
    // our physics calcs.

    // Dont tilt the boat too much (pitch or roll)
    float limit = 0.1f;
    if (m_on_water)
        limit = 0.01f;

    // Clamp us to the limit, but smooth it out a little
    float &nx = ideal_normal[0];
    float &ny = ideal_normal[1];
    if (nx > limit)
        nx = limit + (nx * 0.01f * dt);
    else if (nx < -limit)
        nx = -(limit + (nx * 0.01f * dt));
    if (ny > limit)
        ny = limit + (ny * 0.01f * dt);
    else if (ny < -limit)
        ny = -(limit + (ny * 0.01f * dt));

    // If this is the first frame, we reset these
    // values to 0.  Can be used to reset the boat's 
    // dynamics at some point during the game.
    if (m_frame == 0)
    {
        m_curr_normal       = ideal_normal;
        m_curr_momentum     = Vec2(0.0f, 0.0f);
        m_curr_zval         = ideal_zval;
        m_curr_buoyency     = 0.0f;
    } // if
    else
    {
        // Calculate the normal for the orientation in x, y axis
        // for the vessel
        Vec3 delta_normal = m_curr_normal - ideal_normal;
        Vec2 new_momentum(delta_normal[0], delta_normal[1]);

        // Slow us down when we hit the terrain and when 
        // we get the wobbles.
        if (!m_on_water)
        {
            new_momentum.Scale(new_momentum, dt * 10.0f);
        } // if
        else if (new_momentum[0] + new_momentum[1] > 2.5f)
        {
            new_momentum.Scale(new_momentum, dt * 35.0f);
        } // else

        // Begin to move towards our new pitch and roll
        m_curr_momentum.Lerp(m_curr_momentum, new_momentum, dt * 0.5f);
        m_curr_normal -= Vec3(m_curr_momentum[0], m_curr_momentum[1], 0.0f);

        // Calculate the height of the vessel in the wave
        float delta_z = m_curr_zval - ideal_zval;
        if (delta_z > 0.0f)
            m_curr_buoyency += (delta_z * 0.0005f / dt);
        else
            m_curr_buoyency += (delta_z * 0.0001f / dt);

        // TODO -> This is not variable frame rate safe !!
        m_curr_buoyency *= 0.9f;

        m_curr_zval -= m_curr_buoyency;
    } // else

    m_frame++;
} // InternalSimulateWave



// ----------------------------------------------------------------------------
// Name: MovingVessel::InternalSimulateDrift
// Desc: Simulate the vessel drifting based on the normal
// Parm: float dt - the frame time
// ----------------------------------------------------------------------------
void MovingVessel::InternalSimulateDrift(float dt)
{
    // Move the vessel based on the wave washing
    // against the hull, or sliding down terrain
    Vec2 delta_pos = Vec2(m_curr_normal[0], m_curr_normal[1]) * dt * 5.0f;
    m_position.Add(m_position, delta_pos);
} // InternalSimulateDrift


// ----------------------------------------------------------------------------
// Name: MovingVessel::InternalSimulateMotion
// Desc: Simulate the steering and power of the vessel
// Parm: float dt - the frame time
// ----------------------------------------------------------------------------
void MovingVessel::InternalSimulateMotion(float dt)
{
    const float velocity_decay_rate         = 0.35f;    // ms-1
    const float velocity_steer_decay_rate   = 0.275f;   // ms-1
    const float velocity_increase_rate      = 0.65f;    // ms-1
    const float min_velocity                = 0.0002f;  // ms-1
    const float max_velocity                = 1.0f;     // ms-1

    // Drag force
    m_velocity -= (velocity_decay_rate * dt);

    // Slow when we steer
    if (m_steer)
        m_velocity -= (velocity_steer_decay_rate * dt);

    if (m_steer && m_velocity > 0.5f)
        m_velocity -= (velocity_steer_decay_rate * dt);

    // Thrust
    m_velocity += (velocity_increase_rate * m_throttle * dt);

    // Keep us within the velocity bonuds
    if (m_on_water)
        Utility::Clamp<float>(m_velocity, min_velocity, max_velocity);
    else
        Utility::Clamp<float>(m_velocity, min_velocity, 0.1f + (m_velocity * 0.2f));

    const float max_steer   = 0.04f;
    const float steer_inc   = 0.16f;
    const float steer_dec   = 0.09f;

    // Steering
    float steer_rate = (dt * m_steer * steer_inc * (0.75f + (m_velocity * 0.4f)));

    if (m_throttle)
        m_curr_steer += steer_rate;
    else
        m_curr_steer += (steer_rate * 0.75f);

    if (m_curr_steer > 0.0f)
    {
        m_curr_steer -= (dt * steer_dec);
        Utility::Clamp<float>(m_curr_steer, 0.0f, max_steer);
    } // if
    else
    {
        m_curr_steer += (dt * steer_dec);
        Utility::Clamp<float>(m_curr_steer, -max_steer, 0.0f);
    } // else

    m_curr_heading += m_curr_steer;

    // Pitch and roll the vessel
    if (m_throttle)
    {
        float pitch_delta = (m_pitch - (m_curr_steer * 6.5f)) * 0.2f;
        m_pitch -= pitch_delta;
    } // if
    else
    {
        float pitch_delta = (m_pitch - (m_curr_steer * 5.0f)) * 0.2f;
        m_pitch -= pitch_delta;
    } // else

    if (!m_on_water)
        m_pitch *= 0.9f;

    // Reposition the vessel based on the heading 
    // and velocity
    Vec2 delta_pos = Vec2(m_velocity * cosf(m_curr_heading), m_velocity * sinf(m_curr_heading));
    m_position.Subtract(m_position, delta_pos.Scale(delta_pos, 2.0f));

} // InternalSimulateMotion


// -- EOF
