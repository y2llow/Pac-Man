#ifndef DOOR_VIEW_H
#define DOOR_VIEW_H

#include "Camera.h"
#include "views/EntityView.h"
#include <SFML/Graphics.hpp>

// Forward declaration
namespace pacman::logic::entities {
class DoorModel;
}

namespace pacman::representation::views {

class DoorView : public EntityView {
public:
    explicit DoorView(std::shared_ptr<logic::entities::DoorModel> model, Camera& camera);
    ~DoorView() override = default;

    // EntityView interface
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

private:
    std::shared_ptr<logic::entities::DoorModel> m_model;
    Camera& m_camera;
    sf::RectangleShape m_shape;

    void setupRectangle();
    void updateShape();
};

} // namespace pacman::representation::views

#endif // DOOR_VIEW_H