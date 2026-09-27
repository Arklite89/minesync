#include "Client.h"

#include <iostream>

#include "api/ApiController.h"
#include "files/CacheHandler.h"

Client::Client(const std::string &newServerUrl) {
    Client::setServerUrl(newServerUrl);
}

std::string Client::getServerUrl() { return serverURL; }

bool Client::setServerUrl(const std::string &newServerUrl) {
    serverURL = newServerUrl;
    return true; // TODO add url validation
}

bool Client::sendSaveToServer(const fs::path& savePath) {
    if (!CacheHandler::cacheSaveToZip(savePath)) {
        std::cerr << "Failed to cache save to zip." << std::endl;
        return false;
    }

    const fs::path cachedSavePath = CacheHandler::getLatestCachedSaveZip();

    if (cachedSavePath.empty()) {
        std::cerr << "Failed to get cache save path." << std::endl;
    }

    const cpr::File cachedSaveFile{cachedSavePath.string()};

    cpr::Response res = ApiController::uploadSave(this, cachedSaveFile);

    if (res.status_code != 200) {
        std::cerr << "Error uploading file: " << res.status_code << res.error.message << std::endl;
        return false;
    }

    return true;
}