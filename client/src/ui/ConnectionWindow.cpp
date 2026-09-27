

#include "ConnectionWindow.h"

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>

#include "MainWindow.h"

ConnectionWindow::ConnectionWindow() {
    window = new Fl_Window(640, 120, "Specify a Connection");

    Fl_Box *title = new Fl_Box(20, 0, 600, 50, "Enter the root url of your minesync server: (e.g. 192.168.0.1:1234)");
    Fl_Box *prefix = new Fl_Box(20, 50, 40, 20, ConnectionWindow::URL_PREFIX.c_str());
    connectionInput = new Fl_Input(65, 50, 555, 20);
    connectButton = new Fl_Button(20, 80, 600, 20, "Connect");
    connectButton->callback(connectButtonPressed, this);

    window->end();
}

ConnectionWindow::~ConnectionWindow() {
    delete window;
}

void ConnectionWindow::show() const {
    if (window) {
        window->show();
    }
}

void ConnectionWindow::connectButtonPressed(Fl_Widget* widget, void* data) {
    auto* self = static_cast<ConnectionWindow*>(data);

    std::string connectionString = self->URL_PREFIX + self->connectionInput->value();

    auto client = Client::create(self->connectionInput->value());

    if (!client) {
        self->connectButton->label("Failed to connect to server.");
        self->connectButton->labelcolor(FL_RED);
        return;
    }

    MainWindow* redirect = new MainWindow(client.release());
    redirect->show();
    Fl::delete_widget(self->window);
}