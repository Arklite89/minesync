#pragma once
#include <string>

class IConnectionView;

class ConnectionPresenter {
private:
    IConnectionView& connectionView;
public:
    const std::string URL_PREFIX = "http://";

    explicit ConnectionPresenter(IConnectionView& connectionView) : connectionView(connectionView) {}
    void onConnectButtonClicked() const;
};
