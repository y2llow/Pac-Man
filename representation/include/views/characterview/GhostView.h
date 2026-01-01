#ifndef GHOSTVIEW_H
#define GHOSTVIEW_H

#include "entities/GhostModel.h"
#include "Camera.h"
#include "views/EntityView.h"
#include <SFML/Graphics.hpp>
namespace pacman::representation::views {
class GhostView : public EntityView {
public:
    GhostView(std::shared_ptr<logic::entities::GhostModel> ghostmodel, Camera& camera);
    virtual ~GhostView() = default;

    void update(float deltaTime) override;  // UPDATED
    void draw(sf::RenderWindow& window) override;

protected:
    std::shared_ptr<logic::entities::GhostModel> m_ghostmodel;
    Camera& m_camera;
    sf::Sprite m_sprite;  // CHANGED: gebruik sprite ipv circle
    sf::Color m_normalColor;
    float m_animationTimer;  // NIEUW: voor animatie

    virtual void setupSprite();
    virtual void updateSprite();
    virtual std::string getGhostColor() const;  // NIEUW: voor sprite selectie

};
// Red Ghost View
class RedGhostView : public GhostView {
public:
    RedGhostView(std::shared_ptr<logic::entities::GhostModel> ghostmodel, Camera& camera);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupSprite() override;
    std::string getGhostColor() const override;

};

// Blue Ghost View
class BlueGhostView : public GhostView {
public:
    BlueGhostView(std::shared_ptr<logic::entities::GhostModel> ghostmodel, Camera& camera);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupSprite() override;
    std::string getGhostColor() const override;

};

// Orange Ghost View
class OrangeGhostView : public GhostView {
public:
    OrangeGhostView(std::shared_ptr<logic::entities::GhostModel> ghostmodel, Camera& camera);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupSprite() override;
    std::string getGhostColor() const override;

};

// Pink Ghost View
class PinkGhostView : public GhostView {
public:
    PinkGhostView(std::shared_ptr<logic::entities::GhostModel> ghostmodel, Camera& camera);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupSprite() override;
    std::string getGhostColor() const override;

};
}
#endif // GHOSTVIEW_H

