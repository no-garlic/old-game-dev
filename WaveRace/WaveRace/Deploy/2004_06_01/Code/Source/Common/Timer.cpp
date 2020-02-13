// ----------------------------------------------------------------------------
// File: Timer.h
// Desc: Timer class that uses a high performance counter
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Timer includes
// ----------------------------------------------------------------------------
#include "Common/Timer.h"


// ----------------------------------------------------------------------------
// Include winsock2 so that we don't get old winsock definitions in windows.h, 
// in case some later code needs sockets
// ----------------------------------------------------------------------------
#include <winsock2.h>
#include <windows.h>
#include <complex>


// ----------------------------------------------------------------------------
// Unnamed namespace to hide implementation
// ----------------------------------------------------------------------------
namespace
{
    // ------------------------------------------------------------------------
    // Name: VISIONCOUNTERTYPE (enum)
    // Desc: Enumeration of counter types
    // ------------------------------------------------------------------------
    enum VISIONCOUNTERTYPE
    {
        UNCHECKED,          // Undecided
        NORMAL,             // Normal counter
        HIGHPERFORMANCE     // High performance counter
    }; // VISIONCOUNTERTYPE

    // ------------------------------------------------------------------------
    // Global objects for counter type, frequency, and period
    // ------------------------------------------------------------------------
    VISIONCOUNTERTYPE   g_countertype = UNCHECKED;  // type
    Timer::Counter      g_counterfrequency;         // frequency
    float               g_counterperiod;            // period
}; // namespace


// ----------------------------------------------------------------------------
// Name: GetCounterFrequency
// Desc: Gets the frequency of the counter in this computer
// Retn: Timer::Counter - a counter
// ----------------------------------------------------------------------------
Timer::Counter GetCounterFrequency() throw()
{
    if (g_countertype == UNCHECKED)
    {
        LARGE_INTEGER freq;

        // Determine if we have a high performance counter
        if (QueryPerformanceFrequency(&freq) != 0)
            g_countertype = HIGHPERFORMANCE;
        else
            g_countertype = NORMAL;

        // Set the counter frequency
        g_counterfrequency.low  = freq.LowPart;
        g_counterfrequency.high = freq.HighPart;

        // If using primitive timing with no frequency given, then use 
        // the multimedia timer. Can set to a particular frequency, for 
        // now use the default = 5ms (WinNT) = 1ms (Win95)
        if (g_counterfrequency.low == 0 && g_counterfrequency.high == 0)
        {
            // The time given by the multimedia timer is in milliseconds, 
            // so this is the frequency
            g_counterfrequency.low = 1000;
            g_counterperiod = 0.001f;
        } // if
        else
        {
            g_counterperiod = 1.0f / static_cast<float>(freq.QuadPart);
        } // else
    } // if

    // return the frequency
    return g_counterfrequency;
} // GetCounterFrequency


// ----------------------------------------------------------------------------
// Name: GetCounter
// Desc: Get a counter set to the current time
// Retn: Timer::Counter - a counter with the current time
// ----------------------------------------------------------------------------
Timer::Counter GetCounter() throw()
{
    // Create a counter
    Timer::Counter retvalue;

    // Determine if we have a high performance counter
    if (g_countertype == UNCHECKED) 
        GetCounterFrequency();

    if (g_countertype == HIGHPERFORMANCE)
    {
        LARGE_INTEGER freq;
        QueryPerformanceCounter(&freq);

        // We don't need to do any seconds / nano-seconds
        retvalue.low  = freq.LowPart;
        retvalue.high = freq.HighPart;
    } // if
    else
    {
        retvalue.low  = timeGetTime();
        retvalue.high = 0;
    } // else

    // return the counter
    return retvalue;
} // GetCounter


// ----------------------------------------------------------------------------
// Name: CalculateTimeDifference
// Desc: Calculate the time difference between two counters
// Parm: Timer::Counter start   - the start counter
// Parm: Timer::Counter finish  - the end counter
// Retn: float                  - the time difference in seconds
// ----------------------------------------------------------------------------
float CalculateTimeDifference(Timer::Counter start, Timer::Counter finish) throw()
{
    LARGE_INTEGER listart, lifinish, lidiff;

    listart.LowPart     = start.low;
    listart.HighPart    = start.high;
    lifinish.LowPart    = finish.low;
    lifinish.HighPart   = finish.high;
    lidiff.QuadPart     = lifinish.QuadPart - listart.QuadPart;

    // Presume a counter period has been retrieved
    return static_cast<float>(lidiff.QuadPart) * g_counterperiod;
} // CalculateTimeDifference


// ----------------------------------------------------------------------------
// Name: Timer::Timer
// Desc: Constructor
// ----------------------------------------------------------------------------
Timer::Timer() : m_running(false)
{
    Reset();
} // Timer


// ----------------------------------------------------------------------------
// Name: Timer::~Timer
// Desc: Destructor
// ----------------------------------------------------------------------------
Timer::~Timer()
{
} // ~Timer


// ----------------------------------------------------------------------------
// Name: Timer::Start
// Desc: Starts the timer.  This is treated as a start after the timer has been 
//       reset, or a resume after the timer has been stopped or a no-op if the 
//       timer is already running.
// ----------------------------------------------------------------------------
void Timer::Start() throw()
{
    if (!m_running)
    {
        m_running       = true;
        m_start_counter = GetCounter();
    } // if
} // Start


// ----------------------------------------------------------------------------
// Name: Timer::Stop
// Desc: Stops the timer.  This is basically a pause that suspends the timer's 
//       counter until Start is called again.
// ----------------------------------------------------------------------------
void Timer::Stop() throw()
{
    if (m_running)
    {
        m_end_counter = GetCounter ();
        m_running     = false;
        m_total_time += CalculateTimeDifference(m_start_counter, m_end_counter);
    } // if
} // Stop


// ----------------------------------------------------------------------------
// Name: Timer::Reset
// Desc: Resets the timer.  Initialises all timer values back to 0 so the timer 
//       can be reused.
// ----------------------------------------------------------------------------
void Timer::Reset()
{
    m_total_time    = 0;;
    m_running       = false;
} // Reset


// ----------------------------------------------------------------------------
// Name: Timer::GetTime
// Desc: Gets the current time in seconds
// Parm: float *delta_time - if not null, assigned to the time difference 
//       since tha last call to GetTime.  Note - returns 0.0 if the timer is 
//       not running.
// Retn: float             - time in seconds
// ----------------------------------------------------------------------------
float Timer::GetTime(float *delta_time)
{
    float diff = 0.0;

    // Only recalculate if the timer is running
    if (m_running)
    {
        m_end_counter   = GetCounter ();
        diff            = CalculateTimeDifference(m_start_counter, m_end_counter);
        m_total_time   += diff;
        m_start_counter = GetCounter();
    } // if

    // Return the delta time since the last call
    if (delta_time)
        (*delta_time) = diff;

    // Return the total time
    return m_total_time;
} // GetTime


// ----------------------------------------------------------------------------
// Name: Timer::IsRunning
// Desc: Determines if the timer is running
// Retn: bool - true if the timer is running
// ----------------------------------------------------------------------------
bool Timer::IsRunning()
{
    return m_running;
} // IsRunning


// -- EOF
