#include "entities/DoorModel.h"
#include "entities/EntityModel.h"
#include <string>

DoorModel::DoorModel(const Vector2f& position, const Vector2f& size, const std::string& textureId)
    : m_position(position), m_size(size), m_textureId(textureId) {
    }

void DoorModel::update(float deltaTime) {
    // notifyObservers();
}

void DoorModel::setPosition(const Vector2f& position) {
    m_position = position;
    notifyObservers();
}