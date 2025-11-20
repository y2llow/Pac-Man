#include "scoring/Score.h"

Score::Score()
    : m_currentScore(0) {  // Implementatie hier
}

void Score::update() {
    // Implementatie later toevoegen
}

void Score::onCoinCollected() {
    m_currentScore = m_currentScore + 100;
}

void Score::onGhostEaten() {
    m_currentScore = m_currentScore + 500;
}

void Score::onPacManDied() {
    // Implementatie later toevoegen
}

void Score::reset() {
    m_currentScore = 0;
}