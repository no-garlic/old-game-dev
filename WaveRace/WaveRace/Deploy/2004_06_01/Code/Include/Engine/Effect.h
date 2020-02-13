// ----------------------------------------------------------------------------
// File: Effect.h
// Desc: Implementaion of the Effect rendering strategy
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include "Math/Types.h"
#include "Math/Vec4.h"
#include "Math/Matrix.h"
#include <d3dx9effect.h>


// ----------------------------------------------------------------------------
// Flags for what to pass into the FX
// ----------------------------------------------------------------------------
#define FX_WORLD            0x0001
#define FX_VIEW             0x0002
#define FX_PROJ             0x0004
#define FX_WORLDVIEW        0x0008
#define FX_WORLDVIEWPROJ    0x0010
#define FX_TEX0             0x0020
#define FX_TEX1             0x0040
#define FX_TEX2             0x0080
#define FX_DEBUG            0x8000


// ----------------------------------------------------------------------------
// Forward declaration
// ----------------------------------------------------------------------------
class MaterialCache;


// ----------------------------------------------------------------------------
// Name: Effect  (class)
// Desc: Implementaion of the Effect rendering strategy
// ----------------------------------------------------------------------------
class Effect : private Utility::Unique
{
public:
    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
                    Effect();
    virtual        ~Effect();


    // ------------------------------------------------------------------------
    // Memory routines
    // ------------------------------------------------------------------------
    bool            Create(LPDIRECT3DDEVICE9 device, const char *filename, int flags);
    void            Release();


    // ------------------------------------------------------------------------
    // General rendering interface
    // ------------------------------------------------------------------------
    bool            Begin(uint &num_passes, bool discard_state = false, bool discard_shader_state = false);
    bool            Pass(uint pass);
    bool            End();


    // ------------------------------------------------------------------------
    // Our handle type
    // ------------------------------------------------------------------------
    typedef         D3DXHANDLE EffectHandle;


    // ------------------------------------------------------------------------
    // Get values from the effect
    // ------------------------------------------------------------------------
    bool            GetBool(EffectHandle parameter, bool &value);
    bool            GetBoolArray(EffectHandle parameter, bool *array, uint count);
    bool            GetFloat(EffectHandle parameter, float &value);
    bool            GetFloatArray(EffectHandle parameter, float *array, uint count);
    bool            GetInt(EffectHandle parameter, int &value);
    bool            GetIntArray(EffectHandle parameter, int *array, uint count);
    bool            GetVector(EffectHandle parameter, Vec4 &value);
    bool            GetVectorArray(EffectHandle parameter, Vec4 *array, uint count);
    bool            GetMatrix(EffectHandle parameter, Matrix &value);
    bool            GetMatrixArray(EffectHandle parameter, Matrix *array, uint count);
    bool            GetString(EffectHandle parameter, const char **pstring);


    // ------------------------------------------------------------------------
    // Set values in the effect
    // ------------------------------------------------------------------------
    bool            SetBool(EffectHandle parameter, bool value);
    bool            SetBoolArray(EffectHandle parameter, const bool *array, uint count);
    bool            SetFloat(EffectHandle parameter, float value);
    bool            SetFloatArray(EffectHandle parameter, const float *array, uint count);
    bool            SetInt(EffectHandle parameter, int value);
    bool            SetIntArray(EffectHandle parameter, const int *array, uint count);
    bool            SetVector(EffectHandle parameter, const Vec4 &value);
    bool            SetVectorArray(EffectHandle parameter, const Vec4 *array, uint count);
    bool            SetMatrix(EffectHandle parameter, const Matrix &value);
    bool            SetMatrixArray(EffectHandle parameter, const Matrix *array, uint count);
    bool            SetString(EffectHandle parameter, const char *string);
    bool            SetValue(EffectHandle parameter, const void *pdata, uint bytes);


    // ------------------------------------------------------------------------
    // Annotation interface
    // ------------------------------------------------------------------------
    EffectHandle    GetAnnotation(EffectHandle object, uint index);
    EffectHandle    GetAnnotationByName(EffectHandle object, const char *name);


    // ------------------------------------------------------------------------
    // Function interface
    // ------------------------------------------------------------------------
    EffectHandle    GetFunction(uint index);
    EffectHandle    GetFunctionByName(const char *name);


    // ------------------------------------------------------------------------
    // Parameter interface
    // ------------------------------------------------------------------------
    EffectHandle    GetParameter(uint index);
    EffectHandle    GetParameter(EffectHandle parameter, uint index);
    EffectHandle    GetParameterByName(const char *name);
    EffectHandle    GetParameterByName(EffectHandle parameter, const char *name);
    EffectHandle    GetParameterBySemantic(const char *semantic);
    EffectHandle    GetParameterBySemantic(EffectHandle parameter, const char *semantic);
    EffectHandle    GetParameterElement(EffectHandle parameter, uint index);


    // ------------------------------------------------------------------------
    // Pass interface
    // ------------------------------------------------------------------------
    EffectHandle    GetPass(EffectHandle technique, uint index);
    EffectHandle    GetPassByName(EffectHandle technique, const char *name);


    // ------------------------------------------------------------------------
    // Technique interface
    // ------------------------------------------------------------------------
    bool            IsParameterUsed(EffectHandle parameter, EffectHandle technique);
    EffectHandle    GetCurrentTechnique();
    EffectHandle    FindNextValidTechnique(EffectHandle technique);
    EffectHandle    GetTechnique(uint index);
    EffectHandle    GetTechniqueByName(const char *name);
    bool            SetTechnique(EffectHandle technique);
    bool            ValidateTechnique(EffectHandle technique);

    // ------------------------------------------------------------------------
    // Texture interface
    // ------------------------------------------------------------------------
    bool            SetTexture(EffectHandle parameter, LPDIRECT3DBASETEXTURE9 texture);


private:
    // ------------------------------------------------------------------------
    // Let the material cache access our flags
    // ------------------------------------------------------------------------
    friend class MaterialCache;


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    LPDIRECT3DDEVICE9       m_device;
    LPD3DXEFFECT            m_effect;
    int                     m_flags;


}; // class Effect


#endif // _EFFECT_H_

// -- EOF

