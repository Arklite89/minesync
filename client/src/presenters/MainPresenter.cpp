//
// Created by danya on 9/30/26.
//

#include "MainPresenter.h"

#include "api/ApiController.h"
#include "files/CacheHandler.h"
#include "ui/MainWindow.h"

void MainPresenter::initialize() {
    mainView.setServerUrl(worldService.getServerUrl());
}

void MainPresenter::onScoutDirectoryClicked() {
    fs::path savesDirectory = mainView.getSavesPathInput();

    if (!fs::exists(savesDirectory) || !fs::is_directory(savesDirectory)) {
        mainView.setStatus("Saves directory is invalid!", IMainView::StatusType::Error);
        return;
    }

    cachedWorlds = WorldService::scoutDirectory(savesDirectory);
    const auto worldCount = cachedWorlds.size();
    if (worldCount > 0)
        mainView.setStatus("Scouted " + std::to_string(worldCount) + " world" + (worldCount == 1 ? "." : "s."), IMainView::StatusType::Success);
    else
        mainView.setStatus("Didn't find any worlds!", IMainView::StatusType::Warning);

    std::vector<std::string> worldNames;
    worldNames.reserve(cachedWorlds.size());

    for (const auto& world : cachedWorlds) {
        worldNames.push_back(world.name);
    }
    mainView.setWorldChoices(worldNames);
}

void MainPresenter::onUploadClicked() {
    auto worldIndex = mainView.getSelectedWorldIndex();

    if (worldIndex < 0 || worldIndex >= cachedWorlds.size()) {
        mainView.setStatus("No valid world selected!", IMainView::StatusType::Error);
        return;
    }

    const World selectedWorld = cachedWorlds[worldIndex];

    mainView.setStatus("Uploading save file...", IMainView::StatusType::Info, 50);

    if (worldService.uploadWorld(selectedWorld)) {
        mainView.setStatus("Uploaded world to server.", IMainView::StatusType::Success);
    }
    else
        mainView.setStatus("Couldn't upload - an error occured.", IMainView::StatusType::Error);
}

void MainPresenter::onSyncClicked() {
    auto worldIndex = mainView.getSelectedWorldIndex();

    if (worldIndex < 0 || worldIndex >= cachedWorlds.size()) {
        mainView.setStatus("No valid world selected!", IMainView::StatusType::Error);
        return;
    }

    const World selectedWorld = cachedWorlds[worldIndex];

    mainView.setStatus("Syncing save file...", IMainView::StatusType::Info, 50);

    if (worldService.syncWorld(selectedWorld)) {
        mainView.setStatus("Synced local world with server.", IMainView::StatusType::Success);
    }
    else
        mainView.setStatus("Couldn't sync - an error occured.", IMainView::StatusType::Error);
}
