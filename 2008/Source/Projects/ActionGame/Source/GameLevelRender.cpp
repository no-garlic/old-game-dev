
#include "GameLevelRender.h"


GameLevelRender::GameLevelRender()
{
}


GameLevelRender::~GameLevelRender()
{
  for (uint i = 0; i < m_StaticMeshes.size(); i++)
  {
    SafeUnRef(m_StaticMeshes[i]);
  }

  for (uint i = 0; i < m_GameLights.size(); i++)
  {
    SafeUnRef(m_GameLights[i]);
  }
}


void GameLevelRender::App()
{
}


void GameLevelRender::Cull()
{
  for (uint i = 0; i < m_StaticMeshes.size(); i++)
  {
    StaticMesh *pMesh = m_StaticMeshes[i];

    if (Camera.GetFrustum().Intersects(pMesh->GetMesh()->GetBSphere()) != Frustum::OUT_FRUSTUM)
    {
      m_RenderList.Add(pMesh->GetMesh(), pMesh->GetWorldTransform());
    }
  }
}


void GameLevelRender::Draw()
{
  for (uint i = 0; i < m_Lights.size(); i++)
  {
    Device->SetLight(i, m_Lights[i]);
    Device->LightEnable(i, TRUE);
  }

  m_RenderList.Render(m_Lights);
}


void GameLevelRender::AddStaticMesh(StaticMesh *pStaticMesh)
{
  SafeRef(pStaticMesh);
  m_StaticMeshes.push_back(pStaticMesh);
}


void GameLevelRender::AddLight(GameLight *pLight)
{
  SafeRef(pLight);
  m_GameLights.push_back(pLight);
  m_Lights.push_back(pLight->GetLight());
}


void GameLevelRender::SetRenderState()
{
  RenderState.Set(D3DRS_LIGHTING, TRUE);
}


// -- EOF

