#ifndef ENTITYVIEZ_H
#define ENTITYVIEZ_H
#include "patterns/Observer.h"
#include <SFML/Graphics.hpp>

class EntityView : public Observer{
public:
    virtual ~EntityView() = default;

    virtual void update() {}
    virtual void draw(sf::RenderWindow& window) = 0;

};
#endif //ENTITYVIEZ_H


