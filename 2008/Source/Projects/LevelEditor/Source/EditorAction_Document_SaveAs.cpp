
#include "EditorAction_Document_SaveAs.h"
#include "Editor.h"


EditorAction_Document_SaveAs::EditorAction_Document_SaveAs()
: EditorAction  ()
{
}


EditorAction_Document_SaveAs::~EditorAction_Document_SaveAs()
{
}


bool EditorAction_Document_SaveAs::Init(const String &nodePath)
{
  return true;
}


bool EditorAction_Document_SaveAs::Complete()
{
  return Editor.GetDocument()->SaveAs();
}


void EditorAction_Document_SaveAs::Discard()
{
}


void EditorAction_Document_SaveAs::Update()
{
}


// -- EOF

