
#include "EditorAction_Undo.h"
#include "Editor.h"


EditorAction_Undo::EditorAction_Undo()
: EditorAction  ()
{
}


EditorAction_Undo::~EditorAction_Undo()
{
}


bool EditorAction_Undo::Init(const String &nodePath)
{
  return true;
}


void EditorAction_Undo::SetParameter(const String &paramName, const String &paramValue)
{
}


void EditorAction_Undo::SetParameter(const String &paramName, const Vec3   &paramValue)
{
}


void EditorAction_Undo::SetParameter(const String &paramName, int    paramValue)
{
}


void EditorAction_Undo::SetParameter(const String &paramName, uint   paramValue)
{
}


void EditorAction_Undo::SetParameter(const String &paramName, float  paramValue)
{
}


void EditorAction_Undo::SetParameter(const String &paramName, bool   paramValue)
{
}


bool EditorAction_Undo::Complete()
{
  Editor.GetUndoManager()->Undo();
  return true;
}


void EditorAction_Undo::Discard()
{
}


void EditorAction_Undo::Update()
{
}


// -- EOF

