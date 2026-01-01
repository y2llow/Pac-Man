#ifndef GHOST_MODEL_H
#define GHOST_MODEL_H

#include "entities/EntityModel.h"
#include <memory>
#include <vector>

// Forward declarations - correctly namespaced
namespace pacman::logic::world {
    class World;  // World is in pacman::logic::world namespace
}

namespace pacman::logic::entities {

enum class GhostType {
    RED,
    BLUE,
    ORANGE,
    PINK
};

class GhostModel : public EntityModel {
public:
    GhostModel(const Vector2f& position, const Vector2f& size);
    virtual ~GhostModel() = default;

    // EntityModel interface
    void update(float deltaTime) override;
    [[nodiscard]] Vector2f getPosition() const override { return m_position; }
    void setPosition(const Vector2f& position) override;
    [[nodiscard]] Vector2f getSize() const override { return m_size; }

    // Direction management
    [[nodiscard]] int getDirection() const { return m_direction; }
    void SetDirection(int direction) { m_direction = direction; }
    [[nodiscard]] int getLastDirection() const { return m_lastDirection; }
    void SetLastDirection(int direction) { m_lastDirection = direction; }
    [[nodiscard]] GhostType getType() const { return m_type; }

    // Ghost behavior
    [[nodiscard]] Vector2f checkTunneling(Vector2f position) const;
    [[nodiscard]] bool isScared() const { return m_scared; }
    void setScared(bool scared);
    void setScaredTimer(float time) { m_scaredTimer = time; m_scared = true; }
    void respawn();
    [[nodiscard]] float getScaredTimer() const { return m_scaredTimer; }

    // Movement
    void MoveToStartPosition(Vector2f startposition, float deltaTime);
    [[nodiscard]] Vector2f calculateNextPosition(float deltaTime) const;
    [[nodiscard]] Vector2f calculateNextPositionInDirection(const Vector2f& startPos, int direction, float deltaTime) const;
    bool canMoveInDirection(int direction, const world::World& world, float deltaTime) const;  // Use world:: since we're in entities namespace
    virtual void updateMovement(float deltaTime);
    void reverseDirection();

    // State management
    void setCanMove(bool canMove) { m_canMove = canMove; }
    void SetSpeed(float speed) { m_speed = speed; }
    [[nodiscard]] float GetSpeed() const { return m_speed; }
    void SetBaseSpeed(float baseSpeed) { GHOST_SPEED = baseSpeed; }
    [[nodiscard]] float GetBaseSpeed() const { return GHOST_SPEED; }
    void SetScaredTimerInc(float inc) { m_scaredTimerInc = inc; }

    [[nodiscard]] bool GetOutsideStart() const { return m_outsideStart; }
    void SetOutsideStart(bool outsideStart) { m_outsideStart = outsideStart; }
    void SetMovingToStart(bool movingToStart) { m_MovingToStart = movingToStart; }
    [[nodiscard]] bool GetMovingToStart() const { return m_MovingToStart; }
    virtual void resetMovingToStartTimer(float timeWaiting);
    [[nodiscard]] bool wasEaten() const { return m_wasEaten; }
    void SetWasEaten(bool wasEaten) { m_wasEaten = wasEaten; }

    // Intersection detection - use world:: prefix
    [[nodiscard]] bool isAtIntersection(const world::World& world, float deltaTime) const;
    [[nodiscard]] std::vector<int> getValidDirectionsAtIntersection(const world::World& world, float deltaTime) const;
    bool willCrossIntersection(const world::World& world, float deltaTime) const;
    [[nodiscard]] Vector2f getIntersectionPoint(const world::World& world, float deltaTime) const;

protected:
    Vector2f m_position;
    std::string m_textureId;
    Vector2f m_size;
    int m_direction = 2; // 0=left, 1=down, 2=right, 3=up
    int m_lastDirection = 2;

    // Ghost specific
    float GHOST_SPEED = 0.5f / 3.0f;
    float m_speed = GHOST_SPEED;
    int m_scaredTimerInc = 1;
    float m_scaredTimer = 0.0f;
    Vector2f m_spawnPoint;
    bool m_scared = false;
    bool m_wasEaten = false;
    bool m_canMove = true;
    bool m_outsideStart = false;
    bool m_MovingToStart = false;

    GhostType m_type;
};

// Derived ghost classes
class RedGhostModel : public GhostModel {
public:
    RedGhostModel(const Vector2f& position, const Vector2f& size);
    void updateMovement(float deltaTime) override;
    void resetMovingToStartTimer(float timeWaiting) override;

private:
    float m_MovingToStartTimer = 0.0f;
};

class BlueGhostModel : public GhostModel {
public:
    BlueGhostModel(const Vector2f& position, const Vector2f& size);
    void updateMovement(float deltaTime) override;
    void resetMovingToStartTimer(float timeWaiting) override;

private:
    float m_MovingToStartTimer = 0.0f;
};

class OrangeGhostModel : public GhostModel {
public:
    OrangeGhostModel(const Vector2f& position, const Vector2f& size);
    void updateMovement(float deltaTime) override;
    void resetMovingToStartTimer(float timeWaiting) override;

private:
    float m_MovingToStartTimer = 5.0f;
};

class PinkGhostModel : public GhostModel {
public:
    PinkGhostModel(const Vector2f& position, const Vector2f& size);
    void updateMovement(float deltaTime) override;
    void resetMovingToStartTimer(float timeWaiting) override;

private:
    float m_MovingToStartTimer = 10.0f;
};

} // namespace pacman::logic::entities

#endif // GHOST_MODEL_H