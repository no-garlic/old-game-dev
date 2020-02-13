
#ifndef __EDITOR_RESOURCE_H_
#define __EDITOR_RESOURCE_H_


#define WX_STATIC(id, label, x, y, w, h) {\
  new wxStaticText(this, id, label, wxPoint(x,y), wxSize(w,h));\
  }

#define WX_TEXT(id, text, x, y, w, h, validator) {\
  wxTextCtrl *__pText = new wxTextCtrl(this, id, text, wxPoint(x,y), wxSize(w,h), 0, validator);\
    __pText->SetWindowStyle(wxEVT_COMMAND_TEXT_ENTER | wxTE_LEFT);\
  }

#define WX_SPIN(id, min_, max_, val_, x, y, w, h) {\
  wxSpinCtrl *__pSpin = new wxSpinCtrl(this, id, "", wxPoint(x,y), wxSize(w,h));\
    __pSpin->SetRange(min_, max_);\
    __pSpin->SetValue(val_);\
  }


inline bool wxIsFloat(const wxString &str)
{
  const wxChar *s = str.c_str();
  if (wxStrlen(s))
  {
     if ((s[0] == wxT('-')) || (s[0] == wxT('+'))) 
     {
       s++;
     }
  }
  
  while (*s)
  {
    if (!wxIsdigit(*s) && (*s) != wxT('.'))
    {
      return false;
    }
    s++;
  }

  return true;
}

inline float wxStrToFloat(const wxString &str)
{
  if (str.IsEmpty())
    return 0.0f;

  if (wxIsFloat(str))
    return LexicalCast<float>(String(str.c_str()));

  return 0.0f;
}


inline wxString wxFloatToStr(float val)
{
  char buffer[32];
  sprintf(buffer, "%01.2f", val);
  return wxString(buffer);
}


enum TreeNodeFlags
{
  TREE_NODE_PICKABLE      = (1 << 0),
  TREE_NODE_RENDERABLE    = (1 << 1),
  TREE_NODE_FROZEN        = (1 << 2),

  TREE_NODE_ALL           = 0xffffffff
};


enum EditorResource
{
  // Major Frames
  EDT_TOP_FRAME             = 4000,
  EDT_BOTTOM_FRAME          = 4001,
  EDT_LEFT_FRAME            = 4002,
  EDT_RIGHT_FRAME           = 4003,

  // Major Panels
  EDT_TOP_PANEL             = 4020,
  EDT_BOTTOM_PANEL          = 4021,
  EDT_LEFT_PANEL            = 4022,
  EDT_RIGHT_PANEL           = 4023,

  // Sub Panels
  EDT_TRANSFORM_PANEL       = 4050,
  EDT_TOOL_PANEL            = 4051,
  EDT_CONTENT_PANEL         = 4052,
  EDT_SCENE_PANEL           = 4053,

  // Left Panel
  CTL_SIDEPANEL_BOOK        = 4100,

  // Transform Panel
  CTL_TRASNFORM_XPOS        = 4500,
  CTL_TRASNFORM_YPOS        = 4501,
  CTL_TRASNFORM_ZPOS        = 4502,
  CTL_TRASNFORM_XROT        = 4503,
  CTL_TRASNFORM_YROT        = 4504,
  CTL_TRASNFORM_ZROT        = 4505,
  CTL_TRASNFORM_XSCL        = 4506,
  CTL_TRASNFORM_YSCL        = 4507,
  CTL_TRASNFORM_ZSCL        = 4508,

  // Content Panel
  CTL_CONTENT_TREE          = 4520,
  CTL_SCENE_TREE            = 4521,
  MNU_SCENE_NEW_GROUP       = 4522,
  MNU_SCENE_NEW_MESH        = 4523,
  MNU_RENDER_FLAG           = 4524,
  MNU_FROZEN_FLAG           = 4525,
  MNU_PICKABLE_FLAG         = 4526,
  MNU_DELETE_SELECTED       = 4527,

  // Tool Bar
  TBB_NEW                   = 4600,
  TBB_OPEN                  = 4601,
  TBB_SAVE                  = 4602,
  TBB_COPY                  = 4603,
  TBB_CUT                   = 4604,
  TBB_PASTE                 = 4605,
  TBB_UNDO                  = 4606,
  TBB_REDO                  = 4607,

  // Tool Panel
  TPB_SELECT                = 4700,
  TPB_MOVE                  = 4701,
  TPB_ROTATE                = 4702,
  TPB_SCALE                 = 4703,
  TPB_X                     = 4704,
  TPB_Y                     = 4705,
  TPB_Z                     = 4706,
  TPB_XY                    = 4707,
  TPB_YZ                    = 4708,
  TPB_ZX                    = 4709,

  // File Menu
  MNU_FILE_INDEX_START      = 5000,
  MNU_FILE_NEW              = 5015,
  MNU_FILE_OPEN             = 5016,
  MNU_FILE_SAVE             = 5017,
  MNU_FILE_SAVEAS           = 5018,
  MNU_FILE_CLOSE            = 5019,
  MNU_FILE_EXIT             = 5020,
  MNU_FILE_INDEX_END        = 5099,

  // Edit Menu
  MNU_EDIT_INDEX_START      = 5100,
  MNU_EDIT_UNDO             = 5101,
  MNU_EDIT_REDO             = 5102,
  MNU_EDIT_COPY             = 5103,
  MNU_EDIT_CUT              = 5104,
  MNU_EDIT_PASTE            = 5105,
  MNU_EDIT_DELETE           = 5106,
  MNU_EDIT_INDEX_END        = 5199,

  // View Menu
  MNU_VIEW_MODE_SOLID       = 5200,
  MNU_VIEW_MODE_WIRE        = 5201,
  MNU_VIEW_MODE_SOLID_WIRE  = 5202,
  MNU_VIEW_MODE_UNLIT       = 5203,
  MNU_VIEW_MODE_UNTEX       = 5204,
  MNU_VIEW_CAM_PERSPECTIVE  = 5210,
  MNU_VIEW_CAM_FRONT        = 5211,
  MNU_VIEW_CAM_BACK         = 5212,
  MNU_VIEW_CAM_LEFT         = 5213,
  MNU_VIEW_CAM_RIGHT        = 5214,
  MNU_VIEW_CAM_TOP          = 5215,
  MNU_VIEW_CAM_BOTTOM       = 5216,
  MNU_VIEW_INDEX_END        = 5299,

};


#endif // __EDITOR_RESOURCE_H_

// -- EOF

