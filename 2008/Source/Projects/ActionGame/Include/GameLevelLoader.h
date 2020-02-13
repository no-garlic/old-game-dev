
#ifndef __GAME_LEVEL_LOADER_H_
#define __GAME_LEVEL_LOADER_H_


#include "libEngine.h"
#include "GameLevel.h"


class GameLevelLoader : private Unique
{
public:
  // Constructor and destructor
  GameLevelLoader(GameLevel *pLevel, GameLevel::LoadItem *pItem);
  virtual ~GameLevelLoader();

  // Initialise the loader
  bool Init(const ConfigSection &data);

  // Load and setup the asset
  bool Load();

private:
  // Resolve the type based on a string
  bool ResolveType(const String &typeName);

  // Iniitlaise and load a static mesh
  bool InitStaticMesh(const ConfigSection &data);
  bool LoadStaticMesh();

  // Iniitlaise and load a static mesh
  bool InitLight(const ConfigSection &data);
  bool LoadLight();

  // Enum of item types
  enum GameLevelItemType
  {
    LIT_STATIC_MESH,
    LIT_LIGHT,
    LIT_UNKNOWN
  };

  struct LoadData {};

  // Load data for the static mesh
  struct StaticMeshLoadData : LoadData
  {
    String    FileName;
    Vec3      Position;
    Vec3      Rotation;
    Vec3      Scale;
  };

  // Load data for the light
  struct LightLoadData : LoadData
  {
    String    Type;
    Vec3      Position;
    Vec3      Direction;
    Color     Ambient;
    Color     Diffuse;
    Color     Specular;
    float     Range;
    float     Falloff;
    float     InnerCone;
    float     OuterCone;
    float     Atten0;
    float     Atten1;
    float     Atten2;
  };

private:
  GameLevel            *m_pLevel;     // The game level
  GameLevel::LoadItem  *m_pLoadItem;  // The load item
  LoadData             *m_pLoadData;  // The load data
  String                m_Name;       // The asset name
  GameLevelItemType     m_Type;       // The asset type

};


#endif // __GAME_LEVEL_LOADER_H_

// -- EOF

