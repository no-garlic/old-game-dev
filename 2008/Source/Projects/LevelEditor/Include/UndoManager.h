
#ifndef __UNDO_MANAGER_H_
#define __UNDO_MANAGER_H_


#include "libEngine.h"
#include "libEditor.h"


class UndoAction : private Unique
{
public:
  UndoAction()          {}
  virtual ~UndoAction() {}

  virtual void Undo() = 0;
  virtual void Redo() = 0;

};


class UndoManager : private Unique
{
public:
  UndoManager();
  virtual ~UndoManager();

  bool IsActive() const { return m_Active; }
  void SetActive(bool active) { m_Active = active; }

  // Undo the last operation
  void Undo();
  void Redo();

  // Add an undo action to the manager
  void Add(UndoAction *pAction);

  // Can we undo or redo (used to enable toolbar buttons)
  bool CanUndo() const { return !(m_UndoStack.empty()); }
  bool CanRedo() const { return !(m_RedoStack.empty()); }

  // Flush the undo and redo stacks
  void Flush();

private:
  // Private members
  Stack<UndoAction *> m_UndoStack;
  Stack<UndoAction *> m_RedoStack;
  bool                m_Active;

};


#endif // __UNDO_MANAGER_H_

// -- EOF

