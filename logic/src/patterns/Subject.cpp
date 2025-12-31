#include "patterns/Subject.h"
#include <algorithm>

void pacman::logic::patterns::Subject::attachObserver(Callback callback) {
    if (callback) {
        m_observers.push_back(std::move(callback));
    }
}

void pacman::logic::patterns::Subject::detachAllObservers() {
    m_observers.clear();
}

void pacman::logic::patterns::Subject::notifyObservers() {
    for (const auto& observer : m_observers) {
        if (observer) {
            observer();
        }
    }
}