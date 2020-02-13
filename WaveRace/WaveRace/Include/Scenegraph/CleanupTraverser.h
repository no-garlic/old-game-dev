// ----------------------------------------------------------------------------
// File: CleanupTraverser.h
// Desc: Traverses a scenegraph and deletes all nodes, geosets, and meshes 
//       requested
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _CLEANUP_TRAVERSER_H_
#define _CLEANUP_TRAVERSER_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include "Math/Types.h"
#include "Scenegraph/Node.h"
#include "Scenegraph/Group.h"
#include "Scenegraph/Geode.h"
#include "Scenegraph/GeoSet.h"


// ----------------------------------------------------------------------------
// Name: CleanupTraverser (class)
// Desc: Traverses a scenegraph and deletes all nodes, geosets, and meshes 
//       requested
// ----------------------------------------------------------------------------
class CleanupTraverser
{
public:
    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
     CleanupTraverser() {}
    ~CleanupTraverser() {}

 
    // ------------------------------------------------------------------------
    // Public functions
    // ------------------------------------------------------------------------
    void Traverse(Node *pnode);


private:
    // ------------------------------------------------------------------------
    // Private traversal functions
    // ------------------------------------------------------------------------
    void CleanupGroup(Group *pgroup);
    void CleanupGeode(Geode *pgeode);
    void CleanupGeoSet(GeoSet *pgeoset);


}; // class CullTraverser


#endif // _CLEANUP_TRAVERSER_H_

// -- EOF

