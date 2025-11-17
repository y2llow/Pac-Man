#include "core/Stopwatch.h"

Stopwatch::Stopwatch() {
    start();
}

void Stopwatch::start() {
    m_startTime = Clock::now();
    m_lastTickTime = m_startTime;
}

float Stopwatch::getElapsedTime() const {
    auto currentTime = Clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        currentTime - m_startTime
    );
    return duration.count() / 1000000.0f; // Convert to seconds
}

float Stopwatch::tick() {
    auto currentTime = Clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        currentTime - m_lastTickTime
    );

    float deltaTime = duration.count() / 1000000.0f; // Convert to seconds
    m_lastTickTime = currentTime;

    return deltaTime;
}

float Stopwatch::peek() const {
    auto currentTime = Clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        currentTime - m_lastTickTime
    );
    return duration.count() / 1000000.0f; // Convert to seconds
}

