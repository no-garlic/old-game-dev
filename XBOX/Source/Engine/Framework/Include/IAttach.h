

#ifndef __I_ATTACH_H_
#define __I_ATTACH_H_

#include "libStandard.h"
#include "libMaths.h"
#include "GameObjectInterface.h"
#include "GameObjectInterfaceId.h"
#include "Space.h"


class IAttach : public GameObjectInterface
{
public:
  DECLARE_TYPE_INFO(GameObjectInterface);

  enum { ID = GOI_ATTACH };

  // Constructor and destructor
  IAttach();
  virtual ~IAttach();

  // Set the space that the object that owns this iterface is in
  virtual void SetSpace(Space *pSpace);

  // Update the space when the object that owns this interface moves
  virtual void OnTransformChanged();

  // The space has requested that we update
  virtual void OnUpdate(float deltaTime);

  // The space has requested that we render
  virtual void AddToRenderList(RenderList &renderList);

private:
  // The space that this attachment is in
  Space *m_pSpace;

};


#endif // __I_ATTACH_H_

// -- EOF

