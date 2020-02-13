// ----------------------------------------------------------------------------
// File: CullTraverser.h
// Desc: Traverses the scenegraph and adds the visible geometry to the 
//       appropriate render bin
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _TRAVERSER_H
#define _TRAVERSER_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include "Math/Types.h"
#include "Math/MatrixStack.h"
#include "Math/Frustum.h"
#include "Math/Sphere.h"
#include "Scenegraph/Node.h"


// ----------------------------------------------------------------------------
// Name: CullTraverser (class)
// Desc: Traverses the scenegraph and adds the visible geometry to the 
//       appropriate render bin
// ----------------------------------------------------------------------------
class CullTraverser
{
public:
    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
     CullTraverser();
    ~CullTraverser();

 
    // ------------------------------------------------------------------------
    // Public functions
    // ------------------------------------------------------------------------
    void Reset();
    void Traverse(Node *pnode);


private:
    // ------------------------------------------------------------------------
    // Private functions
    // ------------------------------------------------------------------------
    int CullTest(const Sphere &sphere, const Matrix &matrix);



    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    MatrixStack     m_matrix_stack; // The matrix stack


}; // class CullTraverser


#endif // _TRAVERSER_H

// -- EOF


