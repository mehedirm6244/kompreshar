#include "KPWindow.cpp"

#include <iostream>

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create(argc, argv, "org.chaap.app");

  KPWindow window;
  int status = app->run(window);
  if (status) {
    std::cerr << "App exited with return code " << status << std::endl;
  }
}
