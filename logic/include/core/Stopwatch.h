#pragma once
#include <chrono>

namespace pacman::logic::core {

class Stopwatch {
public:
    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    static Stopwatch& getInstance();
    void start();
    float getElapsedTime() const;
    float tick();
    float peek() const;

private:
    Stopwatch();
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    TimePoint m_startTime;
    TimePoint m_lastTickTime;
};

} // namespace pacman::logic::core


