
#include "Render/Mesh.h"


// ----------------------------------------------------------------------------
// Initialise the static members
// ----------------------------------------------------------------------------
ulong   Mesh::s_id_counter  = 0;


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
MeshInstance::MeshInstance(Mesh *pparent, const String &name, const Matrix &matrix)
: m_pobject       (pparent),
  m_name          (name),
  m_last_frame    (0),
  m_world_matrix  (matrix)
{
  REF_COUNT_CTOR(MeshInstance);

  SafeRef(m_pobject);
} // MeshInstance


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
MeshInstance::MeshInstance(const MeshInstance &other)
: m_pobject       (other.m_pobject),
  m_name          (other.m_name),
  m_last_frame    (other.m_last_frame),
  m_world_matrix  (other.m_world_matrix)
{
  REF_COUNT_CTOR(MeshInstance);

  SafeRef(m_pobject);
} // MeshInstance


// ----------------------------------------------------------------------------
// Assignment operator
// ----------------------------------------------------------------------------
MeshInstance &MeshInstance::operator=(const MeshInstance &other)
{
  REF_COUNT_CTOR(MeshInstance);

  SafeUnRef(m_pobject);

  m_name = other.m_name;
  m_pobject = other.m_pobject;
  m_world_matrix = other.m_world_matrix;
  m_last_frame = other.m_last_frame;

  SafeRef(m_pobject);

  return *this;
} // operator=


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
MeshInstance::~MeshInstance()
{
  REF_COUNT_DTOR(MeshInstance);
  m_pobject->UnRef();
} // ~MeshInstance


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
Mesh::Mesh(const String &name)
: m_name          (name),
  m_id            (++Mesh::s_id_counter)
{
  REF_COUNT_CTOR(Mesh);
} // Mesh


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
Mesh::~Mesh()
{
  REF_COUNT_DTOR(Mesh);

  for (uint i = 0; i < m_SubsetArray.size(); i++)
    delete m_SubsetArray[i];
} // ~Mesh


// ----------------------------------------------------------------------------
// Name: Mesh::Load
// Desc: Load the mesh from the file
// Parm: FileHandle handle - the file handle
// Retn: bool              - true if loaded
// ----------------------------------------------------------------------------
bool Mesh::Load(FileHandle handle)
{
  FILE *pFile = fopen(handle.GetAbsoluteFilename().c_str(), "rb");
  if (!pFile)
    return false;

  bool result = Load(pFile);
  fclose(pFile);
  return result;
} // Load


// ----------------------------------------------------------------------------
// Name: Mesh::Save
// Desc: Save the mesh to the file
// Parm: FileHandle handle - the file handle
// Retn: bool              - true if saved
// ----------------------------------------------------------------------------
bool Mesh::Save(FileHandle handle)
{
  FILE *pFile = fopen(handle.GetAbsoluteFilename().c_str(), "wb");
  if (!pFile)
    return false;

  bool result = Save(pFile);
  fclose(pFile);
  return result;
} // Save


// ----------------------------------------------------------------------------
// Name: MeshSubset::MeshSubset
// Desc: Constructor
// ----------------------------------------------------------------------------
MeshSubset::MeshSubset()
: m_pMaterial     (NULL)
{
  ZeroMemory(&m_ColorMaterial, sizeof(D3DMATERIAL9));
  m_FaceCount = 0;
  m_FaceStart = 0;
} // MeshSubset


// ----------------------------------------------------------------------------
// Name: MeshSubset::~MeshSubset
// Desc: Destructor
// ----------------------------------------------------------------------------
MeshSubset::~MeshSubset()
{
  SafeUnRef(m_pMaterial);
} // ~MeshSubset


// ----------------------------------------------------------------------------
// Print the subsets
// ----------------------------------------------------------------------------
void Mesh::PrintSubsets()
{
  for (uint i = 0; i < GetNumSubsets(); i++)
  {
    MeshSubset &subset = *(GetSubset(i));

    LOG_INFO << "Subset: " 
      << subset.GetFaceStart() << ", " 
      << subset.GetFaceCount() << ", " 
      << (subset.GetMaterial() ? subset.GetMaterial()->GetFileHandle().GetFilename() : "NULL") << ", " 
      << (subset.GetTextureArray().GetDiffuse() ? subset.GetTextureArray().GetDiffuse()->GetFileHandle().GetFilename() : "NULL") 
      << ENDLOG;
  } // for
} // PrintSubsets


// ----------------------------------------------------------------------------
// Create an instance of a mesh
// ----------------------------------------------------------------------------
MeshInstance *Mesh::CreateInstance(const String &name)
{
  return new MeshInstance(this, name);
} // CreateInstance


// ----------------------------------------------------------------------------
// Create an instance of a mesh
// ----------------------------------------------------------------------------
MeshInstance *Mesh::CreateInstance(const String &name, const Matrix &matrix)
{
  return new MeshInstance(this, name, matrix);
} // CreateInstance


// ----------------------------------------------------------------------------
// Get the bounding sphere of a mesh
// ----------------------------------------------------------------------------
const Sphere &Mesh::GetBSphere() const
{
  return m_sphere;
} // GetBSphere


// ----------------------------------------------------------------------------
// Get the bounding box of a mesh
// ----------------------------------------------------------------------------
const Box &Mesh::GetBBox() const
{
  return m_box;
} // GetBBox


// ----------------------------------------------------------------------------
// Test for an intersection with the bounding sphere
// ----------------------------------------------------------------------------
bool Mesh::IntersectsBSphere(const Ray &ray) const
{
  return m_sphere.TestCollision(ray);
} // IntersectsBSphere


// ----------------------------------------------------------------------------
// Load the mesh from a file
// ----------------------------------------------------------------------------
bool Mesh::Load(FILE *pFile)
{
  return false;
} // Load


// ----------------------------------------------------------------------------
// Save the mesh to a file
// ----------------------------------------------------------------------------
bool Mesh::Save(FILE *pFile)
{
  return false;
} // Save


// -- EOF
