#include "Camera.h"

Camera::Camera(sf::RenderWindow& window)
    : m_window(window) {
    updateWindowSize();
}

sf::Vector2f Camera::worldToPixel(const sf::Vector2f& worldPos) const {
    // Convert from normalized [-1, 1] to pixel coordinates [0, windowSize]
    float pixelX = (worldPos.x + 1.0f) * (m_windowSize.x / 2.0f);
    float pixelY = (worldPos.y + 1.0f) * (m_windowSize.y / 2.0f);

    return sf::Vector2f(pixelX, pixelY);
}

sf::Vector2f Camera::worldToPixelSize(const sf::Vector2f& worldSize) const {
    // Convert normalized size to pixel size
    float pixelWidth = worldSize.x * (m_windowSize.x / 2.0f);
    float pixelHeight = worldSize.y * (m_windowSize.y / 2.0f);

    return sf::Vector2f(pixelWidth, pixelHeight);
}

sf::Vector2f Camera::getWindowSize() const {
    return m_windowSize;
}

void Camera::updateWindowSize() {
    sf::Vector2u windowSize = m_window.getSize();
    m_windowSize = sf::Vector2f(static_cast<float>(windowSize.x),
                               static_cast<float>(windowSize.y));
}