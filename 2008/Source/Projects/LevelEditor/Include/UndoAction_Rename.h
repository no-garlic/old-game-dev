
#ifndef __UNDO_ACTION_RENAME_H_
#define __UNDO_ACTION_RENAME_H_


#include "libEngine.h"
#include "libEditor.h"
#include "UndoManager.h"


class UndoAction_Rename : public UndoAction
{
public:
  UndoAction_Rename();
  virtual ~UndoAction_Rename();

  void SetPath(const String &path);
  void SetOldName(const String &name);
  void SetNewName(const String &name);

  virtual void Undo();
  virtual void Redo();

private:
  String  m_Path;
  String  m_OldName;
  String  m_NewName;

};


#endif // __UNDO_ACTION_RENAME_H_

// -- EOf

