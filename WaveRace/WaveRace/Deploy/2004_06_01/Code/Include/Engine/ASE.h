// ----------------------------------------------------------------------------
// File: ASE.h
// Desc: Reads and writes ASE and ASB files
// Auth: Michael Petrou
// Note: An ASB file is a binary file that is a stored copy of in-memory
//       structures that hold the contents of an ASE file.  ASE was chosen due 
//       to its common access of exporters from most modelling packages, and
//       ASB just speeds the loading process up by an enourmous amount.
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _ASE_H
#define _ASE_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include <stdio.h>
#include <vector>
#include <map>
#include "Common/Utilities.h"
#include "Engine/Mesh_IndexVertArray.h"
#include "Engine/Material.h"
#include "Math/Types.h"
#include "Math/Matrix.h"
#include "Math/Vec3.h"


// ----------------------------------------------------------------------------
// Name: ASELoader  (class)
// Desc: Loads and converts ASE and ASB files
// ----------------------------------------------------------------------------
class ASELoader : private Utility::Unique, private Utility::NoInstance
{
public:
    // ------------------------------------------------------------------------
    // Name: Projection (enum)
    // Desc: The type of projection to use (left hand or right hand)
    // ------------------------------------------------------------------------
    enum Projection
    {
        PROJ_LH     = 1,    // LH = +Z into screen
        PROJ_RH     = 2     // RH = -Z into screen (3DS Max Default)
    }; // enum Projection


    // ------------------------------------------------------------------------
    // Name: WindingOrder (enum)
    // Desc: Vertex winding order (clockwise or counter-clockwise)
    // ------------------------------------------------------------------------
    enum WindingOrder
    {
        WIND_CW     = 1,    // Clockwise
        WIND_CCW    = 2     // Counter-clockwise
    }; // enum WindingOrder


    // ------------------------------------------------------------------------
    // Name: RecordType (enum)
    // Desc: Type of record read from the file
    // ------------------------------------------------------------------------
    enum RecordType
    {
        MESH        = 1,
        TRANSFORM   = 2
    }; // enum RecordType

    
    // ------------------------------------------------------------------------
    // Name: Record (struct)
    // Desc: Definition of a record read from the file
    // ------------------------------------------------------------------------
    struct Record
    {
        RecordType      type;
        std::string     name;
        std::string     parent_name;
        Matrix          matrix;
        Mesh           *pmesh;
        uint            material_id;
    }; // struct Record


    // ------------------------------------------------------------------------
    // Typedef for our record vector type and an iterator
    // ------------------------------------------------------------------------
    typedef std::vector<ASELoader::Record>              RecordSet;
    typedef std::vector<ASELoader::Record>::iterator    RecordSetIter;

    
    // ------------------------------------------------------------------------
    // Load an ASE or ASB file
    // ------------------------------------------------------------------------
    static bool LoadFile(const char *filename, RecordSet &records, 
        Projection proj, WindingOrder wo, LPDIRECT3DDEVICE9 device);

    
    // ------------------------------------------------------------------------
    // Convert a file from ASE to ASB
    // ------------------------------------------------------------------------
    static bool ConvertFile(const char *ase, const char *asb);


private:
    // ------------------------------------------------------------------------
    // Private static functions
    // ------------------------------------------------------------------------
    static void SetProjectionAndWinding(RecordSet &records, 
        Projection proj, WindingOrder wo);


    // ------------------------------------------------------------------------
    // Private static members
    // ------------------------------------------------------------------------
    static std::map<int, uint> s_dx_material_map;  // Map ASE material id's to engine material id's 

}; // class ASELoader



// ----------------------------------------------------------------------------
// Name: ASE (class)
// Desc: Holds a list of structures representing the contents of an ASE file. 
//       Also has the ability to read and write the structures in a binary 
//       format (ASB)
// ----------------------------------------------------------------------------
class ASE
{
public:
    // ------------------------------------------------------------------------
    // Name: FaceInfo (struct)
    // Desc: Definition of a set of face triplets for a triangle
    // ------------------------------------------------------------------------
    struct FaceInfo
    {
        Vec3    a;
        Vec3    b;
        Vec3    c;
    }; // struct FaceInfo


    // ------------------------------------------------------------------------
    // Definition of a face record
    // ------------------------------------------------------------------------
    struct FaceRecord
    {
        FaceRecord() : sub_mat_id(-1) {}

        FaceInfo    verticies;
        FaceInfo    normals;
        FaceInfo    colours;
        FaceInfo    uv_coords;
        int         sub_mat_id;
    }; // struct FaceRecord

    // ------------------------------------------------------------------------
    // Name: GeomObject (struct)
    // Desc: Definition of a geometry object (mesh)
    // ------------------------------------------------------------------------
    struct GeomObject
    {
        // --------------------------------------------------------------------
        // Binary read and write functions
        // --------------------------------------------------------------------
        bool                            WriteBinary(FILE *file);
        bool                            ReadBinary(FILE *file);

        
        // --------------------------------------------------------------------
        // Attributes written to the ASB (required data)
        // --------------------------------------------------------------------
        std::string                     name;           // The name of the mesh
        std::string                     parent_name;    // The name of the parent / group
        Matrix                          matrix;         // The absolute matrix to the pivot point
        Mesh_IndexVertArray::VertexVec  verticies;      // The vertex list
        Mesh_IndexVertArray::FaceVec    faces;          // The index list
        int                             material;       // The material id

        
        // --------------------------------------------------------------------
        // Attributes not writen to the ASB (temporary data)
        // --------------------------------------------------------------------
        std::vector<FaceRecord>         face_records;   // Temp storage for face records
        std::vector<Vec3>               vert_records;   // Temp storage for all verticies
        std::vector<Vec3>               tex_verts;      // Temp storage for vertex uv's
        std::vector<Vec3>               col_verts;      // Temp storage for vertex colors
        ulong                           wireframe_col;  // The wireframe color
    }; // struct GeomObject


    // ------------------------------------------------------------------------
    // Name: HelperObject (struct)
    // Desc: Definition of a helper object (transform)
    // ------------------------------------------------------------------------
    struct HelperObject
    {
        // --------------------------------------------------------------------
        // Binary read and write functions
        // --------------------------------------------------------------------
        bool                            WriteBinary(FILE *file);
        bool                            ReadBinary(FILE *file);

        
        // --------------------------------------------------------------------
        // Attributes written to the ASB (required data)
        // --------------------------------------------------------------------
        std::string                     name;           // The name of the helper
        std::string                     parent_name;    // The name of the parent / group
        Matrix                          matrix;         // The absolute matrix to the pivot point
    }; // struct HelperObject


    // ------------------------------------------------------------------------
    // Definition of a material
    // ------------------------------------------------------------------------
    struct MaterialDef
    {
        // --------------------------------------------------------------------
        // Binary read and write functions
        // --------------------------------------------------------------------
        bool                            WriteBinary(FILE *file);
        bool                            ReadBinary(FILE *file);

        
        // --------------------------------------------------------------------
        // Attributes written to the ASB (required data)
        // --------------------------------------------------------------------
        int                             id;             // The id of the material
        Color                           ambient;        // The ambient colour
        Color                           diffuse;        // The diffuse colour
        Color                           specular;       // The specular colour
        Color                           emissive;       // The emissive color       // TODO - Not Set by ASELoader
        float                           power;          // The specular power       // TODO - Not Set by ASELoader
        std::string                     tex_map1;       // The colour map
        std::string                     opac_map;       // The transparent map
        std::map<int, MaterialDef *>    sub_materials;  // The sub-materials

        
        // --------------------------------------------------------------------
        // Attributes not writen to the ASB (temporary data)
        // --------------------------------------------------------------------
        MaterialCache::MapType          curr_tex_map;
    }; // struct MaterialDef


public:
    // ------------------------------------------------------------------------
    // Constructor
    // ------------------------------------------------------------------------
    ASE() : m_pcurr_geom_obj (0), m_pcurr_mat_def (0), m_pcurr_helper_obj (0) {}

    
    // ------------------------------------------------------------------------
    // Read an ASE (text) file and read / write an ASB (binary) file
    // ------------------------------------------------------------------------
    bool                            ReadASCII(const char *filename);
    bool                            ReadBinary(const char *filename);
    bool                            WriteBinary(const char *filename);

    
    // ------------------------------------------------------------------------
    // Get all structures from the loaded file (objects, helpers, materials)
    // ------------------------------------------------------------------------
    bool                             HasData();
    std::vector<GeomObject *>       &GetObjects()   { return m_objects;   }
    std::vector<HelperObject *>     &GetHelpers()   { return m_helpers;   }
    std::map<uint, MaterialDef *>   &GetMaterials() { return m_materials; }


public:
    // ------------------------------------------------------------------------
    // Public static functions for this class to help read the material data
    // ------------------------------------------------------------------------
    static int                      MakeCombinedMaterialId(int mat_id, int sub_mat_id);
    static int                      GetSubMaterialId(int combined_id);
    static int                      GetMaterialId(int combined_id);
    static int                      MakeDefaultMaterialId(int mat_id);


private:
    // ------------------------------------------------------------------------
    // Private functions for this class
    // ------------------------------------------------------------------------
    bool                            ParseLine(const std::string &str);
    bool                            ProcessCommand(const std::string &command, std::stringstream &ss);
    bool                            RebuildGeomObjectForSubMaterials(GeomObject *pobj);


    // ------------------------------------------------------------------------
    // All objects and materials from the loaded file
    // ------------------------------------------------------------------------
    std::vector<GeomObject *>       m_objects;
    std::vector<HelperObject *>     m_helpers;
    std::map<uint, MaterialDef *>   m_materials;

    
    // ------------------------------------------------------------------------
    // Temporary pointers for the ascii file parser
    // ------------------------------------------------------------------------
    GeomObject                     *m_pcurr_geom_obj;
    HelperObject                   *m_pcurr_helper_obj;
    MaterialDef                    *m_pcurr_mat_def;
    int                             m_curr_sub_material;
    int                             m_curr_face_normal;
    int                             m_curr_vert_normal;
}; // class ASE


#endif // _ASE_H

// -- EOF

