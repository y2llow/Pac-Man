#ifndef DOOR_MODEL_H
#define DOOR_MODEL_H

#include "entities/EntityModel.h"
#include <string>

namespace pacman::logic::entities {
class DoorModel : public EntityModel {
public:
    DoorModel(const Vector2f& position, const Vector2f& size);

    // EntityModel interface implementation
    void update(float deltaTime) override;
    Vector2f getPosition() const override { return m_position; }
    void setPosition(const Vector2f& position) override;
    Vector2f getSize() const override { return m_size; }

    const std::string& getTextureId() const { return m_textureId; }

private:
    Vector2f m_position;
    Vector2f m_size;
    std::string m_textureId;
};
}

#endif