
#include "OverrideRenderList.h"


OverrideRenderList::OverrideRenderList()
{
  m_pGlobalOverride = NULL;
}


OverrideRenderList::~OverrideRenderList()
{
}


// --------------------------------------------------------------------------
// Set the override material for all vertex types
// --------------------------------------------------------------------------
void OverrideRenderList::SetGlobalOverrideMaterial(const Material *pOverideMaterial)
{
  m_pGlobalOverride = pOverideMaterial;
}


// --------------------------------------------------------------------------
// Set the override material for a vertex type
// --------------------------------------------------------------------------
void OverrideRenderList::SetOverrideMaterialForVertexType(const Material *pOverideMaterial, const VertexType *pVertexType)
{
  m_OverrideMaterials[pVertexType] = pOverideMaterial;
}


// --------------------------------------------------------------------------
// Add a mesh to the render list
// --------------------------------------------------------------------------
void OverrideRenderList::Add(const Mesh *pMesh, const Matrix &matrix)
{
  Sphere s = pMesh->GetBSphere();
  s.TransformAndScale(matrix);

  if (m_RenderItems.empty())
    m_Bounds = s;
  else
    m_Bounds.Maximize(s);

  uint numSubsets = pMesh->GetNumSubsets();
  for (uint i = 0; i < numSubsets; i++)
  {
    // Get the subset and the material
    const MeshSubset *pSubset = pMesh->GetSubset(i);
    const Material *pMaterial = pSubset->GetMaterial();

    // See if there is a global override
    if (m_pGlobalOverride)
    {
      pMaterial = m_pGlobalOverride;
    }

    // See if there is a vertex type override
    OverrideMaterialMap::iterator materialIter = m_OverrideMaterials.find(pMesh->GetVertexType());
    if (materialIter != m_OverrideMaterials.end())
    {
      pMaterial = materialIter->second;
    }

    // Get the address of the subset and the material
    uint subsetAddr   = reinterpret_cast<uint>(pSubset);
    uint materialAddr = reinterpret_cast<uint>(pMaterial);

    // Search for the material
    RenderList::RenderItemMap::iterator iter(m_RenderItems.find(materialAddr));
    if (iter == m_RenderItems.end())
    {
      // This material is not in the list so create a new render item
      RenderList::RenderItem &renderItem = m_RenderItems[materialAddr];
      renderItem.materialAddr = materialAddr;
      renderItem.pMaterial    = pMaterial;

      // Create a render call for this render item
      RenderList::RenderCall &renderCall = renderItem.renderCalls[subsetAddr];

      // Assign the render call info
      renderCall.pMaterial    = pMaterial;
      renderCall.pMesh        = pMesh;
      renderCall.pSubset      = pSubset;
      renderCall.subsetAddr   = subsetAddr;
      renderCall.subsetId     = i;
      renderCall.matrixArray.push_back(matrix);
    } // if
    else
    {
      // This material is already in the list so get the render item
      RenderList::RenderItem &renderItem = iter->second;

      // See if there is already a render call for the subset
      RenderList::RenderCallMap::iterator renderCallIter(renderItem.renderCalls.find(subsetAddr));
      if (renderCallIter == renderItem.renderCalls.end())
      {
        // This subset is not in the list so create a new render call
        RenderList::RenderCall &renderCall = renderItem.renderCalls[subsetAddr];

        // Assign the render call info
        renderCall.pMaterial    = pMaterial;
        renderCall.pMesh        = pMesh;
        renderCall.pSubset      = pSubset;
        renderCall.subsetAddr   = subsetAddr;
        renderCall.subsetId     = i;
        renderCall.matrixArray.push_back(matrix);
      } // if
      else
      {
        // This subset is in the list so get the render call
        RenderList::RenderCall &renderCall = renderItem.renderCalls[subsetAddr];
        renderCall.matrixArray.push_back(matrix);
      } // else
    } // else
  } // for

  m_TotalCount++;
}


// -- EOF

