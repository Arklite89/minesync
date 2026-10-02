#pragma once
#include <functional>
#include <memory>
#include <string>

#include "ui/ConnectionWindow.h"

class Client;
class IConnectionView;

class ConnectionPresenter {
private:
    IConnectionView& connectionView;
    std::function<void(std::unique_ptr<Client>)> onConnected;
public:
    const std::string URL_PREFIX = "http://";

    explicit ConnectionPresenter(IConnectionView& connectionView, std::function<void(std::unique_ptr<Client>)> onConnected) : connectionView(connectionView), onConnected(std::move(onConnected)) {
        connectionView.setUrlPrefix(URL_PREFIX);
    }
    void onConnectButtonClicked() const;
};
