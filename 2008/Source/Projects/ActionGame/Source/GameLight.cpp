
#include "GameLight.h"


IMPLEMENT_TYPE_INFO(GameLight);


GameLight::GameLight()
{
}


GameLight::~GameLight()
{
}


void GameLight::UpdateWorldTransform()
{
  Parent::UpdateWorldTransform();

  m_Light.Position  = m_WorldTransform.GetTAxis();
  m_Light.Direction = m_WorldTransform.GetYAxis();
}


// -- EOF