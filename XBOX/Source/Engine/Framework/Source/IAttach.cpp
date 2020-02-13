
#include "IAttach.h"
#include "IRender.h"


IMPLEMENT_TYPE_INFO(IAttach);


IAttach::IAttach()
: m_pSpace (NULL)
{
}


IAttach::~IAttach()
{
}


// Set the space that the object that owns this iterface is in
void IAttach::SetSpace(Space *pSpace)
{
  m_pSpace = pSpace;
}


// Update the space when the object that owns this interface moves
void IAttach::OnTransformChanged()
{
  if (m_pSpace)
  {
    m_pSpace->UpdateTransform(this);
  }
}


// The space has requested that we update
void IAttach::OnUpdate(float deltaTime)
{
  GetObject()->Update(deltaTime);
}


// The space has requested that we render
void IAttach::AddToRenderList(RenderList &renderList)
{
  IRender *pRenderInterface = GetObject()->GetInterface<IRender>();
  if (pRenderInterface && pRenderInterface->IsEnabled())
  {
    const Sphere &boundingSphere = pRenderInterface->GetBoundingSphere();
    if (Camera.GetFrustum().Intersects(boundingSphere) != Frustum::OUT_FRUSTUM)
    {
      pRenderInterface->AddToRenderList(renderList);
    }
  }
}


// -- EOF

