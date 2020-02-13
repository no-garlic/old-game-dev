
#include "AnimationMixer.h"


AnimationMixer::AnimationMixer()
: m_pCalCoreModel   (NULL),
  m_pCalModel       (NULL),
  m_pCalMixer       (NULL),
  m_pAnimationTable (NULL)
{
}


AnimationMixer::~AnimationMixer()
{
}


bool AnimationMixer::SetAnimationTable(AnimationTable *pAnimationTable)
{
  NULL_ASSERT(m_pCalCoreModel);
  NULL_ASSERT(m_pCalMixer);
  NULL_ASSERT(pAnimationTable);

  if (m_pAnimationTable)
  {
    LOG_ERROR << "The animation table has already been set" << ENDLOG;
    return false;
  }

  m_pAnimationTable = pAnimationTable;

  m_pCalCoreModel->unloadAllCoreAnimations();

  for (uint i = 0; i < pAnimationTable->GetCount(); i++)
  {
    Animation *pAnimation = pAnimationTable->GetAnimation(i);
    int id = m_pCalCoreModel->addCoreAnimation(pAnimation->m_pCalCoreAnimation);
    m_pCalCoreModel->addAnimationName(pAnimation->GetName(), id);
  }

  m_pCalMixer->updateAnimationTable();
  return true;
}


bool AnimationMixer::BlendCycle(const String &animName, float weight, float delay)
{
  NULL_ASSERT(m_pCalMixer);
  int id = m_pCalCoreModel->getCoreAnimationId(animName);
  return m_pCalMixer->blendCycle(id, weight, delay);
}


bool AnimationMixer::ClearCycle(const String &animName, float delay)
{
  NULL_ASSERT(m_pCalMixer);
  int id = m_pCalCoreModel->getCoreAnimationId(animName);
  return m_pCalMixer->clearCycle(id, delay);
}


bool AnimationMixer::ExecuteAction(const String &animName, float delayIn, float delayOut, float weightTarget, bool autoLock)
{
  NULL_ASSERT(m_pCalMixer);
  int id = m_pCalCoreModel->getCoreAnimationId(animName);
  return m_pCalMixer->executeAction(id, delayIn, delayOut, weightTarget, autoLock);
}


bool AnimationMixer::RemoveAction(const String &animName)
{
  NULL_ASSERT(m_pCalMixer);
  int id = m_pCalCoreModel->getCoreAnimationId(animName);
  return m_pCalMixer->removeAction(id);
}


float AnimationMixer::GetAnimationDuration()
{
  NULL_ASSERT(m_pCalMixer);
  return m_pCalMixer->getAnimationDuration();
}


float AnimationMixer::GetAnimationTime()
{
  NULL_ASSERT(m_pCalMixer);
  return m_pCalMixer->getAnimationTime();
}


void AnimationMixer::SetAnimationTime(float animationTime)
{
  NULL_ASSERT(m_pCalMixer);
  m_pCalMixer->setAnimationTime(animationTime);
}


void AnimationMixer::SetTimeFactor(float timeFactor)
{
  NULL_ASSERT(m_pCalMixer);
  m_pCalMixer->setTimeFactor(timeFactor);
}


float AnimationMixer::GetTimeFactor()
{
  NULL_ASSERT(m_pCalMixer);
  return m_pCalMixer->getTimeFactor();
}


// -- EOF

