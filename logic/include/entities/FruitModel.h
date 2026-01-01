#ifndef FRUIT_H
#define FRUIT_H

#include "EntityModel.h"

namespace pacman::logic::entities {

class FruitModel : public EntityModel {
public:
    FruitModel(const Vector2f& position, const Vector2f& size);

    // Overwritten functions from EntityModel
    void update(float deltaTime) override;
    [[nodiscard]] Vector2f getPosition() const override { return m_position; }
    void setPosition(const Vector2f& position) override;
    [[nodiscard]] Vector2f getSize() const override { return m_size; }
    [[nodiscard]] bool getScoreAwarded() const { return m_scoreAwarded; }
    void setScoreAwarded(bool scoreAwarded) { m_scoreAwarded = scoreAwarded; }

    // FruitModel specific functions
    void collect();  // This will notify observers!
    [[nodiscard]] bool isCollected() const { return m_collected; }

private:
    // Default privates
    Vector2f m_position;
    Vector2f m_size;

    // FruitModel specific privates
    bool m_collected = false;
    bool m_scoreAwarded = false;
};

} // namespace pacman::logic::entities

#endif // FRUIT_H