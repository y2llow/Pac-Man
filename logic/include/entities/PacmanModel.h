#ifndef PACMAN_H
#define PACMAN_H

#include "EntityModel.h"


class PacmanModel : public EntityModel {
public:
     PacmanModel(const sf::Vector2f& position, const sf::Vector2f& size,const std::string& textureId = "") ;

    // overwritten functiosn from entityModel
     void update(float deltaTime) override ;
    [[nodiscard]]  sf::Vector2f getPosition() const override {return m_position;}
     void setPosition(const sf::Vector2f& position) override;
    [[nodiscard]]  sf::Vector2f getSize() const override{return m_size;}

    // Pacman specific funcitons
    sf::Vector2f CheckTunneling(sf::Vector2f position);

private:
    //default privates
    sf::Vector2f m_position;
    std::string m_textureId;
    sf::Vector2f m_size;

    //pacman specific privates
    unsigned char direction;
    unsigned char PACMAN_SPEED = 5.5;

};

#endif //PACMAN_H
