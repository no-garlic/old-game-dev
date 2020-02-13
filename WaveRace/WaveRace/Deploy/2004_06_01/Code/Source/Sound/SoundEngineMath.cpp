
#include "Sound/SoundEngineMath.h"


using namespace SpatialSound;


/****************************************************************************
 * class c_Vector3
 ****************************************************************************/

/* Constructor */
c_Vector3::c_Vector3(float p_fX, float p_fY, float p_fZ)
{
    x = p_fX;
    y = p_fY;
    z = p_fZ;
}

/* Addition operator */
c_Vector3 c_Vector3::operator+(c_Vector3 &v)
{
    return c_Vector3(x + v.x, y + v.y, z + v.z);
}

/* Subtration operator */
c_Vector3 c_Vector3::operator-(c_Vector3 &v)
{
    return c_Vector3(x - v.x, y - v.y, z - v.z);
}

/* Multiplication operator */
c_Vector3 c_Vector3::operator*(c_Vector3 &v)
{
    return c_Vector3(x*v.x + y*v.x + z*v.x,
                      x*v.y + y*v.y + z*v.y,
                      x*v.z + y*v.z + z*v.z);
}

/* Scalar Multiplication operator */
c_Vector3 c_Vector3::operator*(float f)
{
    return c_Vector3(x*f, y*f, z*f);
}

/* Componentwise multiply */
void c_Vector3::ComponentMultiply(c_Vector3 &v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
}

/* Scalar Division operator */
c_Vector3 c_Vector3::operator/(float f)
{
    return c_Vector3(x/f, y/f, z/f);
}

/* Size of the vector */
float c_Vector3::Size(void)
{
    return sqrtf(x*x + y*y + z*z);
}

/* Normalize */
void c_Vector3::Normalize(void)
{
    float a;
    a = sqrtf(x*x + y*y + z*z);
    if (a == 0.0f)
    {
        return;
    }
    a = 1.0f / a;
    x *= a;
    y *= a;
    z *= a;
}


/* end class c_Vector3 */

/* Calculate the magnitude */
float SpatialSound::Magnitude(c_Vector3 &v)
{
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

/* Dot product operator */
float SpatialSound::DotProduct(c_Vector3 &a, c_Vector3 &b)
{
    return (a.x*b.x + a.y*b.y + a.z*b.z);
}

/* Dot product operator */
float SpatialSound::DotProduct(c_Vector3 &a)
{
    return (a.x*a.x + a.y*a.y + a.z*a.z);
}

/* Cross product operator */
c_Vector3 SpatialSound::CrossProduct(c_Vector3 &p, c_Vector3 &q)
{
    return c_Vector3(p.y*q.z - p.z*q.y, 
                     p.z*q.x - p.x*q.z,
                     p.x*q.y - p.y*q.x);
}

/* Projection of P onto Q */
void SpatialSound::ProjPontoQ(c_Vector3 &p, c_Vector3 &q, c_Vector3 &r)
{
    r = q * (SpatialSound::DotProduct(p, q) / SpatialSound::DotProduct(q));
}

/* Perpendicular component of P onto Q */
void SpatialSound::PerpPontoQ(c_Vector3 &p, c_Vector3 &q, c_Vector3 &r)
{
    r = p - (q * (SpatialSound::DotProduct(p, q) / SpatialSound::DotProduct(q)));
}


/****************************************************************************
 * class c_Matrix3x3
 ****************************************************************************/

/* Constructor (Column-Major) */
c_Matrix3x3::c_Matrix3x3(float a, float b, float c,
                       float d, float e, float f,
                       float g, float h, float i)
{
    data[0][0] = a;
    data[0][1] = b;
    data[0][2] = c;
    data[1][0] = d;
    data[1][1] = e;
    data[1][2] = f;
    data[2][0] = g;
    data[2][1] = h;
    data[2][2] = i;
}

/* Addition operator */
c_Matrix3x3 c_Matrix3x3::operator+(c_Matrix3x3 &m)
{
    return c_Matrix3x3( data[0][0] + m.data[0][0], data[0][1] + m.data[0][1], data[0][2] + m.data[0][2],
                        data[1][0] + m.data[1][0], data[1][1] + m.data[1][1], data[1][2] + m.data[1][2],
                        data[2][0] + m.data[2][0], data[2][1] + m.data[2][1], data[2][2] + m.data[2][2] );
}

/* Subtraction operator */
c_Matrix3x3 c_Matrix3x3::operator-(c_Matrix3x3 &m)
{
    return c_Matrix3x3( data[0][0] - m.data[0][0], data[0][1] - m.data[0][1], data[0][2] - m.data[0][2],
                        data[1][0] - m.data[1][0], data[1][1] - m.data[1][1], data[1][2] - m.data[1][2],
                        data[2][0] - m.data[2][0], data[2][1] - m.data[2][1], data[2][2] - m.data[2][2] );
}

/* Multiplication operator */
c_Matrix3x3 c_Matrix3x3::operator*(c_Matrix3x3 &m)
{
    c_Matrix3x3 A;

    int i;
    int j;
    for (i=0;i<3;i++)
    {
        for (j=0;j<3;j++)
        {
            /* init to zero [column][row] */
            A.data[j][i] = 0;
            int k; 
            for (k=0;k<3;k++)
            {
                A.data[j][i] += data[k][i] * m.data[j][k];
            }
        }
    }

    return A;
}

/* Vector Multiplication operator */
c_Vector3 c_Matrix3x3::operator*(c_Vector3 &v)
{
    c_Vector3 a;

//  M*v (in general this is not what we want)
//  a.x = (v.x * data[0][0]) + (v.y * data[0][1]) + (v.z * data[0][2]);
//  a.y = (v.x * data[1][0]) + (v.y * data[1][1]) + (v.z * data[1][2]);
//  a.z = (v.x * data[2][0]) + (v.y * data[2][1]) + (v.z * data[2][2]);

//  M*vT (in general this is what we want)
    a.x = (v.x * data[0][0]) + (v.y * data[1][0]) + (v.z * data[2][0]);
    a.y = (v.x * data[0][1]) + (v.y * data[1][1]) + (v.z * data[2][1]);
    a.z = (v.x * data[0][2]) + (v.y * data[1][2]) + (v.z * data[2][2]);

    return a;
}

/* Scalar Multiplication operator */
c_Matrix3x3 c_Matrix3x3::operator*(float f)
{
    return c_Matrix3x3( data[0][0] * f, data[0][1] * f, data[0][2] * f,
                        data[1][0] * f, data[1][1] * f, data[1][2] * f,
                        data[2][0] * f, data[2][1] * f, data[2][2] * f );
}

/* Scalar Division operator */
c_Matrix3x3 c_Matrix3x3::operator/(float f)
{
    return c_Matrix3x3( data[0][0] / f, data[0][1] / f, data[0][2] / f,
                        data[1][0] / f, data[1][1] / f, data[1][2] / f,
                        data[2][0] / f, data[2][1] / f, data[2][2] / f );
}

/* Set to Identity */
void c_Matrix3x3::SetToIdentity(void)
{
    data[0][0] = 1.0f;
    data[0][1] = 0.0f;
    data[0][2] = 0.0f;
    data[1][0] = 0.0f;
    data[1][1] = 1.0f;
    data[1][2] = 0.0f;
    data[2][0] = 0.0f;
    data[2][1] = 0.0f;
    data[2][2] = 1.0f;
}

/* Calc the determinant */
float c_Matrix3x3::Determinant(void)
{
    return ( data[0][0]*(data[1][1]*data[2][2] - data[2][1]*data[1][2]) -
             data[1][0]*(data[0][1]*data[2][2] - data[2][1]*data[0][2]) +
             data[2][0]*(data[0][1]*data[1][2] - data[1][1]*data[0][2]) );
}


/* Inverse */
bool c_Matrix3x3::Inverse(c_Matrix3x3 &m)
{
    float det;
    det = Determinant();

    if (det == 0.0f)
    {
        /* cannot calc inverse of matrix with determinant of zero */
        return (false);
    }

    m.data[0][0] = (data[1][1]*data[2][2] - data[2][1]*data[1][2]) / det;
    m.data[1][0] = (data[2][0]*data[1][2] - data[1][0]*data[2][2]) / det;
    m.data[2][0] = (data[1][0]*data[2][1] - data[2][0]*data[1][1]) / det;
    m.data[0][1] = (data[2][1]*data[0][2] - data[0][1]*data[2][2]) / det;
    m.data[1][1] = (data[0][0]*data[2][2] - data[2][0]*data[0][2]) / det;
    m.data[2][1] = (data[2][0]*data[0][1] - data[0][0]*data[2][1]) / det;
    m.data[0][2] = (data[0][1]*data[1][2] - data[1][1]*data[0][2]) / det;
    m.data[1][2] = (data[1][0]*data[0][2] - data[0][0]*data[1][2]) / det;
    m.data[2][2] = (data[0][0]*data[1][1] - data[1][0]*data[0][1]) / det;

    return (true);
}

/* end class c_Matrix3x3 */


/****************************************************************************
 * class c_Quaternion
 ****************************************************************************/

/* Calc the matrix representation of the c_Quaternion */
void c_Quaternion::MatrixRep(c_Matrix3x3 *m)
{
    /* Note: Column-major ordering of 3x3 Matrix */
    m->data[0][0] = 1.0f-(2.0f*y*y)-(2.0f*z*z);
    m->data[0][1] = (2.0f*x*y) + (2.0f*w*z);
    m->data[0][2] = (2.0f*x*z) - (2.0f*w*y);
    m->data[1][0] = (2.0f*x*y) - (2.0f*w*z);
    m->data[1][1] = 1.0f - (2.0f*x*x) - (2.0f*z*z);
    m->data[1][2] = (2.0f*y*z) + (2.0f*w*x);
    m->data[2][0] = (2.0f*x*z) + (2.0f*w*y);
    m->data[2][1] = (2.0f*y*z) - (2.0f*w*x);
    m->data[2][2] = 1.0f - (2.0f*x*x) - (2.0f*y*y);
}

/* end class c_Quaternion */

/* return quaternion for the given euler rotation */
c_Quaternion SpatialSound::QuaternionEulerRotation(float p_fYaw, float p_fPitch, float p_fRoll)
{
    float cosY = cosf(p_fYaw / 2.0f);
    float sinY = sinf(p_fYaw / 2.0f);
    float cosP = cosf(p_fPitch / 2.0f);
    float sinP = sinf(p_fPitch / 2.0f);
    float cosR = cosf(p_fRoll / 2.0f);
    float sinR = sinf(p_fRoll / 2.0f);
    return c_Quaternion(cosR*sinP*cosY + sinR*cosP*sinY,
                        cosR*cosP*sinY - sinR*sinP*cosY,
                        sinR*cosP*cosY - cosR*sinP*sinY,
                        cosR*cosP*cosY + sinR*sinP*sinY);
}

