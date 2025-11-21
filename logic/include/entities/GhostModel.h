#ifndef GHOST_H
#define GHOST_H

#include "EntityModel.h"

#include <SFML/System/Vector2.hpp>

class GhostModel : public EntityModel {
public:
    GhostModel(const Vector2f& position, const Vector2f& size,std::string  textureId = "") ;

    // overwritten functiosn from entityModel
    void update(float deltaTime) override ;
    [[nodiscard]]  Vector2f getPosition() const override {return m_position;}
    void setPosition(const Vector2f& position) override;
    [[nodiscard]]  Vector2f getSize() const override{return m_size;}

    //Ghost specific funcitons
    Vector2f CheckTunneling(Vector2f position);
    [[nodiscard]] bool isScared() ;
    void setScared();
    void respawn();
    [[nodiscard]]float getScaredTimer() const {return m_scaredTimer;}

protected:
    //default privates
    Vector2f m_position;
    std::string m_textureId;
    Vector2f m_size;

    //Ghost specific privates
    double GHOST_SPEED = 0.1;
    float m_scaredTimer = 0 ;public:protected:
    Vector2f m_ghost_spawnpoint;
    bool m_scared = false;

    };

class RedGhostModel : public GhostModel {
public:
    RedGhostModel(const Vector2f& position, const Vector2f& size,const std::string& textureId = "")
    : GhostModel(position,size,textureId){}

    // overwritten functiosn from entityModel
    void update(float deltaTime) override ;

    // RedGhost specific funcitons

private:

    //RedGhost specific privates
};

class BlueGhostModel : public GhostModel {
public:
    BlueGhostModel(const Vector2f& position, const Vector2f& size,const std::string& textureId = "")
    : GhostModel(position,size,textureId){}

    // overwritten functiosn from entityModel
    void update(float deltaTime) override ;

    // BlueGhost specific funcitons

private:

    //BlueGhost specific privates
};

class OrangeGhostModel : public GhostModel {
public:
    OrangeGhostModel(const Vector2f& position, const Vector2f& size,const std::string& textureId = "")
    : GhostModel(position,size,textureId){}

    // overwritten functiosn from entityModel
    void update(float deltaTime) override ;

    // PacOrangeGhostman specific funcitons

private:

    //OrangeGhost specific privates
};

class PinkGhostModel : public GhostModel {
public:
    PinkGhostModel(const Vector2f& position, const Vector2f& size,const std::string& textureId = "")
    : GhostModel(position,size,textureId){}

    // overwritten functiosn from entityModel
    void update(float deltaTime) override ;

    // PinkGhost specific funcitons

private:

    //PinkGhost specific privates
};
#endif //GHOST_H
