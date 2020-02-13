// ----------------------------------------------------------------------------
// File: PositionReader.cpp
// Desc: Reads an exported file from 3ds max to get a set of position nodes
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "GameObject/PositionReader.h"
#include "Common/FilePath.h"
#include "Common/Logging.h"
#include <string>
#include <fstream>


// ----------------------------------------------------------------------------
// Name: PositionReader::PositionReader
// Desc: Constructor
// ----------------------------------------------------------------------------
PositionReader::PositionReader()
{
} // PositionReader


// ----------------------------------------------------------------------------
// Name: PositionReader::~PositionReader
// Desc: Destructor
// ----------------------------------------------------------------------------
PositionReader::~PositionReader()
{
} // ~PositionReader


// ----------------------------------------------------------------------------
// Name: PositionReader::Clear
// Desc: Clears the list of poistions
// ----------------------------------------------------------------------------
void PositionReader::Clear()
{
    m_pos.clear();
} // Clear


// ----------------------------------------------------------------------------
// Name: PositionReader::Load
// Desc: Loads the file and puts all of the positions into a map
// Parm: const char *file_name - the filename
// Retn: bool                  - true if loaded ok
// ----------------------------------------------------------------------------
bool PositionReader::Load(const char *file_name)
{
    Clear();
    return Merge(file_name);
} // Load


// ----------------------------------------------------------------------------
// Name: PositionReader::Merge
// Desc: Loads the file and puts all of the positions into a map
// Parm: const char *file_name - the filename
// Retn: bool                  - true if loaded ok
// ----------------------------------------------------------------------------
bool PositionReader::Merge(const char *file_name)
{
    std::string fn = FilePathSingleton::Instance().FindFile(std::string(file_name));
    if (fn.empty())
        return false;

    std::fstream f;
    f.open(fn.c_str(), std::ios_base::in);

    if (!f.is_open())
        return false;

    std::string str;
    std::string node_name;
    while (!f.eof())
    {
        f >> str;
        if (f.fail() || f.bad() || f.eof())
            break;

        if (str == "*NODE_NAME")
        {
            f >> str;
            node_name = str.substr(1, str.size() - 2);

            // Remove whitespace
            String::TrimString(node_name);

            // Find the last _ in the name
            size_t pos = node_name.find_last_of("_");

            // Check if it found a trailing _g
            if (pos >= node_name.size() - 3 && node_name[pos + 1] == 'g')
                node_name = node_name.substr(0, pos);

            // Remove whitespace
            String::TrimString(node_name);

            // Look for trailing [ON] or [OFF]
            if (node_name[node_name.size() - 1] == ']')
            {
                pos = node_name.find_last_of("[");
                node_name = node_name.substr(0, pos);
            } // if

            // Remove whitespace
            String::TrimString(node_name);

            continue;
        } // if

        if (str == "*TM_POS")
        {
            if (m_pos.find(node_name) != m_pos.end())
            {
                LOG_WARNING << "Found duplicate position: " << node_name << "... (skipping)" << ENDLOG;
            } // if
            else
            {
                float x, y, z;
                f >> x;
                f >> y;
                f >> z;
                m_pos[node_name] = PositionReader::Pos(x, y, z, 0.0, 0.0, 0.0);
                continue;
            } // else
        } // if
        else if (str == "*TM_EULERANGLE")
        {
            std::map<std::string, Pos>::iterator iter = m_pos.find(node_name);
            if (iter == m_pos.end())
                continue;

            static const float RAD2DEG = (180.0f / 3.14159f);

            float r, h, p;
            f >> p;
            f >> r;
            f >> h;

            iter->second.r =  r * RAD2DEG;
            iter->second.h =  h * RAD2DEG;
            iter->second.p = (p * RAD2DEG) - 90.0f;
            continue;
        } // else if

    } // while

    return true;
} // Merge


// ----------------------------------------------------------------------------
// Name: PositionReader::Contains
// Desc: Tests if a named position exists
// Parm: const std::string &name - the name
// Retn: bool                    - true if it exists
// ----------------------------------------------------------------------------
bool PositionReader::Contains(const std::string &name)
{
    return (m_pos.find(name) != m_pos.end());
} // Contains


// ----------------------------------------------------------------------------
// Name: PositionReader::Get
// Desc: Gets a position by name
// Parm: const std::string &name - the name
// Retn: PositionReader::Pos     - the position
// ----------------------------------------------------------------------------
PositionReader::Pos PositionReader::Get(const std::string &name)
{
    std::map<std::string, PositionReader::Pos>::iterator iter = m_pos.find(name);
    if (iter != m_pos.end())
        return iter->second;

    return PositionReader::Pos();
} // Get


// -- EOF

