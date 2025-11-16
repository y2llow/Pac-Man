#ifndef GHOST_H
#define GHOST_H

#include "EntityModel.h"

class GhostModel : public EntityModel {
public:
    GhostModel(const sf::Vector2f& position, const sf::Vector2f& size,std::string  textureId = "") ;

    // overwritten functiosn from entityModel
    void update(float deltaTime) override ;
    [[nodiscard]]  sf::Vector2f getPosition() const override {return m_position;}
    void setPosition(const sf::Vector2f& position) override;
    [[nodiscard]]  sf::Vector2f getSize() const override{return m_size;}

    // Pacman specific funcitons

protected:    //default privates
    sf::Vector2f m_position;
    std::string m_textureId;
    sf::Vector2f m_size;

    //pacman specific privates
    };

class RedGhostModel : public GhostModel {
public:
    RedGhostModel(const sf::Vector2f& position, const sf::Vector2f& size,const std::string& textureId = "")
    : GhostModel(position,size,textureId){}

    // overwritten functiosn from entityModel
    void update(float deltaTime) override ;

    // Pacman specific funcitons

private:

    //pacman specific privates
};

class BlueGhostModel : public GhostModel {
public:
    BlueGhostModel(const sf::Vector2f& position, const sf::Vector2f& size,const std::string& textureId = "")
    : GhostModel(position,size,textureId){}

    // overwritten functiosn from entityModel
    void update(float deltaTime) override ;

    // Pacman specific funcitons

private:

    //pacman specific privates
};

class OrangeGhostModel : public GhostModel {
public:
    OrangeGhostModel(const sf::Vector2f& position, const sf::Vector2f& size,const std::string& textureId = "")
    : GhostModel(position,size,textureId){}

    // overwritten functiosn from entityModel
    void update(float deltaTime) override ;

    // Pacman specific funcitons

private:

    //pacman specific privates
};

class PinkGhostModel : public GhostModel {
public:
    PinkGhostModel(const sf::Vector2f& position, const sf::Vector2f& size,const std::string& textureId = "")
    : GhostModel(position,size,textureId){}

    // overwritten functiosn from entityModel
    void update(float deltaTime) override ;

    // Pacman specific funcitons

private:

    //pacman specific privates
};
#endif //GHOST_H
