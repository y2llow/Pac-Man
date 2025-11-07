#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System/Vector2.hpp>

class Entity {
public:
    virtual ~Entity() = default;

    // Pure virtual methods - all entities must implement these
    virtual void update(float deltaTime) = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual void setPosition(const sf::Vector2f& position) = 0;

    // Common properties
    sf::Vector2f getSize() const { return m_size; }
    void setSize(const sf::Vector2f& size) { m_size = size; }

protected:
    sf::Vector2f m_size;
};

#endif
