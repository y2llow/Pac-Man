#include "entities/FruitModel.h"

namespace pacman::logic::entities {
FruitModel::FruitModel(const Vector2f& position, const Vector2f& size){
    m_position = position;{m_size = size;}
}

void FruitModel::update(float deltaTime)  {
    // notifyObservers();
}


void FruitModel::setPosition(const Vector2f& position)  {
    m_position = position;
}

void FruitModel::collect() {
    if (!m_collected) {
        m_collected = true;
        m_scoreAwarded = false;
        notifyObservers();
        m_scoreAwarded = true;
    }
}
}