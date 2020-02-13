
#ifndef __GAME_UI_H_
#define __GAME_UI_H_


#include "libEngine.h"


class GameUI : private Unique
{
public:
  GameUI();
  virtual ~GameUI();

  bool Init();
  void Shutdown();

  void Update();
  void Draw();

  void SetRenderingEnabled(bool enabled);

  void ShowLoadingSequence();
  void HideLoadingSequence();
  uint GetLoadingSequenceProgress();

};


#endif // __GAME_UI_H_

// -- EOF

