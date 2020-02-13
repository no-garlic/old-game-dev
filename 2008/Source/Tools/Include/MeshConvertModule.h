
#ifndef __MESH_CONVERT_MODULE_H_
#define __MESH_CONVERT_MODULE_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libEngine.h"


// ----------------------------------------------------------------------------
// Name: MeshConvertModule  (class)
// Desc: Converts meshes
// ----------------------------------------------------------------------------
class MeshConvertModule : public ApplicationModule_NoGfx
{
public:
  // --------------------------------------------------------------------------
  // Constructor and Destructor
  // --------------------------------------------------------------------------
  MeshConvertModule(const String &name);
  virtual ~MeshConvertModule();

  // --------------------------------------------------------------------------
  // Process Functions
  // --------------------------------------------------------------------------
  virtual int Run(const String &commandLine);

private:
  // --------------------------------------------------------------------------
  // Private methods
  // --------------------------------------------------------------------------
  int ConvertNoFrames();

}; // class MeshConvertModule


#endif // __MESH_CONVERT_MODULE_H_

// -- EOF



