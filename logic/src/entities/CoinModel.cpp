#include "entities/StaticEntity_collectibles/CoinModel.h"

CoinModel::CoinModel(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& textureId)
    : m_position(position), m_textureId(textureId) {
    m_size = size;
}

void CoinModel::update(float deltaTime) {
    // Walls are static - no update logic needed
}

void CoinModel::setPosition(const sf::Vector2f& position) {
    m_position = position;
}
