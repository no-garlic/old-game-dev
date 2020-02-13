
// Include the header file for the OpenAL implementation
#include "Sound/SoundEngine.h"
#include "Sound/SoundEngineMath.h"
#include "Common/Logging.h"
#include "Common/FilePath.h"


// Includes required for OpenAL
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <alc.h>
#include <altypes.h>
#include <alut.h>
#include <memory.h>
#include <windows.h>
#include <math.h>

using namespace SpatialSound;



// Load the sound.
// The sound is loaded by the SoundEngine on creation
bool SoundObject::Load(const char *p_Filename)
{
    if (m_Loaded)
    {
        LOG_ERROR << "Sound already loaded" << ENDLOG;
        return (false);
    }   


    std::string fn = FilePathSingleton::Instance().FindFile(std::string(p_Filename));
    if (fn.empty())
    {
        LOG_ERROR << "Failed to locate the sound file: " << p_Filename << ENDLOG;
        return false;
    } // if

    // temp variables
    ALint     iError;
    ALsizei   iSize;
    ALsizei   iFreq;
    ALenum    eFormat;
    ALvoid   *pData;
    ALboolean bLoop;

    // generate the sound buffer
    alGenBuffers(1, m_Buffer);
    iError = alGetError();
    if (iError != AL_NO_ERROR)
    {
        LOG_ERROR << "Could not generate sound buffer" << ENDLOG;
        return (false);
    }   

    // need to convert from 'const char*' to 'ALbyte*' for alutLoadWAVFile()
    ALbyte *alFilename;
    alFilename = (ALbyte*)(fn.c_str());

    // load the wave file   
    alutLoadWAVFile(alFilename, &eFormat, &pData, &iSize, &iFreq, &bLoop);
    iError = alGetError();
    if (iError != AL_NO_ERROR)
    {
        LOG_ERROR << "Could not load sound file" << ENDLOG;
        // delete the buffer
        alDeleteBuffers(1, m_Buffer);
        return (false);
    }

    // copy wave data in to the buffer
    alBufferData(m_Buffer[0], eFormat, pData, iSize, iFreq);
    iError = alGetError();
    if (iError != AL_NO_ERROR)
    {
        LOG_ERROR << "Could not copy wave data. Does the sound file exist?" << ENDLOG;
        // delete the buffer
        alDeleteBuffers(1, m_Buffer);
        return (false);
    }

    // unload the wave data
    alutUnloadWAV(eFormat, pData, iSize, iFreq);
    iError = alGetError();
    if (iError != AL_NO_ERROR)
    {
        LOG_ERROR << "Could not free the wave data" << ENDLOG;
        // delete the buffer
        alDeleteBuffers(1, m_Buffer);
        return (false);
    }

    // create the source
    alGenSources(1, m_Source);
    iError = alGetError();
    if (iError != AL_NO_ERROR)
    {
        LOG_ERROR << "Could not generate sound source" << ENDLOG;
        // delete the buffer
        alDeleteBuffers(1, m_Buffer);
        return (false);
    }

    // assign the buffer to the source
    alSourcei(m_Source[0], AL_BUFFER, m_Buffer[0]);
    if (iError != AL_NO_ERROR)
    {
        LOG_ERROR << "Could not assign buffer to sound source" << ENDLOG;
        // delete the buffer
        alDeleteBuffers(1, m_Buffer);
        return (false);
    }

    // success
    m_Loaded = true;
    return (true);
}


// Unload the sound.
// The sound is unloaded by the deconstructor
void SoundObject::Unload()
{
    if (m_Loaded)
    {
        ALint iError;

        alDeleteSources(1, m_Source);
        iError = alGetError();
        if (iError != AL_NO_ERROR)
        {
            LOG_ERROR << "Could not cleanup sound source" << ENDLOG;
        }
        
        alDeleteBuffers(1, m_Buffer);
        iError = alGetError();
        if (iError != AL_NO_ERROR)
        {
            LOG_ERROR << "Could not cleanup sound buffer" << ENDLOG;
        }

        m_Loaded = false;
    }
}


// Set the position of the object
void SoundObject::SetPosition(Vec3 p_Position)
{
    ALfloat vec[3] = {p_Position.x, p_Position.y, p_Position.z};

    alSourcefv(m_Source[0], AL_POSITION, vec);

    ALint iError;
    iError = alGetError();
    if (iError != AL_NO_ERROR)
    {
        LOG_ERROR << "Could not set sound position" << ENDLOG;
    }
}


// Set the velocity of the object
void SoundObject::SetVelocity(Vec3 p_Velocity)
{
    ALfloat vec[3] = {p_Velocity.x, p_Velocity.y, p_Velocity.z};

    alSourcefv(m_Source[0], AL_VELOCITY, vec);

    ALint iError;
    iError = alGetError();
    if (iError != AL_NO_ERROR)
    {
        LOG_ERROR << "Could not set sound velocity" << ENDLOG;
    }
}


// Set if the sound loops
void SoundObject::SetLoop(bool p_Loop)
{   
    alSourcei(m_Source[0], AL_LOOPING, p_Loop ? AL_TRUE : AL_FALSE);

    ALint iError;
    iError = alGetError();
    if (iError != AL_NO_ERROR)
    {
        LOG_ERROR << "Could not set sound loop setting" << ENDLOG;
    }   
}


// Set the gain of the sound.
// Must be >= 1
void SoundObject::SetGain(float p_Gain)
{
    alSourcef(m_Source[0], AL_GAIN, p_Gain);

    ALint iError;
    iError = alGetError();
    if (iError != AL_NO_ERROR)
    {
        LOG_ERROR << "Could not set sound gain" << ENDLOG;
    }
}


// Play the sound
void SoundObject::Play()
{
    //alSourcef(m_Source[0], AL_ROLLOFF_FACTOR, 0.0f);
    alSourcePlay(m_Source[0]);
}


// Stop the sound
void SoundObject::Stop()
{
    alSourceStop(m_Source[0]);
}



// Load the sound engine.
// Must be called before all other methods
bool SoundEngine::Load()
{
    if (m_Loaded)
    {
        LOG_ERROR << "Sound engine already loaded" << ENDLOG;
        return (false);
    }

    // open the device (init OpenAL)
    m_pDevice = alcOpenDevice((ALubyte*)"DirectSound3D");
    if (NULL == m_pDevice)
    {
        LOG_ERROR << "Failed to initialise OpenAL sound engine" << ENDLOG;
        return (false);
    }

    // create context
    m_pContext = alcCreateContext(m_pDevice, NULL);
    
    // set active context
    alcMakeContextCurrent(m_pContext);

    // clear error code
    alGetError();

    // engine now loaded
    m_Loaded = true;

    // return success 
    return (true);
}

        
// Unload the sound engine
void SoundEngine::Unload()
{
    // if the engine is not loaded just return
    if (!m_Loaded)
    {
        return;
    }   

    // disable context
    alcMakeContextCurrent(NULL);

    // release context
    alcDestroyContext(m_pContext);

    // close device
    alcCloseDevice(m_pDevice);

    // now unloaded
    m_Loaded = false;
}


// Set the listener position
void SoundEngine::SetListenerPosition(Vec3 p_Position)
{
    if (m_Loaded)
    {   
        ALfloat vec[3];
        vec[0] = p_Position.x;
        vec[1] = p_Position.y;
        vec[2] = p_Position.z;      
        alListenerfv(AL_POSITION, vec);

        ALint error;
        error = alGetError();
        if (error != AL_NO_ERROR)
        {
            LOG_ERROR << "SetListenerPosition() failed" << ENDLOG;
        }
    }
}

        
// Set the listener velocity
void SoundEngine::SetListenerVelocity(Vec3 p_Velocity)
{
    if (m_Loaded)
    {   
        ALfloat vec[3] = {p_Velocity.x, p_Velocity.y, p_Velocity.z};
        
        alListenerfv(AL_VELOCITY, vec);

        ALint error;
        error = alGetError();
        if (error != AL_NO_ERROR)
        {
            LOG_ERROR << "SetListenerVelocity() failed" << ENDLOG;
        }
    }
}


// Set the listener orientation (degrees)
void SoundEngine::SetListenerOrientation(float p_Yaw, float p_Pitch, float p_Roll)
{
    // define the default view orientation vectors here 
    c_Vector3 at(0.0f, 0.0f, -1.0f); // looking at this position from (0.0f, 0.0f, 0.0f)
    c_Vector3 up(0.0f, 1.0f, 0.0f);  // this is a vector 'coming out of the viewers head' pointing up

    // get the quaternion for the euler rotation
    c_Quaternion q = QuaternionEulerRotation(p_Yaw * DEG2RAD, p_Pitch * DEG2RAD, p_Roll * DEG2RAD);

    // convert quaternion to 3x3 matrix
    c_Matrix3x3 m;
    q.MatrixRep(&m);

    // multiply the at and up vectors by the rotation matrix to get the final result
    at = m * at;
    up = m * up;

    // generate the 1x6 vector for OpenAL (at then up)
    ALfloat orientation[6] = {at.x, at.y, at.z, up.x, up.y, up.z};

    // set the orientation
    alListenerfv(AL_ORIENTATION, orientation);

    ALint error;
    error = alGetError();
    if (error != AL_NO_ERROR)
    {
        LOG_ERROR << "SetListenerOrientation() failed" << ENDLOG;   
    }
}

// Create a new sound object and load it.
// Returns non-NULL on success, NULL on failure
SoundObject* SoundEngine::LoadSoundObject(const char *p_Filename)
{
    // create the sound object
    SoundObject *pNew;
    pNew = new SoundObject();
    if (NULL == pNew)
    {
        LOG_ERROR << "Out of memory creating new SoundObject" << ENDLOG;
        return (NULL);
    }

    // attempt to load the sound object
    if (!pNew->Load(p_Filename))
    {
        LOG_ERROR << "Failed to Load new SoundObject" << ENDLOG;
        delete (pNew);
        return (NULL);
    }

    // return the successfully created and loaded sound
    return (pNew);
}       

// -- EO