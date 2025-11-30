#include "../../include/entities/CoinModel.h"

CoinModel::CoinModel(const Vector2f& position, const Vector2f& size, const std::string& textureId)
    : m_position(position), m_textureId(textureId) {
    m_size = size;
}

void CoinModel::update(float deltaTime) {
    // notifyObservers();
    // Coins are static - no update logic needed unless animated
}

void CoinModel::setPosition(const Vector2f& position) {
    m_position = position;
    notifyObservers();  // Notify view when position changes
}

void CoinModel::collect() {
    if (!m_collected) {
        m_collected = true;
        notifyObservers();
    }
}