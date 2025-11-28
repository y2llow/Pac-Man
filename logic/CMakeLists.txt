cmake_minimum_required(VERSION 3.28)

# ============================================================================
# LOGIC LIBRARY - COMPLETELY INDEPENDENT OF SFML
# This library contains ONLY game logic and must compile without SFML
# ============================================================================

add_library(PacMan-logic STATIC
        # === Core System Files ===
        include/core/Stopwatch.h
        src/core/Stopwatch.cpp
        include/core/Random.h
        src/core/Random.cpp

        # === Design Pattern Interfaces ===
        include/patterns/Observer.h
        src/patterns/Observer.cpp
        include/patterns/Subject.h
        include/patterns/AbstractFactory.h

        # === Entity Base Classes ===
        include/entities/EntityModel.h

        # === Character Entities (Dynamic) ===
        include/entities/PacmanModel.h
        src/entities/PacmanModel.cpp
        include/entities/GhostModel.h
        src/entities/GhostModel.cpp

        # === Collectible Entities (Static) ===
        include/entities/CoinModel.h
        src/entities/CoinModel.cpp
        include/entities/FruitModel.h
        src/entities/FruitModel.cpp
        include/entities/WallModel.h
        src/entities/WallModel.cpp

        # === World Management ===
        include/world/World.h
        src/world/World.cpp

        # === Scoring System ===
        include/scoring/Score.h
        src/scoring/Score.cpp
        include/scoring/HighScoreManager.h
        src/scoring/HighScoreManager.cpp
        src/entities/EntityModel.cpp
        src/patterns/Subject.cpp
        include/world/MapModel.h
        src/world/MapModel.cpp
        src/entities/DoorModel.cpp
        include/entities/DoorModel.h
)

# Set include directories
target_include_directories(PacMan-logic
        PUBLIC
        # Public headers that representation can access
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        # Private implementation details
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# CRITICAL: NO SFML LINKAGE HERE
# The logic library must be compilable without SFML installed

# Set library properties
set_target_properties(PacMan-logic PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        POSITION_INDEPENDENT_CODE ON
)

# Enable warnings
target_compile_options(PacMan-logic PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)