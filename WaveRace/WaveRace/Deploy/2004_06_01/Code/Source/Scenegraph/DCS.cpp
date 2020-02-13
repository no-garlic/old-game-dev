// ----------------------------------------------------------------------------
// File: DCS.cpp
// Desc: Dynamic co-ordinate system node type
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Scenegraph/DCS.h"
#include "Engine/RenderBin.h"


// ----------------------------------------------------------------------------
// Name: DCS::DCS
// Desc: Constructor
// ----------------------------------------------------------------------------
DCS::DCS() : Group() 
{
    m_matrix.Identity();
} // DCS


// ----------------------------------------------------------------------------
// Name: DCS::DCS
// Desc: Constructor
// Parm: const std::string &name - the node name
// ----------------------------------------------------------------------------
DCS::DCS(const std::string &name) : Group(name)
{
    m_matrix.Identity();
} // DCS


// ----------------------------------------------------------------------------
// Name: DCS::~DCS
// Desc: Destructor
// ----------------------------------------------------------------------------
DCS::~DCS()
{
} // ~DCS


// ----------------------------------------------------------------------------
// Name: DCS::IsOfType
// Desc: Tests if the node is either the given type, or derives from the given 
//       type
// Parm: const NodeType node_type - the type
// ----------------------------------------------------------------------------
bool DCS::IsOfType(const NodeType node_type)
{
    if (node_type == Node::GetDCSType() || node_type == Node::GetGroupType() || node_type == Node::GetNodeType())
        return true;

    return false;
} // IsOfType


// ----------------------------------------------------------------------------
// Name: DCS::IsExactType
// Desc: Tests if the node is the exact type specified
// Parm: const NodeType node_type - the type
// ----------------------------------------------------------------------------
bool DCS::IsExactType(const NodeType node_type)
{
    if (node_type == Node::GetDCSType())
        return true;

    return false;
} // IsExactType


// ----------------------------------------------------------------------------
// Name: DCS::GetNodeDescription
// Desc: Get a description of the node
// ----------------------------------------------------------------------------
std::string DCS::GetNodeDescription()
{
    std::string str("DCS: ");
    str += GetName();
    str += " - ";
    str += GetBSphereStr();

    return str;
} // GetNodeDescription


// ----------------------------------------------------------------------------
// Name: DCS::GetBSphere
// Desc: Get the bounding sphere of the node
// Retn: Sphere - the sphere
// ----------------------------------------------------------------------------
const Sphere &DCS::GetBSphere()
{
    if (RenderBin::GetFrameCount() == m_last_frame)
        return m_sphere;
    
    if (!m_static)
    {
        m_sphere = Group::GetBSphere();
        m_sphere.center.TransformCoord(m_sphere.center, m_matrix);
    } // if

    m_last_frame = RenderBin::GetFrameCount();
    return m_sphere;
} // GetBSphere


// -- EOF

