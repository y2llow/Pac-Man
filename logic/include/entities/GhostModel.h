#ifndef GHOST_H
#define GHOST_H
#include "EntityModel.h"
#include <memory>

// Forward declaration
class PacmanModel;
class World;

class GhostModel : public EntityModel {
public:
    GhostModel(const Vector2f& position, const Vector2f& size, std::string textureId = "");
    virtual ~GhostModel() = default;
    // Overwritten functions from EntityModel
    void update(float deltaTime) override;

    [[nodiscard]] Vector2f getPosition() const override { return m_position; }
    void setPosition(const Vector2f& position) override;
    [[nodiscard]] Vector2f getSize() const override { return m_size; }
    [[nodiscard]] int getDirection() const { return m_direction; }
    int SetDirection( int direction )  { return m_direction = direction; }
    [[nodiscard]] int getLastDirection() const { return m_lastDirection; }
    int SetLastDirection( int direction )  { return m_lastDirection = direction; }

    // Ghost specific functions
    Vector2f checkTunneling(Vector2f position) const;
    [[nodiscard]] bool isScared() const { return m_scared; }
    void setScared(bool scared);
    void setScaredTimer(float time) { m_scaredTimer = time; m_scared = true; }
    void respawn();
    [[nodiscard]] float getScaredTimer() const { return m_scaredTimer; }

    // ai movement
    void MoveToStartPosition(Vector2f startposition , float deltaTime );
    Vector2f calculateNextPosition(float deltaTime) const;
    Vector2f calculateNextPositionInDirection(const Vector2f& startPos, int direction, float deltaTime) const;
    bool canMoveInDirection(int direction, const World& world, float deltaTime) const ;

    // Simple movement
    virtual void updateMovement(float deltaTime);
    void reverseDirection();

    // Setters for external control
    void setCanMove(bool canMove) { m_canMove = canMove; }

    void SetSpeed(float _m_speed) { m_speed = _m_speed;}
    float GetSpeed() { return m_speed;}
    void SetBaseSpeed(float _GHOST_SPEED) { GHOST_SPEED = _GHOST_SPEED;}
    float GetBaseSpeed() { return GHOST_SPEED;}
    void SetScaredTimerInc(float m_scared_timerInc) {m_scaredTimerInc = m_scared_timerInc;}

    [[nodiscard]]bool GetOutsideStart() const {return m_outsideStart;}
    void SetOutsideStart(bool m_outside_start) {m_outsideStart = m_outside_start;}
    void SetMovingToStart(bool m_moving_to_start) {m_MovingToStart = m_moving_to_start;}
    [[nodiscard]]bool GetMovingToStart() const {return m_MovingToStart;}
    virtual void resetMovingToStartTimer(float TimeWaiting) ;

    // In GhostModel class, voeg toe bij de public methods:
    [[nodiscard]] bool isAtIntersection(const World& world, float deltaTime) const;
    [[nodiscard]] std::vector<int> getValidDirectionsAtIntersection(const World& world, float deltaTime) const;
    [[nodiscard]] Vector2f findClosestPositionToWall(const Vector2f& currentPos, int direction, float deltaTime) const;

     bool willCrossIntersection(const World& world, float deltaTime) const;
    [[nodiscard]] Vector2f getIntersectionPoint(const World& world, float deltaTime) const;
protected:
    Vector2f m_position;
    std::string m_textureId;
    Vector2f m_size;
    int m_direction = 2; // 0=left, 1=down, 2=right, 3=up
    int m_lastDirection;

    // Ghost specific
    float GHOST_SPEED = 0.25f;
    float m_speed ;
    int m_scaredTimerInc = 1;
    float m_scaredTimer = 0.0f;
    Vector2f m_spawnPoint;
    bool m_scared = false;
    bool m_canMove = true;

    bool m_outsideStart = false;
    bool m_MovingToStart = false;
};

class RedGhostModel : public GhostModel {
public:
    RedGhostModel(const Vector2f& position, const Vector2f& size, const std::string& textureId = "")
        : GhostModel(position, size, textureId) { m_direction = 0; } // Left

    void updateMovement(float deltaTime) override;
    void resetMovingToStartTimer(float TimeWaiting) override;

private:
    float m_MovingToStartTimer = 0;

};

class BlueGhostModel : public GhostModel {
public:
    BlueGhostModel(const Vector2f& position, const Vector2f& size, const std::string& textureId = "")
        : GhostModel(position, size, textureId) { m_direction = 2; } // Right

    void updateMovement(float deltaTime) override;
    void resetMovingToStartTimer(float TimeWaiting) override;
private:
    float m_MovingToStartTimer = 0;
};

class OrangeGhostModel : public GhostModel {
public:
    OrangeGhostModel(const Vector2f& position, const Vector2f& size, const std::string& textureId = "")
        : GhostModel(position, size, textureId) { m_direction = 1; } // Down

    void updateMovement(float deltaTime) override;
    void resetMovingToStartTimer(float TimeWaiting) override;

private:
    float m_MovingToStartTimer = 5;
};

class PinkGhostModel : public GhostModel {
public:
    PinkGhostModel(const Vector2f& position, const Vector2f& size, const std::string& textureId = "")
        : GhostModel(position, size, textureId) { m_direction = 3; } // Up

    void updateMovement(float deltaTime) override;
    void resetMovingToStartTimer(float TimeWaiting) override;

private:
    float m_MovingToStartTimer = 10;
};

#endif // GHOST_H