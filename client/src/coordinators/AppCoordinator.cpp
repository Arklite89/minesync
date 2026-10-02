#include "AppCoordinator.h"
#include "ui/ConnectionWindow.h"

void AppCoordinator::showConnectionWindow() {
    if (mainWindow) mainWindow->hide();

    connectionWindow = std::make_unique<ConnectionWindow>();
    connectionPresenter = std::make_unique<ConnectionPresenter>(*connectionWindow, [this](std::unique_ptr<Client> newClient) {
        client = std::move(newClient);
        connectionWindow->hide();
        showMainWindow();
    });

    connectionWindow->setPresenter(connectionPresenter.get());
    connectionWindow->show();
}

void AppCoordinator::showMainWindow() {
    worldService = std::make_unique<WorldService>(client.get());
    mainWindow = std::make_unique<MainWindow>();
    mainPresenter = std::make_unique<MainPresenter>(*mainWindow, *worldService);

    mainWindow->setPresenter(mainPresenter.get());
    mainPresenter->initialize();
    mainWindow->show();
}

void AppCoordinator::onConnected(std::unique_ptr<Client> connectedClient) {
    client = std::move(connectedClient);

    connectionWindow->hide();
    connectionPresenter.reset();
    connectionWindow.reset();

    showMainWindow();
}