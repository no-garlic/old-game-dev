
#ifndef __STD_PROFILE_H_
#define __STD_PROFILE_H_


#include "stdType.h"
#include "stdTimer.h"


// ----------------------------------------------------------------------------
// Duration to capture samples before an average is calculated
// ----------------------------------------------------------------------------
#define PROFILE_SAMPLE_DURATION 0.2f


// ----------------------------------------------------------------------------
// The profile Id's that are supported
// ----------------------------------------------------------------------------
enum ProfileID
{
  PROFILE_FRAME     = 0,    // Frame time
  PROFILE_APP       = 1,    // App time
  PROFILE_CULL      = 2,    // Cull time
  PROFILE_DRAW      = 3,    // Draw tine
  PROFILE_MAX       = 4
};


#if STATS

// ----------------------------------------------------------------------------
// Defines to use the profiler
// ----------------------------------------------------------------------------
#define PROFILE_START(id)         stdProfile::GetProfiler(id).Start();
#define PROFILE_STOP(id)          stdProfile::GetProfiler(id).Stop();
#define PROFILE_RESET_ALL         stdProfile::ResetAllProfilers();
#define PROFILE_TIME(id)          stdProfile::GetProfiler(id).GetSeconds();
#define PROFILE_RENDER_CALLS(x)   stdProfileRender::ProfileAddRenderCalls(x);
#define PROFILE_VERTS(x)          stdProfileRender::ProfileAddVerts(x);
#define PROFILE_FACES(x)          stdProfileRender::ProfileAddFaces(x);
#define PROFILE_STATE_CHANGES(x)  stdProfileRender::ProfileAddStateChanges(x);
#define PROFILE_GET_RENDER_CALLS  stdProfileRender::ProfileGetRenderCalls()
#define PROFILE_GET_VERTS         stdProfileRender::ProfileGetVerts()
#define PROFILE_GET_FACES         stdProfileRender::ProfileGetFaces()
#define PROFILE_GET_STATE_CHANGES stdProfileRender::ProfileGetStateChanges()

#else // !STATS

// ----------------------------------------------------------------------------
// Defines that are no-ops when stats are disabled
// ----------------------------------------------------------------------------
#define PROFILE_START(id)         ;
#define PROFILE_STOP(id)          ;
#define PROFILE_RESET_ALL         ;
#define PROFILE_TIME(id)          0.0f
#define PROFILE_RENDER_CALLS(x)   ;
#define PROFILE_VERTS(x)          ;
#define PROFILE_FACES(x)          ;
#define PROFILE_STATE_CHANGES(x)  ;
#define PROFILE_GET_RENDER_CALLS  0
#define PROFILE_GET_VERTS         0
#define PROFILE_GET_FACES         0
#define PROFILE_GET_STATE_CHANGES 0

#endif // !STATS


// ----------------------------------------------------------------------------
// Profiler class for general timing
// ----------------------------------------------------------------------------
class stdProfile
{
public:
  // --------------------------------------------------------------------------
  // Constructor
  // --------------------------------------------------------------------------
  stdProfile();

  // --------------------------------------------------------------------------
  // Start, stop, and reset the profiler
  // --------------------------------------------------------------------------
  inline void Start();
  inline void Stop();
  void Reset();

  // --------------------------------------------------------------------------
  // Get the current profiler time
  // --------------------------------------------------------------------------
  inline float GetSeconds();

  // --------------------------------------------------------------------------
  // Get the singleton instance
  // --------------------------------------------------------------------------
  static stdProfile &GetProfiler(int id);
  static float GetProfileTime();
  static void ResetAllProfilers();

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  Timer   m_Timer;        // The timer
  float   m_Time;         // The time since the last calc
  float   m_Accum;        // The accumulated time since the last calc
  float   m_timeStamp;    // The time of the last calc
  uint    m_Samples;      // The number of samples since the last calc

};


// ----------------------------------------------------------------------------
// Profiler class for specific render timimgs
// ----------------------------------------------------------------------------
class stdProfileRender
{
public:
  // --------------------------------------------------------------------------
  // Static members
  // --------------------------------------------------------------------------
  static uint   s_RenderCalls;
  static uint   s_Verts;
  static uint   s_Faces;
  static uint   s_StateChanges;
  static uint   s_RenderCallsAccum;
  static uint   s_VertsAccum;
  static uint   s_FacesAccum;
  static uint   s_StateChangesAccum;
  static float  s_timeStamp;
  static uint   s_Frames;

  // --------------------------------------------------------------------------
  // Add render stats
  // --------------------------------------------------------------------------
  static void ProfileAddRenderCalls(uint count)   { s_RenderCallsAccum  += count; }
  static void ProfileAddVerts(uint count)         { s_VertsAccum        += count; }
  static void ProfileAddFaces(uint count)         { s_FacesAccum        += count; }
  static void ProfileAddStateChanges(uint count)  { s_StateChangesAccum += count; }

  // --------------------------------------------------------------------------
  // Get render stats
  // --------------------------------------------------------------------------
  static uint ProfileGetRenderCalls()             { return s_RenderCalls;   }
  static uint ProfileGetVerts()                   { return s_Verts;         }
  static uint ProfileGetFaces()                   { return s_Faces;         }
  static uint ProfileGetStateChanges()            { return s_StateChanges;  }

  // --------------------------------------------------------------------------
  // Reset all stats
  // --------------------------------------------------------------------------
  static void ResetAll();
};



// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
inline stdProfile::stdProfile()
{
  m_Time = 0.0f;
  m_Accum = 0.0f;
  m_Samples = 0;
  m_timeStamp = 0.0f;
  m_Timer.Reset();
}


// ----------------------------------------------------------------------------
// Start the timer
// ----------------------------------------------------------------------------
inline void stdProfile::Start()
{
  m_Timer.Start();
}


// ----------------------------------------------------------------------------
// Stop the timer
// ----------------------------------------------------------------------------
inline void stdProfile::Stop()
{
  m_Timer.Stop();
}


// ----------------------------------------------------------------------------
// Get the profiler time
// ----------------------------------------------------------------------------
inline float stdProfile::GetSeconds()
{
  return m_Time;
}


#endif // __STD_PROFILE_H_

// -- EOF


