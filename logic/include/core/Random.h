#ifndef RANDOM_H
#define RANDOM_H

#include <algorithm>
#include <random>
#include <vector>
#include <memory>
#include <stdexcept>

class Random {
public:
    // Singleton pattern to ensure same generator is used throughout the game
    static Random& getInstance();

    // Delete copy constructor and assignment operator
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    // Generate random integer in range [min, max]
    int getInt(int min, int max);

    // Generate random float in range [min, max]
    float getFloat(float min, float max);

    // Generate random double in range [min, max]
    double getDouble(double min, double max);

    // Generate random boolean with given probability (default 0.5)
    bool getBool(double probability = 0.5);

    // Randomly select an element from a vector
    template<typename T>
    T getRandomElement(const std::vector<T>& elements);

    // Randomly select an index from a vector
    template<typename T>
    size_t getRandomIndex(const std::vector<T>& elements);

    // Shuffle a vector randomly
    template<typename T>
    void shuffle(std::vector<T>& elements);

    // Get the underlying generator for advanced use
    std::mt19937& getGenerator();

private:
    Random(); // Private constructor for singleton

    std::mt19937 m_generator; // Mersenne Twister generator
};

// Template implementations must be in header file
template<typename T>
T Random::getRandomElement(const std::vector<T>& elements) {
    if (elements.empty()) {
        throw std::invalid_argument("Cannot select from empty vector");
    }
    std::uniform_int_distribution<size_t> dist(0, elements.size() - 1);
    return elements[dist(m_generator)];
}

template<typename T>
size_t Random::getRandomIndex(const std::vector<T>& elements) {
    if (elements.empty()) {
        throw std::invalid_argument("Cannot select from empty vector");
    }
    std::uniform_int_distribution<size_t> dist(0, elements.size() - 1);
    return dist(m_generator);
}

template<typename T>
void Random::shuffle(std::vector<T>& elements) {
    std::shuffle(elements.begin(), elements.end(), m_generator);
}

#endif // RANDOM_H