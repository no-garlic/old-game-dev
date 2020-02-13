
#ifndef __ACTION_LOAD_LEVEL_H_
#define __ACTION_LOAD_LEVEL_H_


#include "libEngine.h"
#include "GameAction.h"
#include "GameLevel.h"


class ActionLoadLevel : public GameAction
{
public:
  ActionLoadLevel();
  virtual ~ActionLoadLevel();

  void SetLevelToLoad(const String &levelName);

  virtual void Start();
  virtual void Update();
  virtual void End();

private:
  String      m_LevelName;
  GameLevel  *m_pLoadingLevel;

};



#endif // __ACTION_LOAD_LEVEL_H_

// -- EOF

