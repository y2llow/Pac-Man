#ifndef PACMAN_H
#define PACMAN_H

#include "EntityModel.h"
#include <SFML/System.hpp>


class PacmanModel : public EntityModel {
public:
     PacmanModel(const sf::Vector2f& position, const sf::Vector2f& size,const std::string& textureId = "") ;

    // overwritten functiosn from entityModel
     void update(float deltaTime) override ;
    [[nodiscard]]  sf::Vector2f getPosition() const override {return m_position;}
     void setPosition(const sf::Vector2f& position) override;
    [[nodiscard]]  sf::Vector2f getSize() const override{return m_size;}

    // Pacman specific funcitons

    private:
    //default privates
    sf::Vector2f m_position;
    std::string m_textureId;
    sf::Vector2f m_size;

    //pacman specific privates
};

#endif //PACMAN_H
