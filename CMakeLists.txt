cmake_minimum_required(VERSION 3.28)

# Project definition
project(PacMan-Game VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard (C++17 required for modern C++ features)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable compile warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find SFML (only needed for representation, NOT logic)
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Add subdirectories
add_subdirectory(logic)
add_subdirectory(representation)

# Main executable
add_executable(Pac-Man main.cpp)

# Link main executable with representation library
# The representation library will transitively provide the logic library
target_link_libraries(Pac-Man
        PRIVATE
        PacMan-representation
)

# Set output directory (optional, for cleaner builds)
set_target_properties(Pac-Man PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# Copy the resources folder (which includes your .txt files) to the build directory
add_custom_command(TARGET Pac-Man POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
        COMMENT "Copying resources to build directory"
)