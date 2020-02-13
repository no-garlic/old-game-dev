// ----------------------------------------------------------------------------
// File: OSFunctions.cpp
// Desc: This file contains operating system funtionality for the Microsoft 
//       Windows platform, in a platform-interface inspecific way.
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "stdSystem.h"
#include "stdLog.h"
#include <exception>

#if PC
#include <mmsystem.h>
#endif


// ----------------------------------------------------------------------------
// Throw an exception
// ----------------------------------------------------------------------------
inline void ThrowOSException(const String &message) 
{
  LOG_ERROR << message << ENDLOG;
  std::exception e(message.c_str());
  throw e;
} // ThrowOSException


// ----------------------------------------------------------------------------
// Name: OS (namespace)
// Desc: Wrap all OS funtions in this namespace
// ----------------------------------------------------------------------------
namespace OS
{
  // ------------------------------------------------------------------------
  // Name: CreateThread
  // Desc: Creates a thread
  // Parm: unsigned long stacksize - The stack size for the thread - can use
  //       DEFAULT_STACK_SIZE.
  // Parm: ThreadFunc startaddress - The start address of the thread - pass a 
  //       function pointer
  // Parm: void *pargument         - the data to pass to the thread function
  // Retn: ThreadHandle            - a handle to the thread
  // ------------------------------------------------------------------------
  ThreadHandle CreateThread(unsigned long stacksize, ThreadFunc startaddress, void *pargument)
  {
    DWORD threadid;
    ThreadHandle threadhandle = ::CreateThread(
      0, 
      stacksize,
      reinterpret_cast<LPTHREAD_START_ROUTINE>(startaddress),
      pargument, 
      0, 
      &threadid);

    if (!threadhandle)
      ThrowOSException("Create thread failed");

    return reinterpret_cast<ThreadHandle>(threadhandle);
  } // CreateThread


  // ------------------------------------------------------------------------
  // Name: TerminateThread
  // Desc: Terminates the thread for good. However, it tries to join the 
  //       thread first, allowing it to exit cleanly if possible.
  // Parm: ThreadHandle thread     - the thread to terminate
  // Parm: unsigned long milliseconds - the time to wait for the thread to 
  //       finish before killing it
  // ------------------------------------------------------------------------
  void TerminateThread(ThreadHandle thread, unsigned long milliseconds)
  {
    // Wait for thread to exit.
    if (milliseconds > 0)
    {
      // If we are successful don't bother trying to terminate the thread
      if (::WaitForSingleObject(reinterpret_cast<Handle>(thread), milliseconds) == WAIT_OBJECT_0)
      {
        CloseThread(thread);
        return;
      } // if
    } // if

    // We have waited long enough - terminate the thread
#if XBOX
    ::ExitThread(0);
#else
    if (::TerminateThread(reinterpret_cast<Handle>(thread), 0) == 0)
      ThrowOSException("TerminateThread failed");
#endif

    // Close the thread too
    CloseThread(thread);
  } // TerminateThread


  // ------------------------------------------------------------------------
  // Name: ExitThread
  // Desc: Exits the current thread with the return code specified
  // Parm: unsigned long exit_value - the exit value
  // ------------------------------------------------------------------------
  void ExitThread(unsigned long exit_value)
  {
    ::ExitThread(exit_value);
  } // ExitThread


  // ------------------------------------------------------------------------
  // Name: GetThreadPriority
  // Desc: Get the priority of the thread supplied
  // Parm: ThreadHandle thread - the thread handle
  // Retn: int             - the priority
  // ------------------------------------------------------------------------
  int GetThreadPriority(ThreadHandle thread)
  {
    int priority = ::GetThreadPriority(reinterpret_cast<Handle>(thread));

    if (priority == THREAD_PRIORITY_ERROR_RETURN)
      ThrowOSException("GetThreadPriority failed");

    return priority;
  } // GetThreadPriority


  // ------------------------------------------------------------------------
  // Name: SetThreadPriority
  // Desc: Sets the priority of the thread
  // Parm: ThreadHandle thread - the thread handle
  // Parm: int priority    - the priority
  // ------------------------------------------------------------------------
  void SetThreadPriority(ThreadHandle thread, int priority)
  {
    if (::SetThreadPriority((reinterpret_cast<Handle>(thread)), priority) == FALSE)
      ThrowOSException("SetThreadPriorityFailed");
  } // SetThreadPriority


  // ------------------------------------------------------------------------
  // Name: Sleep
  // Desc: Suspends the current thread for the number of milliseconds 
  //       required
  // Parm: unsigned long milliseconds - the time
  // ------------------------------------------------------------------------
  void Sleep(unsigned long milliseconds) throw()
  {
    ::Sleep(milliseconds);
  } // Sleep


  // ------------------------------------------------------------------------
  // Name: Join
  // Desc: Waits for a thread to exit, and then returns that thread's exit 
  //       code. Once a thread has been joined it no longer needs to be 
  //       closed.  May throw if the thread has already finished, or is not 
  //       joinable for some other reason.
  // Parm: ThreadHandle thread - the thread handle
  // Retn: unsigned long   - the return value from the thread
  // ------------------------------------------------------------------------
  unsigned long Join(ThreadHandle thread)
  {
    // Wait for the thread to terminate
    if (::WaitForSingleObject(thread, INFINITE) != 0)
      ThrowOSException("Error waiting for thread to finish!");

    DWORD exit_code;
    if (::GetExitCodeThread(reinterpret_cast<Handle>(thread), &exit_code) == 0)
      ThrowOSException("Join failed");

    CloseThread(thread);
    unsigned long exit_value = static_cast<unsigned long>(exit_code);
    return exit_value;
  } // Join


  // ------------------------------------------------------------------------
  // Name: GetCurrentThreadHandle
  // Desc: Gets a handle to the current thread
  // Retn: ThreadHandle - the thread handle
  // ------------------------------------------------------------------------
  ThreadHandle GetCurrentThreadHandle()
  {
    Handle thr = GetCurrentThread();
    return reinterpret_cast<ThreadHandle>(thr);
  } // GetCurrentThread


  // ------------------------------------------------------------------------
  // Name: CloseThread
  // Desc: Closes a thread. This cleans a thread up so that we can no longer 
  //       reference it. It does not terminate the thread - it will run to 
  //       completion.    
  // Parm: ThreadHandle thread - the thread handle
  // ------------------------------------------------------------------------
  void CloseThread(ThreadHandle thread)
  {
    if (CloseHandle(reinterpret_cast<void*>(thread)) == 0)
      ThrowOSException("CloseThread failed");
  } // CloseThread


  // ------------------------------------------------------------------------
  // Name: CreateTimer
  // Desc: Creates a timer
  // Parm: bool manualreset - true if the timer should reset after being 
  //       waited for, or remain set.
  // Retn: OS::Handle   - a handle to the timer
  // ------------------------------------------------------------------------
  OS::Handle CreateTimer(bool manualreset)
  {
    Handle htimer;
    if ((htimer = ::CreateWaitableTimer(0, manualreset ? TRUE : FALSE, 0)) == 0)
      ThrowOSException("CreateTimer failed");

    return reinterpret_cast<OS::Handle>(htimer);
  } // CreateTimer


  // ------------------------------------------------------------------------
  // Name: CloseTimer
  // Desc: Closes a timer
  // Parm: OS::Handle timer - the timer handle
  // ------------------------------------------------------------------------
  void CloseTimer(OS::Handle timer)
  {
    if (::CloseHandle(reinterpret_cast<Handle>(timer)) == 0)
      ThrowOSException("CloseTimer failed");
  } // CloseTimer


  // ------------------------------------------------------------------------
  // Name: SetTimer
  // Desc: Sets the timer to start timing. The timing will become 'set' or 
  //       signalled, at the due time, and every period after that.  If due 
  //       time is positive, it is in UTC. If it is negative, it is relative.
  // Parm: OS::Handle timer - the timer handle
  // Parm: TimeInfo duetime - the time to initially become signelled at
  // Parm: bool relative - set to true if the duetime is relative
  // Parm: TimeInfo period - the period to signal at afterwards
  // ------------------------------------------------------------------------
  void SetTimer(OS::Handle timer, TimeInfo duetime, bool relative, TimeInfo period)
  {
    // Remember - this is in terms of 100 ns intervals
    LARGE_INTEGER liduetime;
    liduetime.QuadPart = (duetime.seconds * 10000000) + (duetime.nano_seconds / 100);

    // Make this negative if we are looking for relative timing
    if (relative)
      liduetime.QuadPart *= -1;

    unsigned long period_ms = (period.seconds * 1000) + (period.nano_seconds / 1000000);

    if (::SetWaitableTimer(reinterpret_cast<Handle>(timer), &liduetime, period_ms, 0, 0, TRUE) == 0)
      ThrowOSException("SetTimer failed");
  } // SetTimer


  // ------------------------------------------------------------------------
  // Name: CancelTimer
  // Desc: Cancels the timer - it stops counting down, but will remain in 
  //       whatever signalled state it is in.
  // Parm: OS::Handle timer - the timer handle
  // Retn: bool         - true if the cancel succeeded
  // ------------------------------------------------------------------------
  bool CancelTimer(OS::Handle timer) throw()
  {
    return ::CancelWaitableTimer(reinterpret_cast<Handle>(timer)) != 0;
  } // CancelTimer


  // ------------------------------------------------------------------------
  // Name: CreateEvent
  // Desc: Creates an 'event' - an object for synchronising threads. An event 
  //       can be created by names and shared across processes. In this case 
  //       the name must be unique, and not 0.
  // Parm: bool manualreset - true if the event should remain set until 
  //       someone calls ResetEvent.  Otherwise it resets when a wait has been
  //       performed.
  // Parm: bool initialstate - the initial state (set or reset).
  // Parm: const char *pname - the name of the event - 0 if it is not to be 
  //       shared
  // Retn: OS::Handle     - a handle to the event
  // ------------------------------------------------------------------------
  OS::Handle CreateEvent(bool manualreset, bool initialstate, const char *pname)
  {
    Handle hevent;
    if ((hevent = ::CreateEventA(0, manualreset ? TRUE : FALSE, initialstate ? TRUE : FALSE, pname)) == 0)
      ThrowOSException("CreateEvent failed");

    return reinterpret_cast<OS::Handle>(hevent);
  } // Createevent


  // ------------------------------------------------------------------------
  // Name: OpenEvent
  // Desc: Open's the event by its name. A event must already have been 
  //       created with this name.
  // Parm: const char *pname - the name of the event to open
  // Retn: OS::Handle    - the event handle
  // ------------------------------------------------------------------------
  OS::Handle OpenEvent(const char *pname)
  {
    Handle hevent;
    if ((hevent = ::OpenEvent(EVENT_ALL_ACCESS, TRUE, pname)) == 0)
      ThrowOSException("OpenEvent failed");

    return reinterpret_cast<OS::Handle>(hevent);
  } // OpenEvent


  // ------------------------------------------------------------------------
  // Name: CloseEvent
  // Desc: Closes an event so that it cannot be used any more. The event will 
  //       only truly be released when everybody who called OpenEvent (and 
  //       CreateEvent) have closed it.
  // Parm: OS::Handle event - the event handle
  // ------------------------------------------------------------------------
  void CloseEvent(OS::Handle event)
  {
    if (::CloseHandle(reinterpret_cast<Handle>(event)) == 0)
      ThrowOSException("CloseEvent failed");
  } // CloseEvent


  // ------------------------------------------------------------------------
  // Name: SetEvent
  // Desc: Sets the event. Threads that wait on this event will be released.
  // Parm: OS::Handle event - the event handle
  // ------------------------------------------------------------------------
  void SetEvent(OS::Handle event)
  {
    if (::SetEvent(reinterpret_cast<Handle>(event)) == 0)
      ThrowOSException("SetEvent failed");
  } // SetEvent


  // ------------------------------------------------------------------------
  // Name: ResetEvent
  // Desc: Reset the event
  // Parm: OS::Handle event - the event handle
  // ------------------------------------------------------------------------
  void ResetEvent(OS::Handle event)
  {
    if (::ResetEvent(reinterpret_cast<Handle>(event)) == 0)
      ThrowOSException("ResetEvent failed");
  } // ResetEvent


  // ------------------------------------------------------------------------
  // Name: PulseEvent
  // Desc: Pulses the event. All threads waiting on it will be released, and 
  //       then the event will be reset again.
  // Parm: OS::Handle event - the event handle
  // ------------------------------------------------------------------------
  void PulseEvent(OS::Handle event)
  {
    if (::PulseEvent(reinterpret_cast<Handle>(event)) == 0)
      ThrowOSException("PulseEvent failed");
  } // PulseEvent


  // ------------------------------------------------------------------------
  // Name: CreateMutex
  // Desc: Creates a mutex. If a name is specified the mutex can be shared 
  //       between processes.
  // Parm: const char *pname - the name of the mutex, or 0
  // Retn: OS::Handle    - the mutex handle
  // ------------------------------------------------------------------------
  OS::Handle CreateMutex(const char *pname)
  {
    // No initial ownership of the mutex
    Handle hmutex;
    if ((hmutex = ::CreateMutexA(0, FALSE, pname)) == 0)
      ThrowOSException("CreateMutex failed");
    return reinterpret_cast<OS::Handle>(hmutex);
  } // CreateMutex


  // ------------------------------------------------------------------------
  // Name: OpenMutex
  // Desc: Open's a mutex by name. The mutex must already have been created 
  //       with this name.
  // Parm: const char *pname - the name of the mutex
  // Retn: OS::Handle    - the mutex handle
  // ------------------------------------------------------------------------
  OS::Handle OpenMutex(const char *pname)
  {
    Handle hmutex;
    if ((hmutex = ::OpenMutex(MUTEX_ALL_ACCESS, TRUE, pname)) == 0)
      ThrowOSException("OpenMutex failed");

    return reinterpret_cast<OS::Handle>(hmutex);
  } // OpenMutex


  // ------------------------------------------------------------------------
  // Name: CloseMutex
  // Desc: Closes the mutex provided. This matches a call to CreateMutex or 
  //       OpenMutex, and the handle supplied is no longer valid.
  // Parm: OS::Handle mutex - the mutex handle
  // ------------------------------------------------------------------------
  void CloseMutex(OS::Handle mutex)
  {
    if (::CloseHandle(reinterpret_cast<Handle>(mutex)) == 0)
      ThrowOSException("CloseMutex failed");
  } // CloseMutex


  // ------------------------------------------------------------------------
  // Name: ReleaseMutex
  // Desc: Releases a mutex, so that it can be acquired by someone else.
  // Parm: OS::Handle mutex - the mutex handle
  // Retn: bool         - true if it succeeded, otherwise false if the mutex 
  //       is not owned by this process
  // ------------------------------------------------------------------------
  bool ReleaseMutex(OS::Handle mutex)
  {
    if (::ReleaseMutex(reinterpret_cast<Handle>(mutex)) == 0)
    {
      if (GetLastError() == ERROR_NOT_OWNER)
        return false;
      else
        ThrowOSException("ReleaseMutex failed");
    } // if
    return true;
  } // ReleaseMutex


  // ------------------------------------------------------------------------
  // Name: WaitForSingleObject
  // Desc: Waits for the object provided for the time specified.  Accepted 
  //       objects are timers, events and mutexes.
  // Parm: OS::Handle object     - the handle to wait on
  // Parm: unsigned long timeout - the time to wait for the handle in 
  //       milliseconds, or can be INFINITE.
  // Retn: int                   - 0 if successful, or WAIT_TIMEOUT
  // ------------------------------------------------------------------------
  int WaitForSingleObject(OS::Handle object, unsigned long timeout)
  {
    int retvalue = ::WaitForSingleObject(reinterpret_cast<Handle>(object), timeout);

    // Check for a failure
    if (retvalue == WAIT_FAILED)
      ThrowOSException("WaitForSingleObject failed");

    return retvalue;
  } // WaitForSingleObject


  // ------------------------------------------------------------------------
  // Name: WaitForMultipleObjects
  // Desc: Wait for multiple objects for the time specified.  Accepted objects 
  //       are timers, events and mutexes.
  // Parm: int nobjects          - the number of objects
  // Parm: OS::Handle* pobjects  - the object array
  // Parm: unsigned long timeout - the time to wait for the handles in 
  //       milliseconds, or can be INFINITE.
  // Retn: int                   - 0 if successful, or WAIT_TIMEOUT
  // ------------------------------------------------------------------------
  int WaitForMultipleObjects(int nobjects, OS::Handle* pobjects, unsigned long timeout)
  {
    // We have to be careful that we are not above the limit for the
    // maximum number of wait objects. If we are then there are two
    // principle ways of handling the problem. Possibly the best is
    // two distribute the waits within multiple threads, and wait on
    // some events that correspond to the threads. This may not even
    // require thread creation if we use some precreated pool. However,
    // this is a bit complex for the moment, so we will just copy the
    // methodology used in IrixFeatures (which is basically a poll!)
    if (nobjects > MAXIMUM_WAIT_OBJECTS)
    {
      const int     RELEASE_MS = 1;
      unsigned long time       = 0;

      while(true)
      {
        for(int i = 0; i < nobjects; ++i)
        {
          // Any exceptions will pass straight through
          // If this condition is met, return. We will find out
          // immediately
          if (WaitForSingleObject(pobjects[i], 0) != WAIT_TIMEOUT)
            return i;
        } // for

        // Now sleep for a little while (1 ms) to release some CPU
        unsigned long sleep_time = RELEASE_MS;
        if ((timeout != INFINITE) && ((timeout - time) < RELEASE_MS))
          sleep_time = static_cast<unsigned long>(timeout - time);
        Sleep(sleep_time);

        // Update our time.
        time += sleep_time;

        // If we have a timeout condition, check if this is satisfied
        if ((timeout != INFINITE) && (time >= timeout))
          break;
      } // while

      return WAIT_TIMEOUT;
    } // if

    // If we are here then we can wait on all of our handles simultaneously
    int retvalue = ::WaitForMultipleObjects(nobjects, reinterpret_cast<CONST Handle *>(pobjects), FALSE,
      timeout == INFINITE ? INFINITE : timeout);

    // Check for a failure
    if (retvalue == WAIT_FAILED)
      ThrowOSException("WaitForMultipleObject failed");

    return (retvalue == WAIT_TIMEOUT) ? WAIT_TIMEOUT : retvalue - WAIT_OBJECT_0;
  } // WaitForMultipleObjects


  // ------------------------------------------------------------------------
  // Name: WaitForMultipleObjects
  // Desc: Wait for multiple objects for the time specified.  Accepted objects 
  //       are timers, events and mutexes.
  // Parm: Array <OS::Handle> &objects - the object vector
  // Parm: unsigned long timeout             - the time to wait for the 
  //       handles in milliseconds, or can be INFINITE.
  // Retn: int                               - 0 if successful, or 
  //       WAIT_TIMEOUT
  // ------------------------------------------------------------------------
  int WaitForMultipleObjects(Array <OS::Handle> &objects, unsigned long timeout)
  {
    return WaitForMultipleObjects(static_cast<int>(objects.size()), &objects[0], timeout);
  } // WaitForMultipleObjects


  // ------------------------------------------------------------------------
  // Counter functions
  // If a high performance counter is available for timing, it will be used, 
  // otherwise the multimedia timer will be used. The decision will be made 
  // the first time a counter function is used, when the variable 
  // g_countertype will be set to the timer type being used.
  // ------------------------------------------------------------------------
  namespace
  {
    enum OSCOUNTERTYPE
    {
      UNCHECKED,
      NORMAL,
      HIGHPERFORMANCE
    }; // enum OSCOUNTERTYPE

    OSCOUNTERTYPE       g_countertype = UNCHECKED;
    OS::CounterInfo     g_counterfrequency;
    float               g_counterperiod;
  }; // namespace


  // ------------------------------------------------------------------------
  // Name: GetCounter
  // Desc: Gets the current counter
  // Retn: CounterInfo - the counter info
  // ------------------------------------------------------------------------
  CounterInfo GetCounter() throw()
  {
    CounterInfo retvalue;

    if (g_countertype == UNCHECKED) // if currently unchecked, check now
      GetCounterFrequency();

    if (g_countertype == HIGHPERFORMANCE)
    {
      LARGE_INTEGER liperformancecount;

      // Assume an error indicates no high performance counter is available
      QueryPerformanceCounter(&liperformancecount);

      // We don't need to do any seconds/nano-seconds
      retvalue.low  = liperformancecount.LowPart;
      retvalue.high = liperformancecount.HighPart;
    } // if
    else
    {
      retvalue.low  = timeGetTime();
      retvalue.high = 0;
    } // else

    return retvalue;
  } // GetCounter


  // ------------------------------------------------------------------------
  // Name: GetCounterFrequency
  // Desc: Gets the frequency of the current counter, so that resolution can 
  //       be counted.
  // Retn: CounterInfo - the counter info
  // ------------------------------------------------------------------------
  CounterInfo GetCounterFrequency() throw()
  {
    if (g_countertype == UNCHECKED)
    {
      LARGE_INTEGER liperformancefrequency;

      // Assume an error indicates no high performance counter is available
      if (QueryPerformanceFrequency(&liperformancefrequency) != 0) // supports high performance counter
        g_countertype = HIGHPERFORMANCE;
      else
        g_countertype = NORMAL;

      g_counterfrequency.low  = liperformancefrequency.LowPart;
      g_counterfrequency.high = liperformancefrequency.HighPart;

      // If using primitive timing with no frequency given, then use the multimedia timer
      // Can set to a particular frequency, for now use the default =5ms (WinNT) =1ms (Win95)
      if (g_counterfrequency.low == 0 && g_counterfrequency.high == 0)
      {
        // The time given by the multimedia timer is in milliseconds, so this is the frequency
        g_counterfrequency.low = 1000;
        g_counterperiod = 0.001f;
      } // if
      else
      {
        g_counterperiod = 1.0f / static_cast<float>(liperformancefrequency.QuadPart);
      } // else
    } // if

    return g_counterfrequency;
  } // GetCounterFrequency


  // ------------------------------------------------------------------------
  // Name: CalculateTimeDifference
  // Desc: Calculates the time difference between two counter readings.
  // Parm: CounterInfo start  - the start counter
  // Parm: CounterInfo finish - the end counter
  // Retn: float              - the time difference between the two counters
  // ------------------------------------------------------------------------
  float CalculateTimeDifference(CounterInfo start, CounterInfo finish) throw()
  {
    LARGE_INTEGER listart, lifinish;
    listart.LowPart   = start.low;
    listart.HighPart  = start.high;
    lifinish.LowPart  = finish.low;
    lifinish.HighPart = finish.high;

    LARGE_INTEGER lidiff;
    lidiff.QuadPart = lifinish.QuadPart - listart.QuadPart;

    // Presume a counter period has been retrieved, otherwise 
    // TimeInfo values would be invalid.
    return static_cast<float>(lidiff.QuadPart) * g_counterperiod;
  } // CalculateTimeDifference


  // ------------------------------------------------------------------------
  // Name: Thread::Thread
  // Desc: Constructor to create a thread
  // Parm: Vision::ThreadFunc func - the function to call in the thread
  // Parm: void *parg          - the data to pass to the thread function
  // ------------------------------------------------------------------------
  Thread::Thread(OS::ThreadFunc func, void *parg)
  {
    REF_COUNT_CTOR(Thread);

    DWORD threadid;
    m_threadhandle = ::CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(func), parg, 0, &threadid);

    if (m_threadhandle == NULL)
      ThrowOSException("Failed to create the thread");
  } // Thread


  // ------------------------------------------------------------------------
  // Name: Thread::~Thread
  // Desc: Destructor
  // ------------------------------------------------------------------------
  Thread::~Thread()
  {
    REF_COUNT_DTOR(Thread);

#if XBOX
    ::ExitThread(0);
#else
    if (::TerminateThread(m_threadhandle, 0) == 0)
      ThrowOSException("Failed to terminate the thread");
#endif

    if (CloseHandle(m_threadhandle) == 0)
      ThrowOSException("Failed to close the thread");
  } // ~Thread


  // ------------------------------------------------------------------------
  // Name: Thread::Join
  // Desc: Join the thread
  // Retn: ThreadReturnType - the return value from the thread
  // ------------------------------------------------------------------------
  ThreadReturnType Thread::Join()
  {
    if (WaitForSingleObject(m_threadhandle, INFINITE) != 0)
      ThrowOSException("Error joining thread!");

    DWORD exit_code;
    if (GetExitCodeThread(m_threadhandle, &exit_code) == 0)
      ThrowOSException("Error joining thread!");

    if (CloseHandle(m_threadhandle) == 0)
      ThrowOSException("Failed to close the thread");

    ThreadReturnType exit_value = static_cast<ThreadReturnType>(exit_code);
    return exit_value;
  } // Join


  // ------------------------------------------------------------------------
  // Name: Event::Event
  // Desc: Constructor to create an event
  // ------------------------------------------------------------------------
  Event::Event()
  {
    REF_COUNT_CTOR(Event);

    m_event = CreateEventA(NULL, FALSE, FALSE, 0);

    if (m_event == NULL)
      ThrowOSException("Failed to create the event");
  } // Event


  // ------------------------------------------------------------------------
  // Name: Event::~Event
  // Desc: Destructor
  // ------------------------------------------------------------------------
  Event::~Event()
  {
    REF_COUNT_DTOR(Event);

    if (!::SetEvent(m_event))
      ThrowOSException("Failed to set the event");

    if (!CloseHandle(m_event))
      ThrowOSException("Failed to close the event handle");
  } // ~Event


  // ------------------------------------------------------------------------
  // Name: Event::Set
  // Desc: Set the event
  // ------------------------------------------------------------------------
  void Event::Set()
  {
    if (!::SetEvent(m_event))
      ThrowOSException("Failed to set the event");
  } // Set


  // ------------------------------------------------------------------------
  // Name: Event::Wait
  // Desc: Wait for the event to be set
  // ------------------------------------------------------------------------
  void Event::Wait()
  {
    if (WaitForSingleObject(m_event, INFINITE) == WAIT_FAILED)
      ThrowOSException("Failed to wait for the event");
  } // Wait


  // ------------------------------------------------------------------------
  // Name: Mutex::Mutex
  // Desc: Constructor to create a mutex
  // ------------------------------------------------------------------------
  Mutex::Mutex()
  {
    REF_COUNT_CTOR(Mutex);

    m_mutex = CreateMutexA(NULL, FALSE, 0);

    if (!m_mutex)
      ThrowOSException("Failed to create the mutex");
  } // Mutex


  // ------------------------------------------------------------------------
  // Name: Mutex::~Mutex
  // Desc: Destructor
  // ------------------------------------------------------------------------
  Mutex::~Mutex()
  {
    REF_COUNT_DTOR(Mutex);

    if (!CloseHandle(m_mutex))
      ThrowOSException("Failed to close the mutex handle");
  } // ~Mutex


  // ------------------------------------------------------------------------
  // Name: Mutex::Acquire
  // Desc: Acquire the mutex
  // ------------------------------------------------------------------------
  void Mutex::Acquire()
  {
    if (WaitForSingleObject(m_mutex, INFINITE) == WAIT_FAILED)
      ThrowOSException("Failed to acquire the mutex");
  } // Acquire


  // ------------------------------------------------------------------------
  // Name: Mutex::Release
  // Desc: Release the mutex
  // ------------------------------------------------------------------------
  void Mutex::Release()
  {
    if (!ReleaseMutex(m_mutex))
      ThrowOSException("Failed to release the mutex");
  } // Release


}; // namespace OS


// -- EOF


