#ifndef GHOSTVIEW_H
#define GHOSTVIEW_H

#include "entities/GhostModel.h"
#include "Camera.h"
#include "views/EntityView.h"
#include <SFML/Graphics.hpp>

class GhostView : public EntityView {
public:
    GhostView(std::shared_ptr<GhostModel> ghostmodel, Camera& camera);
    virtual ~GhostView() = default;

    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    std::shared_ptr<GhostModel> m_ghostmodel;
    Camera& m_camera;
    sf::CircleShape m_circle;

    sf::Color m_normalColor;

    virtual void setupShape();
    virtual void updateShape();
};

// Red Ghost View
class RedGhostView : public GhostView {
public:
    RedGhostView(std::shared_ptr<GhostModel> ghostmodel, Camera& camera);
    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupShape() override;
};

// Blue Ghost View
class BlueGhostView : public GhostView {
public:
    BlueGhostView(std::shared_ptr<GhostModel> ghostmodel,  Camera& camera);
    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupShape() override;
};

// Orange Ghost View
class OrangeGhostView : public GhostView {
public:
    OrangeGhostView(std::shared_ptr<GhostModel> ghostmodel,  Camera& camera);
    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupShape() override;
};

// Pink Ghost View
class PinkGhostView : public GhostView {
public:
    PinkGhostView(std::shared_ptr<GhostModel> ghostmodel,  Camera& camera);
    void update() override;
    void draw(sf::RenderWindow& window) override;

protected:
    void setupShape() override;
};

#endif // GHOSTVIEW_H