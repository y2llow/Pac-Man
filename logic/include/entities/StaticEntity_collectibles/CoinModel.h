//
// Created by s0243673@ad.ua.ac.be on 11/6/25.
//

#ifndef COIN_MODEL_H
#define COIN_MODEL_H
#include "entities/EntityModel.h"
#include <SFML/Graphics/Texture.hpp>
#include "patterns/Subject.h"
#include <SFML/System/Vector2.hpp>

class CoinModel : Entity {
public:
    CoinModel(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& textureId = "");

    // Entity interface implementation
    void update(float deltaTime) override;
    [[nodiscard]] sf::Vector2f getPosition() const override { return m_position; }
    void setPosition(const sf::Vector2f& position) override;

    // Texture management (logic only - no SFML types!)
    [[nodiscard]] const std::string& getTextureId() const { return m_textureId; }
    void setTextureId(const std::string& textureId) { m_textureId = textureId; }

private:
    sf::Vector2f m_position;
    std::string m_textureId; // Store texture identifier, not the actual texture
};


#endif //COIN_MODEL_H
