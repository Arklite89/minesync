#include "ApiController.h"
#include "client/Client.h"

ApiController::ApiController(Client *client) {
    this->client = client;
}

cpr::Response ApiController::upload_save(cpr::File file) const {
    return cpr::Post(
        cpr::Url{client->getServerUrl()},
        cpr::Multipart{
        {"file", file}
    });
}
