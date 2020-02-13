// ----------------------------------------------------------------------------
// File: Geode.cpp
// Desc: Node for holding geometry
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Scenegraph/Geode.h"
#include "Engine/RenderBin.h"


// ----------------------------------------------------------------------------
// Name: Geode::Geode
// Desc: Default constructor
// ----------------------------------------------------------------------------
Geode::Geode() : Node()
{
} // Geode


// ----------------------------------------------------------------------------
// Name: Geode::Geode
// Desc: Constructor
// Parm: const std::string &name - the node name
// ----------------------------------------------------------------------------
Geode::Geode(const std::string &name) : Node(name)
{
} // Geode


// ----------------------------------------------------------------------------
// Name: Geode::~Geode
// Desc: Destructor
// ----------------------------------------------------------------------------
Geode::~Geode() 
{
} // ~Geode


// ----------------------------------------------------------------------------
// Name: Geode::IsOfType
// Desc: Tests if the node is either the given type, or derives from the given 
//       type
// Parm: const NodeType node_type - the node type
// Retn: bool                     - true if successful
// ----------------------------------------------------------------------------
bool Geode::IsOfType(const NodeType node_type)
{
    if (node_type == Node::GetNodeType() || node_type == Node::GetGeodeType())
        return true;

    return false;
} // IsOfType


// ----------------------------------------------------------------------------
// Name: Geode::IsExactType
// Desc: Tests if the node is the exact type specified
// Parm: const NodeType node_type - the node type
// Retn: bool                     - true if successful
// ----------------------------------------------------------------------------
bool Geode::IsExactType(const NodeType node_type)
{
    if (node_type == Node::GetGeodeType())
        return true;

    return false;
} // IsExactType


// ----------------------------------------------------------------------------
// Name: Geode::AddGeoSet
// Desc: Add a geoset to teh node
// Parm: GeoSet *pgeoset - the geoset
// ----------------------------------------------------------------------------
void Geode::AddGeoSet(GeoSet *pgeoset)
{
    m_geosets.push_back(pgeoset);
} // AddGeoSet


// ----------------------------------------------------------------------------
// Name: Geode::RemoveGeoSet
// Desc: Remove a geoset from the node
// Parm: GeoSet *pgeoset - the geoset
// ----------------------------------------------------------------------------
void Geode::RemoveGeoSet(GeoSet *pgeoset)
{
    std::vector<GeoSet *>::iterator iter = m_geosets.begin();
    for (; iter != m_geosets.end(); ++iter)
    {
        if (*iter == pgeoset)
        {
            m_geosets.erase(iter);
            return;
        } // if
    } // for
} // RemoveGeoSet


// ----------------------------------------------------------------------------
// Name: Geode::GetGeoSet
// Desc: Get a geoset from the node
// Parm: size_t index - the index of the geoset
// Retn: GeoSet *     - the geoset
// ----------------------------------------------------------------------------
GeoSet *Geode::GetGeoSet(size_t index)
{
    if (index < 0 || index >= m_geosets.size())
        return 0;

    return m_geosets[index];
} // GetGeoSet


// ----------------------------------------------------------------------------
// Name: Geode::GetNodeDescription
// Desc: Get the description of this node
// ----------------------------------------------------------------------------
std::string Geode::GetNodeDescription()
{
    std::string str("Geode: ");
    str += GetName();
    str += " - ";
    str += GetBSphereStr();

    return str;
} // GetNodeDescription


// ----------------------------------------------------------------------------
// Name: Geode::GetBSphere
// Desc: Get the bounding sphere of the node
// Retn: Sphere - the bounding sphere
// ----------------------------------------------------------------------------
const Sphere &Geode::GetBSphere()
{
    if (RenderBin::GetFrameCount() == m_last_frame)
        return m_sphere;
    
    if (!m_static)
    {
        m_sphere.Reset();

        for (size_t i = 0; i < m_geosets.size(); i++)
        {
            GeoSet *pgset = m_geosets[i];

            if (i == 0)
                m_sphere = pgset->GetBSphere();
            else
                m_sphere.Calculate(m_sphere, pgset->GetBSphere());
        } // for
    } // if

    m_last_frame = RenderBin::GetFrameCount();
    return m_sphere;
} // GetBSphere


// -- EOF

