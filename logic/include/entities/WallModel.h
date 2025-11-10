#ifndef WALL_MODEL_H
#define WALL_MODEL_H

#include "entities/EntityModel.h"
#include <SFML/System/Vector2.hpp>
#include <string>

class WallModel : public EntityModel {
public:
    WallModel(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& textureId = "");

    // EntityModel interface implementation
    void update(float deltaTime) override;
    sf::Vector2f getPosition() const override { return m_position; }
    void setPosition(const sf::Vector2f& position) override;
    sf::Vector2f getSize() const override { return m_size; }

    const std::string& getTextureId() const { return m_textureId; }

private:
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    std::string m_textureId;
};

#endif