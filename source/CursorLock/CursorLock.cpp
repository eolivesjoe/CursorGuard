#include <iostream>
#include "CursorLock.h"

bool 
CursorLock::Lock(const RECT& bounds)
{
    if (!ClipCursor(&bounds))
    {
        std::cout << "ClipCursor failed: " << GetLastError() << '\n';
        return false;
    }

    RECT actual{};
    GetClipCursor(&actual);

    m_bounds = bounds;
    m_locked = true;

    return true;
}
void 
CursorLock::Unlock()
{
    ClipCursor(nullptr);
    m_locked = false;
}

void
CursorLock::Refresh()
{
    if (m_locked)
    {
        ClipCursor(&m_bounds);
    }
}

bool 
CursorLock::IsLocked() const
{
    return m_locked;
}
