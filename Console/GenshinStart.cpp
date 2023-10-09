/*
*   Genshin, Start!
*
*   Copyright 2023 Tyler Parret True
*
*   Licensed under the Apache License, Version 2.0 (the "License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
*
*       http://www.apache.org/licenses/LICENSE-2.0
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
*
* @Authors
*   Tyler Parret True <mysteryworldgod@outlook.com><https://github.com/OwlHowlinMornSky>
*/
#include "GenshinStart.h"

#include <iostream>

#define WIN32_LEAN_AND_MEAN TRUE
#include <Windows.h>

#include "MyWhiteWindow.h"


namespace ohms::genshinStart {

bool YuanShen_QiDong(std::filesystem::path path, std::filesystem::path name) {
	if (!std::filesystem::is_regular_file(path / name)) {
		return false;
	}

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
