
#ifndef __EDITOR_CONTENT_H_
#define __EDITOR_CONTENT_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libEngine.h"
#include "libEditor.h"


// ----------------------------------------------------------------------------
// Manages a tree view of content availble to be used in levels.
// ----------------------------------------------------------------------------
class EditorContent
{
public:
  EditorContent();
  ~EditorContent();

  bool Load(FileHandle handle);

  void EnumerateMeshGroups(StringArray &groupNames);
  void EnumerateMeshes(const String &groupName, StringMap &meshes);

private:
  bool LoadSection(const ConfigSection &section);
  bool LoadMeshSection(const String &name, const ConfigValueMap &values);


  Map<String, StringMap>  m_MeshGroups;

};


#endif // __EDITOR_CONTENT_H_

// -- EOF

