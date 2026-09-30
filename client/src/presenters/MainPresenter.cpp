//
// Created by danya on 9/30/26.
//

#include "MainPresenter.h"

#include "api/ApiController.h"
#include "cpr/filesystem.h"
#include "files/CacheHandler.h"

void MainPresenter::onScoutDirectoryClicked() {
    fs::path savesDirectory = mainView.getSavesPathInput();

    if (!fs::exists(savesDirectory) || !fs::is_directory(savesDirectory)) {
        mainView.setStatus("Saves directory is invalid!", IMainView::StatusType::Error);
    }

    cachedWorlds = worldService.scoutDirectory(savesDirectory);
    const auto worldCount = cachedWorlds.size();
    if (worldCount > 0)
        mainView.setStatus("Scouted " + std::to_string(worldCount) + "world" + (worldCount == 1 ? "." : "s."), IMainView::StatusType::Success);
    else
        mainView.setStatus("Didn't find any worlds!", IMainView::StatusType::Warning);
}

void MainPresenter::onUploadClicked() {
    auto selectedWorld = mainView.getSelectedWorld();

    if (selectedWorld == nullptr) {
        mainView.setStatus("No valid world selected!", IMainView::StatusType::Error);
        return;
    }

    mainView.setStatus("Uploading save file...", IMainView::StatusType::Info, 50);

    if (worldService.uploadWorld(*selectedWorld)) {
        mainView.setStatus("Uploaded world", IMainView::StatusType::Success);
    }
    else
        mainView.setStatus("Couldn't upload - an error occured.", IMainView::StatusType::Error);
}

void MainPresenter::onSyncClicked() {
    auto selectedWorld = mainView.getSelectedWorld();

    if (selectedWorld == nullptr) {
        mainView.setStatus("No valid world selected!", IMainView::StatusType::Error);
        return;
    }

    mainView.setStatus("Syncing save file...", IMainView::StatusType::Info, 50);

    if (worldService.syncWorld(*selectedWorld)) {
        mainView.setStatus("Uploaded world", IMainView::StatusType::Success);
    }
    else
        mainView.setStatus("Couldn't sync - an error occured.", IMainView::StatusType::Error);
}
