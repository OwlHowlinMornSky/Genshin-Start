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
