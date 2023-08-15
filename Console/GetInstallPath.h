#pragma once

#include <filesystem>

namespace ohms::genshinStart {

bool GetInstallPath_Registry(std::filesystem::path& out_path);

} // namespace ohms::genshinStart
