// ----------------------------------------------------------------------------
// File: Switch.h
// Desc: Node to control traversals
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Scenegraph/Switch.h"


// ----------------------------------------------------------------------------
// Name: Switch::Switch
// Desc: Constructor
// ----------------------------------------------------------------------------
Switch::Switch() : Group(), m_value(true)
{
} // Switch


// ----------------------------------------------------------------------------
// Name: Switch::Switch
// Desc: Constructor
// Parm: const std::string &name - the name of the node
// ----------------------------------------------------------------------------
Switch::Switch(const std::string &name) : Group(name), m_value(true)
{
} // Switch


// ----------------------------------------------------------------------------
// Name: Switch::~Switch
// Desc: Destructor
// ----------------------------------------------------------------------------
Switch::~Switch()
{
} // ~Switch


// ----------------------------------------------------------------------------
// Name: Switch::IsOfType
// Desc: Tests if the node is either the given type, or derives from the given 
//       type
// Parm: const NodeType node_type - the node type
// ----------------------------------------------------------------------------
bool Switch::IsOfType(const NodeType node_type)
{
    if (node_type == Node::GetSwitchType() || node_type == Node::GetGroupType() || node_type == Node::GetNodeType())
        return true;

    return false;
} // IsOfType


// ----------------------------------------------------------------------------
// Name: Switch::IsExactType
// Desc: Tests if the node is the exact type specified
// Parm: const NodeType node_type - teh node type
// ----------------------------------------------------------------------------
bool Switch::IsExactType(const NodeType node_type)
{
    if (node_type == Node::GetSwitchType())
        return true;

    return false;
} // IsExactType


// ----------------------------------------------------------------------------
// Name: Switch::GetNodeDescription
// Desc: Get the description of the node
// ----------------------------------------------------------------------------
std::string Switch::GetNodeDescription()
{
    std::string str("Switch: ");
    str += GetName();

    if (GetVal())
        str += " [ON]";
    else
        str += " [OFF]";

    str += " - ";
    str += GetBSphereStr();

    return str;
} // GetNodeDescription


// -- EOF

