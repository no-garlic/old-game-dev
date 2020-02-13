
#ifndef __GAME_SCENE_H_
#define __GAME_SCENE_H_


#include "libEngine.h"
#include "Animation.h"
#include "Actor.h"


class GameScene
{
public:
  GameScene();
  ~GameScene();

  bool Init();

  void SetRenderState();

  void Update(float deltaTime);
  void Render();

private:
  Actor      *m_pActor;
  LightArray  m_Lights;

};


#endif // __GAME_SCENE_H_

// -- EOF

