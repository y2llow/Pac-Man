#pragma once

class Random {
public:
    // Delete copy constructor and assignment operator
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;
    
    // Static method to get the singleton instance
    static Random& getInstance();
    
    // Your existing Random methods...
    int getInt(int min, int max);
    float getFloat(float min, float max);
    
private:
    // Private constructor
    Random();
};