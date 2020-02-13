
#include "EditorAction_Exit.h"
#include "Editor.h"


EditorAction_Exit::EditorAction_Exit()
: EditorAction  ()
{
}


EditorAction_Exit::~EditorAction_Exit()
{
}


bool EditorAction_Exit::Init(const String &nodePath)
{
  WxDisplay::GetModule()->RequestExit(0);
  return true;
}


bool EditorAction_Exit::Complete()
{
  return true;
}


void EditorAction_Exit::Discard()
{
}


void EditorAction_Exit::Update()
{
}


// -- EOF

