#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Camera {
public:
    explicit Camera(sf::RenderWindow& window);

    void updateWindowSize(const sf::Vector2f &newSize);
    void updateWindowSize();

    // Convert normalized coordinates [-1, 1] to pixel coordinates
    [[nodiscard]] sf::Vector2f worldToPixel(const sf::Vector2f& worldPos) const;

    // Convert normalized size to pixel size
    [[nodiscard]] sf::Vector2f worldToPixelSize(const sf::Vector2f& worldSize) const;

    // Get current window dimensions
    [[nodiscard]] sf::Vector2f getWindowSize() const;
private:
    sf::RenderWindow& m_window;
    sf::Vector2f m_windowSize;
};

#endif // CAMERA_H