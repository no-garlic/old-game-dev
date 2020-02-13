// ----------------------------------------------------------------------------
// File: DeviceObject.h
// Desc: Interface for any object that allocates device memory
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __DEVICE_OBJECT_H_
#define __DEVICE_OBJECT_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libStandard.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Application;


// TODO: Make sure these functions are not called until a device is lost!!
// then they will be safe to eliminate on xbox

// ----------------------------------------------------------------------------
// Name: DeviceObject (class)
// Desc: Base class for device objects such as textures and meshes
// ----------------------------------------------------------------------------
class DeviceObject
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  DeviceObject();
  virtual ~DeviceObject();

protected:
  // --------------------------------------------------------------------------
  // Friends
  // --------------------------------------------------------------------------
  friend class ApplicationCentral;

  // --------------------------------------------------------------------------
  // Protected methods
  // --------------------------------------------------------------------------
  virtual bool AllocateDeviceMemory() = 0;
  virtual bool ReleaseDeviceMemory() = 0;

}; // class DeviceObject


#endif // __DEVICE_OBJECT_H_

// -- EOF

