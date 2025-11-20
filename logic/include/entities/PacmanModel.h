#ifndef PACMAN_H
#define PACMAN_H

#include "EntityModel.h"


class PacmanModel : public EntityModel {
public:
     PacmanModel(const sf::Vector2f& position, const sf::Vector2f& size,std::string  textureId = "") ;

    // overwritten functiosn from entityModel
     void update(float deltaTime) override ;
    [[nodiscard]]  sf::Vector2f getPosition() const override {return m_position;}
     void setPosition(const sf::Vector2f& position) override;
    [[nodiscard]]  sf::Vector2f getSize() const override{return m_size;}


    // Pacman specific funcitons
    sf::Vector2f CheckTunneling(sf::Vector2f position);
    void undoLastMove();
    [[nodiscard]]unsigned int getLives() const {return m_lives;}
    void loseLife();

private:
    //default privates
    sf::Vector2f m_position;
    std::string m_textureId;
    sf::Vector2f m_size;

    //pacman specific privates
    unsigned char direction{};
    float PACMAN_SPEED = 0.3;
    float m_lastMove{};
    unsigned int m_lives = 3;
    sf::Vector2f m_spawnpoint;

};

#endif //PACMAN_H
