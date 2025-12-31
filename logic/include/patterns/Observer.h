#ifndef OBSERVER_H
#define OBSERVER_H

/**
 * @class Observer
 * @brief Traditional Observer pattern interface (not used in current implementation)
 *
 * DESIGN PATTERN: Observer Pattern (Classic/Traditional)
 * Purpose: Define a one-to-many dependency so when one object changes state,
 * all its dependents are notified automatically.
 */
class Observer {
public:
    /**
     * @brief Virtual destructor for polymorphic deletion
     */
    virtual ~Observer() = default;

    /**
     * @brief Notification callback when subject changes
     *
     * Called by Subject when its state changes.
     * Observer should pull new state from subject or use pushed data.
     */
    virtual void update() = 0;
};

#endif