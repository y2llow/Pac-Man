#include "entities/DoorModel.h"
#include "entities/EntityModel.h"
#include <string>

DoorModel::DoorModel(const pacman::logic::Vector2f& position, const pacman::logic::Vector2f& size)
    : m_position(position), m_size(size) {
    }

void DoorModel::update(float deltaTime) {
    // notifyObservers();
}

void DoorModel::setPosition(const pacman::logic::Vector2f& position) {
    m_position = position;
    notifyObservers();
}