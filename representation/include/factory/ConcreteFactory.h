#ifndef CONCRETEFACTORY_H
#define CONCRETEFACTORY_H
#include "patterns/AbstractFactory.h"

class SFMLFactory : public LogicFactory {
public:
    std::unique_ptr<PacMan> createPacMan() override {
        // 1. Create the Model (logic part)
        auto pacManModel = std::make_unique<PacManModel>();
        // 2. Create the View (representation part)
        auto pacManView = std::make_unique<PacManView>(/* ... */);
        // 3. Link them: The View observes the Model
        pacManModel->attachObserver(std::move(pacManView));
        // 4. Return the Model to the World. The View is now "hidden" inside the observer list.
        return pacManModel;
    }
};
#endif //CONCRETEFACTORY_H
