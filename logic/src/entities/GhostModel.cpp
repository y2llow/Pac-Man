#include "entities/GhostModel.h"

#include "core/Random.h"
#include "world/World.h"

#include <utility>

GhostModel::GhostModel(const Vector2f& position, const Vector2f& size, std::string textureId)
    : m_position(position), m_textureId(std::move(textureId)), m_size(size), m_spawnPoint(position) {
}

void GhostModel::update(float deltaTime) {
    float currentSpeed = GHOST_SPEED;  // Store base speed separately

    // Update scared timer
    if (m_scared) {
        m_scaredTimer -= deltaTime * m_scaredTimerInc;
        currentSpeed = GHOST_SPEED * 0.5f;  // 50% speed when scared

        if (m_scaredTimer <= 0) {
            m_scared = false;
            m_scaredTimer = 0.0f;
        }
    }

    m_speed = currentSpeed;  // Set the actual speed used for movement
    m_position = checkTunneling(m_position);
    notifyObservers();
}

void GhostModel::setPosition(const Vector2f& position) {
    m_position = position;
    notifyObservers();
}

void GhostModel::setScared(bool scared) {
    if (scared && !m_scared) {
        // Just became scared - reverse direction
        reverseDirection();
    }
    m_scared = scared;
    if (scared) {
        m_scaredTimer = 10.0f; // 10 seconds scared time
    }
}

void GhostModel::respawn() {
    m_position = m_spawnPoint;
    m_scared = false;
    m_scaredTimer = 0.0f;
    m_canMove = true;
    m_outsideStart = false;
    m_MovingToStart = false;
    resetMovingToStartTimer(3);
}
void GhostModel::resetMovingToStartTimer(float TimeWaiting) {}
void RedGhostModel::resetMovingToStartTimer(float TimeWaiting) {m_MovingToStartTimer =  TimeWaiting;}
void BlueGhostModel::resetMovingToStartTimer(float TimeWaiting) {m_MovingToStartTimer =  TimeWaiting;}
void OrangeGhostModel::resetMovingToStartTimer(float TimeWaiting) {m_MovingToStartTimer =  TimeWaiting;}
void PinkGhostModel::resetMovingToStartTimer(float TimeWaiting) {m_MovingToStartTimer =  TimeWaiting;}

void GhostModel::updateMovement(float deltaTime) {
    if (!m_canMove) return;

    switch (m_direction) {
        case 0: m_position.x -= m_speed * deltaTime; break; // left
        case 1: m_position.y += m_speed * deltaTime; break; // down
        case 2: m_position.x += m_speed * deltaTime; break; // right
        case 3: m_position.y -= m_speed * deltaTime; break; // up
    }
}

void GhostModel::reverseDirection() {
    // Reverse current direction
    switch (m_direction) {
        case 0: m_direction = 2; break; // left -> right
        case 1: m_direction = 3; break; // down -> up
        case 2: m_direction = 0; break; // right -> left
        case 3: m_direction = 1; break; // up -> down
    }
}

Vector2f GhostModel::checkTunneling(Vector2f position) const {
    float edge = 1.0f + m_size.x / 2.0f;
    if (position.x < -edge) {
        position.x = edge;
    } else if (position.x > edge) {
        position.x = -edge;
    }
    return position;
}

//todo specific ai movement
void GhostModel::GhostAIMovement() {

}

void GhostModel::handleWorldBehavior(World& world) {

}

// Red Ghost Implementation - One of the ghosts, when in chasing mode, should always be locked to moving in a
// fixed direction (either always up, down, right or left). If a ghost reaches a corner or
// intersection it will reconsider which direction it will be locked to. In particular, with
// probability p = 0.5, the ghost will lock to a random direction (that is viable).
void RedGhostModel::updateMovement(float deltaTime) {
    m_MovingToStartTimer -= deltaTime;
       if (m_MovingToStartTimer <= 0) {
           SetMovingToStart(true);
       }
    GhostModel::updateMovement(deltaTime);

}

void RedGhostModel::GhostAIMovement() {
    Random::getInstance();

}

void RedGhostModel::handleWorldBehavior(World& world)  {
    world.handleRedGhostLogic(*this);  // *this is correct here!
}




// Blue Ghost Implementation - Moves right
void BlueGhostModel::updateMovement(float deltaTime) {
    m_MovingToStartTimer -= deltaTime;
    if (m_MovingToStartTimer <= 0) {
        SetMovingToStart(true);
    }
    GhostModel::updateMovement(deltaTime);
}
void BlueGhostModel::GhostAIMovement() {

}

void BlueGhostModel::handleWorldBehavior(World& world)  {

}

// Orange Ghost Implementation - Moves down
void OrangeGhostModel::updateMovement(float deltaTime) {
    m_MovingToStartTimer -= deltaTime;
    if (m_MovingToStartTimer <= 0) {
        SetMovingToStart(true);
    }
    GhostModel::updateMovement(deltaTime);
}
void OrangeGhostModel::GhostAIMovement() {

}

void OrangeGhostModel::handleWorldBehavior(World& world)  {

}

// Pink Ghost Implementation - Moves up
void PinkGhostModel::updateMovement(float deltaTime) {
    m_MovingToStartTimer -= deltaTime;
    if (m_MovingToStartTimer <= 0) {
        SetMovingToStart(true);
    }
    GhostModel::updateMovement(deltaTime);
}

void PinkGhostModel::GhostAIMovement() {

}

void PinkGhostModel::handleWorldBehavior(World& world)  {

}

void GhostModel::MoveToStartPosition(Vector2f startposition, float deltaTime ) {
    Vector2f GhostPosition = this->getPosition();
    if (GhostPosition.x < startposition.x) {
        m_direction = 2;
    }
    if (GhostPosition.x > startposition.x) {
        m_direction = 0;
    }
    if (std::abs(GhostPosition.x - startposition.x) < m_speed * deltaTime && GhostPosition.y < startposition.y ) {
        m_direction = 1;
    }
    if (std::abs(GhostPosition.x - startposition.x) < m_speed * deltaTime && GhostPosition.y > startposition.y ) {
        m_direction = 3;
    }
    if (std::abs(GhostPosition.x - startposition.x) < m_speed * deltaTime && std::abs(GhostPosition.y - startposition.y) < m_speed * deltaTime) {
        SetOutsideStart(true);
        SetMovingToStart(false);
    }
}

Vector2f GhostModel::calculateNextPosition(float deltaTime) const {
    Vector2f newPosition = m_position;
    float moveAmount = m_speed * deltaTime;

    switch (m_direction) {
    case 0: newPosition.x -= moveAmount; break; // Left
    case 1: newPosition.y += moveAmount; break; // Down
    case 2: newPosition.x += moveAmount; break; // Right
    case 3: newPosition.y -= moveAmount; break; // Up
    }

    return checkTunneling(newPosition);
}

bool GhostModel::canMoveInDirection(int direction, const World& world, float deltaTime) const {
    Vector2f testPosition = calculateNextPositionInDirection(m_position, direction, deltaTime); // 60fps
    return !world.GhostWouldCollideWithWalls(*this, testPosition);
}

Vector2f GhostModel::calculateNextPositionInDirection(const Vector2f& startPos, int direction, float deltaTime) const {
        Vector2f newPosition = startPos;
        float moveAmount = m_speed * deltaTime;

        switch (direction) {
        case 0: newPosition.x -= moveAmount; break; // Left
        case 1: newPosition.y += moveAmount; break; // Down
        case 2: newPosition.x += moveAmount; break; // Right
        case 3: newPosition.y -= moveAmount; break; // Up
        }

        return checkTunneling(newPosition);
}



// #include "entities/GhostModel.h"
// #include "entities/PacmanModel.h"
// #include "world/World.h"
// #include <utility>
// #include <random>
//
// GhostModel::GhostModel(const Vector2f& position, const Vector2f& size, std::string textureId)
//     : m_position(position), m_textureId(std::move(textureId)), m_size(size), m_spawnPoint(position) {
// }
//
// void GhostModel::update(float deltaTime) {
//     // Handle spawn delay
//     // if (m_spawnDelay > 0) {
//     //     m_spawnDelay -= deltaTime;
//     //     m_canMove = (m_spawnDelay <= 0);
//     //     m_inCenter = (m_spawnDelay > 0);
//     // }
//
//     // Update scared timer
//     if (m_scared) {
//         m_scaredTimer -= deltaTime;
//         if (m_scaredTimer <= 0) {
//             m_scared = false;
//             m_scaredTimer = 0.0f;
//         }
//     }
//
//     m_position = checkTunneling(m_position);
//     notifyObservers();
// }
//
// void GhostModel::setPosition(const Vector2f& position) {
//     m_position = position;
//     notifyObservers();
// }
//
// void GhostModel::setScared(bool scared) {
//     if (scared && !m_scared) {
//         // Just became scared - reverse direction
//         reverseDirection();
//     }
//     m_scared = scared;
//     if (scared) {
//         m_scaredTimer = 10.0f; // 10 seconds scared time
//     }
// }
//
// void GhostModel::respawn() {
//     m_position = m_spawnPoint;
//     m_scared = false;
//     m_scaredTimer = 0.0f;
//     m_inCenter = true;
//     m_canMove = false;
// }
//
// void GhostModel::updateMovement(float deltaTime, std::shared_ptr<PacmanModel> pacman, const World& world) {
//     if (!m_canMove) return;
//
//     Vector2f targetDirection = calculateChaseDirection(world, pacman);
//
//     // Move in the chosen direction
//     float currentSpeed = m_scared ? m_scaredSpeed : m_speed;
//     Vector2f newPosition = m_position;
//
//     switch (m_direction) {
//         case 0: newPosition.x -= currentSpeed * deltaTime; break; // left
//         case 1: newPosition.y += currentSpeed * deltaTime; break; // down
//         case 2: newPosition.x += currentSpeed * deltaTime; break; // right
//         case 3: newPosition.y -= currentSpeed * deltaTime; break; // up
//     }
//
//     // Check collision with walls
//     if (isValidMove(newPosition, world)) {
//         m_position = newPosition;
//     } else {
//         // Hit a wall - choose new direction
//         auto possibleDirs = getPossibleDirections(world);
//         if (!possibleDirs.empty()) {
//             // Simple random direction change when hitting wall
//             static std::random_device rd;
//             static std::mt19937 gen(rd());
//             std::uniform_int_distribution<> dis(0, possibleDirs.size() - 1);
//             m_direction = possibleDirs[dis(gen)];
//         }
//     }
// }
//
// void GhostModel::reverseDirection() {
//     // Reverse current direction
//     switch (m_direction) {
//         case 0: m_direction = 2; break; // left -> right
//         case 1: m_direction = 3; break; // down -> up
//         case 2: m_direction = 0; break; // right -> left
//         case 3: m_direction = 1; break; // up -> down
//     }
// }
//
// Vector2f GhostModel::checkTunneling(Vector2f position) {
//     float edge = 1.0f + m_size.x / 2.0f;
//     if (position.x < -edge) {
//         position.x = edge;
//     } else if (position.x > edge) {
//         position.x = -edge;
//     }
//     return position;
// }
//
// std::vector<int> GhostModel::getPossibleDirections(const World& world) const {
//     std::vector<int> possibleDirs;
//
//     // Test all 4 directions
//     for (int dir = 0; dir < 4; dir++) {
//         Vector2f testPos = m_position;
//         switch (dir) {
//             case 0: testPos.x -= 0.1f; break; // left
//             case 1: testPos.y += 0.1f; break; // down
//             case 2: testPos.x += 0.1f; break; // right
//             case 3: testPos.y -= 0.1f; break; // up
//         }
//
//         if (isValidMove(testPos, world)) {
//             possibleDirs.push_back(dir);
//         }
//     }
//
//     return possibleDirs;
// }
//
// bool GhostModel::isValidMove(const Vector2f& newPos, const World& world) const {
//     // This should check collision with walls in the world
//     // For now, return true (you'll need to implement proper collision detection)
//     return true;
// }
//
// // Red Ghost Implementation - Fixed direction with random changes
// void RedGhostModel::updateMovement(float deltaTime, std::shared_ptr<PacmanModel> pacman, const World& world) {
//     if (!m_canMove) return;
//
//     m_directionChangeTimer += deltaTime;
//
//     // Change locked direction randomly every 2 seconds
//     if (m_directionChangeTimer >= 0.1f) {
//         auto possibleDirs = getPossibleDirections(world);
//         if (!possibleDirs.empty()) {
//             static std::random_device rd;
//             static std::mt19937 gen(rd());
//             std::uniform_int_distribution<> dis(0, possibleDirs.size() - 1);
//             m_lockedDirection = possibleDirs[dis(gen)];
//         }
//         m_directionChangeTimer = 0.0f;
//     }
//
//     // Use locked direction if set, otherwise use normal AI
//     if (m_lockedDirection != -1) {
//         m_direction = m_lockedDirection;
//     }
//
//     GhostModel::updateMovement(deltaTime, pacman, world);
// }
//
// Vector2f RedGhostModel::calculateChaseDirection(const World& world, std::shared_ptr<PacmanModel> pacman) {
//     // Fixed direction ghost - direction is handled in updateMovement
//     return Vector2f(0, 0);
// }
//
// // Blue Ghost Implementation - Chase Pac-Man's facing direction
// void BlueGhostModel::updateMovement(float deltaTime, std::shared_ptr<PacmanModel> pacman, const World& world) {
//     GhostModel::updateMovement(deltaTime, pacman, world);
// }
//
// Vector2f BlueGhostModel::calculateChaseDirection(const World& world, std::shared_ptr<PacmanModel> pacman) {
//     if (!pacman) return Vector2f(0, 0);
//
//     // Get position in front of Pac-Man based on his direction
//     Vector2f targetPos = pacman->getPosition();
//     int pacmanDir = pacman->getDirection();
//
//     switch (pacmanDir) {
//         case 0: targetPos.x -= 0.3f; break; // left
//         case 1: targetPos.y += 0.3f; break; // down
//         case 2: targetPos.x += 0.3f; break; // right
//         case 3: targetPos.y -= 0.3f; break; // up
//     }
//
//     // Find direction that minimizes Manhattan distance to target
//     auto possibleDirs = getPossibleDirections(world);
//     if (possibleDirs.empty()) return Vector2f(0, 0);
//
//     int bestDir = possibleDirs[0];
//     float bestDistance = std::numeric_limits<float>::max();
//
//     for (int dir : possibleDirs) {
//         Vector2f testPos = m_position;
//         switch (dir) {
//             case 0: testPos.x -= 0.1f; break;
//             case 1: testPos.y += 0.1f; break;
//             case 2: testPos.x += 0.1f; break;
//             case 3: testPos.y -= 0.1f; break;
//         }
//
//         float distance = std::abs(testPos.x - targetPos.x) + std::abs(testPos.y - targetPos.y);
//         if (distance < bestDistance) {
//             bestDistance = distance;
//             bestDir = dir;
//         }
//     }
//
//     m_direction = bestDir;
//     return Vector2f(0, 0);
// }
//
// Vector2f OrangeGhostModel::calculateChaseDirection(const World& world, std::shared_ptr<PacmanModel> pacman) {
//     if (!pacman) return Vector2f(0, 0);
//
//     // Get position in front of Pac-Man based on his direction
//     Vector2f targetPos = pacman->getPosition();
//     int pacmanDir = pacman->getDirection();
//
//     switch (pacmanDir) {
//     case 0: targetPos.x -= 0.3f; break; // left
//     case 1: targetPos.y += 0.3f; break; // down
//     case 2: targetPos.x += 0.3f; break; // right
//     case 3: targetPos.y -= 0.3f; break; // up
//     }
//
//     // Find direction that minimizes Manhattan distance to target
//     auto possibleDirs = getPossibleDirections(world);
//     if (possibleDirs.empty()) return Vector2f(0, 0);
//
//     int bestDir = possibleDirs[0];
//     float bestDistance = std::numeric_limits<float>::max();
//
//     for (int dir : possibleDirs) {
//         Vector2f testPos = m_position;
//         switch (dir) {
//         case 0: testPos.x -= 0.1f; break;
//         case 1: testPos.y += 0.1f; break;
//         case 2: testPos.x += 0.1f; break;
//         case 3: testPos.y -= 0.1f; break;
//         }
//
//         float distance = std::abs(testPos.x - targetPos.x) + std::abs(testPos.y - targetPos.y);
//         if (distance < bestDistance) {
//             bestDistance = distance;
//             bestDir = dir;
//         }
//     }
//
//     m_direction = bestDir;
//     return Vector2f(0, 0);
// }
//
// void OrangeGhostModel::updateMovement(float deltaTime, std::shared_ptr<PacmanModel> pacman, const World& world) {
//     GhostModel::updateMovement(deltaTime, pacman, world);
// }
//
// // Pink Ghost - Directly chase Pac-Man
// Vector2f PinkGhostModel::calculateChaseDirection(const World& world, std::shared_ptr<PacmanModel> pacman) {
//     if (!pacman) return Vector2f(0, 0);
//
//     Vector2f targetPos = pacman->getPosition();
//
//     // Find direction that minimizes Manhattan distance directly to Pac-Man
//     auto possibleDirs = getPossibleDirections(world);
//     if (possibleDirs.empty()) return Vector2f(0, 0);
//
//     int bestDir = possibleDirs[0];
//     float bestDistance = std::numeric_limits<float>::max();
//
//     for (int dir : possibleDirs) {
//         Vector2f testPos = m_position;
//         switch (dir) {
//             case 0: testPos.x -= 0.1f; break;
//             case 1: testPos.y += 0.1f; break;
//             case 2: testPos.x += 0.1f; break;
//             case 3: testPos.y -= 0.1f; break;
//         }
//
//         float distance = std::abs(testPos.x - targetPos.x) + std::abs(testPos.y - targetPos.y);
//         if (distance < bestDistance) {
//             bestDistance = distance;
//             bestDir = dir;
//         }
//     }
//
//     m_direction = bestDir;
//     return Vector2f(0, 0);
// }
//
// void PinkGhostModel::updateMovement(float deltaTime, std::shared_ptr<PacmanModel> pacman, const World& world) {
//     GhostModel::updateMovement(deltaTime, pacman, world);
// }