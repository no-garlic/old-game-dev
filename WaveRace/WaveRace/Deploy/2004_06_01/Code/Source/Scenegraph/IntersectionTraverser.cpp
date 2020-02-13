// ----------------------------------------------------------------------------
// File: IntersectionTraverser.cpp
// Desc: Traverses a scenegraph and tests for a ray intersection with a bounding
//       sphere of a mesh.
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Scenegraph/IntersectionTraverser.h"
#include "Common/Logging.h"
#include "Scenegraph/Node.h"
#include "Scenegraph/Group.h"
#include "Scenegraph/DCS.h"
#include "Scenegraph/Switch.h"
#include "Scenegraph/Sequence.h"
#include "Scenegraph/Geode.h"
#include "Scenegraph/GeoSet.h"
#include "Engine/Mesh.h"


// ----------------------------------------------------------------------------
// Traversal codes
// ----------------------------------------------------------------------------
static const int TRAV_CONTINUE  = 1;    // Continue traversing down
static const int TRAV_COMPLETE  = 2;    // Traversal finished
static const int TRAV_PRUNE     = 3;    // Stop traversal


// ----------------------------------------------------------------------------
// Name: IntersectionTraverser::IntersectionTraverser
// Desc: Constructor
// ----------------------------------------------------------------------------
IntersectionTraverser::IntersectionTraverser()
{
    Reset();
} // IntersectionTraverser


// ----------------------------------------------------------------------------
// Name: IntersectionTraverser::~IntersectionTraverser
// Desc: Destructor
// ----------------------------------------------------------------------------
IntersectionTraverser::~IntersectionTraverser()
{
} // ~IntersectionTraverser


// ----------------------------------------------------------------------------
// Name: IntersectionTraverser::Reset
// Desc: Reset the traverser
// ----------------------------------------------------------------------------
void IntersectionTraverser::Reset()
{
    m_matrix_stack.LoadIdentity();
} // Reset


// ----------------------------------------------------------------------------
// Name: IntersectionTraverser::Traverse
// Desc: Traverses teh node and all children to look for an intersection between
//       a ray and a triangle.  Bounding sphere testing is done to speed up the 
//       process
// Parm: Node *pnode                    - the node to traverse
// Parm: const Ray &ray                 - the ray
// Parm: std::vector<RayHit> &hit_info  - the hit info vector to store the 
//       results
// Retn: bool                           - true if there was at least 1 hit
// ----------------------------------------------------------------------------
bool IntersectionTraverser::Traverse(Node *pnode, const Ray &ray, std::vector<RayHit> &hit_info)
{
    // Check that we have a node to traverse
    if (!pnode)
        return false;

    // Do we need matrix operations for this loop
    bool need_mat_op = pnode->IsExactType(Node::GetDCSType());

    // Store the current matrix for this iteration on the stack
    Matrix this_matrix = m_matrix_stack.GetTop();

    // Get the new world matrix if we need to
    if (need_mat_op)
    {
        m_matrix_stack.Push();
        m_matrix_stack.MultMatrix(*static_cast<DCS *>(pnode)->GetMatrixPtr());
    } // if

    // Test the node for intersection with the ray
    int tr = IntersectionTest(pnode, ray, hit_info, this_matrix);
    if (tr == TRAV_COMPLETE)
        return true;

    // Continue to traverse teh children
    if (tr == TRAV_CONTINUE)
    {
        if (pnode->IsOfType(Node::GetSwitchType()))
        {
            // Traverse the children if enabled
            Switch *pswitch = static_cast<Switch *>(pnode);
            if (pswitch->GetVal())
            {
                for (size_t i = 0; i < pswitch->GetNumChildren(); i++)
                    Traverse(pswitch->GetChild(i), ray, hit_info);
            } // if
        } // if
        else if (pnode->IsOfType(Node::GetGroupType()))
        {
            // Traverse the children
            Group *pgroup = static_cast<Group *>(pnode);
            for (size_t i = 0; i < pgroup->GetNumChildren(); i++)
                Traverse(pgroup->GetChild(i), ray, hit_info);
        } // if
    } // if

    // Restore the pervoius matrix
    if (need_mat_op)
        m_matrix_stack.Pop();

    return (!hit_info.empty());
} // Traverse


// ----------------------------------------------------------------------------
// Name: IntersectionTraverser::IntersectionTest
// Desc: Test a node for intersection with the ray
// Parm: Node *pnode                    - The node to test
// Parm: const Ray &ray                 - the ray to intersect
// Parm: std::vector<RayHit> &hit_info  - the hit info to store the hits
// Parm: const Matrix &matrix           - the world matrix of the node
// Retn: int                            - the traversal code
// ----------------------------------------------------------------------------
int IntersectionTraverser::IntersectionTest(Node                *pnode, 
                                            const Ray           &ray, 
                                            std::vector<RayHit> &hit_info, 
                                            const Matrix        &matrix)
{
    // If intersection is disabled, dont go any deeper
    if (!pnode->GetIntersectionEnabled())
        return TRAV_PRUNE;

    // Test an intersection with the sphere from the node
    if (pnode->GetBSphere().RayIntersects(ray, matrix) <= 0)
        return TRAV_PRUNE;

    // There was a hit, but it was a group type so we
    // continue to iterate to the children
    if (!pnode->IsExactType(Node::GetGeodeType()))
        return TRAV_CONTINUE;

    // Cast the node as a geode and then test
    // all geosets in the geode
    Geode *pgeode       = (Geode *) pnode;
    size_t num_geosets  = pgeode->GetNumGeoSets();

    // Test all geosets
    for (size_t i = 0; i < num_geosets; i++)
    {
        // Get the geoset, and all meshes in the geoset
        GeoSet *pgeoset                         = pgeode->GetGeoSet(i);
        std::vector<GeoSet::Record> &mesh_vec   = pgeoset->GetMeshVec();

        // See if the ray intersects with the geoset
        if (pgeoset->GetBSphere().RayIntersects(ray, matrix) <=0)
            continue;

        // Test the ray against all meshes in the geoset
        std::vector<GeoSet::Record>::iterator iter = mesh_vec.begin();
        for (; iter != mesh_vec.end(); ++iter)
        {
            Mesh *pmesh = (*iter).pmesh;
            Sphere sphere;
            pmesh->GetBounds(sphere);

            // Test the ray against the spehre from the mesh
            if (sphere.RayIntersects(ray, matrix) <= 0)
                continue;

            // Create a ray in model space
            Ray model_space_ray(ray, matrix);

            const std::vector<Triangle> &triangles      = pmesh->GetMeshTriangles();
            std::vector<Triangle>::const_iterator iter2 = triangles.begin();
            for (; iter2 != triangles.end(); ++iter2)
            {
                float u, v, t;
                if (model_space_ray.IntersectsTriangle(*iter2, u, v, t))
                {
                    RayHit hit;

                    // Store the u and v tangents, and the distance to 
                    // the intersection point
                    hit.u_tangent       = u;
                    hit.v_tangent       = v;
                    hit.distance        = t;

                    // Store the name of the mesh we have intersected
                    // with
                    hit.mesh_name       = pmesh->GetName();

                    // Store the world and model matricies
                    hit.matrix_w        = matrix;
                    hit.matrix_m.Inverse(hit.matrix_w);

                    // Store the triangle in world space and model
                    // space
                    hit.triangle_m      = *iter2;
                    hit.triangle_w.p0.TransformCoord(hit.triangle_m.p0, hit.matrix_w);
                    hit.triangle_w.p1.TransformCoord(hit.triangle_m.p1, hit.matrix_w);
                    hit.triangle_w.p2.TransformCoord(hit.triangle_m.p2, hit.matrix_w);

                    // Calculate the triangle normal in model space
                    Vec3 vm0, vm1;
                    vm0.Subtract(hit.triangle_m.p1, hit.triangle_m.p0);
                    vm1.Subtract(hit.triangle_m.p2, hit.triangle_m.p0);
                    hit.normal_m.Cross(vm1, vm0);
                    hit.normal_m.Normalize(hit.normal_m);

                    // Calculate the triangle normal in world space
                    Vec3 vw0, vw1;
                    vw0.Subtract(hit.triangle_w.p1, hit.triangle_w.p0);
                    vw1.Subtract(hit.triangle_w.p2, hit.triangle_w.p0);
                    hit.normal_w.Cross(vw1, vw0);
                    hit.normal_w.Normalize(hit.normal_w);

                    // Store the ray hit
                    hit_info.push_back(hit);
                } // if (intersect triangle)

            } // for (iterate all triangles in mesh)
        } // for (iterate all meshes in geoset)
    } // for (iterate all geosets in geode)

    return TRAV_CONTINUE;
} // IntersectionTest


// -- EOF


