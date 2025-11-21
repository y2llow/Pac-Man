#ifndef SUBJECT_H
#define SUBJECT_H

#include <functional>
#include <memory>
#include <vector>

class Subject {
public:
    using Callback = std::function<void()>;

    virtual ~Subject() = default;

    // Observer management
    void attachObserver(Callback callback);
    void detachAllObservers();
    void notifyObservers();

protected:
    std::vector<Callback> m_observers;
};

#endif