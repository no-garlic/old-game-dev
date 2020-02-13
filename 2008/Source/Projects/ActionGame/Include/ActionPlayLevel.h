
#ifndef __ACTION_PLAY_LEVEL_H_
#define __ACTION_PLAY_LEVEL_H_


#include "libEngine.h"
#include "GameAction.h"


class ActionPlayLevel : public GameAction
{
public:
  ActionPlayLevel();
  virtual ~ActionPlayLevel();

  virtual void Start();
  virtual void Update();
  virtual void End();

private:

};


#endif // __ACTION_PLAY_LEVEL_H_

// -- EOF

  