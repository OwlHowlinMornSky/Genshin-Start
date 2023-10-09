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
#include "GetInstallPath.h"

#include <iostream>

#define WIN32_LEAN_AND_MEAN TRUE
#include <Windows.h>
#include <winreg.h>

namespace ohms::genshinStart {

bool GetInstallPath_Registry(std::filesystem::path& out_path) {
	DWORD type = REG_SZ;
	wchar_t data[256] = { 0 };
	DWORD dataSize = sizeof(data);
	LSTATUS res = RegGetValueW(HKEY_LOCAL_MACHINE,
							   L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Ô­Éñ",
							   L"InstallPath",
							   RRF_RT_REG_SZ, &type,
							   (LPBYTE)&data, &dataSize);
	if (res == ERROR_SUCCESS) {
		out_path = data;
	}
	else {
		switch (res) {
		case ERROR_MORE_DATA:
			std::cout << "Error: The install path is too long to catch." << std::endl;
			break;
		case ERROR_FILE_NOT_FOUND:
			std::cout << "Error: The registry value is not found." << std::endl;
			break;
		case ERROR_INVALID_PARAMETER:
			std::cout << "Error: Unable to read the registry value." << std::endl;
			break;
		default:
			std::cout << "Error: Registry error." << std::endl;
			break;
		}
		return false;
	}
	if (!std::filesystem::is_directory(out_path)) {
		std::cout << "Error: Install path is invalid." << std::endl;
		return false;
	}
	return true;
}

} // namespace ohms::genshinStart
