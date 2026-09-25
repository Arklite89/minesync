

#include "ConnectionWindow.h"

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>

ConnectionWindow::ConnectionWindow() {
    window = new Fl_Window(640, 120, "Specify a Connection");

    Fl_Box *title = new Fl_Box(20, 0, 600, 50, "Enter the root url of your minesync server: (e.g. 192.168.0.1:1234)");
    Fl_Box *prefix = new Fl_Box(20, 50, 40, 20, "http://");
    Fl_Input *input = new Fl_Input(65, 50, 555, 20);
    Fl_Button *connect_button = new Fl_Button(20, 80, 600, 20, "Connect");

    window->end();
}

void ConnectionWindow::show() {
    if (window) {
        window->show();
    }
}
