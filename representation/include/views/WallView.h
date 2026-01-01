#ifndef WALL_VIEW_H
#define WALL_VIEW_H

#include "Camera.h"
#include "views/EntityView.h"
#include <SFML/Graphics.hpp>

// Forward declaration
namespace pacman::logic::entities {
class WallModel;
}

namespace pacman::representation::views {

class WallView : public EntityView {
public:
    explicit WallView(std::shared_ptr<logic::entities::WallModel> model, Camera& camera);
    ~WallView() override = default;

    // EntityView interface
    void update(float deltaTime) override;
    void onModelChanged() override;
    void draw(sf::RenderWindow& window) override;

private:
    std::shared_ptr<logic::entities::WallModel> m_model;
    Camera& m_camera;
    sf::RectangleShape m_shape;

    void setupRectangle();
    void updateShape();
};

} // namespace pacman::representation::views

#endif // WALL_VIEW_H