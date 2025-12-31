#include "scoring/Score.h"
#include "core/Stopwatch.h"
#include <cmath>
#include <algorithm>

pacman::logic::scoring::Score::Score()
    : m_currentScore(0),
      m_timeSinceLastCoin(0.0f),
      m_scoreDecreaseTimer(0.0f) {
    loadHighScores();
}

void pacman::logic::scoring::Score::update() {
    // This method can be used for periodic updates if needed
    // Currently handled by updateScoreOverTime
}

void pacman::logic::scoring::Score::updateScoreOverTime(float deltaTime) {
    // Decrease score over time (every second)
    m_scoreDecreaseTimer += deltaTime;
    if (m_scoreDecreaseTimer >= 1.0f) {
        m_currentScore = std::max(0, (m_currentScore - SCORE_DECREASE_RATE));
        m_scoreDecreaseTimer = 0.0f;
    }

    // Update coin chain timer
    m_timeSinceLastCoin += deltaTime;
}

void pacman::logic::scoring::Score::onCoinCollected() {
    // Calculate bonus based on time since last coin
    int timeBonus = 1 + m_timeSinceLastCoin;
    int coinValue = std::min(BASE_COIN_SCORE * timeBonus, 250); // can max be 500
    m_currentScore += coinValue;

    // Reset chain timer for next coin
    m_timeSinceLastCoin = 0.0f;
}

void pacman::logic::scoring::Score::onGhostEaten() {
    m_currentScore += BASE_GHOST_SCORE;
}

void pacman::logic::scoring::Score::onFruitCollected() {
    m_currentScore += BASE_FRUIT_SCORE;
}

void pacman::logic::scoring::Score::onLevelCleared() {
    m_currentScore += LEVEL_CLEAR_BONUS;
}

void pacman::logic::scoring::Score::onPacManDied() {
    // Optional: Penalty for death or just notification
    m_currentScore += PACMAN_DEATH_BONUS;

    std::cout << "Pac-Man died! Current score: " << m_currentScore << std::endl;
}

void pacman::logic::scoring::Score::loseLife() {
    m_lives = m_lives - 1;
}


void pacman::logic::scoring::Score::reset() {
    m_currentScore = 0;
    m_timeSinceLastCoin = 0.0f;
    m_scoreDecreaseTimer = 0.0f;
}

void pacman::logic::scoring::Score::resetCoinChain() {
    m_timeSinceLastCoin = 0.0f;
}

void pacman::logic::scoring::Score::saveHighScores() {
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

void pacman::logic::scoring::Score::loadHighScores() {
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

void pacman::logic::scoring::Score::addHighScore(int score) {
    m_highScores.push_back(score);
    // Sort in descending order and keep only top 5
    std::sort(m_highScores.rbegin(), m_highScores.rend());
    if (m_highScores.size() > 5) {
        m_highScores.resize(5);
    }
}