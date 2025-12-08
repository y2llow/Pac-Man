#include "world/World.h"

#include "core/Random.h"
#include "entities/WallModel.h"
#include "entities/CoinModel.h"
#include "entities/PacmanModel.h"
#include "entities/GhostModel.h"
#include "entities/FruitModel.h"

#include <algorithm>
#include <cmath>
#include <iostream>

World::World(LogicFactory& factory)
    : m_factory(&factory) {
    m_score = std::make_unique<Score>();
}

void World::initialize() {
    if (m_mapModel.loadFromFile("assets/maps/map2.txt")) {
        createEntitiesFromMap();
        attachScoreObservers();
    }
}

void World::createEntitiesFromMap() {
    //todo use -1,1 here for teh coordinates for camera instead of the sez conversions
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

        for (auto& ghost : m_ghosts) {
            // Ghost moves to starting position outside door
            if (!ghost->GetOutsideStart() && ghost->GetMovingToStart()) {
                ghost->MoveToStartPosition(m_startPosition, deltaTime);
            }
            // Ghost moving left and right inside their house
            else if (!ghost->GetOutsideStart()) {
                TrappedGhostMovement(ghost, deltaTime);
            }
            // Scared ghost movement
            else if (ghost->isScared()) {
                if (ghost->willCrossIntersection(*this, deltaTime)) {
                    Vector2f intersectionPoint = ghost->getIntersectionPoint(*this, deltaTime);
                    ghost->setPosition(intersectionPoint);
                    ScaredGhostMovement(ghost, deltaTime);
                } else {
                    standardGhostMovement(ghost, deltaTime);
                }
            }

            else {
                if (ghost->willCrossIntersection(*this, deltaTime)) {
                    Vector2f intersectionPoint = ghost->getIntersectionPoint(*this, deltaTime);
                    ghost->setPosition(intersectionPoint);

                    // Gebruik het type om de juiste movement te kiezen
                    switch (ghost->getType()) {
                        case GhostType::RED:
                            RedGhostMovement(ghost, deltaTime);
                            break;
                        case GhostType::BLUE:
                            BlueGhostMovement(ghost, deltaTime);
                            break;
                        case GhostType::ORANGE:
                            BlueGhostMovement(ghost, deltaTime);  // Orange gebruikt ook Blue logic volgens je specificatie
                            break;
                        case GhostType::PINK:
                            PinkGhostMovement(ghost, deltaTime);
                            break;
                        default:
                            // Fallback naar red movement
                            standardGhostMovement(ghost, deltaTime);
                            break;
                    }
                } else {
                    standardGhostMovement(ghost, deltaTime);
                }
            }
            ghost->update(deltaTime);
        }

        // DERDE: Collectible collisions (na movement)
        handleCollectibleCollisions();

        // Check for level completion
        if (areAllCoinsCollected()) {
            m_score->onLevelCleared();
        }
    } else {
        m_pacman->update(deltaTime);
    }

    // Always update these
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
bool World::willTunnel(const std::shared_ptr<GhostModel>& ghost, float deltaTime) const {
    Vector2f startPos = ghost->getPosition();
    Vector2f nextPos = ghost->calculateNextPosition(deltaTime);

    // Check for tunneling first
    float distance = std::abs(nextPos.x - startPos.x) + std::abs(nextPos.y - startPos.y);
    float moveAmount = ghost->GetSpeed() * deltaTime;

    bool isTunneling = distance > moveAmount * 1.5f;

    if (isTunneling) {
        // Direct tunneling - geen intersection checks
        if (!GhostWouldCollideWithWalls(*ghost, nextPos)) {
            ghost->setPosition(nextPos);
        }
        ghost->notifyObservers();
        return true;
    }
    return false;

}

void World::TrappedGhostMovement(const std::shared_ptr<GhostModel>& ghost,float deltaTime) const {
    if (ghost->canMoveInDirection(ghost->getDirection(),*this, deltaTime)) {}
    else if (ghost->canMoveInDirection(0,*this, deltaTime)) {
        ghost->SetDirection(0);
    }
    else if (ghost->canMoveInDirection(1,*this, deltaTime)) {
        ghost->SetDirection(1);
    }
    else if (ghost->canMoveInDirection(2,*this, deltaTime)) {
        ghost->SetDirection(2);
    }
    else if (ghost->canMoveInDirection(3,*this, deltaTime)) {
        ghost->SetDirection(3);
    }
    ghost->updateMovement(deltaTime);
}
void World::standardGhostMovement(const std::shared_ptr<GhostModel>& ghost, float deltaTime) {
    // Geen intersection - normale movement
    Vector2f nextPosition = ghost->calculateNextPosition(deltaTime);

    if (!GhostWouldCollideWithWalls(*ghost, nextPosition)) {
        ghost->setPosition(nextPosition);
    } else {
        // Kan niet vooruit - vind dichtste positie tot muur
        Vector2f closestPos = findClosestPositionToWallForGhost(
            ghost->getPosition(),
            ghost->getDirection(),
            deltaTime,
            *ghost
        );

        if (closestPos.x != ghost->getPosition().x ||
            closestPos.y != ghost->getPosition().y) {
            ghost->setPosition(closestPos);
            } else {
                // Volledig vast - kies nieuwe richting
                std::vector<int> validDirs = ghost->getValidDirectionsAtIntersection(*this, deltaTime);
                if (!validDirs.empty()) {
                    auto& rng = Random::getInstance();
                    int newDirection = rng.getRandomElement(validDirs);

                    // std::cout << "*** STUCK - Forcing direction: " << newDirection << " ***" << std::endl;

                    ghost->SetDirection(newDirection);

                    nextPosition = ghost->calculateNextPosition(deltaTime);
                    if (!GhostWouldCollideWithWalls(*ghost, nextPosition)) {
                        ghost->setPosition(nextPosition);
                    }
                }
            }
    }
}

void World::RedGhostMovement(const std::shared_ptr<GhostModel>& ghost, float deltaTime) {
    if (willTunnel(ghost, deltaTime))
        return;

    // intersection logic
    bool crossingIntersection = ghost->willCrossIntersection(*this, deltaTime);

    if (crossingIntersection) {
        // Beweeg naar het intersection punt
        Vector2f intersectionPoint = ghost->getIntersectionPoint(*this, deltaTime);
        ghost->setPosition(intersectionPoint);

        // Nu zijn we bij de intersection - check valid directions
        std::vector<int> validDirs = ghost->getValidDirectionsAtIntersection(*this, deltaTime);

        if (!validDirs.empty()) {
            auto& rng = Random::getInstance();
            bool willChangeDirection = rng.getBool(0.5);

            if (willChangeDirection) {
                int chosenDirection = rng.getRandomElement(validDirs);

                while (chosenDirection == ghost->getDirection()) {
                    chosenDirection = rng.getRandomElement(validDirs);
                }
                ghost->SetDirection(chosenDirection);
            } else {
                bool currentDirValid = false;
                for (int dir : validDirs) {
                    if (dir == ghost->getDirection()) {
                        currentDirValid = true;
                        break;
                    }
                }
                if (!currentDirValid) {
                    int newDirection = rng.getRandomElement(validDirs);
                    ghost->SetDirection(newDirection);
                }
            }
        }
     }

    standardGhostMovement(ghost, deltaTime);

}

void World::BlueGhostMovement(const std::shared_ptr<GhostModel>& ghost, float deltaTime) {
    // Two ghosts, when in chasing mode, should always move in the direction that Pac-Man is
    // currently facing. Concretely, it should move in the direction that minizes the Manhattan
    // distance to the locations “in front of” Pac-Man. For this, look at the viable actions from
    // the set {up, down, left, right} and compute for each viable action what the Manhattan
    // distance to Pac-Man would have been if the ghost had taken one step in that particular
    // direction. Ties between the best actions are broken at random.

    // todo only do this on intersections
    int pacmanDirection = getPacman()->getDirection();
    Vector2f pacmanPos = getPacman()->getPosition();

    // Calculate the position "in front of" Pac-Man (multiple steps ahead for better targeting)
    Vector2f targetPos = pacmanPos;
    float lookAheadDistance = 0.3f; // How far ahead to look (adjust as needed)

    switch (pacmanDirection) {
    case 0: targetPos.x -= lookAheadDistance; break; // Left
    case 1: targetPos.y += lookAheadDistance; break; // Down
    case 2: targetPos.x += lookAheadDistance; break; // Right
    case 3: targetPos.y -= lookAheadDistance; break; // Up
    }

    // Get all viable directions (0=left, 1=down, 2=right, 3=up)
    std::vector<int> viableDirections;
    std::vector<float> distances;
    float bestDistance = std::numeric_limits<float>::max();

    for (int dir = 0; dir < 4; dir++) {
        // Calculate where ghost would be if it moved in this direction
        Vector2f ghostNextPos = ghost->calculateNextPositionInDirection(
            ghost->getPosition(), dir, deltaTime);

        // Check if this move is viable (doesn't collide with walls)
        if (GhostWouldCollideWithWalls(*ghost, ghostNextPos)) {
            continue; // Skip invalid directions
        }

        // Calculate Manhattan distance from this potential position to target
        float dist = getManhattanDistance(ghostNextPos, targetPos);

        viableDirections.push_back(dir);
        distances.push_back(dist);

        if (dist < bestDistance) {
            bestDistance = dist;
        }
    }

    // If no viable directions, keep current direction (shouldn't happen)
    if (viableDirections.empty()) {
        TrappedGhostMovement(ghost, deltaTime);
        return;
    }

    // Find all directions that have the best distance (for tie-breaking)
    std::vector<int> bestDirections;
    for (size_t i = 0; i < viableDirections.size(); i++) {
        if (std::abs(distances[i] - bestDistance) < 0.001f) { // Float comparison with epsilon
            bestDirections.push_back(viableDirections[i]);
        }
    }

    // Choose direction: if tie, break randomly
    int chosenDirection;
    if (bestDirections.size() > 1) {
        // Tie - break randomly
        auto& rng = Random::getInstance();
        chosenDirection = rng.getRandomElement(bestDirections);
    } else {
        chosenDirection = bestDirections[0];
    }

    // Set the chosen direction
    ghost->SetDirection(chosenDirection);

    // Now use the standard predictive movement with the new direction
    standardGhostMovement(ghost, deltaTime);
}

void World::ScaredGhostMovement(const std::shared_ptr<GhostModel>& ghost, float deltaTime) {
    // Only make decisions at intersections
    if (ghost->isAtIntersection(*this, deltaTime)) {
        Vector2f pacmanPos = getPacman()->getPosition();

        // Get all viable directions (excluding going back the way it came)
        std::vector<int> viableDirections = ghost->getValidDirectionsAtIntersection(*this, deltaTime);

        if (viableDirections.empty()) {
            TrappedGhostMovement(ghost, deltaTime);
            return;
        }

        // Find direction that MAXIMIZES Manhattan distance to Pac-Man
        std::vector<int> bestDirections;
        float bestDistance = std::numeric_limits<float>::lowest();  // Kleinst mogelijke float waarde

        for (int dir : viableDirections) {
            // Calculate where ghost would be after moving one step in this direction
            Vector2f ghostNextPos = ghost->calculateNextPositionInDirection(
                ghost->getPosition(), dir, deltaTime);

            // Calculate Manhattan distance to Pac-Man
            float dist = getManhattanDistance(ghostNextPos, pacmanPos);

            if (dist > bestDistance + 0.0001f) { // Slight tolerance for floating point
                bestDistance = dist;
                bestDirections.clear();
                bestDirections.push_back(dir);
            } else if (std::abs(dist - bestDistance) < 0.0001f) {
                // Tie - add to best directions
                bestDirections.push_back(dir);
            }
        }

        // Choose direction: if tie, break randomly
        int chosenDirection;
        if (bestDirections.size() > 1) {
            auto& rng = Random::getInstance();
            chosenDirection = rng.getRandomElement(bestDirections);
        } else {
            chosenDirection = bestDirections[0];
        }

        // Set the chosen direction
        ghost->SetDirection(chosenDirection);
    }

    // Always move in the current direction
    standardGhostMovement(ghost, deltaTime);
}
float World::getManhattanDistance(Vector2f pos1, Vector2f pos2) {
    float dx = std::abs(pos1.x - pos2.x);
    float dy = std::abs(pos1.y - pos2.y);

    // Account for world wrap-around (tunnels)
    // The world width is 2.0 (from -1 to 1)
    // const float WORLD_WIDTH = 2.0f;
    //
    // // Check if going through tunnel might be shorter horizontally
    // float dx_tunnel = WORLD_WIDTH - dx;
    // if (dx_tunnel < dx) {
    //     dx = dx_tunnel;
    // }

    return dx + dy;
}

void World::PinkGhostMovement(const std::shared_ptr<GhostModel>& ghost, float deltaTime) {
    // The last ghost, when in chasing mode, moves after Pac-Man effectively chasing him by
    // trying to minimize the Manhattan distance to its location.

    // Only make decisions at intersections
    if (ghost->isAtIntersection(*this, deltaTime)) {
        Vector2f pacmanPos = getPacman()->getPosition();

        // Get all viable directions (excluding going back the way it came)
        std::vector<int> viableDirections = ghost->getValidDirectionsAtIntersection(*this, deltaTime);

        if (viableDirections.empty()) {
            TrappedGhostMovement(ghost, deltaTime);
            return;
        }

        // Find direction that minimizes Manhattan distance to Pac-Man
        std::vector<int> bestDirections;
        float bestDistance = std::numeric_limits<float>::max();

        for (int dir : viableDirections) {
            // Calculate where ghost would be after moving one step in this direction
            Vector2f ghostNextPos = ghost->calculateNextPositionInDirection(
                ghost->getPosition(), dir, deltaTime);

            // Calculate Manhattan distance to Pac-Man
            float dist = getManhattanDistance(ghostNextPos, pacmanPos);

            if (dist < bestDistance - 0.0001f) { // Slight tolerance for floating point
                bestDistance = dist;
                bestDirections.clear();
                bestDirections.push_back(dir);
            } else if (std::abs(dist - bestDistance) < 0.0001f) {
                // Tie - add to best directions
                bestDirections.push_back(dir);
            }
        }

        // Choose direction: if tie, break randomly
        int chosenDirection;
        if (bestDirections.size() > 1) {
            auto& rng = Random::getInstance();
            chosenDirection = rng.getRandomElement(bestDirections);
        } else {
            chosenDirection = bestDirections[0];
        }

        // Set the chosen direction
        ghost->SetDirection(chosenDirection);
    }

    // Always move in the current direction
    standardGhostMovement(ghost, deltaTime);
    // ghost->updateMovement( deltaTime);

}

Vector2f World::findClosestPositionToWallForGhost(const Vector2f& currentPos, int direction, float deltaTime, GhostModel& ghost) const {
    float moveAmount = ghost.GetSpeed() * deltaTime;
    float minDistance = 0.0f;
    float maxDistance = moveAmount;
    float bestDistance = 0.0f;

    const int iterations = 10;

    for (int i = 0; i < iterations; ++i) {
        float testDistance = (minDistance + maxDistance) / 2.0f;
        Vector2f testPos = currentPos;

        switch (direction) {
        case 0: testPos.x -= testDistance; break;
        case 1: testPos.y += testDistance; break;
        case 2: testPos.x += testDistance; break;
        case 3: testPos.y -= testDistance; break;
        }

        testPos = ghost.checkTunneling(testPos);

        GhostModel tempGhost = ghost;
        tempGhost.setPosition(testPos);

        bool collides = false;
        for (const auto& wall : m_walls) {
            if (checkCollision(tempGhost, *wall)) {
                collides = true;
                break;
            }
        }

        if (!ghost.GetMovingToStart()) {
            for (const auto& door : m_doors) {
                if (checkCollision(tempGhost, *door)) {
                    collides = true;
                    break;
                }
            }
        }

        if (collides) {
            maxDistance = testDistance;
        } else {
            bestDistance = testDistance;
            minDistance = testDistance;
        }
    }

    Vector2f closestPos = currentPos;
    switch (direction) {
    case 0: closestPos.x -= bestDistance; break;
    case 1: closestPos.y += bestDistance; break;
    case 2: closestPos.x += bestDistance; break;
    case 3: closestPos.y -= bestDistance; break;
    }

    return ghost.checkTunneling(closestPos);
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

Vector2f World::tryPositionCorrection(const Vector2f& currentPos,int currentDir,int bufferedDir,float deltaTime) const {
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
    if (newPosition.x > 1 || newPosition.y > 1 || newPosition.x < -1 || newPosition.y < -1) { return false; }
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
    if (ghost.GetOutsideStart()) {
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
    coin.collect();
}

void World::handlePacmanGhostCollision(PacmanModel& pacman, GhostModel& ghost) {
    if (ghost.isScared() && !ghost.wasEaten()) {
        // todo add this to observers
        m_score->onGhostEaten();  // Score ONCE at collision
        ghost.SetWasEaten(true);   // Mark as eaten
        ghost.respawn();           // This will notify observers for view updates
    } else if (!ghost.isScared()) {
        pacman.loseLife();  // This calls startDeathAnimation, which notifies
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
    // m_score->onFruitCollected();
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
    std::string mapFile;
    if (LEVEL == 2) {
        mapFile = "assets/maps/map2.txt";
    } else if (LEVEL == 3) {
        mapFile = "assets/maps/map3.txt";
    }

    if (m_mapModel.loadFromFile(mapFile)) {
        createEntitiesFromMap();
        attachScoreObservers();
    }

    // Make ghosts harder each level
    for (const auto& ghost: m_ghosts) {
        ghost->SetBaseSpeed(ghost->GetBaseSpeed() * LEVEL);
        ghost->SetScaredTimerInc(LEVEL);
    }

    // Reset score chain for new level
    m_score->resetCoinChain();
}

void World::attachScoreObservers() {
    // Coins - use capture by value for safety
    for (auto& coin : m_coins) {
        // Store a weak reference to check validity
        std::weak_ptr<CoinModel> weakCoin = coin;

        coin->attachObserver([this, weakCoin]() {
            auto coinPtr = weakCoin.lock();
            if (!coinPtr || !m_score) return;

            // Only award score ONCE when just collected
            if (coinPtr->isCollected() && !coinPtr->getScoreAwarded()) {
                m_score->onCoinCollected();
                // Note: m_scoreAwarded is set in collect() method
            }
        });
    }

    // Fruits
    for (auto& fruit : m_fruits) {
        std::weak_ptr<FruitModel> weakFruit = fruit;

        fruit->attachObserver([this, weakFruit]() {
            auto fruitPtr = weakFruit.lock();
            if (!fruitPtr || !m_score) return;

            if (fruitPtr->isCollected() && !fruitPtr->getScoreAwarded()) {
                m_score->onFruitCollected();
            }
        });
    }

    // Ghosts - award score when eaten (collision while scared)
    for (auto& ghost : m_ghosts) {
        std::weak_ptr weakGhost = ghost;

        ghost->attachObserver([this, weakGhost]() {
            auto ghostPtr = weakGhost.lock();
            if (!ghostPtr || !m_score) return;

            // Ghost was just eaten if it's respawning and wasn't scored yet
            // This is handled in collision, so we don't score here
            // Observers on ghosts are mainly for view updates
        });
    }

    // Pacman - award death penalty ONCE when animation starts
    if (m_pacman) {
        m_pacman->attachObserver([this]() {
            if (!m_score || !m_pacman) return;

            // Only score when death animation JUST started
            if (m_pacman->isDying() &&
                !m_pacman->isDeathAnimationComplete() &&
                !m_pacman->getDeathScoreAwarded()) {

                m_score->onPacManDied();
                m_pacman->setDeathScoreAwarded(true);
            }
        });
    }
}