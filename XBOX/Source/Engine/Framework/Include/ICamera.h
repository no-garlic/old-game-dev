
#ifndef __I_CAMERA_H_
#define __I_CAMERA_H_

#include "libStandard.h"
#include "libMaths.h"
#include "GameObjectInterface.h"
#include "GameObjectInterfaceId.h"


class ICamera : public GameObjectInterface
{
public:
  DECLARE_TYPE_INFO(GameObjectInterface);

  enum { ID = GOI_CAMERA };

  ICamera();
  virtual ~ICamera();

  virtual void Update(float deltaTime) = 0;
  
private:

};


#endif // __I_CAMERA_H_

// -- EOF


