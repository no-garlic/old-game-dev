
#ifndef __GAME_OBJECT_INTERFACE_H_
#define __GAME_OBJECT_INTERFACE_H_


#include "libStandard.h"
#include "Object.h"
#include "GameObject.h"
#include "GameObjectInterfaceId.h"

class GameObject;



class GameObjectInterface : public Object
{
public:
  DECLARE_TYPE_INFO(Object);

  GameObjectInterface();
  virtual ~GameObjectInterface();

  GameObject *GetObject() { return m_pGameObject; }
  const GameObject *GetObject() const { return m_pGameObject; }

  virtual bool Init();
  virtual void Shutdown();

  virtual void Update(float deltaTime);

private:
  friend class GameObject;

  void SetObject(GameObject *pGameObject) { m_pGameObject = pGameObject; }

  GameObject *m_pGameObject;

};


#endif // __GAME_OBJECT_INTERFACE_H_

// -- EOF

