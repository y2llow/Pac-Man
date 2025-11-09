#include "../../include/entities/WallModel.h"

WallModel::WallModel(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& textureId)
    : m_position(position), m_textureId(textureId) {
    m_size = size;
}

void WallModel::update(float deltaTime) {
    // Walls are static - no update logic needed
}

void WallModel::setPosition(const sf::Vector2f& position) {
    m_position = position;
}