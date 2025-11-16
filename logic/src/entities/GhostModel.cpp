#include "entities/GhostModel.h"
#include <utility>

GhostModel::GhostModel(const sf::Vector2f& position, const sf::Vector2f& size, std::string textureId)
    : m_position(position), m_textureId(std::move(textureId)), m_size(size) {
}

void GhostModel::update(float deltaTime) {
    // Base class handles ONLY tunneling and notification
    m_position = CheckTunneling(m_position);
    notifyObservers();
}

void GhostModel::setPosition(const sf::Vector2f& position) {
    m_position = position;
    notifyObservers();
}

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