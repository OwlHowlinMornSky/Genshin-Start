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
*    Tyler Parret True <mysteryworldgod@outlook.com><https://github.com/OwlHowlinMornSky>
*/
#include "GetGamePath.h"

#include <string>

#include <iostream>
#include <fstream>

namespace ohms::genshinStart {

bool ohms::genshinStart::GetGamePath_Config(const std::filesystem::path& installPath, std::filesystem::path& out_path, std::filesystem::path& out_name) {
	std::ifstream ifs;
	ifs.open(installPath / "config.ini");
	std::string str;
	std::getline(ifs, str);
	if (str != "[launcher]") {
		return 1;
	}
	bool gotPath = false;
	bool gotName = false;
	while (std::getline(ifs, str)) {
		if (str.find("game_install_path") != std::string::npos) {
			size_t pos = str.find_first_of("=");
			if (pos == std::string::npos) {
				return false;
			}
			out_path = str.substr(pos + 1);
			if (!std::filesystem::is_directory(out_path)) {
				std::cout << "Error: Game path is invalid." << std::endl;
				return false;
			}
			gotPath = true;
		}
		else if (str.find("game_start_name") != std::string::npos) {
			size_t pos = str.find_first_of("=");
			if (pos == std::string::npos) {
				return false;
			}
			out_name = str.substr(pos + 1);
			gotName = true;
		}
		if(gotName && gotPath)
			return true;
	}
    return false;
}

} // namespace ohms::genshinStart
