
#ifndef __I_SOUND_H_
#define __I_SOUND_H_

#include "libStandard.h"
#include "libMaths.h"
#include "GameObjectInterface.h"
#include "GameObjectInterfaceId.h"


class ISound : public GameObjectInterface
{
public:
  DECLARE_TYPE_INFO(GameObjectInterface);

  enum { ID = GOI_SOUND };

  ISound();
  virtual ~ISound();

  virtual void Update(float deltaTime) = 0;
  
private:

};


#endif // __I_SOUND_H_

// -- EOF


