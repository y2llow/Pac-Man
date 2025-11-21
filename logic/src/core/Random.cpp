#include "core/Random.h"

Random& Random::getInstance() {
    static Random instance;
    return instance;
}

Random::Random() {
    // Initialize random seed
}

// ... rest of Random implementation