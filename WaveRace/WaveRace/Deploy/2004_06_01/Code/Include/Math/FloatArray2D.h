// ----------------------------------------------------------------------------
// File: FloatArray2D.h
// Desc: Provides an object with array like behaviour but lets the user
//       define the allocation of the array prior to constructing this 
//       wrapper.  Also, the data in the array may be swapped with some
//       other array during the array's lifespan.
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _FLOAT_ARRAY_2D_
#define _FLOAT_ARRAY_2D_


// ----------------------------------------------------------------------------
// Name: FloatArray2D (struct)
// Desc: Provides an object with array like behaviour but lets the user
//       define the allocation of the array prior to constructing this 
//       wrapper.  Also, the data in the array may be swapped with some
//       other array during the array's lifespan.
// ----------------------------------------------------------------------------
struct FloatArray2D
{
    // ------------------------------------------------------------------------
    // Members
    // ------------------------------------------------------------------------
    float   *pdata; // a pointer to externally allocated data
    long     width; // the array width
    bool     own;   // do we now own the data array


    // ------------------------------------------------------------------------
    // Constructor
    // ------------------------------------------------------------------------
     FloatArray2D(bool owner = false) : pdata(0), width(0), own(owner) {}
     FloatArray2D(float *pd, long w, bool owner = false) : pdata(pd), width(w), own(owner) {}
    ~FloatArray2D() { if (own) delete[] pdata; }


    // ------------------------------------------------------------------------
    // Set the data
    // ------------------------------------------------------------------------
    void Set(float *pd, long w, bool owner = false) { pdata = pd; width = w; own = owner; }


    // ------------------------------------------------------------------------
    // Indexing operators - both read / write and read only
    // ------------------------------------------------------------------------
    const float *operator [] (long i) const { return pdata + i * width; }
    float       *operator [] (long i)       { return pdata + i * width; }

}; // struct FloatArray2D


#endif // _FLOAT_ARRAY_2D_

// -- EOF
