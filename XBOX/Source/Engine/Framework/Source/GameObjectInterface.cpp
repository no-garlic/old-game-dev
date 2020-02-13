

#include "GameObjectInterface.h"


IMPLEMENT_TYPE_INFO(GameObjectInterface);


GameObjectInterface::GameObjectInterface()
: Parent        (),
  m_pGameObject (NULL)
{
}


GameObjectInterface::~GameObjectInterface()
{
}


bool GameObjectInterface::Init()
{
  return true;
}


void GameObjectInterface::Shutdown()
{
}


void GameObjectInterface::Update(float deltaTime)
{
}


// -- EOF

