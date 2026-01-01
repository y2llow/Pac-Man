#ifndef MAP_MODEL_H
#define MAP_MODEL_H

#include "entities/WallModel.h"
#include "entities/CoinModel.h"
#include <vector>
#include <string>
#include <memory>

namespace pacman::logic::world {

class MapModel {
public:
    MapModel();
    ~MapModel();

    bool loadFromFile(const std::string& filename);

    [[nodiscard]] const std::vector<std::unique_ptr<entities::WallModel>>& getWalls() const {
        return m_walls;
    }
    [[nodiscard]] const std::vector<std::unique_ptr<entities::CoinModel>>& getCoins() const {
        return m_coins;
    }
    [[nodiscard]] const std::vector<std::string>& getGrid() const {
        return m_grid;
    }
    [[nodiscard]] Vector2f getGridSize() const {
        return m_gridSize;
    }

private:
    std::vector<std::string> m_grid;
    std::vector<std::unique_ptr<entities::WallModel>> m_walls;
    std::vector<std::unique_ptr<entities::CoinModel>> m_coins;
    Vector2f m_gridSize;

    void createWallsFromGrid();
};

} // namespace pacman::logic::world

#endif