#ifndef ENTITY_H
#define ENTITY_H

#include "patterns/Subject.h"
#include <string>

namespace pacman::logic {
struct Vector2f {
    float x, y;
    Vector2f(float x = 0, float y = 0) : x(x), y(y) {}
};

namespace entities {

class EntityModel : public patterns::Subject {
public:
    ~EntityModel() override = default;

    virtual void update(float deltaTime) = 0;
    [[nodiscard]] virtual Vector2f getPosition() const = 0;
    virtual void setPosition(const Vector2f& position) = 0;
    [[nodiscard]] virtual Vector2f getSize() const = 0;

protected:
    void notifyPositionChanged() { notifyObservers(); }
};

} // namespace entities
}

#endif