#pragma once
#include <filesystem>
#include <vector>

#include "client/Client.h"
#include "data/World.h"

namespace fs = std::filesystem;

class WorldService {
private:
    Client* client;
public:
    explicit WorldService(Client* client) : client(client) {}

    std::vector<World> scoutDirectory(const fs::path& savesDir);
    bool uploadWorld(const World& world);
    bool syncWorld(const World& world);
};
