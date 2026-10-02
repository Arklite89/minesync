#pragma once
#include <memory>

#include "client/Client.h"
#include "presenters/ConnectionPresenter.h"
#include "ui/ConnectionWindow.h"
#include "ui/MainWindow.h"

class AppCoordinator {
public:
    enum class State {
        Startup,
        ConnectionScreen,
        MainScreen
    };

private:
    std::unique_ptr<Client> client;
    std::unique_ptr<WorldService> worldService;

    State currentState = State::Startup;

    // --- Active State Data ---
    // Only the window/presenter for the CURRENT state will exist.
    std::unique_ptr<ConnectionWindow> connectionWindow;
    std::unique_ptr<ConnectionPresenter> connectionPresenter;

    std::unique_ptr<MainWindow> mainWindow;
    std::unique_ptr<MainPresenter> mainPresenter;

    // --- State Machine Logic ---
    void changeState(State newState);
    void tearDownCurrentState();
public:
    void start() { showConnectionWindow(); }

    void showConnectionWindow();
    void showMainWindow();
    void onConnected(std::unique_ptr<Client> client);
};
