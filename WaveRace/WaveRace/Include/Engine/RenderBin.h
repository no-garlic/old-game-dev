// ----------------------------------------------------------------------------
// File: RenderBin.h
// Desc: Provides a method of sorting and scheduling items to be rendered, then 
//       rendering them in a controlled manner
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _RENDER_BIN_H_
#define _RENDER_BIN_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include "Common/Logging.h"
#include "Math/Types.h"
#include "Math/Matrix.h"
#include "Engine/Mesh.h"
#include "Math/Frustum.h"
#include <list>
#include <map>


// ----------------------------------------------------------------------------
// Singleton typedef
// ----------------------------------------------------------------------------
class RenderBin;
typedef Singleton::SingletonHolder<RenderBin, Singleton::CreateUsingNew<RenderBin> > RenderBinSingleton;


// ----------------------------------------------------------------------------
// Name: RenderBin  (class)
// Desc: Provides a method of sorting and scheduling items to be rendered, then 
//       rendering them in a controlled manner
// ----------------------------------------------------------------------------
class RenderBin : private Utility::Unique
{
private:
    // ------------------------------------------------------------------------
    // Allow the singleton holder's policy to construct and destruct teh class
    // ------------------------------------------------------------------------
    friend struct Singleton::CreateUsingNew<RenderBin>;


    // ------------------------------------------------------------------------
    // Private constructor and destructor
    // ------------------------------------------------------------------------
             RenderBin();
    virtual ~RenderBin();


public:
    // ------------------------------------------------------------------------
    // Public methods
    // ------------------------------------------------------------------------
    bool Create(LPDIRECT3DDEVICE9 device);
    void Release();
    void AddRenderTarget(Mesh *pmesh, uint material_id, Matrix world_matrix);
    void Render();


    // ------------------------------------------------------------------------
    // Static public methods
    // ------------------------------------------------------------------------
    static ulong GetFrameCount() { return s_frame_count; }


private:
    // ------------------------------------------------------------------------
    // Name: RenderTarget (struct)
    // Desc: Struct to hold a mesh to be rendered, and it's render info
    // ------------------------------------------------------------------------
    struct RenderTarget
    {
        Mesh    *pmesh;
        uint     material_id;
        Matrix   world_matrix;
    }; // struct RenderTarget


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    LPDIRECT3DDEVICE9                               m_device;
    Frustum                                         m_frustum;
    std::multimap<uint,  RenderBin::RenderTarget>   m_opaque_bin;
    std::multimap<float, RenderBin::RenderTarget>   m_transparent_bin;


    // ------------------------------------------------------------------------
    // Static private members
    // ------------------------------------------------------------------------
    static ulong        s_frame_count;  // The frame count


}; // class RenderBin


#endif // _RENDER_BIN_H_

// -- EOF
