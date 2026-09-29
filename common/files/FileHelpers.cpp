//
// Created by danya on 9/29/26.
//

#include "FileHelpers.h"

#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

std::vector<fs::path> getSubdirectories(const fs::path& directory) {
    std::vector<fs::path> directories;

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (fs::is_directory(entry))
            directories.push_back(entry);
    }

    return directories;
}
