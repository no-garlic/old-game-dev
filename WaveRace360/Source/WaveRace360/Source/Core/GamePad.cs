// ----------------------------------------------------------------------------
// File: GamePad.cs
// Desc: Manages the state and the history of the GamePad
// Auth: Michael Petrou
// (C) Copyright: 2008
// ----------------------------------------------------------------------------

using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;


namespace WaveRace360
{
  // --------------------------------------------------------------------------
  // Name: GamePad
  // Desc: Manages the state and history of a GamePad
  // --------------------------------------------------------------------------
  public class GamePad
  {
    // ------------------------------------------------------------------------
    // Public properties
    // ------------------------------------------------------------------------
    public PlayerIndex    PlayerIndex     { get { return m_playerIndex; } }
    public GamePadState   State           { get { return m_current; } }
    public GamePadState   PreviousState   { get { return m_previous; } }


    // ------------------------------------------------------------------------
    // Private members
    // ------------------------------------------------------------------------
    private GamePadState  m_current;      // The current state
    private GamePadState  m_previous;     // The previous frame state
    private PlayerIndex   m_playerIndex;  // The player index


    // ------------------------------------------------------------------------
    // Name: GamePad
    // Desc: Constructor
    // Parm: PlayerIndex a_playerIndex - The player index to use
    // ------------------------------------------------------------------------
    public GamePad(PlayerIndex a_playerIndex)
    {
      m_current  = new GamePadState();
      m_previous = new GamePadState();
      m_playerIndex = a_playerIndex;
    }


    // ------------------------------------------------------------------------
    // Name: Update
    // Desc: Update each frame
    // Parm: float a_deltaTime - the delta frame time
    // ------------------------------------------------------------------------
    public void Update(float a_deltaTime)
    {
      m_previous = m_current;
      m_current  = Microsoft.Xna.Framework.Input.GamePad.GetState(m_playerIndex);
    }


    // ------------------------------------------------------------------------
    // Name: IsButtonPressed
    // Desc: Test if a button was pushed down since the last frame
    // Parm: Buttons a_button - the button(s) to test
    // Retn: bool - true if pressed, otherwise false
    // ------------------------------------------------------------------------
    public bool IsButtonPressed(Buttons a_button)
    {
      if (m_current.IsButtonDown(a_button) && !m_previous.IsButtonDown(a_button))
      {
        return true;
      }
      return false;
    }


    // ------------------------------------------------------------------------
    // Name: IsAnyButtonPressed
    // Desc: Test if any button has been pressed since the last frame
    // Retn: bool - true if a button was pressed, otherewise false
    // ------------------------------------------------------------------------
    public bool IsAnyButtonPressed()
    {
      // Check if the button state has changed
      if (m_current.Buttons.Equals(m_previous.Buttons))
      {
        return false;
      }

      // Test each button
      if (IsButtonPressed(Buttons.A) ||
          IsButtonPressed(Buttons.B) ||
          IsButtonPressed(Buttons.Back) ||
          IsButtonPressed(Buttons.DPadDown) ||
          IsButtonPressed(Buttons.DPadLeft) ||
          IsButtonPressed(Buttons.DPadRight) ||
          IsButtonPressed(Buttons.DPadUp) ||
          IsButtonPressed(Buttons.LeftShoulder) ||
          IsButtonPressed(Buttons.LeftStick) ||
          IsButtonPressed(Buttons.LeftTrigger) ||
          IsButtonPressed(Buttons.RightShoulder) ||
          IsButtonPressed(Buttons.RightStick) ||
          IsButtonPressed(Buttons.RightTrigger) ||
          IsButtonPressed(Buttons.Start) ||
          IsButtonPressed(Buttons.X) ||
          IsButtonPressed(Buttons.Y))
      {
        return true;
      }

      return false;
    }


    // ------------------------------------------------------------------------
    // Name: IsButtonReleased
    // Desc: Test if a button was released up since the last frame
    // Parm: Buttons a_button - the button(s) to test
    // Retn: bool - true if released, otherwise false
    // ------------------------------------------------------------------------
    public bool IsButtonReleased(Buttons a_button)
    {
      if (m_current.IsButtonUp(a_button) && !m_previous.IsButtonUp(a_button))
      {
        return true;
      }
      return false;
    }


    //
    // ------------------------------------------------------------------------
  }
}


// -- EOF


