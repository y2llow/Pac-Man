#include "world/MapModel.h"
#include "entities/StaticEntity_collectibles/WallModel.h" // Include the WallModel class
#include <fstream>
#include <iostream>
#include <algorithm>

MapModel::MapModel() {
}

MapModel::~MapModel() {
    // unique_ptrs will automatically clean up
}

bool MapModel::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to load map file: " << filename << std::endl;
        return false;
    }

    m_grid.clear();
    m_walls.clear();
    std::string line;

    while (std::getline(file, line)) {
        m_grid.push_back(line);
    }

    if (m_grid.empty()) {
        std::cerr << "Map file is empty: " << filename << std::endl;
        return false;
    }

    m_gridSize.y = m_grid.size();
    m_gridSize.x = m_grid[0].size();

    createWallsFromGrid();

    //TODO delete this
    std::cout << "Map loaded: " << m_gridSize.x << "x" << m_gridSize.y
              << " with " << m_walls.size() << " walls" << std::endl;
    return true;
}

void MapModel::createWallsFromGrid() {
    if (m_grid.empty()) return;

    float tileWidth = 2.0f / m_gridSize.x;
    float tileHeight = 2.0f / m_gridSize.y;

    for (unsigned int y = 0; y < m_gridSize.y; ++y) {
        for (unsigned int x = 0; x < m_gridSize.x; ++x) {
            if (m_grid[y][x] == 'x') {
                float posX = -1.0f + (x * tileWidth) + (tileWidth / 2.0f);
                float posY = -1.0f + (y * tileHeight) + (tileHeight / 2.0f);

                // Create wall with texture ID - you can customize this based on position or type
                std::string textureId = "wall_basic"; // Default texture


                auto wall = std::make_unique<WallModel>(
                    sf::Vector2f(posX, posY),
                    sf::Vector2f(tileWidth * 0.9f, tileHeight * 0.9f),
                    textureId
                );

                m_walls.push_back(std::move(wall));
            }

            if (m_grid[y][x] == '.') {
                float posX = -1.0f + (x * tileWidth) + (tileWidth / 2.0f);
                float posY = -1.0f + (y * tileHeight) + (tileHeight / 2.0f);

                // Create wall with texture ID - you can customize this based on position or type
                std::string textureId = "Coin"; // Default texture


                auto coin = std::make_unique<CoinModel>(
                    sf::Vector2f(posX, posY),
                    sf::Vector2f(tileWidth * 0.9f, tileHeight * 0.9f),
                    textureId
                );

                m_coins.push_back(std::move(coin));
            }
        }
    }
}