#pragma once
#include "client/Client.h"
#include <cpr/cpr.h>

namespace  ApiController {
    [[nodiscard]] cpr::Response uploadSave(Client* client, cpr::File file);
};
