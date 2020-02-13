// ----------------------------------------------------------------------------
// File: HeightMap.cpp
// Desc: HeightMap renderer
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "GameObject/HeightMap.h"
#include "Engine/RenderBin.h"
#include "Common/FilePath.h"
#include "Common/Logging.h"
#include "Math/Color.h"
#include <sstream>
#include <stdio.h>


HeightMap::HeightMap()
{
    m_device                = 0;
    m_height_map            = 0;
    m_height_map_size       = 0;
    m_grid_size             = 0;
    m_cell_size             = 0;
    m_grid_width            = 0.0f;
    m_grid_height           = 0.0f;
    m_cell_width            = 0.0f;
    m_material_id           = 0;
} // HeightMap


HeightMap::~HeightMap()
{
    Release();
} // ~HeightMap


bool HeightMap::Create(const char *filename, MapType type, uint grid_size, uint cell_size, float grid_width, float grid_height, LPDIRECT3DDEVICE9 device)
{
    // Check we have not already be initialised
    if (m_height_map || m_device)
        return false;

    m_device                = device;
    m_grid_size             = grid_size;
    m_cell_size             = cell_size;
    m_grid_width            = grid_width;
    m_grid_height           = grid_height;
    m_cell_width            = grid_width / grid_size;

    // Find the texure file in the search path
    std::string path_name = filename;
    FilePath::StripPath(path_name);
    std::string found = FilePathSingleton::Instance().FindFile(path_name);
    if (found.empty())
    {
        LOG_ERROR << "Failed to find the texture file: " << path_name << ENDLOG;
        return false;
    } // if
    path_name = found;

    if (type == MAP_TEXTURE)
    {
        // Load the texture
        IDirect3DTexture9 *ptexture;
        if (FAILED(D3DXCreateTextureFromFile(device, path_name.c_str(), &ptexture)))
        {
            // Failed to load the texture fipl from disk
            LOG_ERROR << "Failed to load the texture file: " << path_name << ENDLOG;
            return false;
        } // if

        // Read the texture image data
        D3DLOCKED_RECT tex_data;
        if (FAILED(ptexture->LockRect(0, &tex_data, 0, D3DLOCK_READONLY)))
        {
            // Failed to load the texture fipl from disk
            LOG_ERROR << "Failed to get the texture image data: " << path_name << ENDLOG;
            Memory::SafeRelease(ptexture);
            return false;
        } // if

        // Get the size of the texture
        m_height_map_size = (uint) tex_data.Pitch / 4;

        // Cast the texture data as an array of unsigned char
        uchar *data         = (uchar *) tex_data.pBits;

        // Create the height map and put it in the array
        m_height_map        = (float *) new float[m_height_map_size * m_height_map_size];
        FloatArray2D height_data(m_height_map, m_height_map_size);

        // Assign the height map data
        for (uint i = 0; i < m_height_map_size; i++)
        {
            for (uint j = 0; j < m_height_map_size; j++)
            {
                // Height data is 0..1
                height_data[i][j] = (((float) data[(((i * m_height_map_size) + j) * 4)]      + 
                                    (float) data[(((i * m_height_map_size) + j) * 4) + 1]  + 
                                    (float) data[(((i * m_height_map_size) + j) * 4) + 2]) /
                                    ((3.0f * 255.0f)));
            } // for
        } // for

        // Finished with the texture now
        ptexture->UnlockRect(0);
        Memory::SafeRelease(ptexture);
    } // if

    else // The file is a raw heightmap (257 x 257)
    {
        // Open up the heightmap file
        FILE *pfile = fopen(path_name.c_str(), "rb");
        if (!pfile) 
            return false;

        // Allocate some space to read the file
        m_height_map_size = 257;
        uchar *data  = new uchar[257 * 257];

        // Read the heightmap data (grayscale)
        fread(data, 257 * 257, 1, pfile);
        
        // Finish up
        fclose(pfile);        

        // Create the height map and put it in the array
        m_height_map        = (float *) new float[m_height_map_size * m_height_map_size];
        FloatArray2D height_data(m_height_map, m_height_map_size);

        // Assign the height map data
        for (uint i = 0; i < m_height_map_size; i++)
        {
            for (uint j = 0; j < m_height_map_size; j++)
            {
                // Height data is 0..1
                height_data[i][j] = (1.0f / 255.0f) * data[((i * m_height_map_size) + j)];
            } // for
        } // for

        delete[] data;
    } // else

    // Now create the grid
    return CreateGrid();
} // Initialise


void HeightMap::Release()
{
    if (m_device)
    {
        delete[] m_height_map;
        m_height_map = 0;

        for (uint i = 0; i < m_grid_size; i++)
        {
            for (uint j = 0; j < m_grid_size; j++)
            {
                HeightMap::Node &node = m_grid.Get(i, j);
                delete   node.pmesh;
                delete[] node.verts;
            } // for
        } // for

        delete[] m_grid.array;
        m_grid.array = 0;
    } // if

    m_device = 0;
} // Release


bool HeightMap::CreateGrid()
{
    m_grid.array = (HeightMap::Node *) new HeightMap::Node[m_grid_size * m_grid_size];
    m_grid.width = m_grid_size;

    float vertex_spacing    = m_cell_width / (m_cell_size - 1);
    float half_grid_width   = m_grid_width / 2.0f;

    for (uint i = 0; i < m_grid_size; i++)
    {
        for (uint j = 0; j < m_grid_size; j++)
        {
            HeightMap::Node &node = m_grid.Get(i, j);

            float start_x = (i * m_cell_width) - half_grid_width;
            float start_y = (j * m_cell_width) - half_grid_width;

            node.rect  = Vec4(start_x, start_x + m_cell_width, start_y, start_y + m_cell_width);
            node.width = m_cell_width;
            node.size  = m_cell_size;
            node.verts = new float[m_cell_size * m_cell_size];

            std::stringstream ss;
            ss << "terrain_" << i << "_" << j;

            Mesh_IndexTriangleStrip::VertexVec      verts;
            Mesh_IndexTriangleStrip::IndexVecVec    indicies;

            verts.resize(m_cell_size * m_cell_size);
            for (uint a = 0; a < m_cell_size; a++)
            {
                for (uint b = 0; b < m_cell_size; b++)
                {
                    Mesh_IndexTriangleStrip::Vertex &vertex = verts[(a * m_cell_size) + b];

                    float map_x     = (i * m_cell_width) + (a * vertex_spacing);
                    float map_y     = (j * m_cell_width) + (b * vertex_spacing);

                    vertex.loc[0]   = start_x + (vertex_spacing * a);
                    vertex.loc[1]   = start_y + (vertex_spacing * b);
                    vertex.loc[2]   = GetVertexHeight(map_x - half_grid_width, map_y - half_grid_width);

                    node.verts[(a * m_cell_size) + b] = vertex.loc[2];

                    vertex.norm     = Vec3(0.0f, 0.0f, -1.0f);

                    vertex.diff     = Color::Black;

                    vertex.u        = (vertex.loc[0] - half_grid_width) / m_grid_width;
                    vertex.v        = (vertex.loc[1] - half_grid_width) / m_grid_width;

                    vertex.u2       = 0.0f;
                    vertex.v2       = 0.0f;
                } // for
            } // for

            indicies.resize(m_cell_size - 1);
            for (uint a = 0; a < m_cell_size - 1; a++)
            {
                Mesh_IndexTriangleStrip::IndexVec &index_vec = indicies[a];
                index_vec.resize(m_cell_size * 2);

                for (uint b = 0; b < m_cell_size; b++)
                {
                    index_vec[(b * 2)]     = (a * m_cell_size) + b;
                    index_vec[(b * 2) + 1] = ((a + 1) * m_cell_size) + b;
                } // for
            } // for

            node.pmesh = new Mesh_IndexTriangleStrip
                (ss.str().c_str(), m_device, verts, indicies, false);
        } // for
    } // for

    uint tex0     = TextureCache::CreateTexture("colormap.bmp",  m_device);
    uint tex1     = TextureCache::CreateTexture("detailmap.jpg", m_device);
    //m_material_id = MaterialCache::CreateMaterial(tex0, tex1, 0, Color::Gray, Color::Yellow, Color::Black, Color::White, 128.0f);
    m_material_id = 0;

    return true;
} // CreateGrid


void HeightMap::AddToRenderBin()
{
    RenderBin &render_bin = RenderBinSingleton::Instance();
    for (uint i = 0; i < m_grid_size; i++)
    {
        for (uint j = 0; j < m_grid_size; j++)
        {
            HeightMap::Node &node = m_grid.Get(i, j);
            //render_bin.AddRenderTarget(node.pmesh, m_material_id, Matrix::GetIdentityRef());
            render_bin.AddRenderTarget(node.pmesh, 0, Matrix::GetIdentityRef());
        } // for
    } // for
} // Render


float HeightMap::GetVertexHeight(float x, float y)
{
    float half_grid_width = m_grid_width / 2.0f;

    if (x < -half_grid_width || x > half_grid_width || y < -half_grid_width || y > half_grid_width)
    {
        return 0;
    } // if
    else
    {
        // Linear interpolate x and y pos (0..1)
        float x_pos = (x + half_grid_width) / m_grid_width;
        float y_pos = (y + half_grid_width) / m_grid_width;

        // Truncate the floats to get the lower bound index
        // into the height map
        int idx_x   = (int) (x_pos * (m_height_map_size - 1));
        int idx_y   = (int) (y_pos * (m_height_map_size - 1));
        int index   = (idx_x * m_height_map_size) + idx_y;

        // Retrieve the value and flip it in the z axis
        return 0.0f - (m_height_map[index] * (m_grid_height));
    } // else
} // GetVertexHeight



void HeightMap::GetHeightMapHeight(float x, float y, float &z, Vec3 &n)
{
    // Clamp to a valid range
    float half_grid_width = m_grid_width / 2.0f;
    Utility::Clamp<float>(x, -half_grid_width, half_grid_width - 0.001f);
    Utility::Clamp<float>(y, -half_grid_width, half_grid_width - 0.001f);

    // Lerp (0..1)
    float lerp_x = (x + half_grid_width) / m_grid_width;
    float lerp_y = (y + half_grid_width) / m_grid_width;
    
    // Work out the grid node
    int node_x = static_cast<int>(lerp_x * m_grid_size);
    int node_y = static_cast<int>(lerp_y * m_grid_size);

    // Get the node
    Node &node = m_grid.Get(node_x, node_y);
    node.GetHeightMapHeight(x, y, z, n);
} // GetHeightMapHeight


void HeightMap::Node::GetHeightMapHeight(float x, float y, float &z, Vec3 &n)
{
    float start_x   = rect[0];
    float end_x     = rect[1];
    float start_y   = rect[2];
    float end_y     = rect[3];

    // Lerp (0..1)
    float lerp_x = (x - start_x) / width;
    float lerp_y = (y - start_y) / width;

    // Work out the quad
    int quad_x1 = static_cast<int>(lerp_x * (size-1));
    int quad_x2 = quad_x1 + 1;
    int quad_y1 = static_cast<int>(lerp_y * (size-1));
    int quad_y2 = quad_y1 + 1;

    float a = verts[(quad_x1 * size) + quad_y1];
    float b = verts[(quad_x1 * size) + quad_y2];
    float c = verts[(quad_x2 * size) + quad_y1];

    float ab = a + ((a - b) * lerp_x);
    float ac = a + ((a - c) * lerp_y);

    z = (ab + ac) / 2.0f;
    n = Vec3(0.0f, 0.0f, -1.0f);
} // GetHeightMapHeight
    

// -- EOF

