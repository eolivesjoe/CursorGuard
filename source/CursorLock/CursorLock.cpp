#include "CursorLock.h"

bool 
CursorLock::Lock(const RECT& bounds)
{
    if (!ClipCursor(&bounds))
    {
        return false;
    }

    m_locked = true;
    return true;
}

void 
CursorLock::Unlock()
{
    ClipCursor(nullptr);
    m_locked = false;
}

bool 
CursorLock::IsLocked() const
{
    return m_locked;
}
