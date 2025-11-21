#ifndef PACMAN_H
#define PACMAN_H

#include "EntityModel.h"


class PacmanModel : public EntityModel {
public:
     PacmanModel(const Vector2f& position, const Vector2f& size,std::string  textureId = "") ;

    // overwritten functiosn from entityModel
     void update(float deltaTime) override ;
    [[nodiscard]]  Vector2f getPosition() const override {return m_position;}
     void setPosition(const Vector2f& position) override;
    [[nodiscard]]  Vector2f getSize() const override{return m_size;}


    // Pacman specific funcitons
    Vector2f CheckTunneling(Vector2f position);
    void undoLastMove();
    [[nodiscard]]unsigned int getLives() const {return m_lives;}
    void loseLife();

private:
    //default privates
    Vector2f m_position;
    std::string m_textureId;
    Vector2f m_size;

    //pacman specific privates
    unsigned char direction{};
    float PACMAN_SPEED = 0.3;
    float m_lastMove{};
    unsigned int m_lives = 3;
    Vector2f m_spawnpoint;

};

#endif //PACMAN_H
