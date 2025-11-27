#include "scoring/Score.h"
#include "core/Stopwatch.h"
#include <cmath>
#include <algorithm>

Score::Score()
    : m_currentScore(0),
      m_timeSinceLastCoin(0.0f),
      m_scoreDecreaseTimer(0.0f) {
    loadHighScores();
}

void Score::update() {
    // This method can be used for periodic updates if needed
    // Currently handled by updateScoreOverTime
}

void Score::updateScoreOverTime(float deltaTime) {
    // Decrease score over time (every second)
    m_scoreDecreaseTimer += deltaTime;
    if (m_scoreDecreaseTimer >= 1.0f) {
        m_currentScore = std::max(0, m_currentScore - static_cast<int>(SCORE_DECREASE_RATE));
        m_scoreDecreaseTimer = 0.0f;
    }

    // Update coin chain timer
    m_timeSinceLastCoin += deltaTime;
}

void Score::onCoinCollected() {
    // Calculate bonus based on time since last coin
    float chainBonus = 1.0f;
//todo change
    if (m_timeSinceLastCoin < MAX_COIN_CHAIN_TIME) {
        // Smaller time window = higher bonus (inverse relationship)
        // When time is small (quick succession), bonus is high
        // When time is large (slow collection), bonus is low
        chainBonus = 1.0f + ( (m_timeSinceLastCoin / MAX_COIN_CHAIN_TIME));
    }

    int coinValue = static_cast<int>(BASE_COIN_SCORE * chainBonus);
    m_currentScore += coinValue;

    // Reset chain timer for next coin
    m_timeSinceLastCoin = 0.0f;
}

void Score::onGhostEaten() {
    m_currentScore += BASE_GHOST_SCORE;
}

void Score::onFruitCollected() {
    m_currentScore += BASE_FRUIT_SCORE;
}

void Score::onLevelCleared() {
    m_currentScore += LEVEL_CLEAR_BONUS;
}

void Score::onPacManDied() {
    // Optional: Penalty for death or just notification
    std::cout << "Pac-Man died! Current score: " << m_currentScore << std::endl;
}

void Score::reset() {
    m_currentScore = 0;
    m_timeSinceLastCoin = 0.0f;
    m_scoreDecreaseTimer = 0.0f;
}

void Score::resetCoinChain() {
    m_timeSinceLastCoin = 0.0f;
}

void Score::saveHighScores() {
    // Add current score to high scores if it qualifies
    addHighScore(m_currentScore);

    std::ofstream file(m_highScoresFile);
    if (file.is_open()) {
        for (int score : m_highScores) {
            file << score << std::endl;
        }
        file.close();
    }
}

void Score::loadHighScores() {
    m_highScores.clear();

    std::ifstream file(m_highScoresFile);
    if (file.is_open()) {
        int score;
        while (file >> score) {
            m_highScores.push_back(score);
        }
        file.close();
    }

    // Ensure we have at least 5 entries
    while (m_highScores.size() < 5) {
        m_highScores.push_back(0);
    }

    // Sort in descending order
    std::sort(m_highScores.rbegin(), m_highScores.rend());
}

void Score::addHighScore(int score) {
    m_highScores.push_back(score);
    // Sort in descending order and keep only top 5
    std::sort(m_highScores.rbegin(), m_highScores.rend());
    if (m_highScores.size() > 5) {
        m_highScores.resize(5);
    }
}