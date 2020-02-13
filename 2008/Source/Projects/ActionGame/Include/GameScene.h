
#ifndef __GAME_SCENE_H_
#define __GAME_SCENE_H_


#include "libEngine.h"


class GameLevel;

class GameScene : private Unique
{
public:
  GameScene();
  virtual ~GameScene();

  bool Init();
  void Shutdown();

  void App();
  void Cull();
  void Draw();

  void SetRenderState();

  void SetRenderingEnabled(bool enabled);

  void ChangeLevel(GameLevel *pLevel);
  GameLevel *GetLevel() { return m_pLevel; }

private:
  GameLevel    *m_pLevel;
  bool          m_RenderingEnabled;

};


#endif // __GAME_SCENE_H_

// -- EOF

