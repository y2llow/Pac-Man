#include "Camera.h"

sf::Vector2f Camera::worldToPixel(float worldX, float worldY,
unsigned int screenWidth,
unsigned int screenHeight) {
    // Convert from [-1,1] to [0, screenSize]
    float pixelX = (worldX + 1.0f) * 0.5f * screenWidth;
    float pixelY = (1.0f - worldY) * 0.5f * screenHeight; // Flip Y-axis

    return {pixelX, pixelY};
}

sf::Vector2f Camera::pixelToWorld(int pixelX, int pixelY,
                             unsigned int screenWidth,
                             unsigned int screenHeight) const {
    // Convert from [0, screenSize] to [-1,1]
    float worldX = (pixelX / static_cast<float>(screenWidth)) * 2.0f - 1.0f;
    float worldY = 1.0f - (pixelY / static_cast<float>(screenHeight)) * 2.0f;

    return {worldX, worldY};
}