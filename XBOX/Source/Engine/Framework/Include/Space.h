
#ifndef __SPACE_H_
#define __SPACE_H_


#include "libRenderExt.h"


class IAttach;


class Space
{
public:
  Space();
  virtual ~Space();

  // Add an object to the space
  virtual void Add(IAttach *pAttach);

  // Remove an object from the space
  virtual void Remove(IAttach *pAttach);

  // Update the game object within the space because it's transform has changed
  virtual void UpdateTransform(IAttach *pAttach);

  // Update game objects in the space
  virtual void Update(float deltaTime);

  // Render objects in the space
  virtual void Render(const LightArray &lights);

private:


};


#endif // __SPACE_H_

// -- EOF

