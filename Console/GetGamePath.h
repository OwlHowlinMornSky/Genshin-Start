#pragma once

#include <filesystem>

namespace ohms::genshinStart {

bool GetGamePath_Config(const std::filesystem::path& installPath, std::filesystem::path& out_path);

} // namespace ohms::genshinStart
