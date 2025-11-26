cmake_minimum_required(VERSION 3.28)

# ============================================================================
# REPRESENTATION LIBRARY - SFML-DEPENDENT VIEW LAYER
# This library depends on both the logic library and SFML
# ============================================================================

add_library(PacMan-representation STATIC
        # === Main Game Controller ===
        include/Game.h
        src/Game.cpp

        # === State Management ===
        include/StateManger.h
        src/StateManager.cpp
        include/states/MenuState.h
        src/states/MenuState.cpp
        include/states/LevelState.h
        src/states/LevelState.cpp
        include/states/PausedState.h
        src/states/PausedState.cpp
        include/states/VictoryState.h
        src/states/VictoryState.cpp
        include/states/GameOverState.h
        src/states/GameOverState.cpp

        # === Camera (Projection System) ===
        include/Camera.h
        src/Camera.cpp

        # === Abstract Factory Implementation ===
        include/factory/ConcreteFactory.h
        src/factory/ConcreteFactory.cpp

        # === Rendering & Animation ===
        include/rendering/SpriteManager.h
        src/rendering/SpriteManager.cpp
        include/rendering/Animations.h
        src/rendering/Animations.cpp

        # === View Base Classes ===
        include/views/EntityView.h
        src/views/EntityView.cpp

        # === Character Views ===
        include/views/characterview/PacmanView.h
        src/views/characterview/PacmanView.cpp
        include/views/characterview/GhostView.h
        src/views/characterview/GhostView.cpp

        # === Collectible Views ===
        include/views/CollectibleView.h
        src/views/CollectibleView.cpp
        include/views/CollectibleView/CoinView.h
        src/views/CollectibleView/CoinView.cpp
        include/views/CollectibleView/FruitView.h
        src/views/CollectibleView/FruitView.cpp

        # === Wall View ===
        include/views/WallView.h
        src/views/WallView.cpp
        include/Window.h
        src/Window.cpp
        include/views/MapView.h
        src/views/MapView.cpp
        include/states/State.h
        src/states/State.cpp
        include/rendering/SpriteSheet.h
        src/rendering/SpriteSheet.cpp
)

# Set include directories
target_include_directories(PacMan-representation
        PUBLIC
        # Public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        # Private implementation details
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link dependencies
target_link_libraries(PacMan-representation
        PUBLIC
        # Logic library (public so main executable can access if needed)
        PacMan-logic
        PRIVATE
        # SFML components (private - implementation detail)
        sfml-graphics
        sfml-window
        sfml-system
)

# Set library properties
set_target_properties(PacMan-representation PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        POSITION_INDEPENDENT_CODE ON
)

# Enable warnings
target_compile_options(PacMan-representation PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

## Copy resources to build directory (sprites, maps, etc.)
#add_custom_command(TARGET PacMan-representation POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/sprites
#        ${CMAKE_BINARY_DIR}/bin/sprites
#        COMMENT "Copying sprite resources to build directory"
#)