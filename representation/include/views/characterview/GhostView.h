
#ifndef GHOSTVIEW_H
#define GHOSTVIEW_H
#include "entities/GhostModel.h"
#include "views/EntityView.h"

class GhostView : public EntityView {
public:

    GhostView(GhostModel& ghostmodel, sf::RenderWindow& window);
    ~GhostView()override  = default;

    void update() override;
    void draw(sf::RenderWindow& window) override;

private:
    GhostModel& m_ghostmodel;
    sf::RenderWindow& m_window;
    sf::Sprite m_sprite;
    sf::CircleShape m_circle;

    void updateShape();
};

#endif //GHOSTVIEW_H
