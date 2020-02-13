// ----------------------------------------------------------------------------
// File: Timer.h
// Desc: Timer class that uses a high performance counter
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef __STD_TIMER_H_
#define __STD_TIMER_H_


// ----------------------------------------------------------------------------
// Timer includes
// ----------------------------------------------------------------------------
#include "stdType.h"
#include "stdMem.h"


// ----------------------------------------------------------------------------
// Name: Timer  (class)
// Desc: The Timer class produces an interface to a timer that can be started, 
//       stopped and reset.  It supports the maximum fidelity that the operaing 
//       system supports
// ----------------------------------------------------------------------------
class Timer : private Unique
{
public:
  // ------------------------------------------------------------------------
  // Constructor and destructor
  // ------------------------------------------------------------------------
  Timer();
  ~Timer();

  // ------------------------------------------------------------------------
  // Control the timer
  // ------------------------------------------------------------------------
  void Start();
  void Stop();
  void Reset();

  // ------------------------------------------------------------------------
  // Get the timer status
  // ------------------------------------------------------------------------
  float GetTime(float *delta_time);
  bool IsRunning();

  // ------------------------------------------------------------------------
  // Name: Counter (struct)
  // Desc: Holds the timing status
  // ------------------------------------------------------------------------
  struct Counter
  {
    signed long     high;   // high word
    unsigned long   low;    // low word
  }; // struct Counter

private:
  // ------------------------------------------------------------------------
  // Private members for the timer
  // ------------------------------------------------------------------------
  Counter   m_start_counter;    // Start
  Counter   m_end_counter;      // End
  float     m_total_time;       // Ttotal
  bool      m_running;          // Running

}; // class Timer


#endif // __STD_TIMER_H_

// -- EOF


