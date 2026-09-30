#include "src/ui/MainWindow.h"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>

#include "src/ui/ConnectionWindow.h"


int main(int argc, char **argv) {
  auto client = Client::create("http://localhost:18080");
  if (!client) { return 1; }

  WorldService service(&*client);

  MainWindow window;
  MainPresenter presenter(window, service);

  window.setPresenter(&presenter);
  presenter.initialize();

  window.show();

  return Fl::run();
}
