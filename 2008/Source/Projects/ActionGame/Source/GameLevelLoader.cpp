
#include "GameLevelLoader.h"
#include "StaticMesh.h"
#include "GameLight.h"


GameLevelLoader::GameLevelLoader(GameLevel *pLevel, GameLevel::LoadItem *pItem)
{
  REF_COUNT_CTOR(GameLevelLoader);

  m_pLevel      = pLevel;
  m_pLoadItem   = pItem;
  m_pLoadData   = NULL;
  m_Type        = LIT_UNKNOWN;
}


GameLevelLoader::~GameLevelLoader()
{
  REF_COUNT_DTOR(GameLevelLoader);

  delete m_pLoadData;
}


bool GameLevelLoader::Init(const ConfigSection &data)
{
  // Store the name
  m_Name = data.Name;

  // Get the type from the string
  if (!ResolveType(data.Type))
  {
    LOG_ERROR << "Failed to resolve the item type: " << data.Type << ENDLOG;
    return false;
  }

  // Init based on the type
  switch (m_Type)
  {
  case GameLevelLoader::LIT_STATIC_MESH:
    return InitStaticMesh(data);

  case GameLevelLoader::LIT_LIGHT:
    return InitLight(data);

  // ...

  };

  return false;
}


bool GameLevelLoader::Load()
{
  // Load the correct type
  switch (m_Type)
  {
  case GameLevelLoader::LIT_STATIC_MESH:
    return LoadStaticMesh();

  case GameLevelLoader::LIT_LIGHT:
    return LoadLight();

  // ...

  };

  return false;
}


bool GameLevelLoader::ResolveType(const String &typeName)
{
  m_Type = GameLevelLoader::LIT_UNKNOWN;

  if (StrICmp(typeName, "Mesh"))
  {
    m_Type = GameLevelLoader::LIT_STATIC_MESH;
    return true;
  }
  else if (StrICmp(typeName, "Light"))
  {
    m_Type = GameLevelLoader::LIT_LIGHT;
    return true;
  }

  // ...

  return false;
}


// ----------------------------------------------------------------------------
// STATIC MESH
// ----------------------------------------------------------------------------

bool GameLevelLoader::InitStaticMesh(const ConfigSection &data)
{
  GameLevelLoader::StaticMeshLoadData *pLoadData = new GameLevelLoader::StaticMeshLoadData;

  pLoadData->FileName = data("File");
  if (pLoadData->FileName.empty())
  {
    LOG_ERROR << "Failed to read the filename for the static mesh: " << data.Name << ENDLOG;
    delete pLoadData;
    return false;
  }

  if (!pLoadData->Position.FromString(data("Pos")))
  {
    LOG_ERROR << "Failed to read the position for the static mesh: " << data.Name << ENDLOG;
    delete pLoadData;
    return false;
  }
  
  if (!pLoadData->Rotation.FromString(data("Rot")))
  {
    LOG_ERROR << "Failed to read the rotation for the static mesh: " << data.Name << ENDLOG;
    delete pLoadData;
    return false;
  }
  
  if (!pLoadData->Scale.FromString(data("Scl")))
  {
    LOG_ERROR << "Failed to read the scale for the static mesh: " << data.Name << ENDLOG;
    delete pLoadData;
    return false;
  }

  m_pLoadData = pLoadData;
  return true;
}


bool GameLevelLoader::LoadStaticMesh()
{
  if (!m_pLoadData)
    return false;

  // Cast the load data
  GameLevelLoader::StaticMeshLoadData *pLoadData = (GameLevelLoader::StaticMeshLoadData *) m_pLoadData;
  
  // Load the indexed mesh
  FileHandle handle = Application.GetModelDatabase()->FindFileHandle(pLoadData->FileName);
  IndexedMesh *pMesh = (IndexedMesh *) MeshLoader::LoadMesh(handle);
  if (!pMesh)
  {
    LOG_ERROR << "Failed to load the mesh: " << handle << ENDLOG;
    return false;
  }

  // Create the static mesh
  StaticMesh *pStaticMesh = new StaticMesh();
  pStaticMesh->SetMesh(pMesh);

  // Set the mesh matrix
  Matrix matrix = Matrix::MakeNewPosRotScale(pLoadData->Position, pLoadData->Rotation, pLoadData->Scale);
  pStaticMesh->SetLocalTransform(matrix);

  // Add the static mesh to the level
  m_pLevel->GetRenderLevel().AddStaticMesh(pStaticMesh);
  return true;
}


// ----------------------------------------------------------------------------
// LIGHT
// ----------------------------------------------------------------------------


bool GameLevelLoader::InitLight(const ConfigSection &data)
{
  GameLevelLoader::LightLoadData *pLoadData = new GameLevelLoader::LightLoadData;

  pLoadData->Type       = data("Type");
  pLoadData->Range      = data("Range");
  pLoadData->Falloff    = data("Falloff");
  pLoadData->InnerCone  = data("InnerCone");
  pLoadData->OuterCone  = data("OuterCone");
  pLoadData->Atten0     = data("Atten0");
  pLoadData->Atten1     = data("Atten1");
  pLoadData->Atten2     = data("Atten2");

  bool colorOk =     (pLoadData->Ambient.FromString(data("Ambient")) &&
                      pLoadData->Diffuse.FromString(data("Diffuse")) &&
                      pLoadData->Specular.FromString(data("Specular")));

  if (!colorOk)
  {
    LOG_ERROR << "Failed to read the color for the light: " << data.Name << ENDLOG;
    delete pLoadData;
    return false;
  } 

  pLoadData->Direction.Set(0.0f, -1.0f, 0.0f);
  pLoadData->Position.Set(0.0f, 0.0f, 0.0f);

  if (StrICmp(pLoadData->Type, "Directional"))
  {
    if (!pLoadData->Direction.FromString(data("Direction")))
    {
      LOG_ERROR << "Failed to read the position for the light: " << data.Name << ENDLOG;
      delete pLoadData;
      return false;
    }
  }
  else if (StrICmp(pLoadData->Type, "Point"))
  {
    if (!pLoadData->Position.FromString(data("Position")))
    {
      LOG_ERROR << "Failed to read the position for the light: " << data.Name << ENDLOG;
      delete pLoadData;
      return false;
    }
    if (!pLoadData->Direction.FromString(data("Direction")))
    {
      LOG_ERROR << "Failed to read the position for the light: " << data.Name << ENDLOG;
      delete pLoadData;
      return false;
    }
  }
  else if (StrICmp(pLoadData->Type, "Spot"))
  {
    if (!pLoadData->Position.FromString(data("Position")))
    {
      LOG_ERROR << "Failed to read the position for the light: " << data.Name << ENDLOG;
      delete pLoadData;
      return false;
    }
  }
  else
  {
    LOG_ERROR << "Unknown light type for light: " << data.Name << ENDLOG;
    delete pLoadData;
    return false;
  }

  m_pLoadData = pLoadData;
  return true;
}


bool GameLevelLoader::LoadLight()
{
  if (!m_pLoadData)
    return false;

  // Cast the load data
  GameLevelLoader::LightLoadData *pLoadData = (GameLevelLoader::LightLoadData *) m_pLoadData;

  // Create the light
  GameLight *pLight = NULL;
  if (StrICmp(pLoadData->Type, "Directional"))
  {
    pLight = new GameLight();
    pLight->SetDirectionalLight(pLoadData->Direction, pLoadData->Ambient, pLoadData->Diffuse, pLoadData->Specular);
  }
  else if (StrICmp(pLoadData->Type, "Spot"))
  {
    pLight = new GameLight();
    pLight->SetSpotLight(pLoadData->Position, pLoadData->Direction, pLoadData->Range, 
      pLoadData->Falloff, pLoadData->Atten0, pLoadData->Atten1, pLoadData->Atten2, pLoadData->InnerCone, 
      pLoadData->OuterCone, pLoadData->Ambient, pLoadData->Diffuse, pLoadData->Specular);
  }
  else if (StrICmp(pLoadData->Type, "Point"))
  {
    pLight = new GameLight();
    pLight->SetPointLight(pLoadData->Position, pLoadData->Range, pLoadData->Atten0, pLoadData->Atten1, 
      pLoadData->Atten2, pLoadData->Ambient, pLoadData->Diffuse, pLoadData->Specular);
  }
  else
  {
    LOG_ERROR << "Invalid light type: " << pLoadData->Type << ENDLOG;
    return false;
  }

  // Set the transform - has the same effect as creating the light 
  // using the T-Axis and Y-Axis of the matrix.
  Matrix matrix = MatrixIdentity;
  matrix.SetTAxis(pLoadData->Position);
  matrix.SetYAxis(pLoadData->Direction);
  pLight->SetLocalTransform(matrix);

  // Add the static mesh to the level
  m_pLevel->GetRenderLevel().AddLight(pLight);
  return true;
}


// -- EOF


