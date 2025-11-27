#ifndef SCORE_H
#define SCORE_H

#include "patterns/Observer.h"
#include "core/Stopwatch.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>

// Forward declaration
class Subject;

class Score : public Observer {
public:
    Score();
    ~Score() = default;

    void update() override;

    // Different update methods for different events
    void onCoinCollected();
    void onGhostEaten();
    void onPacManDied();
    void onFruitCollected();
    void onLevelCleared();

    [[nodiscard]] int getCurrentScore() const { return m_currentScore; }
    void reset();

    // High score management
    void saveHighScores();
    void loadHighScores();
    void addHighScore(int score);
    const std::vector<int>& getHighScores() const { return m_highScores; }

    // Time-based scoring methods
    void updateScoreOverTime(float deltaTime);
    void resetCoinChain();

private:
    int m_currentScore;
    std::vector<int> m_highScores; // Top 5 scores
    std::string m_highScoresFile = "assets/highscores/highscore.txt";

    // Time-based scoring variables
    float m_timeSinceLastCoin;
    float m_scoreDecreaseTimer;
    static constexpr int SCORE_DECREASE_RATE = 5.0f; // Points per second
    static constexpr float MAX_COIN_CHAIN_TIME = 3.0f; // Max time for chain bonus
    static constexpr int BASE_COIN_SCORE = 10;
    static constexpr int BASE_GHOST_SCORE = 50;
    static constexpr int BASE_FRUIT_SCORE = 20;
    static constexpr int LEVEL_CLEAR_BONUS = 100;
};

#endif