#include "MainWindow.h"

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Flex.H>

MainWindow::MainWindow(Client* client) {
  window = new Fl_Window(
    UIConfig::WindowWidth,
    UIConfig::WindowHeight,
    UIConfig::WindowTitle);

  auto *root = new Fl_Flex(0, 0, window->w(), window->h(), Fl_Flex::VERTICAL);

  root->end();

  window->end();
};

void MainWindow::show() {
  if (window) {
    window->show();
  }
}
