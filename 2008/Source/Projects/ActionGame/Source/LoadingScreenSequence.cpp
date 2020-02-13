
#include "LoadingScreenSequence.h"


LoadingScreenSequence::LoadingScreenSequence()
{
  REF_COUNT_CTOR(LoadingScreenSequence);

  m_pUI           = NULL;
  m_pFadeImage    = NULL;

  m_HasFinished   = false;
  m_Progress      = 0.0f;
  m_FadeTime      = 0.0f;
  m_TotalTime     = 0.0f;
  m_ElapsedTime   = 0.0f;
}


LoadingScreenSequence::~LoadingScreenSequence()
{
  REF_COUNT_DTOR(LoadingScreenSequence);

  delete m_pUI;
}


bool LoadingScreenSequence::Init(FileHandle handle)
{
  // Create the user interface
  m_pUI = UIConfig::Create(handle);
  CHECK(m_pUI, return false);

  // Get the fade layer
  UILayer *pFadeLayer = m_pUI->GetLayer("FadeLayer");
  CHECK(pFadeLayer, return false);

  // Get the image layer
  UILayer *pImageLayer = m_pUI->GetLayer("ImageLayer");
  CHECK(pImageLayer, return false);

  // Get the fade image
  UIComponent *pComponent = pFadeLayer->FindComponent("FadeGroup/FadeImage");
  CHECK(pComponent, return false);
  CHECK(pComponent->IsOfType(UI_Image), return false);
  m_pFadeImage = (UIImage *) pComponent;

  // Get the image group
  pComponent = pImageLayer->FindComponent("ImageGroup");
  CHECK(pComponent, return false);
  CHECK(pComponent->IsOfType(UI_Group), return false);

  // Get the child components
  UIComponentArray &components = ((UIGroup *) pComponent)->GetComponents();
  UIComponentArray::iterator iter(components.begin()), end(components.end());
  for (; iter != end; ++iter)
  {
    pComponent = iter->second;
    if (pComponent->IsOfType(UI_Image))
    {
      m_LoadingScreenImages.push_back((UIImage *) pComponent);
    }
  }

  // Check that we found some loading screen images
  if (m_LoadingScreenImages.empty())
  {
    LOG_ERROR << "No loading screen iamges found" << ENDLOG;
    return false;
  }

  return true;
}


void LoadingScreenSequence::Start(float imageTime, float fadeTime)
{
  m_TotalTime   = imageTime * m_LoadingScreenImages.size();
  m_ElapsedTime = 0.0f;
  m_HasFinished = false;
  m_Progress    = 0.0f;
  m_FadeTime    = fadeTime * 0.5f;

  if (m_LoadingScreenImages.size())
  {
    m_LoadingScreenImages[0]->SetVisible(true);
  }

  m_pFadeImage->SetAlpha(1.0f);
  m_pFadeImage->SetVisible(true);
}


uint LoadingScreenSequence::GetProgress()
{
  return (uint) m_Progress;
}


bool LoadingScreenSequence::HasFinished()
{
  return m_HasFinished;
}


void LoadingScreenSequence::Update()
{
  m_ElapsedTime += Application.GetFrameTime();
  m_Progress = (100.0f * m_ElapsedTime) / m_TotalTime;

  if (m_ElapsedTime >= m_TotalTime)
  {
    m_HasFinished = true;
    m_Progress    = 100.0f;
    return;
  }

  UpdateImage();
  UpdateTransition();
}


void LoadingScreenSequence::UpdateImage()
{
  uint count = m_LoadingScreenImages.size();

  float progressEach = 100.0f / count;
  uint index = Min<uint>((uint) (m_Progress / progressEach), count - 1);

  for (uint i = 0; i < count; i++)
  {
    m_LoadingScreenImages[i]->SetVisible(false);
  }

  m_LoadingScreenImages[index]->SetVisible(true);
}


void LoadingScreenSequence::UpdateTransition()
{
  uint count = m_LoadingScreenImages.size();
  float timeEach = m_TotalTime / (float) count;

  m_pFadeImage->SetVisible(false);

  for (uint i = 0; i < count + 1; i++)
  {
    float t = timeEach * i;

    float t2 = fabs(t - m_ElapsedTime);
    if (t2 < m_FadeTime)
    {
      float alpha = 1.0f - (t2 / m_FadeTime);

      m_pFadeImage->SetAlpha(alpha);
      m_pFadeImage->SetVisible(true);
    }
  }
}


void LoadingScreenSequence::Render()
{
  m_pUI->Render();
}


// -- EOF

