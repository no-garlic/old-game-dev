// ----------------------------------------------------------------------------
// File: GameModule.h
// Desc: The main module to run the game
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __GAME_MODULE_H_
#define __GAME_MODULE_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Engine/EngineInc.h"
#include "Render/RenderInc.h"


// ----------------------------------------------------------------------------
// Name: GameModule  (class)
// Desc: Test Module
// ----------------------------------------------------------------------------
class GameModule : public ApplicationModule_Win32
{
public:
  // --------------------------------------------------------------------------
  // Constructor and Destructor
  // --------------------------------------------------------------------------
  GameModule();
  virtual ~GameModule();

  // --------------------------------------------------------------------------
  // Process Functions
  // --------------------------------------------------------------------------
  virtual bool Init();
  virtual bool CreateSafeObjects();
  virtual bool CreateDeviceObjects();
  virtual bool ReleaseSafeObjects();
  virtual bool ReleaseDeviceObjects();
  virtual void Shutdown();
  virtual void App();
  virtual void Cull();
  virtual void Draw();
  virtual void Resize();

private:
  // --------------------------------------------------------------------------
  // Private methods
  // --------------------------------------------------------------------------
  void SetDisplayState();
  void CreateMeshInstance(Mesh *pMesh, float x, float y, float z);

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  MeshInstanceArray     m_MeshArray;    // The array of all mesh instances
  MeshInstanceArray     m_VisibleList;  // The visible list of meshes
  IndexedMesh          *m_pMesh;        // The mesh

}; // class GameModule


#endif // __GAME_MODULE_H_

// -- EOF



