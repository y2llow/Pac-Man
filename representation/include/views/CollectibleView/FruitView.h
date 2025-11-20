
#ifndef FRUITVIEW_H
#define FRUITVIEW_H
#include "Camera.h"
#include "entities/FruitModel.h"
#include "views/EntityView.h"

class FruitView : public EntityView {
public:

    FruitView(FruitModel& fruitmodel, Camera& camera);
    ~FruitView()override  = default;

    void update() override;
    void draw(sf::RenderWindow& window) override;

private:
    FruitModel& m_fruitmodel;
    Camera& m_camera;
    sf::Sprite m_sprite;
    sf::CircleShape m_circle;

    void updateShape();
};
#endif //FRUITVIEW_H
