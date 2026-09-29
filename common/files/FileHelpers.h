//
// Created by danya on 9/29/26.
//

#pragma once

#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

namespace FileHelpers {
    std::vector<fs::path> getSubdirectories(const fs::path& path);
    bool isSaveFolder(const fs::path& directory);
    void filterToJustWorlds(std::vector<fs::path>& directories);
}
