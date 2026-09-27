#include "Client.h"

Client::Client(const std::string &new_server_url) {
    Client::setServerUrl(new_server_url);
}

std::string Client::getServerUrl() { return serverURL; }

bool Client::setServerUrl(const std::string &new_server_url) {
    serverURL = new_server_url;
    return true; // TODO add url validation
}