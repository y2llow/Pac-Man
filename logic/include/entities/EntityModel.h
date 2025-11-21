#ifndef ENTITY_H
#define ENTITY_H

#include "patterns/Subject.h"
#include <string>

struct Vector2f {
    float x, y;
    Vector2f(float x = 0, float y = 0) : x(x), y(y) {}
};

class EntityModel : public Subject {
public:
    ~EntityModel() override = default;

    virtual void update(float deltaTime) = 0;
    [[nodiscard]] virtual Vector2f getPosition() const = 0;
    virtual void setPosition(const Vector2f& position) = 0;
    [[nodiscard]] virtual Vector2f getSize() const = 0;

    // Other common properties that might trigger notifications
    // virtual void setActive(bool active);

protected:
    // Helper method for derived classes
    void notifyPositionChanged() { notifyObservers(); }
};

#endif