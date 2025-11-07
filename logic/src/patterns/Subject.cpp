//
// Created by s0243673@ad.ua.ac.be on 11/7/25.
//

#include "patterns/Subject.h"
#include <bits/stl_algo.h>
#include "patterns/Observer.h" // Include here in .cpp file only


Subject::~Subject() {
    // Observers will be cleaned up by their owners
}

void Subject::attachObserver(Observer* observer) {
    m_observers.push_back(observer);
}

void Subject::detachObserver(Observer* observer) {
    m_observers.erase(
        std::remove(m_observers.begin(), m_observers.end(), observer),
        m_observers.end()
    );
}

void Subject::notifyObservers() {
    for (auto observer : m_observers) {
        if (observer) {
            observer->update();
        }
    }
}