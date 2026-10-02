#pragma once
#include <string>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Window.H>

class ConnectionPresenter;

class IConnectionView {
public:
    virtual ~IConnectionView() = default;

    virtual void setUrlPrefix(std::string urlPrefix) = 0;
    [[nodiscard]] virtual std::string getUrlInput() const = 0;
    virtual void setButtonLabel(std::string label) = 0;

    virtual void show() = 0;
    virtual void hide() = 0;
};

class ConnectionWindow : public IConnectionView {
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
