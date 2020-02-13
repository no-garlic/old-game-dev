// ----------------------------------------------------------------------------
// File: DeviceObject.h
// Desc: Interface for any object that allocates device memory
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "DeviceObject.h"
#include "ApplicationCentral.h"


// ----------------------------------------------------------------------------
// Name: DeviceObject::DeviceObject
// Desc: Constructor
// ----------------------------------------------------------------------------
DeviceObject::DeviceObject()
{
  Application.RegisterDeviceObject(this);
} // DeviceObject


// ----------------------------------------------------------------------------
// Name: DeviceObject::~DeviceObject
// Desc: Destructor
// ----------------------------------------------------------------------------
DeviceObject::~DeviceObject()
{
  Application.UnregisterDeviceObject(this);
} // ~DeviceObject


// -- EOF

