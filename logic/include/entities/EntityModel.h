#ifndef ENTITY_MODEL_H
#define ENTITY_MODEL_H

#include "patterns/Subject.h"
#include <string>

namespace pacman::logic {

// Vector2f is shared across both logic and representation layers
struct Vector2f {
    float x, y;
    Vector2f(float x = 0, float y = 0) : x(x), y(y) {}
};

namespace entities {

/**
 * @brief Base class for all game entities
 * All entities live in the logic layer and are platform-independent
 */
class EntityModel : public patterns::Subject {
public:
    virtual ~EntityModel() = default;

    virtual void update(float deltaTime) = 0;
    [[nodiscard]] virtual Vector2f getPosition() const = 0;
    virtual void setPosition(const Vector2f& position) = 0;
    [[nodiscard]] virtual Vector2f getSize() const = 0;

protected:
    void notifyPositionChanged() { notifyObservers(); }
};

} // namespace entities
} // namespace pacman::logic

#endif // ENTITY_MODEL_H