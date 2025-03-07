/**
 * This file is from Kompreshar - a lossless text compression tool.
 * Copyright (C) 2025 Mehedi Rahman Mahi
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <kompreshar/KP_Window.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create(argc, argv, "org.kompreshar.app");

  KP_Window window;
  int status = app->run(window);
  if (status) {
    std::cerr << "App exited with return code " << status << std::endl;
  }
  return status;
}
