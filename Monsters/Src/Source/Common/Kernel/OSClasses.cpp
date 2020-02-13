// ----------------------------------------------------------------------------
// File: OSClasses.h
// Desc: General OS class wrappers
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Kernel/Types.h"
#include "Kernel/OSClasses.h"
#include "Kernel/Exceptions.h"
#include "Kernel/Logging.h"


// ----------------------------------------------------------------------------
// Name: OS (namespace)
// Desc: Scopes the OS classes
// ----------------------------------------------------------------------------
namespace OS
{
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
      throw std::exception("Failed to create the thread");
  } // Thread


  // ------------------------------------------------------------------------
  // Name: Thread::~Thread
  // Desc: Destructor
  // ------------------------------------------------------------------------
  Thread::~Thread()
  {
    REF_COUNT_DTOR(Thread);

    if (TerminateThread(m_threadhandle, 0) == 0)
      throw std::exception("Failed to terminate the thread");

    if (CloseHandle(m_threadhandle) == 0)
      throw std::exception("Failed to close the thread");
  } // ~Thread


  // ------------------------------------------------------------------------
  // Name: Thread::Join
  // Desc: Join the thread
  // Retn: ThreadReturnType - the return value from the thread
  // ------------------------------------------------------------------------
  ThreadReturnType Thread::Join()
  {
    if (WaitForSingleObject(m_threadhandle, INFINITE) != 0)
      throw std::exception("Error joining thread!");

    DWORD exit_code;
    if (GetExitCodeThread(m_threadhandle, &exit_code) == 0)
      throw std::exception("Error joining thread!");

    if (CloseHandle(m_threadhandle) == 0)
      throw std::exception("Failed to close the thread");

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
      throw std::exception("Failed to create the event");
  } // Event


  // ------------------------------------------------------------------------
  // Name: Event::~Event
  // Desc: Destructor
  // ------------------------------------------------------------------------
  Event::~Event()
  {
    REF_COUNT_DTOR(Event);

    if (!::SetEvent(m_event))
      throw std::exception("Failed to set the event");

    if (!CloseHandle(m_event))
      throw std::exception("Failed to close the event handle");
  } // ~Event


  // ------------------------------------------------------------------------
  // Name: Event::Set
  // Desc: Set the event
  // ------------------------------------------------------------------------
  void Event::Set()
  {
    if (!::SetEvent(m_event))
      throw std::exception("Failed to set the event");
  } // Set


  // ------------------------------------------------------------------------
  // Name: Event::Wait
  // Desc: Wait for the event to be set
  // ------------------------------------------------------------------------
  void Event::Wait()
  {
    if (WaitForSingleObject(m_event, INFINITE) == WAIT_FAILED)
      throw std::exception("Failed to wait for the event");
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
      throw std::exception("Failed to create the mutex");
  } // Mutex


  // ------------------------------------------------------------------------
  // Name: Mutex::~Mutex
  // Desc: Destructor
  // ------------------------------------------------------------------------
  Mutex::~Mutex()
  {
    REF_COUNT_DTOR(Mutex);

    if (!CloseHandle(m_mutex))
      throw std::exception("Failed to close the mutex handle");
  } // ~Mutex


  // ------------------------------------------------------------------------
  // Name: Mutex::Acquire
  // Desc: Acquire the mutex
  // ------------------------------------------------------------------------
  void Mutex::Acquire()
  {
    if (WaitForSingleObject(m_mutex, INFINITE) == WAIT_FAILED)
      throw std::exception("Failed to acquire the mutex");
  } // Acquire


  // ------------------------------------------------------------------------
  // Name: Mutex::Release
  // Desc: Release the mutex
  // ------------------------------------------------------------------------
  void Mutex::Release()
  {
    if (!ReleaseMutex(m_mutex))
      throw std::exception("Failed to release the mutex");
  } // Release


}; // namespace OS


// -- EOF


