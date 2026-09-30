//
// Created by danya on 9/30/26.
//

#include "MainPresenter.h"

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
