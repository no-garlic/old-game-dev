// ----------------------------------------------------------------------------
// File: CourseManager.h
// Desc: Manages the course, the buoys, etc..
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _COURSE_MANAGER_H_
#define _COURSE_MANAGER_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "GameObject/PositionReader.h"
#include "Common/Utilities.h"
#include "SceneGraph/CullTraverser.h"
#include "SceneGraph/Group.h"
#include "Math/Types.h"


// ----------------------------------------------------------------------------
// Singleton accessor
// ----------------------------------------------------------------------------
class   CourseManager;
typedef Singleton::SingletonHolder<CourseManager, 
        Singleton::CreateUsingNew<CourseManager> > CourseManagerSingleton;


// ----------------------------------------------------------------------------
// Name: CourseManager  (class)
// Desc: Manages the course, the buoys, etc..
// ----------------------------------------------------------------------------
class CourseManager : private Utility::Unique
{
private:
    // ------------------------------------------------------------------------
    // Allow the singleton to create this class
    // ------------------------------------------------------------------------
    friend struct Singleton::CreateUsingNew<CourseManager>;

    
    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
    CourseManager();
    virtual ~CourseManager();


public:
    // ------------------------------------------------------------------------
    // Memory functions
    // ------------------------------------------------------------------------
    bool        Create(LPDIRECT3DDEVICE9 device, const char *filename);
    void        Release();


    // ------------------------------------------------------------------------
    // Public interface
    // ------------------------------------------------------------------------
    void        Simulate(float run_time);
    void        Render();



private:
    struct PosData
    {
        float x;
        float y;
        float z;
        float h;
        Vec3  normal;
        Matrix *pmatrix;
    };


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    LPDIRECT3DDEVICE9       m_device;
    PositionReader          m_pos_reader;
    Group                  *m_pgroup_node;
    CullTraverser           m_cull_trav;
    std::vector<PosData>    m_buoys;


}; // class CourseManager


#endif // _COURSE_MANAGER_H_

// -- EOF

