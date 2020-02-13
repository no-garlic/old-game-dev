
#ifndef __I_PAD_H_
#define __I_PAD_H_

#include "libStandard.h"
#include "libMaths.h"
#include "GameObjectInterface.h"
#include "GameObjectInterfaceId.h"


class IPad : public GameObjectInterface
{
public:
  DECLARE_TYPE_INFO(GameObjectInterface);

  enum { ID = GOI_PAD };

  IPad();
  virtual ~IPad();

  virtual void Update(float deltaTime) = 0;
  
private:

};


#endif // __I_PAD_H_

// -- EOF


