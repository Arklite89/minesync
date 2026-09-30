//
// Created by danya on 9/30/26.
//

#include "WorldHandler.h"

#include "files/FileHelpers.h"

std::vector<World> WorldHandler::scoutDirectory(const fs::path &savesDir) {
    if (!fs::exists(savesDir) || !fs::is_directory(savesDir))
        throw std::invalid_argument("Invalid saves directory.");

    std::vector<fs::path> directories = FileHelpers::getSubdirectories(savesDir);
    FileHelpers::filterToJustWorlds(directories);

    return FileHelpers::getWorldsFromDirectories(directories);
};
