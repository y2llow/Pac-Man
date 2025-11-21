#pragma once

#include <chrono>

class Stopwatch {
public:
    // Delete copy constructor and assignment operator
    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    // Static method to get the singleton instance
    static Stopwatch& getInstance();

    // Starts or restarts the stopwatch
    void start();

    // Returns the time elapsed since start in seconds
    float getElapsedTime() const;

    // Returns the time since last tick and updates the internal timestamp
    float tick();

    // Gets the current time without updating the internal timestamp
    float peek() const;

private:
    // Private constructor for singleton
    Stopwatch();

    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    
    TimePoint m_startTime;
    TimePoint m_lastTickTime;
};