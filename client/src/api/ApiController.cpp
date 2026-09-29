#include "ApiController.h"

#include <regex>

#include "client/Client.h"

cpr::Response ApiController::uploadSave(Client* client, cpr::File file) {
    return cpr::Post(
        cpr::Url{client->getServerUrl() + "/upload"},
        cpr::Multipart{
        {"file", file}
    });
}

std::string extractHostname(const std::string& url) {
    std::regex re(R"(^(?:https?://)?([^:/]+))");
    std::smatch match;
    if (std::regex_search(url, match, re) && match.size() > 1) {
        return match[1].str();
    }
    return url;
}

bool ApiController::isServerReachable(const std::string& hostOrUrl) {
    const std::string host = extractHostname(hostOrUrl);

#if defined(_WIN32)
    const std::string command = "ping -n 1 -w 1000 " + host + " > nul 2>&1";
#else
    const std::string command = "ping -c 1 -W 1 " + host + " > /dev/null 2>&1";
#endif

    return std::system(command.c_str()) == 0;
}