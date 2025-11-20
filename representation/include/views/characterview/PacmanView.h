#ifndef PACMANVIEW_H
#define PACMANVIEW_H
#include "Camera.h"
#include "entities/PacmanModel.h"
#include "views/EntityView.h"
#include <SFML/Graphics/View.hpp>

class PacmanView : public EntityView {
    public:

    PacmanView(PacmanModel& coinModel,  Camera& camera);
    ~PacmanView()override  = default;

    void update() override;
    void draw(sf::RenderWindow& window) override;

    private:
    PacmanModel& m_pacmanmodel;
    Camera& m_camera;
    sf::Sprite m_sprite;
    sf::CircleShape m_circle;

    void updateShape();
};


#endif //PACMANVIEW_H
