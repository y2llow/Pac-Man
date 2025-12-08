#include "entities/GhostModel.h"

#include "core/Random.h"
#include "world/World.h"

#include <utility>

GhostModel::GhostModel(const Vector2f& position, const Vector2f& size, std::string textureId)
    : m_position(position), m_textureId(std::move(textureId)), m_size(size), m_spawnPoint(position) {
    // m_type wordt geïnitialiseerd in de afgeleide klassen
    // We initialiseren het hier met een default waarde
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

    // Only notify if scared state changed
    if (wasScared != m_scared) {
        notifyObservers();
    }
}

bool GhostModel::willCrossIntersection(const World& world, float deltaTime) const {
    // Check meerdere punten langs het pad
    Vector2f startPos = m_position;
    Vector2f endPos = calculateNextPosition(deltaTime);

    float distance = std::abs(endPos.x - startPos.x) + std::abs(endPos.y - startPos.y);
    float moveAmount = m_speed * deltaTime;

    // If the distance is much larger than moveAmount, it's tunneling - skip intersection check
    if (distance > moveAmount * 1.5f) {
        return false;
    }

//todo maybe lower this or make this dependant on speed
    // Check 10 punten langs de beweging
    const int numChecks = 100 ;
    for (int i = 0; i <= numChecks; i++) {
        float t = static_cast<float>(i) / numChecks;
        Vector2f checkPos;
        checkPos.x = startPos.x + (endPos.x - startPos.x) * t;
        checkPos.y = startPos.y + (endPos.y - startPos.y) * t;
        // NEW: Skip intersections outside the visible field [-1, 1]
        if (checkPos.x < -1.0f || checkPos.x > 1.0f || checkPos.y < -1.0f || checkPos.y > 1.0f) {
            continue;}

        // Maak temp ghost op deze positie
        GhostModel tempGhost = *this;
        tempGhost.setPosition(checkPos);

        // Check intersection op deze positie
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
            return true; // We gaan door een intersection!
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
        return m_position; // No intersection during tunneling
    }

    // Check meerdere punten en return het eerste intersection punt
    const int numChecks = 10 ;
    for (int i = 0; i <= numChecks; i++) {
        float t = static_cast<float>(i) / numChecks;
        Vector2f checkPos;
        checkPos.x = startPos.x + (endPos.x - startPos.x) * t;
        checkPos.y = startPos.y + (endPos.y - startPos.y) * t;

        if (checkPos.x < -1.0f || checkPos.x > 1.0f || checkPos.y < -1.0f || checkPos.y > 1.0f) {
            continue; }

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
            return checkPos; // Dit is het intersection punt
        }
    }

    return m_position; // Geen intersection gevonden
}

void GhostModel::setPosition(const Vector2f& position) {
    m_position = position;
}

void GhostModel::setScared(bool scared) {
    if (scared && !m_scared) {
        // todo add scared function
        // Just became scared - reverse direction
        reverseDirection();
        m_wasEaten = false;  // Reset eaten flag
    }

    bool wasScared = m_scared;
    m_scared = scared;

    if (scared) {
        m_scaredTimer = 10.0f;
    }

    // Only notify if state CHANGED
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

    // Only notify if state changed
    if (wasScared) {
        notifyObservers();
    }
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


// Red Ghost Implementation - One of the ghosts, when in chasing mode, should always be locked to moving in a
// fixed direction (either always up, down, right or left). If a ghost reaches a corner or
// intersection it will reconsider which direction it will be locked to. In particular, with
// probability p = 0.5, the ghost will lock to a random direction (that is viable).
void RedGhostModel::updateMovement(float deltaTime) {
    m_MovingToStartTimer -= deltaTime;
       if (m_MovingToStartTimer <= 0) {
           if (GetOutsideStart() != true)
           SetMovingToStart(true);
       }
    GhostModel::updateMovement(deltaTime);

}


// Blue Ghost Implementation - Moves right
void BlueGhostModel::updateMovement(float deltaTime) {
    m_MovingToStartTimer -= deltaTime;
    if (m_MovingToStartTimer <= 0) {
        if (GetOutsideStart() != true)
        SetMovingToStart(true);
    }
    GhostModel::updateMovement(deltaTime);
}


// Orange Ghost Implementation - Moves down
void OrangeGhostModel::updateMovement(float deltaTime) {
    m_MovingToStartTimer -= deltaTime;
    if (m_MovingToStartTimer <= 0) {
        if (GetOutsideStart() != true)
        SetMovingToStart(true);
    }
    GhostModel::updateMovement(deltaTime);
}

// Pink Ghost Implementation - Moves up
void PinkGhostModel::updateMovement(float deltaTime) {
    m_MovingToStartTimer -= deltaTime;
    if (m_MovingToStartTimer <= 0) {
        if (GetOutsideStart() != true)
        SetMovingToStart(true);
    }
    GhostModel::updateMovement(deltaTime);
}

void GhostModel::MoveToStartPosition(Vector2f startposition, float deltaTime ) {
    Vector2f GhostPosition = getPosition();
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
        setPosition(startposition);
        SetOutsideStart(true);
        SetMovingToStart(false);
    }
    if (GetOutsideStart()) {
        setPosition(startposition);
    }else {
        updateMovement(deltaTime);
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

bool GhostModel::isAtIntersection(const World& world, float deltaTime) const {
    // Een intersection is waar je meer dan 2 richtingen op kan
    // (huidige richting + tegenovergestelde tellen niet mee)
    int validDirections = 0;
    int oppositeDirection = (m_direction + 2) % 4;

    for (int dir = 0; dir < 4; dir++) {
        if (dir == oppositeDirection) continue; // Skip tegenovergestelde richting

        if (canMoveInDirection(dir, world, deltaTime)) {
            validDirections++;
        }
    }

    // Als we meer dan 1 richting kunnen (behalve terug), is het een intersection
    return validDirections > 1;
}

std::vector<int> GhostModel::getValidDirectionsAtIntersection(const World& world, float deltaTime) const {
    std::vector<int> validDirs;
    int oppositeDirection = (m_direction + 2) % 4;

    for (int dir = 0; dir < 4; dir++) {
        // Skip tegenovergestelde richting (ghosts gaan niet terug)
        if (dir == oppositeDirection) continue;

        if (canMoveInDirection(dir, world, deltaTime)) {
            validDirs.push_back(dir);
        }
    }

    return validDirs;
}

Vector2f GhostModel::findClosestPositionToWall(const Vector2f& currentPos,
                                                int direction,
                                                float deltaTime) const {
    // Binary search om dichtste positie te vinden zonder collision
    float moveAmount = m_speed * deltaTime;
    float minDistance = 0.0f;
    float maxDistance = moveAmount;
    float bestDistance = 0.0f;

    const int iterations = 10;

    for (int i = 0; i < iterations; ++i) {
        float testDistance = (minDistance + maxDistance) / 2.0f;
        Vector2f testPos = currentPos;

        switch (direction) {
            case 0: testPos.x -= testDistance; break; // Left
            case 1: testPos.y += testDistance; break; // Down
            case 2: testPos.x += testDistance; break; // Right
            case 3: testPos.y -= testDistance; break; // Up
        }

        testPos = checkTunneling(testPos);

        // Maak temp ghost om collision te checken
        GhostModel tempGhost = *this;
        tempGhost.setPosition(testPos);

        // We kunnen World niet direct checken, dus we geven alleen de beste distance terug
        // Dit wordt gebruikt in World::handlePredictiveGhostMovement
        bestDistance = testDistance;
        minDistance = testDistance;
    }

    Vector2f closestPos = currentPos;
    switch (direction) {
        case 0: closestPos.x -= bestDistance; break;
        case 1: closestPos.y += bestDistance; break;
        case 2: closestPos.x += bestDistance; break;
        case 3: closestPos.y -= bestDistance; break;
    }

    return checkTunneling(closestPos);
}
