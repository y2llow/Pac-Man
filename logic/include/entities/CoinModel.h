#ifndef COIN_MODEL_H
#define COIN_MODEL_H

#include "entities/EntityModel.h"
#include <string>

class CoinModel : public EntityModel {
public:
    CoinModel(const Vector2f& position, const Vector2f& size, const std::string& textureId = "");

    // Entity interface implementation
    void update(float deltaTime) override;
    [[nodiscard]] Vector2f getPosition() const override { return m_position; }
    void setPosition(const Vector2f& position) override;
    [[nodiscard]] Vector2f getSize() const override { return m_size; }
    [[nodiscard]] bool getScoreAwarded() const {return m_scoreAwarded; }
    void setScoreAwarded(bool scoreAwarded) {m_scoreAwarded = scoreAwarded; }

    // Coin-specific functionality
    void collect();  // This will notify observers!
    
    [[nodiscard]] bool isCollected() const { return m_collected; }
    [[nodiscard]] const std::string& getTextureId() const { return m_textureId; }

private:
    Vector2f m_position;
    std::string m_textureId;
    Vector2f m_size;

    // Coin Specific privates
    bool m_collected = false;
    bool m_scoreAwarded = false;
};

#endif