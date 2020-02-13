// ----------------------------------------------------------------------------
// File: CleanupTraverser.cpp
// Desc: Traverses a scenegraph and deletes all nodes, geosets, and meshes 
//       requested
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Scenegraph/CleanupTraverser.h"
#include "Engine/Mesh.h"


// ----------------------------------------------------------------------------
// Name: CleanupTraverser::Traverse
// Desc: Traverse the scenegraph and delete all objects
// Parm: Node *pnode - the node to start from
// ----------------------------------------------------------------------------
void CleanupTraverser::Traverse(Node *pnode)
{
    if (!pnode)
        return;

    // Cleanup the node's children
    if (pnode->IsOfType(Node::GetGroupType()))
        CleanupGroup((Group *) pnode);
    else if (pnode->IsOfType(Node::GetGeodeType()))
        CleanupGeode((Geode *) pnode);

    // Delete the node
    delete pnode;
} // Traverse


// ----------------------------------------------------------------------------
// Name: CleanupTraverser::CleanupGroup
// Desc: Cleanup a group and all children
// Parm: Group *pgroup - the group to start from
// ----------------------------------------------------------------------------
void CleanupTraverser::CleanupGroup(Group *pgroup)
{
    uint num_children = pgroup->GetNumChildren();
    for (uint i = 0; i < num_children; i++)
    {
        Node *pchild = pgroup->GetChild(i);
        pgroup->RemoveChild(pchild);
        Traverse(pchild);
    } // for
} // CleanupGroup


// ----------------------------------------------------------------------------
// Name: CleanupTraverser::CleanupGeode
// Desc: Cleanup a geode and all children
// Parm: Geode *pgeode - the geode to start from
// ----------------------------------------------------------------------------
void CleanupTraverser::CleanupGeode(Geode *pgeode)
{
    uint num_gsets = pgeode->GetNumGeoSets();
    for (uint i = 0; i < num_gsets; i++)
    {
        GeoSet *pgset = pgeode->GetGeoSet(i);
        pgeode->RemoveGeoSet(pgset);
        CleanupGeoSet(pgset);
    } // for
} // CleanupGeode


// ----------------------------------------------------------------------------
// Name: CleanupTraverser::CleanupGeoSet
// Desc: Cleanup a geoset and all children
// Parm: GeoSet *pgeoset - the geoset to start from
// ----------------------------------------------------------------------------
void CleanupTraverser::CleanupGeoSet(GeoSet *pgeoset)
{
    std::vector<GeoSet::Record> mesh_vec = pgeoset->GetMeshVec();
    for (uint i = 0; i < mesh_vec.size(); i++)
    {
        GeoSet::Record &rec = mesh_vec[i];

        pgeoset->RemoveMesh(rec.pmesh);
        delete rec.pmesh;
    } // for
} // CleanupGeoSet


// -- EOF

