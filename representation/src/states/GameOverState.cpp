#include "states/GameOverState.h"
#include "StateManger.h"
#include "states/MenuState.h"
#include "states/LevelState.h"

#include <iostream>

GameOverState::GameOverState(StateManager& stateManager, sf::RenderWindow& window, Camera& camera)
    : State(stateManager), m_window(window), m_camera(camera) {
}

void GameOverState::initialize() {
    // Update camera with current window size
    m_camera.updateWindowSize();

    if (m_font.loadFromFile("assets/fonts/arial.ttf")) {
        // Use camera to get current window size
        sf::Vector2f windowSize = m_camera.getWindowSize();
        const float windowWidth = windowSize.x;
        const float windowHeight = windowSize.y;

        // Create the overlay
        m_overlay.setSize(sf::Vector2f(windowWidth, windowHeight));
        m_overlay.setFillColor(sf::Color(50, 0, 0, 180)); // Roodige overlay voor game over

        // Create the background panel using camera for sizing
        float panelWidth = windowWidth * 0.6f;   // 60% of window width
        float panelHeight = windowHeight * 0.3f; // 30% of window height
        m_backgroundPanel.setSize(sf::Vector2f(panelWidth, panelHeight));
        m_backgroundPanel.setFillColor(sf::Color(60, 30, 30, 220)); // Donkerrood
        m_backgroundPanel.setOutlineColor(sf::Color(255, 0, 0));    // Rode outline
        m_backgroundPanel.setOutlineThickness(3);
        m_backgroundPanel.setOrigin(panelWidth / 2, panelHeight / 2);
        m_backgroundPanel.setPosition(windowWidth / 2, windowHeight / 2);

        // Initialize text objects with the font
        m_gameOverText.setFont(m_font);
        m_continueText.setFont(m_font);
        m_menuText.setFont(m_font);

        // Set text content and styling
        m_gameOverText.setString("GAME OVER");
        m_gameOverText.setCharacterSize(60);
        m_gameOverText.setFillColor(sf::Color::Red);
        m_gameOverText.setStyle(sf::Text::Bold);

        m_continueText.setString("Press ENTER to Try Again");
        m_continueText.setCharacterSize(34);
        m_continueText.setFillColor(sf::Color::White);

        m_menuText.setString("Press M for Main Menu");
        m_menuText.setCharacterSize(34);
        m_menuText.setFillColor(sf::Color::White);

        // Initialize all UI elements
        updateLayout();
    } else {
        // Handle font loading error
        std::cout << "Failed to load font for GameOverState" << std::endl;
    }
}

void GameOverState::updateLayout() {
    // Get current window size from camera
    sf::Vector2f windowSize = m_camera.getWindowSize();
    const float windowWidth = windowSize.x;
    const float windowHeight = windowSize.y;

    // Update overlay size
    m_overlay.setSize(sf::Vector2f(windowWidth, windowHeight));

    // Update background panel size and position
    float panelWidth = windowWidth * 0.6f;
    float panelHeight = windowHeight * 0.3f;
    m_backgroundPanel.setSize(sf::Vector2f(panelWidth, panelHeight));
    m_backgroundPanel.setOrigin(panelWidth / 2, panelHeight / 2);
    m_backgroundPanel.setPosition(windowWidth / 2, windowHeight / 2);

    // Update text positions using percentages
    auto updateTextPosition = [&](sf::Text& text, float verticalPercentage) {
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2, textBounds.height / 2);
        text.setPosition(windowWidth / 2, windowHeight * verticalPercentage);
    };

    // Position all texts
    updateTextPosition(m_gameOverText, 0.35f);   // 35% from top
    updateTextPosition(m_continueText, 0.50f);   // 50% from top
    updateTextPosition(m_menuText, 0.58f);       // 58% from top
}

void GameOverState::update(float deltaTime) {
    // Blinking effect for instructions
    m_blinkTimer += deltaTime;

    if (m_blinkTimer >= 0.8f) {
        sf::Color newColor = (m_continueText.getFillColor() == sf::Color::White) ?
                            sf::Color(150, 150, 150) : sf::Color::White;

        m_continueText.setFillColor(newColor);
        m_menuText.setFillColor(newColor);
        m_blinkTimer = 0;
    }
}

void GameOverState::render() {
    // Draw semi-transparent overlay
    m_window.draw(m_overlay);

    // Draw background panel
    m_window.draw(m_backgroundPanel);

    // Draw all text elements
    m_window.draw(m_gameOverText);
    m_window.draw(m_continueText);
    m_window.draw(m_menuText);
}

void GameOverState::handleEvent(const sf::Event& event) {
    // Handle window resize
    if (event.type == sf::Event::Resized) {
        // Update camera with new window size
        m_camera.updateWindowSize();

        // Recalculate all UI positions
        updateLayout();
    }

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Enter:
        case sf::Keyboard::Space:
            // Restart the game
            m_stateManager.switchToState(std::make_unique<LevelState>(m_stateManager, m_window, m_camera));
            break;
        case sf::Keyboard::M:
        case sf::Keyboard::Escape:
            m_stateManager.switchToState(std::make_unique<MenuState>(m_stateManager, m_window, m_camera));
            break;
        }
    }

    // Handle mouse clicks for future button implementation
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = m_window.mapPixelToCoords(
                sf::Vector2i(event.mouseButton.x, event.mouseButton.y)
            );
            // Add button click detection here if needed
        }
    }
}