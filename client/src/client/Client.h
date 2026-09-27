#pragma once

#include <optional>
#import <string>

#include "cpr/filesystem.h"

namespace fs = std::filesystem;

class Client {
private:
    explicit Client(std::string serverUrl);

    std::string serverURL;

public:
    static std::unique_ptr<Client> create(const std::string &newServerUrl);

    std::string getServerUrl();
    bool setServerUrl(const std::string& newServerUrl);

    [[nodiscard]] bool canConnect() const;
    bool sendSaveToServer(const fs::path& savePath);
};