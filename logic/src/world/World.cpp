#include "world/World.h"
#include "entities/WallModel.h"
#include "entities/CoinModel.h"

#include <iostream>

World::World(const sf::Vector2u& windowSize, LogicFactory& factory)
    : m_factory(&factory), m_windowSize(windowSize) {
    m_score = std::make_unique<Score>();
}

void World::initialize() {
    // Load map and create entities
    if (m_mapModel.loadFromFile("assets/maps/map2.txt")) {
        createEntitiesFromMap();
    }
    // if (m_mapModel.loadFromFile("assets/maps/map.txt")) {
    //     createEntitiesFromMap();
    // }
}

void World::createEntitiesFromMap() {
    const auto& grid = m_mapModel.getGrid();
    sf::Vector2u gridSize = m_mapModel.getGridSize();

    if (grid.empty()) return;

    sf::Vector2u currentWindowSize = m_windowSize; // This should be updated on resize

    float tileWidth = 2.0f / gridSize.x;
    float tileHeight = 2.0f / gridSize.y;

    for (unsigned int y = 0; y < gridSize.y; ++y) {
        for (unsigned int x = 0; x < gridSize.x; ++x) {
            if (grid[y][x] == 'x') {
                float posX = -1.0f + (x * tileWidth) + (tileWidth / 2.0f);
                float posY = -1.0f + (y * tileHeight) + (tileHeight / 2.0f);

                auto wall = m_factory->createWall(
                    sf::Vector2f(posX, posY),
                    sf::Vector2f(tileWidth * 0.9f, tileHeight * 0.9f),
                    "wall_basic"
                );
                m_walls.push_back(std::move(wall));
            }
            else if (grid[y][x] == '.') {
                float posX = -1.0f + (x * tileWidth) + (tileWidth / 2.0f);
                float posY = -1.0f + (y * tileHeight) + (tileHeight / 2.0f);

                auto coin = m_factory->createCoin(
                    sf::Vector2f(posX, posY),
                    sf::Vector2f(tileWidth * COIN_SIZE , tileHeight * COIN_SIZE ),
                    "Coin"
                );
                m_coins.push_back(std::move(coin));
            }
            else if (grid[y][x] == 'P') {
                float posX = -1.0f + (x * tileWidth) + (tileWidth / 2.0f) ;
                float posY = -1.0f + (y * tileHeight) + (tileHeight / 2.0f);

                auto pacman = m_factory->createPacman(
                    sf::Vector2f(posX, posY),
                    sf::Vector2f(tileWidth * PACMAN_SIZE, tileHeight * PACMAN_SIZE ),
                    "Pacman");

                m_pacman.push_back(std::move(pacman));
            }
            else if (grid[y][x] == 'f' ){
                float posX = -1.0f + (x * tileWidth) + (tileWidth / 2.0f);
                float posY = -1.0f + (y * tileHeight) + (tileHeight / 2.0f);

                auto fruit = m_factory->createFruit(
                    sf::Vector2f(posX, posY),
                    sf::Vector2f(tileWidth * FRUIT_SIZE , tileHeight * FRUIT_SIZE ),
                    "fruit");

                m_fruits.push_back(std::move(fruit));
            }
            else if (grid[y][x] == 'r') {
                float posX = -1.0f + (x * tileWidth) + (tileWidth / 2.0f);
                float posY = -1.0f + (y * tileHeight) + (tileHeight / 2.0f);

                auto ghost = m_factory->createRedGhost(
                    sf::Vector2f(posX, posY),
                    sf::Vector2f(tileWidth * GHOST_SIZE, tileHeight * GHOST_SIZE),
                    "red_ghost");

                m_ghosts.push_back(std::move(ghost));
            }
            else if (grid[y][x] == 'b') {
                float posX = -1.0f + (x * tileWidth) + (tileWidth / 2.0f);
                float posY = -1.0f + (y * tileHeight) + (tileHeight / 2.0f);

                auto ghost = m_factory->createBlueGhost(
                    sf::Vector2f(posX, posY),
                    sf::Vector2f(tileWidth * GHOST_SIZE, tileHeight * GHOST_SIZE),
                    "blue_ghost");

                m_ghosts.push_back(std::move(ghost));
            }            else if (grid[y][x] == 'o') {
                float posX = -1.0f + (x * tileWidth) + (tileWidth / 2.0f);
                float posY = -1.0f + (y * tileHeight) + (tileHeight / 2.0f);

                auto ghost = m_factory->createOrangeGhost(
                    sf::Vector2f(posX, posY),
                    sf::Vector2f(tileWidth * GHOST_SIZE, tileHeight * GHOST_SIZE),
                    "orange_ghost");

                m_ghosts.push_back(std::move(ghost));
            }            else if (grid[y][x] == 'p') {
                float posX = -1.0f + (x * tileWidth) + (tileWidth / 2.0f);
                float posY = -1.0f + (y * tileHeight) + (tileHeight / 2.0f);

                auto ghost = m_factory->createPinkGhost(
                    sf::Vector2f(posX, posY),
                    sf::Vector2f(tileWidth * GHOST_SIZE, tileHeight * GHOST_SIZE),
                    "pink_ghost");

                m_ghosts.push_back(std::move(ghost));
            }
            // r = red
            // b = blue
            // p = pink
            // o = orange
        }
    }
    //TODO remove
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
    // Get bounds for pacman (assuming center-based coordinates)
    float pacman_left = pacman.getPosition().x - (pacman.getSize().x / 2);
    float pacman_right = pacman.getPosition().x + (pacman.getSize().x / 2);
    float pacman_bottom = pacman.getPosition().y - (pacman.getSize().y / 2);
    float pacman_top = pacman.getPosition().y + (pacman.getSize().y / 2);

    // Get bounds for entity2
    float e2_left = entity2.getPosition().x - (entity2.getSize().x / 2);
    float e2_right = entity2.getPosition().x + (entity2.getSize().x / 2);
    float e2_bottom = entity2.getPosition().y - (entity2.getSize().y / 2);
    float e2_top = entity2.getPosition().y + (entity2.getSize().y / 2);

    // Correct AABB collision detection
    // Two rectangles collide if:
    // - pacman's right edge is to the right of entity's left edge AND
    // - pacman's left edge is to the left of entity's right edge AND
    // - pacman's top edge is below entity's bottom edge AND
    // - pacman's bottom edge is above entity's top edge
    if (pacman_right > e2_left &&
        pacman_left < e2_right &&
        pacman_top > e2_bottom &&
        pacman_bottom < e2_top) {
        return true;  // Collision detected
        }

    return false;  // No collision
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

void World::handleResize(const sf::Vector2u& newSize) {
    m_windowSize = newSize;
    // Don't recreate entities, just update the window size for future calculations
}

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

