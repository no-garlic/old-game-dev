
#ifndef __ACTOR_H_
#define __ACTOR_H_


#include "libRenderExt.h"
#include "Motion.h"


class Actor : private Unique
{
public:
  Actor();
  virtual ~Actor();

  bool Load();

  void Update(float deltaTime);
  void Render(const LightArray &lights);

  Motion *GetMotion() { return m_pMotion; }

private:
  Motion *m_pMotion;
};


#endif // __ACTOR_H_


// -- EOF


