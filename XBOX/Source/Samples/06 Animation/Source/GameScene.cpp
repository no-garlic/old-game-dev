

#include "GameScene.h"


GameScene::GameScene()
: m_pActor    (NULL)
{
}


GameScene::~GameScene()
{
  delete m_pActor;
}


bool GameScene::Init()
{
  // Create the actor
  m_pActor = new Actor();

  // Load the actor
  if (!m_pActor->Load())
  {
    return false;
  }

  // Play the walk animation (looping)
  AnimationMixer *pMixer = m_pActor->GetMotion()->GetMixer();
  pMixer->BlendCycle("Walk", 1.0f, 0.0f);
 
  // Add a directional light
  m_Lights.push_back(new DirectionalLight(Vec3(0.0f, 0.7f, 0.7f), Color::Gray, Color::White, Color::Gray));

  SetRenderState();
  return true;
}


void GameScene::SetRenderState()
{
  // Set the view matrix
  Vec3 eye(0.0f, 200.0f, -300.0f);
  Vec3 at(0.0f, 100.0f, 0.0f);
  Vec3 up(0.0f, 1.0f, 0.0f);
  Camera.LookAt(eye, at, up);

  // Set the projection matrix
  Camera.SetProjPerspective(45.0f, Application.CalculateAspectRatio(), 1.0f, 5000.0f);

  // Set the lights
  for (uint i = 0; i < m_Lights.size(); i++)
  {
    D3DLIGHT *pLight = m_Lights[i];

    Device->SetLight(i, pLight);
    Device->LightEnable(i, TRUE);

    RenderState.Set(D3DRS_LIGHTING, TRUE);
  }
}


void GameScene::Update(float deltaTime)
{
  m_pActor->Update(deltaTime);
}


void GameScene::Render()
{
  m_pActor->Render(m_Lights);
}


// -- EOF

