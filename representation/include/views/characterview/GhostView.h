#ifndef GHOSTVIEW_H
#define GHOSTVIEW_H

#include "entities/GhostModel.h"
#include "Camera.h"
#include "views/EntityView.h"
#include <SFML/Graphics.hpp>

class GhostView : public EntityView {
public:
    GhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera);
    virtual ~GhostView() = default;

    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    GhostModel& m_ghostmodel;
    sf::RenderWindow& m_window;
    Camera& m_camera;
    sf::CircleShape m_circle;

    sf::Color m_normalColor;

    virtual void setupShape();
    virtual void updateShape();
};

// Red Ghost View
class RedGhostView : public GhostView {
public:
    RedGhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera);
    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupShape() override;
};

// Blue Ghost View
class BlueGhostView : public GhostView {
public:
    BlueGhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera);
    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupShape() override;
};

// Orange Ghost View
class OrangeGhostView : public GhostView {
public:
    OrangeGhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera);
    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupShape() override;
};

// Pink Ghost View
class PinkGhostView : public GhostView {
public:
    PinkGhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera);
    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupShape() override;
};

#endif // GHOSTVIEW_H