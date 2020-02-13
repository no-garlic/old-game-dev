
#include "Animation.h"


Animation::Animation(const String &name)
: m_Name              (name),
  m_pCalCoreAnimation (NULL)
{
}


Animation::~Animation()
{
  // TODO: 
}


bool Animation::Load(FileHandle handle)
{
  m_pCalCoreAnimation = CalLoader::loadCoreAnimation(handle.GetAbsoluteFilename());
  if (!m_pCalCoreAnimation)
  {
    LOG_ERROR << "Failed to load the animation file: " << handle << ENDLOG;
    return false;
  }

  return true;
}


float Animation::GetDuration() const
{
  if (m_pCalCoreAnimation)
  {
    return m_pCalCoreAnimation->getDuration();
  }

  return 0.0f;
}



// -- EOF

