#ifndef ENTITY_H
#define ENTITY_H

#include "patterns/Subject.h"
#include <SFML/System/Vector2.hpp>
#include <string>

class EntityModel : public Subject {
public:
    ~EntityModel() override = default;

    virtual void update(float deltaTime) = 0;
    [[nodiscard]] virtual sf::Vector2f getPosition() const = 0;
    virtual void setPosition(const sf::Vector2f& position) = 0;
    [[nodiscard]] virtual sf::Vector2f getSize() const = 0;

    // Other common properties that might trigger notifications
    // virtual void setActive(bool active);

protected:
    // Helper method for derived classes
    void notifyPositionChanged() { notifyObservers(); }
};

#endif
