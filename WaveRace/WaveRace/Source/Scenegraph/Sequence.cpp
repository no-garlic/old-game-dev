// ----------------------------------------------------------------------------
// File: Sequence.cpp
// Desc: Node type to interate through a sequence of children
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Scenegraph/Sequence.h"


// ----------------------------------------------------------------------------
// Name: Sequence::Sequence
// Desc: Constructor
// ----------------------------------------------------------------------------
Sequence::Sequence() : Group(), m_interval(0.1f)
{
} // Sequence


// ----------------------------------------------------------------------------
// Name: Sequence::Sequence
// Desc: Constructor
// Parm: const std::string &name - the node name
// ----------------------------------------------------------------------------
Sequence::Sequence(const std::string &name) : Group(name), m_interval(0.1f)
{
} // Sequence


// ----------------------------------------------------------------------------
// Name: Sequence::~Sequence
// Desc: Destructor
// ----------------------------------------------------------------------------
Sequence::~Sequence()
{
} // ~Sequence


// ----------------------------------------------------------------------------
// Name: Sequence::IsOfType
// Desc: Tests if the node is either the given type, or derives from the given 
//       type
// Parm: const NodeType node_type - the node type
// ----------------------------------------------------------------------------
bool Sequence::IsOfType(const NodeType node_type)
{
    if (node_type == Node::GetSequenceType() || node_type == Node::GetGroupType() || node_type == Node::GetNodeType())
        return true;

    return false;
} // IsOfType


// ----------------------------------------------------------------------------
// Name: Sequence::IsExactType
// Desc: Tests if the node is the exact type specified
// Parm: const NodeType node_type - the node type
// ----------------------------------------------------------------------------
bool Sequence::IsExactType(const NodeType node_type)
{
    if (node_type == Node::GetSequenceType())
        return true;

    return false;
} // IsExactType


// ----------------------------------------------------------------------------
// Name: Sequence::GetNodeDescription
// Desc: Get the description of the node
// ----------------------------------------------------------------------------
std::string Sequence::GetNodeDescription()
{
    std::string str("Sequence: ");
    str += GetName();
    str += " - ";
    str += GetBSphereStr();

    return str;
} // GetNodeDescription


// -- EOF

