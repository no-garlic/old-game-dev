// ----------------------------------------------------------------------------
// File: IntersectionTraverser.h
// Desc: Traverses a scenegraph and tests for a ray intersection with a bounding
//       sphere of a mesh.
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _INTERSECTION_TRAVERSER_H
#define _INTERSECTION_TRAVERSER_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include "Math/Types.h"
#include "Math/MatrixStack.h"
#include "Math/Intersect.h"
#include "Scenegraph/Node.h"


// ----------------------------------------------------------------------------
// Name: IntersectionTraverser (class)
// Desc: Traverses a scenegraph and tests for a ray intersection with a bounding
//       sphere of a mesh.
// ----------------------------------------------------------------------------
class IntersectionTraverser
{
public:
    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
     IntersectionTraverser();
    ~IntersectionTraverser();


    // ------------------------------------------------------------------------
    // Public functions
    // ------------------------------------------------------------------------
    void Reset();
    bool Traverse(Node *pnode, const Ray &ray, std::vector<RayHit> &hit_info);


private:
    // ------------------------------------------------------------------------
    // Private functions
    // ------------------------------------------------------------------------
    int IntersectionTest(Node *pnode, const Ray &ray, 
        std::vector<RayHit> &hit_info, const Matrix &matrix);


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    MatrixStack     m_matrix_stack;

}; // class IntersectionTraverser


#endif // _INTERSECTION_TRAVERSER_H

// -- EOF


