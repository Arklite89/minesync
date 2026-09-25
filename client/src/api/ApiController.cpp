#include "ApiController.h"
#include "client/Client.h"

ApiController::ApiController(Client *client) {
    this->client = client;
}

cpr::Response ApiController::upload_save(cpr::File file) const {
    return cpr::Post(
        cpr::Url{client->get_server_url()},
        cpr::Multipart{
        {"file", file}
    });
}
