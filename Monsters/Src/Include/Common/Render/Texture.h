// ----------------------------------------------------------------------------
// File: Texture.h
// Desc: Texture class 
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __TEXTURE_H_
#define __TEXTURE_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"
#include "Maths/MathInc.h"
#include "Engine/EngineInc.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Texture;


// ----------------------------------------------------------------------------
// An array of textures
// ----------------------------------------------------------------------------
struct TextureArray
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  TextureArray();
  ~TextureArray();

  // --------------------------------------------------------------------------
  // Get the textures
  // --------------------------------------------------------------------------
  Texture  *GetDiffuse()  { return m_diffuseTex; }
  Texture  *GetAlpha()    { return m_alphaTex;   }
  Texture  *GetNormal()   { return m_normalTex;  }
  Texture  *GetTex0()     { return m_tex0;       }
  Texture  *GetTex1()     { return m_tex1;       }

  // --------------------------------------------------------------------------
  // Get the textures (const)
  // --------------------------------------------------------------------------
  const Texture  *GetDiffuse()  const { return m_diffuseTex; }
  const Texture  *GetAlpha()    const { return m_alphaTex;   }
  const Texture  *GetNormal()   const { return m_normalTex;  }
  const Texture  *GetTex0()     const { return m_tex0;       }
  const Texture  *GetTex1()     const { return m_tex1;       }

  // --------------------------------------------------------------------------
  // Set the textures
  // --------------------------------------------------------------------------
  void SetDiffuse(Texture *pTex);
  void SetAlpha(Texture *pTex);
  void SetNormal(Texture *pTex);
  void SetTex0(Texture *pTex);
  void SetTex1(Texture *pTex);

private:
  // --------------------------------------------------------------------------
  // The textures
  // --------------------------------------------------------------------------
  Texture  *m_diffuseTex;
  Texture  *m_alphaTex;
  Texture  *m_normalTex;
  Texture  *m_tex0;
  Texture  *m_tex1;
}; // struct TextureArray


// ----------------------------------------------------------------------------
// Name: Texture  (class)
// Desc: Class to manage a texture
// ----------------------------------------------------------------------------
class Texture : public RefCounted
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  Texture();
  virtual ~Texture();

  // --------------------------------------------------------------------------
  // Get the file handle
  // --------------------------------------------------------------------------
  const FileHandle &GetFileHandle() const { return m_handle; }

  // --------------------------------------------------------------------------
  // Load the texture
  // --------------------------------------------------------------------------
  bool Load(FileHandle handle);
  bool Save(FileHandle handle);

  // --------------------------------------------------------------------------
  // Get the d3d texture
  // --------------------------------------------------------------------------
  operator LPDIRECT3DTEXTURE9()             { return m_texture; }
  operator const LPDIRECT3DTEXTURE9() const { return m_texture; }
  LPDIRECT3DTEXTURE9 GetPtr()               { return m_texture; }
  const LPDIRECT3DTEXTURE9 GetPtr() const   { return m_texture; }

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  LPDIRECT3DTEXTURE9  m_texture;
  FileHandle          m_handle;

}; // Texture


// ----------------------------------------------------------------------------
// Name: BaseTextureFunctor (struct)
// Desc: Base class texture functor allowing a texture to be loaded
// ----------------------------------------------------------------------------
struct BaseTextureFunctor
{
  virtual Texture *operator()(FileHandle handle) const = 0;
}; // class BaseTextureFunctor


// ----------------------------------------------------------------------------
// Name: TextureFunctorTemplate  (struct)
// Desc: Templated scene texture functor that can create sceen textures of
//       a derived type (that is specified by the template argument).
// ----------------------------------------------------------------------------
template <class T>
struct TextureFunctorTemplate : public BaseTextureFunctor
{
  // --------------------------------------------------------------------------
  // Name: operator
  // Desc: Create a texture and load it from a file
  // Retn: Texture * - the created texture, or null if hte texture failed to 
  //       load
  // --------------------------------------------------------------------------
  virtual Texture *operator()(FileHandle handle) const 
  { 
    T *ptex = new T();
    if (!ptex->Load(handle))
      SafeDelete(ptex);

    return ptex;
  } // operator()

}; // struct TextureFunctorTemplate


// ----------------------------------------------------------------------------
// Typedef of a texture functor to create Texture instances
// ----------------------------------------------------------------------------
typedef TextureFunctorTemplate<Texture> TextureFunctor;


// ----------------------------------------------------------------------------
// Name: TextureLoader (class)
// Desc: Class to load textures
// ----------------------------------------------------------------------------
class TextureLoader
{
public:
  // --------------------------------------------------------------------------
  // Load the texture from disk
  // --------------------------------------------------------------------------
  static Texture *LoadTexture(FileHandle handle);
  static Texture *LoadTexture(FileHandle handle, const BaseTextureFunctor &type);
  
  // --------------------------------------------------------------------------
  // Release any textures with no external references
  // --------------------------------------------------------------------------
  static void GarbageCollect();

  // --------------------------------------------------------------------------
  // Get all textures
  // --------------------------------------------------------------------------
  static const Map<String, Texture *> &GetAllTextures();

private:
  // --------------------------------------------------------------------------
  // Private static members
  // --------------------------------------------------------------------------
  static Map<String, Texture *> s_texture_map;
  
}; // class TextureLoader


#endif // __TEXTURE_H_


// -- EOF

