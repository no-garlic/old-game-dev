
#include "EditorAction_Document_Save.h"
#include "Editor.h"


EditorAction_Document_Save::EditorAction_Document_Save()
: EditorAction  ()
{
}


EditorAction_Document_Save::~EditorAction_Document_Save()
{
}


bool EditorAction_Document_Save::Init(const String &nodePath)
{
  return true;
}


bool EditorAction_Document_Save::Complete()
{
  return Editor.GetDocument()->Save();
}


void EditorAction_Document_Save::Discard()
{
}


void EditorAction_Document_Save::Update()
{
}


// -- EOF

