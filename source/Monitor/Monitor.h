#pragma once

#include <Windows.h>
#include <vector>

struct Monitor
{
    RECT bounds;
    bool primary;
};

std::vector<Monitor> GetMonitors();
