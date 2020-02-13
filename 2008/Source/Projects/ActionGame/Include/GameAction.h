
#ifndef __GAME_ACTION_H_
#define __GAME_ACTION_H_


#include "libEngine.h"


enum ActionState
{
  AS_NEW,
  AS_STARTING,
  AS_RUNNING,
  AS_ENDING,
  AS_ENDED,
  AS_ERROR
};


class GameAction : private Unique
{
public:
  GameAction();
  virtual ~GameAction();

  ActionState GetState() { return m_State; }

  virtual void Start()  = 0;
  virtual void Update() = 0;
  virtual void End()    = 0;

protected:
  ActionState   m_State;

};


#endif // __GAME_ACTION_H_

// -- EOF

