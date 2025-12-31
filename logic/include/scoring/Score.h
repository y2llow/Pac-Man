#ifndef SCORE_H
#define SCORE_H

#include "patterns/Observer.h"
#include "core/Stopwatch.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>

namespace pacman::logic::scoring {

class Score : public Observer {
public:
    Score();
    ~Score() = default;

    void update() override;
    void onCoinCollected();
    void onGhostEaten();
    void onPacManDied();
    void onFruitCollected();
    void onLevelCleared();

    [[nodiscard]] int getCurrentScore() const { return m_currentScore; }
    [[nodiscard]] int getLives() const { return m_lives; }
    void setLives(int lives) { m_lives = lives; }
    void loseLife();
    void reset();

    void saveHighScores();
    void loadHighScores();
    void addHighScore(int score);
    const std::vector<int>& getHighScores() const { return m_highScores; }

    void updateScoreOverTime(float deltaTime);
    void resetCoinChain();

private:
    int m_currentScore;
    std::vector<int> m_highScores;
    std::string m_highScoresFile = "assets/highscores/highscore.txt";

    float m_timeSinceLastCoin;
    float m_scoreDecreaseTimer;
    int m_lives = 5;

    static constexpr int SCORE_DECREASE_RATE = 5.0f;
    static constexpr float MAX_COIN_CHAIN_TIME = 3.0f;
    static constexpr int BASE_COIN_SCORE = 10;
    static constexpr int BASE_GHOST_SCORE = 100;
    static constexpr int BASE_FRUIT_SCORE = 50;
    static constexpr int LEVEL_CLEAR_BONUS = 250;
    static constexpr int PACMAN_DEATH_BONUS = 125;
};

} // namespace pacman::logic::scoring



#endif
