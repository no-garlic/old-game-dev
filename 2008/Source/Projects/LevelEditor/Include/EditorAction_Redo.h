
#ifndef __EDITOR_ACTION_REDO_H_
#define __EDITOR_ACTION_REDO_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorAction.h"


class EditorAction_Redo : public EditorAction
{
public:
  EditorAction_Redo();
  virtual ~EditorAction_Redo();

  virtual bool Init(const String &nodePath);

  virtual void SetParameter(const String &paramName, const String &paramValue);
  virtual void SetParameter(const String &paramName, const Vec3   &paramValue);
  virtual void SetParameter(const String &paramName, int    paramValue);
  virtual void SetParameter(const String &paramName, uint   paramValue);
  virtual void SetParameter(const String &paramName, float  paramValue);
  virtual void SetParameter(const String &paramName, bool   paramValue);

  virtual bool Complete();
  virtual void Discard();

  virtual void Update();

};


#endif // __EDITOR_ACTION_REDO_H_

// -- EOF

