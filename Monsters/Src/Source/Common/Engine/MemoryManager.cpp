// ----------------------------------------------------------------------------
// File: MemoryManager.cpp
// Desc: A memory manager class that provides seperate copies of memory for 
//       different frames in the render cycle. Each variable that needs to 
//       share data between the application, the culling, or the draw code
//       in your application should be declared as a DataFlux<T>.  Each data
//       flux holds a copy of memory for each of the different threads that
//       the rendered has created. When reading or writing the memory, the
//       current context must be passed into the DataFlux so the correct
//       version of the variable is accessed. This is done through the call
//       operator.
//
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include <new>
#include <stdexcept>
#include "Engine/MemoryManager.h"


// ----------------------------------------------------------------------------
// Null the singleton instance
// ----------------------------------------------------------------------------
MemoryHeapManager* MemoryHeapManager::s_pInstance = 0;


// ----------------------------------------------------------------------------
// Name: MemoryHeap::MemoryHeap
// Desc: Constructor
// Parm: unsigned int numProcesses  - the number of processes
// Parm: unsigned int bytesPerHeap  - the number of bytes to allocate per heap (
//       per process)
// ----------------------------------------------------------------------------
MemoryHeap::MemoryHeap(unsigned int numProcesses, unsigned int bytesPerHeap)
: m_NumProcesses  (numProcesses),
  m_Stride        (bytesPerHeap),
  m_pNext         (0)
{
  REF_COUNT_CTOR(MemoryHeap);

  // Allocate the data
  m_Data = new unsigned char[numProcesses * bytesPerHeap];

  // Set the data indecies
  m_End     = bytesPerHeap;
  m_Current = 0;
} // MemoryHeap


// ----------------------------------------------------------------------------
// Name: MemoryHeap::~MemoryHeap
// Desc: Destructor
// ----------------------------------------------------------------------------
MemoryHeap::~MemoryHeap()
{
  REF_COUNT_DTOR(MemoryHeap);

  delete[] m_Data;
} // ~MemoryHeap


// ----------------------------------------------------------------------------
// Name: MemoryHeap::Alloc
// Desc: Allocate the given number of bytes
// Parm: unsigned char numBytes - the number of bytes to allocate
// Parm: unsigned char **ptr    - a pointer to the pointer to assign to the 
//       memory
// Retn: int                    - the stride between the processes or -1 if the 
//       heap is out of memory
// ----------------------------------------------------------------------------
int MemoryHeap::Alloc(unsigned char numBytes, unsigned char **ptr)
{
  // Get the next current position assuming this 
  // allocation succeeds.
  unsigned int next = m_Current + numBytes;

  // Check that we have enough memory
  if (next > m_End)
    return -1;

  // Assign the data pointer to the memory
  *ptr = m_Data + m_Current;

  // Advance the current pointer
  m_Current = next;

  // Return the stride of the array
  return m_Stride;
} // Alloc


// ----------------------------------------------------------------------------
// Name: MemoryHeap::Swap
// Desc: Copy the memory from the app process to the draw process
// Parm: unsigned int srcId  - the source memory section index
// Parm: unsigned int destId - the destination memory section index
// ----------------------------------------------------------------------------
void MemoryHeap::Swap(unsigned int srcId, unsigned int destId)
{
  // Get thge source (App) pointer and the destination (Draw) pointer.
  unsigned char *srcPtr = m_Data + (srcId  * m_Stride);
  unsigned char *dstPtr = m_Data + (destId * m_Stride);

  // Copy the allocated data (we use m_Current here as that is
  // the size of the allocated data).
  memcpy(dstPtr, srcPtr, m_Current * sizeof(unsigned char));
} // Swap


// ----------------------------------------------------------------------------
// Name: MemoryHeapManager::MemoryHeapManager
// Desc: Constructor
// ----------------------------------------------------------------------------
MemoryHeapManager::MemoryHeapManager()
: m_pFirst        (0),
  m_pCurrent      (0),
  m_NumProcesses  (0),
  m_BytesPerHeap  (0)
{
  REF_COUNT_CTOR(MemoryHeapManager);
} // DataFluxManager


// ----------------------------------------------------------------------------
// Name: MemoryHeapManager::~MemoryHeapManager
// Desc: Destructor
// ----------------------------------------------------------------------------
MemoryHeapManager::~MemoryHeapManager()
{
  REF_COUNT_DTOR(MemoryHeapManager);

  MemoryHeap *next = m_pFirst;
  while (next)
  {
    MemoryHeap *ptr = next;
    next = ptr->GetNext();

    delete ptr;
  } // while
} // ~DataFluxManager


// ----------------------------------------------------------------------------
// Name: MemoryHeapManager::GetInstance
// Desc: Get the singleton instance
// Retn: MemoryHeapManager & - he instance
// ----------------------------------------------------------------------------
MemoryHeapManager &MemoryHeapManager::GetInstance()
{
  if (!s_pInstance)
  {
    // Create the instance
    s_pInstance = new MemoryHeapManager();

    // Delete the instance on shutdown
    atexit(&MemoryHeapManager::DestroyInstance);
  } // if

  return *s_pInstance;
} // GetInstance


// ----------------------------------------------------------------------------
// Name: MemoryHeapManager::DestroyInstance
// Desc: Destroy the singleton instance (called by atexit).  Frees all used
//       memory and invalidate all DataFlux objects. Warning! this deletes
//       all of the allocated memory that the DataFluxes were using and all
//       DataFluxes are invalid after tis has been called.
// ----------------------------------------------------------------------------
void MemoryHeapManager::DestroyInstance()
{
  delete s_pInstance;
  s_pInstance = 0;
} // DestroyInstance


// ----------------------------------------------------------------------------
// Name: MemoryHeapManager::Init
// Desc: Initialise the manager
// Parm: unsigned int numProcesses  - the number of processes
// Parm: unsigned int bytesPerHeap  - the size of each heap
// ----------------------------------------------------------------------------
void MemoryHeapManager::Init(unsigned int numProcesses, unsigned int bytesPerHeap)
{
  if (m_pCurrent) 
    throw std::bad_exception(_MESG("Cannot initialise the memory manager more then once"));

  m_NumProcesses = numProcesses;
  m_BytesPerHeap = bytesPerHeap;

  m_pFirst = new MemoryHeap(numProcesses, bytesPerHeap);
  m_pCurrent = m_pFirst;
} // Init


// ----------------------------------------------------------------------------
// Name: MemoryHeapManager::Swap
// Desc: Copy from the app heap to the draw heap
// Parm: unsigned int appProcess   - the app process id (source)
// Parm: unsigned int drawProcess  - the draw process id (destination)
// ----------------------------------------------------------------------------
void MemoryHeapManager::Swap(unsigned int srcId, unsigned int destId)
{
  MemoryHeap *ptr = m_pFirst;
  while (ptr)
  {
    ptr->Swap(srcId, destId);
    ptr = ptr->GetNext();
  } // while
} // Swap


// -- EOF


