
#ifndef __STD_RAND_H_
#define __STD_RAND_H_


#if PC
#include <MMSystem.h>
#endif


// ----------------------------------------------------------------------------
// Random number generator
// Generates psuedo random numbers
// ----------------------------------------------------------------------------
class Random
{
public:
  // --------------------------------------------------------------------------
  // Constructor
  // --------------------------------------------------------------------------
  Random(int seed = timeGetTime())
    : m_Seed(seed)
  {
  }

  // --------------------------------------------------------------------------
  // Get a floating point value in the range of 0..1
  // --------------------------------------------------------------------------
  float GetFloat()
  {
    MutateSeed();
    static const float tempRand = 1.0f;
    float result;
    *(int *) &result = (* (int *) &tempRand & 0xff800000) | (m_Seed & 0x007fffff);
    return result - (int) result;
  }

  // --------------------------------------------------------------------------
  // Get an integer value in the range 0..INT_MAX
  // --------------------------------------------------------------------------
  int GetInt()
  {
    MutateSeed();
    return m_Seed;
  }

private:
  // --------------------------------------------------------------------------
  // Get the next seed
  // --------------------------------------------------------------------------
  void MutateSeed()
  {
    m_Seed = (m_Seed * 196314165) + 907633515;
  }

  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  int m_Seed;

};


// ----------------------------------------------------------------------------
// Get a random floating point number
// ----------------------------------------------------------------------------
inline float FloatRandom(float start, float end)
{
  static Random random;
  return (random.GetFloat() * (end - start)) + start;
}


// ----------------------------------------------------------------------------
// Get a random integer number
// ----------------------------------------------------------------------------
inline int IntRandom(int start, int end)
{
  static Random random;
  return (random.GetInt() % (end - start)) + start;
}


#endif // __STD_RAND_H_

// -- EOF


