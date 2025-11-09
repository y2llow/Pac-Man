#include "patterns/Subject.h"
#include "patterns/Observer.h"  // Include in .cpp to avoid circular dependency
#include <algorithm>

void Subject::attachObserver(std::unique_ptr<Observer> observer) {
    if (observer) {
        m_observers.push_back(std::move(observer));
    }
}

void Subject::detachObserver(Observer* observer) {
    m_observers.erase(
        std::remove_if(m_observers.begin(), m_observers.end(),
            [observer](const std::unique_ptr<Observer>& ptr) {
                return ptr.get() == observer;
            }),
        m_observers.end()
    );
}

void Subject::notifyObservers() {
    for (const auto& observer : m_observers) {
        if (observer) {
            observer->update();
        }
    }
}