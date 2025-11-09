#ifndef WALL_VIEW_H
#define WALL_VIEW_H

#include "EntityView.h"
#include <SFML/Graphics.hpp>

class WallModel; // Forward declaration

class WallView : public EntityView {
public:
    WallView(WallModel& model, sf::RenderWindow& window);
    void update() override; // From Observer
    void draw(sf::RenderWindow& window);

private:
    WallModel& m_model; // Reference to the model we're observing
    sf::RectangleShape m_shape;

    void updateShape(); // Update graphics based on model state
};

#endif
