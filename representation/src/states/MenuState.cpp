#include "states/MenuState.h"

#include "Game.h"
#include "StateManger.h"
#include "states/LevelState.h"
#include <fstream>
#include <memory>
#include <iomanip>  // For std::setw

class LevelState;

MenuState::MenuState(StateManager& stateManager, sf::RenderWindow& window)
    : State(stateManager), m_window(window) {
}

void MenuState::initialize() {
    // Load font
    if (m_font.loadFromFile("assets/fonts/arial.ttf")) {
        // Window dimensions for centering
        const float windowWidth = pacman::representation::Game::WINDOW_WIDTH;

        // Title with gradient effect (yellow like Pac-Man)
        m_titleText.setFont(m_font);
        m_titleText.setString("PAC-MAN");
        m_titleText.setCharacterSize(64);
        m_titleText.setFillColor(sf::Color(255, 255, 0)); // Bright yellow
        m_titleText.setStyle(sf::Text::Bold);

        // Center the title horizontally
        sf::FloatRect titleBounds = m_titleText.getLocalBounds();
        m_titleText.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
        m_titleText.setPosition(windowWidth / 2, 120);

        // Play instruction
        m_playText.setFont(m_font);
        m_playText.setString("PRESS SPACE TO PLAY");
        m_playText.setCharacterSize(28);
        m_playText.setFillColor(sf::Color::White);
        m_playText.setStyle(sf::Text::Bold);

        // Center the play text
        sf::FloatRect playBounds = m_playText.getLocalBounds();
        m_playText.setOrigin(playBounds.width / 2, playBounds.height / 2);
        m_playText.setPosition(windowWidth / 2, 220);

        // High scores title
        m_highScoreTitle.setFont(m_font);
        m_highScoreTitle.setString("HIGH SCORES");
        m_highScoreTitle.setCharacterSize(32);
        m_highScoreTitle.setFillColor(sf::Color(255, 200, 0)); // Orange-yellow
        m_highScoreTitle.setStyle(sf::Text::Bold);

        // Center the high score title
        sf::FloatRect scoreTitleBounds = m_highScoreTitle.getLocalBounds();
        m_highScoreTitle.setOrigin(scoreTitleBounds.width / 2, scoreTitleBounds.height / 2);
        m_highScoreTitle.setPosition(windowWidth / 2, 300);

        // High score background - centered
        m_highScoreBackground.setSize(sf::Vector2f(350, 200));
        m_highScoreBackground.setFillColor(sf::Color(30, 30, 60, 200));
        m_highScoreBackground.setOutlineColor(sf::Color(255, 255, 0));
        m_highScoreBackground.setOutlineThickness(2);
        m_highScoreBackground.setOrigin(175, 100); // Center the background
        m_highScoreBackground.setPosition(windowWidth / 2, 440);

        // Initialize high score texts with centered alignment
        m_highScoreTexts.resize(5);
        for (int i = 0; i < 5; ++i) {
            m_highScoreTexts[i].setFont(m_font);
            m_highScoreTexts[i].setCharacterSize(24);
            m_highScoreTexts[i].setFillColor(sf::Color::White);

            // Position centered with proper vertical spacing
            m_highScoreTexts[i].setPosition(windowWidth / 2-70 , 350 + i * 35);
            m_highScoreTexts[i].setString(std::to_string(i + 1) + ". -----");
        }

        // Load actual high scores from file
        loadHighScores();
    }
}

void MenuState::loadHighScores() {
    std::ifstream file("assets/highscores/highscore.txt");
    m_highScores.clear();

    if (file.is_open()) {
        int score;
        while (file >> score && m_highScores.size() < 5) {
            m_highScores.push_back(score);
        }
        file.close();
    }

    // Fill with default scores if file doesn't exist or has too few scores
    while (m_highScores.size() < 5) {
        m_highScores.push_back(10000 - (m_highScores.size() * 2000)); // 10000, 8000, 6000, etc.
    }

    // Sort in descending order
    std::sort(m_highScores.begin(), m_highScores.end(), std::greater<int>());
    updateHighScoreDisplay();
}

void MenuState::updateHighScoreDisplay() {
    for (int i = 0; i < m_highScoreTexts.size(); ++i) {
        if (i < m_highScores.size()) {
            // Format with leading zeros and proper spacing
            std::stringstream scoreStream;
            scoreStream << std::setw(2) << (i + 1) << ". " << std::setw(8) << m_highScores[i];
            m_highScoreTexts[i].setString(scoreStream.str());

            // Color the top 3 scores differently
            if (i == 0) {
                m_highScoreTexts[i].setFillColor(sf::Color(255, 215, 0)); // Gold
            } else if (i == 1) {
                m_highScoreTexts[i].setFillColor(sf::Color(192, 192, 192)); // Silver
            } else if (i == 2) {
                m_highScoreTexts[i].setFillColor(sf::Color(205, 127, 50)); // Bronze
            } else {
                m_highScoreTexts[i].setFillColor(sf::Color::White);
            }
        }
    }
}

void MenuState::update(float deltaTime) {
    // Optional: Add blinking effect for play text
    static float blinkTimer = 0;
    blinkTimer += deltaTime;

    if (blinkTimer >= 0.8f) { // Blink every 0.8 seconds
        m_playText.setFillColor(m_playText.getFillColor() == sf::Color::White ?
                               sf::Color(150, 150, 150) : sf::Color::White);
        blinkTimer = 0;
    }
}

void MenuState::render() {
    // Dark blue background (like classic Pac-Man)
    m_window.clear(sf::Color(10, 10, 40));

    // Draw high score background first
    m_window.draw(m_highScoreBackground);

    // Then draw all text elements
    m_window.draw(m_titleText);
    m_window.draw(m_playText);
    m_window.draw(m_highScoreTitle);

    for (const auto& text : m_highScoreTexts) {
        m_window.draw(text);
    }
}

/**
 * MenuState -> LevelState when spacebar is pressed
 * @param event = current SFML event
 */
void MenuState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            m_stateManager.pushState(std::make_unique<LevelState>(m_stateManager, m_window));
        }
    }
}