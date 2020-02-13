// ----------------------------------------------------------------------------
// File: Terrain.h
// Desc: Terrain renderer
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _TERRAIN_H_
#define _TERRAIN_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include "Math/Types.h"
#include "SceneGraph/Geode.h"
#include "Scenegraph/IntersectionTraverser.h"
#include "Scenegraph/CullTraverser.h"


// ----------------------------------------------------------------------------
// Typedef for singleton
// ----------------------------------------------------------------------------
class Terrain;
typedef Singleton::SingletonHolder<Terrain, Singleton::CreateUsingNew<Terrain> > TerrainSingleton;


// ----------------------------------------------------------------------------
// Name: Terrain  (class)
// Desc: Renders terrain
// ----------------------------------------------------------------------------
class Terrain : private Utility::Unique
{
private:
    // ------------------------------------------------------------------------
    // Allow the singleton holder to create this class
    // ------------------------------------------------------------------------
    friend struct Singleton::CreateUsingNew<Terrain>;


    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
             Terrain();
    virtual ~Terrain();


public:
    // ------------------------------------------------------------------------
    // Memory routines
    // ------------------------------------------------------------------------
    bool    Create(const char *filename, LPDIRECT3DDEVICE9 device);
    void    Release();


    // ------------------------------------------------------------------------
    // Render the terrain
    // ------------------------------------------------------------------------
    void    Render();


    // ------------------------------------------------------------------------
    // Get the terrain height and normal at an x, y position
    // ------------------------------------------------------------------------
    bool    GetTerrainHeight(float x, float y, float &z, Vec3 &n);


private:
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    LPDIRECT3DDEVICE9           m_device;       // The d3d device
    Geode                      *m_pterrain;     // The root node
    Geode                      *m_ptrees;       // The root node
    Geode                      *m_pprops;       // The root node
    IntersectionTraverser       m_isect_trav;   // Intersection traverser
    CullTraverser               m_cull_trav;    // Cull traverser


}; // class Terrain


#endif // _TERRAIN_H_

// -- EOF

