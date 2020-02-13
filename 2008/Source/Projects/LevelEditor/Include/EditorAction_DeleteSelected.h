
#ifndef __EDITOR_ACTION_DELETE_SELECTED_H_
#define __EDITOR_ACTION_DELETE_SELECTED_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorAction.h"


class EditorAction_DeleteSelected : public EditorAction
{
public:
  EditorAction_DeleteSelected();
  virtual ~EditorAction_DeleteSelected();

  virtual bool Init(const String &nodePath);

  virtual bool Complete();
  virtual void Discard();

  virtual void Update();

};


#endif // __EDITOR_ACTION_DELETE_SELECTED_H_

// -- EOF

