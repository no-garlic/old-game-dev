
#ifndef __GAME_LEVEL_RENDER_H_
#define __GAME_LEVEL_RENDER_H_


#include "libEngine.h"
#include "StaticMesh.h"
#include "GameLight.h"


class GameLevelRender : private Unique
{
public:
  GameLevelRender();
  virtual ~GameLevelRender();

  // Run the app process
  void App();

  // Cull the visible render items
  void Cull();

  // Render the visible items
  void Draw();

  // Set teh render state
  void SetRenderState();

  // Add a static mesh to the level
  void AddStaticMesh(StaticMesh *pStaticMesh);

  // Add a light to the level
  void AddLight(GameLight *pLight);

private:
  RenderList          m_RenderList;       // Render list for visible geometry
  Array<StaticMesh *> m_StaticMeshes;     // All static meshes
  Array<GameLight *>  m_GameLights;       // All game lights
  LightArray          m_Lights;           // All lights

};


#endif // __GAME_LEVEL_RENDER_H_

// -- EOF

