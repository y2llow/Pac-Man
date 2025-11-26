#ifndef FRUITVIEW_H
#define FRUITVIEW_H

#include "Camera.h"
#include "entities/FruitModel.h"
#include "views/EntityView.h"
#include <SFML/Graphics.hpp>

class FruitView : public EntityView {
public:
    FruitView(std::shared_ptr<FruitModel> fruitmodel, Camera& camera);
    ~FruitView() override = default;

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    bool shouldRender() const;

private:
    std::shared_ptr<FruitModel> m_fruitmodel;
    Camera& m_camera;
    sf::Sprite m_sprite;  // ENIGE: gebruik alleen sprite, geen circle

    void updateSprite();
    void updateShape();
};

#endif // FRUITVIEW_H