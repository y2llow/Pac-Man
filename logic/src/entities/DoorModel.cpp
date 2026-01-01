#include "entities/DoorModel.h"
#include "entities/EntityModel.h"
#include <string>

namespace pacman::logic::entities {
DoorModel::DoorModel(const Vector2f& position, const Vector2f& size)
    : m_position(position), m_size(size) {
}

void DoorModel::update(float deltaTime) {
    notifyObservers();
}

void DoorModel::setPosition(const Vector2f& position) {
    m_position = position;
    notifyObservers();
}
}