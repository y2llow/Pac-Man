#ifndef RANDOM_H
#define RANDOM_H

#include <algorithm>
#include <random>
#include <vector>
#include <stdexcept>



namespace pacman::logic::core {

class Random {
public:
    static Random& getInstance();

    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    int getInt(int min, int max);
    float getFloat(float min, float max);
    double getDouble(double min, double max);
    bool getBool(double probability = 0.5);

    template<typename T>
    T getRandomElement(const std::vector<T>& elements);

    template<typename T>
    size_t getRandomIndex(const std::vector<T>& elements);

    template<typename T>
    void shuffle(std::vector<T>& elements);

    std::mt19937& getGenerator();

private:
    Random();
    std::mt19937 m_generator;
};

// Template implementations
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

} // namespace pacman::logic::core



#endif