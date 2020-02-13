// ----------------------------------------------------------------------------
// File: ASE.cpp
// Desc: Reads and writes ASE and ASB files
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include "Engine/ASE.h"
#include "Common/Logging.h"
#include "Common/FilePath.h"


// ----------------------------------------------------------------------------
// Defines for creating material id ranges
// ----------------------------------------------------------------------------
#define BASE_DEFAULT_MAT_ID_RANGE   10000
#define BASE_SUB_MAT_ID_RANGE       100000


// ----------------------------------------------------------------------------
// Initialise the static map
// ----------------------------------------------------------------------------
std::map<int, uint> ASELoader::s_dx_material_map;


// ----------------------------------------------------------------------------
// Loader I/O Functions
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Name: ASELoader::LoadFile
// Desc: Loads a given ASE or ASB file from disk, and returns a vector of 
//       records.  Note - all materials and textures are created with the
//       material cache and texture cache during loading, and the id's of
//       these records are in the records.
// Parm: const char *filename           - the filename of the file to load
// Parm: Projection proj                - the projection (LH / RH)
// Parm: WindingOrder wo                - the winding order (CW / CCW)
// Parm: LPDIRECT3DDEVICE9 device       - the d3d device to use to allocate 
//       memory for the index and vertex buffers
// Retn: std::vector<ASELoader::Record> - a vector of records.  Note - the 
//       ownership of the meshes in the records is passed to the caller, and the
//       caller is responsible for deleting them when finished.
// ----------------------------------------------------------------------------
bool ASELoader::LoadFile(const char        *filename, 
                         RecordSet         &records,
                         Projection         proj, 
                         WindingOrder       wo, 
                         LPDIRECT3DDEVICE9  device)
{
    // File parser
    ASE ase;


    // ------------------------------------------------------------------------
    // Read either ASE or ASB based on the file extension
    // ------------------------------------------------------------------------
    std::string fn   = filename;
    std::string extn = fn.substr(fn.size() - 3, 3);
    
    FilePath::StripPath(fn);
    std::string found = FilePathSingleton::Instance().FindFile(fn);
    if (!found.empty())
        fn = found;
    
    // Read ASE or ASB
    if (extn == "ase" || extn == "ASE")
    {
        if (!ase.ReadASCII(fn.c_str()))
        {
            LOG_ERROR << "Failed to read the ASE file: " << fn << ENDLOG;
            return false;
        } // if
    } // if
    else if (extn == "asb" || extn == "ASB")
    {
        if (!ase.ReadBinary(fn.c_str()))
        {
            LOG_ERROR << "Failed to read the ASB file: " << fn << ENDLOG;
            return false;
        } // if
    } // else if
    else
    {
        LOG_ERROR << "Cannot read the file: " << fn << " - it is not an ASE or ASB file" << ENDLOG;
        return false;
    } // else

    // Check that the file contained some objects
    if (!ase.HasData())
    {
        LOG_WARNING << "No records found in file: " << fn << ENDLOG;
        return false;
    } // if

    // Clear the material map
    s_dx_material_map.clear();
    s_dx_material_map[-1] = 0;

    
    // ------------------------------------------------------------------------
    // Create all materials
    // ------------------------------------------------------------------------
    size_t num_materials = ase.GetMaterials().size();
    for (size_t i = 0; i < num_materials; i++)
    {
        // Get the material
        ASE::MaterialDef *pmat = ase.GetMaterials()[i];
        if (!pmat)
        {
            LOG_WARNING << "Bad material found in file: " << fn << ENDLOG;
            continue;
        } // if

        // Default color and opacity maps
        uint tex_map1_id = 0;
        uint tex_map2_id = 0;

        // Load colour texture
        if (pmat->tex_map1.size() > 0)
            tex_map1_id = TextureCache::CreateTexture(pmat->tex_map1.c_str(), device);

        // Load opacity texture
        if (pmat->opac_map.size() > 0)
            tex_map2_id = TextureCache::CreateTexture(pmat->opac_map.c_str(), device);

        // Create the material
        //uint mat_id = MaterialCache::CreateMaterial(tex_map1_id, 0, tex_map2_id, pmat->ambient, 
        //    pmat->diffuse, pmat->emissive, pmat->specular, pmat->power);
        uint mat_id = MaterialCache::CreateMaterial(tex_map1_id, tex_map2_id, 0, 
            (tex_map2_id == 0 ? "Opaque.fx" : "Transparent.fx"),
            //(tex_map2_id == 0 ? FX_TEX0 : FX_TEX0 | FX_TEX1), (tex_map2_id == 0));
            FX_TEX0, (tex_map2_id == 0));

        // Register material
        s_dx_material_map[pmat->id] = mat_id;

        // Load the sub-materials
        for (size_t j = 0; j < pmat->sub_materials.size(); j++)
        {
            // Get the material
            ASE::MaterialDef *psub_mat = pmat->sub_materials[j];
            if (!psub_mat)
            {
                LOG_WARNING << "Bad sub-material found in file: " << fn << ENDLOG;
                continue;
            } // if

            // Default color and opacity maps
            uint tex_sub_map1_id = 0;
            uint opac_sub_map_id = 0;

            // Load colour texture
            if (psub_mat->tex_map1.size() > 0)
                tex_sub_map1_id = TextureCache::CreateTexture(psub_mat->tex_map1.c_str(), device);

            // Load opacity texture
            if (psub_mat->opac_map.size() > 0)
                opac_sub_map_id = TextureCache::CreateTexture(psub_mat->opac_map.c_str(), device);

            // Create the material
            //uint sub_mat_id = MaterialCache::CreateMaterial(tex_sub_map1_id, 0, opac_sub_map_id, psub_mat->ambient, 
            //    psub_mat->diffuse, psub_mat->emissive, psub_mat->specular, psub_mat->power);
            uint sub_mat_id = MaterialCache::CreateMaterial(tex_sub_map1_id, opac_sub_map_id, 0, 
                (opac_sub_map_id == 0 ? "Opaque.fx" : "Transparent.fx"),
//                (opac_sub_map_id == 0 ? FX_TEX0 : FX_TEX0 | FX_TEX1), (tex_map2_id == 0));
                FX_TEX0, (tex_map2_id == 0));

            // Make a unique material id
            int new_mat_id = ASE::MakeCombinedMaterialId(pmat->id, psub_mat->id);

            // Register material
            s_dx_material_map[new_mat_id] = sub_mat_id;
        } // for
    } // for

    
    // ------------------------------------------------------------------------
    // Create all geom objects in the group, regardless of the hierarchy in the 
    // ASE file.
    // ------------------------------------------------------------------------
    for (size_t j = 0; j < ase.GetObjects().size(); j++)
    {
        // Get the geom object
        ASE::GeomObject *pobj = ase.GetObjects()[j];
        if (!pobj)
        {
            LOG_WARNING << "Bad object found in file: " << fn << ENDLOG;
            continue;
        } // if

        // Create the mesh
        Mesh_IndexVertArray *pmesh = new 
            Mesh_IndexVertArray(pobj->name.c_str(), device, pobj->verticies, pobj->faces, true);

        // Create a record
        ASELoader::Record record;
        record.type         = ASELoader::MESH;
        record.matrix       = pobj->matrix;
        record.name         = pobj->name;
        record.parent_name  = pobj->parent_name;
        record.pmesh        = pmesh;
        record.material_id  = s_dx_material_map[pobj->material];

        // Add the record
        records.push_back(record);
    } // for


    // ------------------------------------------------------------------------
    // Create all helper objects in the group, regardless of the hierarchy in 
    // the ASE file.
    // ------------------------------------------------------------------------
    for (size_t j = 0; j < ase.GetHelpers().size(); j++)
    {
        // Get the geom object
        ASE::HelperObject *pobj = ase.GetHelpers()[j];
        if (!pobj)
        {
            LOG_WARNING << "Bad helper found in file: " << fn << ENDLOG;
            continue;
        } // if

        // Create a record
        ASELoader::Record record;
        record.type         = ASELoader::TRANSFORM;
        record.matrix       = pobj->matrix;
        record.name         = pobj->name;
        record.parent_name  = pobj->parent_name;
        record.pmesh        = 0;
        record.material_id  = 0;

        // Add the record
        records.push_back(record);
    } // for

    // Set the projection and winding order - note this
    // will be changed to occur before we build the meshes.
    SetProjectionAndWinding(records, proj, wo);

    // Return all objects
    return true;
} // LoadFile


// ----------------------------------------------------------------------------
// Name: ASELoader::SetProjectionAndWinding
// Desc: Set the projection and winding order of the verticies and faces
// Parm: std::vector<ASELoader::Record> &records - the records to set
// Parm: Projection proj                         - the projection type (LH / RH
//       )
// Parm: WindingOrder wo                         - the winding order (CW / CCW)
// Retn: bool                                    - true if set ok
// ----------------------------------------------------------------------------
void ASELoader::SetProjectionAndWinding(std::vector<ASELoader::Record> &records, 
                                        Projection proj, 
                                        WindingOrder wo)
{
    std::vector<ASELoader::Record>::iterator iter = records.begin();
    for (; iter != records.end(); ++iter)
    {
        ASELoader::Record &rec = *iter;

        // Reverse the Z values of the mesh - we would actually
        // prefer to do this to the geom objects prior to building
        // the mesh.

        // Reverse the matricies - again, for geom and helpers can
        // be done prior to making the mesh.

    } // for
} // SetProjectionAndWinding


// ----------------------------------------------------------------------------
// Name: ASELoader::ConvertFile
// Desc: Converts a file from ASE to ASB format
// Parm: const char *ase  - the ASE file
// Parm: const char *asb  - the ASB file
// Retn: bool             - true if the conversion succeeded
// ----------------------------------------------------------------------------
bool ASELoader::ConvertFile(const char *ase, const char *asb)
{
    ASE io;

    // Verify ASE filename
    std::string fn   = ase;
    String::TrimString(fn);
    std::string extn = fn.substr(fn.size() - 3, 3);
    if (extn != "ase" && extn != "ASE")
    {
        LOG_ERROR << "Bad ASE filename: " << ase << ENDLOG;
        return false;
    } // if

    // Verify ASB filename
    fn   = asb;
    String::TrimString(fn);
    extn = fn.substr(fn.size() - 3, 3);
    if (extn != "asb" && extn != "ASB")
    {
        LOG_ERROR << "Bad ASB filename: " << asb << ENDLOG;
        return false;
    } // if

    // Read the ASE file
    if (!io.ReadASCII(ase) || !io.HasData())
    {
        LOG_ERROR << "Failed to read the ASE file: " << ase << ENDLOG;
        return false;
    } // if

    // Write the ASB file
    if (!io.WriteBinary(asb))
    {
        LOG_ERROR << "Failed to write the ASB file: " << asb << ENDLOG;
        return false;
    } // if

    // Success
    return true;
} // ConvertFile


// ----------------------------------------------------------------------------
// Name: ASE::HasData
// Desc: Check if there is any data in the list (materials, objects, helpers)
// Retn: bool - true if there is some data
// ----------------------------------------------------------------------------
bool ASE::HasData()
{
    return (!(m_objects.empty() && m_helpers.empty() && m_materials.empty()));
} // HasData




// ----------------------------------------------------------------------------
// Binary File Functions
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Name: ASE::GeomObject::WriteBinary
// Desc: Write a goem object to a binary file
// Parm: FILE *file - the file
// Retn: bool       - true if succeeded
// ----------------------------------------------------------------------------
bool ASE::GeomObject::WriteBinary(FILE *file)
{
    fwrite(&material, sizeof(uint), 1, file);
    fwrite(&matrix, sizeof(Matrix), 1, file);

    Binary::WriteBinaryString(file, name);
    Binary::WriteBinaryString(file, parent_name);

    int num_verts = (int) verticies.size();
    fwrite(&num_verts, sizeof(int), 1, file);

    for (int i = 0; i < num_verts; i++)
        fwrite(&(verticies[i]), sizeof(Mesh_IndexVertArray::Vertex), 1, file);

    int num_faces = (int) faces.size();
    fwrite(&num_faces, sizeof(int), 1, file);

    for (int i = 0; i < num_faces; i++)
        fwrite(&(faces[i]), sizeof(Mesh_IndexVertArray::Face), 1, file);

    return true;
} // WriteBinary


// ----------------------------------------------------------------------------
// Name: ASE::GeomObject::ReadBinary
// Desc: Read a geom object from a binary file
// Parm: FILE *file - the file
// Retn: bool       - true if succeeded
// ----------------------------------------------------------------------------
bool ASE::GeomObject::ReadBinary(FILE *file)
{
    fread(&material, sizeof(uint), 1, file);
    fread(&matrix, sizeof(Matrix), 1, file);

    Binary::ReadBinaryString(file, name);
    Binary::ReadBinaryString(file, parent_name);
  
    int num_verts = 0;
    fread(&num_verts, sizeof(int), 1, file);

    verticies.resize(num_verts);
    for (int i = 0; i < num_verts; i++)
        fread(&(verticies[i]), sizeof(Mesh_IndexVertArray::Vertex), 1, file);

    int num_faces = 0;
    fread(&num_faces, sizeof(int), 1, file);

    faces.resize(num_faces);
    for (int i = 0; i < num_faces; i++)
        fread(&(faces[i]), sizeof(Mesh_IndexVertArray::Face), 1, file);

    return true;
} // WriteBinary


// ----------------------------------------------------------------------------
// Name: ASE::HelperObject::WriteBinary
// Desc: Write a helper object to a binary file
// Parm: FILE *file - the file
// Retn: bool       - true if succeeded
// ----------------------------------------------------------------------------
bool ASE::HelperObject::WriteBinary(FILE *file)
{
    Binary::WriteBinaryString(file, name);
    Binary::WriteBinaryString(file, parent_name);
    fwrite(&matrix, sizeof(Matrix), 1, file);

    return true;
} // WriteBinary


// ----------------------------------------------------------------------------
// Name: ASE::HelperObject::ReadBinary
// Desc: Read a helper object from a binary file
// Parm: FILE *file - the file
// Retn: bool       - true if succeeded
// ----------------------------------------------------------------------------
bool ASE::HelperObject::ReadBinary(FILE *file)
{
    Binary::ReadBinaryString(file, name);
    Binary::ReadBinaryString(file, parent_name);
    fread(&matrix, sizeof(Matrix), 1, file);

    return true;
} // WriteBinary


// ----------------------------------------------------------------------------
// Name: ASE::MaterialDef::WriteBinary
// Desc: Write a material to a binary file
// Parm: FILE *file - the file
// Retn: bool       - true if succeeded
// ----------------------------------------------------------------------------
bool ASE::MaterialDef::WriteBinary(FILE *file)
{
    fwrite(&id,         sizeof(int),    1, file);
    fwrite(&ambient,    sizeof(Color),  1, file);
    fwrite(&diffuse,    sizeof(Color),  1, file);
    fwrite(&emissive,   sizeof(Color),  1, file);
    fwrite(&specular,   sizeof(Color),  1, file);
    fwrite(&power,      sizeof(float),  1, file);

    Binary::WriteBinaryString(file, tex_map1);
    Binary::WriteBinaryString(file, opac_map);

    int i = static_cast<int>(sub_materials.size());
    fwrite(&i, sizeof(int), 1, file);

    std::map<int, MaterialDef *>::iterator iter = sub_materials.begin();
    for (; iter != sub_materials.end(); ++iter)
    {
        int id                  = iter->first;
        ASE::MaterialDef *pmat  = iter->second;

        fwrite(&id, sizeof(int), 1, file);
        if (!pmat->WriteBinary(file))
            return false;
    } // for

    return true;
} // WriteBinary


// ----------------------------------------------------------------------------
// Name: ASE::MaterialDef::ReadBinary
// Desc: Read a material from a binary file
// Parm: FILE *file - the file
// Retn: bool       - true if succeeded
// ----------------------------------------------------------------------------
bool ASE::MaterialDef::ReadBinary(FILE *file)
{
    fread(&id,          sizeof(int),    1, file);
    fread(&ambient,     sizeof(Color),  1, file);
    fread(&diffuse,     sizeof(Color),  1, file);
    fread(&emissive,    sizeof(Color),  1, file);
    fread(&specular,    sizeof(Color),  1, file);
    fread(&power,       sizeof(float),  1, file);

    Binary::ReadBinaryString(file, tex_map1);
    Binary::ReadBinaryString(file, opac_map);

    int i = 0;
    fread(&i, sizeof(int), 1, file);

    for (int j = 0; j < i; j++)
    {
        int id;
        ASE::MaterialDef *pmat  = new ASE::MaterialDef();

        fread(&id, sizeof(int), 1, file);
        if (!pmat->ReadBinary(file))
            return false;

        sub_materials[id] = pmat;
    } // for

    return true;
} // WriteBinary


// ----------------------------------------------------------------------------
// Name: ASE::ReadBinary
// Desc: Read a binary (ASB) file
// Parm: const char *filename - the filename of the ASB file
// Retn: bool                 - true if succeeded
// ----------------------------------------------------------------------------
bool ASE::ReadBinary(const char *filename)
{
    std::string fn = filename;

    m_objects.clear();
    m_materials.clear();
    m_helpers.clear();

    FILE *f = fopen(fn.c_str(), "rb");
    if (!f)
        return false;

    int num_geom;
    fread(&num_geom, sizeof(int), 1, f);

    m_objects.resize(num_geom);
    for (int i = 0; i < num_geom; i++)
    {
        m_objects[i] = new GeomObject;
        m_objects[i]->ReadBinary(f);
    } // for

    int num_helper;
    fread(&num_helper, sizeof(int), 1, f);

    m_helpers.resize(num_helper);
    for (int i = 0; i < num_helper; i++)
    {
        m_helpers[i] = new HelperObject;
        m_helpers[i]->ReadBinary(f);
    } // for

    int num_mat;
    fread(&num_mat, sizeof(int), 1, f);

    for (int i = 0; i < num_mat; i++)
    {
        int id;
        fread(&id, sizeof(int), 1, f);
        MaterialDef *material_def = new MaterialDef;
        material_def->ReadBinary(f);
        m_materials.insert(std::make_pair(id, material_def));
    } // for

    fclose(f);
    return true;
} // ReadBinary


// ----------------------------------------------------------------------------
// Name: ASE::WriteBinary
// Desc: Write a binary (ASB) file
// Parm: const char *filename - the filname of the ASB file
// Retn: bool                 - true if succeeded
// ----------------------------------------------------------------------------
bool ASE::WriteBinary(const char *filename)
{
    std::string fn = filename;

    FILE *f = fopen(fn.c_str(), "wb");
    if (!f)
        return false;

    int num_geom = (int) m_objects.size();
    fwrite(&num_geom, sizeof(int), 1, f);

    for (int i = 0; i < num_geom; i++)
        m_objects[i]->WriteBinary(f);

    int num_helper = (int) m_helpers.size();
    fwrite(&num_helper, sizeof(int), 1, f);

    for (int i = 0; i < num_helper; i++)
        m_helpers[i]->WriteBinary(f);

    int num_mat = (int) m_materials.size();
    fwrite(&num_mat, sizeof(int), 1, f);

    std::map<uint, MaterialDef *>::iterator iter = m_materials.begin();
    for (; iter != m_materials.end(); ++iter)
    {
        int id = iter->first;
        fwrite(&id, sizeof(int), 1, f);
        iter->second->WriteBinary(f);
    } // for

    fclose(f);
    return true;
} // WriteBinary




// ----------------------------------------------------------------------------
// ASCII File Functions
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Name: ASE::MakeCombinedMaterialId
// Desc: Make a material id that is unique to associate a sub-material with 
//       another material
// Parm: int mat_id      - the material id
// Parm: int sub_mat_id  - the sub-material id
// Retn: int             - the combined material id
// ----------------------------------------------------------------------------
int ASE::MakeCombinedMaterialId(int mat_id, int sub_mat_id)
{
    return ((mat_id + 1) * BASE_SUB_MAT_ID_RANGE) + sub_mat_id;
} // MakeCombinedMaterialId


// ----------------------------------------------------------------------------
// Name: ASE::GetSubMaterialId
// Desc: Get the sub-material id from a combined material id
// Parm: int combined_id - the combined material id
// Retn: int             - the sub-material id
// ----------------------------------------------------------------------------
int ASE::GetSubMaterialId(int combined_id)
{
    return (combined_id % BASE_SUB_MAT_ID_RANGE);
} // GetSubMaterialId


// ----------------------------------------------------------------------------
// Name: ASE::GetMaterialId
// Desc: Get the material id from a combined material id
// Parm: int combined_id - the combined material id
// Retn: int             - the material id
// ----------------------------------------------------------------------------
int ASE::GetMaterialId(int combined_id)
{
    return ((combined_id - GetSubMaterialId(combined_id)) / BASE_SUB_MAT_ID_RANGE) - 1;
} // GetMaterialId


// ----------------------------------------------------------------------------
// Name: ASE::MakeDefaultMaterialId
// Desc: Make a default material id used when no material exists, and we are 
//       using the wireframe color to create a basic material
// Parm: int mat_id - the material id
// Retn: int        - the new material id
// ----------------------------------------------------------------------------
int ASE::MakeDefaultMaterialId(int mat_id)
{
    return mat_id + BASE_DEFAULT_MAT_ID_RANGE;
} // MakeDefaultMaterialId


// ----------------------------------------------------------------------------
// Name: ASE::ReadASCII
// Desc: Read an ASCII (ASE) file
// Parm: const char *filename - the filename of the ASE file
// Retn: bool                 - true if successful
// ----------------------------------------------------------------------------
bool ASE::ReadASCII(const char *filename)
{
    std::string fn = filename;

    std::fstream file;
    file.open(fn.c_str(), std::ios_base::in);

    if (!file.is_open())
        return false;

    m_pcurr_geom_obj    = 0;
    m_pcurr_mat_def     = 0;
    m_pcurr_helper_obj  = 0;
    m_curr_face_normal  = -1;
    m_curr_vert_normal  = -1;
    m_curr_sub_material = -1;

    std::string str;
    while (!file.eof() && !file.fail() && !file.bad())
    {
        std::getline(file, str);
        ParseLine(str);
    } // while

    m_pcurr_geom_obj    = 0;
    m_pcurr_mat_def     = 0;
    m_pcurr_helper_obj  = 0;
    m_curr_face_normal  = -1;
    m_curr_vert_normal  = -1;
    m_curr_sub_material = -1;

    std::vector<GeomObject *> objects = m_objects;
    m_objects.clear();

    // Create the indexed vertex array data
    for (size_t i = 0; i < objects.size(); i++)
    {
        GeomObject *pobj = objects[i];

        if (pobj->material >= 0)
        {
            std::map<uint, MaterialDef *>::iterator mat_iter = m_materials.find(pobj->material);
            if (mat_iter == m_materials.end())
                return false;

            MaterialDef *pmat_def = mat_iter->second;
            if (pmat_def->sub_materials.empty())
            {
                m_objects.push_back(pobj);
            } // if
            else
            {
                if (!RebuildGeomObjectForSubMaterials(pobj))
                    return false;

                continue;
            } // else
        } // if
        else
        {
            m_objects.push_back(pobj);
        } // else

        // Get the number of faces in the mesh
        size_t num_faces = pobj->face_records.size();

        // Allocate the face and vertex records
        pobj->faces.resize(num_faces);
        pobj->verticies.resize(num_faces * 3);

        // See if we have vertex colours
        bool has_col_verts = !pobj->col_verts.empty();

        // Fill out the face and vertex information
        for (size_t j = 0; j < num_faces; j++)
        {
            FaceRecord &face_rec = pobj->face_records[j];

            // Face indicies (a, c, b)
            pobj->faces[j].Assign((j * 3), (j * 3) + 2, (j * 3) + 1);

            // Vertex co-ordinates
            pobj->verticies[(j * 3)].loc     = face_rec.verticies.a;
            pobj->verticies[(j * 3) + 1].loc = face_rec.verticies.b;
            pobj->verticies[(j * 3) + 2].loc = face_rec.verticies.c;

            // Vertex normals
            D3DXVec3Normalize(&pobj->verticies[(j * 3)].norm,     &face_rec.normals.a);
            D3DXVec3Normalize(&pobj->verticies[(j * 3) + 1].norm, &face_rec.normals.b);
            D3DXVec3Normalize(&pobj->verticies[(j * 3) + 2].norm, &face_rec.normals.c);

            // Vertex colours
            if (has_col_verts)
            {
                pobj->verticies[(j * 3)].diff     = Color(face_rec.colours.a);
                pobj->verticies[(j * 3) + 1].diff = Color(face_rec.colours.b);
                pobj->verticies[(j * 3) + 2].diff = Color(face_rec.colours.c);
            } // if
            else
            {
                pobj->verticies[(j * 3)].diff     = Color::White;
                pobj->verticies[(j * 3) + 1].diff = Color::White;
                pobj->verticies[(j * 3) + 2].diff = Color::White;
            } // else

            // Vertex uv coordinates
            pobj->verticies[(j * 3)].u        = face_rec.uv_coords.a[0];
            pobj->verticies[(j * 3)].v        = face_rec.uv_coords.a[1];
            pobj->verticies[(j * 3) + 1].u    = face_rec.uv_coords.b[0];
            pobj->verticies[(j * 3) + 1].v    = face_rec.uv_coords.b[1];
            pobj->verticies[(j * 3) + 2].u    = face_rec.uv_coords.c[0];
            pobj->verticies[(j * 3) + 2].v    = face_rec.uv_coords.c[1];
        } // for

        // See if we need a default material, if so - create one with
        // the wireframe color
        if (pobj->material == -1)
        {
            MaterialDef *pmat   = new MaterialDef();
            pmat->id            = MakeDefaultMaterialId(m_materials.size());
            pobj->material      = pmat->id;

            pmat->diffuse       = pobj->wireframe_col;
            pmat->ambient       = Color::Black;
            pmat->emissive      = Color::Black;
            pmat->specular      = Color::Gray;
            pmat->power         = 100.0f;

            m_materials[pmat->id] = pmat;
            return true;
        } // if
    } // for

    return true;
} // ParseFile


// ----------------------------------------------------------------------------
// Name: ASE::RebuildGeomObjectForSubMaterials
// Desc: Rebuild a geom object to use sub-materials
// Parm: GeomObject *pobj - the geom object
// Retn: bool             - true if succeeded
// ----------------------------------------------------------------------------
bool ASE::RebuildGeomObjectForSubMaterials(GeomObject *pobj)
{
    std::map<uint, MaterialDef *>::iterator mat_iter = m_materials.find(pobj->material);
    if (mat_iter == m_materials.end())
    {
        m_objects.push_back(pobj);
        return false;
    } // if

    int mat_id              = mat_iter->first;
    MaterialDef *pmat_def   = mat_iter->second;

    size_t total_faces = 0;

    int count = 0;
    std::map<int, MaterialDef *>::iterator sub_mat_iter = pmat_def->sub_materials.begin();
    for (; sub_mat_iter != pmat_def->sub_materials.end(); sub_mat_iter++)
    {
        // Get the sub material information
        int sub_mat_id              = sub_mat_iter->first;
        MaterialDef *sub_mat_def    = sub_mat_iter->second;

        // Create a geom object for this sub-material
        GeomObject *pnew_obj        = new GeomObject();
        pnew_obj->name              = pobj->name;
        String::AppendInt(pnew_obj->name, static_cast<int>(count++));

        // Copy the geom object details
        pnew_obj->parent_name       = pobj->parent_name;
        pnew_obj->matrix            = pobj->matrix;
        pnew_obj->material          = MakeCombinedMaterialId(mat_id, sub_mat_id);

        // Get the number of faces in the mesh with the selected
        // sub-material id
        size_t num_faces = 0;
        for (size_t i = 0; i < pobj->face_records.size(); i++)
        {
            if (pobj->face_records[i].sub_mat_id == sub_mat_id)
                num_faces++;
        } // for

        total_faces += num_faces;

        if (num_faces == 0)
        {
            delete pnew_obj;
            continue;
        } // if
        
        // Allocate the face and vertex records
        pnew_obj->faces.resize(num_faces);
        pnew_obj->verticies.resize(num_faces * 3);

        // See if we have vertex colours
        bool has_col_verts = !pobj->col_verts.empty();

        // Fill out the face and vertex information
        size_t j = 0;
        for (size_t i = 0; i < pobj->face_records.size(); i++)
        {
            FaceRecord &face_rec = pobj->face_records[i];
            if (face_rec.sub_mat_id != sub_mat_id)
                continue;

            // Face indicies (a, c, b)
            pnew_obj->faces[j].Assign((j * 3), (j * 3) + 2, (j * 3) + 1);

            // Vertex co-ordinates
            pnew_obj->verticies[(j * 3)].loc     = face_rec.verticies.a;
            pnew_obj->verticies[(j * 3) + 1].loc = face_rec.verticies.b;
            pnew_obj->verticies[(j * 3) + 2].loc = face_rec.verticies.c;

            // Vertex normals
            D3DXVec3Normalize(&pnew_obj->verticies[(j * 3)].norm,     &face_rec.normals.a);
            D3DXVec3Normalize(&pnew_obj->verticies[(j * 3) + 1].norm, &face_rec.normals.b);
            D3DXVec3Normalize(&pnew_obj->verticies[(j * 3) + 2].norm, &face_rec.normals.c);

            // Vertex colours
            if (has_col_verts)
            {
                pnew_obj->verticies[(j * 3)].diff     = Color(face_rec.colours.a);
                pnew_obj->verticies[(j * 3) + 1].diff = Color(face_rec.colours.b);
                pnew_obj->verticies[(j * 3) + 2].diff = Color(face_rec.colours.c);
            } // if
            else
            {
                pnew_obj->verticies[(j * 3)].diff     = Color::White;
                pnew_obj->verticies[(j * 3) + 1].diff = Color::White;
                pnew_obj->verticies[(j * 3) + 2].diff = Color::White;
            } // else

            // Vertex uv coordinates
            pnew_obj->verticies[(j * 3)].u        = face_rec.uv_coords.a[0];
            pnew_obj->verticies[(j * 3)].v        = face_rec.uv_coords.a[1];
            pnew_obj->verticies[(j * 3) + 1].u    = face_rec.uv_coords.b[0];
            pnew_obj->verticies[(j * 3) + 1].v    = face_rec.uv_coords.b[1];
            pnew_obj->verticies[(j * 3) + 2].u    = face_rec.uv_coords.c[0];
            pnew_obj->verticies[(j * 3) + 2].v    = face_rec.uv_coords.c[1];

            j++;
        } // for
        m_objects.push_back(pnew_obj);
    } // for

    if (total_faces != pobj->face_records.size())
    {
        delete pobj;
        return false;
    } // if

    delete pobj;
    return true;
} // RebuildGeomObjectForSubMaterials


// ----------------------------------------------------------------------------
// Name: ASE::ParseLine
// Desc: Parse a single line of the ASE file
// Parm: const std::string &str - the line text
// Retn: bool                   - true if the line was read successfully
// ----------------------------------------------------------------------------
bool ASE::ParseLine(const std::string &str)
{
    std::vector<std::string> tokens;

    std::stringstream ss;
    ss << str;

    std::string token;
    ss >> token;

    return ProcessCommand(token, ss);
} // AddTokens


// ----------------------------------------------------------------------------
// Name: ASE::ProcessCommand
// Desc: Based on the first token on the line (the command), we can parse the 
//       rest of the line to extract the data.
// Parm: const std::string &command - the command
// Parm: std::stringstream &ss      - the line as a stream
// Retn: bool                       - true if the line was parsed successfully
// ----------------------------------------------------------------------------
bool ASE::ProcessCommand(const std::string &command, std::stringstream &ss)
{
    std::string tmp;

    // ------------------------------------------------------------------------
    // Material section start record
    // ------------------------------------------------------------------------
    if (command == "*MATERIAL")
    {
        MaterialDef *pmat = new MaterialDef();
        ss >> pmat->id;

        pmat->diffuse       = Color::White;
        pmat->ambient       = Color::Black;
        pmat->emissive      = Color::Black;
        pmat->specular      = Color::Gray;
        pmat->power         = 100.0f;

        pmat->curr_tex_map = MaterialCache::unknown;

        m_pcurr_mat_def     = pmat;
        m_pcurr_geom_obj    = 0;
        m_pcurr_helper_obj  = 0;
        m_curr_face_normal  = -1;
        m_curr_vert_normal  = -1;
        m_curr_sub_material = -1;

        m_materials[pmat->id] = pmat;
        return true;
    } // if


    // ------------------------------------------------------------------------
    // Sub-Material section start record
    // ------------------------------------------------------------------------
    if (command == "*SUBMATERIAL")
    {
        if (!m_pcurr_mat_def)
            return false;

        MaterialDef *pmat = new MaterialDef();
        ss >> pmat->id;
        
        pmat->diffuse       = Color::White;
        pmat->ambient       = Color::Black;
        pmat->emissive      = Color::Black;
        pmat->specular      = Color::Gray;
        pmat->power         = 100.0f;

        pmat->curr_tex_map = MaterialCache::unknown;
        m_curr_sub_material = pmat->id;

        m_pcurr_mat_def->sub_materials[pmat->id] = pmat;
        return true;
    } // if


    // ------------------------------------------------------------------------
    // Ambient color record
    // ------------------------------------------------------------------------
    else if (command == "*MATERIAL_AMBIENT")
    {
        if (!m_pcurr_mat_def)
            return false;

        MaterialDef *pmat = m_pcurr_mat_def;
        if (m_curr_sub_material != -1)
            pmat = m_pcurr_mat_def->sub_materials[m_curr_sub_material];

        if (!pmat)
            return false;

        float r, g, b;

        ss >> r;
        ss >> g;
        ss >> b;

        pmat->ambient = Color(r, g, b, 1.0f);
    } // else if


    // ------------------------------------------------------------------------
    // Diffuse color record
    // ------------------------------------------------------------------------
    else if (command == "*MATERIAL_DIFFUSE")
    {
        if (!m_pcurr_mat_def)
            return false;

        MaterialDef *pmat = m_pcurr_mat_def;
        if (m_curr_sub_material != -1)
            pmat = m_pcurr_mat_def->sub_materials[m_curr_sub_material];

        if (!pmat)
            return false;

        float r, g, b;

        ss >> r;
        ss >> g;
        ss >> b;

        pmat->diffuse = Color(r, g, b, 1.0f);
    } // else if


    // ------------------------------------------------------------------------
    // Specular color record
    // ------------------------------------------------------------------------
    else if (command == "*MATERIAL_SPECULAR")
    {
        if (!m_pcurr_mat_def)
            return false;

        MaterialDef *pmat = m_pcurr_mat_def;
        if (m_curr_sub_material != -1)
            pmat = m_pcurr_mat_def->sub_materials[m_curr_sub_material];

        if (!pmat)
            return false;

        float r, g, b;

        ss >> r;
        ss >> g;
        ss >> b;

        pmat->specular = Color(r, g, b, 1.0f);
    } // else if


    // ------------------------------------------------------------------------
    // Diffuse texture map section start record
    // ------------------------------------------------------------------------
    else if (command == "*MAP_DIFFUSE")
    {
        if (!m_pcurr_mat_def)
            return false;

        MaterialDef *pmat = m_pcurr_mat_def;
        if (m_curr_sub_material != -1)
            pmat = m_pcurr_mat_def->sub_materials[m_curr_sub_material];

        if (!pmat)
            return false;

        pmat->curr_tex_map = MaterialCache::tex_map1;
    } // else if


    // ------------------------------------------------------------------------
    // Opacity texture map section start record
    // ------------------------------------------------------------------------
    else if (command == "*MAP_OPACITY")
    {
        if (!m_pcurr_mat_def)
            return false;

        MaterialDef *pmat = m_pcurr_mat_def;
        if (m_curr_sub_material != -1)
            pmat = m_pcurr_mat_def->sub_materials[m_curr_sub_material];

        if (!pmat)
            return false;

        pmat->curr_tex_map = MaterialCache::tex_map2;
    } // else if    


    // ------------------------------------------------------------------------
    // Texture map filename record
    // ------------------------------------------------------------------------
    else if (command == "*BITMAP")
    {
        if (!m_pcurr_mat_def)
            return false;

        MaterialDef *pmat = m_pcurr_mat_def;
        if (m_curr_sub_material != -1)
            pmat = m_pcurr_mat_def->sub_materials[m_curr_sub_material];

        if (!pmat)
            return false;

        std::string str = ss.str();

        std::string::size_type start_pos, end_pos;
        start_pos = str.find_first_of("\"");
        end_pos   = str.find_last_of("\"");

        if (start_pos == std::string::npos || end_pos == std::string::npos)
            return false;

        switch (pmat->curr_tex_map)
        {
        case MaterialCache::tex_map1:
            pmat->tex_map1 = str.substr(start_pos + 1, end_pos - (start_pos + 1));
            FilePath::StripPath(pmat->tex_map1);
            break;
        case MaterialCache::tex_map2:
            pmat->opac_map = str.substr(start_pos + 1, end_pos - (start_pos + 1));
            FilePath::StripPath(pmat->opac_map);
            break;
        } // switch

        return true;
    } // else if


    // ------------------------------------------------------------------------
    // Geometry object section start record
    // ------------------------------------------------------------------------
    else if (command == "*GEOMOBJECT")
    {
        GeomObject *pobj = new GeomObject();
        D3DXMatrixIdentity(&pobj->matrix);
        pobj->material = -1;
        pobj->wireframe_col = Color::White;

        m_objects.push_back(pobj);
        
        m_pcurr_geom_obj    = pobj;
        m_pcurr_helper_obj  = 0;
        m_pcurr_mat_def     = 0;
        m_curr_face_normal  = -1;
        m_curr_vert_normal  = -1;
        m_curr_sub_material = -1;

        return true;
    } // if


    // ------------------------------------------------------------------------
    // Helper object section start record
    // ------------------------------------------------------------------------
    else if (command == "*HELPEROBJECT")
    {
        HelperObject *pobj = new HelperObject();
        D3DXMatrixIdentity(&pobj->matrix);

        m_helpers.push_back(pobj);
        
        m_pcurr_geom_obj    = 0;
        m_pcurr_helper_obj  = pobj;
        m_pcurr_mat_def     = 0;
        m_curr_face_normal  = -1;
        m_curr_vert_normal  = -1;
        m_curr_sub_material = -1;

        return true;
    } // if


    // ------------------------------------------------------------------------
    // Geom or helper node name record
    // ------------------------------------------------------------------------
    else if (command == "*NODE_NAME")
    {
        if (m_pcurr_geom_obj)
        {
            ss >> m_pcurr_geom_obj->name;
            String::TrimQuotes(m_pcurr_geom_obj->name);
        }
        else if (m_pcurr_helper_obj)
        {
            ss >> m_pcurr_helper_obj->name;
            String::TrimQuotes(m_pcurr_helper_obj->name);
        }
        else
            return false;

        return (ss.fail());
    } // if


    // ------------------------------------------------------------------------
    // Geom or helper parent node name record
    // ------------------------------------------------------------------------
    else if (command == "*NODE_PARENT")
    {
        if (m_pcurr_geom_obj)
        {
            ss >> m_pcurr_geom_obj->parent_name;
            String::TrimQuotes(m_pcurr_geom_obj->parent_name);
        }
        else if (m_pcurr_helper_obj)
        {
            ss >> m_pcurr_helper_obj->parent_name;
            String::TrimQuotes(m_pcurr_helper_obj->parent_name);
        }
        else
            return false;

        return (ss.fail());
    } // if


    // ------------------------------------------------------------------------
    // Matrix row 0 record
    // ------------------------------------------------------------------------
    else if (command == "*TM_ROW0")
    {
        Matrix *pmatrix = 0;

        if (m_pcurr_geom_obj)
            pmatrix = &m_pcurr_geom_obj->matrix;
        else if (m_pcurr_helper_obj)
            pmatrix = &m_pcurr_helper_obj->matrix;
        else
            return false;

        ss >> (*pmatrix)(0, 0);
        ss >> (*pmatrix)(0, 1);
        ss >> (*pmatrix)(0, 2);

        return (ss.fail());
    } // else if


    // ------------------------------------------------------------------------
    // Matrix row 1 record
    // ------------------------------------------------------------------------
    else if (command == "*TM_ROW1")
    {
        Matrix *pmatrix = 0;

        if (m_pcurr_geom_obj)
            pmatrix = &m_pcurr_geom_obj->matrix;
        else if (m_pcurr_helper_obj)
            pmatrix = &m_pcurr_helper_obj->matrix;
        else
            return false;

        ss >> (*pmatrix)(1, 0);
        ss >> (*pmatrix)(1, 1);
        ss >> (*pmatrix)(1, 2);

        return (ss.fail());
    } // else if


    // ------------------------------------------------------------------------
    // Matrix row 2 record
    // ------------------------------------------------------------------------
    else if (command == "*TM_ROW2")
    {
        Matrix *pmatrix = 0;

        if (m_pcurr_geom_obj)
            pmatrix = &m_pcurr_geom_obj->matrix;
        else if (m_pcurr_helper_obj)
            pmatrix = &m_pcurr_helper_obj->matrix;
        else
            return false;

        ss >> (*pmatrix)(2, 0);
        ss >> (*pmatrix)(2, 1);
        ss >> (*pmatrix)(2, 2);

        return (ss.fail());
    } // else if


    // ------------------------------------------------------------------------
    // Matrix row 3 record
    // ------------------------------------------------------------------------
    else if (command == "*TM_ROW3")
    {
        Matrix *pmatrix = 0;

        if (m_pcurr_geom_obj)
            pmatrix = &m_pcurr_geom_obj->matrix;
        else if (m_pcurr_helper_obj)
            pmatrix = &m_pcurr_helper_obj->matrix;
        else
            return false;

        ss >> (*pmatrix)(3, 0);
        ss >> (*pmatrix)(3, 1);
        ss >> (*pmatrix)(3, 2);

        return (ss.fail());
    } // else if


    // ------------------------------------------------------------------------
    // Geom object material index record
    // ------------------------------------------------------------------------
    else if (command == "*MATERIAL_REF")
    {
        if (!m_pcurr_geom_obj)
            return false;

        int id;
        ss >> id;
        m_pcurr_geom_obj->material = id;
    } // else if


    // ------------------------------------------------------------------------
    // Geom object wireframe colour record
    // ------------------------------------------------------------------------
    else if (command == "*WIREFRAME_COLOR")
    {
        if (!m_pcurr_geom_obj)
            return false;

        if (m_pcurr_geom_obj->material >= 0)
            return true;        

        float r, g, b;
        ss >> r;
        ss >> g;
        ss >> b;

        Color color(r, g, b, 1.0f);
        ulong col_ulong = color.operator DWORD();
        m_pcurr_geom_obj->wireframe_col = col_ulong;

    } // else if


    // ------------------------------------------------------------------------
    // Number of vertecies record
    // ------------------------------------------------------------------------
    else if (command == "*MESH_NUMVERTEX")
    {
        if (!m_pcurr_geom_obj)
            return false;

        size_t num = 0;
        ss >> num;

        m_pcurr_geom_obj->vert_records.resize(num);
    } // else if


    // ------------------------------------------------------------------------
    // Mesh vertex record
    // ------------------------------------------------------------------------
    else if (command == "*MESH_VERTEX")
    {
        if (!m_pcurr_geom_obj)
            return false;

        size_t num = 0;
        ss >> num;

        Vec3 &vec = m_pcurr_geom_obj->vert_records[num];
        ss >> vec[0];
        ss >> vec[1];
        ss >> vec[2];

        // Convert RH to LH
        //vec[2] = 0.0f - vec[2];

        return (ss.fail());
    } // else if


    // ------------------------------------------------------------------------
    // Number of indicies record
    // ------------------------------------------------------------------------
    else if (command == "*MESH_NUMFACES")
    {
        if (!m_pcurr_geom_obj)
            return false;

        size_t num = 0;
        ss >> num;

        m_pcurr_geom_obj->face_records.resize(num);
    } // else if


    // ------------------------------------------------------------------------
    // Mesh face (index) record
    // ------------------------------------------------------------------------
    else if (command == "*MESH_FACE")
    {
        if (!m_pcurr_geom_obj)
            return false;

        size_t num = 0;
        ss >> tmp;
        num = atoi(tmp.substr(0, tmp.size() - 1).c_str());

        // Face indicies
        int vert_a, vert_b, vert_c;

        ss >> tmp;
        ss >> vert_a;

        ss >> tmp;
        ss >> vert_b;

        ss >> tmp;
        ss >> vert_c;

        // Get the sub material id
        FaceRecord &face_rec = m_pcurr_geom_obj->face_records[num];
        while (!ss.eof() && !ss.fail() && !ss.bad())
        {
            ss >> tmp;
            if (tmp == "*MESH_MTLID")
            {
                ss >> face_rec.sub_mat_id;
                break;
            } // if
        } // while

        // Set the verticies
        face_rec.verticies.a = m_pcurr_geom_obj->vert_records[vert_a];
        face_rec.verticies.b = m_pcurr_geom_obj->vert_records[vert_b];
        face_rec.verticies.c = m_pcurr_geom_obj->vert_records[vert_c];

        return (ss.fail());
    } // else if
    

    // ------------------------------------------------------------------------
    // Face normal record
    // ------------------------------------------------------------------------
    else if (command == "*MESH_FACENORMAL")
    {
        if (!m_pcurr_geom_obj)
            return false;

        ss >> m_curr_face_normal;
        m_curr_vert_normal = 0;

        return (ss.fail());
    } // else if


    // ------------------------------------------------------------------------
    // Vertex normal record
    // ------------------------------------------------------------------------
    else if (command == "*MESH_VERTEXNORMAL")
    {
        if (!m_pcurr_geom_obj)
            return false;

        if (m_curr_vert_normal < 0 || m_curr_vert_normal > 2)
            return false;

        size_t num = 0;
        ss >> num;

        FaceRecord &face_rec = m_pcurr_geom_obj->face_records[m_curr_face_normal];
        switch (m_curr_vert_normal)
        {
        case 0:
            {
                Vec3 &vec = face_rec.normals.a;

                ss >> vec[0];
                ss >> vec[1];
                ss >> vec[2];

                //vec[0] = 0.0f - vec[0];
                //vec[1] = 0.0f - vec[1];
                vec[2] = 0.0f - vec[2];
        
                D3DXVec3Normalize(&vec, &vec);
                m_curr_vert_normal++;
                return (ss.fail());
            } // case            

        case 2:
            {
                Vec3 &vec = face_rec.normals.c;

                ss >> vec[0];
                ss >> vec[1];
                ss >> vec[2];

                //vec[0] = 0.0f - vec[0];
                //vec[1] = 0.0f - vec[1];
                vec[2] = 0.0f - vec[2];
        
                D3DXVec3Normalize(&vec, &vec);
                m_curr_vert_normal++;
                return (ss.fail());
            } // case            


        case 1:
            {
                Vec3 &vec = face_rec.normals.b;

                ss >> vec[0];
                ss >> vec[1];
                ss >> vec[2];

                //vec[0] = 0.0f - vec[0];
                //vec[1] = 0.0f - vec[1];
                vec[2] = 0.0f - vec[2];
        
                D3DXVec3Normalize(&vec, &vec);
                m_curr_vert_normal++;
                return (ss.fail());
            } // case            
        } // switch

        return false;
    } // else if


    // ------------------------------------------------------------------------
    // Number of texture verticies record
    // ------------------------------------------------------------------------
    else if (command == "*MESH_NUMTVERTEX")
    {
        if (!m_pcurr_geom_obj)
            return false;

        size_t num = 0;
        ss >> num;

        m_pcurr_geom_obj->tex_verts.resize(num);
    } // else if


    // ------------------------------------------------------------------------
    // Vertex texture uv record
    // ------------------------------------------------------------------------
    else if (command == "*MESH_TVERT")
    {
        if (!m_pcurr_geom_obj)
            return false;

        size_t num = 0;
        ss >> num;

        Vec3 &vec = m_pcurr_geom_obj->tex_verts[num];

        ss >> vec[0];   // u
        ss >> vec[1];   // v
        ss >> vec[2];   // w (not used)

        vec[1] = 0 - vec[1];
        
        return (ss.fail());
    } // else if


    // ------------------------------------------------------------------------
    // Face texture index record
    // ------------------------------------------------------------------------
    else if (command == "*MESH_TFACE")
    {
        if (!m_pcurr_geom_obj)
            return false;

        size_t vert_a, vert_b, vert_c, num = 0;
        ss >> num;
        ss >> vert_a;
        ss >> vert_b;
        ss >> vert_c;

        FaceRecord &face_rec = m_pcurr_geom_obj->face_records[num];
        face_rec.uv_coords.a = m_pcurr_geom_obj->tex_verts[vert_a];
        face_rec.uv_coords.b = m_pcurr_geom_obj->tex_verts[vert_b];
        face_rec.uv_coords.c = m_pcurr_geom_obj->tex_verts[vert_c];

        return (ss.fail());
    } // else if


    // ------------------------------------------------------------------------
    // Number of vertex colours record
    // ------------------------------------------------------------------------
    else if (command == "*MESH_NUMCVERTEX")
    {
        if (!m_pcurr_geom_obj)
            return false;

        size_t num = 0;
        ss >> num;

        if (num == 0)
            return true;

        // Allocate a vertex colour for each vertex
        //m_pcurr_geom_obj->col_verts.resize(m_pcurr_geom_obj->vert_records.size());
        m_pcurr_geom_obj->col_verts.resize(num);

        // Default all vertex colors to white
        //for (size_t i = 0; i < m_pcurr_geom_obj->verticies.size(); i++)
        //    m_pcurr_geom_obj->col_verts[i] = Vec3(1.0f, 1.0f, 1.0f);
        for (size_t i = 0; i < num; i++)
            m_pcurr_geom_obj->col_verts[i] = Vec3(1.0f, 1.0f, 1.0f);

    } // else if


    // ------------------------------------------------------------------------
    // Vertex colour record
    // ------------------------------------------------------------------------
    else if (command == "*MESH_VERTCOL")
    {
        if (!m_pcurr_geom_obj)
            return false;

        size_t num = 0;
        ss >> num;

        Vec3 &vec = m_pcurr_geom_obj->col_verts[num];
        ss >> vec[0];
        ss >> vec[1];
        ss >> vec[2];

        return (ss.fail());
    } // else if


    // ------------------------------------------------------------------------
    // Vertex face index record
    // ------------------------------------------------------------------------
    else if (command == "*MESH_CFACE")
    {
        if (!m_pcurr_geom_obj)
            return false;

        size_t vert_a, vert_b, vert_c, num = 0;
        ss >> num;
        ss >> vert_a;
        ss >> vert_b;
        ss >> vert_c;

        Mesh_IndexVertArray::Face &face = m_pcurr_geom_obj->faces[num];

        FaceRecord &face_rec = m_pcurr_geom_obj->face_records[num];
        face_rec.colours.a   = m_pcurr_geom_obj->col_verts[vert_a];
        face_rec.colours.b   = m_pcurr_geom_obj->col_verts[vert_b];
        face_rec.colours.c   = m_pcurr_geom_obj->col_verts[vert_c];

        return (ss.fail());
    } // else if


    return true;
} // ProcessCommand



// -- EOF

