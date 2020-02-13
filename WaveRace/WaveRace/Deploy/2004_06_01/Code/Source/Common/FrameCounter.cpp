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


// ----------------------------------------------------------------------------
// FrameCounter Specific Includes
// ----------------------------------------------------------------------------
#include "Common/FrameCounter.h"


// ----------------------------------------------------------------------------
// Name: FrameCounter::FrameCounter
// Desc: Constructor
// ----------------------------------------------------------------------------
FrameCounter::FrameCounter()
{
	// Query performance hardware and setup time scaling values
	if (QueryPerformanceFrequency((LARGE_INTEGER *) &m_PerfFreq)) 
    { 
		m_PerfHardware		= TRUE;
		QueryPerformanceCounter((LARGE_INTEGER *) &m_LastTime); 
		m_TimeScale			= 1.0f / m_PerfFreq;
	} // if
    else 
    { 
		// no performance counter, read in using timeGetTime 
		m_PerfHardware		= FALSE;
		m_LastTime			= timeGetTime(); 
		m_TimeScale			= 0.001f;
	} // else

	// Clear any needed values
    m_SampleCount       = 0;
	m_FrameRate			= 0;
	m_FPSFrameCount		= 0;
	m_FPSTimeElapsed	= 0.0f;
} // FrameCounter


// ----------------------------------------------------------------------------
// Name: FrameCounter::~FrameCounter
// Desc: Destructor
// ----------------------------------------------------------------------------
FrameCounter::~FrameCounter()
{
} // ~FrameCounter


// ----------------------------------------------------------------------------
// Name: FrameCounter::Tick
// Desc: Function which signals that frame has advanced Note : You can specify a
//       number of frames per second to lock the frame rate to. This will simply
//       soak up the remaining time to hit that target.
// Parm: float fLockFPS - if specified then locks the frame rate to the 
//       specified time
// ----------------------------------------------------------------------------
void FrameCounter::Tick(float fLockFPS)
{
    float fTimeElapsed; 

    // Is performance hardware available?
	if (m_PerfHardware) 
		QueryPerformanceCounter((LARGE_INTEGER *) &m_CurrentTime);
    else 
		m_CurrentTime = timeGetTime();

	// Calculate elapsed time in seconds
	fTimeElapsed = (m_CurrentTime - m_LastTime) * m_TimeScale;
    
    // Should we lock the frame rate
    // TODO - this would be better as a sleep 
    // rather than burning CPU
    if (fLockFPS > 0.0f)
    {
        while (fTimeElapsed < (1.0f / fLockFPS))
        {
	        if (m_PerfHardware) 
		        QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentTime);
            else 
		        m_CurrentTime = timeGetTime();

	        // Calculate elapsed time in seconds
	        fTimeElapsed = (m_CurrentTime - m_LastTime) * m_TimeScale;
        } // while
    } // End If

	// Save current frame time
	m_LastTime = m_CurrentTime;

    // Filter out values wildly different from current average
    if (fabsf(fTimeElapsed - m_TimeElapsed) < 1.0f)
    {
        // Wrap FIFO frame time buffer.
        memmove(&m_FrameTime[1], m_FrameTime, (MAX_SAMPLE_COUNT - 1) * sizeof(float));
        m_FrameTime[0] = fTimeElapsed;
        if (m_SampleCount < MAX_SAMPLE_COUNT) 
            m_SampleCount++;
    } // if
    
	// Calculate Frame Rate
	m_FPSFrameCount++;
	m_FPSTimeElapsed += m_TimeElapsed;
	if (m_FPSTimeElapsed > 1.0f) 
    {
		m_FrameRate			= m_FPSFrameCount;
		m_FPSFrameCount		= 0;
		m_FPSTimeElapsed	= 0.0f;
	} // if

    // Count up the new average elapsed time
    m_TimeElapsed = 0.0f;
    for (ULONG i = 0; i < m_SampleCount; i++) 
        m_TimeElapsed += m_FrameTime[ i ];

    if (m_SampleCount > 0) 
        m_TimeElapsed /= m_SampleCount;
} // Tick


// ----------------------------------------------------------------------------
// Name: FrameCounter::GetFrameRate
// Desc: Returns the frame rate, sampled over the last second or so.
// Parm: LPTSTR lpszString - a string buffer to write the frame rate to
// Retn: unsigned long     - the frame rate
// ----------------------------------------------------------------------------
unsigned long FrameCounter::GetFrameRate(LPTSTR lpszString) const
{
    // Fill string buffer
    if (lpszString)
    {
        // Copy frame rate value into string
        _itot(m_FrameRate, lpszString, 10);

        // Append with FPS
        strcat(lpszString, _T(" FPS"));
    } // if
    return m_FrameRate;
} // GetFrameRate


// ----------------------------------------------------------------------------
// Name: FrameCounter::GetTimeElapsed
// Desc: Returns the amount of time elapsed since the last frame (Seconds)
// Retn: float - the time in seconds
// ----------------------------------------------------------------------------
float FrameCounter::GetTimeElapsed() const
{
    return m_TimeElapsed;
} // GetTimeElapsed


// -- EOF
