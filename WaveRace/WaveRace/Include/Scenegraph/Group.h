// ----------------------------------------------------------------------------
// File: Group.h
// Desc: Node to collect child nodes
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _GROUP_H
#define _GROUP_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include <vector>
#include "Common/Utilities.h"
#include "Math/Types.h"
#include "Scenegraph/Node.h"


// ----------------------------------------------------------------------------
// Name: Group  (class)
// Desc: Node to collect child nodes
// ----------------------------------------------------------------------------
class Group : public Node
{
public:
    // ------------------------------------------------------------------------
    // Constructors and destructor
    // ------------------------------------------------------------------------
             Group();
             Group(const std::string &name);
    virtual ~Group();


    // ------------------------------------------------------------------------
    // Public functions
    // ------------------------------------------------------------------------
    void    AddChild(Node *pnode);
    void    RemoveChild(Node *pnode);
    size_t  GetNumChildren() { return m_nodes.size(); }
    Node   *GetChild(size_t index);


    // ------------------------------------------------------------------------
    // The bounding sphere
    // ------------------------------------------------------------------------
    virtual const Sphere &GetBSphere();


protected:
    // ------------------------------------------------------------------------
    // Protected functions
    // ------------------------------------------------------------------------
    virtual std::string GetNodeDescription();
    virtual bool        IsOfType(const NodeType node_type);
    virtual bool        IsExactType(const NodeType node_type);


private:
    // ------------------------------------------------------------------------
    // Private functions
    // ------------------------------------------------------------------------
    std::vector<Node *>  m_nodes;   // child nodes


}; // class Group


#endif // _GROUP_H

// -- EOF

