
#ifndef __I_PHYSICS_H_
#define __I_PHYSICS_H_

#include "libStandard.h"
#include "libMaths.h"
#include "GameObjectInterface.h"
#include "GameObjectInterfaceId.h"


class IPhysics : public GameObjectInterface
{
public:
  DECLARE_TYPE_INFO(GameObjectInterface);

  enum { ID = GOI_PHYSICS };

  IPhysics();
  virtual ~IPhysics();

  virtual void Update(float deltaTime) = 0;
  
private:

};


#endif // __I_PHYSICS_H_

// -- EOF


