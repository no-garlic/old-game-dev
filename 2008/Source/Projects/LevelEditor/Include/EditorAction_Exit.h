
#ifndef __EDITOR_ACTION_EXIT_H_
#define __EDITOR_ACTION_EXIT_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorAction.h"


class EditorAction_Exit : public EditorAction
{
public:
  EditorAction_Exit();
  virtual ~EditorAction_Exit();

  virtual bool Init(const String &nodePath);

  virtual bool Complete();
  virtual void Discard();

  virtual void Update();

};


#endif // __EDITOR_ACTION_EXIT_H_

// -- EOF

