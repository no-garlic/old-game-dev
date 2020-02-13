
#include "UndoManager.h"


UndoManager::UndoManager()
{
  m_Active = false;
}


UndoManager::~UndoManager()
{
  Flush();
}


void UndoManager::Undo()
{
  if (m_UndoStack.empty())
    return;

  UndoAction *pAction = m_UndoStack.top();
  m_UndoStack.pop();

  bool active = m_Active;
  m_Active = false;

  pAction->Undo();

  m_Active = active;

  m_RedoStack.push(pAction);
}


void UndoManager::Redo()
{
  if (m_RedoStack.empty())
    return;

  UndoAction *pAction = m_RedoStack.top();
  m_RedoStack.pop();

  bool active = m_Active;
  m_Active = false;

  pAction->Redo();

  m_Active = active;

  m_UndoStack.push(pAction);
}


void UndoManager::Add(UndoAction *pAction)
{
  LOG_INFO << "###################### Adding Undo Action" << ENDLOG;
  m_UndoStack.push(pAction);

  while (!m_RedoStack.empty())
  {
    delete m_RedoStack.top();
    m_RedoStack.pop();
  }
}


void UndoManager::Flush()
{
  while (!m_UndoStack.empty())
  {
    delete m_UndoStack.top();
    m_UndoStack.pop();
  }

  while (!m_RedoStack.empty())
  {
    delete m_RedoStack.top();
    m_RedoStack.pop();
  }
}




// -- EOF

