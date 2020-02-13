

#ifndef __I_RENDER_H_
#define __I_RENDER_H_

#include "libStandard.h"
#include "libMaths.h"
#include "GameObjectInterface.h"
#include "GameObjectInterfaceId.h"


class IRender : public GameObjectInterface
{
public:
  DECLARE_TYPE_INFO(GameObjectInterface);

  enum { ID = GOI_RENDER };

  IRender();
  virtual ~IRender();

  virtual void Update(float deltaTime) = 0;
  virtual void AddToRenderList(RenderList &renderList) = 0;

  virtual const Sphere &GetBoundingSphere() const = 0;
  virtual void SetBoundsDirty() = 0;

  void SetEnabled(bool isEnabled) { m_IsEnabled = isEnabled; }
  bool IsEnabled() const { return m_IsEnabled; }
  
private:
  bool m_IsEnabled;
};


#endif // __I_RENDER_H_

// -- EOF

