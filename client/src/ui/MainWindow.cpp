#include "MainWindow.h"

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Flex.H>
#include <FL/Fl_Input.H>

MainWindow::MainWindow(Client* client) {
  window = new Fl_Window(
    UIConfig::WindowWidth,
    UIConfig::WindowHeight,
    UIConfig::WindowTitle);

  auto urlLabel = new Fl_Box(0, 10, UIConfig::WindowWidth, 20);
  urlLabel->copy_label(("Connected to: " + client->getServerUrl()).c_str());

  constexpr int WINDOW_QUARTER = UIConfig::WindowWidth / 4;

  auto worldSelectLabel = new Fl_Box(10, 50, WINDOW_QUARTER - 10, 20, "Select a world:");
  auto worldSelectChoice = new Fl_Choice(WINDOW_QUARTER + 10, 50, WINDOW_QUARTER * 3 - 20, 20);

  auto savesPathLabel = new Fl_Box(10, 80, WINDOW_QUARTER - 10, 20, "Path to saves: ");
  auto savesPathInput = new Fl_Input(WINDOW_QUARTER + 10, 80, (WINDOW_QUARTER - 10) *2, 20);
  auto savesPathBrowse = new Fl_Button(WINDOW_QUARTER * 3, 80, WINDOW_QUARTER - 10, 20, "Browse...");

  auto syncButton = new Fl_Button(10, UIConfig::WindowHeight - 160, UIConfig::WindowWidth - 20, 70, "Sync!");
  auto uploadButton = new Fl_Button(10, UIConfig::WindowHeight - 80, UIConfig::WindowWidth - 20, 70, "Upload!");

  window->end();
};

void MainWindow::show() {
  if (window) {
    window->show();
  }
}
