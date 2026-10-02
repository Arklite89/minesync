#pragma once
#include "services/WorldService.h"

class IMainView;

class MainPresenter {
private:
    IMainView& mainView;
    WorldService worldService;
    std::vector<World> cachedWorlds;
public:
    MainPresenter(IMainView& view, const WorldService& worldService) : mainView(view), worldService(worldService) {};
    void initialize();
    void onScoutDirectoryClicked();
    void onUploadClicked();
    void onSyncClicked();
};
