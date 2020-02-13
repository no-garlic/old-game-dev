
#ifndef __GAME_SCENE_H_
#define __GAME_SCENE_H_


#include "libEngine.h"


class GameScene : private Unique
{
public:
  GameScene();
  virtual ~GameScene();

  bool Init();
  void Shutdown();

  void Update();
  void Cull();
  void Draw();

  void SetRenderState();

  void SetRenderingEnabled(bool enabled);


  // Get Player

  // Static Object Array

  // Dynamic Object Array

  // Load / Save (background)

  // Lights


};


#endif // __GAME_SCENE_H_

// -- EOF

