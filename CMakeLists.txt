cmake_minimum_required(VERSION 3.10)

# set the project name
project(Pac-Man)

# set C++ standard
set(CMAKE_CXX_STANDARD 17)

# find SFML (graphics, window, system)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_subdirectory(logic)
add_subdirectory(representation)

# add the executable
add_executable(Pac-Man main.cpp
        logic/include/core/Random.h
        logic/include/core/Stopwatch.h
        logic/include/world/World.h
        logic/include/core/GameEvent.h
        logic/include/core/Constants.h
        logic/include/patterns/Observer.h
        logic/include/patterns/AbstractFactory.h
        logic/include/entitities/Entity.h
        logic/include/entitities/DynamicEntity/Pacman.h
        logic/include/entitities/DynamicEntity/Ghost.h
        logic/include/entitities/StaticEntity_collectibles/Coin.h
        logic/include/entitities/StaticEntity_collectibles/Fruit.h
        logic/include/entitities/StaticEntity_collectibles/wall.h
        logic/include/world/Camera.h
        logic/include/world/collision.h
        logic/include/scoring/Score.h
        logic/include/scoring/HighScoreManager.h
        representation/include/Game.h
        representation/src/Game.cpp
        representation/include/factory/ConcreteFactory.h
        representation/src/factory/ConcreteFactory.cpp
        representation/include/views/EntityView.h
        representation/include/views/characterview/PacManView.h
        representation/include/views/characterview/GhostView.h
        representation/include/views/CollectibleView/coinView.h
        representation/include/views/CollectibleView/FruitView.h
        representation/include/views/WallView.h
        representation/include/states/MenuState.h
        representation/include/states/LevelState.h
        representation/include/states/PausedState.h
        representation/include/states/VictoryState.h
        representation/include/states/GameOverState.h
        logic/include/entitities/StaticEntity.h
        logic/include/entitities/DynamicEntity.h
        logic/include/entitities/DynamicEntity/Character.h
        logic/include/patterns/subject.h
        logic/src/entitities/StaticEntity.cpp
        logic/src/entitities/DynamicEntity.cpp
        logic/src/entitities/Character.cpp
        logic/src/entitities/Pacman.cpp
        logic/src/entitities/Ghost.cpp
        logic/src/entitities/Collectable.cpp
        logic/src/entitities/Coin.cpp
        logic/src/entitities/Fruit.cpp
        logic/src/entitities/wall.cpp
        logic/src/core/Random.cpp
        logic/src/core/Stopwatch.cpp
        logic/src/scoring/HighScoreManager.cpp
        logic/src/scoring/Score.cpp
        logic/src/world/Camera.cpp
        logic/src/world/collision.cpp
        logic/src/world/World.cpp
        representation/include/views/StaticEntityView.h
        representation/include/views/DynamicEntityView.h
        representation/include/views/CharacterView.h
        representation/include/views/CollectibleView.h
        representation/include/rendering/Animation.h
        representation/include/rendering/SpriteManager.h
        representation/src/rendering/Animation.cpp
        representation/src/rendering/SpriteManager.cpp
        representation/src/views/CharacterView.cpp
        representation/src/views/WallView.cpp
        representation/src/views/StaticEntityView.cpp
        representation/src/views/EntityView.cpp
        representation/src/views/DynamicEntityView.cpp
        representation/src/views/CollectibleView.cpp
        representation/src/views/characterview/PacManView.cpp
        representation/src/views/characterview/GhostView.cpp
        representation/src/views/CollectibleView/coinView.cpp
        representation/src/views/CollectibleView/FruitView.cpp
        representation/src/states/MenuState.cpp
        representation/src/states/PausedState.cpp
        representation/src/states/VictoryState.cpp
        representation/src/states/LevelState.cpp
        representation/src/states/GameOverState.cpp
        representation/src/StateManager.cpp
        representation/src/Camera.cpp
        representation/include/Camera.h
        representation/include/StateManger.h
)

# link SFML libraries
target_link_libraries(Pac-Man sfml-graphics sfml-window sfml-system)
