// ----------------------------------------------------------------------------
// File: MatrixStack.cpp
// Desc: Manages a matrix stack
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Math/MatrixStack.h"
#include "Math/Vec3.h"
#include "Math/Matrix.h"


MatrixStack::MatrixStack()
{
    if (FAILED(D3DXCreateMatrixStack(0, &m_pmatrix_stack)))
        m_pmatrix_stack = 0;
} // MatrixStack


MatrixStack::~MatrixStack()
{
    if (m_pmatrix_stack)
    {
        m_pmatrix_stack->Release();
        m_pmatrix_stack = 0;
    } // if
} // ~MatrixStack


bool MatrixStack::IsValid()
{
    return (m_pmatrix_stack != 0);
} // IsValid


Matrix &MatrixStack::GetTop()
{
    return *(reinterpret_cast<Matrix *>(m_pmatrix_stack->GetTop()));
} // GetTop


bool MatrixStack::LoadIdentity()
{
    return m_pmatrix_stack->LoadIdentity() == TRUE;
} // LoadIdentity


bool MatrixStack::LoadMatrix(const Matrix &m)
{
    return m_pmatrix_stack->LoadMatrix(&m) == TRUE;
} // LoadMatrix


bool MatrixStack::MultMatrix(const Matrix &m)
{
    return m_pmatrix_stack->MultMatrix(&m) == TRUE;
} // MultMatrix


bool MatrixStack::MultMatrixLocal(const Matrix &m)
{
    return m_pmatrix_stack->MultMatrixLocal(&m) == TRUE;
} // MultMatrixLocal


void MatrixStack::Pop()
{
    m_pmatrix_stack->Pop();
} // Pop


void MatrixStack::Push()
{
    m_pmatrix_stack->Push();
} // Push


bool MatrixStack::RotateAxis(const Vec3 &v, float angle)
{
    return m_pmatrix_stack->RotateAxis(&v, angle) == TRUE;
} // RotateAxis


bool MatrixStack::RotateAxisLocal(const Vec3 &v, float angle)
{
    return m_pmatrix_stack->RotateAxisLocal(&v, angle) == TRUE;
} // RotateAxisLocal


bool MatrixStack::RotateYawPitchRoll(float yaw, float pitch, float roll)
{
    return m_pmatrix_stack->RotateYawPitchRoll(yaw, pitch, roll) == TRUE;
} // RotateYawPitchRoll


bool MatrixStack::RotateYawPitchRollLocal(float yaw, float pitch, float roll)
{
    return m_pmatrix_stack->RotateYawPitchRollLocal(yaw, pitch, roll) == TRUE;
} // RotateYawPitchRollLocal


bool MatrixStack::Scale(float x, float y, float z)
{
    return m_pmatrix_stack->Scale(x, y, z) == TRUE;
} // Scale


bool MatrixStack::ScaleLocal(float x, float y, float z)
{
    return m_pmatrix_stack->ScaleLocal(x, y, z) == TRUE;
} // ScaleLocal


bool MatrixStack::Translate(float x, float y, float z)
{
    return m_pmatrix_stack->Translate(x, y, z) == TRUE;
} // Translate


bool MatrixStack::TranslateLocal(float x, float y, float z)
{
    return m_pmatrix_stack->TranslateLocal(x, y, z) == TRUE;
} // TranslateLocal


// -- EOF

