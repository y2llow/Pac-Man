#include "entities/FruitModel.h"

FruitModel::FruitModel(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& textureId){
m_position = position, m_textureId = textureId;{m_size = size;}
}

void FruitModel::update(float deltaTime)  {
     // notify observer when soemthing happens
 }


void FruitModel::setPosition(const sf::Vector2f& position)  {
     m_position = position;
     notifyObservers();
 }