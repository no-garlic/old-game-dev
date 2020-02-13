// ----------------------------------------------------------------------------
// File: DCS.h
// Desc: Dynamic co-ordinate system node type
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _DCS_H
#define _DCS_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include "Math/Types.h"
#include "Math/Coords.h"
#include "Math/Matrix.h"
#include "Math/Vec3.h"
#include "Scenegraph/Group.h"


// ----------------------------------------------------------------------------
// Name: DCS  (class)
// Desc: Dynamic co-ordinate system node type
// ----------------------------------------------------------------------------
class DCS : public Group
{
public:
    // ------------------------------------------------------------------------
    // Constructors and destructor
    // ------------------------------------------------------------------------
             DCS();
             DCS(const std::string &name);
    virtual ~DCS();


    // ------------------------------------------------------------------------
    // The matrix transform
    // ------------------------------------------------------------------------
    void            GetMatrix(Matrix &m) const  { m = m_matrix;     }
    void            SetMatrix(const Matrix &m)  { m_matrix = m;     }

    const Matrix   &GetMatrix()          const  { return  m_matrix; }
    Matrix         &GetMatrix()                 { return  m_matrix; }

    const Matrix   *GetMatrixPtr()       const  { return &m_matrix; }
    Matrix         *GetMatrixPtr()              { return &m_matrix; }


    // ------------------------------------------------------------------------
    // Get he bonuding sphere
    // ------------------------------------------------------------------------
    virtual const Sphere &GetBSphere();


protected:
    // ------------------------------------------------------------------------
    // Protected functions
    // ------------------------------------------------------------------------
    virtual std::string GetNodeDescription();
    virtual bool        IsOfType(const NodeType node_type);
    virtual bool        IsExactType(const NodeType node_type);


private:
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    Matrix      m_matrix;

}; // class DCS


#endif // _DCS_H

// -- EOF

