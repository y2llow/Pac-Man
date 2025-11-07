//
// Created by s0243673@ad.ua.ac.be on 11/6/25.
//

#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H
#include <memory>

class LogicFactory {
public:
    virtual ~LogicFactory() = default;
    virtual std::unique_ptr<PacMan> createPacMan() = 0;
    // virtual std::unique_ptr<Ghost> createGhost(GhostType type) = 0;
    // virtual std::unique_ptr<Coin> createCoin() = 0;
};

#endif //ABSTRACTFACTORY_H
