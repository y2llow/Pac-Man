#ifndef WALL_MODEL_H
#define WALL_MODEL_H

#include "entities/EntityModel.h"
#include <string>

namespace pacman::logic::entities {

class WallModel : public EntityModel {
public:
    WallModel(const Vector2f& position, const Vector2f& size);

    // EntityModel interface implementation
    void update(float deltaTime) override;
    [[nodiscard]] Vector2f getPosition() const override { return m_position; }
    void setPosition(const Vector2f& position) override;
    [[nodiscard]] Vector2f getSize() const override { return m_size; }

    [[nodiscard]] const std::string& getTextureId() const { return m_textureId; }

private:
    Vector2f m_position;
    Vector2f m_size;
    std::string m_textureId;
};

} // namespace pacman::logic::entities

#endif // WALL_MODEL_H