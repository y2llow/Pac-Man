#ifndef WALL_MODEL_H
#define WALL_MODEL_H

#include <SFML/Graphics/Texture.hpp>

#include "entities/EntityModel.h"
#include "patterns/Subject.h"
#include <SFML/System/Vector2.hpp>
class WallModel : public EntityModel {
public:
    WallModel(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& textureId = "");

    // Entity interface implementation
    void update(float deltaTime) override;
    [[nodiscard]] sf::Vector2f getPosition() const override { return m_position; }
    void setPosition(const sf::Vector2f& position) override;
    [[nodiscard]] sf::Vector2f getSize() const override { return m_size; }

    // Texture management (logic only - no SFML types!)
    [[nodiscard]] const std::string& getTextureId() const { return m_textureId; }
    void setTextureId(const std::string& textureId) { m_textureId = textureId; }

private:
    sf::Vector2f m_position;
    std::string m_textureId; // Store texture identifier, not the actual texture
    sf::Vector2f m_size;

};


#endif