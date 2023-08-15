#pragma once

#define WIN32_LEAN_AND_MEAN TRUE
#include <Windows.h>

namespace ohms::genshinStart {

bool MyRegisterClass();

HWND MyCreateWindow();

} // namespace ohms::genshinStart
