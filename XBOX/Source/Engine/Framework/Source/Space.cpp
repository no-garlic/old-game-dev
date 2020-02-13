
#include "Space.h"
#include "IAttach.h"


Space::Space()
{
}


Space::~Space()
{
}


// Add an object to the space
void Space::Add(IAttach *pAttach)
{
}


// Remove an object from the space
void Space::Remove(IAttach *pAttach)
{
}


// Update the game object within the space because it's transform has changed
void Space::UpdateTransform(IAttach *pAttach)
{
}


// Update game objects in the space
void Space::Update(float deltaTime)
{
}

// Render objects in the space
void Space::Render(const LightArray &lights)
{
}


// -- EOF

