
#ifndef __EDITOR_ACTION_DOCUMENT_NEW_H_
#define __EDITOR_ACTION_DOCUMENT_NEW_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorAction.h"


class EditorAction_Document_New : public EditorAction
{
public:
  EditorAction_Document_New();
  virtual ~EditorAction_Document_New();

  virtual bool Init(const String &nodePath);

  virtual bool Complete();
  virtual void Discard();

  virtual void Update();

};


#endif // __EDITOR_ACTION_DOCUMENT_NEW_H_

// -- EOF

