//
// Created by danya on 9/29/26.
//

#include "FileHelpers.h"

#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

std::vector<fs::path> FileHelpers::getSubdirectories(const fs::path& directory) {
    std::vector<fs::path> directories;

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (fs::is_directory(entry))
            directories.push_back(entry);
    }

    return directories;
}

bool FileHelpers::isSaveFolder(const fs::path& directory) {
    if (!fs::is_directory(directory)) return false;
    if (!fs::exists(directory / "data")) return false;
    if (!fs::exists(directory / "level.dat")) return false;
    if (!fs::exists(directory / "playerdata")) return false;

    return true;
}