// ----------------------------------------------------------------------------
// File: Vessels.h
// Desc: Manages the ocean
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _VESSELS_H_
#define _VESSELS_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include "Math/Types.h"
#include "Math/Matrix.h"
#include "Engine/Mesh.h"
#include "GameObject/Player.h"
#include "SceneGraph/CullTraverser.h"
#include "SceneGraph/Group.h"
#include <string>
#include <vector>


// ----------------------------------------------------------------------------
// Singleton typedefs
// ----------------------------------------------------------------------------
class Vessels;
typedef Singleton::SingletonHolder<Vessels, Singleton::CreateUsingNew<Vessels> > VesselsSingleton;


// ----------------------------------------------------------------------------
// Name: Vessels  (class)
// Desc: Manages the environmental conditions
// ----------------------------------------------------------------------------
class Vessels : private Utility::Unique
{
private:
    // ------------------------------------------------------------------------
    // Allow the singleton holder to construct this class
    // ------------------------------------------------------------------------
    friend struct Singleton::CreateUsingNew<Vessels>;


    // ------------------------------------------------------------------------
    // Private constructor and destructor
    // ------------------------------------------------------------------------
             Vessels();
    virtual ~Vessels();


public:
    // ------------------------------------------------------------------------
    // Memory routines
    // ------------------------------------------------------------------------
    bool Create(LPDIRECT3DDEVICE9 device);
    bool Release();


    // ------------------------------------------------------------------------
    // Name: VesselType (enum)
    // Desc: Types of vessels
    // ------------------------------------------------------------------------
    enum VesselType
    {
        WOODEN_CANNOE,
        YACHT,
        SEA_DOO
    }; // enum VesselType


    // ------------------------------------------------------------------------
    // Public methods
    // ------------------------------------------------------------------------
    bool            Add(const char *name, VesselType type, float x, float y, float h, Player *pplayer = 0);
    void            Simulate(float dt);
    void            Render();
    const Matrix   &GetMatrix(const char *name);
    float           GetHeading(const char *name);
    float           GetSpeed(const char *name);
    bool            GetOnWater(const char *name);


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    LPDIRECT3DDEVICE9           m_device;
    Group                      *m_pgroup_node;
    CullTraverser               m_cull_trav;
    uint                        m_material_id;


}; // class Vessels


#endif // _VESSELS_H_

// -- EOF

