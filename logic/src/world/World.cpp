#include "world/World.h"
#include "entities/WallModel.h"
#include "entities/CoinModel.h"
#include "entities/PacmanModel.h"
#include "entities/GhostModel.h"
#include "entities/FruitModel.h"


#include <cmath>
#include <iostream>

World::World(LogicFactory& factory)
    : m_factory(&factory) {
    m_score = std::make_unique<Score>();
}

void World::initialize() {
    if (m_mapModel.loadFromFile("assets/maps/map3.txt")) {
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
            else if (grid[y][x] == 'S') {
                auto coin = m_factory->createCoin(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth * COIN_SIZE, tileHeight * COIN_SIZE),
                    "Coin"
                );
                m_startPosition = Vector2f(posX, posY);
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
            else if (grid[y][x] == 'd') {
                auto door = m_factory->createDoor(
                    Vector2f(posX, posY),
                    Vector2f(tileWidth , tileHeight),
                    "wall"
                );
                m_doors.push_back(door);
            }
        }
    }
    std::cout << "World: Created " << m_walls.size() << " walls and " << m_coins.size() << " coins" << std::endl;
}

void World::update(float deltaTime) {
    // Update score over time (decreases score)
    m_score->updateScoreOverTime(deltaTime);

    // Check if we need to handle death animation completion
    checkDeathAnimationState();

    // If Pac-Man is dying, skip normal movement updates
    if (!m_pacman->isDying()) {
        // EERST: Predictive movement voor Pacman
        handlePredictivePacmanMovement(deltaTime);

//todo
        for (auto& ghost : m_ghosts) {
            // If ghost is outside starting house
            if (!ghost->GetOutsideStart() && ghost->GetMovingToStart()) {
                ghost->MoveToStartPosition(m_startPosition, deltaTime);

            }else if (!ghost->GetOutsideStart()) {
                handlePredictiveGhostMovement(ghost,deltaTime);
            }else {
                ghost->GhostAIMovement();
                handlePredictiveGhostMovement(ghost,deltaTime);

            }
                // handleGhostMovement(ghost, deltaTime);
            // }else {
            //     ghost->MoveToStartPosition(m_startPosition, deltaTime);
            // }
            //todo before update check first if there is a wall inront of the ghosts or in the movement they want to go

            ghost->updateMovement(deltaTime);
            ghost->update(deltaTime);
        }

        // DERDE: Collectible collisions (na movement)
        handleCollectibleCollisions();

        // Check for level completion - maar DON'T call advanceToNextLevel hier!
        // Dat wordt nu gedaan vanuit LevelState na de overlay
        if (areAllCoinsCollected()) {
            m_score->onLevelCleared();
            // VERWIJDERD: advanceToNextLevel();
            // Dit wordt nu vanuit LevelState gedaan
        }
    } else {
        // Only update Pac-Man during death animation (for animation timing)
        m_pacman->update(deltaTime);
    }

    // Always update these (they might have their own animations)
    for (auto& wall : m_walls) {
        wall->update(deltaTime);
    }
    for (auto& coin : m_coins) {
        coin->update(deltaTime);
    }
    for (auto& fruit : m_fruits) {
        fruit->update(deltaTime);
    }

    // VIERDE: Cleanup
    cleanupCollectedItems();
}


void World::handlePredictivePacmanMovement(float deltaTime) {
    // 1. Update input buffer
    m_pacman->update(deltaTime);

    // 2. Check if buffered direction is possible
    int bufferedDir = m_pacman->getBufferedDirection();
    if (bufferedDir != -1) {
        // Try buffered direction
        Vector2f bufferedPosition = m_pacman->calculatePositionInDirection(
            m_pacman->getPosition(), bufferedDir, deltaTime);

        if (!PacmanWouldCollideWithWalls(*m_pacman, bufferedPosition)) {
            // Buffered direction is possible! Change direction
            m_pacman->setDirection(bufferedDir);
            m_pacman->clearBufferedDirection();
        } else {
            // Try position correction to allow the turn
            Vector2f correctedPos = tryPositionCorrection(
                m_pacman->getPosition(),
                m_pacman->getDirection(),
                bufferedDir,
                deltaTime
            );

            if (correctedPos.x != m_pacman->getPosition().x ||
                correctedPos.y != m_pacman->getPosition().y) {
                // Correction was successful! Apply it and change direction
                m_pacman->setPosition(correctedPos);
                m_pacman->setDirection(bufferedDir);
                m_pacman->clearBufferedDirection();
            }
        }
    }

    // 3. Move in current direction (or new if buffer worked)
    Vector2f nextPosition = m_pacman->calculateNextPosition(deltaTime);

    if (!PacmanWouldCollideWithWalls(*m_pacman, nextPosition)) {
        m_pacman->applyMovement(nextPosition);
    } else {
        // NEW: Can't move forward - find closest valid position to the wall
        Vector2f closestPos = findClosestPositionToWall(
            m_pacman->getPosition(),
            m_pacman->getDirection(),
            deltaTime
        );

        if (closestPos.x != m_pacman->getPosition().x ||
            closestPos.y != m_pacman->getPosition().y) {
            m_pacman->setPosition(closestPos);
        }
    }

    // 4. Notify observers
    m_pacman->notifyObservers();
}

void World::handlePredictiveGhostMovement(const std::shared_ptr<GhostModel>& ghost,float deltaTime) {

    if (ghost->canMoveInDirection(ghost->getDirection(),*this, deltaTime)) {
    }
    else if (ghost->canMoveInDirection(ghost->SetDirection(0),*this, deltaTime)) {
        ghost->SetDirection(0);
    }
    else if (ghost->canMoveInDirection(ghost->SetDirection(1),*this, deltaTime)) {
        ghost->SetDirection(1);

    }
    else if (ghost->canMoveInDirection(ghost->SetDirection(2),*this, deltaTime)) {
        ghost->SetDirection(2);

    }
    else if (ghost->canMoveInDirection(ghost->SetDirection(2),*this, deltaTime)) {
        ghost->SetDirection(3);
    }


    // // 1. Update input buffer
    // ghost->update(deltaTime);
    //
    // // 2. Check if buffered direction is possible
    // int bufferedDir = ghost->getBufferedDirection();
    // if (bufferedDir != -1) {
    //     // Try buffered direction
    //     Vector2f bufferedPosition = ghost->calculatePositionInDirection(
    //         ghost->getPosition(), bufferedDir, deltaTime);
    //
    //     if (!PacmanWouldCollideWithWalls(*ghost, bufferedPosition)) {
    //         // Buffered direction is possible! Change direction
    //         ghost->setDirection(bufferedDir);
    //         ghost->clearBufferedDirection();
    //     } else {
    //         // Try position correction to allow the turn
    //         Vector2f correctedPos = tryPositionCorrection(
    //             ghost->getPosition(),
    //             ghost->getDirection(),
    //             bufferedDir,
    //             deltaTime
    //         );
    //
    //         if (correctedPos.x != ghost->getPosition().x ||
    //             correctedPos.y != ghost->getPosition().y) {
    //             // Correction was successful! Apply it and change direction
    //             ghost->setPosition(correctedPos);
    //             ghost->setDirection(bufferedDir);
    //             ghost->clearBufferedDirection();
    //         }
    //     }
    // }
    //
    // // 3. Move in current direction (or new if buffer worked)
    // Vector2f nextPosition = ghost->calculateNextPosition(deltaTime);
    //
    // if (!PacmanWouldCollideWithWalls(*ghost, nextPosition)) {
    //     ghost->applyMovement(nextPosition);
    // } else {
    //     // NEW: Can't move forward - find closest valid position to the wall
    //     Vector2f closestPos = findClosestPositionToWall(
    //         ghost->getPosition(),
    //         ghost->getDirection(),
    //         deltaTime
    //     );
    //
    //     if (closestPos.x != ghost->getPosition().x ||
    //         closestPos.y != ghost->getPosition().y) {
    //         ghost->setPosition(closestPos);
    //     }
    // }
    //
    // // 4. Notify observers
    // ghost->notifyObservers();
}

Vector2f World::findClosestPositionToWall(const Vector2f& currentPos,
                                          int direction,
                                          float deltaTime) const {
    // Binary search to find the closest position we can move to without colliding
    float moveAmount = m_pacman->getSpeed() * deltaTime;
    float minDistance = 0.0f;
    float maxDistance = moveAmount;
    float bestDistance = 0.0f;

    const int iterations = 10; // Precision of binary search

    for (int i = 0; i < iterations; ++i) {
        float testDistance = (minDistance + maxDistance) / 2.0f;
        Vector2f testPos = currentPos;

        // Apply movement in current direction
        switch (direction) {
            case 0: testPos.x -= testDistance; break; // Left
            case 1: testPos.y += testDistance; break; // Down
            case 2: testPos.x += testDistance; break; // Right
            case 3: testPos.y -= testDistance; break; // Up
        }

        testPos = m_pacman->CheckTunneling(testPos);

        // Check if this position would collide
        PacmanModel tempPacman = *m_pacman;
        tempPacman.setPosition(testPos);

        bool collides = false;

        for (const auto& wall : m_walls) {
            if (checkCollision(tempPacman, *wall)) {
                collides = true;
                break;
            }
        }

        for (const auto& door : m_doors) {
            if (checkCollision(tempPacman, *door)) {  // This should work if DoorModel properly inherits
                collides = true;
                break;
            }
        }

        if (collides) {
            // Too far, search closer
            maxDistance = testDistance;
        } else {
            // Valid position, try to get even closer
            bestDistance = testDistance;
            minDistance = testDistance;
        }
    }

    // Apply the best distance found
    Vector2f closestPos = currentPos;
    switch (direction) {
        case 0: closestPos.x -= bestDistance; break; // Left
        case 1: closestPos.y += bestDistance; break; // Down
        case 2: closestPos.x += bestDistance; break; // Right
        case 3: closestPos.y -= bestDistance; break; // Up
    }

    return m_pacman->CheckTunneling(closestPos);
}

Vector2f World::tryPositionCorrection(const Vector2f& currentPos,
                                      int currentDir,
                                      int bufferedDir,
                                      float deltaTime) const {
    // Only allow correction when turning perpendicular
    bool isPerpendicular = (currentDir == 0 || currentDir == 2) &&(bufferedDir == 1 || bufferedDir == 3) ||(currentDir == 1 || currentDir == 3) &&(bufferedDir == 0 || bufferedDir == 2);

    if (!isPerpendicular) {
        return currentPos; // No correction for non-perpendicular turns
    }

    // Maximum correction distance (one movement step)
    float maxCorrection = m_pacman->getSpeed() * deltaTime;

    // Try small corrections in the current direction
    for (float correction = 0.0f; correction <= maxCorrection; correction += maxCorrection / 10.0f) {
        Vector2f testPos = currentPos;

        // Apply correction in current direction
        switch (currentDir) {
        case 0: testPos.x -= correction; break; // Left
        case 1: testPos.y += correction; break; // Down
        case 2: testPos.x += correction; break; // Right
        case 3: testPos.y -= correction; break; // Up
        }

        // Test if buffered direction would work from this corrected position
        Vector2f bufferedTestPos = m_pacman->calculatePositionInDirection(
            testPos, bufferedDir, deltaTime);

        if (!PacmanWouldCollideWithWalls(*m_pacman, bufferedTestPos)) {
            return testPos; // This correction allows the turn!
        }
    }

    return currentPos; // No correction found
}

bool World::PacmanWouldCollideWithWalls(const PacmanModel& pacman, const Vector2f& newPosition) const {
    PacmanModel tempPacman = pacman;
    tempPacman.setPosition(newPosition);

    // Check collision with all walls - now works with template!
    for (const auto& wall : m_walls) {
        if (checkCollision(tempPacman, *wall)) {
            return true;
        }
    }

    // Check collision with all doors - also works!
    for (const auto& door : m_doors) {
        if (checkCollision(tempPacman, *door)) {
            return true;
        }
    }

    return false;
}

bool World::GhostWouldCollideWithWalls(const GhostModel& ghost, const Vector2f& newPosition) const {
    GhostModel tempghost = ghost;
    tempghost.setPosition(newPosition);

    // Check collision with all walls - now works with template!
    for (const auto& wall : m_walls) {
        if (checkCollision(tempghost, *wall)) {
            return true;
        }
    }

    // Check collision with all doors - if they are not escaping the house
    if (!ghost.GetMovingToStart()) {
        for (const auto& door : m_doors) {
            if (checkCollision(tempghost, *door)) {
                return true;
            }
        }
    }
    return false;
}
void World::handleCollectibleCollisions() {
    // Pacman vs Coins
    for (auto it = m_coins.begin(); it != m_coins.end(); ) {
        if (checkCollision(*m_pacman, **it)) {
            handlePacmanCoinCollision(**it);
            it = m_coins.erase(it);
        } else {
            ++it;
        }
    }

    // Pacman vs Fruits
    for (auto it = m_fruits.begin(); it != m_fruits.end(); ) {
        if (checkCollision(*m_pacman, **it)) {
            handlePacmanFruitCollision(**it);
            it = m_fruits.erase(it);
        } else {
            ++it;
        }
    }

    // Pacman vs Ghosts
    for (auto& ghost : m_ghosts) {
        if (checkCollision(*m_pacman, *ghost)) {
            handlePacmanGhostCollision(*m_pacman, *ghost);
        }
    }
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
        m_score->onPacManDied(); // Notify score about death
        pacman.loseLife(); // This now starts the death animation
    }
}

// Add this method to World class
void World::checkDeathAnimationState() {
    if (m_pacman->isDying() && m_pacman->isDeathAnimationComplete()) {
        // Death animation finished, now reset positions
        m_pacman->setPosition(m_pacman->getSpawnPoint());
        m_pacman->resetDeathAnimation();

        for (auto& ghost : m_ghosts) {
            ghost->respawn();
        }
    }
}

void World::handlePacmanFruitCollision(FruitModel& fruit) {
    m_score->onFruitCollected();
    fruit.collect();
    for (auto& ghost : m_ghosts) {
        ghost->setScared(true);
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



//todo add funciton so ghosts go to start position and than toggel their own following path
void World::handleGhostMovement(const std::shared_ptr<GhostModel>& ghost, float deltaTime){
    // if (ghost.isRed) {
    //     redghostmovement();
    // }
    // if (ghost.isBlue) {
    //     Blueghostmovement();
    // }
    // if (ghost.isOrange) {
    //     Orangeghostmovement();
    // }
    // if (ghost.isPink) {
    //     Pinkghostmovement();
    // }

}
//todo add prediction for ghosts check in how many ways the ghost can do a correct movement if that way is more than 2 (right and left) trigger random choosing and repeat


void World::advanceToNextLevel() {
    // Increment level
    if (LEVEL < 3) {
        LEVEL++;
    }

    // Clear all entities EXCEPT Pacman
    m_walls.clear();
    m_coins.clear();
    m_fruits.clear();
    m_ghosts.clear();

    // Reset Pacman position to spawn
    if (m_pacman) {
        m_pacman->setPosition(m_pacman->getSpawnPoint());
    }

    // Clear all views EXCEPT PacmanView using polymorphism
    m_factory->clearNonPacmanViews();

    // Load the appropriate map based on level
    std::string mapFile = "assets/maps/map1.txt";
    if (LEVEL == 2) {
        mapFile = "assets/maps/map2.txt";
    } else if (LEVEL == 3) {
        mapFile = "assets/maps/map3.txt";
    }

    if (m_mapModel.loadFromFile(mapFile)) {
        createEntitiesFromMap();
    }

    // Make ghosts harder each level
    for (const auto& ghost: m_ghosts) {
        ghost->SetBaseSpeed(ghost->GetBaseSpeed() * LEVEL);
        ghost->SetScaredTimerInc(LEVEL);
    }

    // Reset score chain for new level
    m_score->resetCoinChain();
}
