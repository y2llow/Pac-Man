#ifndef WALL_MODEL_H
#define WALL_MODEL_H

#include "entities/EntityModel.h"
#include <string>

class WallModel : public pacman::logic::entities::EntityModel {
public:
    WallModel(const pacman::logic::Vector2f& position, const pacman::logic::Vector2f& size);

    // EntityModel interface implementation
    void update(float deltaTime) override;
    [[nodiscard]] pacman::logic::Vector2f getPosition() const override { return m_position; }
    void setPosition(const pacman::logic::Vector2f& position) override;
    [[nodiscard]] pacman::logic::Vector2f getSize() const override { return m_size; }

    const std::string& getTextureId() const { return m_textureId; }

private:
    pacman::logic::Vector2f m_position;
    pacman::logic::Vector2f m_size;
    std::string m_textureId;
};

#endif