// ----------------------------------------------------------------------------
// File: RenderList.h
// Desc: A list of meshes to be rendered
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "RenderList.h"
#include "Material.h"
#include "Texture.h"


// ----------------------------------------------------------------------------
// Name: RenderList::RenderList
// Desc: Constructor
// ----------------------------------------------------------------------------
RenderList::RenderList()
{
  REF_COUNT_CTOR(RenderList);

  m_TotalCount = 0;
} // RenderList

                       
// ----------------------------------------------------------------------------
// Name: RenderList::~RenderList
// Desc: Destructor
// ----------------------------------------------------------------------------
RenderList::~RenderList()
{
  REF_COUNT_DTOR(RenderList);
} // ~RenderList


// ----------------------------------------------------------------------------
// Name: RenderList::Render
// Desc: Render the list
// ----------------------------------------------------------------------------
uint RenderList::Render(const LightArray &lights)
{
  return RenderInternal(lights, NULL);
} // Render


// ----------------------------------------------------------------------------
// Name: RenderList::RenderWithShadows
// Desc: Render the list
// ----------------------------------------------------------------------------
uint RenderList::RenderWithShadows(const LightArray &lights, ShadowCaster *pShadowCaster)
{
  return RenderInternal(lights, pShadowCaster);
} // RenderWithShadows


// ----------------------------------------------------------------------------
// Name: RenderList::Add
// Desc: Add an item to the render list
// Parm: const Mesh *pMesh     - the mesh
// Parm: const Matrix &matrix  - the matrix for the mesh
// ----------------------------------------------------------------------------
void RenderList::Add(const Mesh *pMesh, const Matrix &matrix)
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
} // Add


// ----------------------------------------------------------------------------
// Name: RenderList::RenderInternal
// Desc: Render the list
// ----------------------------------------------------------------------------
uint RenderList::RenderInternal(const LightArray &lights, ShadowCaster *pShadowCaster)
{
  uint renderCallCount = 0;

  RenderList::RenderItemMap::iterator iter(m_RenderItems.begin()), end(m_RenderItems.end());
  for (; iter != end; ++iter)
  {
    // Get the render item
    RenderList::RenderItem &renderItem = iter->second;

    // Begin the render call
    const Material *pMaterial = renderItem.pMaterial;
    uint numPasses = pMaterial->Begin();

    // Iterate for each render call for this render item
    RenderList::RenderCallMap::iterator renderCallIter(renderItem.renderCalls.begin()), renderCallEnd(renderItem.renderCalls.end());
    for (; renderCallIter != renderCallEnd; ++renderCallIter)
    {
      // Get the render call and the material
      RenderList::RenderCall &renderCall = renderCallIter->second;
      for (uint passId = 0; passId < numPasses; passId++)
      {
        // Begin the pass
        pMaterial->BeginPass(passId);

        // Iterate all instances of the subset
        Array<Matrix>::iterator matrixIter(renderCall.matrixArray.begin()), matrixEnd(renderCall.matrixArray.end());
        for (; matrixIter != matrixEnd; ++matrixIter)
        {
          // Prepare the instance
          pMaterial->Prepare(*matrixIter, renderCall.pSubset->GetColorMaterial(), renderCall.pSubset->GetTextureArray(), lights, pShadowCaster);

          // Render the instance
          renderCall.pMesh->RenderSubset(renderCall.subsetId, passId);
          renderCallCount++;
        } // for (render instance)

        // End the pass
        pMaterial->EndPass();
      } // for (render pass)
    } // for (render subset)

    // End the material
    pMaterial->End();
  } // for (render material)

  // Clear the render list
  m_RenderItems.clear();
  m_Bounds.Reset();
  m_TotalCount = 0;

  // Return the render call count
  return renderCallCount;
} // Render


// ----------------------------------------------------------------------------
// Name: RenderList::RenderInternal
// Desc: Render the list to the shadow caster
// ----------------------------------------------------------------------------
uint RenderList::RenderToShadowCaster(const LightArray &lights, ShadowCaster *pShadowCaster, const Material *pMaterial)
{
  D3DMATERIAL nullMaterial;
  TextureArray textureArray;

  uint renderCallCount = 0;

  // Begin the render call
  uint numPasses = pMaterial->Begin();
  for (uint passId = 0; passId < numPasses; passId++)
  {
    // Begin the pass
    pMaterial->BeginPass(passId);

    RenderList::RenderItemMap::iterator iter(m_RenderItems.begin()), end(m_RenderItems.end());
    for (; iter != end; ++iter)
    {
      // Get the render item
      RenderList::RenderItem &renderItem = iter->second;

      // Iterate for each render call for this render item
      RenderList::RenderCallMap::iterator renderCallIter(renderItem.renderCalls.begin()), renderCallEnd(renderItem.renderCalls.end());
      for (; renderCallIter != renderCallEnd; ++renderCallIter)
      {
        // Get the render call and the material
        RenderList::RenderCall &renderCall = renderCallIter->second;

        // Iterate all instances of the subset
        Array<Matrix>::iterator matrixIter(renderCall.matrixArray.begin()), matrixEnd(renderCall.matrixArray.end());
        for (; matrixIter != matrixEnd; ++matrixIter)
        {
          // Prepare the instance
          pMaterial->Prepare(*matrixIter, nullMaterial, textureArray, lights, pShadowCaster);

          // Render the instance
          renderCall.pMesh->RenderSubset(renderCall.subsetId, passId);
          renderCallCount++;
        } // for (render instance)
      } // for (render subset)
    } // for (render item)

    // End the pass
    pMaterial->EndPass();
  } // for (render pass)

  // End the material
  pMaterial->End();

  // Clear the render list
  m_RenderItems.clear();
  m_Bounds.Reset();
  m_TotalCount = 0;

  // Return the render call count
  return renderCallCount;
}


// -- EOF


