
#ifndef __TRASNFORM_PANEL_H_
#define __TRASNFORM_PANEL_H_


#include "libEngine.h"
#include "libEditor.h"


class TransformPanel : public wxPanel
{
public:
  TransformPanel(EditorPanel *pParent);
  virtual ~TransformPanel();

  void GetPos(float &x, float &y, float &z) const;
  void SetPos(float x, float y, float z);

  void GetRot(float &x, float &y, float &z) const;
  void SetRot(float x, float y, float z);

  void GetScale(float &x, float &y, float &z) const;
  void SetScale(float x, float y, float z);

  void OnPosChanged(wxCommandEvent& event);
  void OnRotChanged(wxCommandEvent& event);
  void OnScaleChanged(wxCommandEvent& event);

protected:
  DECLARE_EVENT_TABLE();

private:
  bool  m_AllowEvents;
  float m_PosX;  
  float m_PosY;  
  float m_PosZ;  
  float m_RotX;  
  float m_RotY;  
  float m_RotZ;  
  float m_ScaleX;  
  float m_ScaleY;  
  float m_ScaleZ;  

};


#endif // __TRASNFORM_PANEL_H_

// -- EOF


