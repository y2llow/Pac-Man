//
// Created by s0243673@ad.ua.ac.be on 11/6/25.
//

#ifndef FRUIT_H
#define FRUIT_H
#include "EntityModel.h"

class FruitModel : public EntityModel {
public:
    FruitModel(const sf::Vector2f& position, const sf::Vector2f& size,const std::string& textureId = "") ;

    // overwritten functiosn from entityModel
    void update(float deltaTime) override ;
    [[nodiscard]]  sf::Vector2f getPosition() const override {return m_position;}
    void setPosition(const sf::Vector2f& position) override;
    [[nodiscard]]  sf::Vector2f getSize() const override{return m_size;}

    // FruitModel specific funcitons
    void collect();  // This will notify observers!

    [[nodiscard]] bool isCollected() const { return m_collected; }
    [[nodiscard]] const std::string& getTextureId() const { return m_textureId; }


private:
    //default privates
    sf::Vector2f m_position;
    std::string m_textureId;
    sf::Vector2f m_size;

    //FruitModel specific privates
    bool m_collected = false;  // Track collection state

};
#endif //FRUIT_H
