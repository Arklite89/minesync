#pragma once

#include "ui/ConnectionWindow.h"

class ConnectionPresenter {
private:
    IConnectionView& connectionView;
public:
    const std::string URL_PREFIX = "http://";

    ConnectionPresenter(IConnectionView& connectionView) : connectionView(connectionView) {}
    void onConnectButtonClicked() const;
};
