#include "ApiController.h"
#include "client/Client.h"

cpr::Response ApiController::uploadSave(Client* client, cpr::File file) {
    return cpr::Post(
        cpr::Url{client->getServerUrl()},
        cpr::Multipart{
        {"file", file}
    });
}
