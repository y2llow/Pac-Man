
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

protected:
    GhostModel& m_ghostmodel;
    sf::RenderWindow& m_window;
    sf::Sprite m_sprite;
    sf::CircleShape m_circle;

    virtual void updateShape();  // Made virtual for overriding
    virtual void setupShape();   // Added for initial shape setup
};

class RedGhostView : public GhostView {
public:
    RedGhostView(GhostModel& ghostmodel, sf::RenderWindow& window);

    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupShape() override;   // Override for different color/setup
    // Don't override updateShape() unless you need different positioning logic
};

class BlueGhostView : public GhostView {
public:
    BlueGhostView(GhostModel& ghostmodel, sf::RenderWindow& window);

    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupShape() override;   // Override for different color/setup
    // Don't override updateShape() unless you need different positioning logic
};

class OrangeGhostView : public GhostView {
public:
    OrangeGhostView(GhostModel& ghostmodel, sf::RenderWindow& window);

    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupShape() override;   // Override for different color/setup
    // Don't override updateShape() unless you need different positioning logic
};

class PinkGhostView : public GhostView {
public:
    PinkGhostView(GhostModel& ghostmodel, sf::RenderWindow& window);

    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupShape() override;   // Override for different color/setup
    // Don't override updateShape() unless you need different positioning logic
};

#endif //GHOSTVIEW_H
