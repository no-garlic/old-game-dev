
#ifndef __EDITOR_ACTION_H_
#define __EDITOR_ACTION_H_


#include "libEngine.h"
#include "libEditor.h"


class EditorAction : private Unique
{
public:
  EditorAction();
  virtual ~EditorAction();

  virtual bool Init(const String &nodePath) = 0;

  virtual void SetParameter(const String &paramName, const String &paramValue)  { DEBUG_BREAK; }
  virtual void SetParameter(const String &paramName, const Vec3   &paramValue)  { DEBUG_BREAK; }
  virtual void SetParameter(const String &paramName, int    paramValue)         { DEBUG_BREAK; }
  virtual void SetParameter(const String &paramName, uint   paramValue)         { DEBUG_BREAK; }
  virtual void SetParameter(const String &paramName, float  paramValue)         { DEBUG_BREAK; }
  virtual void SetParameter(const String &paramName, bool   paramValue)         { DEBUG_BREAK; }

  virtual bool Complete() = 0;
  virtual void Discard()  { DEBUG_BREAK; }

  virtual void Update()   {}

};


#endif // __EDITOR_ACTION_H_

// -- EOF

