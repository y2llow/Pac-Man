#include "states/LevelState.h"
#include "StateManger.h"
#include "states/GameOverState.h"
#include "states/MenuState.h"
#include "states/PausedState.h"
#include "views/EntityView.h"

#include <memory>

namespace pacman::representation::states {

/**
 * @brief Constructor - Initialiseer LevelState met alle benodigde referenties
 *
 * Deze state is verantwoordelijk voor de daadwerkelijke gameplay.
 * Het maakt een factory en world aan om het spel te runnen.
 */
LevelState::LevelState(StateManager& stateManager, sf::RenderWindow& window, Camera& camera)
    : State(stateManager), m_window(window),
      m_factory(std::make_unique<factory::SFMLFactory>(window, camera)),
      m_camera(camera) {
}

/**
 * @brief Initialiseer het level
 *
 * Verantwoordelijkheden:
 * - Reset de view naar huidige window size
 * - Maak de game world aan met alle entiteiten
 * - Laad fonts en setup UI elementen (score, lives, overlays)
 * - Positioneer alle UI elementen correct
 */
void LevelState::initialize() {
    // Reset de view om te matchen met current window size
    sf::Vector2u windowSize = m_window.getSize();
    sf::FloatRect visibleArea(0, 0, windowSize.x, windowSize.y);
    m_window.setView(sf::View(visibleArea));

    // Update camera met current window size
    m_camera.updateWindowSize();

    // Initialiseer world (laadt map, maakt entiteiten aan)
    m_world = std::make_unique<logic::world::World>(*m_factory, m_camera);
    m_world->initialize();

    // Laad font voor alle text elementen
    if (m_font.loadFromFile("assets/fonts/arial.ttf")) {
        // Initialiseer score text (linksboven)
        m_scoreText.setFont(m_font);
        m_livesText.setFont(m_font);

        m_scoreText.setFillColor(sf::Color::Yellow);
        m_scoreText.setStyle(sf::Text::Bold);

        m_livesText.setFillColor(sf::Color::Yellow);
        m_livesText.setStyle(sf::Text::Bold);

        // Game Over overlay text
        m_gameOverText.setFont(m_font);
        m_gameOverText.setString("GAME OVER");
        m_gameOverText.setFillColor(sf::Color::Red);
        m_gameOverText.setStyle(sf::Text::Bold);

        // Semi-transparante overlay achter game over text
        m_gameOverOverlay.setFillColor(sf::Color(0, 0, 0, 180));

        // Level Complete overlay text (gele achtergrond)
        m_levelCompleteText.setFont(m_font);
        m_levelCompleteText.setFillColor(sf::Color::Yellow);
        m_levelCompleteText.setStyle(sf::Text::Bold);

        m_levelCompleteOverlay.setFillColor(sf::Color(255, 255, 0, 120));
    }

    // Positioneer alle UI elementen correct
    updateLayout();
}

/**
 * @brief Update de posities en groottes van alle UI elementen
 *
 * Wordt aangeroepen bij:
 * - Initialisatie
 * - Window resize
 * - Level complete (om nieuwe level nummer te tonen)
 *
 * Zorgt ervoor dat UI elementen altijd correct geschaald en gepositioneerd zijn,
 * ongeacht window grootte.
 */
void LevelState::updateLayout() {
    logic::Vector2f windowSize;
    windowSize.x = m_window.getSize().x;
    windowSize.y = m_window.getSize().y;

    // Update camera met nieuwe window size
    m_camera.updateWindowSize(logic::Vector2f(windowSize));

    // Reset de view
    sf::FloatRect visibleArea(0, 0, windowSize.x, windowSize.y);
    m_window.setView(sf::View(visibleArea));

    // Update factory (zorgt dat views correct geschaald worden)
    if (m_factory) {
        m_factory->handleResize(windowSize);
    }

    // Schaal text grootte op basis van window hoogte (7% van hoogte)
    unsigned int scaledCharSize = static_cast<unsigned int>(windowSize.y * 0.07f);
    m_scoreText.setCharacterSize(scaledCharSize);
    m_livesText.setCharacterSize(scaledCharSize);

    // Update text content om correcte bounds te krijgen
    int currentScore = m_world ? m_world->Getscore()->getCurrentScore() : 0;
    int currentLives = m_world ? m_world->Getscore()->getLives() : 5;

    m_scoreText.setString("SCORE: " + std::to_string(currentScore));
    m_livesText.setString("Lives: " + std::to_string(currentLives));

    // Positioneer score text linksboven met padding
    float padding = windowSize.x * 0.005f;
    m_scoreText.setPosition(padding, padding);

    // Positioneer lives text rechtsboven met padding
    sf::FloatRect livesBounds = m_livesText.getLocalBounds();
    m_livesText.setPosition(windowSize.x - livesBounds.width - padding, 0);

    // === Game Over Text - Schaalbaar ===
    unsigned int gameOverCharSize = static_cast<unsigned int>(windowSize.y * 0.12f);
    m_gameOverText.setCharacterSize(gameOverCharSize);

    // Schaal text als het te breed is voor window
    sf::FloatRect gameOverBounds = m_gameOverText.getLocalBounds();
    float maxWidthGameOver = windowSize.x * 0.9f;

    if (gameOverBounds.width > maxWidthGameOver) {
        float scaleFactor = maxWidthGameOver / gameOverBounds.width;
        gameOverCharSize = static_cast<unsigned int>(gameOverCharSize * scaleFactor);
        m_gameOverText.setCharacterSize(gameOverCharSize);
        gameOverBounds = m_gameOverText.getLocalBounds();
    }

    // Center in het midden van screen
    m_gameOverText.setOrigin(gameOverBounds.width / 2, gameOverBounds.height / 2);
    m_gameOverText.setPosition(windowSize.x / 2, windowSize.y / 2);
    m_gameOverOverlay.setSize(sf::Vector2f(windowSize.x, windowSize.y));

    // === Level Complete Text - Schaalbaar ===
    unsigned int levelCompleteCharSize = static_cast<unsigned int>(windowSize.y * 0.12f);
    m_levelCompleteText.setCharacterSize(levelCompleteCharSize);

    if (m_isLevelComplete) {
        m_levelCompleteText.setString("LEVEL " + std::to_string(m_completedLevel) + " COMPLETE!");
    }

    sf::FloatRect levelCompleteBounds = m_levelCompleteText.getLocalBounds();
    float maxWidth = windowSize.x * 0.9f;

    if (levelCompleteBounds.width > maxWidth) {
        float scaleFactor = maxWidth / levelCompleteBounds.width;
        levelCompleteCharSize = static_cast<unsigned int>(levelCompleteCharSize * scaleFactor);
        m_levelCompleteText.setCharacterSize(levelCompleteCharSize);
        levelCompleteBounds = m_levelCompleteText.getLocalBounds();
    }

    // Center in het midden van screen
    m_levelCompleteText.setOrigin(levelCompleteBounds.width / 2, levelCompleteBounds.height / 2);
    m_levelCompleteText.setPosition(windowSize.x / 2, windowSize.y / 2);
    m_levelCompleteOverlay.setSize(sf::Vector2f(windowSize.x, windowSize.y));
}

/**
 * @brief Hoofd update loop voor gameplay
 *
 * Update flow:
 * 1. Check game over condition
 * 2. Handle game over timer (3 sec delay)
 * 3. Handle level complete timer (2 sec delay)
 * 4. Normal gameplay: input → world update → view updates
 *
 * @param deltaTime Tijd sinds vorige frame (voor frame-rate independent movement)
 */
void LevelState::update(float deltaTime) {
    // === GAME OVER HANDLING ===
    // Check of game over moet worden getriggerd (geen levens meer)
    if (m_world && m_world->getScore().getLives() <= 0 && !m_isGameOver) {
        m_isGameOver = true;
        m_gameOverTimer = 0.0f;
        m_world->Getscore()->saveHighScores();  // Save scores naar file
    }

    // Als game over is, toon overlay en wacht 3 seconden
    if (m_isGameOver) {
        m_gameOverTimer += deltaTime;

        // Update Pacman death animatie tijdens game over
        if (m_world && m_world->getPacman()) {
            m_world->getPacman()->update(deltaTime);

            // Update views voor animaties
            for (const auto& view : m_factory->getViews()) {
                if (view) {
                    view->update(deltaTime);
                }
            }
        }

        // Na 3 seconden, terug naar menu
        if (m_gameOverTimer >= GAME_OVER_DISPLAY_TIME) {
            m_stateManager.switchToState(std::make_unique<MenuState>(m_stateManager, m_window, m_camera));
            return;
        }
        return;  // Skip normale game logic tijdens game over
    }

    // === LEVEL COMPLETE HANDLING ===
    // Als level complete is, toon overlay en wacht 2 seconden
    if (m_isLevelComplete) {
        m_levelCompleteTimer += deltaTime;

        // Na 2 seconden, ga naar volgend level
        if (m_levelCompleteTimer >= LEVEL_COMPLETE_DISPLAY_TIME) {
            m_isLevelComplete = false;
            m_levelCompleteTimer = 0.0f;

            if (m_world) {
                m_world->advanceToNextLevel();  // Reset world voor volgend level
                m_completedLevel = m_world->getCurrentLevel();
            }
        }
        return;  // Skip normale game logic tijdens level complete
    }

    // === NORMALE GAMEPLAY UPDATES ===
    handleInput();  // Verwerk keyboard input

    // Update world (beweging, collisions, AI)
    if (m_world) {
        m_world->update(deltaTime); // Onze Logic updaten

        // Check of level net is voltooid (alle coins verzameld)
        if (m_world->areAllCoinsCollected() && !m_isLevelComplete) {
            m_isLevelComplete = true;
            m_levelCompleteTimer = 0.0f;
            m_completedLevel = m_world->getCurrentLevel();

            // Update text voor nieuwe level nummer
            m_levelCompleteText.setString("LEVEL " + std::to_string(m_completedLevel) + " COMPLETE!");
            updateLayout();
        }
    }

    // Update alle views (animaties, posities)
    if (m_factory) {
        for (const auto& view : m_factory->getViews()) {
            if (view) {
                view->update(deltaTime);
            }
        }
        m_factory->cleanupCollectedViews();  // Verwijder views van verzamelde items
    }

    // Update UI text met huidige score en lives
    if (m_world) {
        int scoreValue = m_world->Getscore()->getCurrentScore();
        int livesValue = m_world->Getscore()->getLives();

        m_scoreText.setString("SCORE: " + std::to_string(scoreValue));
        m_livesText.setString("Lives: " + std::to_string(livesValue));

        // Herpositioneer lives text (width kan veranderen bij cijfer change)
        sf::FloatRect livesBounds = m_livesText.getLocalBounds();
        float padding = m_window.getSize().x * 0.005f;
        m_livesText.setPosition(m_window.getSize().x - livesBounds.width - padding * 3, padding);
    }
}

/**
 * @brief Render alle game elementen en overlays
 *
 * Render volgorde (van achter naar voor):
 * 1. Donkerblauwe achtergrond
 * 2. Game entiteiten (walls, coins, pacman, ghosts)
 * 3. UI text (score, lives)
 * 4. Overlays (level complete of game over indien actief)
 */
void LevelState::render() {
    // Clear window met donkerblauwe kleur
    m_window.clear(sf::Color(5, 5, 20));

    // Teken alle game entiteiten (via hun views)
    for (const auto& view : m_factory->getViews()) {
        if (view) {
            view->draw(m_window);
        }
    }

    // Teken UI text
    m_window.draw(m_scoreText);
    m_window.draw(m_livesText);

    // Teken Level Complete overlay indien actief
    if (m_isLevelComplete) {
        m_window.draw(m_levelCompleteOverlay);
        m_window.draw(m_levelCompleteText);
    }

    // Teken Game Over overlay indien actief
    if (m_isGameOver) {
        m_window.draw(m_gameOverOverlay);
        m_window.draw(m_gameOverText);
    }
}

/**
 * @brief Verwerk keyboard input en buffer Pacman's richting
 *
 * Input wordt gebufferd omdat Pacman niet altijd meteen kan draaien
 * (bijv. als hij net voorbij een bocht is). De buffer wordt verwerkt
 * in World::handlePredictivePacmanMovement().
 *
 * Arrow keys bepalen bewegingsrichting:
 * - Left: 0
 * - Down: 1
 * - Right: 2
 * - Up: 3
 */
void LevelState::handleInput() {
    if (!m_world) return;

    auto pacman = m_world->getPacman();
    if (!pacman) return;

    // Check welke arrow key is ingedrukt en buffer de richting
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        pacman->bufferDirection(0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        pacman->bufferDirection(1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        pacman->bufferDirection(2);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        pacman->bufferDirection(3);
    }
}

/**
 * @brief Handle SFML events (keyboard, window resize)
 *
 * Event handling:
 * - Window resize: Recalculeer alle UI posities en sizes
 * - ESC key: Open pause menu (tenzij in level complete/game over)
 *
 * @param event SFML event om te verwerken
 */
void LevelState::handleEvent(const sf::Event& event) {
    // Altijd resize events eerst afhandelen
    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        m_window.setView(sf::View(visibleArea));
        updateLayout();
        return;
    }

    // Verwerk toetsenbord events
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Escape:
            // Alleen pauzeren als we niet in level complete of game over zijn
            if (!m_isLevelComplete && !m_isGameOver) {
                m_stateManager.pushState(std::make_unique<PausedState>(m_stateManager, m_window, m_camera));
            }
            break;
        default:
            break;
        }
    }
}

} // namespace pacman::representation::states