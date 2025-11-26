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

    // Ghost specific functions
    Vector2f checkTunneling(Vector2f position);
    [[nodiscard]] bool isScared() const { return m_scared; }
    void setScared(bool scared);
    void setScaredTimer(float time) { m_scaredTimer = time; m_scared = true; }
    void respawn();
    [[nodiscard]] float getScaredTimer() const { return m_scaredTimer; }

    // Simple movement
    virtual void updateMovement(float deltaTime);
    void reverseDirection();

    // Setters for external control
    void setCanMove(bool canMove) { m_canMove = canMove; }

protected:
    Vector2f m_position;
    std::string m_textureId;
    Vector2f m_size;
    int m_direction = 2; // 0=left, 1=down, 2=right, 3=up

    // Ghost specific
    float m_speed = 0.3f ;
    float m_scaredSpeed = 0.5f;
    float m_scaredTimer = 0.0f;
    Vector2f m_spawnPoint;
    bool m_scared = false;
    bool m_canMove = true;
};

class RedGhostModel : public GhostModel {
public:
    RedGhostModel(const Vector2f& position, const Vector2f& size, const std::string& textureId = "")
        : GhostModel(position, size, textureId) { m_direction = 0; } // Left

    void updateMovement(float deltaTime) override;
};

class BlueGhostModel : public GhostModel {
public:
    BlueGhostModel(const Vector2f& position, const Vector2f& size, const std::string& textureId = "")
        : GhostModel(position, size, textureId) { m_direction = 2; } // Right

    void updateMovement(float deltaTime) override;
};

class OrangeGhostModel : public GhostModel {
public:
    OrangeGhostModel(const Vector2f& position, const Vector2f& size, const std::string& textureId = "")
        : GhostModel(position, size, textureId) { m_direction = 1; } // Down

    void updateMovement(float deltaTime) override;
};

class PinkGhostModel : public GhostModel {
public:
    PinkGhostModel(const Vector2f& position, const Vector2f& size, const std::string& textureId = "")
        : GhostModel(position, size, textureId) { m_direction = 3; } // Up

    void updateMovement(float deltaTime) override;
};

#endif // GHOST_H

// #ifndef GHOST_H
// #define GHOST_H
//
// #include "EntityModel.h"
// #include <memory>
//
// // Forward declaration
// class PacmanModel;
// class World;
//
// class GhostModel : public EntityModel {
// public:
//     GhostModel(const Vector2f& position, const Vector2f& size, std::string textureId = "");
//     virtual ~GhostModel() = default;
//
//     // Overwritten functions from EntityModel
//     void update(float deltaTime) override;
//     [[nodiscard]] Vector2f getPosition() const override { return m_position; }
//     void setPosition(const Vector2f& position) override;
//     [[nodiscard]] Vector2f getSize() const override { return m_size; }
//     [[nodiscard]] int getDirection() const { return m_direction; }
//
//     // Ghost specific functions
//     Vector2f checkTunneling(Vector2f position);
//     [[nodiscard]] bool isScared() const { return m_scared; }
//     void setScared(bool scared);
//     void setScaredTimer(float time) { m_scaredTimer = time; m_scared = true; }
//     void respawn();
//     [[nodiscard]] float getScaredTimer() const { return m_scaredTimer; }
//
//     // AI and movement
//     virtual void updateMovement(float deltaTime, std::shared_ptr<PacmanModel> pacman, const World& world);
//     void reverseDirection();
//
//     // Setters for external control
//     void setSpawnDelay(float delay) { m_spawnDelay = delay; }
//     void setCanMove(bool canMove) { m_canMove = canMove; }
//     [[nodiscard]] bool isInCenter() const { return m_inCenter; }
//
// protected:
//     Vector2f m_position;
//     std::string m_textureId;
//     Vector2f m_size;
//     int m_direction = 2; // 0=left, 1=down, 2=right, 3=up
//
//     // Ghost specific
//     float m_speed = 0.5f;
//     float m_scaredSpeed = 0.3f;
//     float m_scaredTimer = 0.0f;
//     Vector2f m_spawnPoint;
//     bool m_scared = false;
//     bool m_inCenter = true;
//     float m_spawnDelay = 0.0f;
//     bool m_canMove = false;
//
//     // Helper methods
//     virtual Vector2f calculateChaseDirection(const World& world, std::shared_ptr<PacmanModel> pacman) = 0;
//     std::vector<int> getPossibleDirections(const World& world) const;
//     bool isValidMove(const Vector2f& newPos, const World& world) const;
// };
//
// class RedGhostModel : public GhostModel {
// public:
//     RedGhostModel(const Vector2f& position, const Vector2f& size, const std::string& textureId = "")
//         : GhostModel(position, size, textureId) {}
//
//     void updateMovement(float deltaTime, std::shared_ptr<PacmanModel> pacman, const World& world) override;
//
// private:
//     Vector2f calculateChaseDirection(const World& world, std::shared_ptr<PacmanModel> pacman) override;
//     // Fixed direction ghost - randomly chooses direction at intersections
//     int m_lockedDirection = -1;
//     float m_directionChangeTimer = 0.0f;
// };
//
// class BlueGhostModel : public GhostModel {
// public:
//     BlueGhostModel(const Vector2f& position, const Vector2f& size, const std::string& textureId = "")
//         : GhostModel(position, size, textureId) {}
//
//     void updateMovement(float deltaTime, std::shared_ptr<PacmanModel> pacman, const World& world) override;
//
//     Vector2f calculateChaseDirection(const World& world, std::shared_ptr<PacmanModel> pacman) override;
//     // Moves in direction that minimizes Manhattan distance to Pac-Man's facing direction
// };
//
// class OrangeGhostModel : public GhostModel {
// public:
//     OrangeGhostModel(const Vector2f& position, const Vector2f& size, const std::string& textureId = "")
//         : GhostModel(position, size, textureId) {}
//
//     void updateMovement(float deltaTime, std::shared_ptr<PacmanModel> pacman, const World& world) override;
//
//     Vector2f calculateChaseDirection(const World& world, std::shared_ptr<PacmanModel> pacman) override;
//     // Moves in direction that minimizes Manhattan distance to Pac-Man's facing direction
// };
//
// class PinkGhostModel : public GhostModel {
// public:
//     PinkGhostModel(const Vector2f& position, const Vector2f& size, const std::string& textureId = "")
//         : GhostModel(position, size, textureId) {}
//
//     void updateMovement(float deltaTime, std::shared_ptr<PacmanModel> pacman, const World& world) override;
//
//     Vector2f calculateChaseDirection(const World& world, std::shared_ptr<PacmanModel> pacman) override;
//     // Moves to minimize Manhattan distance directly to Pac-Man
// };
//
// #endif // GHOST_H