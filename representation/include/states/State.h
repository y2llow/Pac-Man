#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
namespace pacman::representation {
class StateManager;  // Forward declaration

/**
 * @class State
 * @brief Abstract base class for all game states using the State Pattern
 *
 * This class implements the State design pattern, allowing the game to switch
 * between different states (Menu, Level, Paused, GameOver) seamlessly.
 * Each state encapsulates its own behavior, rendering, and event handling.
 *
 * Design Pattern: State Pattern
 * - Allows an object (Game) to alter its behavior when its internal state changes
 * - Each concrete state (MenuState, LevelState, etc.) implements this interface
 * - StateManager handles the state stack and transitions
 *
 * Key Benefits:
 * - Clean separation of concerns (each state manages its own logic)
 * - Easy to add new states without modifying existing code
 * - State-specific behavior is encapsulated in concrete state classes
 */
class State {
public:
    /**
     * @brief Constructor that stores reference to the StateManager
     * @param stateManager Reference to the StateManager controlling state transitions
     *
     * Each state needs access to the StateManager to trigger state transitions
     * (e.g., MenuState pushing LevelState, or LevelState pushing PausedState)
     */
    explicit State(StateManager& stateManager) : m_stateManager(stateManager) {}

    /**
     * @brief Virtual destructor to ensure proper cleanup of derived classes
     *
     * Essential for polymorphic deletion through base class pointers
     */
    virtual ~State() = default;

    // ========================================================================
    // PURE VIRTUAL METHODS - Must be implemented by all concrete states
    // ========================================================================

    /**
     * @brief Initialize state-specific resources
     *
     * Called once when the state is first created and pushed onto the stack.
     * Used for:
     * - Loading fonts, textures, and other resources
     * - Setting up UI elements (buttons, text, overlays)
     * - Initializing game objects specific to this state
     *
     * Example: MenuState loads high scores, LevelState creates the game world
     */
    virtual void initialize() = 0;

    /**
     * @brief Update state logic based on elapsed time
     * @param deltaTime Time elapsed since last frame in seconds
     *
     * Called every frame to update:
     * - Game logic (entity movement, collision detection)
     * - Animations (blinking text, sprite animations)
     * - Timers (game over countdown, level complete timer)
     * - Input handling (via handleInput or buffered input)
     *
     * The deltaTime parameter ensures frame-rate independent updates
     */
    virtual void update(float deltaTime) = 0;

    /**
     * @brief Render all visual elements of this state
     *
     * Called every frame after update() to draw:
     * - Background elements
     * - Game entities (walls, coins, characters)
     * - UI elements (score, lives, buttons)
     * - Overlays (pause screen, game over screen)
     *
     * States deeper in the stack may still be visible (e.g., LevelState
     * visible behind semi-transparent PausedState overlay)
     */
    virtual void render() = 0;

    /**
     * @brief Handle SFML input events
     * @param event SFML event to process (keyboard, mouse, window events)
     *
     * Processes discrete input events:
     * - Key presses (ESC for pause, ENTER for menu selection)
     * - Mouse clicks (clicking buttons)
     * - Window events (resize, close)
     *
     * Note: Continuous input (holding arrow keys) is often handled in update()
     * or handleInput() methods rather than discrete events
     */
    virtual void handleEvent(const sf::Event& event) = 0;

protected:
    /**
     * @brief Reference to the StateManager for triggering state transitions
     *
     * Protected access allows derived states to:
     * - Push new states: m_stateManager.pushState(...)
     * - Pop current state: m_stateManager.popState()
     * - Switch states: m_stateManager.switchToState(...)
     *
     * Example usage:
     * - MenuState: m_stateManager.pushState(std::make_unique<LevelState>(...))
     * - LevelState: m_stateManager.pushState(std::make_unique<PausedState>(...))
     * - PausedState: m_stateManager.popState() to resume game
     */
    StateManager& m_stateManager;
};
}
#endif