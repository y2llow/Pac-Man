#ifndef ENTITYVIEZ_H
#define ENTITYVIEZ_H
#include "patterns/Observer.h"
#include <SFML/Graphics.hpp>

class EntityView : public Observer{  // ← AbstractProductB interface
public:
    virtual ~EntityView() = default;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void setPosition(const sf::Vector2f& position) = 0;

};
#endif //ENTITYVIEZ_H


