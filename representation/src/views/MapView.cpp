#include "views/MapView.h"
#include "rendering/SpriteManager.h"
#include <iostream>
#include "../../../logic/include/entities/WallModel.h"
#include "world/MapModel.h"



MapView::MapView() {
}

bool MapView::initialize(const MapModel& mapModel, sf::RenderWindow& window) {
    // Load textures first
    loadTextures();
    createWallShapes(mapModel, window.getSize());

    return true;
}

bool MapView::loadTextures() {
    auto& textureManager = TextureManager::getInstance();

    // Load your wall textures - adjust paths as needed
    textureManager.loadTexture("wall_basic", "assets/textures/wall.png");
    textureManager.loadTexture("Coin", "assets/textures/Coin.png");

    return true;
}

void MapView::createWallShapes(const MapModel& mapModel, const sf::Vector2u& windowSize) {
    m_wallShapes.clear();

    Vector2f mapSize = mapModel.getGridSize();
    const auto& walls = mapModel.getWalls(); // Get the actual wall entities

    if (mapSize.x == 0 || mapSize.y == 0) return;

    float tileWidth = static_cast<float>(windowSize.x) / mapSize.x;
    float tileHeight = static_cast<float>(windowSize.y) / mapSize.y;

    auto& textureManager = TextureManager::getInstance();

    // Create wall shapes based on the actual wall entities
    for (const auto& wall : walls) {
        sf::RectangleShape wallShape(sf::Vector2f(tileWidth - 2, tileHeight - 2));

        // Convert normalized coordinates to pixel coordinates
        Vector2f logicPos = wall->getPosition();
        float pixelX = (logicPos.x + 1.0f) * (windowSize.x / 2.0f);
        float pixelY = (logicPos.y + 1.0f) * (windowSize.y / 2.0f);

        wallShape.setPosition(pixelX - (tileWidth / 2.0f), pixelY - (tileHeight / 2.0f));

        // Apply texture based on texture ID from WallModel
        const std::string& textureId = wall->getTextureId();

        if (textureManager.hasTexture(textureId)) {
            const sf::Texture& texture = textureManager.getTexture(textureId);
            wallShape.setTexture(&texture); // SFML verwacht pointer, maar we geven address van reference
        } else {
            // Fallback: use color
            wallShape.setFillColor(sf::Color(70, 70, 200));
        }

        m_wallShapes.push_back(wallShape);
    }



    std::cout << "MapView: Created " << m_wallShapes.size() << " textured wall shapes" << std::endl;
}

void MapView::createCoinShapes(const MapModel& mapModel, const sf::Vector2u& windowSize) {
    m_coinShapes.clear();

    Vector2f mapSize = mapModel.getGridSize();
    const auto& coins = mapModel.getCoins(); // Get the actual wall entities

    if (mapSize.x == 0 || mapSize.y == 0) return;

    float tileWidth = static_cast<float>(windowSize.x) / mapSize.x;
    float tileHeight = static_cast<float>(windowSize.y) / mapSize.y;

    auto& textureManager = TextureManager::getInstance();

    // Create wall shapes based on the actual wall entities
    for (const auto& coin : coins) {
        sf::RectangleShape wallShape(sf::Vector2f(tileWidth - 35, tileHeight - 50));

        // Convert normalized coordinates to pixel coordinates
        Vector2f logicPos = coin->getPosition();
        float pixelX = (logicPos.x + 1.0f) * (windowSize.x / 2.0f);
        float pixelY = (logicPos.y + 1.0f) * (windowSize.y / 2.0f);

        wallShape.setPosition(pixelX - (tileWidth / 10.0f), pixelY - (tileHeight / 10.0f));

        // Apply texture based on texture ID from WallModel
        const std::string& textureId = coin->getTextureId();

        if (textureManager.hasTexture(textureId)) {
            const sf::Texture& texture = textureManager.getTexture(textureId);
            wallShape.setTexture(&texture); // SFML verwacht pointer, maar we geven address van reference
        } else {
            // Fallback: use color
            wallShape.setFillColor(sf::Color(70, 70, 200));
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