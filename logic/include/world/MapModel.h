#ifndef MAP_MODEL_H
#define MAP_MODEL_H

#include "../entities/CoinModel.h"


#include <vector>
#include <string>
#include <memory>

// Forward declarations
class WallModel;
class Entity;

class MapModel {
public:
    MapModel();
    ~MapModel();
    bool loadFromFile(const std::string& filename);

    [[nodiscard]] const std::vector<std::unique_ptr<WallModel>>& getWalls() const { return m_walls; }
    [[nodiscard]] const std::vector<std::unique_ptr<CoinModel>>& getCoins() const { return m_coins; }
    [[nodiscard]] const std::vector<std::string>& getGrid() const { return m_grid; }
    [[nodiscard]] pacman::logic::Vector2f getGridSize() const { return m_gridSize; }

private:
    std::vector<std::string> m_grid;
    std::vector<std::unique_ptr<WallModel>> m_walls;
    std::vector<std::unique_ptr<CoinModel>> m_coins;

    pacman::logic::Vector2f m_gridSize;

    void createWallsFromGrid();
};

#endif

