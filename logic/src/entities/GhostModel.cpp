#include "entities/GhostModel.h"

 GhostModel::GhostModel(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& textureId){
m_position = position, m_textureId = textureId;{m_size = size;}
}

void GhostModel::update(float deltaTime)  {
     // notify observer when soemthing happens
 }


void GhostModel::setPosition(const sf::Vector2f& position)  {
     m_position = position;
     notifyObservers();

 }

