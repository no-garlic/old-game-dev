// ----------------------------------------------------------------------------
// File: EffectMaterial.h
// Desc: Material class that uses a vertex and pixel shader
// Auth: Michael Petrou
// (C) Copyright: 2007
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "EffectMaterial.h"


// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
EffectMaterial::EffectMaterial()
: m_VertexDeclaration (NULL),
  m_Effect            (NULL)
{
  REF_COUNT_CTOR(EffectMaterial);
}


// --------------------------------------------------------------------------
// Destructor
// --------------------------------------------------------------------------
EffectMaterial::~EffectMaterial()
{
  REF_COUNT_DTOR(EffectMaterial);

  SafeRelease(m_VertexDeclaration);
  SafeRelease(m_Effect);
}


// --------------------------------------------------------------------------
// Load the material
// --------------------------------------------------------------------------
bool EffectMaterial::Load()
{
  if (!CreateVertexDeclaration())
    return false;
  if (!CreateEffect())
    return false;
  return true;
}


// --------------------------------------------------------------------------
// Bind the material
// --------------------------------------------------------------------------
uint EffectMaterial::Begin() const
{
#if PC
  D3DCheck(Device->SetVertexDeclaration(m_VertexDeclaration));
#endif

  uint passes;
  ulong flags = 0;

  D3DCheck(m_Effect->Begin(&passes, flags));

  return passes;
}


// --------------------------------------------------------------------------
// Bind the material
// --------------------------------------------------------------------------
void EffectMaterial::BeginPass(uint pass) const
{
  D3DCheck(m_Effect->BeginPass(pass));
}


// --------------------------------------------------------------------------
// Commit the changes of the effect (must be called at the end of prepare)
// --------------------------------------------------------------------------
void EffectMaterial::CommitChanges() const
{
  D3DCheck(m_Effect->CommitChanges());
}


// --------------------------------------------------------------------------
// Bind the material
// --------------------------------------------------------------------------
void EffectMaterial::EndPass() const
{
  D3DCheck(m_Effect->EndPass());
}


// --------------------------------------------------------------------------
// Bind the material
// --------------------------------------------------------------------------
void EffectMaterial::End() const
{
#if PC
  D3DCheck(Device->SetVertexDeclaration(NULL)); // Causes a D3D warning 
#endif
  D3DCheck(m_Effect->End());
}


// --------------------------------------------------------------------------
// Allocate device memory
// --------------------------------------------------------------------------
bool EffectMaterial::AllocateDeviceMemory()
{
  if (m_Effect)
    return false;

  return LoadEffect(m_EffectHandle);
}


// --------------------------------------------------------------------------
// Release device memory
// --------------------------------------------------------------------------
bool EffectMaterial::ReleaseDeviceMemory()
{
  if (m_Effect)
    SafeRelease(m_Effect);

  m_Effect = NULL;
  return true;
}


// --------------------------------------------------------------------------
// Create the vertex shader
// --------------------------------------------------------------------------
bool EffectMaterial::LoadEffect(FileHandle handle)
{
  m_EffectHandle = handle;

#ifdef _DEBUG
  ulong flags = D3DXSHADER_DEBUG;
#else
  ulong flags = 0;
#endif

  LPD3DXBUFFER errors;
  if (FAILED(D3DXCreateEffectFromFile(Device, handle.GetAbsoluteFilename().c_str(),
    NULL, NULL, flags, NULL, &m_Effect, &errors)))
  {
    LOG_ERROR << "Failed to create the effect: " << handle << ENDLOG;
    if (errors)
    {
      LOG_ERROR << (const char *) errors->GetBufferPointer() << ENDLOG;
      SafeRelease(errors);
    } // if

    return false;
  } // if

  LOG_INFO << "Loaded the material: " << handle << ENDLOG;
  return true;
}


// -- EOF

