#include "ApiController.h"
#include "client/Client.h"

cpr::Response ApiController::uploadSave(Client* client, cpr::File file) {
    return cpr::Post(
        cpr::Url{client->getServerUrl()},
        cpr::Multipart{
        {"file", file}
    });
}

bool ApiController::isServerReachable(const std::string& host) {
#if defined(_WIN32)
    const std::string command = "ping -n 1 -w 1000" + host + " > nul 2>&1";
#else
    const std::string command = "ping -c 1 -W 1 " + host + " > /dev/null 2>&1";
#endif

    const int result = std::system(command.c_str());
    return result == 0;
}