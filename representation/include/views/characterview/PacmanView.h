#ifndef PACMANVIEW_H
#define PACMANVIEW_H
#include "entities/PacmanModel.h"
#include "views/EntityView.h"
#include <SFML/Graphics/View.hpp>

class PacmanView : public EntityView {
    public:

    PacmanView(PacmanModel& coinModel, sf::RenderWindow& window);
    ~PacmanView()override  = default;

    void update() override;
    void draw(sf::RenderWindow& window) override;

    private:
    PacmanModel& m_pacmanmodel;
    sf::RenderWindow& m_window;
    sf::Sprite m_sprite;
    sf::CircleShape m_circle;

    void updateShape();
};


#endif //PACMANVIEW_H
