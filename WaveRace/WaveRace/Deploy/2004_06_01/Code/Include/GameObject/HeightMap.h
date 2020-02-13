// ----------------------------------------------------------------------------
// File: HeightMap.h
// Desc: HeightMap renderer
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _HEIGHT_MAP_H_
#define _HEIGHT_MAP_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include "Engine/Material.h"
#include "Engine/Mesh_IndexTriangleStrip.h"
#include "Math/Types.h"
#include "Math/Matrix.h"
#include "Math/Vec3.h"
#include "Math/Vec4.h"
#include "Math/FloatArray2D.h"


// ----------------------------------------------------------------------------
// Typedef for singleton
// ----------------------------------------------------------------------------
class HeightMap;
typedef Singleton::SingletonHolder<HeightMap, Singleton::CreateUsingNew<HeightMap> > HeightMapSingleton;


// ----------------------------------------------------------------------------
// Name: HeightMap  (class)
// Desc: Renders terrain
// ----------------------------------------------------------------------------
class HeightMap : private Utility::Unique
{
private:
    // ------------------------------------------------------------------------
    // Allow the singleton holder to create this class
    // ------------------------------------------------------------------------
    friend struct Singleton::CreateUsingNew<HeightMap>;


    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
             HeightMap();
    virtual ~HeightMap();


public:
    // ------------------------------------------------------------------------
    // Name: MapType (enum)
    // Desc: Types of height maps
    // ------------------------------------------------------------------------
    enum MapType
    {
        MAP_TEXTURE,
        MAP_RAW
    }; // enum MapType


    // ------------------------------------------------------------------------
    // Memory routines
    // ------------------------------------------------------------------------
    bool    Create(const char *filename, MapType type, uint grid_size, uint cell_size, 
                float grid_width, float grid_height, LPDIRECT3DDEVICE9 device);
    void    Release();


    // ------------------------------------------------------------------------
    // Render the terrain
    // ------------------------------------------------------------------------
    void    AddToRenderBin();


    // ------------------------------------------------------------------------
    // Get the terrain height and normal at an x, y position
    // ------------------------------------------------------------------------
    void    GetHeightMapHeight(float x, float y, float &z, Vec3 &n);


private:
    // ------------------------------------------------------------------------
    // Internal functions
    // ------------------------------------------------------------------------
    bool    CreateGrid();
    float   GetVertexHeight(float x, float y);


    // ------------------------------------------------------------------------
    // Name: Node (struct)
    // Desc: Grid node
    // ------------------------------------------------------------------------
    struct Node
    {
        // --------------------------------------------------------------------
        // Get the terrain height and normal at an x, y position
        // --------------------------------------------------------------------
        void GetHeightMapHeight(float x, float y, float &z, Vec3 &n);


        // --------------------------------------------------------------------
        // Public Members
        // --------------------------------------------------------------------
        Mesh_IndexTriangleStrip     *pmesh;     // The mesh
        float                       *verts;     // Vertex Z array for lookup
        Vec4                         rect;      // The extents
        float                        width;     // The cell width
        int                          size;      // Size of node (verts per side)


    }; // struct HeightMapData


    // ------------------------------------------------------------------------
    // Name: Grid (struct)
    // Desc: Holds a 2D array of nodes
    // ------------------------------------------------------------------------
    struct Grid
    {
        HeightMap::Node      *array;                  // The node array
        uint                width;                  // number of nodes per side (total = size^2)

              Node &Get(int x, int y)       { return array[(y * width) + x]; }
        const Node &Get(int x, int y) const { return array[(y * width) + x]; }
    }; // struct Grid


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    LPDIRECT3DDEVICE9           m_device;           // The d3d device

    
    // ------------------------------------------------------------------------
    // Height map data
    // ------------------------------------------------------------------------
    float                      *m_height_map;       // The height map array
    uint                        m_height_map_size;  // The sqrt size of the array (N^2)


    // ------------------------------------------------------------------------
    // Grid data
    // ------------------------------------------------------------------------
    HeightMap::Grid               m_grid;             // The grid
    uint                        m_grid_size;        // The sqrt number of cells in the grid (N^2)

    float                       m_grid_width;       // The width of the grid in meters
    float                       m_grid_height;      // The height of the grid in meters

    uint                        m_cell_size;        // The sqrt number of verticies in each cell (N^2)
    float                       m_cell_width;       // The width of a grid cell in meters

    uint                        m_material_id;      // The material id

}; // class HeightMap


#endif // _HEIGHT_MAP_H_

// -- EOF

