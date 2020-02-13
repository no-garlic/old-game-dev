
#ifndef __GAME_UI_H_
#define __GAME_UI_H_


#include "libEngine.h"
#include "LoadingScreenSequence.h"
#include "GameFrontEnd.h"


class GameUI : private Unique
{
public:
  GameUI();
  virtual ~GameUI();

  bool Init();
  void Shutdown();

  void Update();
  void Render();

  void SetRenderingEnabled(bool enabled);

  void ShowLoadingSequence();
  void HideLoadingSequence();
  uint GetLoadingSequenceProgress();

  void ShowLevelLoadingScreen();
  void HideLevelLoadingScreen();
  void SetLevelLoadingProgress(uint progress);

  void ShowFrontEnd();
  void HideFrontEnd();
  GameFrontEnd &GetFrontEnd() { return m_GameFrontEnd; }

private:
  LoadingScreenSequence   m_LoadingScreenSequence;
  GameFrontEnd            m_GameFrontEnd;
  bool                    m_RenderingDisabled;
  bool                    m_ShowLoadingScreen;
  bool                    m_ShowFrontEnd;

};


#endif // __GAME_UI_H_

// -- EOF

