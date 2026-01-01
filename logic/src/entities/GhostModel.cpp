#include "entities/GhostModel.h"
#include "core/Random.h"
#include "world/World.h"
#include <utility>

namespace pacman::logic::entities {

// Namespace alias for convenience
using World = world::World;

GhostModel::GhostModel(const Vector2f& position, const Vector2f& size)
    : m_position(position), m_size(size), m_spawnPoint(position) {
    m_type = GhostType::RED; // Default, wordt overschreven door afgeleide klassen
}

void GhostModel::update(float deltaTime) {
    float currentSpeed = GHOST_SPEED;
    bool wasScared = m_scared;

    if (m_scared) {
        if (m_scaredTimer >= 0) {
            m_scaredTimer -= deltaTime * m_scaredTimerInc;
            currentSpeed = GHOST_SPEED * 0.5f;
        } else {
            m_scared = false;
            m_scaredTimer = 0.0f;
        }
    }

    m_speed = currentSpeed;
    m_position = checkTunneling(m_position);

    if (wasScared != m_scared) {
        notifyObservers();
    }
}

bool GhostModel::willCrossIntersection(const World& world, float deltaTime) const {
    Vector2f startPos = m_position;
    Vector2f endPos = calculateNextPosition(deltaTime);

    float distance = std::abs(endPos.x - startPos.x) + std::abs(endPos.y - startPos.y);
    float moveAmount = m_speed * deltaTime;

    if (distance > moveAmount * 1.5f) {
        return false;
    }

    const int numChecks = 10;
    for (int i = 0; i <= numChecks; i++) {
        float t = static_cast<float>(i) / numChecks;
        Vector2f checkPos;
        checkPos.x = startPos.x + (endPos.x - startPos.x) * t;
        checkPos.y = startPos.y + (endPos.y - startPos.y) * t;

        if (checkPos.x < -1.0f || checkPos.x > 1.0f || checkPos.y < -1.0f || checkPos.y > 1.0f) {
            continue;
        }

        GhostModel tempGhost = *this;
        tempGhost.setPosition(checkPos);

        int validDirections = 0;
        int oppositeDirection = (m_direction + 2) % 4;

        for (int dir = 0; dir < 4; dir++) {
            if (dir == oppositeDirection) continue;

            Vector2f testPos = tempGhost.calculateNextPositionInDirection(checkPos, dir, deltaTime);
            if (!world.GhostWouldCollideWithWalls(tempGhost, testPos)) {
                validDirections++;
            }
        }

        if (validDirections > 1) {
            return true;
        }
    }

    return false;
}

Vector2f GhostModel::getIntersectionPoint(const World& world, float deltaTime) const {
    Vector2f startPos = m_position;
    Vector2f endPos = calculateNextPosition(deltaTime);

    float distance = std::abs(endPos.x - startPos.x) + std::abs(endPos.y - startPos.y);
    float moveAmount = m_speed * deltaTime;

    if (distance > moveAmount * 1.5f) {
        return m_position;
    }

    const int numChecks = 10;
    for (int i = 0; i <= numChecks; i++) {
        float t = static_cast<float>(i) / numChecks;
        Vector2f checkPos;
        checkPos.x = startPos.x + (endPos.x - startPos.x) * t;
        checkPos.y = startPos.y + (endPos.y - startPos.y) * t;

        if (checkPos.x < -1.0f || checkPos.x > 1.0f || checkPos.y < -1.0f || checkPos.y > 1.0f) {
            continue;
        }

        GhostModel tempGhost = *this;
        tempGhost.setPosition(checkPos);

        int validDirections = 0;
        int oppositeDirection = (m_direction + 2) % 4;

        for (int dir = 0; dir < 4; dir++) {
            if (dir == oppositeDirection) continue;

            Vector2f testPos = tempGhost.calculateNextPositionInDirection(checkPos, dir, deltaTime);
            if (!world.GhostWouldCollideWithWalls(tempGhost, testPos)) {
                validDirections++;
            }
        }

        if (validDirections > 1) {
            return checkPos;
        }
    }

    return m_position;
}

void GhostModel::setPosition(const Vector2f& position) {
    m_position = position;
}

void GhostModel::setScared(bool scared) {
    if (scared && !m_scared) {
        reverseDirection();
        m_wasEaten = false;
    }

    bool wasScared = m_scared;
    m_scared = scared;

    if (scared) {
        m_scaredTimer = 10.0f;
    }

    if (wasScared != m_scared) {
        notifyObservers();
    }
}

void GhostModel::respawn() {
    m_position = m_spawnPoint;
    bool wasScared = m_scared;
    m_scared = false;
    m_scaredTimer = 0.0f;
    m_canMove = true;
    m_outsideStart = false;
    m_MovingToStart = false;
    resetMovingToStartTimer(3);

    if (wasScared) {
        notifyObservers();
    }
}

void GhostModel::resetMovingToStartTimer(float TimeWaiting) {}
void RedGhostModel::resetMovingToStartTimer(float TimeWaiting) { m_MovingToStartTimer = TimeWaiting; }
void BlueGhostModel::resetMovingToStartTimer(float TimeWaiting) { m_MovingToStartTimer = TimeWaiting; }
void OrangeGhostModel::resetMovingToStartTimer(float TimeWaiting) { m_MovingToStartTimer = TimeWaiting; }
void PinkGhostModel::resetMovingToStartTimer(float TimeWaiting) { m_MovingToStartTimer = TimeWaiting; }

void GhostModel::updateMovement(float deltaTime) {
    if (!m_canMove) return;

    switch (m_direction) {
    case 0: m_position.x -= m_speed * deltaTime; break;
    case 1: m_position.y += m_speed * deltaTime; break;
    case 2: m_position.x += m_speed * deltaTime; break;
    case 3: m_position.y -= m_speed * deltaTime; break;
    }
}

void GhostModel::reverseDirection() {
    switch (m_direction) {
    case 0: m_direction = 2; break;
    case 1: m_direction = 3; break;
    case 2: m_direction = 0; break;
    case 3: m_direction = 1; break;
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

// Derived class implementations
RedGhostModel::RedGhostModel(const Vector2f& position, const Vector2f& size)
    : GhostModel(position, size) {
    m_type = GhostType::RED;
}

void RedGhostModel::updateMovement(float deltaTime) {
    m_MovingToStartTimer -= deltaTime;
    if (m_MovingToStartTimer <= 0) {
        if (GetOutsideStart() != true)
            SetMovingToStart(true);
    }
    GhostModel::updateMovement(deltaTime);
}

BlueGhostModel::BlueGhostModel(const Vector2f& position, const Vector2f& size)
    : GhostModel(position, size) {
    m_type = GhostType::BLUE;
}

void BlueGhostModel::updateMovement(float deltaTime) {
    m_MovingToStartTimer -= deltaTime;
    if (m_MovingToStartTimer <= 0) {
        if (GetOutsideStart() != true)
            SetMovingToStart(true);
    }
    GhostModel::updateMovement(deltaTime);
}

OrangeGhostModel::OrangeGhostModel(const Vector2f& position, const Vector2f& size)
    : GhostModel(position, size) {
    m_type = GhostType::ORANGE;
}

void OrangeGhostModel::updateMovement(float deltaTime) {
    m_MovingToStartTimer -= deltaTime;
    if (m_MovingToStartTimer <= 0) {
        if (GetOutsideStart() != true)
            SetMovingToStart(true);
    }
    GhostModel::updateMovement(deltaTime);
}

PinkGhostModel::PinkGhostModel(const Vector2f& position, const Vector2f& size)
    : GhostModel(position, size) {
    m_type = GhostType::PINK;
}

void PinkGhostModel::updateMovement(float deltaTime) {
    m_MovingToStartTimer -= deltaTime;
    if (m_MovingToStartTimer <= 0) {
        if (GetOutsideStart() != true)
            SetMovingToStart(true);
    }
    GhostModel::updateMovement(deltaTime);
}

void GhostModel::MoveToStartPosition(Vector2f startposition, float deltaTime) {
    Vector2f GhostPosition = getPosition();
    if (GhostPosition.x < startposition.x) {
        m_direction = 2;
    }
    if (GhostPosition.x > startposition.x) {
        m_direction = 0;
    }
    if (std::abs(GhostPosition.x - startposition.x) < m_speed * deltaTime && GhostPosition.y < startposition.y) {
        m_direction = 1;
    }
    if (std::abs(GhostPosition.x - startposition.x) < m_speed * deltaTime && GhostPosition.y > startposition.y) {
        m_direction = 3;
    }
    if (std::abs(GhostPosition.x - startposition.x) < m_speed * deltaTime &&
        std::abs(GhostPosition.y - startposition.y) < m_speed * deltaTime) {
        setPosition(startposition);
        SetOutsideStart(true);
        SetMovingToStart(false);
    }
    if (GetOutsideStart()) {
        setPosition(startposition);
    } else {
        updateMovement(deltaTime);
    }
}

Vector2f GhostModel::calculateNextPosition(float deltaTime) const {
    Vector2f newPosition = m_position;
    float moveAmount = m_speed * deltaTime;

    switch (m_direction) {
    case 0: newPosition.x -= moveAmount; break;
    case 1: newPosition.y += moveAmount; break;
    case 2: newPosition.x += moveAmount; break;
    case 3: newPosition.y -= moveAmount; break;
    }

    return checkTunneling(newPosition);
}

bool GhostModel::canMoveInDirection(int direction, const World& world, float deltaTime) const {
    Vector2f testPosition = calculateNextPositionInDirection(m_position, direction, deltaTime);
    return !world.GhostWouldCollideWithWalls(*this, testPosition);
}

Vector2f GhostModel::calculateNextPositionInDirection(const Vector2f& startPos, int direction, float deltaTime) const {
    Vector2f newPosition = startPos;
    float moveAmount = m_speed * deltaTime;

    switch (direction) {
    case 0: newPosition.x -= moveAmount; break;
    case 1: newPosition.y += moveAmount; break;
    case 2: newPosition.x += moveAmount; break;
    case 3: newPosition.y -= moveAmount; break;
    }

    return checkTunneling(newPosition);
}

bool GhostModel::isAtIntersection(const World& world, float deltaTime) const {
    int validDirections = 0;
    int oppositeDirection = (m_direction + 2) % 4;

    for (int dir = 0; dir < 4; dir++) {
        if (dir == oppositeDirection) continue;

        if (canMoveInDirection(dir, world, deltaTime)) {
            validDirections++;
        }
    }

    return validDirections > 1;
}

std::vector<int> GhostModel::getValidDirectionsAtIntersection(const World& world, float deltaTime) const {
    std::vector<int> validDirs;
    int oppositeDirection = (m_direction + 2) % 4;

    for (int dir = 0; dir < 4; dir++) {
        if (dir == oppositeDirection) continue;

        if (canMoveInDirection(dir, world, deltaTime)) {
            validDirs.push_back(dir);
        }
    }

    return validDirs;
}

} // namespace pacman::logic::entities