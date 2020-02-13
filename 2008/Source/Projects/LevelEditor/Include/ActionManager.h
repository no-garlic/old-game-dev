
#ifndef __ACTION_MANAGER_H_
#define __ACTION_MANAGER_H_


// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "libEngine.h"
#include "libEditor.h"
#include "EditorAction.h"


// ----------------------------------------------------------------------------
// Manages all actions for the editor - provides a factory to create and set
// action parameters, and the ability to complete or discard non-instant
// actions.
// Note - the actual action logic is in the EditorAction derived classes.
// ----------------------------------------------------------------------------
class ActionManager : private Unique
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  ActionManager();
  virtual ~ActionManager();

  // --------------------------------------------------------------------------
  // Called each frame to update the actions and the user interface if needed
  // --------------------------------------------------------------------------
  void Update();

  // --------------------------------------------------------------------------
  // All available actions
  // --------------------------------------------------------------------------
  enum EditorActionType
  {
    // Scene group actions
    ACTION_SCENE_GROUP_ADD,
    ACTION_SCENE_GROUP_DELETE,
    ACTION_SCENE_GROUP_RENAME,

    // Static mesh actions
    ACTION_STATIC_MESH_ADD,
    ACTION_STATIC_MESH_DELETE,
    ACTION_STATIC_MESH_DUPLICATE,
    ACTION_STATIC_MESH_RENAME,
    ACTION_STATIC_MESH_MOVE,      // Interactive with the mouse
    ACTION_STATIC_MESH_ROTATE,    // Interactive with the mouse
    ACTION_STATIC_MESH_SCALE,     // Interactive with the mouse
    ACTION_STATIC_MESH_TRANSFORM, // Specify pos, rot, scale
    ACTION_STATIC_MESH_RELOCATE,  // Relocate to a different parent in the scene
    ACTION_STATIC_MESH_FLAG,      // Set a bit flag for a static mesh

    // Generic node actions
    ACTION_DELETE_SELECTED,

    // Document actions
    ACTION_DOCUMENT_NEW,
    ACTION_DOCUMENT_SAVE,
    ACTION_DOCUMENT_SAVEAS,
    ACTION_DOCUMENT_OPEN,
    ACTION_DOCUMENT_CLOSE,

    // Clipboard actions
    ACTION_CLIPBOARD_CUT,
    ACTION_CLIPBOARD_COPY,
    ACTION_CLIPBOARD_PASTE,

    // Undo actions
    ACTION_UNDO,
    ACTION_REDO,

    // Application actions
    ACTION_EXIT
  };

  // --------------------------------------------------------------------------
  // Create an action to be performed
  // --------------------------------------------------------------------------
  bool CreateAction(EditorActionType type, const String &nodePath = "");

  // --------------------------------------------------------------------------
  // Create an action to be performed, and complete it instantly.  Actions
  // that do not require user input or parameters can use this method for
  // convenience.
  // --------------------------------------------------------------------------
  bool CreateAndCompleteAction(EditorActionType type, const String &nodePath = "");

  // --------------------------------------------------------------------------
  // Set parameters for the current aciton
  // --------------------------------------------------------------------------
  void SetActionParameter(const String &paramName, const String &paramValue);
  void SetActionParameter(const String &paramName, const Vec3   &paramValue);
  void SetActionParameter(const String &paramName, int    paramValue);
  void SetActionParameter(const String &paramName, uint   paramValue);
  void SetActionParameter(const String &paramName, float  paramValue);
  void SetActionParameter(const String &paramName, bool   paramValue);

  // --------------------------------------------------------------------------
  // Either complete or discard an action which was started with CreateAction.
  // --------------------------------------------------------------------------
  bool CompleteAction();
  void DiscardAction();

  // --------------------------------------------------------------------------
  // Get the current action
  // --------------------------------------------------------------------------
  bool HasCurrentAction() const    { return m_pCurrentAction != NULL; }
  EditorAction *GetCurrentAction() { return m_pCurrentAction; }

  // --------------------------------------------------------------------------
  // The appliation (node) clipboard. Note, the clipboard holds a reference to
  // a node rather than copyinf it, so if the node is changed or becomes 
  // invalid, the clipboard will reflect that change (or become invlaid).
  // --------------------------------------------------------------------------
  struct Clipboard
  {
    bool    IsValid;  // Is the clipboard valid?
    bool    IsCut;    // Was the contents of the cut into the clipboard or copied?
    String  Path;     // The path of the node copied into the clipboard.
  };

  // --------------------------------------------------------------------------
  // Get the clipboard
  // --------------------------------------------------------------------------
  Clipboard &GetClipboard()   { return m_Clipboard; }

  // Manage *all* UI states: menus, toolbars, etc.
  /*
  void Update();
  void UpdateMenu();
  void UpdateToolBar();
  void UpdateToolPanel();
  */

private:
  // --------------------------------------------------------------------------
  // Private members
  // --------------------------------------------------------------------------
  Clipboard       m_Clipboard;
  EditorAction   *m_pCurrentAction;

};


#endif // __ACTION_MANAGER_H_

// -- EOF

