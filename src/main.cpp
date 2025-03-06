#include <kompreshar/KP_Window.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create(argc, argv, "org.kompreshar.app");

  KP_Window window;
  int status = app->run(window);
  if (status) {
    std::cerr << "App exited with return code " << status << std::endl;
  }
  return status;
}
