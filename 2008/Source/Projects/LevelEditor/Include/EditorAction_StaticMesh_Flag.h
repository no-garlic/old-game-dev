
#ifndef __EDITOR_ACTION_STATIC_MESH_FLAG_H_
#define __EDITOR_ACTION_STATIC_MESH_FLAG_H_


#include "libEngine.h"
#include "libEditor.h"
#include "EditorAction.h"


class EditorAction_StaticMesh_Flag : public EditorAction
{
public:
  EditorAction_StaticMesh_Flag();
  virtual ~EditorAction_StaticMesh_Flag();

  virtual bool Init(const String &nodePath);

  virtual void SetParameter(const String &paramName, bool paramValue);
  virtual void SetParameter(const String &paramName, uint paramValue);

  virtual bool Complete();
  virtual void Discard();

  virtual void Update();

private:
  String  m_Node;
  uint    m_Flag;
  uint    m_Value;
  bool    m_Add;    // Add or remove the flag

};


#endif // __EDITOR_ACTION_STATIC_MESH_FLAG_H_

// -- EOF

