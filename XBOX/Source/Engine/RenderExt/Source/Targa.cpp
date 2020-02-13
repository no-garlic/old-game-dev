// ----------------------------------------------------------------------------
// File: Targa.cpp
// Desc: Native tga class to save some raw inage data to a targa file
// Auth: Michael Petrou
// (C) Copyright: 2006
// ----------------------------------------------------------------------------
#include "Targa.h"


// ----------------------------------------------------------------------------
// Targa namespace
// ----------------------------------------------------------------------------
namespace Targa
{

  // --------------------------------------------------------------------------
  // Targa header info
  // --------------------------------------------------------------------------
  #pragma pack (push)
  #pragma pack (1)	// dont pad the following struct
  typedef struct _TGAHeaderInfo
  {
    BYTE idlen;    // length of optional identification sequence
    BYTE cmtype;   // indicates whether a palette is present
    BYTE imtype;   // image data type (e.g., uncompressed RGB)
    WORD cmorg;    // first palette index, if present
    WORD cmcnt;    // number of palette entries, if present
    BYTE cmsize;   // number of bits per palette entry
    WORD imxorg;   // horiz pixel coordinate of lower left of image
    WORD imyorg;   // vert pixel coordinate of lower left of image
    WORD imwidth;  // image width in pixels
    WORD imheight; // image height in pixels
    BYTE imdepth;  // image color depth (bits per pixel)
    BYTE imdesc;   // image attribute flags
  } TGAHeaderInfo;
  #pragma pack (pop)


  // --------------------------------------------------------------------------
  // Save the data to a targa file
  // --------------------------------------------------------------------------
  bool SaveTGA(FileHandle handle, uchar *pimage_data, uint width, uint height)
  {
    const char *filename = handle.GetAbsoluteFilename().c_str();

    FILE *foutput = fopen(filename, "wb");
    if (!foutput)
    {
      LOG_ERROR << "Failed to open targa file: " << filename << ENDLOG;
      return false;
    } // if

    TGAHeaderInfo header;
    header.idlen    = 0;
    header.cmtype   = 0;
    header.imtype   = 2;
    header.cmorg    = 0;
    header.cmcnt    = 0;
    header.cmsize   = 0;
    header.imxorg   = 0;
    header.imyorg   = 0;
    header.imwidth  = width;
    header.imheight = height;
    header.imdepth  = 32;
    header.imdesc   = 8;

    // Write to output file TARGA header
    if (fwrite(&header, sizeof (header), 1, foutput) != 1)
    {
      LOG_ERROR << "Failed to write the targa header: " << filename << ENDLOG;
      fclose(foutput);
      return false;
    } // if

    // Write the image data
    uint size = width * height * sizeof(uchar) * 4;
    if (fwrite(pimage_data, size, 1, foutput) != 1)
    {
      LOG_ERROR << "Failed to write the targa image data: " << filename << ENDLOG;
      fclose(foutput);
      return false;
    } // if

    fclose(foutput);
    return true;
  }

}; // namespace Targa


// -- EOF



