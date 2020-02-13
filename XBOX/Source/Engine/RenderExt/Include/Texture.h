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
#include "libStandard.h"
#include "libMaths.h"
#include "libRenderCore.h"


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
  Texture  *GetTex0()     { return m_tex0;       }
  Texture  *GetTex1()     { return m_tex1;       }
  Texture  *GetTex2()     { return m_tex2;       }
  Texture  *GetTex3()     { return m_tex3;       }

  // --------------------------------------------------------------------------
  // Get the textures (const)
  // --------------------------------------------------------------------------
  const Texture  *GetTex0()     const { return m_tex0;       }
  const Texture  *GetTex1()     const { return m_tex1;       }
  const Texture  *GetTex2()     const { return m_tex2;       }
  const Texture  *GetTex3()     const { return m_tex3;       }

  // --------------------------------------------------------------------------
  // Set the textures
  // --------------------------------------------------------------------------
  void SetTex0(Texture *pTex);
  void SetTex1(Texture *pTex);
  void SetTex2(Texture *pTex);
  void SetTex3(Texture *pTex);

private:
  // --------------------------------------------------------------------------
  // The textures
  // --------------------------------------------------------------------------
  Texture  *m_tex0;
  Texture  *m_tex1;
  Texture  *m_tex2;
  Texture  *m_tex3;
}; // struct TextureArray


// ----------------------------------------------------------------------------
// Name: Texture  (class)
// Desc: Class to manage a texture
// ----------------------------------------------------------------------------
class Texture : public DeviceObject, public RefCounted, private Unique
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  Texture();
  Texture(DIRECT3DTEXTURE pTexture);
  virtual ~Texture();

  // --------------------------------------------------------------------------
  // Get the file handle
  // --------------------------------------------------------------------------
  const FileHandle &GetFileHandle() const { return m_handle; }

  // --------------------------------------------------------------------------
  // Load the texture
  // --------------------------------------------------------------------------
  virtual bool Load(FileHandle handle);

  // --------------------------------------------------------------------------
  // Save the texture
  // --------------------------------------------------------------------------
#if PC
  virtual bool Save(FileHandle handle);
#endif

  // --------------------------------------------------------------------------
  // Texture attribute (generic value that can be bound to the shader)
  // --------------------------------------------------------------------------
  const Vec4 &GetAttr() const     { return m_Attr; }
  void SetAttr(const Vec4 &attr)  { m_Attr = attr; }

  // --------------------------------------------------------------------------
  // Get the texture size
  // --------------------------------------------------------------------------
  bool GetSize(uint &width, uint &height) const;

  // --------------------------------------------------------------------------
  // Get the d3d texture
  // --------------------------------------------------------------------------
  virtual DIRECT3DTEXTURE GetPtr()               { return m_texture; }
  virtual const DIRECT3DTEXTURE GetPtr() const   { return m_texture; }

protected:
  // --------------------------------------------------------------------------
  // Manage device memory
  // --------------------------------------------------------------------------
  virtual bool AllocateDeviceMemory();
  virtual bool ReleaseDeviceMemory();

protected:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  DIRECT3DTEXTURE     m_texture;  // The D3D texture
  FileHandle          m_handle;   // File handle to the texture
  Vec4                m_Attr;     // Generic attribute value
  mutable float       m_Width;    // The texture width
  mutable float       m_Height;   // The texture height

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

