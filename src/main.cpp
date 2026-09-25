#include "ui/MainWindow.h"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>

int main(int argc, char **argv) {
  MainWindow app;
  app.show();
  return Fl::run();
}
