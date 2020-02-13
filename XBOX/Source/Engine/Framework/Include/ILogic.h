
#ifndef __I_LOGIC_H_
#define __I_LOGIC_H_

#include "libStandard.h"
#include "libMaths.h"
#include "GameObjectInterface.h"
#include "GameObjectInterfaceId.h"


class ILogic : public GameObjectInterface
{
public:
  DECLARE_TYPE_INFO(GameObjectInterface);

  enum { ID = GOI_LOGIC };

  ILogic();
  virtual ~ILogic();

  virtual void Update(float deltaTime) = 0;
  
private:

};


#endif // __I_LOGIC_H_

// -- EOF


