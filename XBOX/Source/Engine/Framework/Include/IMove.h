
#ifndef __I_MOVE_H_
#define __I_MOVE_H_

#include "libStandard.h"
#include "libMaths.h"
#include "GameObjectInterface.h"
#include "GameObjectInterfaceId.h"


class IMove : public GameObjectInterface
{
public:
  DECLARE_TYPE_INFO(GameObjectInterface);

  enum { ID = GOI_MOVE };

  IMove();
  virtual ~IMove();

  virtual void Update(float deltaTime) = 0;
  
private:

};


#endif // __I_MOVE_H_

// -- EOF


