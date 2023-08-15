#include "GetGamePath.h"

#include <string>

#include <iostream>
#include <fstream>

namespace ohms::genshinStart {

bool ohms::genshinStart::GetGamePath_Config(const std::filesystem::path& installPath, std::filesystem::path& out_path) {
	std::ifstream ifs;
	ifs.open(installPath / "config.ini");
	std::string str;
	std::getline(ifs, str);
	if (str != "[launcher]") {
		return 1;
	}
	while (std::getline(ifs, str)) {
		if (str.find("game_install_path") == std::string::npos)
			continue;
		size_t pos = str.find_first_of("=");
		if (pos == std::string::npos) {
			return false;
		}
		out_path = str.substr(pos + 1);
		if (!std::filesystem::is_directory(out_path)) {
			std::cout << "Error: Game path is invalid." << std::endl;
			return false;
		}
		return true;
	}
    return false;
}

} // namespace ohms::genshinStart
