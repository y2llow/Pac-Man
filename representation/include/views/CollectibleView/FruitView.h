
#ifndef FRUITVIEW_H
#define FRUITVIEW_H
#include "Camera.h"
#include "entities/FruitModel.h"
#include "views/EntityView.h"

class FruitView : public EntityView {
public:

    FruitView(FruitModel& fruitmodel, sf::RenderWindow& window, Camera& camera);
    ~FruitView()override  = default;

    void update() override;
    void draw(sf::RenderWindow& window) override;

private:
    FruitModel& m_fruitmodel;
    sf::RenderWindow& m_window;
    Camera& m_camera;
    sf::Sprite m_sprite;
    sf::CircleShape m_circle;

    float FRUIT_SIZE = 0.1f;

    void updateShape();
};
#endif //FRUITVIEW_H
