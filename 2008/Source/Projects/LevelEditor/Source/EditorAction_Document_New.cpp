
#include "EditorAction_Document_New.h"
#include "Editor.h"


EditorAction_Document_New::EditorAction_Document_New()
: EditorAction  ()
{
}


EditorAction_Document_New::~EditorAction_Document_New()
{
}


bool EditorAction_Document_New::Init(const String &nodePath)
{
  return true;
}


bool EditorAction_Document_New::Complete()
{
  return Editor.GetDocument()->New();
}


void EditorAction_Document_New::Discard()
{
}


void EditorAction_Document_New::Update()
{
}


// -- EOF

