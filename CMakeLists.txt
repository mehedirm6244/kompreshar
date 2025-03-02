cmake_minimum_required(VERSION 3.31)
project(Kompreshar)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

# Include directories
include_directories(./include)
include_directories(${GTKMM_INCLUDE_DIRS})

# Define the executable and its source files
add_executable(kompreshar
    src/main.cpp
    src/KP_Compressor.cpp
    src/KP_Window.cpp
)

# Link libraries
target_link_libraries(kompreshar ${GTKMM_LIBRARIES})
