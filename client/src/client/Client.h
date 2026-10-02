#pragma once

#include <optional>
#import <string>
#include <vector>

#include "cpr/filesystem.h"
#include "data/World.h"

namespace fs = std::filesystem;

class Client {
private:
    explicit Client(std::string serverUrl);

    std::string serverURL;


public:
    std::vector<World> worlds;

    std::string getServerUrl();
    bool setServerUrl(const std::string& newServerUrl);

    static std::unique_ptr<Client> create(const std::string &newServerUrl);
    [[nodiscard]] bool canConnect() const;
};