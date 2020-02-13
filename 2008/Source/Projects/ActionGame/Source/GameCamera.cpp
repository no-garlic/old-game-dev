
#include "GameCamera.h"


GameCamera::GameCamera()
{
  REF_COUNT_CTOR(GameCamera);
}


GameCamera::~GameCamera()
{
  REF_COUNT_DTOR(GameCamera);
}


bool GameCamera::Init()
{
  return true;
}


void GameCamera::Shutdown()
{
}


void GameCamera::Update()
{
}


void GameCamera::SetRenderState()
{
  // Get the aspect ratio of the main window
  float aspect = Application.CalculateAspectRatio();
  float fov = 45.0f;

  // Set the global camera perspective projection (proj matrix)
  Camera.SetProjPerspective(fov, aspect, 1.0f, 5000.0f);

  // Set the global camera lookat vectors (view matrix)
  Vec3 eye(0.0f, 250.0f, 750.0f);
  Vec3  at(0.0f, 0.0f, 0.0f);
  Vec3  up(0.0f, 1.0f, 0.0f);
  Camera.LookAt(eye, at, up);
}


// -- EOF

