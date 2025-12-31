#ifndef GHOST_H
#define GHOST_H
#include "EntityModel.h"
#include <memory>

// Forward declaration
class PacmanModel;
class World;

// Voeg deze enum toe bovenaan het bestand
enum class GhostType {
    RED,
    BLUE,
    ORANGE,
    PINK
};
namespace entities {
class GhostModel : public pacman::logic::entities::EntityModel {
public:
    GhostModel(const pacman::logic::Vector2f& position, const pacman::logic::Vector2f& size);
    virtual ~GhostModel() = default;
    // Overwritten functions from EntityModel
    void update(float deltaTime) override;

    [[nodiscard]] pacman::logic::Vector2f getPosition() const override { return m_position; }
    void setPosition(const pacman::logic::Vector2f& position) override;
    [[nodiscard]] pacman::logic::Vector2f getSize() const override { return m_size; }
    [[nodiscard]] int getDirection() const { return m_direction; }
    int SetDirection( int direction )  { return m_direction = direction; }
    [[nodiscard]] int getLastDirection() const { return m_lastDirection; }
    int SetLastDirection( int direction )  { return m_lastDirection = direction; }
    [[nodiscard]]GhostType getType() const {return m_type;}

    // Ghost specific functions
    pacman::logic::Vector2f checkTunneling(pacman::logic::Vector2f position) const;
    [[nodiscard]] bool isScared() const { return m_scared; }
    void setScared(bool scared);
    void setScaredTimer(float time) { m_scaredTimer = time; m_scared = true; }
    void respawn();
    [[nodiscard]] float getScaredTimer() const { return m_scaredTimer; }

    // ai movement
    void MoveToStartPosition(pacman::logic::Vector2f startposition , float deltaTime );
    pacman::logic::Vector2f calculateNextPosition(float deltaTime) const;
    pacman::logic::Vector2f calculateNextPositionInDirection(const pacman::logic::Vector2f& startPos, int direction, float deltaTime) const;
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
    [[nodiscard]] bool wasEaten() const{return m_wasEaten;}
    void SetWasEaten(bool wasEaten) { m_wasEaten = wasEaten;}

    // In GhostModel class, voeg toe bij de public methods:
    [[nodiscard]] bool isAtIntersection(const World& world, float deltaTime) const;
    [[nodiscard]] std::vector<int> getValidDirectionsAtIntersection(const World& world, float deltaTime) const;

    bool willCrossIntersection(const World& world, float deltaTime) const;
    [[nodiscard]] pacman::logic::Vector2f getIntersectionPoint(const World& world, float deltaTime) const;
protected:
    pacman::logic::Vector2f m_position;
    std::string m_textureId;
    pacman::logic::Vector2f m_size;
    int m_direction = 2; // 0=left, 1=down, 2=right, 3=up
    int m_lastDirection{};

    // Ghost specific
    float GHOST_SPEED = 0.5/3;
    float m_speed{} ;
    int m_scaredTimerInc = 1;
    float m_scaredTimer = 0.0f;
    pacman::logic::Vector2f m_spawnPoint;
    bool m_scared = false;
    bool m_wasEaten = false;
    bool m_canMove = true;

    bool m_outsideStart = false;
    bool m_MovingToStart = false;

    GhostType m_type;  // Het type ghost

};

class RedGhostModel : public GhostModel {
public:
    RedGhostModel(const pacman::logic::Vector2f& position, const pacman::logic::Vector2f& size)
        : GhostModel(position, size) {m_direction = 0; m_type = GhostType::RED;}  // Zet type Left

    void updateMovement(float deltaTime) override;
    void resetMovingToStartTimer(float TimeWaiting) override;

private:
    float m_MovingToStartTimer = 0;
};

class BlueGhostModel : public GhostModel {
public:
    BlueGhostModel(const pacman::logic::Vector2f& position, const pacman::logic::Vector2f& size)
        : GhostModel(position, size) { m_direction = 2; m_type = GhostType::BLUE; } // Right

    void updateMovement(float deltaTime) override;
    void resetMovingToStartTimer(float TimeWaiting) override;
private:
    float m_MovingToStartTimer = 0;
};

class OrangeGhostModel : public GhostModel {
public:
    OrangeGhostModel(const pacman::logic::Vector2f& position, const pacman::logic::Vector2f& size)
        : GhostModel(position, size) { m_direction = 1; m_type = GhostType::ORANGE; } // Down

    void updateMovement(float deltaTime) override;
    void resetMovingToStartTimer(float TimeWaiting) override;

private:
    float m_MovingToStartTimer = 5;
};

class PinkGhostModel : public GhostModel {
public:
    PinkGhostModel(const pacman::logic::Vector2f& position, const pacman::logic::Vector2f& size)
        : GhostModel(position, size) { m_direction = 3;  m_type = GhostType::PINK;} // Up

    void updateMovement(float deltaTime) override;
    void resetMovingToStartTimer(float TimeWaiting) override;

private:
    float m_MovingToStartTimer = 10;
};
}

#endif // GHOST_H