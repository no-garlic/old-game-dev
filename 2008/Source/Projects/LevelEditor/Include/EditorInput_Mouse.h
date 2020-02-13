
#ifndef __EDITOR_INPUT_MOUSE_H_
#define __EDITOR_INPUT_MOUSE_H_


#include "libEngine.h"
#include "libEditor.h"


class EditorInput_Mouse : private Unique
{
public:
  EditorInput_Mouse();
  virtual ~EditorInput_Mouse();

  void Update();

private:
  POINT m_CursorPos;

};


#endif // __EDITOR_INPUT_MOUSE_H_

// -- EOF

