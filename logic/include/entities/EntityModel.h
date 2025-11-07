#ifndef ENTITY_MODEL_H
#define ENTITY_MODEL_H

#include "Subject.h"
#include <SFML/System/Vector2.hpp>

class EntityModel : public Subject {
public:
    virtual ~EntityModel() = default;
    virtual void update(float deltaTime) = 0;

    sf::Vector2f getPosition() const { return m_position; }
    // ... other common entity properties

protected:
    sf::Vector2f m_position;
};

#endif
