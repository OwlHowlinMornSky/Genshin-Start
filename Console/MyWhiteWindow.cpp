/*
*                          Apache License
*                    Version 2.0, January 2004
* 
*   Copyright (c) 2023  Tyler Parret True
*     Tyler Parret True (OwlHowlinMornSky) <mysteryworldgod@outlook.com>
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
*/
#include "MyWhiteWindow.h"

namespace {

LRESULT CALLBACK MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static size_t cnt = 0;

	switch (message) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 100, NULL);
		cnt = 0;
		break;
	//case WM_PAINT:
	//{
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(hWnd, &ps);
	//	EndPaint(hWnd, &ps);
	//	break;
	//}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			++cnt;
			SetFocus(hWnd);
			if (cnt >= 200 || FindWindowW(L"UnityWndClass", L"原神") != NULL) {
				KillTimer(hWnd, 1);
				SetTimer(hWnd, 2, 5000, NULL);
				SetForegroundWindow(FindWindowW(L"UnityWndClass", L"原神"));
			}
			else {
				SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				SetForegroundWindow(hWnd);
			}
			break;
		case 2:
			SetForegroundWindow(FindWindowW(L"UnityWndClass", L"原神"));
			KillTimer(hWnd, 2);
			PostMessageW(hWnd, WM_CLOSE, NULL, NULL);
			break;
		default:
			return DefWindowProcW(hWnd, message, wParam, lParam);
		}
		break;
	default:
		return DefWindowProcW(hWnd, message, wParam, lParam);
	}
	return 0;
}

} // namespace


namespace ohms::genshinStart {

bool MyRegisterClass() {
	WNDCLASSW wc = { 0 };
	wc.lpszClassName = L"OHMS_GS_MAIN";
	wc.lpfnWndProc = MyWndProc;
	wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	wc.hInstance = NULL;
	wc.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
	RegisterClass(&wc);
	return true;
}

HWND MyCreateWindow() {
	HWND hwnd = CreateWindowExW(NULL,
								L"OHMS_GS_MAIN",
								L"",
								WS_POPUP,
								0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
								NULL, NULL, NULL, NULL);
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	return hwnd;
}

} // namespace ohms::genshinStart
