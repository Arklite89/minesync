#pragma once
#include <string>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Window.H>

class ConnectionWindow {
private:
    const std::string URL_PREFIX = "http://";

    Fl_Window *window;
    Fl_Input* connectionInput;
    Fl_Button* connectButton;

public:
    ConnectionWindow();
    ~ConnectionWindow();
    void show() const;
    static void connectButtonPressed(Fl_Widget* widget, void* data);
};
