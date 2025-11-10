#include "scoring/Score.h"

Score::Score()
    : m_currentScore(0) {  // Implementatie hier
}

void Score::update() {
    // Implementatie later toevoegen
}

void Score::onCoinCollected() {
    // Implementatie later toevoegen
}

void Score::onGhostEaten() {
    // Implementatie later toevoegen
}

void Score::onPacManDied() {
    // Implementatie later toevoegen
}

void Score::reset() {
    m_currentScore = 0;
}