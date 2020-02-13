
#include "GameAction.h"


GameAction::GameAction()
: m_State(AS_NEW)
{
  REF_COUNT_CTOR(GameAction);
}


GameAction::~GameAction()
{
  REF_COUNT_DTOR(GameAction);
}




// -- EOF

