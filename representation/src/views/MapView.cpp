#include "views/MapView.h"
#include "world/MapModel.h"

MapView::MapView() {
}

bool MapView::initialize(const MapModel& mapModel, sf::RenderWindow& window) {
    createWallShapes(mapModel, window.getSize());
    return true;
}

void MapView::createWallShapes(const MapModel& mapModel, const sf::Vector2u& windowSize) {
    m_wallShapes.clear();
    
    const auto& grid = mapModel.getGrid();
    sf::Vector2u mapSize = mapModel.getSize();
    sf::Color wallColor(0, 40, 225);
    
    if (mapSize.x == 0 || mapSize.y == 0) return;
    
    // Calculate tile size in pixels based on window size
    float tileWidth = static_cast<float>(windowSize.x) / mapSize.x;
    float tileHeight = static_cast<float>(windowSize.y) / mapSize.y;
    
    // Create wall shapes for each '#' in the grid
    for (unsigned int y = 0; y < mapSize.y; ++y) {
        for (unsigned int x = 0; x < mapSize.x; ++x) {
            if (grid[y][x] == 'x') {
                sf::RectangleShape wall(sf::Vector2f(tileWidth - 5, tileHeight - 5)); // Slightly smaller for gaps
                wall.setPosition(x * tileWidth + 1, y * tileHeight + 1); // Center in tile
                wall.setFillColor(wallColor);
                m_wallShapes.push_back(wall);
            }
        }
    }
}

void MapView::draw(sf::RenderWindow& window) {
    for (const auto& wall : m_wallShapes) {
        window.draw(wall);
    }
}