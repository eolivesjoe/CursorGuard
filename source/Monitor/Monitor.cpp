#include "Monitor.h"

BOOL CALLBACK
MonitorCallback(
    HMONITOR monitor,
    HDC,
    LPRECT,
    LPARAM data)
{
    auto* monitors = reinterpret_cast<std::vector<Monitor>*>(data);

    MONITORINFO info{};
    info.cbSize = sizeof(info);

    if (!GetMonitorInfo(monitor, &info))
    {
        return true;
    }

    Monitor result;
    result.bounds = info.rcMonitor;
    result.primary = (info.dwFlags & MONITORINFOF_PRIMARY) != 0;

    monitors->push_back(result);

    return true;
}

std::vector<Monitor> 
GetMonitors()
{
    std::vector<Monitor> monitors;

    EnumDisplayMonitors(
        nullptr,
        nullptr,
        MonitorCallback,
        reinterpret_cast<LPARAM>(&monitors)
    );

    return monitors;
}
