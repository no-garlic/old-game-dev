//******************************************************************************
//
//  File:           CullTraverser.cpp
//
//  Description:    Traverses the scenegraph and adds the visible geometry to 
//                  the appropriate render bin
//
//  Reference:      Engine
//
//  Author:         Michael Petrou
//
//  (C) Copyright:  Petrou Software Pty Ltd, 2003
//
//******************************************************************************

#include "Scenegraph/CullTraverser.h"
#include "Common/Logging.h"
#include "Scenegraph/Node.h"
#include "Scenegraph/Group.h"
#include "Scenegraph/DCS.h"
#include "Scenegraph/Switch.h"
#include "Scenegraph/Sequence.h"
#include "Scenegraph/Geode.h"
#include "Scenegraph/GeoSet.h"
#include "Engine/Mesh.h"
#include "Engine/RenderBin.h"
#include "Engine/Camera.h"


// ----------------------------------------------------------------------------
// Traversal result types
// ----------------------------------------------------------------------------
static const int TRAV_CONTINUE  = 1;    // Continue traversing down
static const int TRAV_PRUNE     = 2;    // Stop traversal


// ----------------------------------------------------------------------------
// Name: CullTraverser::CullTraverser
// Desc: Constructor
// ----------------------------------------------------------------------------
CullTraverser::CullTraverser()
{
    Reset();
} // CullTraverser


// ----------------------------------------------------------------------------
// Name: CullTraverser::~CullTraverser
// Desc: Destructor
// ----------------------------------------------------------------------------
CullTraverser::~CullTraverser()
{
} // ~CullTraverser


// ----------------------------------------------------------------------------
// Name: CullTraverser::Reset
// Desc: Reset the traverser
// ----------------------------------------------------------------------------
void CullTraverser::Reset()
{
    m_matrix_stack.LoadIdentity();
} // Reset


// ----------------------------------------------------------------------------
// Name: CullTraverser::Traverse
// Desc: Traverse the given node (recursively) and add the visible geometry to 
//       the appropriate render bin
// Parm: Node *pnode - the node to begin the traversal at
// ----------------------------------------------------------------------------
void CullTraverser::Traverse(Node *pnode)
{
    if (pnode)
    {
        // Get the current matrix
        Matrix this_matrix = m_matrix_stack.GetTop();

        // Do we need matrix operations
        bool need_mat_op = pnode->IsExactType(Node::GetDCSType());

        // Get the new world matrix
        if (need_mat_op)
        {
            m_matrix_stack.Push();
            m_matrix_stack.MultMatrix(*static_cast<DCS *>(pnode)->GetMatrixPtr());
        } // if

        // Test the node
        if (!pnode->GetCullingEnabled() || CullTest(pnode->GetBSphere(), this_matrix) == TRAV_CONTINUE)
        {
            if (pnode->IsOfType(Node::GetGeodeType()))
            {
                // Add the child to be rendered
                Geode *pgeode = static_cast<Geode *>(pnode);

                // Iterate through all geosets
                for (size_t i = 0; i < pgeode->GetNumGeoSets(); i++)
                {
                    GeoSet *pgeoset = pgeode->GetGeoSet(i);

                    // Test the geoset
                    if (CullTest(pgeoset->GetBSphere(), this_matrix) != TRAV_CONTINUE)
                        continue;

                    // Add all meshes in the geoset to the appropriate render bin
                    std::vector<GeoSet::Record> &mesh_vec = pgeoset->GetMeshVec();
                    std::vector<GeoSet::Record>::iterator iter = mesh_vec.begin();
                    for (; iter != mesh_vec.end(); ++iter)
                    {
                        GeoSet::Record &record = *iter;

                        // Test the mesh
                        Sphere s;
                        record.pmesh->GetBounds(s);
                        if (CullTest(s, this_matrix) != TRAV_CONTINUE)
                            continue;

                        RenderBinSingleton::Instance().AddRenderTarget(record.pmesh, record.mat_id, m_matrix_stack.GetTop());
                    } // for
                } // for
            } // if
            else if (pnode->IsOfType(Node::GetSwitchType()))
            {
                // Traverse the children
                Switch *pswitch = static_cast<Switch *>(pnode);
                if (pswitch->GetVal())
                {
                    for (size_t i = 0; i < pswitch->GetNumChildren(); i++)
                        Traverse(pswitch->GetChild(i));
                } // if
            } // else if
            else if (pnode->IsOfType(Node::GetGroupType()))
            {
                // Traverse the children
                Group *pgroup = static_cast<Group *>(pnode);
                for (size_t i = 0; i < pgroup->GetNumChildren(); i++)
                    Traverse(pgroup->GetChild(i));
            } // if
        } // if

        // Restore the pervoius matrix
        if (need_mat_op)
            m_matrix_stack.Pop();
    } // if
} // Traverse


// ----------------------------------------------------------------------------
// Name: CullTraverser::CullTest
// Desc: Test the given node for visibility within the frustum
// Parm: Node *pnode           - the node to test
// Parm: const Matrix &matrix  - the world matrix where the node is
// Retn: int                   - the return code (TRAV_CONTINUE or TRAV_PRUNE)
// ----------------------------------------------------------------------------
int CullTraverser::CullTest(const Sphere &sphere, const Matrix &matrix)
{
    // Test the sphere against the frustum
    if (CameraSingleton::Instance().SphereInFrustum(sphere, matrix))
        return TRAV_CONTINUE;
    else
        return TRAV_PRUNE;
} // CullTest


// -- EOF


