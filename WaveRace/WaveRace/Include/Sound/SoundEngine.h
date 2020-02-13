// ----------------------------------------------------------------------------
// File: SoundEngine.h
// Desc: Implementation of 'SoundEngine' using OpenAL. OpenAL, like OpenGL, uses
//       a right handed coordinate system, where in a frontal default view X (
//       thumb) points right, Y points up (index finger), and Z points out of 
//       the screen. 
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _OPENAL_SOUND_ENGINE_H_
#define _OPENAL_SOUND_ENGINE_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Types.h"
#include "Math/Vec3.h"
#include "Common/Utilities.h"


// ----------------------------------------------------------------------------
// OpenAL includes
// ----------------------------------------------------------------------------
#include <alc.h>
#include <altypes.h>
#include <alut.h>


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class SoundEngine;
class SoundObject;


// ----------------------------------------------------------------------------
// Singleton accessor
// ----------------------------------------------------------------------------
typedef Singleton::SingletonHolder<SoundEngine, 
        Singleton::CreateUsingNew<SoundEngine> > SoundEngineSingleton;


// ----------------------------------------------------------------------------
// Name: SoundEngine  (class)
// Desc: Implementation of a spatial sound engine using OpenAL
// ----------------------------------------------------------------------------
class SoundEngine
{   
private:
    // ------------------------------------------------------------------------
    // Allow the singleton to create the class
    // ------------------------------------------------------------------------
    friend struct Singleton::CreateUsingNew<SoundEngine>;


    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
     SoundEngine()  { m_Loaded = false; }
    ~SoundEngine()  { Unload();         }


public:
    // ------------------------------------------------------------------------
    // Load the sound engine. Must be called before all other methods, and 
    // Unload the sound engine
    // ------------------------------------------------------------------------
    bool Load();
    void Unload();


    // ------------------------------------------------------------------------
    // Set the listener position, velocity, and orientation (in degrees)
    // ------------------------------------------------------------------------
    void SetListenerPosition(Vec3 p_Position);
    void SetListenerVelocity(Vec3 p_Velocity);
    void SetListenerOrientation(float p_Yaw, float p_Pitch, float p_Roll);


    // ------------------------------------------------------------------------
    // Create a new sound object and load it. Returns non-NULL on success, NULL 
    // on failure
    // ------------------------------------------------------------------------
    SoundObject* LoadSoundObject(const char *p_Filename);       

private:
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    ALCcontext *m_pContext;     // Sound engine context
    ALCdevice  *m_pDevice;      // Sound engine device
    bool        m_Loaded;       // Has the sound engine been loaded?


}; // class SoundEngine


// ----------------------------------------------------------------------------
// Name: SoundObject  (class)
// Desc: Implementation of a single sound including spatial and audio 
//       information
// ----------------------------------------------------------------------------
class SoundObject
{   
protected:
    // ------------------------------------------------------------------------
    // Protected constructor to ensure that only the SoundEngine can create 
    // instances of this class
    // ------------------------------------------------------------------------
    SoundObject()   { m_Loaded = false; }

    
    // ------------------------------------------------------------------------
    // Load the sound. The sound is loaded by the SoundEngine on creation
    // Unload the sound. The sound is unloaded by the deconstructor
    // ------------------------------------------------------------------------
    bool Load(const char *p_Filename);
    void Unload();

public:
    // ------------------------------------------------------------------------
    // Destructor
    // ------------------------------------------------------------------------
    ~SoundObject()  { Unload(); }                   


    // ------------------------------------------------------------------------
    // Set the position and velocity of the object
    // ------------------------------------------------------------------------
    void SetPosition(Vec3 p_Position);
    void SetVelocity(Vec3 p_Velocity);

    
    // ------------------------------------------------------------------------
    // Set if the sound loops, and set the gain of the sound. Must be >= 1
    // ------------------------------------------------------------------------
    void SetLoop(bool p_Loop);
    void SetGain(float p_Gain);

    
    // ------------------------------------------------------------------------
    // Play and Stop the sound
    // ------------------------------------------------------------------------
    void Play();
    void Stop();


    // ------------------------------------------------------------------------
    // Define the SoundEngine as a friend of this class
    // ------------------------------------------------------------------------
    friend SoundEngine;


private:
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    bool    m_Loaded;        // Has the buffer been loaded?
    ALuint  m_Buffer[1];     // The sound buffer
    ALuint  m_Source[1];     // The sound source


}; // class SoundObject


#endif // _OPENAL_SOUND_ENGINE_H_

// -- EOF
