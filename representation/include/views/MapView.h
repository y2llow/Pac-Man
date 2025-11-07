#ifndef MAP_VIEW_H
#define MAP_VIEW_H

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
    void createWallShapes(const MapModel& mapModel, const sf::Vector2u& windowSize);
};

#endif