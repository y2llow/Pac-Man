
#ifndef GHOSTVIEW_H
#define GHOSTVIEW_H
#include "Camera.h"
#include "entities/GhostModel.h"
#include "views/EntityView.h"

class GhostView : public EntityView {
public:

    GhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera);
    ~GhostView()override  = default;

    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    GhostModel& m_ghostmodel;
    sf::RenderWindow& m_window;
    Camera& m_camera;  // Reference to camera
    sf::Sprite m_sprite;
    sf::CircleShape m_circle;

    float GHOST_SIZE = 4;

    virtual void updateShape();
    virtual void setupShape();
};

class RedGhostView : public GhostView {
public:
    RedGhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera);

    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupShape() override;   // Override for different color/setup
    // Don't override updateShape() unless you need different positioning logic
};

class BlueGhostView : public GhostView {
public:
    BlueGhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera);

    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupShape() override;
};

class OrangeGhostView : public GhostView {
public:
    OrangeGhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera);

    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupShape() override;
};

class PinkGhostView : public GhostView {
public:
    PinkGhostView(GhostModel& ghostmodel, sf::RenderWindow& window, Camera& camera);

    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupShape() override;
};

#endif //GHOSTVIEW_H
