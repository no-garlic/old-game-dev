
#ifndef __PROPERTY_GRID_TYPES_H_
#define __PROPERTY_GRID_TYPES_H_


#include "wx/propgrid/propdev.h"
#include "wx/propgrid/advprops.h"
#include "wx/propgrid/manager.h"


// This decl is what you would use in a normal app
#define wxPG_EXTRAS_DECL

WX_DECLARE_OBJARRAY_WITH_DECL(double, wxArrayDouble, class wxPG_EXTRAS_DECL);

WX_PG_DECLARE_VALUE_TYPE_VOIDP_WITH_DECL(wxArrayDouble,wxPG_EXTRAS_DECL)

WX_PG_DECLARE_PROPERTY_WITH_DECL(wxArrayDoubleProperty,const wxArrayDouble&,wxArrayDouble(),wxPG_EXTRAS_DECL)

WX_PG_DECLARE_VALUE_TYPE_WITH_DECL(wxFontData,wxPG_EXTRAS_DECL)
WX_PG_DECLARE_VALUE_TYPE_VOIDP_WITH_DECL(wxPoint,wxPG_EXTRAS_DECL)
WX_PG_DECLARE_VALUE_TYPE_VOIDP_WITH_DECL(wxSize,wxPG_EXTRAS_DECL)
WX_PG_DECLARE_VALUE_TYPE_VOIDP_WITH_DECL(wxLongLong,wxPG_EXTRAS_DECL)



// wxPaintedEnumPropertyClass - wxEnumProperty with totally custom painted list items.
class wxPaintedEnumPropertyClass : public wxEnumPropertyClass
{
public:
  wxPaintedEnumPropertyClass(const wxString& label, const wxString& name,
    const wxArrayString& labels, const wxArrayInt& values = wxArrayInt(),
    int value = 0);

  virtual void OnCustomPaint(wxDC& dc, const wxRect& rect, wxPGPaintData& paintdata);
  virtual wxSize GetImageSize() const;
};


WX_PG_DECLARE_PROPERTY_WITH_DECL(wxFontDataProperty,const wxFontData&,wxFontData(),wxPG_EXTRAS_DECL)
WX_PG_DECLARE_PROPERTY_WITH_DECL(wxPointProperty,const wxPoint&,wxPoint(0,0),wxPG_EXTRAS_DECL)
WX_PG_DECLARE_PROPERTY_WITH_DECL(wxSizeProperty,const wxSize&,wxSize(0,0),wxPG_EXTRAS_DECL)
WX_PG_DECLARE_PROPERTY_WITH_DECL(wxLongLongProperty,const wxLongLong&,wxLongLong(0),wxPG_EXTRAS_DECL)
WX_PG_DECLARE_ARRAYSTRING_PROPERTY_WITH_DECL(wxDirsProperty,wxPG_EXTRAS_DECL)



class wxVector2f
{
public:
  wxVector2f()
  {
    x = y = 0.0;
  }
  wxVector2f(float _x, float _y)
  {
    x = _x; 
    y = _y; 
  }
  friend inline bool operator==(const wxVector2f &a, const wxVector2f &b)
  {
    return (a.x == b.x && a.y == b.y);
  }

  float x, y;
};


class wxVector3f
{
public:
  wxVector3f()
  {
    x = y = z = 0.0;
  }
  wxVector3f(float _x, float _y, float _z)
  {
    x = _x; 
    y = _y; 
    z = _z;
  }
  friend inline bool operator==(const wxVector3f &a, const wxVector3f &b)
  {
    return (a.x == b.x && a.y == b.y && a.z == b.z);
  }

  float x, y, z;
};


class wxVector4f
{
public:
  wxVector4f()
  {
    x = y = z = w = 0.0;
  }
  wxVector4f(float _x, float _y, float _z, float _w)
  {
    x = _x; 
    y = _y; 
    z = _z;
    w = _w;
  }
  friend inline bool operator==(const wxVector4f &a, const wxVector4f &b)
  {
    return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
  }

  float x, y, z, w;
};

WX_PG_DECLARE_VALUE_TYPE_VOIDP(wxVector2f)
WX_PG_DECLARE_PROPERTY(wxVector2Property,const wxVector2f&,wxVector2f())
WX_PG_DECLARE_VALUE_TYPE_VOIDP(wxVector3f)
WX_PG_DECLARE_PROPERTY(wxVector3Property,const wxVector3f&,wxVector3f())
WX_PG_DECLARE_VALUE_TYPE_VOIDP(wxVector4f)
WX_PG_DECLARE_PROPERTY(wxVector4Property,const wxVector4f&,wxVector4f())


#endif // __PROPERTY_GRID_TYPES_H_

// -- EOF


