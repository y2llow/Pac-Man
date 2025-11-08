#ifndef MAP_MODEL_H
#define MAP_MODEL_H

#include <vector>
#include <string>
#include <memory>
#include <SFML/System/Vector2.hpp>

// Forward declarations
class WallModel;
class Entity;

class MapModel {
public:
    MapModel();
    ~MapModel();
    bool loadFromFile(const std::string& filename);

    [[nodiscard]] const std::vector<std::unique_ptr<WallModel>>& getWalls() const { return m_walls; }
    [[nodiscard]] const std::vector<std::string>& getGrid() const { return m_grid; }
    [[nodiscard]] sf::Vector2u getGridSize() const { return m_gridSize; }

private:
    std::vector<std::string> m_grid;
    std::vector<std::unique_ptr<WallModel>> m_walls;
    sf::Vector2u m_gridSize;

    void createWallsFromGrid();
};

#endif

