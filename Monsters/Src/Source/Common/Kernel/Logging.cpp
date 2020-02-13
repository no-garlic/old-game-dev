// ----------------------------------------------------------------------------
// File: Logging.cpp
// Desc: Flexible logging class that provides logging to file,console, or the 
//       CRT window in VS .NET
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Logging include files
// ----------------------------------------------------------------------------
#include "Kernel/Types.h"
#include "Kernel/Logging.h"


// ----------------------------------------------------------------------------
// Name: Log (namespace)
// Desc: The logger namespace
// ----------------------------------------------------------------------------
namespace Log
{
#ifdef _DEBUG
  // Warning: in debug we never delete the logger, because
  // we use it to log memory leaks as the very last thing
  // before program termination.
  Logger *g_plogger = new Logger;
#else
  // In release we do not log the memory leaks, so we can
  // make the logger a static.
  static Logger g_logger;         // The logger
  Logger *g_plogger = &g_logger;  // The global endlog object
#endif
}; // namespace Log


// ----------------------------------------------------------------------------
// Name: ConvertDxErrorToString
// Desc: Convert the HRESULT to the directx error string
// Parm: HRESULT hr - the result
// Retn: char *     - the error string
// ----------------------------------------------------------------------------
char *ConvertDxErrorToString(HRESULT hr)
{
  switch (hr)
  {
  case D3D_OK:                              return "No error.";
  case D3DERR_CONFLICTINGRENDERSTATE:       return "Error: D3DERR_CONFLICTINGRENDERSTATE: The currently set render states cannot be used together.";
  case D3DERR_CONFLICTINGTEXTUREFILTER:     return "Error: D3DERR_CONFLICTINGTEXTUREFILTER: The current texture filters cannot be used together.";
  case D3DERR_CONFLICTINGTEXTUREPALETTE:    return "Error: D3DERR_CONFLICTINGTEXTUREPALETTE: The current textures cannot be used simultaneously. This generally occurs when a multitexture device requires that all palletized textures simultaneously enabled also share the same palette.";
  case D3DERR_DEVICELOST:                   return "Error: D3DERR_DEVICELOST: The device is lost and cannot be restored at the current time, so rendering is not possible.";
  case D3DERR_DEVICENOTRESET:               return "Error: D3DERR_DEVICENOTRESET: The device cannot be reset.";
  case D3DERR_DRIVERINTERNALERROR:          return "Error: D3DERR_DRIVERINTERNALERROR: Internal driver error.";
  case D3DERR_INVALIDCALL:                  return "Error: D3DERR_INVALIDCALL: The method call is invalid. For example, a method's parameter may have an invalid value.";
  case D3DERR_INVALIDDEVICE:                return "Error: D3DERR_INVALIDDEVICE: The requested device type is not valid.";
  case D3DERR_MOREDATA:                     return "Error: D3DERR_MOREDATA: There is more data available than the specified buffer size can hold.";
  case D3DERR_NOTAVAILABLE:                 return "Error: D3DERR_NOTAVAILABLE: This device does not support the queried technique.";
  case D3DERR_NOTFOUND:                     return "Error: D3DERR_NOTFOUND: The requested item was not found.";
  case D3DERR_OUTOFVIDEOMEMORY:             return "Error: D3DERR_OUTOFVIDEOMEMORY: Direct3D does not have enough display memory to perform the operation.";
  case D3DERR_TOOMANYOPERATIONS:            return "Error: D3DERR_TOOMANYOPERATIONS: The application is requesting more texture-filtering operations than the device supports.";
  case D3DERR_UNSUPPORTEDALPHAARG:          return "Error: D3DERR_UNSUPPORTEDALPHAARG: The device does not support one of the specified texture-blending arguments for the alpha channel.";
  case D3DERR_UNSUPPORTEDALPHAOPERATION:    return "Error: D3DERR_UNSUPPORTEDALPHAOPERATION: The device does not support one of the specified texture-blending operations for the alpha channel.";
  case D3DERR_UNSUPPORTEDCOLORARG:          return "Error: D3DERR_UNSUPPORTEDCOLORARG: The device does not support one of the specified texture-blending arguments for color values.";
  case D3DERR_UNSUPPORTEDCOLOROPERATION:    return "Error: D3DERR_UNSUPPORTEDCOLOROPERATION: The device does not support one of the specified texture-blending operations for color values.";
  case D3DERR_UNSUPPORTEDFACTORVALUE:       return "Error: D3DERR_UNSUPPORTEDFACTORVALUE: The specified texture factor value is not supported by the device.";
  case D3DERR_UNSUPPORTEDTEXTUREFILTER:     return "Error: D3DERR_UNSUPPORTEDTEXTUREFILTER: The specified texture filter is not supported by the device.";
  case D3DERR_WRONGTEXTUREFORMAT:           return "Error: D3DERR_WRONGTEXTUREFORMAT: The pixel format of the texture surface is not valid.";
  case E_FAIL:                              return "Error: E_FAIL: An undetermined error occurred inside the Direct3D subsystem.";
  case E_INVALIDARG:                        return "Error: E_INVALIDARG: An invalid parameter was passed to the returning function";
  case E_OUTOFMEMORY:                       return "Error: E_OUTOFMEMORY: Direct3D could not allocate sufficient memory to complete the call.";
  case D3DXERR_INVALIDDATA:                 return "Error: D3DXERR_INVALIDDATA: The data is invalid.";
  default:                                  return "Error: Unknown error";
  } // switch
} // ConvertDxErrorToString


// ----------------------------------------------------------------------------
// Name: LoggerTime
// Desc: Gets the current time as a string
// Retn: String - the time
// ----------------------------------------------------------------------------
String LoggerTime()
{
  char ptime_str[128];
  time_t m_time_stamp = time(0);
  strftime(ptime_str, sizeof(ptime_str), "%d/%m/%y %H:%M:%S", localtime(&m_time_stamp));
  return ptime_str;
} // LoggerTime


// ----------------------------------------------------------------------------
// Name: LoggerStamp
// Desc: Get the file and line stamp as a string, and remove the path from the 
//       file.
// Parm: const char *file - the file (use __FILE__)
// Parm: const int line   - the line (use __LINE__)
// Retn: String      - the file and line as a string
// ----------------------------------------------------------------------------
String LoggerStamp(const char *file, const int line)
{
  String m_file = file;
  String out;
  String file_str;

  // Remove the path from the filename
  file_str = m_file.substr(m_file.insert(
    String::size_type(0), 1, '\\').find_last_of('\\'));
  file_str = file_str.substr(file_str.insert(
    String::size_type(0), 1, '/').find_last_of('/'));

  // Add a comma
  out.append(", ");
  out.append(file_str.substr(file_str.find_first_not_of("\\/")));

  // Add the line
  out.append(" [");
  char str_line[32];
  sprintf(str_line, "%d", line);
  out.append(str_line);
  out.append("] - ");

  // Return the string
  return out;
} // LoggerStamp


// ----------------------------------------------------------------------------
// Name: LoggerException
// Desc: Create a string containing a formatted exception log
// Parm: const GeneralException &e - the exception to log
// Parm: const char *file          - the filename
// Parm: const int line            - the line
// Retn: String               - the string
// ----------------------------------------------------------------------------
String LoggerException(const GeneralException &e, const char *file, const int line)
{
  StringStream ss;

  // Add the exception message
  ss << "** ERROR **   " << LoggerTime() << LoggerStamp(file, line);
  ss << e.what();

  // Check if we have a trace. Don't add it if we don't have one
  String str = e.GetTrace();
  if (!str.empty())
    ss << std::endl << str;

  ss << std::endl;

  return ss.str();
} // LoggerException
  

// ----------------------------------------------------------------------------
// Name: Logger::Out
// Desc: Log the message
// Parm: const char *message - the message
// ----------------------------------------------------------------------------
void Logger::Out(const char *message)
{
#ifdef _DEBUG
  _RPT1(0, "%s\n", message);
#endif // _DEBUG

  for (uint i = 0; i < callbacks.size(); i++)
    (*callbacks[i])(message);
} // Out


// -- EOF
