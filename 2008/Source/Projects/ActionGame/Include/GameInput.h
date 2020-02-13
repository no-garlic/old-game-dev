
#ifndef __GAME_INPUT_H_
#define __GAME_INPUT_H_


#include "libEngine.h"


class GameInput : private Unique
{
public:
  GameInput();
  virtual ~GameInput();

  bool Init();
  void Shutdown();

  void Update();

};


#endif // __GAME_INPUT_H_

// -- EOF

