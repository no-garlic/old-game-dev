
#include "Actor.h"


Actor::Actor()
{
  m_pMotion = new Motion();
}


Actor::~Actor()
{
  delete m_pMotion;
}


bool Actor::Load()
{
  FileHandle handle = Application.GetModelDatabase()->FindFileHandle("skeleton.cfg");
  if (!m_pMotion->Load(handle))
    return false;

  FileHandle animationTableHandle = Application.GetModelDatabase()->FindFileHandle("skeleton.ant");
  AnimationTable *pAnimationTable = new AnimationTable();
  if (!pAnimationTable->Load(animationTableHandle))
    return false;

  m_pMotion->GetMixer()->SetAnimationTable(pAnimationTable);
  return true;
}


void Actor::Update(float deltaTime)
{
  static int z = 0;
  z++;

  if (z == 50)
  {
    m_pMotion->GetMixer()->ExecuteAction("Wave", 0.0f, 0.0f);
  }

  m_pMotion->Update(deltaTime);
}


void Actor::Render(const LightArray &lights)
{
  Matrix m = MatrixIdentity;
  m.PostMultiply(Matrix::MakeNewRotationAxis(Vec3(-1.0f, 0.0f, 0.0f), D3DX_PI / 2.0f));
  m.PostMultiply(Matrix::MakeNewRotationAxis(Vec3(0.0f, 0.0f, 1.0f), D3DX_PI / 1.15f));

  RenderList rl;
  rl.Add(m_pMotion->GetMesh(), m);
  rl.Render(lights);

}


// -- EOF


