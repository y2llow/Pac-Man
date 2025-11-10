#ifndef WALL_VIEW_H
#define WALL_VIEW_H

#include "EntityView.h"
#include <SFML/Graphics.hpp>

class WallModel;
class TextureManager;

class WallView : public Observer {
public:
    WallView(WallModel& model, sf::RenderWindow& window);
    ~WallView() override = default;

    void update() override; // From Observer

    // rendering
    void draw(sf::RenderWindow& window);


private:
    WallModel& m_model; // Reference to the model we're observing
    sf::RectangleShape m_shape;
    sf::Sprite m_sprite;

    void updateShape(); // Update graphics based on model state
};

#endif
