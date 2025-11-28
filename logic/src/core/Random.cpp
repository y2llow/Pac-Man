#include "core/Random.h"

#include <stdexcept>
#include <random>

Random& Random::getInstance() {
    static Random instance;
    return instance;
}

Random::Random() {
    // Seed with true random device if available
    std::random_device rd;
    m_generator.seed(rd());
}

int Random::getInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_generator);
}

float Random::getFloat(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_generator);
}

double Random::getDouble(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(m_generator);
}

bool Random::getBool(double probability) {
    std::bernoulli_distribution dist(probability);
    return dist(m_generator);
}

std::mt19937& Random::getGenerator() {
    return m_generator;
}