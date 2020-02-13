
#include "EditorContent.h"


EditorContent::EditorContent()
{
}


EditorContent::~EditorContent()
{
}


bool EditorContent::Load(FileHandle handle)
{
  ConfigFile cfg;
  if (!cfg.Load(handle.GetAbsoluteFilename()))
  {
    LOG_ERROR << "Failed to load the editor content file: " << handle << ENDLOG;
    return false;
  }

  const ConfigSectionMap &sections = cfg.GetSections();
  ConfigSectionMap::const_iterator iter(sections.begin()), end(sections.end());
  for (; iter != end; ++iter)
  {
    if (!LoadSection(iter->second))
    {
      LOG_ERROR << "Failed to load the section: " << iter->first << " from the editor content file: " << handle << ENDLOG;
      return false;
    }
  }

  return true;
}


bool EditorContent::LoadSection(const ConfigSection &section)
{
  if (StrICmp(section.Type, "Mesh"))
  {
    return LoadMeshSection(section.Name, section.Items);
  }

  // ...

  return false;
}


bool EditorContent::LoadMeshSection(const String &name, const ConfigValueMap &values)
{
  StringMap &meshGroup = m_MeshGroups[name];

  ConfigValueMap::const_iterator iter(values.begin()), end(values.end());
  for (; iter != end; ++iter)
  {
    meshGroup[iter->first] = iter->second;
  }

  return true;
}


void EditorContent::EnumerateMeshGroups(StringArray &groupNames)
{
  Map<String, StringMap>::const_iterator iter(m_MeshGroups.begin()), end(m_MeshGroups.end());
  for (; iter != end; ++iter)
  {
    groupNames.push_back(iter->first);
  }
}


void EditorContent::EnumerateMeshes(const String &groupName, StringMap &meshes)
{
  StringMap &meshGroup = m_MeshGroups[groupName];
  StringMap::const_iterator iter(meshGroup.begin()), end(meshGroup.end());
  for (; iter != end; ++iter)
  {
    meshes[iter->first] = iter->second;
  }
}


// -- EOF

