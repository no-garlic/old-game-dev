// ----------------------------------------------------------------------------
// File: Geode.h
// Desc: Node for holding geometry
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _GEODE_H
#define _GEODE_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include <vector>
#include "Common/Utilities.h"
#include "Math/Types.h"
#include "Scenegraph/Node.h"
#include "SceneGraph/GeoSet.h"


// ----------------------------------------------------------------------------
// Name: Geode  (class)
// Desc: Node for holding geometry
// ----------------------------------------------------------------------------
class Geode : public Node
{
public:
    // ------------------------------------------------------------------------
    // Constructors and destructor
    // ------------------------------------------------------------------------
             Geode();
             Geode(const std::string &name);
    virtual ~Geode();


    // ------------------------------------------------------------------------
    // Manage geosets
    // ------------------------------------------------------------------------
    void    AddGeoSet(GeoSet *pgeoset);
    void    RemoveGeoSet(GeoSet *pgeoset);
    size_t  GetNumGeoSets() { return m_geosets.size(); }
    GeoSet *GetGeoSet(size_t index);


    // ------------------------------------------------------------------------
    // Get the bounding sphere
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
    // Private members
    // ------------------------------------------------------------------------
    std::vector<GeoSet *>   m_geosets;  // All geosets


}; // class Geode


#endif // _GEODE_H

// -- EOF

