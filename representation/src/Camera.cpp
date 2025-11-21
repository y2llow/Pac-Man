#include "Camera.h"

Camera::Camera(sf::RenderWindow& window)
    : m_window(window) {
    updateWindowSize();
}

void Camera::updateWindowSize() {
    sf::Vector2u windowSize = m_window.getSize();
    m_windowSize = sf::Vector2f(static_cast<float>(windowSize.x),
                               static_cast<float>(windowSize.y));
}

void Camera::updateWindowSize(const Vector2f& newSize) {
    m_windowSize.x = newSize.x;
    m_windowSize.y = newSize.y;
}

Vector2f Camera::worldToPixel(const Vector2f& worldPos) const {
    // Convert from normalized [-1, 1] to pixel coordinates [0, windowSize]
    float pixelX = (worldPos.x + 1.0f) * (m_windowSize.x / 2.0f);
    float pixelY = (worldPos.y + 1.0f) * (m_windowSize.y / 2.0f);
    return {pixelX, pixelY};
}

Vector2f Camera::worldToPixelSize(const Vector2f& worldSize) const {
    // Convert normalized size to pixel size
    float pixelWidth = worldSize.x * (m_windowSize.x / 2.0f);
    float pixelHeight = worldSize.y * (m_windowSize.y / 2.0f);
    return {pixelWidth, pixelHeight};
}

sf::Vector2f Camera::getWindowSize() const {
    return m_windowSize;
}