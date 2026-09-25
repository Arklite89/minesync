#include "MainWindow.h"

MainWindow::MainWindow() {
  window = new Fl_Window(UIConfig::WindowWidth, UIConfig::WindowHeight,
                         UIConfig::WindowTitle);
  window->end();
};

void MainWindow::show() {
  if (window) {
    window->show();
  }
}
