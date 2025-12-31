#ifndef PACMANVIEW_H
#define PACMANVIEW_H

#include "Camera.h"
#include "entities/PacmanModel.h"
#include "views/EntityView.h"
#include <SFML/Graphics/View.hpp>

namespace pacman::representation::views {

class PacmanView : public EntityView {
public:
    PacmanView(std::shared_ptr<logic::entities::PacmanModel> pacmanModel, Camera& camera);
    ~PacmanView() override = default;

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

private:
    std::shared_ptr<logic::entities::PacmanModel> m_pacmanmodel;
    Camera& m_camera;
    sf::Sprite m_sprite;
    float m_animationTimer = 0.0f;
    float m_deathAnimationTimer = 0.0f;

    void updateShape();
    std::string getDeathAnimationSprite() const;
};

} // namespace views
#endif