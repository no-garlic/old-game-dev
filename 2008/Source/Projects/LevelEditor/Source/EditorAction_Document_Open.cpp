
#include "EditorAction_Document_Open.h"
#include "Editor.h"


EditorAction_Document_Open::EditorAction_Document_Open()
: EditorAction  ()
{
}


EditorAction_Document_Open::~EditorAction_Document_Open()
{
}


bool EditorAction_Document_Open::Init(const String &nodePath)
{
  return true;
}


bool EditorAction_Document_Open::Complete()
{
  return Editor.GetDocument()->Open();
}


void EditorAction_Document_Open::Discard()
{
}


void EditorAction_Document_Open::Update()
{
}


// -- EOF

