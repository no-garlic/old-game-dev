
#include "ImageList.h"


ImageList::ImageList()
: wxImageList(16, 16)
{
}


ImageList::~ImageList()
{
}


int ImageList::GetIndex(const String &name)
{
  Map<String, int>::const_iterator iter = m_ImageMap.find(name);
  if (iter == m_ImageMap.end())
    return -1;

  return iter->second;
}


bool ImageList::Load(FileHandle handle)
{
  ConfigFile cfg;
  if (!cfg.Load(handle.GetAbsoluteFilename()))
  {
    LOG_ERROR << "Failed to load the image list config: " << handle << ENDLOG;
    return false;
  }

  ConfigSectionMap::const_iterator iter(cfg.GetSections().begin()), end(cfg.GetSections().end());
  for (; iter != end; ++iter)
  {
    const ConfigSection &section = iter->second;
    if (!LoadSection(section))
    {
      LOG_ERROR << "Failed to load an image in the section: " << iter->first << " in the file: " << handle << ENDLOG;
      return false;
    }
  }

  return true;
}


bool ImageList::LoadSection(const ConfigSection &section)
{
  ConfigValueMap::const_iterator iter(section.Items.begin()), end(section.Items.end());
  for (; iter != end; ++iter)
  {
    if (!LoadImage(iter->second))
    {
      LOG_ERROR << "Failed to load the image: " << iter->first << ENDLOG;
      return false;
    }
  }

  return true;
}


bool ImageList::LoadImage(const ConfigValue &value)
{
  FileHandle handle = Application.GetTextureDatabase()->FindFileHandle(value.Value);
  if (!handle.Exists())
  {
    LOG_ERROR << "The image file does not exist: " << handle << ENDLOG;
    return false;
  }

  wxImage image;
  if (!image.LoadFile(handle.GetAbsoluteFilename().c_str()))
  {
    LOG_ERROR << "The image file failed to load: " << handle << ENDLOG;
    return false;
  }

  wxBitmap bitmap(image);

  // Convert alpha, etc...

  int id = Add(bitmap);
  m_ImageMap[value.Key] = id;

  return true;
}


// -- EOF

