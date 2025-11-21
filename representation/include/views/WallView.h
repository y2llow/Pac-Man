#ifndef WALL_VIEW_H
#define WALL_VIEW_H

#include "Camera.h"
#include "EntityView.h"
#include <SFML/Graphics.hpp>

class WallModel;

class WallView : public EntityView {
public:
    explicit WallView(std::shared_ptr<WallModel> model, Camera& camera);
    ~WallView() override = default;

    // Observer interface
    void update() override;

    // Rendering
    void draw(sf::RenderWindow& window) override;

private:
    std::shared_ptr<WallModel> m_model;
    Camera& m_camera;
    sf::RectangleShape m_shape;

    void setupRectangle();
    void updateShape();
};

#endif // WALL_VIEW_H

