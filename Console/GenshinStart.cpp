#include "GenshinStart.h"

#include <iostream>

#define WIN32_LEAN_AND_MEAN TRUE
#include <Windows.h>

#include "MyWhiteWindow.h"


namespace ohms::genshinStart {

bool YuanShen_QiDong(std::filesystem::path path) {
	HWND myWhiteWnd = ohms::genshinStart::MyCreateWindow();

	STARTUPINFOW si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);

	BOOL res;
	res = CreateProcessW(
		(path / "YuanShen.exe").c_str(),
		NULL,
		NULL,
		NULL,
		FALSE,
		NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_NEW_PROCESS_GROUP,
		NULL,
		path.c_str(),
		&si,
		&pi);

	if (!res) {
		printf("CreateProcess failed (%d).\n", GetLastError());
		return false;
	}

	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return true;
}

} // namespace ohms::genshinStart
