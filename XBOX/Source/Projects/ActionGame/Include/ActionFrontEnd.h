
#ifndef __ACTION_FRONT_END_H_
#define __ACTION_FRONT_END_H_


#include "libEngine.h"
#include "GameAction.h"


class ActionFrontEnd : public GameAction
{
public:
  ActionFrontEnd();
  virtual ~ActionFrontEnd();

  virtual void Start();
  virtual void Update();
  virtual void End();

private:

};


#endif // __ACTION_FRONT_END_H_

// -- EOF

