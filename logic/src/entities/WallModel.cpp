#include "entities/WallModel.h"

namespace pacman::logic::entities {

WallModel::WallModel(const Vector2f& position, const Vector2f& size)
    : m_position(position), m_size(size), m_textureId("wall_basic") {
}

void WallModel::update(float deltaTime) {
    // Walls are static - no update logic needed
}

void WallModel::setPosition(const Vector2f& position) {
    m_position = position;
    notifyObservers();
}

} // namespace pacman::logic::entities