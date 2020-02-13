
// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "MeshConvertModule.h"
#include "libEngine.h"


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
MeshConvertModule::MeshConvertModule(const String &name)
: ApplicationModule_NoGfx(name)
{
} // MeshConvertModule


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
MeshConvertModule::~MeshConvertModule()
{
} // ~MeshConvertModule


// ----------------------------------------------------------------------------
// Run the module
// ----------------------------------------------------------------------------
int MeshConvertModule::Run(const String &commandLine)
{
  const StringArray &args = AppArgs.GetDefaultArgs();
  if (args.empty())
    return -1;

  String inputName;
  String extension;
  String inputFilename = args[0];
  SplitFilename(inputFilename, inputName, extension);
  String outputFilename = inputName + ".msh";

  // Get the file handles
  FileHandle inputFile  = Application.GetImportDatabase()->FindFileHandle(inputFilename);
  FileHandle outputFile = Application.GetModelDatabase()->MakeFileHandle(outputFilename);

  // See if the file is up-to-date
  if (FileIsUpToDate(inputFile, outputFile))
  {
    LOG_INFO << "File us up-to-date: " << outputFile.GetAbsoluteFilename() << ENDLOG;
    RequestExit(0);
    return 0;
  }

  return ConvertNoFrames();
} // Run


int MeshConvertModule::ConvertNoFrames()
{
  IndexedMesh *pMesh = NULL;
  StackDelete<IndexedMesh> sd(pMesh);

  const StringArray &args = AppArgs.GetDefaultArgs();
  if (args.empty())
    return -1;

  String inputName;
  String extension;
  String inputFilename = args[0];
  SplitFilename(inputFilename, inputName, extension);

  // Get the file handles
  FileHandle inputFile  = FileSystem("Import")->FindFileHandle(inputFilename);

  pMesh = new IndexedMesh(inputName);
  if (!pMesh->ImportFromX(inputFile.GetAbsoluteFilename()))
  {
    LOG_ERROR << "Failed to import the mesh: " << inputFile.GetFilename() << ENDLOG;
    Application.RequestExit(1);
    return -1;
  }

  // Create the file handle
  String outputName = inputName + ".msh";
  FileHandle outputFile = Application.GetModelDatabase()->MakeFileHandle(outputName);

  if (!pMesh->Save(outputFile))
  {
    LOG_ERROR << "Failed to save the mesh: " << outputFile.GetFilename() << ENDLOG;
    Application.RequestExit(1);
    return -1;
  }

  // Save out all textures
  const Map<String, Texture *> &textureArray = TextureLoader::GetAllTextures();
  Map<String, Texture *>::const_iterator texIter(textureArray.begin()), texEnd(textureArray.end());
  for (; texIter != texEnd; ++texIter)
  {
    // Get the texture
    Texture *pTexture = texIter->second;

    // Save the texture
    FileHandle handle = Application.GetTextureDatabase()->MakeFileHandle(pTexture->GetFileHandle().GetFilename());
    if (!pTexture->Save(handle))
    {
      LOG_ERROR << "Failed to save the texture: " << pTexture->GetFileHandle().GetFilename() << ENDLOG;
      Application.RequestExit(1);
      return -1;
    }
  } // for

  LOG_INFO << "Successfully converted the mesh: " << inputFile.GetFilename() << " to: " << outputFile.GetFilename() << ENDLOG;
  Application.RequestExit(0);

  return 0;
} // ConvertNoFrames



// -- EOF

