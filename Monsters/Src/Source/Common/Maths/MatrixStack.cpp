// ----------------------------------------------------------------------------
// File: MatrixStack.cpp
// Desc: Manages a matrix stack
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Maths/MatrixStack.h"
#include "Maths/Vec3.h"
#include "Maths/Matrix.h"


// ----------------------------------------------------------------------------
// Name: MatrixStack::MatrixStack
// Desc: Constructor
// ----------------------------------------------------------------------------
MatrixStack::MatrixStack()
{
  if (FAILED(D3DXCreateMatrixStack(0, &m_pmatrix_stack)))
    m_pmatrix_stack = 0;
} // MatrixStack


// ----------------------------------------------------------------------------
// Name: MatrixStack::~MatrixStack
// Desc: Destructor
// ----------------------------------------------------------------------------
MatrixStack::~MatrixStack()
{
  if (m_pmatrix_stack)
  {
    m_pmatrix_stack->Release();
    m_pmatrix_stack = 0;
  } // if
} // ~MatrixStack


// ----------------------------------------------------------------------------
// Name: MatrixStack::IsValid
// Desc: Check if the matrix stack is valid
// Retn: bool - true if valid
// ----------------------------------------------------------------------------
bool MatrixStack::IsValid()
{
  return (m_pmatrix_stack != 0);
} // IsValid


// ----------------------------------------------------------------------------
// Name: MatrixStack::GetTop
// Desc: Get the matrix at the top of the stack
// ----------------------------------------------------------------------------
Matrix &MatrixStack::GetTop()
{
  return *(reinterpret_cast<Matrix *>(m_pmatrix_stack->GetTop()));
} // GetTop


// ----------------------------------------------------------------------------
// Name: MatrixStack::LoadIdentity
// Desc: Load the identity matrix
// ----------------------------------------------------------------------------
bool MatrixStack::LoadIdentity()
{
  return m_pmatrix_stack->LoadIdentity() == TRUE;
} // LoadIdentity


// ----------------------------------------------------------------------------
// Name: MatrixStack::LoadMatrix
// Desc: Load the matrix onto the stack
// Parm: const Matrix &m - the matrix
// ----------------------------------------------------------------------------
bool MatrixStack::LoadMatrix(const Matrix &m)
{
  return m_pmatrix_stack->LoadMatrix(&m) == TRUE;
} // LoadMatrix


// ----------------------------------------------------------------------------
// Name: MatrixStack::MultMatrix
// Desc: Multiply the matrix onto the stack
// Parm: const Matrix &m - the matrix
// ----------------------------------------------------------------------------
bool MatrixStack::MultMatrix(const Matrix &m)
{
  return m_pmatrix_stack->MultMatrix(&m) == TRUE;
} // MultMatrix


// ----------------------------------------------------------------------------
// Name: MatrixStack::MultMatrixLocal
// Desc: Multiply the matrix locally onto the stack
// Parm: const Matrix &m - the matrx
// ----------------------------------------------------------------------------
bool MatrixStack::MultMatrixLocal(const Matrix &m)
{
  return m_pmatrix_stack->MultMatrixLocal(&m) == TRUE;
} // MultMatrixLocal


// ----------------------------------------------------------------------------
// Name: MatrixStack::Pop
// Desc: Pop a matrix from the stack
// ----------------------------------------------------------------------------
void MatrixStack::Pop()
{
  m_pmatrix_stack->Pop();
} // Pop


// ----------------------------------------------------------------------------
// Name: MatrixStack::Push
// Desc: Push a matrix onto the stack
// ----------------------------------------------------------------------------
void MatrixStack::Push()
{
  m_pmatrix_stack->Push();
} // Push


// ----------------------------------------------------------------------------
// Name: MatrixStack::RotateAxis
// Desc: Set the top matrix to be a rotation matrix
// Parm: const Vec3 &v - the vector
// Parm: the angle   - the angle
// ----------------------------------------------------------------------------
bool MatrixStack::RotateAxis(const Vec3 &v, float angle)
{
  return m_pmatrix_stack->RotateAxis(&v, angle) == TRUE;
} // RotateAxis


// ----------------------------------------------------------------------------
// Name: MatrixStack::RotateAxisLocal
// Desc: Set the top matrix to be a local rotation matrix
// Parm: const Vec3 &v - the vector
// Parm: float angle   - the angle
// ----------------------------------------------------------------------------
bool MatrixStack::RotateAxisLocal(const Vec3 &v, float angle)
{
  return m_pmatrix_stack->RotateAxisLocal(&v, angle) == TRUE;
} // RotateAxisLocal


// ----------------------------------------------------------------------------
// Name: MatrixStack::RotateYawPitchRoll
// Desc: Set the top matrix to be a HPR rotation matrix
// Parm: float yaw    - the heading
// Parm: float pitch  - the pitch
// Parm: float roll   - thr roll
// ----------------------------------------------------------------------------
bool MatrixStack::RotateYawPitchRoll(float yaw, float pitch, float roll)
{
  return m_pmatrix_stack->RotateYawPitchRoll(yaw, pitch, roll) == TRUE;
} // RotateYawPitchRoll


// ----------------------------------------------------------------------------
// Name: MatrixStack::RotateYawPitchRollLocal
// Desc: Set the top matrix to be local HPR matrix
// Parm: float yaw    - the heading
// Parm: float pitch  - the pitch
// Parm: float roll   - the roll
// ----------------------------------------------------------------------------
bool MatrixStack::RotateYawPitchRollLocal(float yaw, float pitch, float roll)
{
  return m_pmatrix_stack->RotateYawPitchRollLocal(yaw, pitch, roll) == TRUE;
} // RotateYawPitchRollLocal


// ----------------------------------------------------------------------------
// Name: MatrixStack::Scale
// Desc: Set the top matrix to be scaling matrix
// Parm: float x  - the x scale
// Parm: float y  - the y scale
// Parm: float z  - the z scale
// ----------------------------------------------------------------------------
bool MatrixStack::Scale(float x, float y, float z)
{
  return m_pmatrix_stack->Scale(x, y, z) == TRUE;
} // Scale


// ----------------------------------------------------------------------------
// Name: MatrixStack::ScaleLocal
// Desc: Set the top matrix to be local scale matrix
// Parm: float x  - the x scale
// Parm: float y  - the y scale
// Parm: float z  - the z scale
// ----------------------------------------------------------------------------
bool MatrixStack::ScaleLocal(float x, float y, float z)
{
  return m_pmatrix_stack->ScaleLocal(x, y, z) == TRUE;
} // ScaleLocal


// ----------------------------------------------------------------------------
// Name: MatrixStack::Translate
// Desc: Set the top matrix to be a translation matrix
// Parm: float x  - the x translation
// Parm: float y  - the y translation 
// Parm: float z  - the z translation
// ----------------------------------------------------------------------------
bool MatrixStack::Translate(float x, float y, float z)
{
  return m_pmatrix_stack->Translate(x, y, z) == TRUE;
} // Translate


// ----------------------------------------------------------------------------
// Name: MatrixStack::TranslateLocal
// Desc: Set the top matrix to be a local translation matrix
// Parm: float x  - the x translation
// Parm: float y  - the y translation 
// Parm: float z  - the z translation
// ----------------------------------------------------------------------------
bool MatrixStack::TranslateLocal(float x, float y, float z)
{
  return m_pmatrix_stack->TranslateLocal(x, y, z) == TRUE;
} // TranslateLocal


// -- EOF

