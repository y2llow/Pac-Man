#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"


#include <functional>
#include <memory>
#include <vector>



class Subject {
public:
    using Callback = std::function<void()>;

    virtual ~Subject() = default;

    // Observer management
    void attachObserver(Callback callback);
    // detach observer
    void notifyObservers();

    // Optional: different notification types for different events
    // enum class EventType { PositionChanged, StateChanged, Collected, etc. };
    // virtual void notifyObservers(EventType eventType);

protected:
    std::vector<Callback> m_observers;
};

#endif

// pacman -> Observer1
// ghost -> Observer1
//
// pacman -> observer2
// coin -> observer2