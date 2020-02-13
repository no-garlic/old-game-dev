
#include "AnimationTable.h"


AnimationTable::AnimationTable()
{
}


AnimationTable::~AnimationTable()
{
  // TODO
}


bool AnimationTable::Load(FileHandle handle)
{
  ConfigFile cfg;
  if (!cfg.Load(handle.GetAbsoluteFilename()))
  {
    LOG_ERROR << "Failed to load the animation table from: " << handle << ENDLOG;
    return FALSE;
  }

  if (cfg.GetSections().size() != 1)
  {
    LOG_ERROR << "The animation table config file must have 1 section" << ENDLOG;
    return FALSE;
  }

  const ConfigSection &section = cfg.GetSections().begin()->second;
  ConfigValueMap::const_iterator iter(section.Items.begin()), end(section.Items.end());
  for (; iter != end; ++iter)
  {
    String name = iter->second.Key;
    String file = iter->second.Value;

    if (FindAnimation(name) != NULL)
    {
      LOG_ERROR << "Duplicate animation found (" << name << ") in file: " << handle << ENDLOG;
      return false;
    }

    FileHandle animHandle = Application.GetModelDatabase()->FindFileHandle(file);
    Animation *pAnimation = new Animation(name);

    if (!pAnimation->Load(animHandle))
    {
      LOG_ERROR << "Failed to load the anmation: " << name << " from: " << file << ENDLOG;
      delete pAnimation;
      return FALSE;
    }

    m_AnimationArray.push_back(pAnimation);
    m_AnimationMap.insert(MakePair(name, pAnimation));
  }

  return true;
}


uint AnimationTable::GetCount()
{
  return m_AnimationArray.size();
}


Animation *AnimationTable::GetAnimation(uint index)
{
  ASSERT(index < m_AnimationArray.size(), "Index out of bounds");
  return m_AnimationArray[index];
}


Animation *AnimationTable::FindAnimation(const String &name)
{
  Map<String, Animation *>::iterator iter = m_AnimationMap.find(name);
  if (iter == m_AnimationMap.end())
    return NULL;

  return iter->second;
}


// -- EOF

