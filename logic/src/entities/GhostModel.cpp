#include "entities/GhostModel.h"

#include <utility>

 GhostModel::GhostModel(const sf::Vector2f& position, const sf::Vector2f& size, std::string  textureId)
    : m_position(position),  m_textureId(std::move(textureId)), m_size(size) {
 }

void GhostModel::update(float deltaTime)  {
     // notify observer when soemthing happens
 }


void GhostModel::setPosition(const sf::Vector2f& position)  {
     m_position = position;
     notifyObservers();

 }

// RedGhostModel constructor is now just calling base constructor
void RedGhostModel::update(float deltaTime) {
     // RedGhost-specific update logic
 }

// RedGhostModel constructor is now just calling base constructor
void BlueGhostModel::update(float deltaTime) {
     // RedGhost-specific update logic
 }

// RedGhostModel constructor is now just calling base constructor
void OrangeGhostModel::update(float deltaTime) {
     // RedGhost-specific update logic
 }

// RedGhostModel constructor is now just calling base constructor
void PinkGhostModel::update(float deltaTime) {
     // RedGhost-specific update logic
 }

