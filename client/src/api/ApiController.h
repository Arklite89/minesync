#pragma once
#include "client/Client.h"
#include <cpr/cpr.h>

#include "data/World.h"

namespace  ApiController {
    [[nodiscard]] cpr::Response uploadSave(Client* client, cpr::File file);
    [[nodiscard]] cpr::Response syncSave(Client* client, const World& world);
    bool isServerReachable(const std::string& host);
};
