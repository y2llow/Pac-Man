#include "core/Random.h"

#include <stdexcept>
#include <random>

pacman::logic::core::Random& pacman::logic::core::Random::getInstance() {
    static pacman::logic::core::Random instance;
    return instance;
}

pacman::logic::core::Random::Random() {
    // Seed with true random device if available
    std::random_device rd;
    m_generator.seed(rd());
}

int pacman::logic::core::Random::getInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_generator);
}

float pacman::logic::core::Random::getFloat(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_generator);
}

double pacman::logic::core::Random::getDouble(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(m_generator);
}

bool pacman::logic::core::Random::getBool(double probability) {
    std::bernoulli_distribution dist(probability);
    return dist(m_generator);
}

std::mt19937& pacman::logic::core::Random::getGenerator() {
    return m_generator;
}