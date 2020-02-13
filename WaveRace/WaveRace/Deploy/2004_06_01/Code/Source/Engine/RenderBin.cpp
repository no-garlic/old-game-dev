// ----------------------------------------------------------------------------
// File: RenderBin.cpp
// Desc: Provides a method of sorting and scheduling items to be rendered, then 
//       rendering them in a controlled manner
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Engine/RenderBin.h"
#include "Engine/Material.h"
#include "Engine/Camera.h"
#include "Math/Vec3.h"
#include "Math/Sphere.h"


// ----------------------------------------------------------------------------
// Static initialsiers
// ----------------------------------------------------------------------------
ulong RenderBin::s_frame_count = 1;


// ----------------------------------------------------------------------------
// Name: RenderBin::RenderBin
// Desc: Constructor
// ----------------------------------------------------------------------------
RenderBin::RenderBin()
{
    m_device    = 0;
} // RenderBin


// ----------------------------------------------------------------------------
// Name: RenderBin::~RenderBin
// Desc: Destructor
// ----------------------------------------------------------------------------
RenderBin::~RenderBin()
{
    Release();
} // ~RenderBin


// ----------------------------------------------------------------------------
// Name: RenderBin::Create
// Desc: Create the render bin
// Parm: LPDIRECT3DDEVICE9 device - the device
// Retn: bool                     - true if successful
// ----------------------------------------------------------------------------
bool RenderBin::Create(LPDIRECT3DDEVICE9 device)
{
    Release();
    m_device = device;
    return (m_device != 0);
} // Create


// ----------------------------------------------------------------------------
// Name: RenderBin::Release
// Desc: Release the render bin
// ----------------------------------------------------------------------------
void RenderBin::Release()
{
    m_device = 0;
} // release


// ----------------------------------------------------------------------------
// Name: RenderBin::AddRenderTarget
// Desc: Add an item to be rendered
// Parm: Mesh *pmesh          - the mesh
// Parm: uint material_id     - the material id
// Parm: Matrix world_matrix  - the world matrix
// ----------------------------------------------------------------------------
void RenderBin::AddRenderTarget(Mesh *pmesh, uint material_id, Matrix world_matrix)
{
    // Recalculate the frustum at the start of each cycle
    if (m_opaque_bin.empty() && m_transparent_bin.empty())
    {
        Camera &camera = CameraSingleton::Instance();
        m_frustum.SetProjMatrix(camera.GetProjMatrix());
        m_frustum.SetViewMatrix(camera.GetViewMatrix());
    } // if

    // Get the bounding sphere
    Sphere sphere;
    pmesh->GetBounds(sphere);

    // Create a render target
    RenderBin::RenderTarget target;
    target.pmesh        = pmesh;
    target.material_id  = material_id;
    target.world_matrix = world_matrix;

    // If the material is opaque, we don't need to sort
    // the objects by distance from the viewer, so we 
    // place them in a list that is sorted by material.
    if (MaterialCache::IsOpaque(material_id))
    {
        m_opaque_bin.insert(std::make_pair(material_id, target));
    } // if

    // The material has some transparency, we we need to sort
    // the objects to be rendered last, and from back to front.
    else
    {
        Camera &camera = CameraSingleton::Instance();
        const Vec3 &view_vec = camera.GetPosition();

        Vec3 world_vec(world_matrix._41, world_matrix._42, world_matrix._43);
        world_vec.Add(world_vec, sphere.center);
        world_vec.Subtract(world_vec, view_vec);
        float dst = world_vec.LengthSq();

        m_transparent_bin.insert(std::make_pair(-dst, target));
    } // else
} // Render


// ----------------------------------------------------------------------------
// Name: RenderBin::Render
// Desc: Render the contents of the bin and then clear the bin
// ----------------------------------------------------------------------------
void RenderBin::Render()
{
    // We need a device to render
    if (!m_device)
        return;

    // Render all opaque objects first
    std::multimap<uint, RenderBin::RenderTarget>::iterator opaque_iter = m_opaque_bin.begin();
    for (; opaque_iter != m_opaque_bin.end(); ++opaque_iter)
    {
        m_device->SetTransform(D3DTS_WORLD, &(opaque_iter->second.world_matrix));
        Effect *peffect = MaterialCache::Apply(opaque_iter->second.material_id, opaque_iter->second.world_matrix, m_device);
        if (peffect)
        {
            uint num_passes;
            if (peffect->Begin(num_passes))
            {
                for (uint i = 0; i < num_passes; i++)
                {
                    peffect->Pass(i);
                    opaque_iter->second.pmesh->Draw();
                } // for
                peffect->End();
            } // if
        } // if
    } // for

    // Render all transparent objects last
    std::multimap<float, RenderBin::RenderTarget>::iterator transparent_iter = m_transparent_bin.begin();
    for (; transparent_iter != m_transparent_bin.end(); ++transparent_iter)
    {
        m_device->SetTransform(D3DTS_WORLD, &(transparent_iter->second.world_matrix));
        Effect *peffect = MaterialCache::Apply(transparent_iter->second.material_id, opaque_iter->second.world_matrix, m_device);
        if (peffect)
        {
            uint num_passes;
            if (peffect->Begin(num_passes))
            {
                for (uint i = 0; i < num_passes; i++)
                {
                    peffect->Pass(i);
                    transparent_iter->second.pmesh->Draw();
                } // for
                peffect->End();
            } // if
        } // if
    } // for
    
    // Clear the lists
    m_opaque_bin.clear();
    m_transparent_bin.clear();

    // Increment the frame counter
    RenderBin::s_frame_count++;
} // Render


// -- EOF
