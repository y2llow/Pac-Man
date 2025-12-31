#include "entities/WallModel.h"

WallModel::WallModel(const pacman::logic::Vector2f& position, const pacman::logic::Vector2f& size)
    : m_position(position), m_size(size){
    // Proper initialization in initializer list
}

void WallModel::update(float deltaTime) {
    // notifyObservers();
    // Walls are static - no update logic needed
}

void WallModel::setPosition(const pacman::logic::Vector2f& position) {
    m_position = position;
}