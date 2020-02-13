// ----------------------------------------------------------------------------
// File: Node.cpp
// Desc: Base scenegraph node
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include <sstream>
#include "Scenegraph/Node.h"
#include "Scenegraph/Group.h"
#include "Common/Logging.h"


// ----------------------------------------------------------------------------
// The node types
// ----------------------------------------------------------------------------
const Node::NodeType Node::GetNodeType()        { return 1; }
const Node::NodeType Node::GetGroupType()       { return 2; }
const Node::NodeType Node::GetDCSType()         { return 3; }
const Node::NodeType Node::GetGeodeType()       { return 4; }
const Node::NodeType Node::GetSwitchType()      { return 5; }
const Node::NodeType Node::GetSequenceType()    { return 6; }


// ----------------------------------------------------------------------------
// Name: Node::Node
// Desc: Constructor
// ----------------------------------------------------------------------------
Node::Node()
{
    m_can_cull      = true;
    m_can_isect     = true;
    m_static        = false;
    m_last_frame    = 0;
} // Node


// ----------------------------------------------------------------------------
// Name: Node::Node
// Desc: Constructor
// Parm: const std::string &name - the node name
// ----------------------------------------------------------------------------
Node::Node(const std::string &name) : m_name(name)
{
    m_can_cull      = true;
    m_can_isect     = true;
    m_static        = false;
    m_last_frame    = 0;
} // Node


// ----------------------------------------------------------------------------
// Name: Node::~Node
// Desc: Destructor
// ----------------------------------------------------------------------------
Node::~Node()
{
} // ~Node


// ----------------------------------------------------------------------------
// Name: Node::AddParent
// Desc: Add a parent node
// Parm: Node *pnode - the parent node
// ----------------------------------------------------------------------------
void Node::AddParent(Node *pnode)
{
    std::vector<Node *>::iterator iter = m_parents.begin();
    for (; iter != m_parents.end(); ++iter)
    {
        if (*iter == pnode)
            return;
    } // for

    m_parents.push_back(pnode);
} // AddParent


// ----------------------------------------------------------------------------
// Name: Node::RemoveParent
// Desc: Remove a parent node
// Parm: Node *pnode - the parent node
// ----------------------------------------------------------------------------
void Node::RemoveParent(Node *pnode)
{
    std::vector<Node *>::iterator iter = m_parents.begin();
    for (; iter != m_parents.end(); ++iter)
    {
        if (*iter == pnode)
        {
            m_parents.erase(iter);
            return;
        } // if
    } // for
} // RemoveParent


// ----------------------------------------------------------------------------
// Name: Node::GetParent
// Desc: Get the parent
// Parm: size_t index - the index
// Retn: Node *       - the parent
// ----------------------------------------------------------------------------
Node *Node::GetParent(size_t index)
{
    if (index < 0 || index >= m_parents.size())
        return 0;

    return m_parents[index];
} // GetParent


// ----------------------------------------------------------------------------
// Name: Node::PrintTree
// Desc: Print the node hierarchy
// Parm: uint indent - the indentation to use
// ----------------------------------------------------------------------------
void Node::PrintTree(uint indent)
{
    std::string str = String::Space(indent);

    str += GetNodeDescription();
    LOG << str << ENDLOG;

    if (IsOfType(Node::GetGroupType()))
    {
        Group *pgroup = static_cast<Group *>(this);
        for (size_t i = 0; i < pgroup->GetNumChildren(); i++)
        {
            Node *pnode = pgroup->GetChild(i);
            pnode->PrintTree(indent + 2);
        } // for
    } // if
} // PrintTree


// ----------------------------------------------------------------------------
// Name: Node::GetBSphereStr
// Desc: Get the bounding sphere as a string
// Retn: std::string - the string
// ----------------------------------------------------------------------------
std::string Node::GetBSphereStr()
{
    Sphere s = GetBSphere();
    std::stringstream str;
    str << "Radius: " << s.radius << ", Center: (" << 
        s.center[0] << ", " << s.center[1] << ", " << s.center[2] << ")";
    return str.str();
} // GetBSphereStr


void Node::SetBSphereStatic()
{
    m_static = false;
    GetBSphere();
    m_static = true;
} // SetBSphereStatic

// -- EOF

