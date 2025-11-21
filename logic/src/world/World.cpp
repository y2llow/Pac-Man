#include "world/World.h"
#include "entities/WallModel.h"
#include "entities/CoinModel.h"

#include <iostream>

World::World(LogicFactory& factory)
    : m_factory(&factory) {
    m_score = std::make_unique<Score>();
}

void World::initialize(const Vector2f& gridSize) {
    m_gridSize = gridSize;

    // Load map and create entities
    if (m_mapModel.loadFromFile("assets/maps/map2.txt")) {
        createEntitiesFromMap();
    }
}

void World::createEntitiesFromMap() {
    const auto& grid = m_mapModel.getGrid();
    Vector2f gridSize = m_mapModel.getGridSize();

    if (grid.empty()) return;

    // Calculate tile sizes in normalized coordinates [-1, 1]
    float tileWidth = 2.0f / gridSize.x;
    float tileHeight = 2.0f / gridSize.y;

    for (unsigned int y = 0; y < gridSize.y; ++y) {
        for (unsigned int x = 0; x < gridSize.x; ++x) {
            // Calculate center of each tile in normalized coordinates
            float posX = -1.0f + (x * tileWidth) + (tileWidth / 2.0f);
            float posY = -1.0f + (y * tileHeight) + (tileHeight / 2.0f);

            if (grid[y][x] == 'x') {
                auto wall = m_factory->createWall(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth * 0.9f, tileHeight * 0.9f),
                    "wall_basic"
                );
                m_walls.push_back(std::move(wall));
            }
            else if (grid[y][x] == '.') {
                auto coin = m_factory->createCoin(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth * COIN_SIZE, tileHeight * COIN_SIZE),
                    "Coin"
                );
                m_coins.push_back(std::move(coin));
            }
            else if (grid[y][x] == 'P') {
                auto pacman = m_factory->createPacman(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth * PACMAN_SIZE, tileHeight * PACMAN_SIZE),
                    "Pacman"
                );
                m_pacman.push_back(std::move(pacman));
            }
            else if (grid[y][x] == 'f') {
                auto fruit = m_factory->createFruit(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth * FRUIT_SIZE, tileHeight * FRUIT_SIZE),
                    "fruit"
                );
                m_fruits.push_back(std::move(fruit));
            }
            else if (grid[y][x] == 'r') {
                auto ghost = m_factory->createRedGhost(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth * GHOST_SIZE, tileHeight * GHOST_SIZE),
                    "red_ghost"
                );
                m_ghosts.push_back(std::move(ghost));
            }
            else if (grid[y][x] == 'b') {
                auto ghost = m_factory->createBlueGhost(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth * GHOST_SIZE, tileHeight * GHOST_SIZE),
                    "blue_ghost"
                );
                m_ghosts.push_back(std::move(ghost));
            }
            else if (grid[y][x] == 'o') {
                auto ghost = m_factory->createOrangeGhost(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth * GHOST_SIZE, tileHeight * GHOST_SIZE),
                    "orange_ghost"
                );
                m_ghosts.push_back(std::move(ghost));
            }
            else if (grid[y][x] == 'p') {
                auto ghost = m_factory->createPinkGhost(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth * GHOST_SIZE, tileHeight * GHOST_SIZE),
                    "pink_ghost"
                );
                m_ghosts.push_back(std::move(ghost));
            }
        }
    }
    std::cout << "World: Created " << m_walls.size() << " walls and " << m_coins.size() << " coins" << std::endl;
}

void World::addEntity(std::unique_ptr<EntityModel> entity) {
    // For dynamic entity creation later
}

void World::update(float deltaTime) {
    // First: Update all entities (movement, animation, etc.)
    for (auto& pacman : m_pacman) {
        pacman->update(deltaTime);
    }
    for (auto& ghost : m_ghosts) {
        ghost->update(deltaTime);
    }
    for (auto& wall : m_walls) {
        wall->update(deltaTime);
    }
    for (auto& coin : m_coins) {
        coin->update(deltaTime);
    }
    for (auto& fruit : m_fruits) {
        fruit->update(deltaTime);
    }

    // Second: Handle collisions after all positions are updated
    handleCollisions();

    // Third: Clean up collected items, check win/lose conditions
     cleanupCollectedItems();
    // checkGameState();
}

void World::handleCollisions() {
    // Pacman vs Walls
    for (auto& pacman : m_pacman) {
        for (auto& wall : m_walls) {
            if (checkCollision(*pacman, *wall)) {
                handlePacmanWallCollision(*pacman, *wall);
            }
        }
    }

    // Pacman vs Coins
    for (auto& pacman : m_pacman) {
        for (auto it = m_coins.begin(); it != m_coins.end(); ) {
            if (checkCollision(*pacman, **it)) {
                handlePacmanCoinCollision(**it);
                it = m_coins.erase(it); // Remove collected coin
            } else {
                ++it;
            }
        }
    }

    // Pacman vs Ghosts
    for (auto& pacman : m_pacman) {
        for (auto& ghost : m_ghosts) {
            if (checkCollision(*pacman, *ghost)) {
                handlePacmanGhostCollision(*pacman, *ghost);
            }
        }
    }

    // Pacman vs Fruits
    for (auto& pacman : m_pacman) {
        for (auto it = m_fruits.begin(); it != m_fruits.end(); ) {
            if (checkCollision(*pacman, **it)) {
                handlePacmanFruitCollision( **it);
                it = m_fruits.erase(it); // Remove collected fruit
            } else {
                ++it;
            }
        }
    }
}

bool World::checkCollision(const PacmanModel& pacman, const EntityModel& entity2) {
    // All coordinates are normalized [-1, 1], so collision works the same

    const Vector2f& pacmanPos = pacman.getPosition();
    const Vector2f& pacmanSize = pacman.getSize();
    const Vector2f& entity2Pos = entity2.getPosition();
    const Vector2f& entity2Size = entity2.getSize();

    // Calculate bounds in normalized coordinates
    float pacmanLeft = pacmanPos.x - (pacmanSize.x / 2);
    float pacmanRight = pacmanPos.x + (pacmanSize.x / 2);
    float pacmanBottom = pacmanPos.y - (pacmanSize.y / 2);
    float pacmanTop = pacmanPos.y + (pacmanSize.y / 2);

    float entity2Left = entity2Pos.x - (entity2Size.x / 2);
    float entity2Right = entity2Pos.x + (entity2Size.x / 2);
    float entity2Bottom = entity2Pos.y - (entity2Size.y / 2);
    float entity2Top = entity2Pos.y + (entity2Size.y / 2);

    // AABB collision in normalized space
    return (pacmanRight > entity2Left &&
            pacmanLeft < entity2Right &&
            pacmanTop > entity2Bottom &&
            pacmanBottom < entity2Top);
}

void World::handlePacmanWallCollision(PacmanModel& pacman, const WallModel& wall) {// Push pacman back to previous position
    pacman.undoLastMove();
    // Or prevent movement in that direction
}

void World::handlePacmanCoinCollision(CoinModel& coin) {
    m_score->onCoinCollected(); // Add points for coin
    coin.collect();
}

void World::handlePacmanGhostCollision(PacmanModel& pacman, GhostModel& ghost) {
    if (ghost.isScared()) {
        m_score->onGhostEaten(); // Add points for coin
        ghost.respawn();
    } else {
        // Pacman loses life
        pacman.loseLife();
        if (pacman.getLives() <= 0) {
            //TODO push game over state
            pacman.setPosition({0.5,0.5});
        }
    }
}

void World::handlePacmanFruitCollision(FruitModel& fruit) {
    m_score->onCoinCollected();
    fruit.collect();
    for (auto& ghost : m_ghosts) {
        ghost->setScared();  // Use the smart pointer directly
    }
}

void World::cleanupCollectedItems() {
    // Remove any null pointers or cleanup
    m_coins.erase(std::remove_if(m_coins.begin(), m_coins.end(),
        [](const std::unique_ptr<CoinModel>& coin) {
            return coin->isCollected();
        }), m_coins.end());

    m_fruits.erase(std::remove_if(m_fruits.begin(), m_fruits.end(),
        [](const std::unique_ptr<FruitModel>& fruit) {
            return fruit->isCollected();
        }), m_fruits.end());
}

// void World::handleResize(const Vector2f& newSize) {
//     m_windowSize = newSize;
//     // Don't recreate entities, just update the window size for future calculations
// }

//TODO implement checkgamestate
void World::checkGameState() {
    // Check win condition (all coins collected)
    if (m_coins.empty()) {
        // Level completed
    }

    // Check lose condition (no lives left)
    for (auto& pacman : m_pacman) {
        if (pacman->getLives() <= 0) {
            // Game over
        }
    }
}

