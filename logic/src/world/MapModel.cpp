#include "world/MapModel.h"
#include <fstream>
#include <iostream>

MapModel::MapModel() : m_tileSize(0.05f) { // Small size for normalized coords
}

bool MapModel::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to load map file: " << filename << std::endl;
        return false;
    }

    m_grid.clear();
    std::string line;

    while (std::getline(file, line)) {
        m_grid.push_back(line);
    }

    if (m_grid.empty()) {
        std::cerr << "Map file is empty: " << filename << std::endl;
        return false;
    }

    // Set map size based on loaded grid
    m_size.y = m_grid.size();
    m_size.x = m_grid[0].size(); // Assume all rows have same length

    return true;
}

bool MapModel::isWall(const sf::Vector2f& position) const {
    // Convert normalized coordinates to grid coordinates
    int gridX = static_cast<int>((position.x + 1.0f) / (2.0f / m_size.x));
    int gridY = static_cast<int>((position.y + 1.0f) / (2.0f / m_size.y));

    // Check bounds and if it's a wall
    if (gridX < 0 || gridX >= static_cast<int>(m_size.x) ||
        gridY < 0 || gridY >= static_cast<int>(m_size.y)) {
        return true; // Treat out-of-bounds as walls
        }

    return m_grid[gridY][gridX] == '#';
}

sf::Vector2u MapModel::getSize() const {
    return m_size;
}

float MapModel::getTileSize() const {
    return m_tileSize;
}