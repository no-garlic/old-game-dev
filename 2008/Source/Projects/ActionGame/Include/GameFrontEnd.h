
#ifndef __GAME_FRONT_END_H_
#define __GAME_FRONT_END_H_


#include "libEngine.h"


class GameFrontEnd : private Unique
{
public:
  GameFrontEnd();
  virtual ~GameFrontEnd();

  void Update();
  void Render();


private:
  bool LoadLevel(const String &levelName);


private:



};


#endif // __GAME_FRONT_END_H_

// -- EOF

