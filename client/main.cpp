#include "src/ui/MainWindow.h"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>

#include "src/ui/ConnectionWindow.h"


int main(int argc, char **argv) {
  auto client = Client::create("localhost");

  if (!client) { return 1; }

  MainWindow app(client.release());
  app.show();
  return Fl::run();
}
