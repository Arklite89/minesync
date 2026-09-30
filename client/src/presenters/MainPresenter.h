#pragma once
#include "services/WorldService.h"

class IMainView {
public:
    enum class StatusType { Info, Success, Warning, Error};

    virtual ~IMainView() = default;
    virtual void setServerUrl(const std::string& url) = 0;
    virtual void setWorldChoices(const std::vector<std::string>& worldNames) = 0;
    virtual void setStatus(const std::string& message, StatusType type = StatusType::Info, float progress = 0.0f);
    virtual std::string getSavesPathInput() const = 0;
    virtual void setSavesPathInput(const std::string& path) = 0;
    virtual int getSelectedWorldIndex() const = 0;
};

class MainPresenter {
private:
    IMainView& mainView;
    WorldService worldService;
    std::vector<World> cachedWorlds;
public:
    MainPresenter(IMainView& view, WorldService& worldService) : mainView(view), worldService(worldService) {};
    void initialize();
    void onScoutDirectoryClicked();
    void onUploadClicked();
    void onSyncClicked();
};
