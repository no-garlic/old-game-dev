
#ifndef __ACTION_FINISH_LEVEL_H_
#define __ACTION_FINISH_LEVEL_H_


#include "libEngine.h"
#include "GameAction.h"


class ActionFinishLevel : public GameAction
{
public:
  ActionFinishLevel();
  virtual ~ActionFinishLevel();

  virtual void Start();
  virtual void Update();
  virtual void End();

private:

};


#endif // __ACTION_FINISH_LEVEL_H_

// -- EOF

