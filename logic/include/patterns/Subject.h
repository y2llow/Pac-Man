#ifndef SUBJECT_H
#define SUBJECT_H

#include <functional>
#include <memory>
#include <vector>

/**
 * @class Subject
 * @brief Modern callback-based implementation of Observer pattern
 *
 * DESIGN PATTERN: Observer Pattern (Modern C++ Style)
 * Purpose: Allow models to notify views when state changes, without tight coupling.
 */


namespace pacman::logic::patterns {
class Subject {
public:
    /**
     * @brief Type alias for callback functions
     *
     * Using std::function allows:
     * - Lambda expressions: []() { ... }
     * - Function pointers: &myFunction
     * - Member functions: std::bind(&Class::method, this)
     * - Any callable with signature void()
     */
    using Callback = std::function<void()>;

    /**
     * @brief Virtual destructor for proper polymorphic deletion
     *
     * EntityModel inherits from Subject, so entities can be deleted
     * through Subject pointers safely.
     */
    virtual ~Subject() = default;

    // ========================================================================
    // OBSERVER MANAGEMENT
    // ========================================================================

    /**
     * @brief Attach a callback to be notified of state changes
     * @param callback Function to call when notifyObservers() is called
     *
     * Common usage patterns:
     *
     * 1. Lambda with capture:
     *    subject->attachObserver([this, weakRef]() {
     *        // Access 'this' and 'weakRef' safely
     *    });
     *
     * 2. View update:
     *    model->attachObserver([viewPtr]() {
     *        viewPtr->update();
     *    });
     *
     * 3. Score update:
     *    coin->attachObserver([score, coin]() {
     *        if (coin->isCollected()) score->onCoinCollected();
     *    });
     *
     * Note: Callbacks are stored by value (copied), so captured variables
     * must be carefully managed (use weak_ptr for shared ownership).
     */
    void attachObserver(Callback callback);

    /**
     * @brief Remove all attached observers
     *
     * Useful when:
     * - Destroying subject (cleanup)
     * - Resetting entity state
     * - Preventing stale callbacks from firing
     *
     * Note: Individual callback removal not supported (would need IDs or handles).
     * Current design assumes observers live as long as subject or are cleared all at once.
     */
    void detachAllObservers();

    /**
     * @brief Notify all attached observers of a state change
     *
     * Calls each attached callback in order of attachment.
     *
     * WHEN TO CALL:
     * - After changing any observable state (position, collected, scared, etc.)
     * - Not on every frame (only when something meaningful changes)
     * - Often at end of methods that modify state
     *
     * EXAMPLES:
     * - CoinModel::collect() → notifyObservers()
     * - PacmanModel::setPosition() → notifyObservers()
     * - GhostModel::setScared(true) → notifyObservers()
     *
     * PERFORMANCE:
     * - Cheap if no observers attached (empty vector iteration)
     * - O(n) where n = number of observers
     * - Not called every frame unless state actually changes
     */
    void notifyObservers();

protected:
    /**
     * @brief Storage for all attached callbacks
     *
     * Vector chosen because:
     * - Observers rarely added/removed during gameplay
     * - Fast iteration (cache-friendly)
     * - Order of notification might matter
     *
     * Protected so derived classes can see it but external code cannot.
     *
     * Memory: Each callback is ~32 bytes (std::function overhead)
     * Typical usage: 1-3 observers per entity (view, score, etc.)
     */
    std::vector<Callback> m_observers;
};
}


#endif