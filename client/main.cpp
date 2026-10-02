#include "src/ui/MainWindow.h"
#include <FL/Fl.H>

#include "coordinators/AppCoordinator.h"
#include "src/ui/ConnectionWindow.h"


int main(int argc, char **argv) {
  AppCoordinator coordinator;
  coordinator.start();

  return Fl::run();
}
