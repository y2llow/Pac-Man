#ifndef ENTITYVIEZ_H
#define ENTITYVIEZ_H
#include "patterns/Observer.h"
#include <SFML/Graphics.hpp>

class EntityView : public Observer{  // ← AbstractProductB interface
public:
    virtual ~EntityView() = default;
    // Make these virtual but not pure virtual
    virtual void update() {}
    virtual void draw(sf::RenderWindow& window) = 0; // Keep this pure virtual

};
#endif //ENTITYVIEZ_H


