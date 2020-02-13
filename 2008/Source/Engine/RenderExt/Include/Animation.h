
#ifndef __ANIMATION_H_
#define __ANIMATION_H_


#include "libRenderCore.h"
#include "libCal3D.h"


class AnimationMixer;


class Animation : private Unique
{
public:
  Animation(const String &name);
  ~Animation();

  const String &GetName() const     { return m_Name; }
  void SetName(const String &name)  { m_Name = name; }

  bool Load(FileHandle handle);

  float GetDuration() const;

private:
  friend class AnimationMixer;

  CalCoreAnimation *m_pCalCoreAnimation;
  String            m_Name;

};


#endif // __ANIMATION_H_


// -- EOF


