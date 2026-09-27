#include "Client.h"

Client::Client(const std::string &new_server_url) {
    Client::set_server_url(new_server_url);
}

std::string Client::get_server_url() { return server_url; }

void Client::set_server_url(const std::string &new_server_url) {
    server_url = new_server_url;
}