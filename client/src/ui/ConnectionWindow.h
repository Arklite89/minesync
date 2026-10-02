#pragma once
#include <string>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Window.H>

#include "presenters/ConnectionPresenter.h"

class ConnectionWindow : IConnectionView {
private:
    Fl_Window *window;
    Fl_Box *urlPrefix;
    Fl_Input* connectionInput;
    Fl_Button* connectButton;

    ConnectionPresenter *connectionPresenter;

public:
    ConnectionWindow();
    ~ConnectionWindow() override;

    void setPresenter(ConnectionPresenter *presenter) { connectionPresenter = presenter; }

    void setUrlPrefix(std::string label) override;
    [[nodiscard]] std::string getUrlInput() const override;
    void setButtonLabel(std::string label) override;

    void show() override { if (window) window->show(); };
    void hide() override { if (window) window->hide(); };
};
