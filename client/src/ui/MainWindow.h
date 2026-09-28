#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <string>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Input.H>

#include "client/Client.h"

namespace UIConfig {
inline constexpr int WindowWidth = 400;
inline constexpr int WindowHeight = 500;
inline constexpr const char *WindowTitle = "Minesync";
} // namespace UIConfig

class MainWindow {
private:
  Fl_Window *window;
  Fl_Choice *worldSelectChoice;
  Fl_Input *savesPathInput;
  Fl_Button *savesPathBrowseButton;
  Fl_Button *scoutDirectoryButton;
  Fl_Button *syncButton;
  Fl_Button *uploadButton;

  Client* client;

  static void savesPathBrowseButtonPressed(Fl_Widget* widget, void* data);


public:
  explicit MainWindow(Client* client);
  ~MainWindow();
  MainWindow() = delete;

  void show() const;
};
