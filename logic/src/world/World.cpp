#include "world/World.h"
#include "entities/WallModel.h"
#include "entities/CoinModel.h"
#include "entities/PacmanModel.h"
#include "entities/GhostModel.h"
#include "entities/FruitModel.h"
#include <iostream>

World::World(LogicFactory& factory)
    : m_factory(&factory) {
    m_score = std::make_unique<Score>();
}

void World::initialize() {
    if (m_mapModel.loadFromFile("assets/maps/map2.txt")) {
        createEntitiesFromMap();
    }
}

void World::createEntitiesFromMap() {
    const auto& grid = m_mapModel.getGrid();
    Vector2f gridSize = m_mapModel.getGridSize();

    if (grid.empty()) return;

    float tileWidth = 2.0f / gridSize.x;
    float tileHeight = 2.0f / gridSize.y;

    for (unsigned int y = 0; y < gridSize.y; ++y) {
        for (unsigned int x = 0; x < gridSize.x; ++x) {
            float posX = -1.0f + (x * tileWidth) + (tileWidth / 2.0f);
            float posY = -1.0f + (y * tileHeight) + (tileHeight / 2.0f);

            if (grid[y][x] == 'x') {
                auto wall = m_factory->createWall(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth , tileHeight),
                    "wall_basic"
                );
                m_walls.push_back(wall);
            }
            else if (grid[y][x] == '.') {
                auto coin = m_factory->createCoin(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth * COIN_SIZE, tileHeight * COIN_SIZE),
                    "Coin"
                );
                m_coins.push_back(coin);
            }
            else if (grid[y][x] == 'P') {
                auto pacman = m_factory->createPacman(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth * PACMAN_SIZE, tileHeight * PACMAN_SIZE),
                    "Pacman"
                );
                m_pacman = pacman;
            }
            else if (grid[y][x] == 'f') {
                auto fruit = m_factory->createFruit(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth * FRUIT_SIZE, tileHeight * FRUIT_SIZE),
                    "fruit"
                );
                m_fruits.push_back(fruit);
            }
            else if (grid[y][x] == 'r') {
                auto ghost = m_factory->createRedGhost(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth * GHOST_SIZE, tileHeight * GHOST_SIZE),
                    "red_ghost"
                );
                m_ghosts.push_back(ghost);
            }
            else if (grid[y][x] == 'b') {
                auto ghost = m_factory->createBlueGhost(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth * GHOST_SIZE, tileHeight * GHOST_SIZE),
                    "blue_ghost"
                );
                m_ghosts.push_back(ghost);
            }
            else if (grid[y][x] == 'o') {
                auto ghost = m_factory->createOrangeGhost(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth * GHOST_SIZE, tileHeight * GHOST_SIZE),
                    "orange_ghost"
                );
                m_ghosts.push_back(ghost);
            }
            else if (grid[y][x] == 'p') {
                auto ghost = m_factory->createPinkGhost(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth * GHOST_SIZE, tileHeight * GHOST_SIZE),
                    "pink_ghost"
                );
                m_ghosts.push_back(ghost);
            }
        }
    }
    std::cout << "World: Created " << m_walls.size() << " walls and " << m_coins.size() << " coins" << std::endl;
}



void World::update(float deltaTime) {
    // EERST: Predictive movement voor Pacman
    handlePredictiveMovement(deltaTime);

    // TWEEDE: Ghosts en andere entities (geen predictive nodig)
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

    // DERDE: Collectible collisions (na movement)
    handleCollectibleCollisions();

    // VIERDE: Cleanup
    cleanupCollectedItems();

    checkGameState();
}

void World::handlePredictiveMovement(float deltaTime) {
        // 1. Update input buffer
        m_pacman->update(deltaTime);

        // 2. Check of gebufferde richting mogelijk is
        int bufferedDir = m_pacman->getBufferedDirection();
        if (bufferedDir != -1) {
            // Probeer gebufferde richting
            Vector2f bufferedPosition = m_pacman->calculatePositionInDirection(
                m_pacman->getPosition(), bufferedDir, deltaTime);

            if (!wouldCollideWithWalls(*m_pacman, bufferedPosition)) {
                // Gebufferde richting is mogelijk! Verander richting
                m_pacman->setDirection(bufferedDir);
                m_pacman->clearBufferedDirection();
            }
        }

        // 3. Beweeg in huidige richting (of nieuwe als buffer werkte)
        Vector2f nextPosition = m_pacman->calculateNextPosition(deltaTime);

        if (!wouldCollideWithWalls(*m_pacman, nextPosition)) {
            m_pacman->applyMovement(nextPosition);
        }
        // ELSE: m_pacman blijft staan maar buffer blijft actief

        // 4. Notify observers
        m_pacman->notifyObservers();

}

bool World::wouldCollideWithWalls(const PacmanModel& pacman, const Vector2f& newPosition) const {
    // Maak tijdelijke pacman met nieuwe positie voor collision check
    PacmanModel tempPacman = pacman;
    tempPacman.setPosition(newPosition);

    // Check collision met alle walls
    for (const auto& wall : m_walls) {
        if (checkCollision(tempPacman, *wall)) {
            return true; // Zou colliden
        }
    }
    return false; // Geen collision
}

void World::handleCollectibleCollisions() {
    // Pacman vs Coins (na movement)
    for (auto it = m_coins.begin(); it != m_coins.end(); ) {
        if (checkCollision(*m_pacman, **it)) {
            handlePacmanCoinCollision(**it);
            it = m_coins.erase(it);
        } else {
            ++it;
        }
    }

// Pacman vs Fruits (na movement)
    for (auto it = m_fruits.begin(); it != m_fruits.end(); ) {
        if (checkCollision(*m_pacman, **it)) {
            handlePacmanFruitCollision(**it);
            it = m_fruits.erase(it);
        } else {
            ++it;
        }
    }

// Pacman vs Ghosts (na movement)
    for (auto& ghost : m_ghosts) {
        if (checkCollision(*m_pacman, *ghost)) {
            handlePacmanGhostCollision(*m_pacman, *ghost);
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
    if (pacman_right > e2_left &&
        pacman_left < e2_right &&
        pacman_top > e2_bottom &&
        pacman_bottom < e2_top) {
        return true;  // Collision detected
    }

    return false;  // No collision
}



void World::handlePacmanCoinCollision(CoinModel& coin) {
    m_score->onCoinCollected();
    coin.collect();
}

void World::handlePacmanGhostCollision(PacmanModel& pacman, GhostModel& ghost) {
    if (ghost.isScared()) {
        m_score->onGhostEaten();
        ghost.respawn();
    } else {
        pacman.loseLife();
        for (auto g : m_ghosts) {
            g->respawn();
        }
        if (pacman.getLives() <= 0) {
            pacman.setPosition({0.5,0.5});
        }
    }
}

void World::handlePacmanFruitCollision(FruitModel& fruit) {
    m_score->onCoinCollected();
    fruit.collect();
    for (auto& ghost : m_ghosts) {
        ghost->setScared();
    }
}

void World::cleanupCollectedItems() {
    // Remove any null pointers or cleanup
    m_coins.erase(std::remove_if(m_coins.begin(), m_coins.end(),
        [](const std::shared_ptr<CoinModel>& coin) {
            return coin->isCollected();
        }), m_coins.end());

    m_fruits.erase(std::remove_if(m_fruits.begin(), m_fruits.end(),
        [](const std::shared_ptr<FruitModel>& fruit) {
            return fruit->isCollected();
        }), m_fruits.end());
}

//TODO IMPLEMNT THISS
void World::checkGameState() {
    // Check win condition (all coins collected)
    // if (m_coins.empty()) {
    //     m_stateManager.switchToState(std::make_unique<MenuState>(m_stateManager, m_window, m_camera));
    // }
    // // Check lose condition (no lives left)
    // for (auto& pacman : m_pacman) {
    //     if (pacman->getLives() <= 0) {
    //         m_stateManager.switchToState(std::make_unique<MenuState>(m_stateManager, m_window, m_camera));
    //     }
    // }
}
