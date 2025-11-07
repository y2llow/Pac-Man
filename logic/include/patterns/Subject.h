#ifndef SUBJECT_H
#define SUBJECT_H

#include <memory>
#include <vector>

class Observer;

class Subject {
public:
    virtual ~Subject() = default;
    void attachObserver(std::unique_ptr<Observer> observer);
    void notifyObservers();

private:
    std::vector<std::unique_ptr<Observer>> m_observers;
};

#endif
