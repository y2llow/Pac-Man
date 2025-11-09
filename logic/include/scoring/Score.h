#ifndef SCORE_H
#define SCORE_H

#include "patterns/Observer.h"
#include <string>

// Forward declaration
class Subject;

class Score : public Observer {
public:
    Score();

    void update() override;

    // Different update methods for different events
    void onCoinCollected();
    void onGhostEaten();
    void onPacManDied();

    int getCurrentScore() const { return m_currentScore; }
    void reset();

private:
    int m_currentScore;
    int m_highScore;
};

#endif
