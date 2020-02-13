// ----------------------------------------------------------------------------
// File: Material.h
// Desc: Provides resource management for materials and textures
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes for the material and texture classes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include "Common/Logging.h"
#include "Common/FilePath.h"
#include "Engine/Material.h"
#include "Engine/Camera.h"


// ----------------------------------------------------------------------------
// Initialise the texture cache static members
// ----------------------------------------------------------------------------
uint                                            TextureCache::s_counter         = 1;
std::map<std::string, TextureCache::TexFile *>  TextureCache::s_texture_files;
std::map<uint, TextureCache::Record>            TextureCache::s_texture_ids;

// ----------------------------------------------------------------------------
// Initialise the material cache static members
// ----------------------------------------------------------------------------
uint                                            MaterialCache::s_counter        = 1;
uint                                            MaterialCache::s_curr_mat       = 0;
bool                                            MaterialCache::s_default_mat    = false;
LPDIRECT3DDEVICE9                               MaterialCache::s_device         = 0;
std::map<uint, MaterialCache::Record>           MaterialCache::s_material_ids;


// ----------------------------------------------------------------------------
// Name: TextureCache::CreateTexture
// Desc: Load the texture filename given using the device given.  If the texture
//       has been loaded before and is in the cache, dont load it - rather 
//       return it's id.
// Parm: const char *filename      - the filname of the texture to load
// Parm: LPDIRECT3DDEVICE9 device  - the device to load the texture with
// Retn: uint                      - the texture id
// ----------------------------------------------------------------------------
uint TextureCache::CreateTexture(const char *filename, LPDIRECT3DDEVICE9 device)
{
    // If the filename is blank, return 0;
    if (!filename || strlen(filename) == 0)
        return 0;

    // Pointer for the texture file
    TexFile *ptex_file = 0;

    // Add the data path to the filename
    std::string path_name = filename;
    FilePath::StripPath(path_name);
    std::string found = FilePathSingleton::Instance().FindFile(path_name);
    if (!found.empty())
        path_name = found;

    // Se if we have already loaded the texture file
    std::map<std::string, TextureCache::TexFile *>::iterator tex_file_iter = s_texture_files.find(filename);
    if (tex_file_iter != s_texture_files.end())
    {
        ptex_file = tex_file_iter->second;
    } // if
    else
    {
        // Create a new texture file
        ptex_file = new TexFile;
        ptex_file->filename = filename;

        // Load the file from disk
        if (FAILED(D3DXCreateTextureFromFile(device, path_name.c_str(), &ptex_file->d3d_tex)))
        {
            // Failed to load the texture fipl from disk
            LOG_ERROR << "Failed to load the texture: " << path_name << ENDLOG;

            delete ptex_file;
            return 0;
        } // if
        else
        {
            // Successfully loaded the texture file from disk
            LOG_INFO << "Loaded the texture file: " << path_name << ENDLOG;
    
            // Add the texture to the cache
            s_texture_files.insert(std::make_pair(ptex_file->filename, ptex_file));
        } // else
    } // else

    // Check that the texture loaded
    if (!ptex_file)
        return 0;

    // Now check if we have already got a texture record in the cache
    std::map<uint, TextureCache::Record>::iterator texture_record_iter = s_texture_ids.begin();
    for (; texture_record_iter != s_texture_ids.end(); ++texture_record_iter)
    {
        TextureCache::Record &record = texture_record_iter->second;
        if (record.ptex_file->filename  == filename)
            return texture_record_iter->first;
    } // for

    // Create a new texture record
    TextureCache::Record record;
    record.ptex_file    = ptex_file;

    // Add the texture record to the cache
    uint id = TextureCache::s_counter++;
    TextureCache::s_texture_ids.insert(std::make_pair(id, record));

    // Return the texture record id
    return id;
} // CreateTexture


// ----------------------------------------------------------------------------
// Name: TextureCache::GetTexture
// Desc: Get a texture from the cache
// Parm: uint texture_id      - the id of the texture
// Retn: TextureCache::Record - the texture record
// ----------------------------------------------------------------------------
TextureCache::Record TextureCache::GetTexture(uint texture_id)
{
    // Relase all textures
    std::map<uint, TextureCache::Record>::iterator iter = s_texture_ids.find(texture_id);
    if (iter == s_texture_ids.end())
    {
        // Not found, return an empty texture record
        TextureCache::Record record;
        record.ptex_file = 0;

        return record;
    } // if
    else
    {
        // Return the texture record
        return iter->second;
    } // else
} // GetTexture


// ----------------------------------------------------------------------------
// Name: TextureCache::Clear
// Desc: Clear all textures in the cache
// ----------------------------------------------------------------------------
void TextureCache::Clear()
{
    std::map<std::string, TextureCache::TexFile *>::iterator iter = s_texture_files.begin();
    for (; iter != s_texture_files.end(); ++iter)
    {
        TextureCache::TexFile *ptex_file = iter->second;
        Memory::SafeRelease(ptex_file->d3d_tex);
    } // for

    s_texture_ids.clear();
    s_texture_files.clear();
    s_counter = 1;
} // Clear


// ----------------------------------------------------------------------------
// Name: MaterialCache::CreateMaterial
// Desc: Create a material using the given device and attributes.  Note - if a
//       material already exists in the cache with the given attributes, it is
//       returned rather than creating a new material.
// Parm: uint tex_map0         - the color map
// Parm: uint tex_map1       - the detail map
// Parm: uint tex_map2         - the opacity map
// Parm: Color ambient         - the ambient color
// Parm: Color diffuse         - the diffuse color
// Parm: Color emissive        - the emissive color
// Parm: Color specular        - the specular color
// Parm: float specular_power  - the specular power
// Retn: uint                  - the material id
// ----------------------------------------------------------------------------
uint MaterialCache::CreateMaterial(uint tex_map0, uint tex_map1, uint tex_map2, 
                                   const std::string &effect_filename, int flags, bool isopaque)
{
    // Check if we have already got a material record in the cache
    std::map<uint, MaterialCache::Record>::iterator material_record_iter = s_material_ids.begin();
    for (; material_record_iter != s_material_ids.end(); ++material_record_iter)
    {
        MaterialCache::Record &record = material_record_iter->second;
        if (record.isopaque == isopaque &&
            record.tex_map0 == tex_map0 &&
            record.tex_map1 == tex_map1 &&
            record.tex_map2 == tex_map2 &&
            record.flags    == flags    &&
            record.filename == effect_filename)
        {
            return material_record_iter->first;
        } // if
    } // for

    // Create a new material record
    MaterialCache::Record record;

    // Set the material record attributes
    record.isopaque         = isopaque;
    record.tex_map0         = tex_map0;
    record.tex_map1         = tex_map1;
    record.tex_map2         = tex_map2;
    record.flags            = flags;
    record.filename         = effect_filename;
    record.peffect          = new Effect();

    // Create the effect
    std::string fn = FilePathSingleton::Instance().FindFile(effect_filename);
    if (!record.peffect->Create(s_device, fn.c_str(), flags))
        return 0;

    // Add the material to the cache
    uint id = MaterialCache::s_counter++;
    MaterialCache::s_material_ids.insert(std::make_pair(id, record));

    // return the material id
    return id;
} // CreateMaterial


// ----------------------------------------------------------------------------
// Name: MaterialCache::CreateDefaultMaterial
// Desc: Create the default material
// ----------------------------------------------------------------------------
bool MaterialCache::Create(LPDIRECT3DDEVICE9 device)
{
    Release();

    s_device = device;

    // Create a new material record
    MaterialCache::Record record;

    record.filename = "Default.fx";
    record.tex_map0 = 0;
    record.tex_map1 = 0;
    record.tex_map2 = 0;
    record.isopaque = true;
    record.peffect  = new Effect();

    // Create the effect
    std::string fn = FilePathSingleton::Instance().FindFile(record.filename);
    if (!record.peffect->Create(s_device, fn.c_str(), 0))
        return false;

    // Add the material to the cache
    MaterialCache::s_material_ids.insert(std::make_pair(0, record));
    MaterialCache::s_default_mat = true;

    return true;
} // CreateDefaultMaterial


// ----------------------------------------------------------------------------
// Name: MaterialCache::Release
// Desc: Release the material
// ----------------------------------------------------------------------------
void MaterialCache::Release()
{
    if (!s_device)
        return;

    s_device = 0;

    Clear();
    MaterialCache::s_default_mat = false;
} // Release


// ----------------------------------------------------------------------------
// Name: MaterialCache::GetMaterial
// Desc: Get a material from the cache with the given id
// Parm: uint material_id      - the material id
// Retn: MaterialCache::Record - the material record
// ----------------------------------------------------------------------------
MaterialCache::Record MaterialCache::GetMaterial(uint material_id)
{
    // Find the material record by id
    std::map<uint, MaterialCache::Record>::iterator iter = s_material_ids.find(material_id);
    if (iter == s_material_ids.end())
    {
        // Not found, return an empty material record
        MaterialCache::Record record;
        record.peffect = 0;
        return record;
    } // if
    else
    {
        // Return the material record
        return iter->second;
    } // else
} // GetMaterial


// ----------------------------------------------------------------------------
// Name: MaterialCache::IsOpaque
// Desc: Returns true if the material has no transparency
// Parm: uint id - the material id
// ----------------------------------------------------------------------------
bool MaterialCache::IsOpaque(uint id)
{
    // Find the material record by id
    std::map<uint, MaterialCache::Record>::iterator iter = s_material_ids.find(id);
    if (iter == s_material_ids.end())
        return false;

    return (iter->second.isopaque);
} // IsOpaque


// ----------------------------------------------------------------------------
// Name: MaterialCache::GetCurrentMaterial
// Desc: Get the id of the currently applied material
// Retn: uint - the material id
// ----------------------------------------------------------------------------
uint MaterialCache::GetCurrentMaterial()
{
    return s_curr_mat;
} // GetCurrentMaterial


// ----------------------------------------------------------------------------
// Name: MaterialCache::Clear
// Desc: Clears all materials in the cache
// ----------------------------------------------------------------------------
void MaterialCache::Clear()
{
    std::map<uint, MaterialCache::Record>::iterator iter = s_material_ids.begin();
    for (; iter != s_material_ids.end(); ++iter)
    {
        iter->second.peffect->Release();
        delete iter->second.peffect;
    } // for

    s_material_ids.clear();
    s_counter        = 1;
    s_curr_mat       = 0;
    s_default_mat    = false;
} // Clear


// ----------------------------------------------------------------------------
// Name: MaterialCache::Apply
// Desc: Apply the material given by the material id
// Parm: uint material_id          - the id of the material to apply
// Parm: LPDIRECT3DDEVICE9 device  - the device that applies the material
// ----------------------------------------------------------------------------
Effect *MaterialCache::Apply(uint material_id, const Matrix &world_matrix, LPDIRECT3DDEVICE9 device)
{
    // Check the default material is created
    if (!MaterialCache::s_default_mat)
        Create(device);
    
    // Set the current material id
    s_curr_mat = material_id;

    // Get the material record for the id
    MaterialCache::Record mat = MaterialCache::GetMaterial(material_id);
    if (!mat.peffect)
        return 0;

    // Get the matricies
    const Matrix &view_matrix   = CameraSingleton::Instance().GetViewMatrix();
    const Matrix &proj_matrix   = CameraSingleton::Instance().GetProjMatrix();

    // Set the world matrix
    if (mat.peffect->m_flags & FX_WORLD)
    {
        if (!mat.peffect->SetMatrix("World", world_matrix))
        {
            LOG_ERROR << "Failed to set the world matrix for effect: " << mat.filename << ENDLOG;
            return 0;
        } // if
    } // if

    // Set the view matrix
    if (mat.peffect->m_flags & FX_VIEW)
    {
        if (!mat.peffect->SetMatrix("View", view_matrix))
        {
            LOG_ERROR << "Failed to set the view matrix for effect: " << mat.filename << ENDLOG;
            return 0;
        } // if
    } // if

    // Set the projection matrix
    if (mat.peffect->m_flags & FX_PROJ)
    {
        if (!mat.peffect->SetMatrix("Projection", proj_matrix))
        {
            LOG_ERROR << "Failed to set the projection matrix for effect: " << mat.filename << ENDLOG;
            return 0;
        } // if
    } // if

    // Set the view matrix
    if (mat.peffect->m_flags & FX_WORLDVIEW)
    {
        Matrix world_view_matrix;
        world_view_matrix.Multiply(world_matrix, view_matrix);
        if (!mat.peffect->SetMatrix("WorldView", world_view_matrix))
        {
            LOG_ERROR << "Failed to set the world_view matrix for effect: " << mat.filename << ENDLOG;
            return 0;
        } // if

        if (mat.peffect->m_flags & FX_WORLDVIEWPROJ)
        {
            Matrix world_view_proj_matrix;
            world_view_proj_matrix.Multiply(world_view_matrix, proj_matrix);
            if (!mat.peffect->SetMatrix("WorldViewProj", world_view_proj_matrix))
            {
                LOG_ERROR << "Failed to set the world_view_proj matrix for effect: " << mat.filename << ENDLOG;
                return 0;
            } // if
        } // if
    } // if
    else
    {
        if (mat.peffect->m_flags & FX_WORLDVIEWPROJ)
        {
            Matrix world_view_matrix, world_view_proj_matrix;
            world_view_matrix.Multiply(world_matrix, view_matrix);
            world_view_proj_matrix.Multiply(world_view_matrix, proj_matrix);
            if (!mat.peffect->SetMatrix("WorldViewProj", world_view_proj_matrix))
            {
                LOG_ERROR << "Failed to set the world_view_proj matrix for effect: " << mat.filename << ENDLOG;
                return 0;
            } // if
        } // if
    } // else

    if ((mat.peffect->m_flags & FX_TEX0) && mat.tex_map0)
    {
        LPDIRECT3DTEXTURE9 tex = TextureCache::GetTexture(mat.tex_map0).ptex_file->d3d_tex;
        if (!mat.peffect->SetTexture("tex0", tex))
        {
            LOG_ERROR << "Failed to set the texture tex0 for effect: " << mat.filename << ENDLOG;
            return 0;
        } // if
    } // if

    if ((mat.peffect->m_flags & FX_TEX1) && mat.tex_map1)
    {
        LPDIRECT3DTEXTURE9 tex = TextureCache::GetTexture(mat.tex_map1).ptex_file->d3d_tex;
        if (!mat.peffect->SetTexture("tex1", tex))
        {
            LOG_ERROR << "Failed to set the texture tex1 for effect: " << mat.filename << ENDLOG;
            return 0;
        } // if
    } // if

    if ((mat.peffect->m_flags & FX_TEX2) && mat.tex_map2)
    {
        LPDIRECT3DTEXTURE9 tex = TextureCache::GetTexture(mat.tex_map2).ptex_file->d3d_tex;
        if (!mat.peffect->SetTexture("tex2", tex))
        {
            LOG_ERROR << "Failed to set the texture tex2 for effect: " << mat.filename << ENDLOG;
            return 0;
        } // if
    } // if

    return mat.peffect;
} // Apply


// -- EOF


// OLD code before we moed to HLSL
//
// Can be deleted soon..
/*
    // Set the D3D material
    device->SetMaterial(&mat.d3d_mat);

    // Keep track of the number of stages we use
    int channel = 0;

    // Work out what texture maps we have
    bool has_diffuse_map = (mat.tex_map0 != 0);
    bool has_tex_map1  = (mat.tex_map1 != 0);
    bool has_opacity_map = (mat.tex_map2 != 0);

    // Set antiailasing
    if (has_opacity_map)
    {
        device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
        device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);
    } // if
    else
    {
        device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);
        device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
    } // else

    // Set the texture filter mode
    if (mat.tex_map2 != 0 || mat.tex_map0 != 0 || mat.tex_map1 != 0)
    {
        device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
        device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
        device->SetSamplerState(0, D3DSAMP_ADDRESSU,  D3DTADDRESS_WRAP);
        device->SetSamplerState(0, D3DSAMP_ADDRESSV,  D3DTADDRESS_WRAP);
    } // if

    // No textures
    if (!has_diffuse_map && !has_opacity_map)
    {
        // Use diffuse colour
        device->SetTexture(channel, 0);
        device->SetTextureStageState(channel, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);
        device->SetTextureStageState(channel, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

        // Enable material colours
        device->SetRenderState(D3DRS_COLORVERTEX, true);
        device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE,  D3DMCS_MATERIAL);
        device->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
        device->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,  D3DMCS_MATERIAL);
        device->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);

        // Disable alpha blend
        device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        device->SetTextureStageState(channel, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

        channel++;
    } // if

    // Difuse texture only
    else if (has_diffuse_map && !has_opacity_map)
    {
        LPDIRECT3DTEXTURE9 pcolor_map   = TextureCache::GetTexture(mat.tex_map0).ptex_file->d3d_tex;
        if (pcolor_map)
        {
            // Set the texture
            device->SetTexture(channel, pcolor_map);

            // Modulate between the vertex colours and the texture colour
            device->SetTextureStageState(channel, D3DTSS_COLOROP,   D3DTOP_MODULATE);
            device->SetTextureStageState(channel, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
            device->SetTextureStageState(channel, D3DTSS_COLORARG2, D3DTA_TEXTURE);

            // Disable material colours
            device->SetRenderState(D3DRS_COLORVERTEX, true);
            device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE,  D3DMCS_COLOR1);
            device->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_COLOR1);
            device->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,  D3DMCS_COLOR1);
            device->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_COLOR1);

            // Disable alpha blend
            device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
            device->SetTextureStageState(channel, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
            device->SetTextureStageState(channel, D3DTSS_TEXCOORDINDEX, 0);

            channel++;
        } // if
        if (has_tex_map1)
        {
            LPDIRECT3DTEXTURE9 ptex_map1  = TextureCache::GetTexture(mat.tex_map1).ptex_file->d3d_tex;
            if (ptex_map1)
            {
                // Set the texture
                device->SetTexture(channel, ptex_map1);

                // Add the vertex colours and the texture colour
                device->SetTextureStageState(channel, D3DTSS_COLOROP,   D3DTOP_ADDSIGNED);
                device->SetTextureStageState(channel, D3DTSS_COLORARG1, D3DTA_CURRENT);
                device->SetTextureStageState(channel, D3DTSS_COLORARG2, D3DTA_TEXTURE);
                device->SetTextureStageState(channel, D3DTSS_TEXCOORDINDEX, 1);

                channel++;
            } // if
        } // if
    } // if

    // Both diffuse and opacity textures
    else if (has_diffuse_map && has_opacity_map)
    {
        LPDIRECT3DTEXTURE9 ptexture = TextureCache::GetTexture(mat.tex_map2).ptex_file->d3d_tex;
        if (ptexture)
        {
            // Set the texture
            device->SetTexture(channel, ptexture);

            // Modulate between the vertex colours and the texture colour
            device->SetTextureStageState(channel, D3DTSS_COLOROP,   D3DTOP_MODULATE);
            device->SetTextureStageState(channel, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
            device->SetTextureStageState(channel, D3DTSS_COLORARG2, D3DTA_TEXTURE);

            // Disable material colours
            device->SetRenderState(D3DRS_COLORVERTEX, true);
            device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE,  D3DMCS_COLOR1);
            device->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_COLOR1);
            device->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,  D3DMCS_COLOR1);
            device->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_COLOR1);

            // Enable alpha blend
            device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
            device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
            device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
            device->SetTextureStageState(channel, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
            device->SetTextureStageState(channel, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
            device->SetTextureStageState(channel, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
            device->SetTextureStageState(channel, D3DTSS_TEXCOORDINDEX, 0);

            channel++;
        } // if
    } // else if

    // Disable the next stage
    device->SetTextureStageState(channel, D3DTSS_COLOROP, D3DTOP_DISABLE);
    device->SetTextureStageState(channel, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
    device->SetTexture(channel, 0);


*/
