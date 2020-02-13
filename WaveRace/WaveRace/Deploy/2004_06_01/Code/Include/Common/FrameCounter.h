// ----------------------------------------------------------------------------
// File: FrameCounter.h
// Desc: This class handles all timing functionality. This includes counting the
//       number of frames per second, to scaling vectors and values relative to 
//       the time that has passed since the previous frame.
// Auth: Michael Petrou
// Note: Thanks to Adam Hoult & Gary Simmons from GameInstitute.com for the 
//       great code that was so easily adapted to work in my application.
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef FRAME_COUNTER_H
#define FRAME_COUNTER_H


// ----------------------------------------------------------------------------
// FrameCounter specific includes
// ----------------------------------------------------------------------------
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <D3DX9.h>


// ----------------------------------------------------------------------------
// Cap the number of samples taken per second
// ----------------------------------------------------------------------------
const ULONG MAX_SAMPLE_COUNT = 50;


// ----------------------------------------------------------------------------
// Name: FrameCounter (class)
// Desc: Timer class, queries performance hardware if available, and calculates 
//       all the various values required for frame rate based vector / value 
//       scaling.
// ----------------------------------------------------------------------------
class FrameCounter
{
public:
    // ------------------------------------------------------------------------
    // Constructors & Destructors for this class
    // ------------------------------------------------------------------------
	         FrameCounter();
	virtual ~FrameCounter();


    //-------------------------------------------------------------------------
	// Public functions for this class
	//-------------------------------------------------------------------------
	void	        Tick(float fLockFPS = 0.0f);
    unsigned long   GetFrameRate(LPTSTR lpszString = 0) const;
    float           GetTimeElapsed() const;

private:
	//-------------------------------------------------------------------------
	// Private Variables for this class
	//-------------------------------------------------------------------------
    bool            m_PerfHardware;             // Has Performance Counter
	float           m_TimeScale;                // Amount to scale counter
	float           m_TimeElapsed;              // Time elapsed since previous frame
    __int64         m_CurrentTime;              // Current Performance Counter
    __int64         m_LastTime;                 // Performance Counter last frame
	__int64         m_PerfFreq;                 // Performance Frequency

    float           m_FrameTime[MAX_SAMPLE_COUNT];
    ULONG           m_SampleCount;

    unsigned long   m_FrameRate;                // Stores current framerate
	unsigned long   m_FPSFrameCount;            // Elapsed frames in any given second
	float           m_FPSTimeElapsed;           // How much time has passed during FPS sample
}; // FrameCounter


#endif // FRAME_COUNTER_H

// -- EOF

