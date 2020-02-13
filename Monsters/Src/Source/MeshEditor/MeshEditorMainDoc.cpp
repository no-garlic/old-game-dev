// ----------------------------------------------------------------------------
// File: MeshEditorMainDoc.cpp
// Desc: The main document
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "MeshEditor/MeshEditorModule.h"
#include "MeshEditor/MeshEditorMainDoc.h"
#include "MeshEditor/Resource.h"


IMPLEMENT_DYNCREATE(MeshEditorMainDoc, CDocument)


BEGIN_MESSAGE_MAP(MeshEditorMainDoc, CDocument)
END_MESSAGE_MAP()


MeshEditorMainDoc::MeshEditorMainDoc()
{
} // MeshEditorMainDoc


MeshEditorMainDoc::~MeshEditorMainDoc()
{
} // ~MeshEditorMainDoc


BOOL MeshEditorMainDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
} // OnNewDocument


void MeshEditorMainDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	} // if
	else
	{
		// TODO: add loading code here
	} // else
} // Serialize






// -- EOF

