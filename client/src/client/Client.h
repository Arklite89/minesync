#pragma once

#import <string>

#include "cpr/filesystem.h"

namespace fs = std::filesystem;

class Client {
private:
    std::string serverURL;

public:
    explicit Client(const std::string& newServerUrl);

    std::string getServerUrl();
    bool setServerUrl(const std::string& newServerUrl);

    bool sendSaveToServer(const fs::path& savePath);
};