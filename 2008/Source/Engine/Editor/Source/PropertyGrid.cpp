
#include "PropertyGrid.h"
#include "PropertyGridTypes.h"


PropertyGrid::PropertyGrid(wxWindow *pParent, wxWindowID id)
{
  m_pCallback     = NULL;
  m_pParentWindow = pParent;

  long flags = wxTAB_TRAVERSAL | wxPG_TOOLBAR;

  m_pGridManager  = new wxPropertyGridManager(pParent, id, wxDefaultPosition, wxDefaultSize, flags);
  m_pGrid         = m_pGridManager->GetGrid();

  m_pGridManager->SetExtraStyle(wxPG_EX_MODE_BUTTONS);

  m_pGridManager->RegisterAdvancedPropertyClasses();
  wxPGRegisterPropertyClass(wxFontDataProperty);
  wxPGRegisterPropertyClass(wxPointProperty);
  wxPGRegisterPropertyClass(wxSizeProperty);
  wxPGRegisterPropertyClass(wxDirsProperty);
  wxPGRegisterPropertyClass(wxArrayDoubleProperty);
  wxPGRegisterPropertyClass(wxVector2Property);
  wxPGRegisterPropertyClass(wxVector3Property);
  wxPGRegisterPropertyClass(wxVector4Property);

  m_pGrid->SetVerticalSpacing(2);
  m_pGridManager->RegisterAdditionalEditors();
  m_pGridManager->AddPage("Standard");
  m_pGridManager->SetTargetPage(0);
}


PropertyGrid::~PropertyGrid()
{
}


void PropertyGrid::SetPosition(const wxPoint &pos)
{
  m_pGridManager->SetPosition(pos);
}


void PropertyGrid::SetSize(const wxSize &size)
{
  m_pGridManager->SetSize(size);
}


void PropertyGrid::SetObserver(const Callback<void, const String &> &cb)
{
  RemoveObserver();
  m_pCallback = cb.Clone();
}


void PropertyGrid::RemoveObserver()
{
  delete m_pCallback;
  m_pCallback = NULL;
}


void PropertyGrid::DeleteAll()
{
  m_pGridManager->ClearPage(0);
}


uint PropertyGrid::AddLookupTable(const StringArray &table)
{
  wxArrayString stringArray;

  for (uint i = 0; i < table.size(); i++)
    stringArray.Add(wxString(table[i].c_str()));

  m_LookupTables.push_back(stringArray);
  return m_LookupTables.size() - 1;
}


void PropertyGrid::SetLookupTable(uint lookupId, const StringArray &table)
{
  if (lookupId >= m_LookupTables.size())
    return;

  wxArrayString &stringArray = m_LookupTables[lookupId];
  stringArray.Clear();

  for (uint i = 0; i < table.size(); i++)
    stringArray.Add(wxString(table[i].c_str()));
}


void PropertyGrid::AddGroup(const String &name)
{
  m_pGrid->Append(wxPropertyCategory(name.c_str(), wxPG_LABEL));
  m_pGrid->Refresh();
}


void PropertyGrid::Add(const String &name, const String &value, uint lookupId, bool allowOthers)
{
  if (lookupId >= m_LookupTables.size())
    return;

  wxArrayString &stringArray = m_LookupTables[lookupId];

  int selected = 0;

  wxPGChoices choices;
  for (uint i = 0; i < stringArray.Count(); i++)
  {
    choices.Add(stringArray.Item(i), (int) i);

    if (stringArray.Item(i) == wxString(value.c_str()))
      selected = i;
  }  

  wxPGId id = m_pGrid->Append(wxEnumProperty(name.c_str(), wxPG_LABEL, choices, selected));
  m_RowNames[name] = id;
  m_pGrid->Refresh();
}


void PropertyGrid::Add(const String &name, const String &value, bool readOnly)
{
  wxPGId id = m_pGrid->Append(wxStringProperty(name.c_str(), wxPG_LABEL, value.c_str()));
  m_RowNames[name] = id;
  m_pGrid->SetPropertyReadOnly(id, readOnly);
  m_pGrid->Refresh();
}


void PropertyGrid::Add(const String &name, int value, bool readOnly)
{
  wxPGId id = m_pGrid->Append(wxIntProperty(name.c_str(), wxPG_LABEL, value));
  m_RowNames[name] = id;
  m_pGrid->SetPropertyReadOnly(id, readOnly);
  if (!readOnly)
    m_pGrid->SetPropertyEditor(id, wxPG_EDITOR(SpinCtrl));
  m_pGrid->Refresh();
}


void PropertyGrid::Add(const String &name, uint value, bool readOnly)
{
  wxPGId id = m_pGrid->Append(wxUIntProperty(name.c_str(), wxPG_LABEL, value));
  m_RowNames[name] = id;
  m_pGrid->SetPropertyReadOnly(id, readOnly);
  if (!readOnly)
    m_pGrid->SetPropertyEditor(id, wxPG_EDITOR(SpinCtrl));
  m_pGrid->Refresh();
}


void PropertyGrid::Add(const String &name, bool value, bool readOnly)
{
  wxPGId id = m_pGrid->Append(wxBoolProperty(name.c_str(), wxPG_LABEL, value));
  m_RowNames[name] = id;
  m_pGrid->SetPropertyReadOnly(id, readOnly);
  m_pGrid->SetPropertyAttribute(id, wxPG_BOOL_USE_CHECKBOX, (long)1);
  m_pGrid->Refresh();
}


void PropertyGrid::Add(const String &name, float value, bool readOnly)
{
  wxPGId id = m_pGrid->Append(wxFloatProperty(name.c_str(), wxPG_LABEL, value));
  m_RowNames[name] = id;
  m_pGrid->SetPropertyReadOnly(id, readOnly);
  m_pGrid->Refresh();
}


void PropertyGrid::Add(const String &name, const Color &value, bool readOnly)
{
  wxColour col(value.operator DWORD());

  wxPGId id = m_pGrid->Append(wxColourProperty(name.c_str(), wxPG_LABEL, col));
  m_RowNames[name] = id;
  m_pGrid->SetPropertyReadOnly(id, readOnly);
  m_pGrid->Refresh();
}


void PropertyGrid::Add(const String &name, const Vec2 &value, bool readOnly)
{
  wxVector2f *pVec = (wxVector2f *) &value;
  wxPGId id = m_pGrid->Append(wxVector2Property(name.c_str(), wxPG_LABEL, *pVec));
  m_RowNames[name] = id;
  m_pGrid->SetPropertyReadOnly(id, readOnly);
  m_pGrid->Refresh();
}


void PropertyGrid::Add(const String &name, const Vec3 &value, bool readOnly)
{
  wxVector3f *pVec = (wxVector3f *) &value;
  wxPGId id = m_pGrid->Append(wxVector3Property(name.c_str(), wxPG_LABEL, *pVec));
  m_RowNames[name] = id;
  m_pGrid->SetPropertyReadOnly(id, readOnly);
  m_pGrid->Refresh();
}


void PropertyGrid::Add(const String &name, const Vec4 &value, bool readOnly)
{
  wxVector4f *pVec = (wxVector4f *) &value;
  wxPGId id = m_pGrid->Append(wxVector4Property(name.c_str(), wxPG_LABEL, *pVec));
  m_RowNames[name] = id;
  m_pGrid->SetPropertyReadOnly(id, readOnly);
  m_pGrid->Refresh();
}


bool PropertyGrid::Get(const String &name, String &value)
{
  Map<String, wxPGId>::iterator iter = m_RowNames.find(name);
  if (iter == m_RowNames.end())
    return false;

  value = (m_pGrid->GetPropertyValueAsString(iter->second)).wx_str();
  return true;
}


bool PropertyGrid::Get(const String &name, int &value)
{
  String s;
  if (!Get(name, s))
    return false;

  if (s.empty())
  {
    value = 0;
    return true;
  }

  return (sscanf(s.c_str(), "%d", &value) == 1);
}


bool PropertyGrid::Get(const String &name, uint &value)
{
  String s;
  if (!Get(name, s))
    return false;

  if (s.empty())
  {
    value = 0;
    return true;
  }

  return (sscanf(s.c_str(), "%u", &value) == 1);
}


bool PropertyGrid::Get(const String &name, bool &value)
{
  int i;
  if (!Get(name, i))
    return false;

  value = (i != 0);
  return true;
}


bool PropertyGrid::Get(const String &name, float &value)
{
  String s;
  if (!Get(name, s))
    return false;

  if (s.empty())
  {
    value = 0.0f;
    return true;
  }

  return (sscanf(s.c_str(), "%f", &value) == 1);
}


bool PropertyGrid::Get(const String &name, Color &value)
{
  String s;
  if (!Get(name, s))
    return false;

  if (value.FromString(s, false))
    return true;

  return false;
}


bool PropertyGrid::Get(const String &name, Vec3 &value)
{
  String s;
  if (!Get(name, s))
    return false;

  if (s.empty())
    return false;

  if (value.FromString(s))
    return true;

  return false;
}



void PropertyGrid::OnCellValueChanged(wxPropertyGridEvent &event)
{
  if (m_pCallback)
  {
    (*m_pCallback)(String(event.GetPropertyName().wx_str()));
  }
}


// -- EOf

