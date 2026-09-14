#pragma once

#include <Windows.h>

class CursorLock
{
public:
    bool Lock(const RECT& bounds);
    void Unlock();
    void Refresh();

    bool IsLocked() const;

private:
    bool m_locked = false;
	RECT m_bounds{};
};