// ----------------------------------------------------------------------------
// File: SkyBox.h
// Desc: Manages a number of sky boxes
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _SKY_BOX_H
#define _SKY_BOX_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include "Engine/Mesh.h"
#include "Engine/Object.h"
#include <vector>


// ----------------------------------------------------------------------------
// Singleton typedefs
// ----------------------------------------------------------------------------
class SkyBox;
typedef Singleton::SingletonHolder<SkyBox, Singleton::CreateUsingNew<SkyBox> > SkyBoxSingleton;


// ----------------------------------------------------------------------------
// Name: SkyBox  (class)
// Desc: Manages a number of sky boxes
// ----------------------------------------------------------------------------
class SkyBox : private Utility::Unique
{
private:
    // ------------------------------------------------------------------------
    // Allow the singleton holder to construct this class
    // ------------------------------------------------------------------------
    friend struct Singleton::CreateUsingNew<SkyBox>;


    // ------------------------------------------------------------------------
    // Private constructor and destructor
    // ------------------------------------------------------------------------
             SkyBox();
    virtual ~SkyBox();


public:
    // ------------------------------------------------------------------------
    // Memory routines
    // ------------------------------------------------------------------------
    bool Create(LPDIRECT3DDEVICE9 device);
    void Release();


    // ------------------------------------------------------------------------
    // Name: SkyBoxType (enum)
    // Desc: Available sky boxes
    // ------------------------------------------------------------------------
    enum SkyBoxType
    {
        SKY_NONE,
        SKY_SUNNY,
        SKY_CLOUDY,
        SKY_STORMY
    };

    // ------------------------------------------------------------------------
    // Public functions
    // ------------------------------------------------------------------------
    void Select(SkyBox::SkyBoxType type);
    void Simulate(float run_time);
    void Render();


private:
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    LPDIRECT3DDEVICE9       m_device;
    SkyBox::SkyBoxType      m_type;
    Object                 *m_psunny;
    Object                 *m_pcloudy;
    Object                 *m_pstormy;
    float                   m_heading;

}; // class SkyBox


#endif // _SKY_BOX_H

// -- EOF

