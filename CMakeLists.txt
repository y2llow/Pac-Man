cmake_minimum_required(VERSION 3.10)

# set the project name
project(Pac-Man)

# set C++ standard
set(CMAKE_CXX_STANDARD 17)

# find SFML (graphics, window, system)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# add the executable
add_executable(Pac-Man main.cpp)

# link SFML libraries
target_link_libraries(Pac-Man sfml-graphics sfml-window sfml-system)
