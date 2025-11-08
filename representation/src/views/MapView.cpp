#include "views/MapView.h"
#include "rendering/SpriteManager.h"
#include <iostream>
#include "entities/StaticEntity_collectibles/WallModel.h"
#include "world/MapModel.h"



MapView::MapView() {
}

bool MapView::initialize(const MapModel& mapModel, sf::RenderWindow& window) {
    // Load textures first
    if (!loadTextures()) {
        std::cerr << "Failed to load textures!" << std::endl;
        return false;
    }

    createWallShapes(mapModel, window.getSize());
    return true;
}

bool MapView::loadTextures() {
    auto& textureManager = TextureManager::getInstance();

    // Load your wall textures - adjust paths as needed
    if (!textureManager.loadTexture("wall_basic", "assets/textures/wall.png")) {
        // Fallback: create a colored rectangle instead
        std::cout << "Using fallback colored walls" << std::endl;
    }

    if (!textureManager.loadTexture("wall_border", "assets/textures/wall_border.png")) {
        // Fallback will use the basic texture
    }

    return true;
}

void MapView::createWallShapes(const MapModel& mapModel, const sf::Vector2u& windowSize) {
    m_wallShapes.clear();

    sf::Vector2u mapSize = mapModel.getGridSize();
    const auto& walls = mapModel.getWalls(); // Get the actual wall entities

    if (mapSize.x == 0 || mapSize.y == 0) return;

    float tileWidth = static_cast<float>(windowSize.x) / mapSize.x;
    float tileHeight = static_cast<float>(windowSize.y) / mapSize.y;

    auto& textureManager = TextureManager::getInstance();

    // Create wall shapes based on the actual wall entities
    for (const auto& wall : walls) {
        sf::RectangleShape wallShape(sf::Vector2f(tileWidth - 2, tileHeight - 2));

        // Convert normalized coordinates to pixel coordinates
        sf::Vector2f logicPos = wall->getPosition();
        float pixelX = (logicPos.x + 1.0f) * (windowSize.x / 2.0f);
        float pixelY = (logicPos.y + 1.0f) * (windowSize.y / 2.0f);

        wallShape.setPosition(pixelX - (tileWidth / 2.0f), pixelY - (tileHeight / 2.0f));

        // Apply texture based on texture ID from WallModel
        const std::string& textureId = wall->getTextureId();
        const sf::Texture* texture = textureManager.getTexture(textureId);

        if (texture) {
            wallShape.setTexture(texture);
            // If texture not found, you could try fallback texture
            // texture = textureManager.getTexture("wall_basic");
        } else {
            // Fallback: use color if texture not available
            if (textureId == "wall_border") {
                wallShape.setFillColor(sf::Color(100, 100, 200)); // Dark blue for borders
            } else {
                wallShape.setFillColor(sf::Color(70, 70, 200)); // Blue for basic walls
            }
        }

        m_wallShapes.push_back(wallShape);
    }

    std::cout << "MapView: Created " << m_wallShapes.size() << " textured wall shapes" << std::endl;
}

void MapView::draw(sf::RenderWindow& window) {
    for (const auto& wall : m_wallShapes) {
        window.draw(wall);
    }
}