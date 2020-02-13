

#ifndef __I_ANIMATE_H_
#define __I_ANIMATE_H_

#include "libStandard.h"
#include "libMaths.h"
#include "GameObjectInterface.h"
#include "GameObjectInterfaceId.h"


class IAnimate : public GameObjectInterface
{
public:
  DECLARE_TYPE_INFO(GameObjectInterface);

  enum { ID = GOI_ANIMATION };

  IAnimate();
  virtual ~IAnimate();

  virtual void Update(float deltaTime) = 0;

private:

};


#endif // __I_ANIMATE_H_

// -- EOF


