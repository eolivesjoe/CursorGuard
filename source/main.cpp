#include "CursorLock/CursorLock.h"
#include "Monitor/Monitor.h"

#include <iostream>

int main(int argc, char* argv[])
{
    const auto monitors = GetMonitors();

    if (monitors.empty())
    {
        std::cerr << "No monitors found.\n";
        return 1;
    }

    for (size_t i = 0; i < monitors.size(); ++i)
    {
        std::cout << i + 1;

        if (monitors[i].primary)
            std::cout << " [Primary]";

        std::cout << '\n';
    }

    std::cout << "Select monitor: ";

    int selected;
    std::cin >> selected;

    if (selected < 1 || selected > static_cast<int>(monitors.size()))
    {
        std::cerr << "Invalid monitor.\n";
        return 1;
    }

    const RECT bounds = monitors[selected - 1].bounds;

    constexpr int HOTKEY_TOGGLE = 1;
    constexpr int HOTKEY_EXIT = 2;

    if (!RegisterHotKey(
        nullptr,
        HOTKEY_TOGGLE,
        MOD_CONTROL | MOD_ALT,
        'L'))
    {
        std::cerr << "Failed to register lock hotkey.\n";
        return 1;
    }

    RegisterHotKey(
        nullptr,
        HOTKEY_EXIT,
        MOD_CONTROL | MOD_ALT,
        'Q');

    const UINT_PTR timer = SetTimer(
        nullptr,
        0,
        250,
        nullptr);

    CursorLock cursorLock;

    std::cout << "\nCtrl+Alt+L - Toggle cursor lock\n";
    std::cout << "Ctrl+Alt+Q - Exit\n";

    MSG message{};

    while (GetMessage(&message, nullptr, 0, 0) > 0)
    {
        if (message.message == WM_HOTKEY)
        {
            if (message.wParam == HOTKEY_TOGGLE)
            {
                if (cursorLock.IsLocked())
                {
                    cursorLock.Unlock();
                    std::cout << "Unlocked\n";
                }
                else
                {
                    cursorLock.Lock(bounds);
                    std::cout << "Locked\n";
                }
            }

            if (message.wParam == HOTKEY_EXIT)
            {
                cursorLock.Unlock();
                PostQuitMessage(0);
            }
        }

        if (message.message == WM_TIMER)
        {
            cursorLock.Refresh();
        }
    }

    KillTimer(nullptr, timer);

    UnregisterHotKey(nullptr, HOTKEY_TOGGLE);
    UnregisterHotKey(nullptr, HOTKEY_EXIT);

    cursorLock.Unlock();

    return 0;
}
