
#ifndef __GAME_OBJECT_INTERFACE_ID_
#define __GAME_OBJECT_INTERFACE_ID_


enum GameObjectInterfaceId
{
  GOI_LOGIC,      // Game Logic or AI
  GOI_CAMERA,     // Camera
  GOI_MOVE,       // Movement
  GOI_PHYSICS,    // Physics
  GOI_ANIMATION,  // Animation
  GOI_RENDER,     // Rendering
  GOI_SOUND,      // Sound
  GOI_PAD,        // Gamepad / Input
  GOI_HUD,        // UI / HUD
  GOI_ATTACH,     // Attach to a Space

  GOI_MAX
};



#endif // __GAME_OBJECT_INTERFACE_ID_

// -- EOF


