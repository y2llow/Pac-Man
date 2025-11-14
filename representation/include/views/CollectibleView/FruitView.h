
#ifndef FRUITVIEW_H
#define FRUITVIEW_H
#include "entities/FruitModel.h"
#include "views/EntityView.h"

class FruitView : public EntityView {
public:

    FruitView(FruitModel& fruitmodel, sf::RenderWindow& window);
    ~FruitView()override  = default;

    void update() override;
    void draw(sf::RenderWindow& window) override;

private:
    FruitModel& m_fruitmodel;
    sf::RenderWindow& m_window;
    sf::Sprite m_sprite;
    sf::CircleShape m_circle;

    void updateShape();
};
#endif //FRUITVIEW_H
