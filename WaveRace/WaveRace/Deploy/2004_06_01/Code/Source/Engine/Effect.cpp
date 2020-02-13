// ----------------------------------------------------------------------------
// File: Effect.cpp
// Desc: Implementaion of the Effect rendering strategy
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Engine/Effect.h"
#include "Common/Logging.h"


// ----------------------------------------------------------------------------
// Name: Effect::Effect
// Desc: Constructor
// ----------------------------------------------------------------------------
Effect::Effect()
{
    m_device    = 0;
    m_effect    = 0;
    m_flags     = 0;
} // Effect


// ----------------------------------------------------------------------------
// Name: Effect::~Effect
// Desc: Destructor
// ----------------------------------------------------------------------------
Effect::~Effect()
{
    Release();
} // ~Effect


// ----------------------------------------------------------------------------
// Name: Effect::Create
// Desc: Create the effect
// Parm: LPDIRECT3DDEVICE9 device - the device
// Parm: const char *filename     - the effect filename
// Parm: int flags                - the creation flags
// Retn: bool                     - true if loaded and compiled ok
// ----------------------------------------------------------------------------
bool Effect::Create(LPDIRECT3DDEVICE9 device, const char *filename, int flags)
{
    Release();

    m_device = device;
    m_flags  = flags;

    LPD3DXBUFFER errors = 0;
    HRESULT hr;
    hr = D3DXCreateEffectFromFile(
            m_device,   // device
            filename,   // file
            0,          // defines
            0,          // includes
            (flags & FX_DEBUG) ? D3DXSHADER_DEBUG : 0, // flags
            0,          // pool
            &m_effect,  // effect
            &errors);   // error buffer

    if (FAILED(hr))
    {
        LOG_ERROR << "Failed to create the effect: " << 
            (errors ? (const char *) errors->GetBufferPointer() : "<no errors>") << ENDLOG;

        Memory::SafeRelease(errors);
        return false;
    } // if

    return true;
} // Create


// ----------------------------------------------------------------------------
// Name: Effect::Release
// Desc: Release the effect
// ----------------------------------------------------------------------------
void Effect::Release()
{
    if (!m_device)
        return;

    Memory::SafeRelease(m_effect);
    m_device = 0;
} // Release


// ----------------------------------------------------------------------------
// Name: Effect::Begin
// Desc: Begin rendering with the effect
// Parm: uint &num_passes           - the number of passes required to render 
//       the chosen technique
// Parm: bool discard_state         - shall we discard state when we are 
//       finished
// Parm: bool discard_shader_state  - shall we discard the shader state when 
//       finished
// Retn: bool                       - true if the effect is ready to be used
// ----------------------------------------------------------------------------
bool Effect::Begin(uint &num_passes, bool discard_state, bool discard_shader_state)
{
    if (!m_effect)
        return false;

    uint flags = 0;
    if (discard_state)
        flags |= D3DXFX_DONOTSAVESTATE;
    if (discard_shader_state)
        flags |= D3DXFX_DONOTSAVESHADERSTATE;

    return (m_effect->Begin(&num_passes, flags) == D3D_OK);
} // Begin



// ----------------------------------------------------------------------------
// Name: Effect::Pass
// Desc: Called to configure the effect for the render pass
// Parm: uint pass - the pass
// Retn: bool      - true if the pass was set correctly
// ----------------------------------------------------------------------------
bool Effect::Pass(uint pass)
{
    if (!m_effect)
        return false;

    return (m_effect->Pass(pass) == D3D_OK);
} // Pass



// ----------------------------------------------------------------------------
// Name: Effect::End
// Desc: End rendering with the effect
// Retn: bool - true if the effect was closed
// ----------------------------------------------------------------------------
bool Effect::End()
{
    if (!m_effect)
        return false;

    return (m_effect->End() == D3D_OK);
} // End


// ----------------------------------------------------------------------------
// Name: Effect::GetBool
// Desc: Get a bool value from the effect
// Parm: Effect::EffectHandle parameter - the effect handle
// Parm: bool &value                    - the value
// Retn: bool                           - true if the value was read
// ----------------------------------------------------------------------------
bool Effect::GetBool(Effect::EffectHandle parameter, bool &value)
{
    if (!m_effect)
        return false;

    BOOL b;
    if (m_effect->GetBool(parameter, &b) == D3D_OK)
    {
        value = (b == TRUE);
        return true;
    } // if

    return false;
} // GetBool


// ----------------------------------------------------------------------------
// Name: Effect::GetBoolArray
// Desc: Read an array of bools from the effect
// Parm: Effect::EffectHandle parameter - the effect handle
// Parm: bool *array                    - the array of bools to read into 
// Parm: uint count                     - the number of bools to read
// Retn: bool                           - reue if the array was read
// ----------------------------------------------------------------------------
bool Effect::GetBoolArray(Effect::EffectHandle parameter, bool *array, uint count)
{
    if (!m_effect)
        return false;

    BOOL b[256];
    if (m_effect->GetBoolArray(parameter, (BOOL *) &b, count) == D3D_OK)
    {
        for (uint i = 0; i < count; i++)
            array[i] = (b[i] == TRUE);
        
        return true;
    } // if

    return false;
} // GetBoolArray


// TODO: More commenting of this file
//

bool Effect::GetFloat(Effect::EffectHandle parameter, float &value)
{
    if (!m_effect)
        return false;


    return (m_effect->GetFloat(parameter, &value) == D3D_OK);
} // GetFloat



bool Effect::GetFloatArray(Effect::EffectHandle parameter, float *array, uint count)
{
    if (!m_effect)
        return false;


    return (m_effect->GetFloatArray(parameter, array, count) == D3D_OK);
} // GetFloatArray



bool Effect::GetInt(Effect::EffectHandle parameter, int &value)
{
    if (!m_effect)
        return false;


    return (m_effect->GetInt(parameter, &value) == D3D_OK);
} // GetInt



bool Effect::GetIntArray(Effect::EffectHandle parameter, int *array, uint count)
{
    if (!m_effect)
        return false;


    return (m_effect->GetIntArray(parameter, array, count) == D3D_OK);
} // GetIntArray



bool Effect::GetVector(Effect::EffectHandle parameter, Vec4 &value)
{
    if (!m_effect)
        return false;


    return (m_effect->GetVector(parameter, &value) == D3D_OK);
} // GetVector



bool Effect::GetVectorArray(Effect::EffectHandle parameter, Vec4 *array, uint count)
{
    if (!m_effect)
        return false;


    return (m_effect->GetVectorArray(parameter, array, count) == D3D_OK);
} // GetVectorArray



bool Effect::GetMatrix(Effect::EffectHandle parameter, Matrix &value)
{
    if (!m_effect)
        return false;


    return (m_effect->GetMatrix(parameter, &value) == D3D_OK);
} // GetMatrix



bool Effect::GetMatrixArray(Effect::EffectHandle parameter, Matrix *array, uint count)
{
    if (!m_effect)
        return false;


    return (m_effect->GetMatrixArray(parameter, array, count) == D3D_OK);
} // GetMatrixArray



bool Effect::GetString(Effect::EffectHandle parameter, const char **pstring)
{
    if (!m_effect)
        return false;


    return (m_effect->GetString(parameter, pstring) == D3D_OK);
} // GetString



bool Effect::SetBool(Effect::EffectHandle parameter, bool value)
{
    if (!m_effect)
        return false;


    return (m_effect->SetBool(parameter, value ? TRUE : FALSE) == D3D_OK);
} // SetBool



bool Effect::SetBoolArray(Effect::EffectHandle parameter, const bool *array, uint count)
{
    if (!m_effect)
        return false;

    BOOL b[256];
    for (uint i = 0; i < count; i++)
        b[i] = (array[i] ? TRUE : FALSE);

    return (m_effect->SetBoolArray(parameter, (BOOL *) &b, count) == D3D_OK);
} // SetBoolArray



bool Effect::SetFloat(Effect::EffectHandle parameter, float value)
{
    if (!m_effect)
        return false;


    return (m_effect->SetFloat(parameter, value) == D3D_OK);
} // SetFloat



bool Effect::SetFloatArray(Effect::EffectHandle parameter, const float *array, uint count)
{
    if (!m_effect)
        return false;


    return (m_effect->SetFloatArray(parameter, array, count) == D3D_OK);
} // SetFloatArray



bool Effect::SetInt(Effect::EffectHandle parameter, int value)
{
    if (!m_effect)
        return false;


    return (m_effect->SetInt(parameter, value) == D3D_OK);
} // SetInt



bool Effect::SetIntArray(Effect::EffectHandle parameter, const int *array, uint count)
{
    if (!m_effect)
        return false;


    return (m_effect->SetIntArray(parameter, array, count) == D3D_OK);
} // SetIntArray



bool Effect::SetVector(Effect::EffectHandle parameter, const Vec4 &value)
{
    if (!m_effect)
        return false;


    return (m_effect->SetVector(parameter, &value) == D3D_OK);
} // SetVector



bool Effect::SetVectorArray(Effect::EffectHandle parameter, const Vec4 *array, uint count)
{
    if (!m_effect)
        return false;


    return (m_effect->SetVectorArray(parameter, array, count) == D3D_OK);
} // SetVectorArray



bool Effect::SetMatrix(Effect::EffectHandle parameter, const Matrix &value)
{
    if (!m_effect)
        return false;


    return (m_effect->SetMatrix(parameter, &value) == D3D_OK);
} // SetMatrix



bool Effect::SetMatrixArray(Effect::EffectHandle parameter, const Matrix *array, uint count)
{
    if (!m_effect)
        return false;


    return (m_effect->SetMatrixArray(parameter, array, count) == D3D_OK);
} // SetMatrixArray



bool Effect::SetString(Effect::EffectHandle parameter, const char *string)
{
    if (!m_effect)
        return false;


    return (m_effect->SetString(parameter, string) == D3D_OK);
} // SetString



bool Effect::SetValue(Effect::EffectHandle parameter, const void *pdata, uint bytes)
{
    if (!m_effect)
        return false;


    return (m_effect->SetValue(parameter, pdata, bytes) == D3D_OK);
} // SetValue



Effect::EffectHandle Effect::GetAnnotation(Effect::EffectHandle object,uint index)
{
    return m_effect->GetAnnotation(object, index);
} // GetAnnotation



Effect::EffectHandle Effect::GetAnnotationByName(Effect::EffectHandle object,const char *name)
{
    return m_effect->GetAnnotationByName(object, name);
} // GetAnnotationByName



Effect::EffectHandle Effect::GetFunction(uint index)
{
    return m_effect->GetFunction(index);
} // GetFunction



Effect::EffectHandle Effect::GetFunctionByName(const char *name)
{
    return m_effect->GetFunctionByName(name);
} // GetFunctionByName



Effect::EffectHandle Effect::GetParameter(uint index)
{
    return m_effect->GetParameter(0, index);
} // GetParameter



Effect::EffectHandle Effect::GetParameter(Effect::EffectHandle parameter, uint index)
{
    return m_effect->GetParameter(parameter, index);
} // GetParameter



Effect::EffectHandle Effect::GetParameterByName(const char *name)
{
    return m_effect->GetParameterByName(0, name);
} // GetParameterByName



Effect::EffectHandle Effect::GetParameterByName(Effect::EffectHandle parameter, const char *name)
{
    return m_effect->GetParameterByName(parameter, name);
} // GetParameterByName



Effect::EffectHandle Effect::GetParameterBySemantic(const char *semantic)
{
    return m_effect->GetParameterBySemantic(0, semantic);
} // GetParameterBySemantic



Effect::EffectHandle Effect::GetParameterBySemantic(Effect::EffectHandle parameter, const char *semantic)
{
    return m_effect->GetParameterBySemantic(parameter, semantic);
} // GetParameterBySemantic



Effect::EffectHandle Effect::GetParameterElement(Effect::EffectHandle parameter, uint index)
{
    return m_effect->GetParameterElement(parameter, index);
} // GetParameterElement



Effect::EffectHandle Effect::GetPass(Effect::EffectHandle technique, uint index)
{
    return m_effect->GetPass(technique, index);
} // GetPass



Effect::EffectHandle Effect::GetPassByName(Effect::EffectHandle technique, const char *name)
{
    return m_effect->GetPassByName(technique, name);
} // GetPassByName



bool Effect::IsParameterUsed(Effect::EffectHandle parameter, Effect::EffectHandle technique)
{
    if (!m_effect)
        return false;


    return (m_effect->IsParameterUsed(parameter, technique) == TRUE);
} // IsParameterUsed



Effect::EffectHandle Effect::GetCurrentTechnique()
{
    return m_effect->GetCurrentTechnique();
} // GetCurrentTechnique



Effect::EffectHandle Effect::FindNextValidTechnique(Effect::EffectHandle technique)
{
    Effect::EffectHandle *pnext = 0;
    if (m_effect->FindNextValidTechnique(technique, pnext) == D3D_OK)
        return *pnext;
    else
        return NULL;
} // FindNextValidTechnique



Effect::EffectHandle Effect::GetTechnique(uint index)
{
    return m_effect->GetTechnique(index);
} // GetTechnique



Effect::EffectHandle Effect::GetTechniqueByName(const char *name)
{
    return m_effect->GetTechniqueByName(name);
} // GetTechniqueByName



bool Effect::SetTechnique(Effect::EffectHandle technique)
{
    if (!m_effect)
        return false;


    return (m_effect->SetTechnique(technique) == D3D_OK);
} // SetTechnique



bool Effect::ValidateTechnique(Effect::EffectHandle technique)
{
    if (!m_effect)
        return false;


    return (m_effect->ValidateTechnique(technique) == D3D_OK);
} // ValidateTechnique



bool Effect::SetTexture(Effect::EffectHandle parameter, LPDIRECT3DBASETEXTURE9 texture)
{
    if (!m_effect)
        return false;


    return (m_effect->SetTexture(parameter, texture) == D3D_OK);
} // SetTexture



/*

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

VS_OUTPUT VertexShader(float4 Position   : POSITION, 
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

PS_OUTPUT PixelShader(VS_OUTPUT In) : COLOR
{
    PS_OUTPUT Out   = (PS_OUTPUT) 0;
    
    float4 color1   = tex2D(DiffuseSampler, In.TexCoord0) * In.Diffuse * 1.5;
    float4 color2   = tex2D(DiffuseSampler, In.TexCoord1) * 0.1;
    
    color1.a        = 0.85;
    color2.a        = 0.0;
    
    Out.RGBColor    = color1 + color2;
    
    return Out;
}
*/

// -- EOF

