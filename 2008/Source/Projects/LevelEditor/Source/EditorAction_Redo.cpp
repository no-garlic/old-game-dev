
#include "EditorAction_Redo.h"
#include "Editor.h"


EditorAction_Redo::EditorAction_Redo()
: EditorAction  ()
{
}


EditorAction_Redo::~EditorAction_Redo()
{
}


bool EditorAction_Redo::Init(const String &nodePath)
{

  return true;
}


void EditorAction_Redo::SetParameter(const String &paramName, const String &paramValue)
{
}


void EditorAction_Redo::SetParameter(const String &paramName, const Vec3   &paramValue)
{
}


void EditorAction_Redo::SetParameter(const String &paramName, int    paramValue)
{
}


void EditorAction_Redo::SetParameter(const String &paramName, uint   paramValue)
{
}


void EditorAction_Redo::SetParameter(const String &paramName, float  paramValue)
{
}


void EditorAction_Redo::SetParameter(const String &paramName, bool   paramValue)
{
}


bool EditorAction_Redo::Complete()
{
  Editor.GetUndoManager()->Redo();
  return true;
}


void EditorAction_Redo::Discard()
{
}


void EditorAction_Redo::Update()
{
}


// -- EOF

