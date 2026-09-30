#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <string>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Input.H>

#include "client/Client.h"
#include <FL//Fl_Progress.H>
#include <utility>
#include <vector>

#include "data/World.h"
#include "presenters/MainPresenter.h"

namespace UIConfig {
inline constexpr int WindowWidth = 400;
inline constexpr int WindowHeight = 500;
inline constexpr const char *WindowTitle = "Minesync";
} // namespace UIConfig

class MainWindow : public IMainView {
private:
  Fl_Window *window;
  Fl_Choice *worldSelectChoice;
  Fl_Input *savesPathInput;
  Fl_Button *savesPathBrowseButton;
  Fl_Button *scoutDirectoryButton;
  Fl_Progress *statusProgress;
  Fl_Button *syncButton;
  Fl_Button *uploadButton;

  MainPresenter *mainPresenter;

  Client* client;

  static void savesPathBrowseButtonPressed(Fl_Widget* widget, void* data);
  static void scoutDirectoryButtonPressed(Fl_Widget* widget, void* data);
  static void uploadButtonPressed(Fl_Widget* widget, void* data);
  static void syncButtonPressed(Fl_Widget* widget, void* data);

  void updateStatus(const std::string& message, StatusType type = StatusType::Info, float progress = 0.0f);

  void updateWorlds(const std::vector<World>& worlds);
  void updateWorldSelectChoices();

  [[nodiscard]] const World* getSelectedWorld() const;

public:
  explicit MainWindow(Client* client);
  ~MainWindow();
  MainWindow() = delete;

  void show() const;
};
