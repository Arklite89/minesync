
#include "ConnectionPresenter.h"

#include "client/Client.h"


void ConnectionPresenter::onConnectButtonClicked() const {
    const std::string connectionString = URL_PREFIX + connectionView.getUrlInput();

    connectionView.setButtonLabel("Connecting to " + connectionString + "  ...");

    auto client = Client::create(connectionString);

    if (!client) {
        connectionView.setButtonLabel("Failed to connect to server.");
        return;
    }
}
