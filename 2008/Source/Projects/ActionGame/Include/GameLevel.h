
#ifndef __GAME_LEVEL_H_
#define __GAME_LEVEL_H_


#include "libEngine.h"
#include "GameLevelRender.h"


class GameLevel : private Unique
{
public:
  // Constructor and destructor
  GameLevel();
  virtual ~GameLevel();

  // Begin loading the level in the background
  bool BeginLoad(FileHandle handle);

  // Request for the load to be cancelled
  void CancelLoad(bool wait);

  // Unload the level
  bool Unload();

  // The possible load states
  enum LoadState { LS_NONE, LS_LOADING, LS_LOADED, LS_FAILED, LS_CANCEL, LS_CANCELLED };

  // Get the load state
  LoadState GetLoadState() const;

  // Get the load progress (from 0 to 100)
  uint GetLoadProgress() const;

  // Get the render level
  GameLevelRender &GetRenderLevel() { return m_RenderLevel; }

private:
  // Set the load state
  void SetLoadState(LoadState state);

  // Threaded function for loading the level in the background
  static OS::ThreadReturnType BackgroundLoadThread(void *pArg);
  void BackgroundLoad();

  // Generate a queue of all of the items that need to be loaded
  bool GenerateLoadQueue();
  bool GenerateLoadQueueFromConfig(const ConfigSection &cfg);

  // A structure that holds the definition of an item to be loaded
  friend class GameLevelLoader;
  struct LoadItem
  {
    LoadItem(GameLevel *pLevel);
    ~LoadItem();

    bool Init(const ConfigSection &data);
    bool Load();

    GameLevelLoader *pLoader;  
  };

  // A list of load items
  typedef Queue<GameLevel::LoadItem *> LoadQueue;

private:
  LoadState           m_LoadState;        // The current load state
  ConfigFile          m_Config;           // The config file holding hte level definition
  OS::Thread         *m_pLoadThread;      // The loading thread
  LoadQueue           m_LoadQueue;        // The queueof items to load
  FileHandle          m_Handle;           // The file handle
  mutable OS::Mutex   m_StateMutex;       // Mutex for the load state variable
  mutable OS::Mutex   m_LoadCountMutex;   // Mutex for the load count variable
  mutable OS::Event   m_CancelEvent;      // Event that is set once the thread executes the cancel operation
  uint                m_LoadCount;        // The total count of load items
  uint                m_LoadCurrent;      // The index of the item being loaded
  GameLevelRender     m_RenderLevel;      // Teh render level

};


#endif // __GAME_LEVEL_H_

// -- EOF

