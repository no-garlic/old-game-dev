
#ifndef __I_HUD_H_
#define __I_HUD_H_

#include "libStandard.h"
#include "libMaths.h"
#include "GameObjectInterface.h"
#include "GameObjectInterfaceId.h"


class IHud : public GameObjectInterface
{
public:
  DECLARE_TYPE_INFO(GameObjectInterface);

  enum { ID = GOI_HUD };

  IHud();
  virtual ~IHud();

  virtual void Update(float deltaTime) = 0;
  
private:

};


#endif // __I_HUD_H_

// -- EOF


