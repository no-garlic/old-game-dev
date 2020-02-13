
#ifndef __EDITOR_ACTION_CLIPBOARD_PASTE_H_
#define __EDITOR_ACTION_CLIPBOARD_PASTE_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorAction.h"


class EditorAction_Clipboard_Paste : public EditorAction
{
public:
  EditorAction_Clipboard_Paste();
  virtual ~EditorAction_Clipboard_Paste();

  virtual bool Init(const String &nodePath);

  virtual bool Complete();
  virtual void Discard();

  virtual void Update();

};


#endif // __EDITOR_ACTION_CLIPBOARD_PASTE_H_

// -- EOF

