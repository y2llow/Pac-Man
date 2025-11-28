#ifndef PACMAN_GAME_DOORVIEW_H
#define PACMAN_GAME_DOORVIEW_H

#include "Camera.h"
#include "views/EntityView.h"
#include <SFML/Graphics.hpp>

// Forward declaration
class DoorModel;

class DoorView : public EntityView {
public:
    explicit DoorView(std::shared_ptr<DoorModel> model, Camera& camera);
    ~DoorView() override = default;

    // EntityView interface
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

private:
    std::shared_ptr<DoorModel> m_model;
    Camera& m_camera;
    sf::RectangleShape m_shape;

    void setupRectangle();
    void updateShape();
};

#endif //PACMAN_GAME_DOORVIEW_H
