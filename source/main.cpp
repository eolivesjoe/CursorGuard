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

    std::cout << "Monitors:\n\n";

    for (size_t i = 0; i != monitors.size(); ++i)
    {
        const Monitor& monitor = monitors[i];

        std::cout
            << i + 1 << ": "
            << monitor.bounds.left << ", "
            << monitor.bounds.top << " -> "
            << monitor.bounds.right << ", "
            << monitor.bounds.bottom;

        if (monitor.primary)
            std::cout << " [Primary]";

        std::cout << '\n';
    }

    std::cout << "\nSelect monitor: ";

    int selected;
    std::cin >> selected;

    if (selected < 1 || selected > static_cast<int>(monitors.size()))
    {
        std::cerr << "Invalid monitor.\n";
        return 1;
    }

    CursorLock cursorLock;

    if (!cursorLock.Lock(monitors[selected - 1].bounds))
    {
        std::cerr << "Failed to lock cursor.\n";
        return 1;
    }

    std::cout << "Cursor locked to monitor " << selected << ".\n";

    std::cin.ignore();
    std::cin.get();

    cursorLock.Unlock();

    return 0;
}