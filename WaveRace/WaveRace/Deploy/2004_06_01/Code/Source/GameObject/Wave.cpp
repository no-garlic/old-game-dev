// ----------------------------------------------------------------------------
// File: wave.cpp
// Desc: Simulates a wave using the Central Difference Algorithm as demonstrated
//       in Game Gems 1. Portions Copyright (C) Miguel Gomez, 2000.
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------

#include "GameObject/wave.h"
#include "Math/Vec3.h"
#include "Math/FloatArray2D.h"
#include "Engine/Camera.h"
#include "Engine/Material.h"
#include "Common/Logging.h"
#include "Common/FilePath.h"
#include "Engine/Effect.h"


// ----------------------------------------------------------------------------
// Wave size - number of verticies in each axis, so the total number of 
// verticies is (WAVE_VERTEX_COUNT * WAVE_VERTEX_COUNT) and the total number of
//  cells is ((WAVE_VERTEX_COUNT - 1) * (WAVE_VERTEX_COUNT - 1))
// ----------------------------------------------------------------------------
#define WAVE_VERTEX_COUNT       97
#define FFT_DECAY               0.9999f
#define UPDATE_TIME             0.04f


// ----------------------------------------------------------------------------
// Name of the HSLS shader file
// ----------------------------------------------------------------------------
#define SHADER_FILE_NAME    "wave.fx"


// ----------------------------------------------------------------------------
// Name: CDAWaveData (struct)
// Desc: Struct to hold the wave data
// ----------------------------------------------------------------------------
struct CDAWave::CDAWaveData
{
    // ------------------------------------------------------------------------
    // Members of the wave data struct
    // ------------------------------------------------------------------------
    float           height_map[WAVE_VERTEX_COUNT][WAVE_VERTEX_COUNT];       // z[n] values
    float           height_map_ref[WAVE_VERTEX_COUNT][WAVE_VERTEX_COUNT];   // z[n-1] and z[n+1] values
    float           height_map_swell[WAVE_VERTEX_COUNT][WAVE_VERTEX_COUNT]; // wave swell
    float           height_map_comb[WAVE_VERTEX_COUNT][WAVE_VERTEX_COUNT];  // combined ripple and swell
    Vec3            vertex_array[WAVE_VERTEX_COUNT][WAVE_VERTEX_COUNT];     // triangle vertices
    Vec3            normal_array[WAVE_VERTEX_COUNT][WAVE_VERTEX_COUNT];     // vertex normals
    float           wave_space;                                             // wave space, meters/sec
    float           wave_height;                                            // wave height
    float           cell_size;                                              // grid cell width (min for stability, assuming dt<=0.1)
    float           grid_size;                                              // width of entire grid
    FloatArray2D    height_map_array;                                       // Array wrapper
    FloatArray2D    height_map_array_ref;                                   // Array wrapper

    
    // ------------------------------------------------------------------------
    // Constructor
    // ------------------------------------------------------------------------
    CDAWaveData()
    {
        wave_space  = 3.0f;
        wave_height = 0.45f;
        grid_size   = 200.0f;
        cell_size   = grid_size / (WAVE_VERTEX_COUNT - 1);

        height_map_array.Set(reinterpret_cast<float *>(height_map), WAVE_VERTEX_COUNT);
        height_map_array_ref.Set(reinterpret_cast<float *>(height_map_ref), WAVE_VERTEX_COUNT);
    } // CDAWaveData

} g_wave_data;


// ----------------------------------------------------------------------------
// Name: CDAWave::CDAWave
// Desc: Constructor
// ----------------------------------------------------------------------------
CDAWave::CDAWave() : m_data(g_wave_data)
{
    // Set the initial values
    m_material_id           = 0;
    m_device                = 0;
    m_pmesh                 = 0;
    m_pouter_mesh           = 0;
    m_dirty                 = true;
    m_scroll                = true;

    // Set the swell params
    m_swell                 = true;
    m_swell_offset_i        = 0;
    m_swell_offset_j        = 0;
    m_num_swell_x           = 3;
    m_num_swell_y           = 14;
    m_swell_speed_x         = 0.15f;
    m_swell_speed_y         = 0.3f;
    m_swell_height_x        = 0.075f;
    m_swell_height_y        = 0.2f;
    m_last_update_time      = -1.0f;

    // Set the world matrix
    m_world_mat             = Matrix::GetIdentityRef();

    // Set the rectangle bounding the camera position to be the 
    // center most cell of the grid
    int num_cells           = WAVE_VERTEX_COUNT - 1;
    int num_cells_div2      = static_cast<int>(num_cells / 2);
    float grid_ctr          = m_data.grid_size * 0.5f;
    float pt1               = (m_data.cell_size * num_cells_div2) - grid_ctr;
    float pt2               = (m_data.cell_size + pt1);
    m_camera_rect           = Vec4(pt1, pt2, pt1, pt2); // (xmin, xmax, ymin, ymax)
} // CDAWave


// ----------------------------------------------------------------------------
// Name: CDAWave::~CDAWave
// Desc: Destructor
// ----------------------------------------------------------------------------
CDAWave::~CDAWave()
{
    Release();
} // ~CDAWave


// ----------------------------------------------------------------------------
// Name: CDAWave::Create
// Desc: Initialise the wave
// Parm: LPDIRECT3DDEVICE9 device - the D3D device to use
// Retn: bool                     - true if successful
// ----------------------------------------------------------------------------
bool CDAWave::Create(LPDIRECT3DDEVICE9 device)
{
    Release();

    m_device = device;

    uint tex0       = TextureCache::CreateTexture("wave.tga", m_device);
    uint tex1       = TextureCache::CreateTexture("SurfaceMap.tga", m_device);
    uint tex2       = TextureCache::CreateTexture("SurfaceMap2.tga", m_device);

    m_material_id   = MaterialCache::CreateMaterial(tex0, tex1, tex2, 
        SHADER_FILE_NAME, FX_WORLDVIEWPROJ | FX_TEX0 | FX_TEX1 | FX_TEX2, true);

    // Triangle vertices, normals, z-values
    for (int i = 0; i < WAVE_VERTEX_COUNT; i++)
    {
        for (int j = 0; j < WAVE_VERTEX_COUNT; j++)
        {
            // Get the vertex and normal
            Vec3 &v = m_data.vertex_array[i][j];
            Vec3 &n = m_data.normal_array[i][j];

            // Vertices, center of grid is at x=0, y=0
            v.x = i * m_data.cell_size - m_data.grid_size / 2;
            v.y = j * m_data.cell_size - m_data.grid_size / 2;
            v.z = 0;

            // Normal - later we will let the hardware normalise
            // the normals
            n.z = -2 * m_data.cell_size;

            // Z-values
            m_data.height_map[i][j]     = 0;
            m_data.height_map_ref[i][j] = 0;

        } // for
    } // for

    // Normals at the edge of the grid point straight up
    for (int i = 0; i < WAVE_VERTEX_COUNT; i++)
    {
        m_data.normal_array[i][0].z             = -1;
        m_data.normal_array[i][WAVE_VERTEX_COUNT - 1].z = -1;
    } // for
    for (int j = 0; j < WAVE_VERTEX_COUNT; j++)
    {
        m_data.normal_array[0][j].z             = -1;
        m_data.normal_array[WAVE_VERTEX_COUNT - 1][j].z = -1;
    } // for

    // The mesh creation data
    Mesh_IndexTriangleStrip::VertexVec    verticies;
    Mesh_IndexTriangleStrip::IndexVecVec  indicies;

    // Resize the vertex array
    verticies.resize(WAVE_VERTEX_COUNT * WAVE_VERTEX_COUNT);

    // Create the indicies
    for (size_t i = 0; i < WAVE_VERTEX_COUNT - 1; i++)
    {
        // Create a new triangle strip
        Mesh_IndexTriangleStrip::IndexVec tri_strip;

        // Add the indicies to this triangle strip
        for (size_t j = 0; j < WAVE_VERTEX_COUNT; j++)
        {
            // Can do this faster!!
            tri_strip.push_back(i * WAVE_VERTEX_COUNT + j);
            tri_strip.push_back((i + 1) * WAVE_VERTEX_COUNT + j);
        } // for

        // Can do this faster!!
        indicies.push_back(tri_strip);
    } // for

    // Create the mesh
    m_pmesh = new Mesh_IndexTriangleStrip("CDA_Wave", device, verticies, indicies);

    verticies.clear();
    verticies.resize(16);

    const float outer_size = 500.0f;
    const float inner_size = m_data.grid_size * 0.485f;
    float size[] = { -outer_size, -inner_size, inner_size, outer_size };

    for (uint i = 0; i < 4; i++)
    {
        for (uint j = 0; j < 4; j++)
        {
            verticies[(i * 4) + j].loc.Set(size[i], size[j], 0.15f);
            verticies[(i * 4) + j].norm.Set(0.0f, 0.0f, -1.0f);
            verticies[(i * 4) + j].diff     = Color::White;
            verticies[(i * 4) + j].u        = 0.5f;
            verticies[(i * 4) + j].v        = 0.5f;
            verticies[(i * 4) + j].u2       = (float) i;
            verticies[(i * 4) + j].v2       = (float) j;
        } // for
    } // for

    indicies.clear();
    indicies.resize(4);

    indicies[0].resize(8);
    indicies[0][0]  = 0;    indicies[0][1]  = 4;    indicies[0][2]  = 1;    indicies[0][3]  = 5;
    indicies[0][4]  = 2;    indicies[0][5]  = 6;    indicies[0][6]  = 3;    indicies[0][7]  = 7;

    indicies[1].resize(4);
    indicies[1][0]  = 4;    indicies[1][1]  = 8;    indicies[1][2]  = 5;    indicies[1][3]  = 9;

    indicies[2].resize(4);
    indicies[2][0]  = 6;    indicies[2][1]  = 10;   indicies[2][2]  = 7;    indicies[2][3]  = 11;

    indicies[3].resize(8);
    indicies[3][0]  = 8;    indicies[3][1]  = 12;   indicies[3][2]  = 9;    indicies[3][3]  = 13;
    indicies[3][4]  = 10;   indicies[3][5]  = 14;   indicies[3][6]  = 11;   indicies[3][7]  = 15;

    m_pouter_mesh   = new Mesh_IndexTriangleStrip("Ocean", m_device, verticies, indicies, false);

    // Done
    return true;
} // Create


// ----------------------------------------------------------------------------
// Name: CDAWave::Release
// Desc: Release the data from the device
// ----------------------------------------------------------------------------
void CDAWave::Release()
{
    if (m_pmesh)
    {
        delete m_pmesh;
        m_pmesh = 0;
    } // if

    if (m_pouter_mesh)
    {
        delete m_pouter_mesh;
        m_pouter_mesh = 0;
    } // if

    m_material_id   = 0;
    m_device        = 0;
} // Release


// ----------------------------------------------------------------------------
// Name: CDAWave::Simulate
// Desc: Simulate the wave
// Parm: float t - the engine time
// ----------------------------------------------------------------------------
void CDAWave::Simulate(float t)
{
    for (uint k = 0; k < 60; k++)
    {
        int i = Random::IntRand(2, WAVE_VERTEX_COUNT - 2);
        while (i > -10 && i < 10)
            i = Random::IntRand(2, WAVE_VERTEX_COUNT - 2);

        int j = Random::IntRand(2, WAVE_VERTEX_COUNT - 2);
        while (j > -10 && j < 10)
            j = Random::IntRand(2, WAVE_VERTEX_COUNT - 2);

        m_data.height_map[i][j] = m_data.height_map_ref[i][j] = -0.105f;
    } // for

    // Update at about 20fps
    //if (t - m_last_update_time < 0.03f)
    //    return;
    //m_last_update_time = t;

    // Reposition the mesh and alter the verticies if 
    // the camera has moved into a new cell
    if (m_scroll)
        InternalMoveMesh();

    // Perform the CDA (central difference approximation)
    // algorithm simulation
    InternalSimulateCDA(UPDATE_TIME);

    // If we are simulating a swell
    if (m_swell)
    {
        // Simulate the swell
        InternalSimulateSwell(t);

        // Update the vertices and the normals
        for (int i = 0; i < WAVE_VERTEX_COUNT; i++)
        {
            for (int j = 0; j < WAVE_VERTEX_COUNT; j++)
            {
                // Only the z needs to be updated
                m_data.height_map_comb[i][j] = m_data.height_map[i][j] + m_data.height_map_swell[i][j];
                m_data.vertex_array[i][j].z  = 0.0f - m_data.height_map_comb[i][j];

                // Only the x and y need to be updated
                m_data.normal_array[i][j].x = 0.0f - (m_data.height_map_comb[i][j-1] - m_data.height_map_comb[i][j+1]);
                m_data.normal_array[i][j].y = 0.0f - (m_data.height_map_comb[i-1][j] - m_data.height_map_comb[i+1][j]);
            } // for
        } // for
    } // if
    else
    {
        // We are not simulating a swell, so there is no need 
        // to run the algorithm or combine the results.

        // Update the vertices and the normals
        for (int i = 0; i < WAVE_VERTEX_COUNT; i++)
        {
            for (int j = 0; j < WAVE_VERTEX_COUNT; j++)
            {
                // Only the z needs to be updated
                m_data.vertex_array[i][j].z  = 0.0f - m_data.height_map[i][j];

                // Only the x and y need to be updated
                m_data.normal_array[i][j].x = 0.0f - (m_data.height_map[i][j-1] - m_data.height_map[i][j+1]);
                m_data.normal_array[i][j].y = 0.0f - (m_data.height_map[i-1][j] - m_data.height_map[i+1][j]);
            } // for
        } // for
    } // else

    // Swap pointers
    Utility::Swap(m_data.height_map_array.pdata, m_data.height_map_array_ref.pdata);
} // Simulate


// ----------------------------------------------------------------------------
// Name: CDAWave::InternalSimulateCDA
// Desc: Simulate the central difference algorithm for the wave ripples
// Parm: float dt - the delta time
// ----------------------------------------------------------------------------
void CDAWave::InternalSimulateCDA(float dt)
{
    // Precalculate the coefficients
    const float A = (m_data.wave_space * dt / m_data.cell_size) * (m_data.wave_space * dt / m_data.cell_size);
    const float B = 2 - 4 * A;

    const int edge_min = static_cast<int>(0.15f * WAVE_VERTEX_COUNT);
    const int edge_max = static_cast<int>(0.85f * WAVE_VERTEX_COUNT);

    // Edges are unchanged
    for (int i = 1; i < WAVE_VERTEX_COUNT - 1; i++)
    {
        for (int j = 1; j < WAVE_VERTEX_COUNT - 1; j++)
        {
            // Integrate, replacing z[n-1] with z[n+1] in place
            m_data.height_map_array_ref[i][j] = 
                A * (m_data.height_map_array[i-1][j] + 
                     m_data.height_map_array[i+1][j] + 
                     m_data.height_map_array[i][j-1] + 
                     m_data.height_map_array[i][j+1])
              + B *  m_data.height_map_array[i][j] - 
                     m_data.height_map_array_ref[i][j];

            // Apply damping coefficients
            m_data.height_map_array_ref[i][j] *= FFT_DECAY;

            if (m_data.height_map_array_ref[i][j] >= m_data.wave_height)
                m_data.height_map_array_ref[i][j] *= 0.75f;

            if (i < edge_min || i > edge_max || j < edge_min || j > edge_max)
            {
                m_data.height_map_array_ref[i][j] *= 0.98f;
            } /// if

        } // for
    } // for
} // InternalSimulateCDA


// ----------------------------------------------------------------------------
// Name: CDAWave::InternalSimulateSwell
// Desc: Simulate the ocean wave
// Parm: float t - the current time
// ----------------------------------------------------------------------------
void CDAWave::InternalSimulateSwell(float t)
{
    float sin_table_x[WAVE_VERTEX_COUNT];
    float cos_table_y[WAVE_VERTEX_COUNT];

    for (int i = 0; i < WAVE_VERTEX_COUNT; i++)
        sin_table_x[i] = (1.0f + sinf((t * m_swell_speed_x) + 
            (((i * (float)m_num_swell_x) / WAVE_VERTEX_COUNT) * 2.0f * D3DX_PI))) * 
            0.5f * m_data.cell_size * m_swell_height_x;

    for (int i = 0; i < WAVE_VERTEX_COUNT; i++)
        cos_table_y[i] = (1.0f + cosf((t * m_swell_speed_y) + 
            (((i * (float)m_num_swell_y) / WAVE_VERTEX_COUNT) * 2.0f * D3DX_PI))) * 
            0.5f * m_data.cell_size * m_swell_height_y;

    // Update the vertices and the normals
    for (int i = 0; i < WAVE_VERTEX_COUNT; i++)
    {
        for (int j = 0; j < WAVE_VERTEX_COUNT; j++)
        {
            int idx_i = (i + m_swell_offset_i) % WAVE_VERTEX_COUNT;
            int idx_j = (j + m_swell_offset_j) % WAVE_VERTEX_COUNT;
            
            m_data.height_map_swell[i][j] = (
                sin_table_x[idx_i] + 
                cos_table_y[idx_j]);

            // OLD code, looks better but the fmod was too slow
            //m_data.height_map_swell[i][j] = (
            //    sin_table_x[idx_i] + 
            //    cos_table_y[(int) fmodf(idx_j + (idx_j * 0.75f), (float) idx_j)]);
        } // for
    } // for
} // InternalSimulateSwell


// ----------------------------------------------------------------------------
// Name: CDAWave::InternalMoveMesh
// Desc: Recalculate the worl matrix and the vertex data so the camera is always
//       in the middle of them mesh and the mesh moves with the camera
// Parm: const Vec3 &camera_pos - the camera position in world coordinates
// ----------------------------------------------------------------------------
void CDAWave::InternalMoveMesh()
{
    // Get the camera position
    const Vec3 &camera_pos = CameraSingleton::Instance().GetPosition();

    // TODO: Another spot for optimization, instead of moving 
    // one cell at a time in a while loop, we should calculate the 
    // amount to move in both x, and y axis and do it all in a
    // single pass.  When moving at high speed on a diagonal at 
    // 30fps it is possible that we are doing upto 10 loops - which
    // is a waste of valuable electrons.

    // See if the camera has moved out of it's 
    // current rect to the left
    while (camera_pos[0] < m_camera_rect[0])
    {
        // Moved left
        m_camera_rect[0] -= m_data.cell_size;
        m_camera_rect[1] -= m_data.cell_size;

        if (--m_swell_offset_i < 0)
            m_swell_offset_i += WAVE_VERTEX_COUNT;

        m_world_mat.PostMultiply(Matrix::MakeNewTranslation(0.0f - m_data.cell_size, 0.0f, 0.0f));

        for (int i = WAVE_VERTEX_COUNT - 1; i > 2; i--) for (int j = 1; j < WAVE_VERTEX_COUNT - 1; j++)
        {
            m_data.height_map_array[i][j] = m_data.height_map_array[i-1][j];
            m_data.height_map_array_ref[i][j] = m_data.height_map_array_ref[i-1][j];
        } // for
    } // while

    // See if the camera has moved out of it's 
    // current rect to the right
    while (camera_pos[0] >= m_camera_rect[1])
    {
        // Moved right
        m_camera_rect[0] += m_data.cell_size;
        m_camera_rect[1] += m_data.cell_size;

        m_swell_offset_i++;

        m_world_mat.PostMultiply(Matrix::MakeNewTranslation(m_data.cell_size, 0.0f, 0.0f));

        for (int i = 1; i < WAVE_VERTEX_COUNT - 2; i++) for (int j = 1; j < WAVE_VERTEX_COUNT - 1; j++)
        {
            m_data.height_map_array[i][j] = m_data.height_map_array[i+1][j];
            m_data.height_map_array_ref[i][j] = m_data.height_map_array_ref[i+1][j];
        } // for
    } // while

    // See if the camera has moved out of it's 
    // current rect to the front
    while (camera_pos[1] < m_camera_rect[2])
    {
        // Moved backward
        m_camera_rect[2] -= m_data.cell_size;
        m_camera_rect[3] -= m_data.cell_size;

        if (--m_swell_offset_j < 0)
            m_swell_offset_j += WAVE_VERTEX_COUNT;

        m_world_mat.PostMultiply(Matrix::MakeNewTranslation(0.0f, 0.0f - m_data.cell_size, 0.0f));

        for (int i = 1; i < WAVE_VERTEX_COUNT - 1; i++) for (int j = WAVE_VERTEX_COUNT - 1; j > 2; j--)
        {
            m_data.height_map_array[i][j] = m_data.height_map_array[i][j-1];
            m_data.height_map_array_ref[i][j] = m_data.height_map_array_ref[i][j-1];
        } // for
    } // while

    // See if the camera has moved out of it's 
    // current rect to the back
    while (camera_pos[1] >= m_camera_rect[3])
    {
        // Moved forward
        m_camera_rect[2] += m_data.cell_size;
        m_camera_rect[3] += m_data.cell_size;

        m_swell_offset_j++;

        m_world_mat.PostMultiply(Matrix::MakeNewTranslation(0.0f, m_data.cell_size, 0.0f));

        for (int i = 1; i < WAVE_VERTEX_COUNT - 1; i++) for (int j = 1; j < WAVE_VERTEX_COUNT - 2; j++)
        {
            m_data.height_map_array[i][j] = m_data.height_map_array[i][j+1];
            m_data.height_map_array_ref[i][j] = m_data.height_map_array_ref[i][j+1];
        } // for
    } // while
} // InternalMoveMesh


// ----------------------------------------------------------------------------
// Name: CDAWave::Render
// Desc: Render the wave
// ----------------------------------------------------------------------------
void CDAWave::Render()
{
    if (!m_device)
        return;

    // Get a pointer to the vertex buffer
    Mesh_IndexTriangleStrip::Vertex *verts;
    if (!m_pmesh->LockVertexBuffer(&verts, D3DLOCK_DISCARD))
        return;

    // TEST: Animate the cloud surface map texture.  If this
    // looks good, I'll move it into the shader.
    static float ctr = 0.0f;
    ctr += 0.002f;

    // Assign the verticies
    int count = 0;
    for (int i = 0; i < WAVE_VERTEX_COUNT; i++)
    {
        for (int j = 0; j < WAVE_VERTEX_COUNT; j++)
        {
            // Vertex x, y, z
            verts[count].loc[0]  = m_data.vertex_array[i][j].x;
            verts[count].loc[1]  = m_data.vertex_array[i][j].y;
            verts[count].loc[2]  = m_data.vertex_array[i][j].z;

            // normal x, y, z
            verts[count].norm[0] = m_data.normal_array[i][j].x;
            verts[count].norm[1] = m_data.normal_array[i][j].y;
            verts[count].norm[2] = m_data.normal_array[i][j].z;

            // diffuse color
            verts[count].diff    = Color::White;

            // u, v coords
            float uv = 0.5f + (m_data.vertex_array[i][j].z * 0.25f / m_data.wave_height);
            Utility::Clamp(uv, 0.01f, 0.99f);
            verts[count].u  = uv;
            verts[count].v  = uv;

            verts[count].u2 = ctr + ((i + m_swell_offset_i) * 0.05f);
            verts[count].v2 = -ctr + ((j + m_swell_offset_j) * 0.05f);

            count++;
        } // for
    } // for

    // Update the verts
    m_pmesh->UnlockVertexBuffer(m_dirty);

    // Set the world matrix
    m_device->SetTransform(D3DTS_WORLD, &m_world_mat);

    // Draw the mesh
    Effect *peffect = MaterialCache::Apply(m_material_id, m_world_mat, m_device);
    if (peffect)
    {
        uint num_passes;
        if (peffect->Begin(num_passes))
        {
            for (uint i = 0; i < num_passes; i++)
            {
                peffect->Pass(i);
                m_pmesh->Draw();
                m_pouter_mesh->Draw();
            } // for
            peffect->End();
        } // if
    } // if

    m_dirty = false;
} // Render


// ----------------------------------------------------------------------------
// Name: CDAWave::GetWaveHeight
// Desc: Calculate the wave height and the normal at a particular x, y position
// Parm: float x    - the x position
// Parm: float y    - the y position
// Parm: float &zw  - the z position of the water
// Parm: Vec3 &nw   - the normal of the water
// ----------------------------------------------------------------------------
void CDAWave::GetWaveHeight(float x, float y, float &zw, Vec3 &nw)
{
    // Put x, and y in model space.
    x -= m_world_mat._41;
    y -= m_world_mat._42;

    const float rh = 1 / m_data.cell_size;

    // Fractional index
    float u = (x + 0.5f * m_data.grid_size) * rh;
    float v = (y + 0.5f * m_data.grid_size) * rh;

    // Lower-left vertex of the enclosing grid cell
    const long i = long( u );
    const long j = long( v );

    // Interpolation coefficients
    const float a  = u - i;
    const float b  = v - j;
    const float ab = a * b;

    // If the position is outside of the grid, give a fake value
    if (i < 0 || WAVE_VERTEX_COUNT <= i || j < 0 || WAVE_VERTEX_COUNT <= j)
    {
        zw   = 0;
        nw.x = 0;
        nw.y = 0;
        nw.z = -1;
    } // if
    else
    {
        if (m_swell)
        {
            // Bilinearly interpolate zw and nw
            zw = (1 - a - b + ab) * m_data.height_map_comb[i][j]   + 
                (b - ab) * m_data.height_map_comb[i][j+1]         + 
                (a-ab) * m_data.height_map_comb[i+1][j]           + 
                ab * m_data.height_map_comb[i+1][j+1];

            nw = (1 - a - b + ab) * m_data.normal_array[i][j]      +
                (b - ab) * m_data.normal_array[i][j+1]            + 
                (a-ab) * m_data.normal_array[i+1][j]              + 
                ab * m_data.normal_array[i+1][j+1];
        } // if
        else
        {
            // Bilinearly interpolate zw and nw
            zw = (1 - a - b + ab) * m_data.height_map[i][j]   + 
                (b - ab) * m_data.height_map[i][j+1]         + 
                (a-ab) * m_data.height_map[i+1][j]           + 
                ab * m_data.height_map[i+1][j+1];

            nw = (1 - a - b + ab) * m_data.normal_array[i][j]      +
                (b - ab) * m_data.normal_array[i][j+1]            + 
                (a-ab) * m_data.normal_array[i+1][j]              + 
                ab * m_data.normal_array[i+1][j+1];
        } // else

        nw[2] = 0.0f - nw[2];
        zw    = 0.0f - zw;
        nw.Normalize(nw);
    } // else
} // GetWaveHeight


// ----------------------------------------------------------------------------
// Name: CDAWave::InjectRipple
// Desc: Inject a ripple into the wave
// Parm: float x  - the x position in world space
// Parm: float y  - the y position in world space
// Parm: float h  - the height of the ripple
// ----------------------------------------------------------------------------
void CDAWave::InjectRipple(float x, float y, float h)
{
    x -= m_world_mat._41;
    y -= m_world_mat._42;

    const float rh = 1 / m_data.cell_size;

    // Fractional index
    float u = (x + 0.5f * m_data.grid_size) * rh;
    float v = (y + 0.5f * m_data.grid_size) * rh;

    // Lower-left vertex of the enclosing grid cell
    const long i = long( u + 0.49999f );
    const long j = long( v + 0.49999f );

    if (i < 0 || i >= WAVE_VERTEX_COUNT || j < 0 || j >= WAVE_VERTEX_COUNT)
        return;

    m_data.height_map[i][j] = m_data.height_map_ref[i][j] = 0.0f - h;
} // InjectRipple


// ----------------------------------------------------------------------------
// Name: CDAWave::GetBounds
// Desc: Get the bounding sphere of the water
// Parm: Sphere &sphere - the bsphere
// ----------------------------------------------------------------------------
const Sphere &CDAWave::GetBounds()
{
    m_pmesh->GetBounds(m_sphere);
    return m_sphere;
} // GetBounds


// ----------------------------------------------------------------------------
// Name: CDAWave::SetCDAParams
// Desc: Set the wave CDA params
// Parm: float wave_space   - the wave space
// Parm: float grid_size    - the total grid size
// Parm: float wave_height  - the wave height
// ----------------------------------------------------------------------------
void CDAWave::SetCDAParams(float wave_space, float grid_size, float wave_height)
{
    m_data.wave_space   = wave_space;
    m_data.wave_height  = wave_height;
    m_data.grid_size    = grid_size;
    m_data.cell_size    = grid_size / (WAVE_VERTEX_COUNT - 1);
} // SetCDAParams


// ----------------------------------------------------------------------------
// Name: 
// Desc: Set the swell swell params
// Parm: int num_swell_x      - the number of swell along the x axis
// Parm: int num_swell_y      - the number of swell along the y axis
// Parm: float swell_speed_x  - the speed of the swell along the x axis
// Parm: float swell_speed_y  - the speed of the swell alng the y axis
// Parm: float swell_height_x - the height of the swell along the x axis
// Parm: float swell_height_y - the height of the swell along the y axis
// ----------------------------------------------------------------------------
void CDAWave::SetSwellParams (int    num_swell_x, 
                              int    num_swell_y, 
                              float swell_speed_x, 
                              float swell_speed_y, 
                              float swell_height_x, 
                              float swell_height_y)
{
    m_num_swell_x        = num_swell_x;
    m_num_swell_y        = num_swell_y;
    m_swell_speed_x      = swell_speed_x;
    m_swell_speed_y      = swell_speed_y;
    m_swell_height_x     = swell_height_x;
    m_swell_height_y     = swell_height_y;
} // SetSwellParams


// -- EOF


// TODO: OLD shader code, can delete this soon
//
/*
texture tex0 < string name = "0"; >;
texture tex1 < string name = "1"; >;

float4x4 WorldViewProj : WORLDVIEWPROJ;

sampler  DiffuseSampler;

struct VS_OUTPUT
{
    float4 Position  : POSITION;
    float4 Diffuse   : COLOR0;
    float2 TexCoord0 : TEXCOORD0;
    float2 TexCoord1 : TEXCOORD1;
};

struct PS_OUTPUT
{
    float4 RGBColor : COLOR0;
};

VS_OUTPUT VS (float4 Position   : POSITION, 
              float4 Diffuse    : COLOR0,
              float2 TexCoord0  : TEXCOORD0,
              float2 TexCoord1  : TEXCOORD1)
{
    VS_OUTPUT Out   = (VS_OUTPUT) 0;
    
    Out.Position    = mul(Position, WorldViewProj);
    Out.Diffuse     = Diffuse;
    Out.TexCoord0   = TexCoord0;
    Out.TexCoord1   = TexCoord1;

    return Out;
}

PS_OUTPUT PS (VS_OUTPUT In) : COLOR
{
    PS_OUTPUT Out   = (PS_OUTPUT) 0;
    
    float4 color1   = tex2D(DiffuseSampler, In.TexCoord0) * In.Diffuse * 1.5; // bad!!!
    float4 color2   = tex2D(DiffuseSampler, In.TexCoord1) * 0.1;
    
    color1.a        = 0.85;
    color2.a        = 0.0;
    
    Out.RGBColor    = color1 + color2;
    
    return Out;
}

technique tec0
{
    pass p0
    {
        // Set up reasonable material defaults
        MaterialAmbient = {1.0, 1.0, 1.0, 1.0}; 
        MaterialDiffuse = {1.0, 1.0, 1.0, 1.0}; 
        MaterialSpecular = {1.0, 1.0, 1.0, 1.0}; 
        MaterialPower = 40.0f;
        
        // Turn lighting on and use light 0
        LightEnable[0] = False;
        Lighting = False;
        
        // Set up texture stage 0
        Texture[0] = <tex0>;
        Texture[1] = <tex1>;

        ColorOp[0] = Modulate;
        ColorArg1[0] = Texture;
        ColorArg2[0] = Diffuse;

        ColorOp[1] = Modulate;
        ColorArg1[1] = Current;
        ColorArg2[1] = Texture;

        AlphaOp[0] = Modulate;
        AlphaArg1[0] = Texture;
        AlphaArg2[0] = Diffuse;

        MinFilter[0] = Linear;
        MagFilter[0] = Linear;
        MipFilter[0] = Linear;
        
        // Disable texture stage 1
        ColorOp[2] = Disable;
        AlphaOp[1] = Disable;
        
        VertexShader = compile vs_1_1 VS();
        PixelShader =  compile ps_1_1 PS();
    }
}


*/