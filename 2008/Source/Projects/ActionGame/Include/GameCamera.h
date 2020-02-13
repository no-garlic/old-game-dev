
#ifndef __GAME_CAMERA_H_
#define __GAME_CAMERA_H_


#include "libEngine.h"


class GameCamera : private Unique
{
public:
  GameCamera();
  virtual ~GameCamera();

  bool Init();
  void Shutdown();

  void Update();

  void SetRenderState();

};


#endif // __GAME_CAMERA_H_

// -- EOF

