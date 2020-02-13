
#ifndef __ACTION_STARTUP_H_
#define __ACTION_STARTUP_H_


#include "libEngine.h"
#include "GameAction.h"


class ActionStartup : public GameAction
{
public:
  ActionStartup();
  virtual ~ActionStartup();

  virtual void Start();
  virtual void Update();
  virtual void End();

private:

};


#endif // __ACTION_STARTUP_H_

// -- EOF

