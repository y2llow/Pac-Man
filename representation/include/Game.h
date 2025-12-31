#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "StateManger.h"
#include "states/MenuState.h"

/**
 * @namespace pacman::representation
 * @brief Contains all representation layer classes for the Pac-Man game
 *
 * This namespace separates the representation (view) layer from the logic layer,
 * following clean architecture principles. The representation layer is responsible
 * for SFML-dependent code, rendering, and user interface.
 */
namespace pacman::representation {

/**
 * @class Game
 * @brief Main game controller class - entry point for the entire application
 *
 * ARCHITECTURE OVERVIEW:
 * The Game class serves as the central hub of the application, coordinating:
 * - The game window (SFML RenderWindow)
 * - The camera system (coordinate transformations)
 * - The state machine (StateManager)
 * - The main game loop (run method)
 *
 * DESIGN PATTERNS USED:
 * 1. Facade Pattern: Provides a simplified interface to the complex subsystems
 * 2. State Pattern: Delegates game behavior to StateManager
 * 3. Game Loop Pattern: Classic game loop with fixed timestep
 *
 * RESPONSIBILITIES:
 * - Initialize the game window and core systems
 * - Run the main game loop (process events → update → render)
 * - Maintain the camera for coordinate transformations
 * - Bootstrap the initial state (MenuState)
 *
 * CLEAN ARCHITECTURE:
 * This class belongs to the representation layer and is SFML-dependent.
 * It coordinates high-level flow but delegates actual game logic to the
 * logic layer through the World and entity models.
 */
class Game {
public:
    /**
     * @brief Constructor - Initializes the game window, camera, and state manager
     *
     * Initialization sequence:
     * 1. Creates SFML window with predefined dimensions
     * 2. Sets frame rate limit for consistent timing
     * 3. Loads the sprite sheet (required for all game entities)
     * 4. Initializes camera with window reference
     * 5. Creates StateManager with window reference
     */
    Game();

    /**
     * @brief Default destructor
     *
     * Using default because:
     * - unique_ptr members handle their own cleanup
     * - SFML window closes automatically
     * - No manual resource management needed
     */
    ~Game() = default;

    /**
     * @brief Main game loop - runs until window is closed
     *
     * GAME LOOP STRUCTURE (Classic Game Loop Pattern):
     *
     * 1. Initialize stopwatch for delta time tracking
     * 2. Push initial state (MenuState) onto state stack
     * 3. Loop while window is open:
     *    a. Calculate deltaTime (time since last frame)
     *    b. Process input events
     *    c. Update game logic
     *    d. Render frame
     *
     * WHY THIS ORDER?
     * - Events first: Respond to user input immediately
     * - Update second: Apply physics, AI, and game logic
     * - Render last: Display the updated game state
     *
     * DELTA TIME:
     * Using delta time ensures frame-rate independent movement.
     * If the game runs at 30 FPS or 60 FPS, entities move at the same speed.
     * Formula: newPosition = oldPosition + (velocity * deltaTime)
     */
    void run();

    // ========================================================================
    // CONFIGURATION CONSTANTS
    // ========================================================================

    /**
     * @brief Window width in pixels
     *
     * 800px chosen because:
     * - Standard aspect ratio when paired with 880px height
     * - Comfortable size for desktop monitors
     * - Matches classic Pac-Man proportions (slightly taller than wide)
     */
    static constexpr unsigned int WINDOW_WIDTH = 800;

    /**
     * @brief Window height in pixels
     *
     * 880px (taller than width) provides space for:
     * - Main game area (square-ish maze)
     * - Score/lives display at top
     * - Maintains classic Pac-Man arcade cabinet proportions
     */
    static constexpr unsigned int WINDOW_HEIGHT = 880;

    /**
     * @brief Frame rate limit (frames per second)
     *
     * 60 FPS chosen because:
     * - Standard refresh rate for most monitors
     * - Smooth animation without excessive CPU usage
     * - Consistent with game industry standards
     * - Provides good balance between smoothness and performance
     *
     * Note: Delta time calculation still ensures frame-rate independence,
     * so the game logic works correctly even if FPS drops below 60
     */
    static constexpr unsigned int FPS_LIMIT = 60;

private:
    // ========================================================================
    // PRIVATE HELPER METHODS - Game Loop Components
    // ========================================================================

    /**
     * @brief Process all pending SFML events
     *
     * Handles:
     * - Window close events (clicking X button)
     * - Forwards all other events to the active state
     */
    void processEvents();

    /**
     * @brief Update game logic for the current frame
     * @param deltaTime Time elapsed since last frame in seconds
     *
     * Simply delegates to StateManager, which forwards to the active state.
     * The active state (Menu, Level, Paused, GameOver) handles its own update logic.
     */
    void update(float deltaTime);

    /**
     * @brief Render the current frame
     *
     * Rendering pipeline:
     * 1. Clear window (black background)
     * 2. StateManager renders active state
     * 3. Display rendered frame to screen
     *
     * This is double buffering - prevents screen tearing and flickering
     */
    void render();

    // ========================================================================
    // MEMBER VARIABLES - Core Game Systems
    // ========================================================================

    /**
     * @brief The SFML window where everything is rendered
     *
     * This is the primary interface to the OS windowing system
     */
    std::unique_ptr<sf::RenderWindow> m_window;

    /**
     * @brief Camera system for coordinate transformations
     *
     * CAMERA RESPONSIBILITIES:
     * - Convert normalized world coordinates [-1, 1] to pixel coordinates
     * - Handle window resizing (recalculate projection)
     * - Provide consistent coordinate system to logic layer
     *
     * COORDINATE SYSTEMS:
     * - Logic layer uses normalized coordinates: x ∈ [-1, 1], y ∈ [-1, 1]
     * - Representation layer uses pixel coordinates: x ∈ [0, 800], y ∈ [0, 880]
     * - Camera bridges these two systems
     */
    Camera m_camera;

    /**
     * @brief State manager controlling game states
     *
     * STATE STACK CONCEPT:
     * StateManager maintains a stack of states:
     * - Bottom: MenuState (game starts here)
     * - Middle: LevelState (active gameplay)
     * - Top: PausedState (temporarily paused)
     *
     * Only the top state is updated and rendered.
     * When you pop a state, the previous state becomes active.
     *
     * Example flow:
     * 1. Game starts: [MenuState]
     * 2. Click Play: [MenuState, LevelState] → LevelState active
     * 3. Press ESC: [MenuState, LevelState, PausedState] → PausedState active
     * 4. Unpause: [MenuState, LevelState] → LevelState active again
     * 5. Game Over: [MenuState, GameOverState] → switched states
     */
    StateManager m_stateManager;
};

} // namespace pacman::representation