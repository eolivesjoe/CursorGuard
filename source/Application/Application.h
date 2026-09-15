#pragma once

#include "../CursorLock/CursorLock.h"
#include "../Monitor/Monitor.h"

#include <Windows.h>
#include <vector>

class Application
{
public:
    int Run();

private:
    bool Initialize();
    void Shutdown();

    bool SelectMonitor();
    bool RegisterHotkeys();

    void RunMessageLoop();
    void HandleHotkey(WPARAM hotkey);

private:
    std::vector<Monitor> m_monitors;
    CursorLock m_cursorLock;
    RECT m_bounds{};
    UINT_PTR m_timer = 0;

    static constexpr int s_hotkeyToggle = 1;
    static constexpr int s_hotkeyExit = 2;
};