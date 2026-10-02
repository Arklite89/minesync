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
#include <FL/Fl_Box.H>

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
  Fl_Box *urlLabel;
  Fl_Choice *worldSelectChoice;
  Fl_Input *savesPathInput;
  Fl_Button *savesPathBrowseButton;
  Fl_Button *scoutDirectoryButton;
  Fl_Progress *statusProgress;
  Fl_Button *syncButton;
  Fl_Button *uploadButton;

  MainPresenter *mainPresenter;

public:
  MainWindow();
  ~MainWindow() override;

  void setPresenter(MainPresenter *presenter) { mainPresenter = presenter; }

  void setServerUrl(const std::string &url) override;
  void setWorldChoices(const std::vector<std::string> &worldNames) override;
  void setStatus(const std::string &message, StatusType type, float progress) override;
  [[nodiscard]] std::string getSavesPathInput() const override;
  void setSavesPathInput(const std::string &path) override;
  [[nodiscard]] int getSelectedWorldIndex() const override;

  void show() override { if (window) window->show(); };
  void hide() override { if (window) window->hide(); };
};
