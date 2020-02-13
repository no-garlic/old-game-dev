// ----------------------------------------------------------------------------
// File: PositionReader.h
// Desc: Reads a file from 3dsmax and gets a list of positions
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _POSITION_READER_H_
#define _POSITION_READER_H_


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include <map>
#include <string>


// ----------------------------------------------------------------------------
// Name: PositionReader  (class)
// Desc: Reads a file from 3dsmax and gets a list of positions
// ----------------------------------------------------------------------------
class PositionReader : private Utility::Unique
{
public:
    // ------------------------------------------------------------------------
    // Name: Pos (struct)
    // Desc: Holds a position
    // ------------------------------------------------------------------------
    struct Pos
    {
        Pos() : x(0.0), y(0.0), z(0.0), h(0.0), p(0.0), r(0.0) {}
        Pos(float _x, float _y, float _z, float _h, float _p, float _r) : x(_x), y(_y), z(_z), h(_h), p(_p), r(_r) {}

        float x;    float y;    float z;
        float h;    float p;    float r;
    }; // struct Pos


    // ------------------------------------------------------------------------
    // Constructor and destructor
    // ------------------------------------------------------------------------
             PositionReader();
    virtual ~PositionReader();


    // ------------------------------------------------------------------------
    // Public interface
    // ------------------------------------------------------------------------
    void    Clear();
    bool    Load(const char *file_name);
    bool    Merge(const char *file_name);
    bool    Contains(const std::string &name);
    Pos     Get(const std::string &name);

    
    // ------------------------------------------------------------------------
    // Get the position data
    // ------------------------------------------------------------------------
    const std::map<std::string, Pos> &GetData() { return m_pos; }


private:
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    std::map<std::string, Pos>  m_pos;


}; // PositionReader


#endif // _POSITION_READER_H_

// -- EOF

