#include "world/World.h"

World::World(sf::Vector2u l_windSize){
    m_blockSize = 16;
    m_windowSize = l_windSize;
    // RespawnApple();
    m_appleShape.setFillColor(sf::Color::Red);
    m_appleShape.setRadius(m_blockSize / 2);
    for(int i = 0; i < 4; ++i){
        m_bounds[i].setFillColor(sf::Color(150,0,0));
        if(!((i + 1) % 2)){
            m_bounds[i].setSize(sf::Vector2f(m_windowSize.x,
            m_blockSize));
        } else {
            m_bounds[i].setSize(sf::Vector2f(m_blockSize,
            m_windowSize.y));
        }
         if(i < 2){
             m_bounds[i].setPosition(0,0);
         } else {
             m_bounds[i].setOrigin(m_bounds[i].getSize());
             m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
         }
    }
}

World::~World(){}

void World::Render(sf::RenderWindow& l_window){
    for(const auto & m_bound : m_bounds){
        l_window.draw(m_bound);
    }
    l_window.draw(m_appleShape);
}

int World::GetBlockSize() const { return m_blockSize; }
