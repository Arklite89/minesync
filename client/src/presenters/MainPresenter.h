#pragma once
#include "services/WorldService.h"
#include "ui/MainWindow.h"

class MainPresenter {
private:
    IMainView& mainView;
    WorldService worldService;
    std::vector<World> cachedWorlds;
public:
    MainPresenter(IMainView& view, const WorldService& worldService) : mainView(view), worldService(worldService) {};
    void initialize() {
        mainView.setServerUrl(worldService.getServerUrl());
    }
    void onScoutDirectoryClicked();
    void onUploadClicked();
    void onSyncClicked();
};
