
#include "EditorAction_Document_Close.h"
#include "Editor.h"


EditorAction_Document_Close::EditorAction_Document_Close()
: EditorAction  ()
{
}


EditorAction_Document_Close::~EditorAction_Document_Close()
{
}


bool EditorAction_Document_Close::Init(const String &nodePath)
{
  return true;
}


bool EditorAction_Document_Close::Complete()
{
  return Editor.GetDocument()->Close();
}


void EditorAction_Document_Close::Discard()
{
}


void EditorAction_Document_Close::Update()
{
}


// -- EOF

