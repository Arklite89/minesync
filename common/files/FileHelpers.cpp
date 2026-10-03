#include "FileHelpers.h"

#include <algorithm>
#include <vector>
#include <filesystem>

#include "data/World.h"

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

void FileHelpers::filterToJustWorlds(std::vector<fs::path>& directories) {
    directories.erase(
    std::remove_if(directories.begin(), directories.end(), [](const fs::path& directory) {
      return !isSaveFolder(directory);
    })
    , directories.end()
    );
}

std::vector<World> FileHelpers::getWorldsFromDirectories(const std::vector<fs::path>& directories) {
    std::vector<World> newWorlds;

    for (const auto& directory: directories) {
        newWorlds.emplace_back(directory);
    }

    return newWorlds;
}