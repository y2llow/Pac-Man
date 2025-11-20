#ifndef SCORE_H
#define SCORE_H

#include "patterns/Observer.h"
#include <string>
#include <vector>

// Forward declaration
class Subject;

class Score : public Observer {
public:
    Score();  // Alleen declaratie
    ~Score() = default;

    void update() override;

    // Different update methods for different events
    void onCoinCollected();
    void onGhostEaten();
    void onPacManDied();

    [[nodiscard]] int getCurrentScore() const { return m_currentScore; }
    void reset();

private:
    int m_currentScore;
    std::vector<int> m_highScores; // Top 5 scores
    std::string m_highScoresFile = "assets/highscores/highscore.txt";
};

#endif

// public:
// Score();
//
// // Observer pattern - reageert op game events
// void update() override;
//
// // Score modifiers voor verschillende events
// void addCoinScore();
// void addGhostScore();
// void addFruitScore();
// void addLevelClearBonus();
//
// // High score management
// void saveHighScores();
// void loadHighScores();
// void addHighScore(int score);
// const std::vector<int>& getHighScores() const { return m_highScores; }
//
// // Current score
// int getCurrentScore() const { return m_currentScore; }
// void resetCurrentScore() { m_currentScore = 0; }
// };
