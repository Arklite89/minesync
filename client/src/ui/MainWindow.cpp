#include "MainWindow.h"

#include <format>
#include <algorithm>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Flex.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Progress.H>

#include "lib/pfd/portable-file-dialogs.h"
#include "files/FileHelpers.h"

MainWindow::MainWindow(Client* client) : client(client) {
  window = new Fl_Window(
    UIConfig::WindowWidth,
    UIConfig::WindowHeight,
    UIConfig::WindowTitle);

  auto urlLabel = new Fl_Box(0, 10, UIConfig::WindowWidth, 20);
  urlLabel->copy_label(("Connected to: " + client->getServerUrl()).c_str());

  constexpr int WINDOW_QUARTER = UIConfig::WindowWidth / 4;

  auto worldSelectLabel = new Fl_Box(10, 50, WINDOW_QUARTER - 10, 20, "Select a world:");
  worldSelectChoice = new Fl_Choice(WINDOW_QUARTER + 10, 50, WINDOW_QUARTER * 3 - 20, 20);

  auto savesPathLabel = new Fl_Box(10, 80, WINDOW_QUARTER - 10, 20, "Path to saves: ");
  savesPathInput = new Fl_Input(WINDOW_QUARTER + 10, 80, (WINDOW_QUARTER - 10) *2, 20);
  savesPathBrowseButton = new Fl_Button(WINDOW_QUARTER * 3, 80, WINDOW_QUARTER - 10, 20, "Browse...");
  savesPathBrowseButton->callback(savesPathBrowseButtonPressed, this);

  scoutDirectoryButton = new Fl_Button(10, 110, UIConfig::WindowWidth - 20, 30, "Scout directory");
  scoutDirectoryButton->callback(scoutDirectoryButtonPressed, this);

  statusProgress = new Fl_Progress(10, UIConfig::WindowHeight - 200, UIConfig::WindowWidth - 20, 30, "Status");

  syncButton = new Fl_Button(10, UIConfig::WindowHeight - 160, UIConfig::WindowWidth - 20, 70, "Sync!");
  uploadButton = new Fl_Button(10, UIConfig::WindowHeight - 80, UIConfig::WindowWidth - 20, 70, "Upload!");

  window->end();
};

MainWindow::~MainWindow() {
  delete window;
}

void MainWindow::show() const {
  if (window) {
    window->show();
  }
}

void MainWindow::savesPathBrowseButtonPressed(Fl_Widget* widget, void* data) {
  auto& self = *static_cast<MainWindow*>(data);
  auto selection = pfd::select_folder("Select your save file", "." ).result();

  if (!selection.empty()) {
    self.savesPathInput->value(selection.c_str());
  }
}


void MainWindow::updateStatus(const StatusMessage& message) { // NOLINT(readability-make-member-function-const)
  statusProgress->value(message.progress);
  statusProgress->copy_label(message.message.c_str());

  using Type = StatusMessage::Type;
  statusProgress->color(message.type == Type::Error   ? FL_RED :
                        message.type == Type::Warning ? FL_YELLOW : FL_BLUE);
}

void MainWindow::scoutDirectoryButtonPressed(Fl_Widget* widget, void* data) {
  auto& self = *static_cast<MainWindow*>(data);

  fs::path savesDirectory = self.savesPathInput->value();
  if (!fs::exists(savesDirectory))
    return self.updateStatus(StatusMessage{"Path invalid.", 0.0f, StatusMessage::Type::Error});

  if (!fs::is_directory(savesDirectory))
    return self.updateStatus(StatusMessage{"Selected path is not a directory.", 0.0f, StatusMessage::Type::Error});


  std::vector<fs::path> directories = FileHelpers::getSubdirectories(savesDirectory);

  directories.erase(
    std::remove_if(directories.begin(), directories.end(), [](const fs::path& directory) {
      return !FileHelpers::isSaveFolder(directory);
    })
    , directories.end()
    );

  auto worldCount = directories.size();
  self.updateStatus(StatusMessage("Scouted " + std::to_string(worldCount) + " world" + (worldCount == 1 ? "." : "s.")));

  for (auto directory: directories) {
    self.worldSelectChoice->add(directory.filename().c_str());
  }
}
