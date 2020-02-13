

#ifndef OPEN_AL_SOUND_ENGINE_MATH_H
#define OPEN_AL_SOUND_ENGINE_MATH_H

#include <math.h>
#include "Math/Types.h"
#include "Common/Utilities.h"

namespace SpatialSound
{

    /* constant definitions */
//    const float EPSILON         = 0.000000000001f;
//    const float PI              = 3.1415926535897932384626433832795f;
    const float PIDIV2          = D3DX_PI / 2.0f;
    const float DEG2RAD         = 2.0f*D3DX_PI/360.0f;
    const float RAD2DEG         = 1.0f/DEG2RAD;
    const float ONEONROOTTWO    = 1.0f/sqrtf(2.0f);

    /* macros */
    #define MIN(a, b)  (((a) < (b)) ? (a) : (b))
    #define MAX(a, b)  (((a) > (b)) ? (b) : (a))
    #define SWAP(a, b) { float f = a; a = b; b = f; }


    /****************************************************************************
    * class c_Vector3
    ****************************************************************************/
    class c_Vector3
    {

    public:

        /* Members */
        union
        {
            struct
            {
                float a[3];
            };
            struct
            {
                float x, y, z;
            };
            struct
            {
                float red, green, blue;
            };
        };

        /* Constructor */
        c_Vector3(void){};

        /* Constructor */
        c_Vector3(float p_fX, float p_fY, float p_fZ);  

        /* Addition operator */
        c_Vector3 operator+(c_Vector3 &v);

        /* Subtraction operator */
        c_Vector3 operator-(c_Vector3 &v);

        /* Multiplication operator */
        c_Vector3 operator*(c_Vector3 &v);

        /* Componentwise multiply */
        void ComponentMultiply(c_Vector3 &v);

        /* Scalar Multiplication operator */
        c_Vector3 operator*(float f);

        /* Scalar Division operator */
        c_Vector3 operator/(float f);

        /* Size of the vector */
        float Size(void);

        /* Normalize */
        void Normalize(void);

    };
    /* end class c_Vector3 */

    /* Calculate the magnitude */
    float Magnitude(c_Vector3 &v);

    /* Dot product operator */
    float DotProduct(c_Vector3 &a, c_Vector3 &b);
    float DotProduct(c_Vector3 &a);

    /* Cross product operator */
    c_Vector3 CrossProduct(c_Vector3 &p, c_Vector3 &q);

    /* Projection of P onto Q */
    void ProjPontoQ(c_Vector3 &p, c_Vector3 &q, c_Vector3 &r);

    /* Perpendicular component of P onto Q */
    void PerpPontoQ(c_Vector3 &p, c_Vector3 &q, c_Vector3 &r);

    /****************************************************************************
    * class c_Matrix3x3
    ****************************************************************************/
    class c_Matrix3x3
    {

    public:

        /* Members */
        union
        {
            float a[9];         /**< column-major */
            float data[3][3];   /**< [column][row] */
        };

        /* Constructor */
        c_Matrix3x3(void) {};

        /* Constructor (Column-major) */
        c_Matrix3x3(float a, float b, float c,
                    float d, float e, float f,
                    float g, float h, float i);

        /* Addition operator */
        c_Matrix3x3 operator+(c_Matrix3x3 &m);

        /* Subtraction operator */
        c_Matrix3x3 operator-(c_Matrix3x3 &m);

        /* Multiplication operator */
        c_Matrix3x3 operator*(c_Matrix3x3 &m);

        /* Vector Multiplication operator */
        c_Vector3 operator*(c_Vector3 &v);

        /* Scalar Multiplication operator */
        c_Matrix3x3 operator*(float f);

        /* Scalar Division operator */
        c_Matrix3x3 operator/(float f);

        /* Set to Identity */
        void SetToIdentity(void);

        /* Calc the determinant */
        float Determinant(void);

        /* Inverse */
        bool Inverse(c_Matrix3x3 &m);

    };
    /* end class c_Matrix3x3 */


    /****************************************************************************
    * class c_Quaternion
    ****************************************************************************/
    class c_Quaternion
    {

    public:

        /* Members */
        float x, y, z, w;

        /* Constructor */
        c_Quaternion(void) {};

        /* Constructor */
        c_Quaternion::c_Quaternion(float p_x, float p_y, float p_z, float p_w)
        {
            x = p_x;
            y = p_y;
            z = p_z;
            w = p_w;
        }

        /* Calc the matrix representation of the quat */
        void MatrixRep(c_Matrix3x3 *m);

    };
    /* end class c_Quaternion */

    /* return quaternion for the given euler rotation */
    c_Quaternion QuaternionEulerRotation(float p_fYaw, float p_fPitch, float p_fRoll);

}; // namespace SpatialSound

#endif //OPEN_AL_SOUND_ENGINE_MATH_H