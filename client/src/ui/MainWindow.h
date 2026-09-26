#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <string>

namespace UIConfig {
inline constexpr int WindowWidth = 400;
inline constexpr int WindowHeight = 500;
inline constexpr const char *WindowTitle = "Minesync";
} // namespace UIConfig

class MainWindow {
private:
  Fl_Window *window;

public:
  MainWindow();
  void show();
};
