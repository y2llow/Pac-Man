#ifndef WALL_VIEW_H
#define WALL_VIEW_H

#include "Camera.h"
#include "EntityView.h"
#include <SFML/Graphics.hpp>

class WallModel;

class WallView : public EntityView {
public:
    WallView(WallModel& model, sf::RenderWindow& window, Camera& camera);
    ~WallView() override = default;

    void update() override;
    void draw(sf::RenderWindow& window);
    void setupRectangle();

private:
    sf::RenderWindow& m_window;
    WallModel& m_model;
    sf::RectangleShape m_shape;
    Camera& m_camera;
    // Remove: sf::Sprite m_sprite; (you're not using it)
    // Remove: float WALL_SIZE = 1; (not needed with Option 1)

    void updateShape();
};

#endif