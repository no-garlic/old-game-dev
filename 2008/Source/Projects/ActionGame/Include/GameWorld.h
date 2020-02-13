
#ifndef __GAME_WORLD_H_
#define __GAME_WORLD_H_


#include "libEngine.h"
#include "GameCamera.h"
#include "GameScene.h"
#include "GameUI.h"
#include "GameInput.h"
#include "GameAction.h"


#define GameWorld GameWorldManager::GetInstance()


class GameWorldManager : private Unique
{
public:
  static GameWorldManager &GetInstance();
  static void DestroyInstance();

  GameCamera  &GetCamera()  { return *m_pCamera; }
  GameScene   &GetScene()   { return *m_pScene;  }
  GameUI      &GetUI()      { return *m_pUI;     }
  GameInput   &GetInput()   { return *m_pInput;  }
  
  bool PushAction(GameAction *pAction);

  GameAction *GetCurrentAction()  { return m_pCurrentAction; }
  GameAction *GetPendingAction()  { return m_pPendingAction; }

  bool Init();
  void Shutdown();

  void App();
  void Cull();
  void Draw();

  void SetRenderState();
  
private:
  GameWorldManager();
  virtual ~GameWorldManager();

  static GameWorldManager  *s_pInstance;        // The singleton instance
  GameCamera               *m_pCamera;           // The game camera
  GameScene                *m_pScene;            // The game scene
  GameUI                   *m_pUI;               // The game user interface
  GameInput                *m_pInput;            // The game input

  GameAction               *m_pCurrentAction;   // The current action
  GameAction               *m_pPendingAction;   // The pending action

};


#endif // __GAME_WORLD_H_

// -- EOF

