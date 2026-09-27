#include "client/src/ui/MainWindow.h"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>

#include "client/src/ui/ConnectionWindow.h"


int main(int argc, char **argv) {
  ConnectionWindow app;
  app.show();
  return Fl::run();
}
