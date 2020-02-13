
#ifndef __LIB_RENDER_CORE_H_
#define __LIB_RENDER_CORE_H_


#include "libStandard.h"
#include "libMaths.h"


#include "ApplicationCentral.h"
#include "ApplicationModule.h"
#include "Camera3D.h"
#include "DeviceObject.h"
#include "DisplaySettings.h"
#include "Input.h"
#include "RenderTarget.h"
#include "RenderState.h"


#if XBOX
#include "ApplicationModule_Xbox.h"
#include "Input_Xbox.h"
#else
#include "ApplicationModule_NoGfx.h"
#include "ApplicationModule_Win32.h"
#include "Input_PC.h"
#endif


#endif // __LIB_RENDER_CORE_H_

// -- EOF


