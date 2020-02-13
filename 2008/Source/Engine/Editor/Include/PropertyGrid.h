
#ifndef __PROPERTY_GRID_H_
#define __PROPERTY_GRID_H_


#include "libRenderExt.h"
#include "TreeNode.h"
#include "wxWindows/wxDisplay.h"
#include "wx/propgrid/propgrid.h"
#include "wx/image.h"


class PropertyGrid : private Unique
{
public:
  PropertyGrid(wxWindow *pParent, wxWindowID id = wxID_ANY);
  virtual ~PropertyGrid();

  // Set the position and size
  void SetPosition(const wxPoint &pos);
  void SetSize(const wxSize &size);

  // Set the observer for the grid
  void SetObserver(const Callback<void, const String &> &cb);
  void RemoveObserver();

  // Add or update a lookup table
  uint AddLookupTable(const StringArray &table);
  void SetLookupTable(uint lookupId, const StringArray &table);

  // Add a group to the grid
  void AddGroup(const String &name);

  // Add an item to the grid
  void Add(const String &name, const String &value, bool readOnly);
  void Add(const String &name, int value, bool readOnly);
  void Add(const String &name, uint value, bool readOnly);
  void Add(const String &name, bool value, bool readOnly);
  void Add(const String &name, float value, bool readOnly);
  void Add(const String &name, const Color &value, bool readOnly);
  void Add(const String &name, const Vec2 &value, bool readOnly);
  void Add(const String &name, const Vec3 &value, bool readOnly);
  void Add(const String &name, const Vec4 &value, bool readOnly);
  void Add(const String &name, const String &value, uint lookupId, bool allowOthers);

  // Delete all items int he grid
  void DeleteAll();

  // Get a value from the grid
  bool Get(const String &name, String &value);
  bool Get(const String &name, int &value);
  bool Get(const String &name, uint &value);
  bool Get(const String &name, bool &value);
  bool Get(const String &name, float &value);
  bool Get(const String &name, Color &value);
  bool Get(const String &name, Vec3 &value);

  void OnCellValueChanged(wxPropertyGridEvent &event);

private:
  wxWindow                       *m_pParentWindow;  // The parent window
  wxPropertyGrid                 *m_pGrid;          // The grid
  wxPropertyGridManager          *m_pGridManager;   // The grid manager
  Callback<void, const String &> *m_pCallback;      // The observer callback
  Map<String, wxPGId>             m_RowNames;       // The row names
  Array <wxArrayString>           m_LookupTables;   // The lookup tables

};


#endif // __PROPERTY_GRID_H_

// -- EOF

