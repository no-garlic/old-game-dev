
#ifndef __EDITOR_ACTION_CLIPBOARD_CUT_H_
#define __EDITOR_ACTION_CLIPBOARD_CUT_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorAction.h"


class EditorAction_Clipboard_Cut : public EditorAction
{
public:
  EditorAction_Clipboard_Cut();
  virtual ~EditorAction_Clipboard_Cut();

  virtual bool Init(const String &nodePath);

  virtual bool Complete();
  virtual void Discard();

  virtual void Update();

};


#endif // __EDITOR_ACTION_CLIPBOARD_CUT_H_

// -- EOF

