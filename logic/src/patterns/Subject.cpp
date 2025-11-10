#include "patterns/Subject.h"
#include "patterns/Observer.h"  // Include in .cpp to avoid circular dependency
#include <algorithm>

void Subject::attachObserver(Callback callback) {
    if (callback) {
        m_observers.push_back(std::move(callback));
    }
}

void Subject::notifyObservers() {
    for (const auto& observer : m_observers) {
        if (observer) {
            observer();
        }
    }
}