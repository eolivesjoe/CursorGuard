#include "Application.h"

#include <iostream>

int Application::Run()
{
    if (!Initialize())
    {
        return 1;
    }

    RunMessageLoop();

    Shutdown();

    return 0;
}

bool Application::Initialize()
{
    m_monitors = GetMonitors();

    if (m_monitors.empty())
    {
        std::cerr << "No monitors found.\n";
        return false;
    }

    if (!SelectMonitor())
    {
        std::cerr << "Invalid monitor.\n";
        return false;
    }

    if (!RegisterHotkeys())
    {
        std::cerr << "Failed to register hotkeys.\n";
        return false;
    }

    m_timer = SetTimer(
        nullptr,
        0,
        250,
        nullptr);

    std::cout << "\nCtrl+Alt+L to toggle cursor lock\n";
    std::cout << "Ctrl+Alt+Q to exit\n";

    return true;
}

bool Application::SelectMonitor()
{
    for (size_t i = 0; i < m_monitors.size(); ++i)
    {
        std::cout << i + 1;

        if (m_monitors[i].primary)
            std::cout << " [Primary]";

        std::cout << '\n';
    }

    std::cout << "Select monitor: ";

    int selected;
    std::cin >> selected;

    if (selected < 1 ||
        selected > static_cast<int>(m_monitors.size()))
    {
        return false;
    }

    m_bounds = m_monitors[selected - 1].bounds;

    return true;
}

bool Application::RegisterHotkeys()
{
    if (!RegisterHotKey(
        nullptr,
        s_hotkeyToggle,
        MOD_CONTROL | MOD_ALT,
        'L'))
    {
        return false;
    }

    if (!RegisterHotKey(
        nullptr,
        s_hotkeyExit,
        MOD_CONTROL | MOD_ALT,
        'Q'))
    {
        UnregisterHotKey(nullptr, s_hotkeyToggle);
        return false;
    }

    return true;
}

void Application::RunMessageLoop()
{
    MSG message{};

    while (GetMessage(&message, nullptr, 0, 0) > 0)
    {
        switch (message.message)
        {
        case WM_HOTKEY:
            HandleHotkey(message.wParam);
            break;

        case WM_TIMER:
            m_cursorLock.Refresh();
            break;
        }
    }
}

void Application::HandleHotkey(WPARAM hotkey)
{
    if (hotkey == s_hotkeyToggle)
    {
        if (m_cursorLock.IsLocked())
        {
            m_cursorLock.Unlock();
            std::cout << "Unlocked\n";
        }
        else
        {
            if (m_cursorLock.Lock(m_bounds))
            {
                std::cout << "Locked\n";
            }
            else
            {
                std::cerr << "Failed to lock cursor.\n";
            }
        }

        return;
    }

    if (hotkey == s_hotkeyExit)
    {
        m_cursorLock.Unlock();
        PostQuitMessage(0);
    }
}

void Application::Shutdown()
{
    if (m_timer != 0)
    {
        KillTimer(nullptr, m_timer);
    }

    UnregisterHotKey(nullptr, s_hotkeyToggle);
    UnregisterHotKey(nullptr, s_hotkeyExit);

    m_cursorLock.Unlock();
}