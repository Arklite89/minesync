#include "Client.h"

#include <iostream>

#include "api/ApiController.h"
#include "../../common/files/CacheHandler.h"

Client::Client(std::string serverUrl) : serverURL(std::move(serverUrl)) {}

std::unique_ptr<Client> Client::create(const std::string& newServerUrl) {
    if (!ApiController::isServerReachable(newServerUrl)) {
        std::cerr << "Failed to reach server: " << newServerUrl << std::endl;
        return nullptr;
    }

    return std::unique_ptr<Client>(new Client(newServerUrl));
}

std::string Client::getServerUrl() { return serverURL; }

bool Client::canConnect() const {
    return ApiController::isServerReachable(Client::serverURL);
}

bool Client::setServerUrl(const std::string &newServerUrl) {
    const bool urlReachable = ApiController::isServerReachable(newServerUrl);

    if (urlReachable) {
        serverURL = newServerUrl;
        return true;
    }

    return false;
}

// bool Client::sendSaveToServer(const fs::path& savePath) {
//     if (!CacheHandler::cacheWorldToZip(savePath)) {
//         std::cerr << "Failed to cache save to zip." << std::endl;
//         return false;
//     }
//
//     const fs::path cachedSavePath = CacheHandler::getLatestCachedSaveZip();
//
//     if (cachedSavePath.empty()) {
//         std::cerr << "Failed to get cache save path." << std::endl;
//     }
//
//     const cpr::File cachedSaveFile{cachedSavePath.string()};
//
//     cpr::Response res = ApiController::uploadSave(this, cachedSaveFile);
//
//     if (res.status_code != 200) {
//         std::cerr << "Error uploading file: " << res.status_code << res.error.message << std::endl;
//         return false;
//     }
//
//     return true;
// }