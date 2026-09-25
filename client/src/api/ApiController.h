#pragma once
#include "client/Client.h"
#include <cpr/cpr.h>

class ApiController {
private:
    Client *client;
public:
    explicit ApiController(Client *client);
    [[nodiscard]] cpr::Response upload_save(cpr::File file) const;
};
