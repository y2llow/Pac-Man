#ifndef COIN_MODEL_H
#define COIN_MODEL_H

#include "entities/EntityModel.h"
#include <string>
#include <SFML/System/Vector2.hpp>

class CoinModel : public EntityModel {
public:
    CoinModel(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& textureId = "");

    // Entity interface implementation
    void update(float deltaTime) override;
    [[nodiscard]] sf::Vector2f getPosition() const override { return m_position; }
    void setPosition(const sf::Vector2f& position) override;
    [[nodiscard]] sf::Vector2f getSize() const override { return m_size; }

    // Coin-specific functionality
    void collect();  // This will notify observers!
    
    [[nodiscard]] bool isCollected() const { return m_collected; }
    [[nodiscard]] const std::string& getTextureId() const { return m_textureId; }

private:
    sf::Vector2f m_position;
    std::string m_textureId;
    sf::Vector2f m_size;

    // Coin Specific privates
    bool m_collected = false;  // Track collection state
};

#endif