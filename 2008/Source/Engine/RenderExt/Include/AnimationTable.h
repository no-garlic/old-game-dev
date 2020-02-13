
#ifndef __ANIMATION_TABLE_H_
#define __ANIMATION_TABLE_H_


#include "libRenderCore.h"
#include "Animation.h"


class AnimationTable
{
public:
  AnimationTable();
  ~AnimationTable();

  // Load the animation table
  bool Load(FileHandle handle);

  // Get the number of animations
  uint GetCount();

  // Get an animation by index
  Animation *GetAnimation(uint index);

  // Find an animation by name
  Animation *FindAnimation(const String &name);

private:
  // Private members
  Map<String, Animation *>  m_AnimationMap;
  Array<Animation *>        m_AnimationArray;

};


#endif // __ANIMATION_TABLE_H_

// -- EOF

