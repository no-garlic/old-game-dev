// ----------------------------------------------------------------------------
// File: MatrixStack.h
// Desc: Matrix stack for traversing hierarchies of matricies
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _MATRIXSTACK_H
#define _MATRIXSTACK_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/Types.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class Matrix;
class Vec3;


// ----------------------------------------------------------------------------
// Name: MatrixStack (class)
// Desc: For traversing hierarchies of matricies
// ----------------------------------------------------------------------------
class MatrixStack
{
public:
    // ------------------------------------------------------------------------
    // Constructors
    // ------------------------------------------------------------------------
     MatrixStack();
    ~MatrixStack();


    // ------------------------------------------------------------------------
    // Get the matrix on the top of the stack
    // ------------------------------------------------------------------------
    Matrix &GetTop();


    // ------------------------------------------------------------------------
    // Member functions
    // ------------------------------------------------------------------------
    bool    IsValid();
    bool    LoadIdentity();
    bool    LoadMatrix(const Matrix &m);
    bool    MultMatrix(const Matrix &m);
    bool    MultMatrixLocal(const Matrix &m);
    void    Pop();
    void    Push();
    bool    RotateAxis(const Vec3 &v, float angle);
    bool    RotateAxisLocal(const Vec3 &v, float angle);
    bool    RotateYawPitchRoll(float yaw, float pitch, float roll);
    bool    RotateYawPitchRollLocal(float yaw, float pitch, float roll);
    bool    Scale(float x, float y, float z);
    bool    ScaleLocal(float x, float y, float z);
    bool    Translate(float x, float y, float z);
    bool    TranslateLocal(float x, float y, float z);

private:
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    ID3DXMatrixStack    *m_pmatrix_stack;

}; // class MatrixStack


#endif //_MATRIXSTACK_H

// -- EOF

