#pragma once
#include <filesystem>
#include <vector>

#include "data/World.h"

namespace fs = std::filesystem;

namespace WorldHandler {
    std::vector<World> scoutDirectory(const fs::path& savesDir);
    bool uploadWorld(const World& world);
    bool syncWorld(const World& world);
}
