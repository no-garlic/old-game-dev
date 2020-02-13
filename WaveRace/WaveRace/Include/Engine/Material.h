// ----------------------------------------------------------------------------
// File: Material.h
// Desc: Provides resource management for materials and textures
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _MATERIAL_H
#define _MATERIAL_H


// ----------------------------------------------------------------------------
// Includes for the material and texture classes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include "Engine/Effect.h"
#include "Math/Types.h"
#include "Math/Color.h"
#include "Math/Matrix.h"
#include <map>


// ----------------------------------------------------------------------------
// Name: MaterialCache  (class)
// Desc: Provides resource management for all materials
// ----------------------------------------------------------------------------
class MaterialCache : private Utility::Unique
{
public:
    // ------------------------------------------------------------------------
    // Name: Record (struct)
    // Desc: Holds a record containing the material attributes
    // ------------------------------------------------------------------------
    struct Record
    {
        Effect      *peffect;   // Shader (optional)
        std::string filename;   // Shader filename
        uint        tex_map0;   // The colour map
        uint        tex_map1;   // The detail map
        uint        tex_map2;   // The opacity map
        int         flags;      // FX Flags
        bool        isopaque;   // Opaque flag
    }; // struct Record


    // ------------------------------------------------------------------------
    // Get a material from the cache by id
    // ------------------------------------------------------------------------
    static MaterialCache::Record GetMaterial(uint material_id);


    // ------------------------------------------------------------------------
    // Name: MapType (enum)
    // Desc: The material map types
    // ------------------------------------------------------------------------
    enum MapType
    {
        unknown     = 0,
        tex_map0    = 1,    // The colour map 1
        tex_map1    = 2,    // The colour map 2
        tex_map2    = 3,    // The opacity map
    }; // enum MapType


    // ------------------------------------------------------------------------
    // Creates a material
    // ------------------------------------------------------------------------
    static uint CreateMaterial(uint tex_map0, uint tex_map1, uint tex_map2, 
        const std::string &effect_filename, int flags, bool isopaque);

    
    // ------------------------------------------------------------------------
    // Public static functions
    // ------------------------------------------------------------------------
    static Effect  *Apply(uint material_id, const Matrix &world_matrix, LPDIRECT3DDEVICE9 device);
    static uint     GetCurrentMaterial();
    static bool     IsOpaque(uint id);
    static void     Clear();


    // ------------------------------------------------------------------------
    // Create the default material
    // ------------------------------------------------------------------------
    static bool Create(LPDIRECT3DDEVICE9 device);
    static void Release();


private:
    // ------------------------------------------------------------------------
    // Private members of this class
    // ------------------------------------------------------------------------
    static LPDIRECT3DDEVICE9                     s_device;          // Device
    static std::map<uint, MaterialCache::Record> s_material_ids;    // All material id's
    static uint                                  s_counter;         // The material counter
    static uint                                  s_curr_mat;        // The current applied material
    static bool                                  s_default_mat;     // The default material
}; // class MaterialCache


// ----------------------------------------------------------------------------
// Name: TextureCache  (class)
// Desc: Provides resource management for all textures
// ----------------------------------------------------------------------------
class TextureCache : private Utility::Unique
{
private:
    // ------------------------------------------------------------------------
    // Name: TexFile (struct)
    // Desc: structure for holding a texture and it's filename
    // ------------------------------------------------------------------------
    struct TexFile
    {
        LPDIRECT3DTEXTURE9  d3d_tex;    // The texture
        std::string         filename;   // The filename
    }; // struct TexFile

    
    // ------------------------------------------------------------------------
    // Name: Record (struct)
    // Desc: structure for holding a texture file and the uv data for the 
    //       texture
    // ------------------------------------------------------------------------
    struct Record
    {
        TexFile *ptex_file;             // The texture
    }; // struct Record


public:
    // ------------------------------------------------------------------------
    // Public static funtions
    // ------------------------------------------------------------------------
    static uint                 CreateTexture(const char *filename, LPDIRECT3DDEVICE9 device);
    static TextureCache::Record GetTexture(uint texture_id);
    static void                 Clear();


private:
    // ------------------------------------------------------------------------
    // Allow the material cache to access the private members
    // ------------------------------------------------------------------------
    friend class MaterialCache;


    // ------------------------------------------------------------------------
    // Private members of this class
    // ------------------------------------------------------------------------
    static std::map<uint, TextureCache::Record>             s_texture_ids;      // All texture id's
    static std::map<std::string, TextureCache::TexFile *>   s_texture_files;    // All texture files
    static uint                                             s_counter;          // The texture counter
}; // class TextureCache


#endif //_MATERIAL_H

// -- EOF

