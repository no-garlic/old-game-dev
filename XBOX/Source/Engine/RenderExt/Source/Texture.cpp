// ----------------------------------------------------------------------------
// File: Texture.cpp
// Desc: Texture class
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Texture.h"


// ----------------------------------------------------------------------------
// Static initialisation
// ----------------------------------------------------------------------------
Map<String, Texture *> TextureLoader::s_texture_map;


// ----------------------------------------------------------------------------
// Name: Texture::Texture
// Desc: Constructor
// ----------------------------------------------------------------------------
Texture::Texture()
: m_texture   (NULL),
  m_Width     (0.0f),
  m_Height    (0.0f)
{
  REF_COUNT_CTOR(Texture);

  // Install the garbage collector task at exit
  static bool gcInstalled = false;
  if (!gcInstalled)
  {
    atexit(&TextureLoader::GarbageCollect);
    gcInstalled = true;
  } // if
} // Texture


// ----------------------------------------------------------------------------
// Name: Texture::Texture
// Desc: Constructor
// ----------------------------------------------------------------------------
Texture::Texture(DIRECT3DTEXTURE pTexture)
: m_Width (0.0f),
  m_Height(0.0f)
{
  REF_COUNT_CTOR(Texture);

  m_texture = pTexture;
  //m_texture->AddRef();
}


// ----------------------------------------------------------------------------
// Name: Texture::~Texture
// Desc: Destructor
// ----------------------------------------------------------------------------
Texture::~Texture()
{
  REF_COUNT_DTOR(Texture);
  SafeRelease(m_texture);
} // ~Texture


// ----------------------------------------------------------------------------
// Name: Texture::AllocateDeviceMemory
// Desc: Called when the device has been reset
// ----------------------------------------------------------------------------
bool Texture::AllocateDeviceMemory()
{
  if (m_texture)
    return false;

  return Load(m_handle);
} // AllocateDeviceMemory


// ----------------------------------------------------------------------------
// Name: Texture::ReleaseDeviceMemory
// Desc: Called before the device is reset
// ----------------------------------------------------------------------------
bool Texture::ReleaseDeviceMemory()
{
  if (m_texture)
    SafeRelease(m_texture);

  m_texture = NULL;

  return true;
} // ReleaseDeviceMemory


// ----------------------------------------------------------------------------
// Name: Texture::Load
// Desc: Load the texture
// Parm: FileHandle handle - the file handle
// Retn: bool              - true if loaded
// ----------------------------------------------------------------------------
bool Texture::Load(FileHandle handle)
{
  m_handle = handle;

  uint num_mip_levels = D3DX_DEFAULT;

  HRESULT loadResult = D3DXCreateTextureFromFile(Device, handle.GetAbsoluteFilename().c_str(), &m_texture);
  if (FAILED(loadResult))
  {
    D3DCheck(loadResult);
    LOG_ERROR << "Failed to load the texture: " << handle.GetAbsoluteFilename() << ENDLOG;
    m_texture = NULL;
    return false;
  } // if  

  LOG_INFO << "Loaded the texture: " << handle.GetAbsoluteFilename() << ENDLOG;
  return true;
} // Load


#if PC
// ----------------------------------------------------------------------------
// Name: Texture::Save
// Desc: Save the texture
// Parm: FileHandle handle - the file handle
// Retn: bool              - true if saved
// ----------------------------------------------------------------------------
bool Texture::Save(FileHandle handle)
{
  // Get the top level surface
  DIRECT3DSURFACE pSurface;
  if (FAILED(m_texture->GetSurfaceLevel(0, &pSurface)))
  {
    LOG_ERROR << "Failed to save the texture: " << handle.GetAbsoluteFilename() << ENDLOG;
    return false;
  } // if  

  // Get the texture file extension
  String filename, extension;
  SplitFilename(handle.GetFilename(), filename, extension);
  ToUpper(extension);
  
  // Find the file format
  D3DXIMAGE_FILEFORMAT fileType = (D3DXIMAGE_FILEFORMAT) -1;
  if (extension == "BMP")
    fileType = D3DXIFF_BMP;
  else if (extension == "JPG")
    fileType = D3DXIFF_JPG;
  else if (extension == "TGA")
    fileType = D3DXIFF_TGA;
  else if (extension == "PNG")
    fileType = D3DXIFF_PNG;
  else if (extension == "DDS")
    fileType = D3DXIFF_DDS;
  else if (extension == "PPM")
    fileType = D3DXIFF_PPM;
  else if (extension == "DIB")
    fileType = D3DXIFF_DIB;
  else if (extension == "HDR")
    fileType = D3DXIFF_HDR;
  else if (extension == "PFM")
    fileType = D3DXIFF_PFM;
  else
  {
    LOG_ERROR << "Failed to save the texture: " << handle.GetAbsoluteFilename() << ENDLOG;
    return false;
  } // else

  // Save the surface to the file
  if (FAILED(D3DXSaveSurfaceToFile(handle.GetAbsoluteFilename().c_str(), fileType, pSurface, NULL, NULL)))
  {
    LOG_ERROR << "Failed to save the texture: " << handle.GetAbsoluteFilename() << ENDLOG;
    return false;
  } // if  

  // Saved
  return true;
} // Save
#endif



// ----------------------------------------------------------------------------
// Get the texture size
// ----------------------------------------------------------------------------
bool Texture::GetSize(uint &width, uint &height) const
{
  if (m_Width != 0.0f)
  {
    width  = m_Width;
    height = m_Height;
    return true;
  }

  if (!m_texture)
    return false;

  DIRECT3DSURFACE pSurface = NULL;
  if (FAILED(m_texture->GetSurfaceLevel(0, &pSurface)))
    return false;

  if (pSurface)
  {
    D3DSURFACE_DESC surfaceDesc;
    if (FAILED(pSurface->GetDesc(&surfaceDesc)))
      return false;

    m_Width  = surfaceDesc.Width;
    m_Height = surfaceDesc.Height;
    width    = m_Width;
    height   = m_Height;

    SafeRelease(pSurface);
    return true;
  }

  return false;
}


// ----------------------------------------------------------------------------
// Name: TextureLoader::LoadTexture
// Desc: Load a texture or retrieve it from the cache
// Parm: FileHandle handle - the file handle
// Retn: Texture *         - the texture
// ----------------------------------------------------------------------------
Texture *TextureLoader::LoadTexture(FileHandle handle)
{
  return LoadTexture(handle, TextureFunctor());
} // LoadTexture


// ----------------------------------------------------------------------------
// Name: TextureLoader::LoadTexture
// Desc: Load a texture or get it from the cache
// Parm: FileHandle handle                - the file handle
// Parm: const BaseTextureFunctor &type   - the creation functor
// Retn: Texture *                        - the texture
// ----------------------------------------------------------------------------
Texture *TextureLoader::LoadTexture(FileHandle handle, const BaseTextureFunctor &type)
{
  Map<String, Texture *>::iterator iter = s_texture_map.find(handle.GetAbsoluteFilename());
  if (iter != s_texture_map.end())
    return iter->second;

  Texture *ptex = type(handle);
  if (!ptex)
    return NULL;

  s_texture_map.insert(MakePair(handle.GetAbsoluteFilename(), ptex));
  SafeRef(ptex);

  return ptex;
} // LoadTexture


// ----------------------------------------------------------------------------
// Name: TextureLoader::GarbageCollect
// Desc: Release any textures with no external references
// ----------------------------------------------------------------------------
void TextureLoader::GarbageCollect()
{
  Map<String, Texture *>::iterator iter(s_texture_map.begin()), end(s_texture_map.end());
  while (iter != end)
  {
    Texture *ptex = iter->second;
    if (ptex->GetRefCount() == 1)
    {
      iter = s_texture_map.erase(iter);
      SafeUnRef(ptex);
    } // if
    else
    {
      ++iter;
    } // else
  } // if
} // GarbageCollect


// ----------------------------------------------------------------------------
// Name: TextureLoader::GetAllTextures
// Desc: Get all textures
// Retn: const Map<String, Texture *> & - the texture array
// ----------------------------------------------------------------------------
const Map<String, Texture *> &TextureLoader::GetAllTextures()
{
  return s_texture_map;
} // GetAllTextures


// ----------------------------------------------------------------------------
// Name: TextureArray::TextureArray
// Desc: Constructor
// ----------------------------------------------------------------------------
TextureArray::TextureArray()
: m_tex0          (NULL),
  m_tex1          (NULL),
  m_tex2          (NULL),
  m_tex3          (NULL)
{
} // TextureArray


// ----------------------------------------------------------------------------
// Name: TextureArray::~TextureArray
// Desc: Destructor
// ----------------------------------------------------------------------------
TextureArray::~TextureArray()
{
  SafeUnRef(m_tex0);
  SafeUnRef(m_tex1);
  SafeUnRef(m_tex2);
  SafeUnRef(m_tex3);
} // ~TextureArray


// ----------------------------------------------------------------------------
// Name: TextureArray::SetTex0
// Desc: Set the tex0 texture
// Parm: Texture *pTex - the texture
// ----------------------------------------------------------------------------
void TextureArray::SetTex0(Texture *pTex)
{
  SafeUnRef(m_tex0);
  m_tex0 = pTex;      
  SafeRef(m_tex0);
} // SetTex0


// ----------------------------------------------------------------------------
// Name: TextureArray::SetTex1
// Desc: Set the tex1 texture
// Parm: Texture *pTex - the texture
// ----------------------------------------------------------------------------
void TextureArray::SetTex1(Texture *pTex)
{
  SafeUnRef(m_tex1);
  m_tex1 = pTex;      
  SafeRef(m_tex1);
} // SetTex1


// ----------------------------------------------------------------------------
// Name: TextureArray::SetTex2
// Desc: Set the tex2 texture
// Parm: Texture *pTex - the texture
// ----------------------------------------------------------------------------
void TextureArray::SetTex2(Texture *pTex)
{
  SafeUnRef(m_tex2);
  m_tex2 = pTex;      
  SafeRef(m_tex2);
} // SetTex2


// ----------------------------------------------------------------------------
// Name: TextureArray::SetTex3
// Desc: Set the tex3 texture
// Parm: Texture *pTex - the texture
// ----------------------------------------------------------------------------
void TextureArray::SetTex3(Texture *pTex)
{
  SafeUnRef(m_tex3);
  m_tex3 = pTex;      
  SafeRef(m_tex3);
} // SetTex3


// -- EOF

