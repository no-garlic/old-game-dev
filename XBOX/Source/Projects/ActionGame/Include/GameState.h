
#ifndef __GAME_STATE_H_
#define __GAME_STATE_H_


#include "libEngine.h"


#define GameState GameStateManager::GetInstance()


class GameStateManager : private Unique
{
public:
  static GameStateManager &GetInstance();
  static void DestroyInstance();

  bool Init();

  bool OnStartupComplete();



private:
  GameStateManager();
  virtual ~GameStateManager();

  static GameStateManager *s_pInstance;

};


#endif // __GAME_STATE_H_

// -- EOF

