#ifndef ENTITY_VIEW_H
#define ENTITY_VIEW_H

#include <SFML/Graphics.hpp>
#include <memory>

class Camera;
class EntityModel;

class EntityView {
public:
    virtual ~EntityView() = default;

    // Update view based on model state
    virtual void update(float deltaTime) = 0;

    // Draw to window
    virtual void draw(sf::RenderWindow& window) = 0;

};

#endif


