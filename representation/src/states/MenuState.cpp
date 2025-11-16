#include "states/MenuState.h"

#include "Game.h"
#include "StateManger.h"
#include "states/LevelState.h"
#include <fstream>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <sstream>

class LevelState;

MenuState::MenuState(StateManager& stateManager, sf::RenderWindow& window)
    : State(stateManager), m_window(window), m_isButtonHovered(false) {
}

void MenuState::initialize() {
    // Reset the view to match current window size
    sf::Vector2u windowSize = m_window.getSize();
    sf::FloatRect visibleArea(0, 0, windowSize.x, windowSize.y);
    m_window.setView(sf::View(visibleArea));

    // Load font
    if (!m_font.loadFromFile("assets/fonts/arial.ttf")) {
        // Handle error appropriately
        return;
    }

    // Title with gradient effect (yellow like Pac-Man)
    m_titleText.setFont(m_font);
    m_titleText.setString("PAC-MAN");
    m_titleText.setCharacterSize(64);
    m_titleText.setFillColor(sf::Color(255, 255, 0)); // Bright yellow
    m_titleText.setStyle(sf::Text::Bold);

    // Play button
    m_playButton.setSize(sf::Vector2f(250, 60));
    m_playButton.setFillColor(sf::Color(50, 50, 200));
    m_playButton.setOutlineColor(sf::Color(255, 255, 0));
    m_playButton.setOutlineThickness(3);

    // Play button text
    m_playButtonText.setFont(m_font);
    m_playButtonText.setString("PLAY");
    m_playButtonText.setCharacterSize(32);
    m_playButtonText.setFillColor(sf::Color::White);
    m_playButtonText.setStyle(sf::Text::Bold);

    // High scores title
    m_highScoreTitle.setFont(m_font);
    m_highScoreTitle.setString("HIGH SCORES");
    m_highScoreTitle.setCharacterSize(32);
    m_highScoreTitle.setFillColor(sf::Color(255, 200, 0)); // Orange-yellow
    m_highScoreTitle.setStyle(sf::Text::Bold);

    // High score background
    m_highScoreBackground.setSize(sf::Vector2f(350, 200));
    m_highScoreBackground.setFillColor(sf::Color(30, 30, 60, 200));
    m_highScoreBackground.setOutlineColor(sf::Color(255, 255, 0));
    m_highScoreBackground.setOutlineThickness(2);

    // Initialize high score texts
    m_highScoreTexts.resize(5);
    for (int i = 0; i < 5; ++i) {
        m_highScoreTexts[i].setFont(m_font);
        m_highScoreTexts[i].setCharacterSize(24);
        m_highScoreTexts[i].setFillColor(sf::Color::White);
        m_highScoreTexts[i].setString(std::to_string(i + 1) + ". -----");
    }

    // Load actual high scores from file
    loadHighScores();

    // Update all positions based on current window size
    updateLayout();
}

void MenuState::updateLayout() {
    sf::Vector2u windowSize = m_window.getSize();
    const float windowWidth = static_cast<float>(windowSize.x);
    const float windowHeight = static_cast<float>(windowSize.y);

    // Center the title horizontally
    sf::FloatRect titleBounds = m_titleText.getLocalBounds();
    m_titleText.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    m_titleText.setPosition(windowWidth / 2, windowHeight * 0.15f);

    // Center the play button
    m_playButton.setOrigin(m_playButton.getSize().x / 2, m_playButton.getSize().y / 2);
    m_playButton.setPosition(windowWidth / 2, windowHeight * 0.30f);

    // Center the play button text
    sf::FloatRect playTextBounds = m_playButtonText.getLocalBounds();
    m_playButtonText.setOrigin(playTextBounds.width / 2, playTextBounds.height / 2);
    m_playButtonText.setPosition(windowWidth / 2, windowHeight * 0.29f);

    // Center the high score title
    sf::FloatRect scoreTitleBounds = m_highScoreTitle.getLocalBounds();
    m_highScoreTitle.setOrigin(scoreTitleBounds.width / 2, scoreTitleBounds.height / 2);
    m_highScoreTitle.setPosition(windowWidth / 2, windowHeight * 0.45f);

    // Center the high score background
    m_highScoreBackground.setOrigin(m_highScoreBackground.getSize().x / 2,
                                     m_highScoreBackground.getSize().y / 2);
    m_highScoreBackground.setPosition(windowWidth / 2, windowHeight * 0.65f);

    // Position high score texts
    for (int i = 0; i < m_highScoreTexts.size(); ++i) {
        m_highScoreTexts[i].setPosition(windowWidth / 2 - 70,
                                        windowHeight * 0.55f + i * 35);
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
        m_highScores.push_back(10000 - (m_highScores.size() * 2000));
    }

    // Sort in descending order
    std::sort(m_highScores.begin(), m_highScores.end(), std::greater<int>());
    updateHighScoreDisplay();
}

void MenuState::updateHighScoreDisplay() {
    for (size_t i = 0; i < m_highScoreTexts.size(); ++i) {
        if (i < m_highScores.size()) {
            std::stringstream scoreStream;
            scoreStream << std::setw(2) << (i + 1) << ". "
                       << std::setw(8) << m_highScores[i];
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

bool MenuState::isMouseOverButton(const sf::Vector2i& mousePos) const {
    sf::FloatRect buttonBounds = m_playButton.getGlobalBounds();
    return buttonBounds.contains(static_cast<float>(mousePos.x),
                                 static_cast<float>(mousePos.y));
}

void MenuState::startGame() {
    m_stateManager.pushState(std::make_unique<LevelState>(m_stateManager, m_window));
}

void MenuState::update(float deltaTime) {
    // Check if mouse is hovering over button
    sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
    m_isButtonHovered = isMouseOverButton(mousePos);

    // Update button appearance based on hover state
    if (m_isButtonHovered) {
        m_playButton.setFillColor(sf::Color(80, 80, 230));
        m_playButton.setOutlineThickness(4);
    } else {
        m_playButton.setFillColor(sf::Color(50, 50, 200));
        m_playButton.setOutlineThickness(3);
    }
}

void MenuState::render() {
    // Dark blue background (like classic Pac-Man)
    m_window.clear(sf::Color(10, 10, 40));

    // Draw high score background first
    m_window.draw(m_highScoreBackground);

    // Draw play button
    m_window.draw(m_playButton);
    m_window.draw(m_playButtonText);

    // Then draw all text elements
    m_window.draw(m_titleText);
    m_window.draw(m_highScoreTitle);

    for (const auto& text : m_highScoreTexts) {
        m_window.draw(text);
    }
}

/**
 * MenuState -> LevelState when button is pressed
 * @param event = current SFML event
 */
void MenuState::handleEvent(const sf::Event& event) {
    // Handle window resize
    if (event.type == sf::Event::Resized) {
        // Update the view to match new window size
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        m_window.setView(sf::View(visibleArea));

        // Recalculate all positions
        updateLayout();
    }

    // Handle mouse button click
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            if (isMouseOverButton(mousePos)) {
                startGame();
            }
        }
    }

    // Keep spacebar functionality as backup
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            startGame();
        }
    }
}