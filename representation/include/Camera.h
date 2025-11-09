#ifndef CAMERA_H
#define CAMERA_H
#include <SFML/System/Vector2.hpp>

class Camera {
public:
    Camera();

    // Convert normalized [-1,1] coordinates to pixel coordinates
    static sf::Vector2f worldToPixel(float worldX, float worldY,
                         unsigned int screenWidth,
                         unsigned int screenHeight) ;

    // Convert pixel coordinates to normalized world coordinates
    [[nodiscard]] sf::Vector2f pixelToWorld(int pixelX, int pixelY,
                         unsigned int screenWidth,
                         unsigned int screenHeight) const;

    // Get visible world bounds
    [[nodiscard]] float getLeft() const { return m_centerX - m_width/2; }
    [[nodiscard]] float getRight() const { return m_centerX + m_width/2; }
    [[nodiscard]] float getTop() const { return m_centerY - m_height/2; }
    [[nodiscard]] float getBottom() const { return m_centerY + m_height/2; }

private:
    float m_centerX, m_centerY;
    float m_width, m_height;  // In world units (normalized)
};

#endif //CAMERA_H
