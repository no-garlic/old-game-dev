
#ifndef __UNDO_ACTION_FLAG_H_
#define __UNDO_ACTION_FLAG_H_


#include "libEngine.h"
#include "libEditor.h"
#include "UndoManager.h"


class UndoAction_Flag : public UndoAction
{
public:
  UndoAction_Flag();
  virtual ~UndoAction_Flag();

  void AddFlag(const String &nodePath, bool add, uint flag);

  virtual void Undo();
  virtual void Redo();

private:
  struct FlagData
  {
    String  m_Path;
    bool    m_Add;
    uint    m_Flag;
  };

  Array<FlagData> m_Flags;

};


#endif // __UNDO_ACTION_FLAG_H_

// -- EOF


