// ----------------------------------------------------------------------------
// File: OSClasses.h
// Desc: General OS class wrappers
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef __STD_SYSTEM_H_
#define __STD_SYSTEM_H_


// ----------------------------------------------------------------------------
// OSFunctions includes
// ----------------------------------------------------------------------------
#include "stdType.h"


// ----------------------------------------------------------------------------
// Undefine CreateEvent if it has already been defined by windows so we can use 
// our implementation
// ----------------------------------------------------------------------------
#ifdef CreateEvent
#undef CreateEvent
#endif

// ----------------------------------------------------------------------------
// Undefine CreateMutex if it has already been defined by windows so we can use 
// our implementation
// ----------------------------------------------------------------------------
#ifdef CreateMutex
#undef CreateMutex
#endif


// ----------------------------------------------------------------------------
// Name: OS (namespace)
// Desc: Scopes the OS classes
// ----------------------------------------------------------------------------
namespace OS
{
  // ------------------------------------------------------------------------
  // Typedefs for the thread function and thread return type
  // ------------------------------------------------------------------------
  typedef unsigned long ThreadReturnType;
  typedef ThreadReturnType (*ThreadFunc)(void *);

  // ------------------------------------------------------------------------
  // Generic handle type
  // ------------------------------------------------------------------------
  typedef HANDLE Handle;
  typedef HANDLE ThreadHandle;

  // ------------------------------------------------------------------------
  // Name: TimeInfo (struct)
  // Desc: Time information
  // ------------------------------------------------------------------------
  struct TimeInfo
  {
    unsigned long seconds;
    unsigned long nano_seconds;
  }; // struct TimeInfo

  // ------------------------------------------------------------------------
  // Name: CounterInfo (struct)
  // Desc: Counter information
  // ------------------------------------------------------------------------
  struct CounterInfo
  {
    signed long   high;
    unsigned long low;
  }; // struct CounterInfo

  // ------------------------------------------------------------------------
  // Thread functions
  // ------------------------------------------------------------------------
  ThreadHandle    CreateThread(unsigned long stacksize, ThreadFunc startaddress, void *pargument);
  void            TerminateThread(ThreadHandle thread, unsigned long milliseconds = 0);
  void            ExitThread(unsigned long exit_value);
  void            Sleep(unsigned long milliseconds = 0) throw();
  unsigned long   Join(ThreadHandle thread);
  ThreadHandle    GetCurrentThreadHandle();
  void            CloseThread(ThreadHandle thread);
  int             GetThreadPriority(ThreadHandle thread);
  void            SetThreadPriority(ThreadHandle thread, int priority);

  // ------------------------------------------------------------------------
  // Timer functions
  // ------------------------------------------------------------------------
  Handle          CreateTimer(bool manual_reset);
  void            CloseTimer(Handle timer);
  void            SetTimer(Handle timer, TimeInfo duetime, bool relative, TimeInfo period);
  bool            CancelTimer(Handle timer) throw();

  // ------------------------------------------------------------------------
  // Event functions
  // ------------------------------------------------------------------------
  Handle          CreateEvent(bool manualreset, bool initialstate, const char *pname = 0);
  Handle          OpenEvent(const char *pname);
  void            CloseEvent(Handle event);
  void            SetEvent(Handle event);
  void            ResetEvent(Handle event);
  void            PulseEvent(Handle event);

  // ------------------------------------------------------------------------
  // Mutex functions
  // ------------------------------------------------------------------------
  Handle          CreateMutex(const char *pname = 0);
  Handle          OpenMutex(const char *pname);
  void            CloseMutex(Handle mutex);
  bool            ReleaseMutex(Handle mutex);

  // ------------------------------------------------------------------------
  // Waiting for handles
  // ------------------------------------------------------------------------
  int             WaitForSingleObject(Handle object, unsigned long timeout);
  int             WaitForMultipleObjects(int nobjects, Handle* pobjects, unsigned long timeout);
  int             WaitForMultipleObjects(Array <Handle> &objects, unsigned long timeout);

  // ------------------------------------------------------------------------
  // Counter functions
  // ------------------------------------------------------------------------
  CounterInfo     GetCounter() throw();
  CounterInfo     GetCounterFrequency() throw();
  float           CalculateTimeDifference(CounterInfo start, CounterInfo finish) throw();


  // -------------------------------------------------------------------------
  // Name: Thread (class)
  // Desc: Manages a thread
  // -------------------------------------------------------------------------
  class Thread
  {
  public:
    // --------------------------------------------------------------------
    // Constructor and destructor
    // --------------------------------------------------------------------
    Thread(OS::ThreadFunc func, void *parg);
    ~Thread();

    // --------------------------------------------------------------------
    // Join the thread
    // --------------------------------------------------------------------
    ThreadReturnType Join();

  private:
    // --------------------------------------------------------------------
    // Hide the copy constructor
    // --------------------------------------------------------------------
    Thread (const Thread &rhs) {}

    // --------------------------------------------------------------------
    // The thread
    // --------------------------------------------------------------------
    Handle m_threadhandle;
  }; // class Thread


  // -------------------------------------------------------------------------
  // Name: Event  (class)
  // Desc: Manages an event
  // -------------------------------------------------------------------------
  class Event
  {
  public:
    // --------------------------------------------------------------------
    // Constructor and destructor
    // --------------------------------------------------------------------
    Event();
    ~Event();

    // --------------------------------------------------------------------
    // Set and wait for the event
    // --------------------------------------------------------------------
    void Set();
    void Wait();

  private:
    // --------------------------------------------------------------------
    // Hide the copy constructor
    // --------------------------------------------------------------------
    Event (const Event &rhs) {}

    // --------------------------------------------------------------------
    // The event
    // --------------------------------------------------------------------
    Handle m_event;
  }; // class Event


  // ------------------------------------------------------------------------
  // Name: Mutex  (class)
  // Desc: Manages a mutex
  // ------------------------------------------------------------------------
  class Mutex
  {
  public:
    // --------------------------------------------------------------------
    // Constructor and destructor
    // --------------------------------------------------------------------
    Mutex();
    virtual ~Mutex();

    // --------------------------------------------------------------------
    // Acquire and release the mutex
    // --------------------------------------------------------------------
    void Acquire();
    void Release();

  private:
    // --------------------------------------------------------------------
    // Hide the copy constructor
    // --------------------------------------------------------------------
    Mutex (const Mutex &rhs) {}

    // --------------------------------------------------------------------
    // The mutex
    // --------------------------------------------------------------------
    Handle m_mutex;

  }; // class Mutex


  // ------------------------------------------------------------------------
  // Name: MutexLock (class)
  // Desc: Locks the mutex in the constructor, and releases it in the 
  //       destructor.  Useful for ensuring a mutex is released when the 
  //       MutexLock goes out of scope
  // ------------------------------------------------------------------------
  class MutexLock
  {
  public:
    // --------------------------------------------------------------------
    // Constructor and destructor
    // --------------------------------------------------------------------
    MutexLock (Mutex &m) : m_mutex(m) {m.Acquire();}
    virtual ~MutexLock() {m_mutex.Release();}

  private:
    // --------------------------------------------------------------------
    // The OS Mutex
    // --------------------------------------------------------------------
    Mutex &m_mutex;

  }; // MutexLock


}; // namespace OS


#endif // __STD_SYSTEM_H_

// -- EOF


