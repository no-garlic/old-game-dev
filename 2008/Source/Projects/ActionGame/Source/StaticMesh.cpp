
#include "StaticMesh.h"


IMPLEMENT_TYPE_INFO(StaticMesh);


StaticMesh::StaticMesh()
{
  m_pMesh = NULL;
}


StaticMesh::~StaticMesh()
{
  SafeUnRef(m_pMesh);
}


void StaticMesh::SetMesh(IndexedMesh *pMesh)
{
  SafeUnRef(m_pMesh);
  m_pMesh = pMesh;
  SafeRef(m_pMesh);
}


IndexedMesh *StaticMesh::GetMesh()
{
  return m_pMesh;
}


// -- EOF

