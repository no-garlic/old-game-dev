// ----------------------------------------------------------------------------
// File: OSFunctions.h
// Desc: This file contains operating system funtionality for the Microsoft 
//       Windows platform, in a platform-interface inspecific way.
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef OS_FUNCTIONS_H
#define OS_FUNCTIONS_H


// ----------------------------------------------------------------------------
// OSFunctions includes
// ----------------------------------------------------------------------------
#include <windows.h>
#include <vector>
#include "Common/Exceptions.h"


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
// Desc: Wrap all OS funtions in this namespace
// ----------------------------------------------------------------------------
namespace OS
{
    // ------------------------------------------------------------------------
    // Thread handle and thread function types
    // ------------------------------------------------------------------------
    typedef void (*ThreadHandle);
    typedef unsigned long (*ThreadFunc) (void *);


    // ------------------------------------------------------------------------
    // Generic handle type
    // ------------------------------------------------------------------------
    typedef void (*Handle);


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
    ThreadHandle    GetCurrentThread();
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
    int             WaitForMultipleObjects(std::vector <Handle> &objects, unsigned long timeout);


    // ------------------------------------------------------------------------
    // Counter functions
    // ------------------------------------------------------------------------
    CounterInfo     GetCounter() throw();
    CounterInfo     GetCounterFrequency() throw();
    float           CalculateTimeDifference(CounterInfo start, CounterInfo finish) throw();

}; // namespace OS


#endif // OS_FUNCTIONS_H

// -- EOF


