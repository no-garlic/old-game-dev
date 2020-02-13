// ----------------------------------------------------------------------------
// File: Group.cpp
// Desc: Node to collect child nodes
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Scenegraph/Group.h"
#include "Scenegraph/Geode.h"
#include "Engine/RenderBin.h"


// ----------------------------------------------------------------------------
// Name: Group::Group
// Desc: Constructor
// ----------------------------------------------------------------------------
Group::Group() : Node()
{
} // Group


// ----------------------------------------------------------------------------
// Name: Group::Group
// Desc: Constructor
// Parm: const std::string &name - the node name
// ----------------------------------------------------------------------------
Group::Group(const std::string &name) : Node(name)
{
} // Group


// ----------------------------------------------------------------------------
// Name: Group::~Group
// Desc: Destructor
// ----------------------------------------------------------------------------
Group::~Group() 
{
} // ~Group


// ----------------------------------------------------------------------------
// Name: Group::IsOfType
// Desc: Tests if the node is either the given type, or derives from the given 
//       type
// Parm: const NodeType node_type - the node type
// ----------------------------------------------------------------------------
bool Group::IsOfType(const NodeType node_type)
{
    if (node_type == Node::GetNodeType() || node_type == Node::GetGroupType())
        return true;

    return false;
} // IsOfType


// ----------------------------------------------------------------------------
// Name: Group::IsExactType
// Desc: Tests if the node is the exact type specified
// Parm: const NodeType node_type - the node type
// ----------------------------------------------------------------------------
bool Group::IsExactType(const NodeType node_type)
{
    if (node_type == Node::GetGroupType())
        return true;

    return false;
} // IsExactType


// ----------------------------------------------------------------------------
// Name: Group::AddChild
// Desc: Add a child node
// Parm: Node *pnode - the node
// ----------------------------------------------------------------------------
void Group::AddChild(Node *pnode)
{
    pnode->AddParent(this);
    m_nodes.push_back(pnode);
} // AddChildNode


// ----------------------------------------------------------------------------
// Name: Group::RemoveChild
// Desc: Remove a child node
// Parm: Node *pnode - the node
// ----------------------------------------------------------------------------
void Group::RemoveChild(Node *pnode)
{
    std::vector<Node *>::iterator iter = m_nodes.begin();
    for (; iter != m_nodes.end(); ++iter)
    {
        if (*iter == pnode)
        {
            m_nodes.erase(iter);
            pnode->RemoveParent(this);
            return;
        } // if
    } // for
} // RemoveChild


// ----------------------------------------------------------------------------
// Name: Group::GetChild
// Desc: Get a child node
// Parm: size_t index - the index
// Retn: Node *       - the node
// ----------------------------------------------------------------------------
Node *Group::GetChild(size_t index)
{
    if (index < 0 || index >= m_nodes.size())
        return 0;

    return m_nodes[index];
} // GetChild


// ----------------------------------------------------------------------------
// Name: Group::GetNodeDescription
// Desc: Get the description of this node
// ----------------------------------------------------------------------------
std::string Group::GetNodeDescription()
{
    std::string str("Group: ");
    str += GetName();
    str += " - ";
    str += GetBSphereStr();

    return str;
} // GetNodeDescription


// ----------------------------------------------------------------------------
// Name: Group::GetBSphere
// Desc: Get the bounding shpere of this node
// Retn: Sphere - the sphere
// ----------------------------------------------------------------------------
const Sphere &Group::GetBSphere()
{
    if (RenderBin::GetFrameCount() == m_last_frame)
        return m_sphere;
    
    if (!m_static)
    {
        m_sphere.Reset();

        for (size_t i = 0; i < m_nodes.size(); i++)
        {
            Node *pnode = m_nodes[i];

            if (i == 0)
                m_sphere = pnode->GetBSphere();
            else
                m_sphere.Calculate(m_sphere, pnode->GetBSphere());
        } // for
    } // for

    m_last_frame = RenderBin::GetFrameCount();
    return m_sphere;
} // GetBSphere



// -- EOF

