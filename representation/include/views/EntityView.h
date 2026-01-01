#ifndef ENTITY_VIEW_H
#define ENTITY_VIEW_H

#include <SFML/Graphics.hpp>
#include <memory>

namespace pacman::representation::views {

class EntityView {
public:
    virtual ~EntityView() = default;
    virtual void update(float deltaTime) = 0;
    virtual void onModelChanged() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};

} // namespace pacman::representation::views

#endif