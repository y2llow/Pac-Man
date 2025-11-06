cmake_minimum_required(VERSION 3.10)

# set the project name
project(Pac-Man)

# set C++ standard
set(CMAKE_CXX_STANDARD 17)

# find SFML (graphics, window, system)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# add the executable
add_executable(Pac-Man main.cpp
        Logic_Library/include/core/Random.h
        Logic_Library/include/core/Stopwatch.h
        Logic_Library/include/world/World.h
        Logic_Library/include/core/GameEvent.h
        Logic_Library/include/core/Constants.h
        Logic_Library/include/patterns/Observer.h
        Logic_Library/include/patterns/AbstractFactory.h
        Logic_Library/include/entitities/Entity.h
        Logic_Library/include/entitities/DynamicEntity/Pacman.h
        Logic_Library/include/entitities/DynamicEntity/Ghost.h
        Logic_Library/include/entitities/StaticEntity_collectibles/Coin.h
        Logic_Library/include/entitities/StaticEntity_collectibles/Fruit.h
        Logic_Library/include/entitities/StaticEntity_collectibles/wall.h
        Logic_Library/include/world/Camera.h
        Logic_Library/include/world/collision.h
        Logic_Library/include/scoring/Score.h
        Logic_Library/include/scoring/HighScoreManager.h
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
        Logic_Library/include/entitities/StaticEntity.h
        Logic_Library/include/entitities/DynamicEntity.h
        Logic_Library/include/entitities/DynamicEntity/Character.h
        Logic_Library/include/patterns/subject.h
        Logic_Library/src/entitities/StaticEntity.cpp
        Logic_Library/src/entitities/DynamicEntity.cpp
        Logic_Library/src/entitities/Character.cpp
        Logic_Library/src/entitities/Pacman.cpp
        Logic_Library/src/entitities/Ghost.cpp
        Logic_Library/src/entitities/Collectable.cpp
        Logic_Library/src/entitities/Coin.cpp
        Logic_Library/src/entitities/Fruit.cpp
        Logic_Library/src/entitities/wall.cpp
        Logic_Library/src/core/Random.cpp
        Logic_Library/src/core/Stopwatch.cpp
        Logic_Library/src/scoring/HighScoreManager.cpp
        Logic_Library/src/scoring/Score.cpp
        Logic_Library/src/world/Camera.cpp
        Logic_Library/src/world/collision.cpp
        Logic_Library/src/world/World.cpp
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
