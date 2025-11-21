#include "entities/WallModel.h"

WallModel::WallModel(const Vector2f& position, const Vector2f& size, const std::string& textureId)
    : m_position(position), m_size(size), m_textureId(textureId) {
    // Proper initialization in initializer list
}

void WallModel::update(float deltaTime) {
    notifyObservers();

    // Walls are static - no update logic needed
}

void WallModel::setPosition(const Vector2f& position) {
    m_position = position;
    notifyObservers();  // Notify views when position changes
}