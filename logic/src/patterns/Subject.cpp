#include "patterns/Subject.h"
#include <algorithm>

void Subject::attachObserver(Callback callback) {
    if (callback) {
        m_observers.push_back(std::move(callback));
    }
}

void Subject::detachAllObservers() {
    m_observers.clear();
}

void Subject::notifyObservers() {
    for (const auto& observer : m_observers) {
        if (observer) {
            observer();
        }
    }
}