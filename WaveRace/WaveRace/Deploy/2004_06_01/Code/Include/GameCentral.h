// ----------------------------------------------------------------------------
// File: GameCentral.h
// Desc: Central management for the game state and behaviour
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _GAME_CENTRAL_H_
#define _GAME_CENTRAL_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include "GameObject/Player.h"
#include "Common/FrameCounter.h"
#include "Common/Timer.h"
#include "Engine/D3DSettingsDlg.h"
#include "Math/Matrix.h"
#include "Math/Sphere.h"
#include "Sound/SoundEngine.h"
#include "Scenegraph/Node.h"
#include "Scenegraph/Group.h"
#include "Scenegraph/CullTraverser.h"
#include "ParticleSystem/WakeParticleEmitter.h"


// ----------------------------------------------------------------------------
// Singleton Accessor
// ----------------------------------------------------------------------------
class GameCentral;
typedef Singleton::SingletonHolder<GameCentral, 
        Singleton::CreateUsingNew<GameCentral> > GameCentralSingleton;


// ----------------------------------------------------------------------------
// Name: GameCentral  (class)
// Desc: Central management for the game state and behaviour
// ----------------------------------------------------------------------------
class GameCentral : private Utility::Unique
{
private:
    // ------------------------------------------------------------------------
    // Allow the singleton holder to construct this class
    // ------------------------------------------------------------------------
    friend struct Singleton::CreateUsingNew<GameCentral>;


    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
             GameCentral();
    virtual ~GameCentral();


public:
    // ------------------------------------------------------------------------
    // Public memory functions
    // ------------------------------------------------------------------------
    bool    Create(LPDIRECT3DDEVICE9 device);
    void    Release();

    
    // ------------------------------------------------------------------------
    // Public functions
    // ------------------------------------------------------------------------
    void    Init();
    void    SetGlobalState();
    void    AnimateObjects(float run_time, float frame_time);
    void    RenderObjects();


private:
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    LPDIRECT3DDEVICE9       m_device;
    Player                  m_player;
    Group                  *m_pscenegraph;
    CullTraverser           m_cull_trav;
    WakeParticleEmitter     m_particle_emitter;
    SoundObject            *m_pmusic;
    float                   m_volume;


}; // class GameCentral


#endif // _GAME_CENTRAL_H_

// -- EOF

