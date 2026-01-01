#ifndef CAMERA_H
#define CAMERA_H

#include "entities/EntityModel.h"
#include <SFML/Graphics.hpp>

namespace pacman::representation {

// Import Vector2f from logic layer
using logic::Vector2f;

class Camera {
public:
    explicit Camera(sf::RenderWindow& window);

    void updateWindowSize(const Vector2f& newSize);
    void updateWindowSize();

    // Convert normalized coordinates [-1, 1] to pixel coordinates
    [[nodiscard]] Vector2f worldToPixel(const Vector2f& worldPos) const;

    // Convert normalized size to pixel size
    [[nodiscard]] Vector2f worldToPixelSize(const Vector2f& worldSize) const;

    // Get current window dimensions
    [[nodiscard]] sf::Vector2f getWindowSize() const;

private:
    sf::RenderWindow& m_window;
    sf::Vector2f m_windowSize;
};

} // namespace pacman::representation

#endif // CAMERA_H