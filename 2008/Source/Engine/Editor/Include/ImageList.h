
#ifndef __IMAGE_LIST_H_
#define __IMAGE_LIST_H_


#include "libRenderExt.h"
#include "wxWindows/wxDisplay.h"
#include "wx/image.h"


class ImageList : public wxImageList
{
public:
  ImageList();
  virtual ~ImageList();

  bool Load(FileHandle handle);

  int GetIndex(const String &name);

private:
  bool LoadSection(const ConfigSection &section);
  bool LoadImage(const ConfigValue &value);

  Map<String, int>  m_ImageMap;

};


#endif // __IMAGE_LIST_H_

// -- EOF

