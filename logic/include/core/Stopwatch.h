#pragma once

#include <chrono>

class Stopwatch {
public:
    Stopwatch();
    
    // Starts or restarts the stopwatch
    void start();
    
    // Returns the time elapsed since start in seconds
    float getElapsedTime() const;
    
    // Returns the time since last tick and updates the internal timestamp
    float tick();
    
    // Gets the current time without updating the internal timestamp
    float peek() const;


private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    
    TimePoint m_startTime;
    TimePoint m_lastTickTime;
};