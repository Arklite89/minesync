#pragma once
#include "client/Client.h"
#include <cpr/cpr.h>

#include "data/World.h"

namespace  ApiController {
    [[nodiscard]] cpr::Response uploadSave(Client* client, cpr::File file);
    [[nodiscard]] cpr::Response getSave(Client* client, const World& world, const fs::path& output);
    bool isServerReachable(const std::string& host);
};
