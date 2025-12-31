#ifndef DOOR_MODEL_H
#define DOOR_MODEL_H

#include "entities/EntityModel.h"
#include <string>

class DoorModel : public pacman::logic::entities::EntityModel {
public:
    DoorModel(const pacman::logic::Vector2f& position, const pacman::logic::Vector2f& size);

    // EntityModel interface implementation
    void update(float deltaTime) override;
    pacman::logic::Vector2f getPosition() const override { return m_position; }
    void setPosition(const pacman::logic::Vector2f& position) override;
    pacman::logic::Vector2f getSize() const override { return m_size; }

    const std::string& getTextureId() const { return m_textureId; }

private:
    pacman::logic::Vector2f m_position;
    pacman::logic::Vector2f m_size;
    std::string m_textureId;
};

#endif