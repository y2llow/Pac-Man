#ifndef MAP_MODEL_H
#define MAP_MODEL_H

#include <vector>
#include <string>
#include <SFML/System/Vector2.hpp>

class MapModel {
public:
    MapModel();
    bool loadFromFile(const std::string& filename);
    
    // Pure logic methods - no graphics!
    bool isWall(const sf::Vector2f& position) const;
    sf::Vector2u getSize() const;
    float getTileSize() const;
    
    // For the World to access map data
    const std::vector<std::string>& getGrid() const { return m_grid; }

private:
    std::vector<std::string> m_grid; // Stores the map data (e.g., '#' for walls)
    sf::Vector2u m_size; // Dimensions in tiles
    float m_tileSize; // Size of each tile in normalized coordinates
};

#endif