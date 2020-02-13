// ----------------------------------------------------------------------------
// File: Sequence.h
// Desc: Node type to interate through a sequence of children
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _SEQUENCE_H
#define _SEQUENCE_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include "Math/Types.h"
#include "Scenegraph/Group.h"


// ----------------------------------------------------------------------------
// Name: Sequence  (class)
// Desc: Node type to interate through a sequence of children
// ----------------------------------------------------------------------------
class Sequence : public Group
{
public:
    // ------------------------------------------------------------------------
    // Constructors and destructor
    // ------------------------------------------------------------------------
             Sequence();
             Sequence(const std::string &name);
    virtual ~Sequence();


    // ------------------------------------------------------------------------
    // Manage the sequence atributes
    // ------------------------------------------------------------------------
    void    SetSequenceInterval(float t) { m_interval = t;    }
    float   GetSequenceInterval()        { return m_interval; }
    float   GetTotalTime() { return m_interval * GetNumChildren(); }


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
    float m_interval;


}; // class Sequence


#endif // _SEQUENCE_H

// -- EOF

