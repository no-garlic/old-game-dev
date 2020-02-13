// ----------------------------------------------------------------------------
// File: Switch.h
// Desc: Node to control traversals
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _SWITCH_H
#define _SWITCH_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Common/Utilities.h"
#include "Math/Types.h"
#include "Scenegraph/Group.h"


// ----------------------------------------------------------------------------
// Name: Switch  (class)
// Desc: Node to control traversals
// ----------------------------------------------------------------------------
class Switch : public Group
{
public:
    // ------------------------------------------------------------------------
    // Constructors and destructor
    // ------------------------------------------------------------------------
             Switch();
             Switch(const std::string &name);
    virtual ~Switch();

    // ------------------------------------------------------------------------
    // Switch on / off
    // ------------------------------------------------------------------------
    void SetVal(bool value) { m_value = value; }
    bool GetVal()           { return m_value; }


protected:
    // ------------------------------------------------------------------------
    // Protected members
    // ------------------------------------------------------------------------
    virtual std::string GetNodeDescription();
    virtual bool        IsOfType(const NodeType node_type);
    virtual bool        IsExactType(const NodeType node_type);

private:
    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    bool m_value;


}; // class Switch


#endif // _SWITCH_H

// -- EOF

