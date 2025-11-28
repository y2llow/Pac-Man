#include "entities/PacmanModel.h"

#include <utility>

PacmanModel::PacmanModel(const Vector2f& position, const Vector2f& size, std::string  textureId )
    : m_position(position), m_textureId(std::move(textureId)), m_spawnpoint(position) { m_size = size; }

Vector2f PacmanModel::calculateNextPosition(float deltaTime) const {
    if (m_isDying) return m_position; // Don't move during death animation

    Vector2f newPosition = m_position;
    float moveAmount = PACMAN_SPEED * deltaTime;

    switch (m_direction) {
    case 0: newPosition.x -= moveAmount; break; // Left
    case 1: newPosition.y += moveAmount; break; // Down
    case 2: newPosition.x += moveAmount; break; // Right
    case 3: newPosition.y -= moveAmount; break; // Up
    }

    return CheckTunneling(newPosition);
}

void PacmanModel::setDirection(int newDirection) {
    m_direction = newDirection;
}

void PacmanModel::applyMovement(const Vector2f& newPosition) {
    m_position = newPosition;
    // De observer wordt aangeroepen door World
}

void PacmanModel::update(float deltaTime) {
    if (m_isDying && !m_deathAnimationComplete) {
        m_deathAnimationTimer += deltaTime;

        if (m_deathAnimationTimer >= DEATH_ANIMATION_DURATION) {
            m_deathAnimationComplete = true;
        }
    }
}

void PacmanModel::startDeathAnimation() {
    m_isDying = true;
    m_deathAnimationTimer = 0.0f;
    m_deathAnimationComplete = false;
    notifyObservers(); // Notify view about state change
}

void PacmanModel::resetDeathAnimation() {
    m_isDying = false;
    m_deathAnimationComplete = false;
    m_deathAnimationTimer = 0.0f;
    notifyObservers();
}

void PacmanModel::loseLife() {
    if (m_lives > 0) {
        m_lives -= 1;
        startDeathAnimation(); // Start death animation instead of immediate reset
    }
}

Vector2f PacmanModel::CheckTunneling(Vector2f position) const {
    float edge = 1 + m_size.x / 2;
    if (-edge >= position.x){
        position.x = edge ;
        return position;
    }if (edge <= position.x){
        position.x = -edge;
        return position;
    }
    return position;
}



void PacmanModel::setPosition(const Vector2f& position)  {
    m_position = position;
    notifyObservers();

}

void PacmanModel::bufferDirection(int newDirection) {
    m_bufferedDirection = newDirection;
}

void PacmanModel::clearBufferedDirection() {
    m_bufferedDirection = -1;
}

bool PacmanModel::canMoveInDirection(int direction, const World& world, float deltaTime) const {
    Vector2f testPosition = calculatePositionInDirection(m_position, direction, deltaTime);
    return !world.PacmanWouldCollideWithWalls(*this, testPosition);
}

Vector2f PacmanModel::calculatePositionInDirection(const Vector2f& startPos, int direction, float deltaTime) const {
    Vector2f newPosition = startPos;
    float moveAmount = PACMAN_SPEED * deltaTime;

    switch (direction) {
    case 0: newPosition.x -= moveAmount; break; // Left
    case 1: newPosition.y += moveAmount; break; // Down
    case 2: newPosition.x += moveAmount; break; // Right
    case 3: newPosition.y -= moveAmount; break; // Up
    }

    return CheckTunneling(newPosition);
}


