#ifndef GHOST_H
#define GHOST_H

#include "EntityModel.h"

class GhostModel : public EntityModel {
public:
    GhostModel(const sf::Vector2f& position, const sf::Vector2f& size,const std::string& textureId = "") ;

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
#endif //GHOST_H
