// ----------------------------------------------------------------------------
// File: Node.h
// Desc: Base scenegraph node class
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _NODE_H
#define _NODE_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include <string>
#include <vector>
#include "Common/Utilities.h"
#include "Math/Types.h"
#include "Math/Sphere.h"


// ----------------------------------------------------------------------------
// Name: Node  (class)
// Desc: Base scenegraph node class
// ----------------------------------------------------------------------------
class Node : private Utility::Unique
{
public:
    // ------------------------------------------------------------------------
    // Constructors and destructor
    // ------------------------------------------------------------------------
             Node();
             Node(const std::string &name);
    virtual ~Node();


    // ------------------------------------------------------------------------
    // Public methods
    // ------------------------------------------------------------------------
    const std::string  &GetName() const                  { return m_name; }
    void                SetName(const std::string &name) { m_name = name; }
    void                PrintTree(uint indent = 0);


    // ------------------------------------------------------------------------
    // Manage the parents
    // ------------------------------------------------------------------------
    void            AddParent(Node *pnode);
    void            RemoveParent(Node *pnode);
    Node           *GetParent(size_t index);
    size_t          GetNumParents() { return m_parents.size(); }


    // ------------------------------------------------------------------------
    // Bounding sphere functions
    // ------------------------------------------------------------------------
    virtual const Sphere &GetBSphere() = 0;
    void                  SetBSphereStatic();
    std::string           GetBSphereStr();


    // ------------------------------------------------------------------------
    // Manage the cull traversal
    // ------------------------------------------------------------------------
    bool            GetCullingEnabled()                { return m_can_cull;     }
    void            SetCullingEnabled(bool can_cull)   { m_can_cull = can_cull; }


    // ------------------------------------------------------------------------
    // Manage the intersection traversal
    // ------------------------------------------------------------------------
    bool            GetIntersectionEnabled()               { return m_can_isect;      }
    void            SetIntersectionEnabled(bool can_isect) { m_can_isect = can_isect; }


    // ------------------------------------------------------------------------
    // Manage user data
    // ------------------------------------------------------------------------
    void            SetUserData(void *pdata)            { m_data[0] = pdata;   }
    void            SetUserData(uint idx, void *pdata)  { m_data[idx] = pdata; }
    void           *GetUserData()                       { return m_data[0];    }
    void           *GetUserData(uint idx)               { return m_data[idx];  }


public:
    // ------------------------------------------------------------------------
    // Types of nodes
    // ------------------------------------------------------------------------
    typedef int  NodeType;

    static const NodeType GetNodeType();
    static const NodeType GetGroupType();
    static const NodeType GetDCSType();
    static const NodeType GetGeodeType();
    static const NodeType GetSwitchType();
    static const NodeType GetSequenceType();


    // ------------------------------------------------------------------------
    // Node functions
    // ------------------------------------------------------------------------
    virtual std::string GetNodeDescription() = 0;
    virtual bool        IsOfType(const NodeType node_type) = 0;
    virtual bool        IsExactType(const NodeType node_type) = 0;
    const NodeType      GetType() { return m_node_type; }


protected:
    // ------------------------------------------------------------------------
    // Protected functions
    // ------------------------------------------------------------------------
    NodeType            m_node_type;    // Node type
    Sphere              m_sphere;       // Bounding sphere
    bool                m_static;       // Bounds static
    ulong               m_last_frame;   // Frame num when last bsphere calc


private:
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    std::string             m_name;         // Node name
    std::vector<Node *>     m_parents;      // Parent list
    std::map<uint, void *>  m_data;         // User data
    bool                    m_can_isect;    // Intersection flag
    bool                    m_can_cull;     // Cull flag


}; // class Node


#endif // _NODE_H

// -- EOF

