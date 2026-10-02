#pragma once

#include "ui/ConnectionWindow.h"

class IConnectionView {
public:
    virtual ~IConnectionView() = default;

    virtual void setUrlPrefix(std::string urlPrefix) = 0;
    [[nodiscard]] virtual std::string getUrlInput() const = 0;
    virtual void setButtonLabel(std::string label);

    virtual void show() = 0;
    virtual void hide() = 0;
};

class ConnectionPresenter {
private:
    IConnectionView& connectionView;
public:
    const std::string URL_PREFIX = "http://";

    explicit ConnectionPresenter(IConnectionView& connectionView) : connectionView(connectionView) {}
    void onConnectButtonClicked() const;
};
