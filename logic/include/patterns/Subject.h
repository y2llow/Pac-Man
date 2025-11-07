#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

// Forward declaration
class Observer;

class Subject {
public:
    virtual ~Subject();
    void attachObserver(Observer* observer);
    void detachObserver(Observer* observer);
    void notifyObservers();

protected:
    std::vector<Observer*> m_observers;
};

#endif