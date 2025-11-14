#include "entities/PacmanModel.h"

#include <SFML/Window/Keyboard.hpp>

PacmanModel::PacmanModel(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& textureId )
    : m_position(position), m_textureId(textureId) { m_size = size; }


void PacmanModel::update(float deltaTime)  {

	// std::array<bool, 4> walls{};
	// walls[0] = map_collision(0, 0, PACMAN_SPEED + position.x, position.y, i_map);
	// walls[1] = map_collision(0, 0, position.x, position.y - PACMAN_SPEED, i_map);
	// walls[2] = map_collision(0, 0, position.x - PACMAN_SPEED, position.y, i_map);
	// walls[3] = map_collision(0, 0, position.x, PACMAN_SPEED + position.y, i_map);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	    m_position.x =  m_position.x - 10;
	}	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	    m_position.x =  m_position.x + 10;
	}	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
	    m_position.y =  m_position.y + 10;
	}	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
	    m_position.y =  m_position.y - 10;
	}
	// 	if (0 == walls[0]) //You can't turn in this direction if there's a wall there.
	// 	{
	// 		direction = 0;
	// 	}
	// }
	//
	// if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	// {
	// 	if (0 == walls[1])
	// 	{
	// 		direction = 1;
	// 	}
	// }
	//
	// if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	// {
	// 	if (0 == walls[2])
	// 	{
	// 		direction = 2;
	// 	}
	// }
	//
	// if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	// {
	// 	if (0 == walls[3])
	// 	{
	// 		direction = 3;
	// 	}
	// }

	// if (0 == walls[direction])
	// {
	// 	switch (direction)
	// 	{
	// 		case 0:
	// 		{
	// 			position.x += PACMAN_SPEED;
	//
	// 			break;
	// 		}
	// 		case 1:
	// 		{
	// 			position.y -= PACMAN_SPEED;
	//
	// 			break;
	// 		}
	// 		case 2:
	// 		{
	// 			position.x -= PACMAN_SPEED;
	//
	// 			break;
	// 		}
	// 		case 3:
	// 		{
	// 			position.y += PACMAN_SPEED;
	// 		}
	// 	}
	// }
	//
	// if (-CELL_SIZE >= position.x)
	// {
	// 	position.x = CELL_SIZE * MAP_WIDTH - PACMAN_SPEED;
	// }
	// else if (CELL_SIZE * MAP_WIDTH <= position.x)
	// {
	// 	position.x = PACMAN_SPEED - CELL_SIZE;
	// }

}


void PacmanModel::setPosition(const sf::Vector2f& position)  {
    m_position = position;
    notifyObservers();

}

