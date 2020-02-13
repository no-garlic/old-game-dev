
#ifndef __UNDO_ACTION_STATIC_MESH_ADD_H_
#define __UNDO_ACTION_STATIC_MESH_ADD_H_


#include "libEngine.h"
#include "libEditor.h"
#include "UndoManager.h"


class UndoAction_StaticMesh_Add_Delete : public UndoAction
{
public:
  UndoAction_StaticMesh_Add_Delete();
  virtual ~UndoAction_StaticMesh_Add_Delete();

  // Newly added node
  void SetAddNode(const String &path);
  void SetAddMesh(const String &filename);
  void SetAddTransform(const Vec3 &pos, const Vec3 &rot, const Vec3 &scale);

  // Deleted node
  void SetDeleteNode(const String &path);
  void SetDeleteMesh(const String &filename);
  void SetDeleteTransform(const Vec3 &pos, const Vec3 &rot, const Vec3 &scale);

  virtual void Undo();
  virtual void Redo();

private:
  String  m_AddPath;
  String  m_AddFilename;
  Vec3    m_AddPos;
  Vec3    m_AddRot;
  Vec3    m_AddScale;
  String  m_DeletePath;
  String  m_DeleteFilename;
  Vec3    m_DeletePos;
  Vec3    m_DeleteRot;
  Vec3    m_DeleteScale;
};


#endif // __UNDO_ACTION_STATIC_MESH_ADD_H_

// -- EOf

