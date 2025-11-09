#ifndef SUBJECT_H
#define SUBJECT_H

#include <memory>
#include <vector>

// Forward declaration - Observer is in representation layer
class Observer;

class Subject {
public:
    virtual ~Subject() = default;

    // Observer management
    void attachObserver(std::unique_ptr<Observer> observer);
    void detachObserver(Observer* observer);
    void notifyObservers();

    // Optional: different notification types for different events
    // enum class EventType { PositionChanged, StateChanged, Collected, etc. };
    // virtual void notifyObservers(EventType eventType);

protected:
    std::vector<std::unique_ptr<Observer>> m_observers;
};

#endif