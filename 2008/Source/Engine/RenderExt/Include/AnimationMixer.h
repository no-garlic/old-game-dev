
#ifndef __ANIMATION_MIXER_H_
#define __ANIMATION_MIXER_H_


#include "libRenderCore.h"
#include "libCal3D.h"
#include "Animation.h"
#include "AnimationTable.h"


class AnimationMixer
{
public:
  // Destructor
  ~AnimationMixer();

  // Set the animation table
  bool SetAnimationTable(AnimationTable *pAnimationTable);
  AnimationTable *GetAnimationTable() { return m_pAnimationTable; }

  // Looping animations (lower priority)
  bool BlendCycle(const String &animName, float weight, float delay);
  bool ClearCycle(const String &animName, float delay);
  
  // One-Shot animations (higher priority)
  bool ExecuteAction(const String &animName, float delayIn, float delayOut, float weightTarget = 1.0f, bool autoLock = false);
  bool RemoveAction(const String &animName);
  
  // The animation duration
  float GetAnimationDuration();  

  // The animation time
  float GetAnimationTime();
  void SetAnimationTime(float animationTime);

  // The time factor
  void SetTimeFactor(float timeFactor);
  float GetTimeFactor();

private:
  // Allow this class to be constructed by Actor
  friend class Motion;
  AnimationMixer();

private:
  // Private members
  CalCoreModel     *m_pCalCoreModel;    // The core model
  CalModel         *m_pCalModel;        // The instance model
  CalMixer         *m_pCalMixer;        // The animation mixer
  AnimationTable   *m_pAnimationTable;  // The animation table
  
};


#endif // __ANIMATION_MIXER_H_

// -- EOF

