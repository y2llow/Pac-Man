#include "entities/GhostModel.h"
#include <utility>

GhostModel::GhostModel(const sf::Vector2f& position, const sf::Vector2f& size, std::string textureId)
    : m_position(position), m_textureId(std::move(textureId)), m_size(size), m_ghost_spawnpoint(position)  {
}

void GhostModel::update(float deltaTime) {
    // Base class handles ONLY tunneling and notification
    m_position = CheckTunneling(m_position);
    if (isScared()) {
        // Assuming m_scaredTimer is a member variable that tracks remaining scared time
        m_scaredTimer -= deltaTime;
        m_scaredTimer = std::max(m_scaredTimer, 0.0f);
    }
    notifyObservers();
}

void GhostModel::setPosition(const sf::Vector2f& position) {
    m_position = position;
    notifyObservers();
}

bool GhostModel::isScared()  {
    if (m_scaredTimer > 0) {
        m_scared = true;
        return true;
    }
    m_scared = false;
    return false;
}
void GhostModel::setScared() {
    m_scaredTimer = 5.0f;
}

void GhostModel::respawn() {
    m_position = m_ghost_spawnpoint;
}

//-----------------------------------------------------------------------------------------------------//
// Each ghost handles its own movement, then calls base for tunneling + notification
void RedGhostModel::update(float deltaTime) {
    m_position.x += GHOST_SPEED * deltaTime;  // Red moves right
    GhostModel::update(deltaTime);     // Call base for tunneling + notification
}

void BlueGhostModel::update(float deltaTime) {
    m_position.x -= GHOST_SPEED * deltaTime;   // Blue moves left
    GhostModel::update(deltaTime);     // Call base for tunneling + notification
}

void OrangeGhostModel::update(float deltaTime) {
    m_position.y += GHOST_SPEED * deltaTime;   // Orange moves down
    GhostModel::update(deltaTime);     // Call base for tunneling + notification
}

void PinkGhostModel::update(float deltaTime) {
    m_position.y -= GHOST_SPEED * deltaTime;   // Pink moves up
    GhostModel::update(deltaTime);     // Call base for tunneling + notification
}

sf::Vector2f GhostModel::CheckTunneling(sf::Vector2f position) {
    float edge = 1 + m_size.x / 2;
    if (-edge >= position.x) {
        position.x = edge;
        return position;
    }
    if (edge <= position.x) {
        position.x = -edge;
        return position;
    }
    return position;
}