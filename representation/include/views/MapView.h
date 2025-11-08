#ifndef MAP_VIEW_H
#define MAP_VIEW_H

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <vector>
#include "world/MapModel.h"

class MapView {
public:
    MapView();
    bool initialize(const MapModel& mapModel, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    std::vector<sf::RectangleShape> m_wallShapes;
    std::vector<sf::RectangleShape> m_coinShapes;

    std::unordered_map<std::string, sf::Texture> m_textures;

    void createWallShapes(const MapModel& mapModel, const sf::Vector2u& windowSize);
    void createCoinShapes(const MapModel& mapModel, const sf::Vector2u& windowSize);

    bool loadTextures();
};
#endif