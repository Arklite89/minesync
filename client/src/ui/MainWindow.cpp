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

#include "api/ApiController.h"
#include "files/CacheHandler.h"
#include "lib/pfd/portable-file-dialogs.h"
#include "files/FileHelpers.h"
#include "handlers/WorldHandler.h"
#include "zip/ZipUtils.h"

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

  uploadButton->callback(uploadButtonPressed, this);
  syncButton->callback(syncButtonPressed, this);

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
                        message.type == Type::Warning ? FL_YELLOW :
                        message.type == Type::Success ? FL_GREEN : FL_BLUE);
  statusProgress->redraw();
  Fl::check();
}

void MainWindow::scoutDirectoryButtonPressed(Fl_Widget* widget, void* data) {
  auto& self = *static_cast<MainWindow*>(data);

  fs::path savesDirectory = self.savesPathInput->value();
  if (!fs::exists(savesDirectory))
    return self.updateStatus(StatusMessage{"Path invalid.", 0.0f, StatusMessage::Type::Error});

  if (!fs::is_directory(savesDirectory))
    return self.updateStatus(StatusMessage{"Selected path is not a directory.", 0.0f, StatusMessage::Type::Error});

  std::vector<World> scoutedWorlds = WorldHandler::scoutDirectory(savesDirectory);
  self.updateWorlds(scoutedWorlds);

  const auto worldCount = scoutedWorlds.size();
  if (worldCount > 0)
    self.updateStatus(StatusMessage("Scouted " + std::to_string(worldCount) + " world" + (worldCount == 1 ? "." : "s.")));
  else
    self.updateStatus(StatusMessage("Didn't find any worlds!", 0.0f, StatusMessage::Type::Warning));
}

void MainWindow::updateWorlds(const std::vector<World>& worlds) {
  client->worlds = worlds;
  updateWorldSelectChoices();
}

void MainWindow::updateWorldSelectChoices() { // NOLINT(readability-make-member-function-const)
  worldSelectChoice->clear();
  for (const auto& world : client->worlds ) {
    worldSelectChoice->add(world.name.c_str());
  }
}

const World* MainWindow::getSelectedWorld() const {
  const char* selectedText = worldSelectChoice->text();
  if (!selectedText) return nullptr;

  std::string selectedName(selectedText);
  const std::vector<World>& worlds = client->worlds;

  auto selectedWorld = std::find_if(worlds.begin(), worlds.end(), [&](const World& world) {
        return world.name == selectedName;
    });

  return (selectedWorld != worlds.end()) ? &*selectedWorld : nullptr;
}

void MainWindow::uploadButtonPressed(Fl_Widget* widget, void* data) {
  auto& self = *static_cast<MainWindow*>(data);

  auto selectedWorld = self.getSelectedWorld();

  if (selectedWorld == nullptr) {
    self.updateStatus(StatusMessage("No valid world selected!", 0.0f, StatusMessage::Type::Error));
    return;
  }

  self.updateStatus(StatusMessage("Zipping save file...", 0.3f, StatusMessage::Type::Info));

  CacheHandler::cacheWorldToZip(*selectedWorld);
  fs::path zip = CacheHandler::getLatestCachedSaveZip();

  self.updateStatus(StatusMessage("Uploading save file...", 0.6f, StatusMessage::Type::Info));

  cpr::Response res = ApiController::uploadSave(self.client, cpr::File(zip));
  if (res.status_code == 200) {
    self.updateStatus(StatusMessage("Save uploaded!", 0.0f, StatusMessage::Type::Success));
  }
  else {
    self.updateStatus(StatusMessage("There was an error.", 0.0f, StatusMessage::Type::Error));
  }
}

void MainWindow::syncButtonPressed(Fl_Widget* widget, void* data) {
  auto& self = *static_cast<MainWindow*>(data);
  auto selectedWorld = self.getSelectedWorld();

  if (selectedWorld == nullptr) {
    self.updateStatus(StatusMessage("No valid world selected!", 0.0f, StatusMessage::Type::Error));
  }

  self.updateStatus(StatusMessage("Fetching...", 0.3f, StatusMessage::Type::Info));

  const fs::path zipPath = CacheHandler::getAppCacheDir() / "sync.tmp.zip";
  cpr::Response res = ApiController::getSave(self.client, *selectedWorld, zipPath);

  if (res.status_code != 200) {
    self.updateStatus(StatusMessage("There was an error.", 0.0f, StatusMessage::Type::Error));
    return;
  }

  std::error_code ec;
  const bool removed = fs::remove_all(selectedWorld->rootPath, ec);

  if (ec || !removed) {
    self.updateStatus(StatusMessage("Can't overwrite existing save - is it being used?", 0.0f, StatusMessage::Type::Error));
    return;
  }

  self.updateStatus(StatusMessage("Unzipping...", 0.6f, StatusMessage::Type::Info));
  ZipUtils::extractZip(zipPath, selectedWorld->rootPath);

  self.updateStatus(StatusMessage("Save synced!", 0.0f, StatusMessage::Type::Success));
}