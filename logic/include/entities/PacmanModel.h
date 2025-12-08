#ifndef PACMAN_H
#define PACMAN_H

#include "EntityModel.h"
#include "world/World.h"

class World;

class PacmanModel : public EntityModel {
public:
     PacmanModel(const Vector2f& position, const Vector2f& size) ;

    // overwritten functiosn from entityModel
     void update(float deltaTime) override ;
    [[nodiscard]]  Vector2f getPosition() const override {return m_position;}
     void setPosition(const Vector2f& position) override;
    [[nodiscard]]  Vector2f getSize() const override{return m_size;}

    // Death animation methods
    void startDeathAnimation();
    bool isDying() const { return m_isDying; }
    bool isDeathAnimationComplete() const { return m_deathAnimationComplete; }
    void resetDeathAnimation();

    // Pacman specific funcitons
    Vector2f CheckTunneling(Vector2f position) const;
    void loseLife();

    [[nodiscard]] Vector2f calculateNextPosition(float deltaTime) const;
    void setDirection(int newDirection);
    void applyMovement(const Vector2f& newPosition);
    int getDirection() const { return m_direction; }

    // Input buffering methodes
    void bufferDirection(int newDirection);
    void clearBufferedDirection();
    [[nodiscard]] int getBufferedDirection() const { return m_bufferedDirection; }

    // Nieuwe methodes voor movement logic
    [[nodiscard]] bool canMoveInDirection(int direction, const World& world, float deltaTime) const;
    [[nodiscard]] Vector2f calculatePositionInDirection(const Vector2f& startPos, int direction, float deltaTime) const;
    [[nodiscard]] float getSpeed() const { return PACMAN_SPEED; }
    [[nodiscard]] bool getDeathScoreAwarded() const {return m_deathScoreAwarded; }
    void setDeathScoreAwarded(bool scoreAwarded) {m_deathScoreAwarded = scoreAwarded; }

    [[nodiscard]]Vector2f getSpawnPoint() const {return m_spawnpoint;}
private:
    //default privates
    Vector2f m_position;
    std::string m_textureId;
    Vector2f m_size;

    //pacman specific privates
    int m_direction = 3;        // Huidige bewegingrichting
    int m_bufferedDirection = -1; // -1 = geen buffer, 0-3 = gebufferde richting
    float PACMAN_SPEED = 0.5;
    float m_lastMove{};

    Vector2f m_spawnpoint;

    // Death animation state
    bool m_isDying = false;
    bool m_deathAnimationComplete = false;
    bool m_deathScoreAwarded = false;
    float m_deathAnimationTimer = 0.0f;
    static constexpr float DEATH_ANIMATION_DURATION = 2.0f; // 2 seconds for full death animation


};

#endif //PACMAN_H
