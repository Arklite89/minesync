#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <string>

#include "client/Client.h"

namespace UIConfig {
inline constexpr int WindowWidth = 400;
inline constexpr int WindowHeight = 500;
inline constexpr const char *WindowTitle = "Minesync";
} // namespace UIConfig

class MainWindow {
private:
  Fl_Window *window;
  Client* client;

public:
  explicit MainWindow(Client* client);
  MainWindow() = delete;

  void show();
};
