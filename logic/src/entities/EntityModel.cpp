#include "entities/EntityModel.h"

void EntityModel::setPosition(const sf::Vector2f& position) {
    // Only notify if position actually changed
    // if (position != m_position) {
    //     m_position = position;
    notifyObservers();  // Notify all observing views
    // }
}

void EntityModel::setActive(bool active) {
    // if (m_active != active) {
    //     m_active = active;
    notifyObservers();  // Notify views about state change
    // }
}