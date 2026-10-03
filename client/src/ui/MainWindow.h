#pragma once
#include <FL/Fl_Window.H>
#include <string>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Input.H>

#include <FL//Fl_Progress.H>
#include <vector>
#include <FL/Fl_Box.H>

#include "presenters/MainPresenter.h"

namespace UIConfig {
inline constexpr int WindowWidth = 400;
inline constexpr int WindowHeight = 500;
inline constexpr const char *WindowTitle = "Minesync";
} // namespace UIConfig

class IMainView {
public:
  enum class StatusType { Info, Success, Warning, Error};

  virtual ~IMainView() = default;
  virtual void setServerUrl(const std::string& url) = 0;
  virtual void setWorldChoices(const std::vector<std::string>& worldNames) = 0;
  virtual void setStatus(const std::string& message, StatusType type = StatusType::Info, float progress = 0.0f) = 0;
  [[nodiscard]] virtual std::string getSavesPathInput() const = 0;
  virtual void setSavesPathInput(const std::string& path) = 0;
  [[nodiscard]] virtual int getSelectedWorldIndex() const = 0;

  virtual void show() = 0;
  virtual void hide() = 0;
};

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
