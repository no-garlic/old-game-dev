
#ifndef __EDITOR_INPUT_KEYBOARD_H_
#define __EDITOR_INPUT_KEYBOARD_H_


#include "libEngine.h"
#include "libEditor.h"


class EditorInput_Keyboard : private Unique
{
public:
  EditorInput_Keyboard();
  virtual ~EditorInput_Keyboard();

  void Update();

};


#endif // __EDITOR_INPUT_KEYBOARD_H_

// -- EOF

