// ----------------------------------------------------------------------------
// File: wave.h
// Desc: Simulates a wave using the Central Difference Algorithm as demonstrated
//       in Game Gems 1. Portions Copyright (C) Miguel Gomez, 2000.
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _WAVE_H_
#define _WAVE_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Types.h"
#include "Math/Sphere.h"
#include "Math/Vec4.h"
#include "Math/Matrix.h"
#include "Engine/Mesh_IndexTriangleStrip.h"
#include "Engine/Effect.h"
#include "Common/Utilities.h"


// ----------------------------------------------------------------------------
// Create the singleton accessor for this class
// ----------------------------------------------------------------------------
class CDAWave;
using namespace Singleton;
typedef SingletonHolder<CDAWave, CreateUsingNew<CDAWave> > CDAWaveSingleton;


class CDAWave : private Utility::Unique
{
private:
    // ------------------------------------------------------------------------
    // Singleton creation accessor
    // ------------------------------------------------------------------------
    friend struct Singleton::CreateUsingNew<CDAWave>;


    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
                    CDAWave();
    virtual        ~CDAWave();


public:
    // ------------------------------------------------------------------------
    // Memory management
    // ------------------------------------------------------------------------
    bool            Create(LPDIRECT3DDEVICE9 device);
    void            Release();


    // ------------------------------------------------------------------------
    // Simulation and rendering
    // ------------------------------------------------------------------------
    void            Simulate(float t);
    void            Render();


    // ------------------------------------------------------------------------
    // Control the wave swell
    // ------------------------------------------------------------------------
    void            SetSwellEnabled(bool enabled) { m_swell = enabled; }
    void            SetSwellParams (int num_swell_x, int num_swell_y, float swell_speed_x,
                        float swell_speed_y, float swell_height_x, float swell_height_y);


    // ------------------------------------------------------------------------
    // Control the CDA (central difference apporximation) algorithm params
    // ------------------------------------------------------------------------
    void            SetCDAParams(float wave_space, float grid_size, float wave_height);


    // ------------------------------------------------------------------------
    // Control the wave scrolling
    // ------------------------------------------------------------------------
    void            SetScrollEnabled(bool enabled) { m_scroll = enabled; }


    // ------------------------------------------------------------------------
    // Extract data from the wave
    // ------------------------------------------------------------------------
    const Sphere   &GetBounds();
    void            GetWaveHeight(float x, float y, float &zw, Vec3 &nw);
    void            InjectRipple(float x, float y, float h);


private:
    // ------------------------------------------------------------------------
    // Internal functions
    // ------------------------------------------------------------------------
    void            InternalSimulateCDA(float dt);
    void            InternalSimulateSwell(float t);
    void            InternalMoveMesh();


    // ------------------------------------------------------------------------
    // Forward declaration
    // ------------------------------------------------------------------------
    struct          CDAWaveData;


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    LPDIRECT3DDEVICE9           m_device;
    Mesh_IndexTriangleStrip    *m_pmesh;
    Mesh_IndexTriangleStrip    *m_pouter_mesh;
    CDAWaveData                &m_data;
    bool                        m_dirty;
    bool                        m_swell;
    bool                        m_scroll;
    Vec4                        m_camera_rect;
    Matrix                      m_world_mat;

    int                         m_swell_offset_i;
    int                         m_swell_offset_j;
    int                         m_num_swell_x;
    int                         m_num_swell_y;
    float                       m_swell_speed_x;
    float                       m_swell_speed_y;
    float                       m_swell_height_x;
    float                       m_swell_height_y;
    float                       m_last_update_time;

    uint                        m_material_id;
    Sphere                      m_sphere;
}; // class CDAWave


#endif // _WAVE_H_

// -- EOF
