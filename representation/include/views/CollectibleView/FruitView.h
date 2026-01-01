#ifndef FRUITVIEW_H
#define FRUITVIEW_H

#include "Camera.h"
#include "views/EntityView.h"
#include <SFML/Graphics.hpp>

namespace pacman::logic::entities {
class FruitModel;
}

namespace pacman::representation::views {

class FruitView : public EntityView {
public:
    FruitView(std::shared_ptr<logic::entities::FruitModel> fruitmodel, Camera& camera);
    ~FruitView() override = default;

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    bool shouldRender() const;

private:
    std::shared_ptr<logic::entities::FruitModel> m_fruitmodel;
    Camera& m_camera;
    sf::Sprite m_sprite;

    void updateSprite();
    void updateShape();
};

} // namespace pacman::representation::views

#endif // FRUITVIEW_H