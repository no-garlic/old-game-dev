// ----------------------------------------------------------------------------
// File: MeshConvertModule.cpp
// Desc: The main module to run the game
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "MeshConvert/MeshConvertModule.h"
#include "Render/XFileLoader.h"


// ----------------------------------------------------------------------------
// Register this module
// ----------------------------------------------------------------------------
REGISTER_MODULE(MeshConvertModule);


// ----------------------------------------------------------------------------
// Name: MeshConvertModule::MeshConvertModule
// Desc: Constructor
// ----------------------------------------------------------------------------
MeshConvertModule::MeshConvertModule()
{
  REF_COUNT_CTOR(MeshConvertModule);

  // Load the config file
  ConfigFile cfg;
  if (cfg.Load("..\\Data\\Config\\MeshConvert.cfg"))
  {
    // Get the section
    ConfigSection &section = cfg("FilePath");

    // Set the base path
    FileSystem.SetBasePath(section("BasePath"));

    // Set the file database to save the model to
    FileSystem.AddDatabase("SrcModel",    section("SrcModel"));
    FileSystem.AddDatabase("Model",       section("DstModel"));
    FileSystem.AddDatabase("Texture",     section("SrcTexture"));
    FileSystem.AddDatabase("DstTexture",  section("DstTexture"));
    FileSystem.AddDatabase("Material",    section("Material"));
  } // if
} // MeshConvertModule


// ----------------------------------------------------------------------------
// Name: MeshConvertModule::~MeshConvertModule
// Desc: Destructor
// ----------------------------------------------------------------------------
MeshConvertModule::~MeshConvertModule() 
{
  REF_COUNT_DTOR(MeshConvertModule);
} // ~MeshConvertModule


// ----------------------------------------------------------------------------
// Name: MeshConvertModule::Run
// Desc: Run the module
// Retn: int - the application return code
// ----------------------------------------------------------------------------
int MeshConvertModule::Run()
{
  // Get the default args passed to the application
  const StringArray &argsArray = AppArgs.GetDefaultArgs();
  if (argsArray.empty())
    return -1;

  // Get the mesh filename to convert
  String meshFilename = argsArray[0];

  // Get the mesh filename to save to
  String saveFilename, extension, path, filename;
  SplitPath(meshFilename, path, filename);
  SplitFilename(filename, saveFilename, extension);

  // Get the source mesh filename
  FileDatabase *pModelDB = FileSystem("SrcModel");
  if (!pModelDB)
    return -1;
  FileHandle saveHandle = pModelDB->MakeFileHandle(meshFilename);

  // Load the mesh
  XFileLoader loader;
  if (!loader.Load(saveHandle.GetAbsoluteFilename()))
    return -1;

  // Get the frames
  Array<XFileLoader::Frame> frames = loader.GetFrames();
  Array<XFileLoader::Frame>::iterator iter(frames.begin()), end(frames.end());

  // Save out all meshes
  int i = 0;
  for (; iter != end; ++iter)
  {
    XFileLoader::Frame &frame = (*iter);

    String out = saveFilename;
    AppendInt(out, i++);
    out += ".msh";

    // Create the file handle
    FileDatabase *pModelDb = FileSystem("Model");
    if (!pModelDb)
      return -1;

    FileHandle handle = pModelDb->MakeFileHandle(out);

    if (!frame.pMesh->Save(handle))
      return -1;
  } // for

  // Get the output database for textures
  FileDatabase *pTextureDB = FileSystem("DstTexture");
  if (!pTextureDB)
    return -1;

  // Save out all textures
  const Map<String, Texture *> &textureArray = TextureLoader::GetAllTextures();
  Map<String, Texture *>::const_iterator texIter(textureArray.begin()), texEnd(textureArray.end());
  for (; texIter != texEnd; ++texIter)
  {
    // Get the texture
    Texture *pTexture = texIter->second;

    // Save the texture
    FileHandle handle = pTextureDB->MakeFileHandle(pTexture->GetFileHandle().GetFilename());
    pTexture->Save(handle);
  } // for

  // Done
  return 0;
} // Init


// -- EOF


