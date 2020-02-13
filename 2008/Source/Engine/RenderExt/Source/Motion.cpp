
#include "Motion.h"


#define CAL3D_MAXBONES_PER_MESH 29
#define CAL3D_MAXVERTS          30000
#define CAL3D_MAXFACES          150000
#define CAL3D_VERTEX_TYPE       "VertexType_PNT_ANIM"
#define CAL3D_MATERIAL          "Material_PNT_ANIM"


Motion::Motion()
: m_pIndexedMesh      (NULL),
  m_pMaterial         (NULL),
  m_pCalHardwareModel (NULL),
  m_pCalCoreModel     (NULL),
  m_pCalModel         (NULL),
  m_pMixer            (NULL)
{
}


Motion::~Motion()
{
  // todo: cleanup
  // IndexedMesh
  // m_pMixer
  // textures in user data (addRef)
}


AnimationMixer *Motion::GetMixer()
{
  NULL_ASSERT(m_pMixer);
  return m_pMixer;
}


const AnimationMixer *Motion::GetMixer() const
{
  NULL_ASSERT(m_pMixer);
  return m_pMixer;
}


bool Motion::Load(FileHandle handle)
{
  // Load the config file
  ConfigFile cfg;
  if (!cfg.Load(handle.GetAbsoluteFilename()))
  {
    LOG_ERROR << "Failed to load the Motion config file: " << handle << ENDLOG;
    return false;
  }

  // Create the core model
  m_pCalCoreModel = new CalCoreModel("");

  // Flags for loading
  bool loadedSkeleton = false;

  // Get all root sections from the config file
  const ConfigSectionMap &rootSections = cfg.GetSections();

  // Iterate over all sections in the config
  ConfigSectionMap::const_iterator sectionIter(rootSections.begin()), sectionEnd(rootSections.end());
  for (; sectionIter != sectionEnd; ++sectionIter)
  {
    // Get the config section
    const ConfigSection &section = sectionIter->second;

    // Load the skeleton
    if (StrICmp(section.Type, "Skeleton"))
    {
      ConfigValueMap::const_iterator valueIter(section.Items.begin()), valueEnd(section.Items.end());
      for (; valueIter != valueEnd; ++valueIter)
      {
        // Check we have not already loaded the skeleton
        if (loadedSkeleton)
        {
          LOG_ERROR << "Duplicate Skeleton entry in the Motion config file: " << handle << ENDLOG;
          return false;
        }

        // Get the value
        const ConfigValue &value = valueIter->second;

        // Load the skeleton
        FileHandle skeletonHandle = Application.GetModelDatabase()->FindFileHandle(value.Value);
        if (!m_pCalCoreModel->loadCoreSkeleton(skeletonHandle.GetAbsoluteFilename()))
        {
          LOG_ERROR << "Failed to load the skeleton from the file: " << skeletonHandle << ENDLOG;
          return false;
        }

        // Mark the skeleton as loaded
        loadedSkeleton = true;
      }
    }

    // Load the meshes
    if (StrICmp(section.Type, "Mesh"))
    {
      ConfigValueMap::const_iterator meshIter(section.Items.begin()), meshEnd(section.Items.end());
      for (; meshIter != meshEnd; ++meshIter)
      {
        const ConfigValue &value = meshIter->second;

        // Load the mesh
        FileHandle meshHandle = Application.GetModelDatabase()->FindFileHandle(value.Value);
        if (m_pCalCoreModel->loadCoreMesh(meshHandle.GetAbsoluteFilename()) == -1)
        {
          LOG_ERROR << "Failed to load the mesh from the file: " << meshHandle << ENDLOG;
          return false;
        }
      }
    }

    // Load the materials
    if (StrICmp(section.Type, "Material"))
    {
      ConfigValueMap::const_iterator materialIter(section.Items.begin()), materialEnd(section.Items.end());
      for (; materialIter != materialEnd; ++materialIter)
      {
        const ConfigValue &value = materialIter->second;

        // Load the material
        FileHandle materialHandle = Application.GetModelDatabase()->FindFileHandle(value.Value);
        if (m_pCalCoreModel->loadCoreMaterial(materialHandle.GetAbsoluteFilename()) == -1)
        {
          LOG_ERROR << "Failed to load the material from the file: " << materialHandle << ENDLOG;
          return false;
        }
      }
    }
  }

  if (!loadedSkeleton)
  {
    LOG_ERROR << "No skeleton specified in the Motion config file: " << handle << ENDLOG;
    return false;
  }

  for (int materialId = 0; materialId < m_pCalCoreModel->getCoreMaterialCount(); materialId++)
  {
    // create the a material thread
    m_pCalCoreModel->createCoreMaterialThread(materialId);

    // initialize the material thread
    m_pCalCoreModel->setCoreMaterialId(materialId, 0, materialId);
  }

  m_pCalModel = new CalModel(m_pCalCoreModel);

  // Create the animation mixer
  m_pMixer = new AnimationMixer();
  m_pMixer->m_pCalModel = m_pCalModel;
  m_pMixer->m_pCalCoreModel = m_pCalCoreModel;
  m_pMixer->m_pCalMixer = m_pCalModel->getMixer();

  if (!CreateMaterials())
  {
    return false;
  }

  // attach all meshes to the model
  for (int meshId = 0; meshId < m_pCalCoreModel->getCoreMeshCount(); meshId++)
  {
    m_pCalModel->attachMesh(meshId);
  }

  // Attach all meshes to the model
  for (int meshId = 0; meshId < m_pCalCoreModel->getCoreMeshCount(); meshId++)
  {
    m_pCalModel->attachMesh(meshId);
  }

  // Set the material set of the whole model
  m_pCalModel->setMaterialSet(0);

  // Disable the spring system
  m_pCalModel->disableInternalData();

  if (!CreateMesh())
  {
    return false;
  }

  return true;
}


bool Motion::CreateMaterials()
{
  // load all textures and store the D3D texture object id in the corresponding map in the material
  for (int materialId = 0; materialId < m_pCalCoreModel->getCoreMaterialCount(); materialId++)
  {
    // get the core material
    CalCoreMaterial *pCoreMaterial;
    pCoreMaterial = m_pCalCoreModel->getCoreMaterial(materialId);

    // loop through all maps of the core material
    for (int mapId = 0; mapId < pCoreMaterial->getMapCount(); mapId++)
    {
      // get the filename of the texture
      std::string strFilename;
      strFilename = pCoreMaterial->getMapFilename(mapId);

      // load the texture from the file
      FileHandle handle = Application.GetTextureDatabase()->FindFileHandle(strFilename);
      Texture *pTexture = TextureLoader::LoadTexture(handle);
      if (!pTexture)
      {
        LOG_ERROR << "Failed to load the texture: " << strFilename << ENDLOG;
        return false;
      }
      SafeRef(pTexture);

      // store the texture pointer in the user data of the map
      pCoreMaterial->setMapUserData(mapId, (Cal::UserData)pTexture);
    }
  }

  // set the material set of the whole model
  m_pCalModel->setMaterialSet(0);
  return true;
}


bool Motion::CreateMesh()
{
  ASSERT(sizeof(CalIndex) == sizeof(ushort), "CalIndex is not 16bit");

  // Get the vertex type
  const VertexType *pVertexType = VertexTypeCache::GetVertexType(CAL3D_VERTEX_TYPE);
  if (!pVertexType)
  {
    LOG_ERROR << "Failed to find the Cal3d vertex type" << ENDLOG;
    return false;
  }

  // Get the material
  m_pMaterial = MaterialCache::GetMaterial(CAL3D_MATERIAL);
  if (!m_pMaterial)
  {
    LOG_ERROR << "Failed to find the Cal3d material" << ENDLOG;
    return false;
  }

  // Create the core model
  m_pCalHardwareModel = new CalHardwareModel(m_pCalCoreModel);

  // Create the indexed mesh
  m_pIndexedMesh = new IndexedMesh("", pVertexType);
  m_pIndexedMesh->SetPreRenderCallback(MakeCallback(&Motion::MeshSubsetPreRenderCallback, this));
  
  // Set the indexed mesh vertex and index count (todo: optimize this)
  m_pIndexedMesh->SetNumVerts(CAL3D_MAXVERTS);
  m_pIndexedMesh->SetNumFaces(CAL3D_MAXFACES);
  m_pIndexedMesh->SetDirty();

  // Get the vertex item offsets
  int positionOffset    = pVertexType->GetItemOffset(VI_Position);
  int normalOffset      = pVertexType->GetItemOffset(VI_Normal);
  int textureOffset     = pVertexType->GetItemOffset(VI_Texture);
  int boneWeightOffset  = pVertexType->GetItemOffset(VI_BoneWeight);
  int boneIndexOffset   = pVertexType->GetItemOffset(VI_BoneIndex);

  // Get the size of the vertex type
  int vertexSize = pVertexType->GetSize();

  // Check all the required streams exist
  if (positionOffset < 0 || normalOffset < 0 || textureOffset < 0 || boneWeightOffset < 0 || boneIndexOffset < 0)
  {
    LOG_ERROR << "Vertex type is not valid for a hardware animated mesh" << ENDLOG;
    return false;
  }

  // Get the vertex data and the face data
  void *pVertexData = m_pIndexedMesh->GetVertexData();
  IndexedMesh::Face *pFaceData = m_pIndexedMesh->GetFaceData();

  // Set the vertex streams into the hardware model
  m_pCalHardwareModel->setVertexBuffer(          ((char *) pVertexData) + positionOffset,    vertexSize);
  m_pCalHardwareModel->setWeightBuffer(          ((char *) pVertexData) + boneWeightOffset,  vertexSize);
  m_pCalHardwareModel->setMatrixIndexBuffer(     ((char *) pVertexData) + boneIndexOffset,   vertexSize);  
  m_pCalHardwareModel->setNormalBuffer(          ((char *) pVertexData) + normalOffset,      vertexSize);
  m_pCalHardwareModel->setTextureCoordBuffer(0,  ((char *) pVertexData) + textureOffset,     vertexSize);

  // Set the number of texture coordinates
  m_pCalHardwareModel->setTextureCoordNum(1);

  // Set the index buffer
  m_pCalHardwareModel->setIndexBuffer((CalIndex *) pFaceData);

  // Load the meshes into the hardware model
  if (!m_pCalHardwareModel->load(0, 0, CAL3D_MAXBONES_PER_MESH))
  {
    LOG_ERROR << "Failed to load the Motion hardware model" << ENDLOG;
    return false;
  }

  // Create the mesh subsets
  for (int hardwareMeshId = 0; hardwareMeshId < m_pCalHardwareModel->getHardwareMeshCount() ;hardwareMeshId++)
  {
    m_pCalHardwareModel->selectHardwareMesh(hardwareMeshId);

    D3DMATERIAL mat;
    unsigned char meshColor[4];

    m_pCalHardwareModel->getAmbientColor(&meshColor[0]);
    mat.Ambient.r = meshColor[0] / 255.0f;
    mat.Ambient.g = meshColor[1] / 255.0f;
    mat.Ambient.b = meshColor[2] / 255.0f;
    mat.Ambient.a = meshColor[3] / 255.0f;

    m_pCalHardwareModel->getDiffuseColor(&meshColor[0]);
    mat.Diffuse.r = meshColor[0] / 255.0f;
    mat.Diffuse.g = meshColor[1] / 255.0f;
    mat.Diffuse.b = meshColor[2] / 255.0f;
    mat.Diffuse.a = meshColor[3] / 255.0f;

    m_pCalHardwareModel->getSpecularColor(&meshColor[0]);
    mat.Specular.r = meshColor[0] / 255.0f;
    mat.Specular.g = meshColor[1] / 255.0f;
    mat.Specular.b = meshColor[2] / 255.0f;
    mat.Specular.a = meshColor[3] / 255.0f;

    mat.Power = 0.0f;
    mat.Emissive.r = 0.0f;
    mat.Emissive.g = 0.0f;
    mat.Emissive.b = 0.0f;
    mat.Emissive.a = 0.0f;

    // Get the diffuse texture
    Texture *pTexture = (Texture *) m_pCalHardwareModel->getMapUserData(0);

    // Create the mesh subset
    MeshSubset *pSubset = m_pIndexedMesh->AddSubset();
    pSubset->SetColorMaterial(mat);
    pSubset->SetMaterial(m_pMaterial);
    pSubset->SetFaceStart(m_pCalHardwareModel->getStartIndex() / 3);
    pSubset->SetFaceCount(m_pCalHardwareModel->getFaceCount());
    pSubset->SetVertexStart(m_pCalHardwareModel->getBaseVertexIndex());
    pSubset->SetVertexCount(m_pCalHardwareModel->getVertexCount());

    // Set the subset diffuse texture
    if (pTexture)
    {
      pSubset->GetTextureArray().SetTex0(pTexture);
    }
  }

  return true;
}


void Motion::Update(float deltaTime)
{
  // Update the animation
  m_pCalModel->update(deltaTime);
}


void Motion::MeshSubsetPreRenderCallback(MeshSubset *pSubset)
{
  uint id = pSubset->GetIndex();
  m_pCalHardwareModel->selectHardwareMesh(id);

  // Update the bone matrices
  for (int boneId = 0; boneId < m_pCalHardwareModel->getBoneCount(); boneId++)
  {
    D3DXMATRIX transformation;
    D3DXMatrixRotationQuaternion(&transformation, (CONST D3DXQUATERNION*) &m_pCalHardwareModel->getRotationBoneSpace(boneId, m_pCalModel->getSkeleton()));

    CalVector translationBoneSpace = m_pCalHardwareModel->getTranslationBoneSpace(boneId, m_pCalModel->getSkeleton());

    transformation._14 = translationBoneSpace.x;
    transformation._24 = translationBoneSpace.y;
    transformation._34 = translationBoneSpace.z;

    m_pMaterial->SetBoneMatrix(boneId, (Matrix) transformation);
  }
}


// -- EOF



