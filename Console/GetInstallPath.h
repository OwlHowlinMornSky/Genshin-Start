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
#pragma once

#include <filesystem>

namespace ohms::genshinStart {

bool GetInstallPath_Registry(std::filesystem::path& out_path);

} // namespace ohms::genshinStart
