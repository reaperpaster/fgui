//
// FGUI - WIN32 Input System
//

#pragma once

#include <array>

#define FGUI_IMPLEMENTATION
#include <FGUI/FGUI.hpp>

namespace FGUI_INPUT_WIN32
{
   inline std::array<bool, 256> m_prgpCurrentPressedKeys, m_prgpOldPressedKeys;
   inline FGUI::POINT m_ptCursorPosition, m_ptCursorPositionDelta;

   inline void PullInput()
  {
    static FGUI::POINT ptLastKnownPosition = { 0, 0 };

    std::copy(m_prgpCurrentPressedKeys.begin(), m_prgpCurrentPressedKeys.end(), m_prgpOldPressedKeys.begin());

    for (std::size_t i = 0; i < 256; i++)
    {
      m_prgpCurrentPressedKeys.at(i) = GetAsyncKeyState(i);
    }

    // Get current cursor position
    GetCursorPos(reinterpret_cast<LPPOINT>(&m_ptCursorPosition));

    // Calculate the cursor position delta
    m_ptCursorPositionDelta = { (m_ptCursorPosition.m_iX - ptLastKnownPosition.m_iX), (m_ptCursorPosition.m_iY - ptLastKnownPosition.m_iY) };

    // Get last known position of the cursor
    ptLastKnownPosition = m_ptCursorPosition;
  }

  inline bool GetKeyState(int _key_code)
  {
    return m_prgpCurrentPressedKeys.at(_key_code);
  }

  inline bool GetKeyRelease(int _key_code)
  {
    return (!m_prgpCurrentPressedKeys.at(_key_code) && m_prgpOldPressedKeys.at(_key_code));
  }

  inline bool GetKeyPress(int _key_code)
  {
    return (m_prgpCurrentPressedKeys.at(_key_code) && !m_prgpOldPressedKeys.at(_key_code));
  }

  inline FGUI::POINT GetCursorPos()
  {
    return m_ptCursorPosition;
  }

  inline FGUI::POINT GetCursorPosDelta()
  {
    return m_ptCursorPositionDelta;
  }

  inline int GetCursorWheelDelta()
  {
    return m_iCursorWheelDelta;
  }

  inline bool IsCursorInArea(FGUI::AREA area)
  {
    return (GetCursorPos().m_iX > area.m_iLeft && GetCursorPos().m_iY > area.m_iTop &&
      GetCursorPos().m_iX < area.m_iLeft + area.m_iRight && GetCursorPos().m_iY < area.m_iTop + area.m_iBottom);
  }

  // NOTE: call this function only once (preferably when you initialize your application)
  inline void OnEntryPoint()
  {
    FGUI::INPUT.PullInput = FGUI_INPUT_WIN32::PullInput;
    FGUI::INPUT.GetKeyState = FGUI_INPUT_WIN32::GetKeyState;
    FGUI::INPUT.GetKeyRelease = FGUI_INPUT_WIN32::GetKeyRelease;
    FGUI::INPUT.GetKeyPress = FGUI_INPUT_WIN32::GetKeyPress;
    FGUI::INPUT.GetCursorPos = FGUI_INPUT_WIN32::GetCursorPos;
    FGUI::INPUT.GetCursorPosDelta = FGUI_INPUT_WIN32::GetCursorPosDelta;
    FGUI::INPUT.GetCursorWheelDelta = FGUI_INPUT_WIN32::GetCursorWheelDelta;
    FGUI::INPUT.IsCursorInArea = FGUI_INPUT_WIN32::IsCursorInArea;
  }
}
