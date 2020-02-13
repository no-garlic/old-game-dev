// ----------------------------------------------------------------------------
// File: ShaderMaterial.h
// Desc: Material class that uses a vertex and pixel shader
// Auth: Michael Petrou
// (C) Copyright: 2007
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "ShaderMaterial.h"


// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
ShaderMaterial::ShaderMaterial()
: m_VertexDeclaration (NULL),
  m_VertexShader      (NULL),
  m_PixelShader       (NULL)
{
  REF_COUNT_CTOR(ShaderMaterial);
}


// --------------------------------------------------------------------------
// Destructor
// --------------------------------------------------------------------------
ShaderMaterial::~ShaderMaterial()
{
  REF_COUNT_DTOR(ShaderMaterial);

#if PC
  SafeRelease(m_VertexDeclaration);
  SafeRelease(m_VertexShader);
  SafeRelease(m_PixelShader);
#else
  // TODO
  //Device->DeletePixelShader(m_PixelShader);
  //Device->DeleteVertexShader(m_VertexShader);
#endif
}


// --------------------------------------------------------------------------
// Load the material
// --------------------------------------------------------------------------
bool ShaderMaterial::Load()
{
  if (!CreateVertexDeclaration())
    return false;
  if (!CreateVertexShader())
    return false;
  if (!CreatePixelShader())
    return false;
  return true;
}


// --------------------------------------------------------------------------
// Bind the material
// --------------------------------------------------------------------------
uint ShaderMaterial::Begin() const
{
#if PC
  D3DCheck(Device->SetVertexDeclaration(m_VertexDeclaration));
#endif
  D3DCheck(Device->SetVertexShader(m_VertexShader));
  D3DCheck(Device->SetPixelShader(m_PixelShader));
  return 1;
}


// --------------------------------------------------------------------------
// Bind the material
// --------------------------------------------------------------------------
void ShaderMaterial::BeginPass(uint pass) const
{
}


// --------------------------------------------------------------------------
// Bind the material
// --------------------------------------------------------------------------
void ShaderMaterial::EndPass() const
{
}


// --------------------------------------------------------------------------
// Bind the material
// --------------------------------------------------------------------------
void ShaderMaterial::End() const
{
#if PC
  D3DCheck(Device->SetVertexDeclaration(NULL)); // Causes a D3D warning 
#endif
  D3DCheck(Device->SetVertexShader(NULL));
  D3DCheck(Device->SetPixelShader(NULL));
}


// --------------------------------------------------------------------------
// Allocate device memory
// --------------------------------------------------------------------------
bool ShaderMaterial::AllocateDeviceMemory()
{
  // TODO

  //LoadVertexShader(m_VertexShaderHandle);
  //LoadPixelShader(m_PixelShaderHandle);

  return false;
}


// --------------------------------------------------------------------------
// Release device memory
// --------------------------------------------------------------------------
bool ShaderMaterial::ReleaseDeviceMemory()
{
  // TODO

  //SafeRelease(m_VertexShader);
  //SafeRelease(m_PixelShader);

  return false;
}


// --------------------------------------------------------------------------
// Create the vertex shader
// --------------------------------------------------------------------------
bool ShaderMaterial::LoadVertexShader(FileHandle handle)
{
  m_VertexShaderHandle = handle;

  // Open the shader file
  FileStream inStream;
  inStream.open(handle.GetAbsoluteFilename().c_str(), std::ios_base::in);
  if (!inStream.is_open())
  {
    LOG_ERROR << "Failed to open the file: " << handle.GetAbsoluteFilename() << ENDLOG;
    return false;
  }

  // Parse and preprocess the shader file for the compiled platform 
  StringStream outStream;  
  Parser parser(IS_PC);
  if (!parser.Process(inStream, outStream))
  {
    LOG_ERROR << "Failed to preprocess the file: " << handle.GetAbsoluteFilename() << ENDLOG;
    return false;
  }

  // Get the string buffer from the output stream
  String outString = outStream.str();
  const char *pStr = outString.c_str();
  uint len = outString.length();

#if FINAL_RELEASE
  ulong shaderFlags = 0;
#else
#if XBOX
  ulong shaderFlags = SASM_DEBUG | SASM_SKIPPREPROCESSOR;
#else
  ulong shaderFlags = D3DXSHADER_DEBUG;
#endif
#endif

#if PC
  // Compile the shader from the given file
  LPD3DXBUFFER function;
  LPD3DXBUFFER errors;
  if (FAILED(D3DXAssembleShader(pStr, len, NULL, NULL, shaderFlags, &function, &errors)))
  {
    char *error_message = (char *) errors->GetBufferPointer();
    LOG_ERROR << "Failed to compile the vertex shader: " << handle.GetAbsoluteFilename() << " - " << error_message << ENDLOG;
    SafeRelease(errors);
    m_VertexShader = NULL;
    return false;
  } // if

  // Now create the vertex shader
  if (FAILED(Device->CreateVertexShader((ulong *) function->GetBufferPointer(), &m_VertexShader)))
  {
    LOG_ERROR << "Failed to create the vertex shader: " << handle.GetAbsoluteFilename() << ENDLOG;
    SafeRelease(function);
    SafeRelease(m_VertexShader);
    m_VertexShader = NULL;
    return false;
  } // if

  SafeRelease(function);

  return true;
#else
  LPXGBUFFER errors;
  LPXGBUFFER function; 
  if (FAILED(XGAssembleShader(handle.GetFilename().c_str(), pStr, len, shaderFlags, NULL, &function, &errors, NULL, NULL, NULL, NULL)))
  {
    char *error_message = (char *) errors->GetBufferPointer();
    LOG_ERROR << "Failed to compile the vertex shader: " << handle.GetAbsoluteFilename() << " - " << error_message << ENDLOG;
    SafeRelease(errors);
    m_VertexShader = NULL;
    return false;
  }

  // Now create the vertex shader
  if (FAILED(Device->CreateVertexShader(m_VertexDeclaration, (ulong *) function->GetBufferPointer(), &m_VertexShader, 0)))
  {
    LOG_ERROR << "Failed to create the vertex shader: " << handle.GetAbsoluteFilename() << ENDLOG;
    SafeRelease(function);
    //TODO: SafeRelease(m_VertexShader);
    m_VertexShader = NULL;
    return false;
  } // if

  return true;
#endif
}


// --------------------------------------------------------------------------
// Create the pixel shader
// --------------------------------------------------------------------------
bool ShaderMaterial::LoadPixelShader(FileHandle handle)
{
  m_PixelShaderHandle = handle;

  // Open the shader file
  FileStream inStream;
  inStream.open(handle.GetAbsoluteFilename().c_str(), std::ios_base::in);
  if (!inStream.is_open())
  {
    LOG_ERROR << "Failed to open the file: " << handle.GetAbsoluteFilename() << ENDLOG;
    return false;
  }

  // Parse and preprocess the shader file for the compiled platform 
  StringStream outStream;  
  Parser parser(IS_PC);
  if (!parser.Process(inStream, outStream))
  {
    LOG_ERROR << "Failed to preprocess the file: " << handle.GetAbsoluteFilename() << ENDLOG;
    return false;
  }

  // Get the string buffer from the output stream
  String outString = outStream.str();
  const char *pStr = outString.c_str();
  uint len = outString.length();

#if FINAL_RELEASE
  ulong shaderFlags = 0;
#else
#if XBOX
  ulong shaderFlags = SASM_DEBUG | SASM_SKIPPREPROCESSOR;
#else
  ulong shaderFlags = D3DXSHADER_DEBUG;
#endif
#endif

#if PC
  // Compile the shader from the given file
  LPD3DXBUFFER function;
  LPD3DXBUFFER errors;
  if (FAILED(D3DXAssembleShader(pStr, len, NULL, NULL, shaderFlags, &function, &errors)))
  {
    char *error_message = (char *) errors->GetBufferPointer();
    LOG_ERROR << "Failed to compile the pixel shader: " << handle.GetAbsoluteFilename() << " - " << error_message << ENDLOG;
    SafeRelease(errors);
    m_PixelShader = NULL;
    return false;
  } // if

  // Now create the pixel shader
  if (FAILED(Device->CreatePixelShader((ulong *) function->GetBufferPointer(), &m_PixelShader)))
  {
    LOG_ERROR << "Failed to create the pixel shader: " << handle.GetAbsoluteFilename() << ENDLOG;
    SafeRelease(function);
    SafeRelease(m_PixelShader);
    m_PixelShader = NULL;
    return false;
  } // if

  SafeRelease(function);

  return true;
#else
  LPXGBUFFER errors;
  LPXGBUFFER function; 
  if (FAILED(XGAssembleShader(handle.GetFilename().c_str(), pStr, len, shaderFlags, NULL, &function, &errors, NULL, NULL, NULL, NULL)))
  {
    char *error_message = (char *) errors->GetBufferPointer();
    LOG_ERROR << "Failed to compile the pixel shader: " << handle.GetAbsoluteFilename() << " - " << error_message << ENDLOG;
    SafeRelease(errors);
    m_PixelShader = NULL;
    return false;
  }

  // Now create the pixel shader
  if (FAILED(Device->CreatePixelShader((D3DPIXELSHADERDEF*) function->GetBufferPointer(), &m_PixelShader)))
  {
    LOG_ERROR << "Failed to create the vertex shader: " << handle.GetAbsoluteFilename() << ENDLOG;
    SafeRelease(function);
    // TODO: SafeRelease(m_PixelShader);
    m_PixelShader = NULL;
    return false;
  } // if
  return true;
#endif
}


void ShaderMaterial::SetVSFloat(uint reg, float data) const
{
#if XBOX
  D3DCheck(Device->SetVertexShaderConstant(reg, &(Vec4(data, data, data, data).x), 1));
#else
  D3DCheck(Device->SetVertexShaderConstantF(reg, &(Vec4(data, data, data, data).x), 1));
#endif
}


void ShaderMaterial::SetVSVec3(uint reg, const Vec3 &data) const
{
#if XBOX
  D3DCheck(Device->SetVertexShaderConstant(reg, &(Vec4(data, 1.0f).x), 1));
#else
  D3DCheck(Device->SetVertexShaderConstantF(reg, &(Vec4(data, 1.0f).x), 1));
#endif
}


void ShaderMaterial::SetVSVec4(uint reg, const Vec4 &data) const
{
#if XBOX
  D3DCheck(Device->SetVertexShaderConstant(reg, &(data.x), 1));
#else
  D3DCheck(Device->SetVertexShaderConstantF(reg, &(data.x), 1));
#endif
}


void ShaderMaterial::SetVSMatrix(uint reg, const Matrix &data) const
{
#if XBOX
  D3DCheck(Device->SetVertexShaderConstant(reg, &(data._11), 4));
#else
  D3DCheck(Device->SetVertexShaderConstantF(reg, &(data._11), 4));
#endif
}


void ShaderMaterial::SetPSFloat(uint reg, float data) const
{
#if XBOX
  D3DCheck(Device->SetPixelShaderConstant(reg, &(Vec4(data, data, data, data).x), 1));
#else
  D3DCheck(Device->SetPixelShaderConstantF(reg, &(Vec4(data, data, data, data).x), 1));
#endif
}


void ShaderMaterial::SetPSVec3(uint reg, const Vec3 &data) const
{
#if XBOX
  D3DCheck(Device->SetPixelShaderConstant(reg, &(Vec4(data, 1.0f).x), 1));
#else
  D3DCheck(Device->SetPixelShaderConstantF(reg, &(Vec4(data, 1.0f).x), 1));
#endif
}


void ShaderMaterial::SetPSVec4(uint reg, const Vec4 &data) const
{
#if XBOX
  D3DCheck(Device->SetPixelShaderConstant(reg, &(data.x), 1));
#else
  D3DCheck(Device->SetPixelShaderConstantF(reg, &(data.x), 1));
#endif
}


void ShaderMaterial::SetPSMatrix(uint reg, const Matrix &data) const
{
#if XBOX
  D3DCheck(Device->SetPixelShaderConstant(reg, &(data._11), 4));
#else
  D3DCheck(Device->SetPixelShaderConstantF(reg, &(data._11), 4));
#endif
}

// -- EOF

