// ----------------------------------------------------------------------------
// File: StdMath.h
// Desc: Standard math operations
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#ifndef __STD_MATH_H_
#define __STD_MATH_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "stdType.h"


// ----------------------------------------------------------------------------
// Float values
// ----------------------------------------------------------------------------
const float FLOAT_EPSILON = 0.001f;
const float FLOAT_MAX     =  3.402823466e+38F;
const float FLOAT_MIN     = -3.402823466e+38F;
const float PI            = D3DX_PI;
const float PI_DIV_2      = D3DX_PI * 0.5f;
const float PI_DIV_4      = D3DX_PI * 0.25f;
const float PI_TIMES_2    = D3DX_PI * 2.0f;


// ----------------------------------------------------------------------------
// Name: IsPowerOf2
// Desc: Test if the given number is a power of two
// Parm: unsigned int num - the number to test
// Retn: bool             - true if it is a power of two
// ----------------------------------------------------------------------------
inline bool IsPowerOf2(unsigned int num)
{
  for (uint i = 0; i < 32; i++)
  {
    if (num == 2)
      return true;

    num = num >> 1;
  } // for

  return false;
} // IsPowerOf2


// ----------------------------------------------------------------------------
// Name: Clamp
// Temp: The type of the object we are going to clamp.  Note - must have the 
//       less-than and greater-than operators defined.
// Desc: Useful here and there, allows the user to 'snap' a variable to lie 
//       within the bounds of two inputted vars
// Parm: T &a          - the object we are clamping
// Parm: const T &min  - the lower bound
// Parm: const T &max  - the upper bound
// ----------------------------------------------------------------------------
template <class T>
static void Clamp(T &a, const T &min, const T &max)
{
  if (a < min)
    a = min;
  if (a > max) 
    a = max;
} // Clamp


// ----------------------------------------------------------------------------
// Name: Swap
// Temp: The type of the items we are swapping
// Desc: Swaps the values of A and B
// Parm: T &a - the first item
// Parm: T &b - the second item
// ----------------------------------------------------------------------------
template<class T>
void Swap(T &a, T &b)
{
  const T temp = a;
  a = b;
  b = temp;
} // Swap


// ----------------------------------------------------------------------------
// Name: IsBetween
// Temp: The type
// Desc: Test if a value is between two other values
// Parm: const T &a  - the value to test
// Parm: const T &b  - the first value
// Parm: const T &c  - the second value
// Retn: bool        - true if the value to test is between the first and second
// ----------------------------------------------------------------------------
template<class T>
bool IsBetween(const T &a, const T &b, const T &c)
{
  return (b <= a && a <= c);
} // IsBetween


// ----------------------------------------------------------------------------
// Name: Round
// Desc: Round the float to the nearest integer
// Parm: float f - the float
// Retn: int     - the rounder int
// ----------------------------------------------------------------------------
inline int Round(float f)
{
  int a;

  __asm
  {
    fld f
    fistp a
  };

  return a;
} // Round	


// ----------------------------------------------------------------------------
// Name: FastSqrt
// Desc: Calculate the fast square root of a floating point number
// ----------------------------------------------------------------------------
inline float FastSqrt(float x)
{
  float xhalf = 0.5f * x;
  float xprime;

  long i = *((long *)&x);     // transfer to integer register, causes memory access
  i = 0x5F3759DF - (i >> 1);  // poor man's exponent
  xprime = *((float*)&i);     // transfer back to floating point register
  xprime = xprime * (1.5f - xhalf * xprime * xprime);  

  return xprime * x;
} // FastSqrt


// ----------------------------------------------------------------------------
// Handles bit masks
// ----------------------------------------------------------------------------
struct BitField
{
  BitField()                          { m_Data = 0;    }
  BitField(uint data)                 { m_Data = data; }

  inline void Set(uint data)          { m_Data = data; }
  inline uint Get() const             { return m_Data; }

  inline operator uint()              { return m_Data; }

  inline void Add(uint data)          { m_Data = (m_Data |  data); }
  inline void Remove(uint data)       { m_Data = (m_Data & ~data); }

  inline void Add(BitField data)      { m_Data = (m_Data |  data.m_Data); }
  inline void Remove(BitField data)   { m_Data = (m_Data & ~data.m_Data); }

  inline bool Test(BitField data)     { return ((m_Data & data) != 0x0);  }
  inline bool TestAll(BitField data)  { return ((m_Data & data) == data); }

private:
  uint m_Data;

};


#endif // __STD_MATH_H_

// -- EOF

