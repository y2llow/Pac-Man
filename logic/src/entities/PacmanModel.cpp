#include "entities/PacmanModel.h"

#include <SFML/Window/Keyboard.hpp>
#include <utility>

PacmanModel::PacmanModel(const sf::Vector2f& position, const sf::Vector2f& size, std::string  textureId )
    : m_position(position), m_textureId(std::move(textureId)), m_spawnpoint(position) { m_size = size; }

void PacmanModel::update(float deltaTime) {
    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        direction = 0;
    } if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        direction = 1;
    }if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        direction = 2;
    }if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        direction = 3;
    }

    m_lastMove = PACMAN_SPEED*deltaTime;

    switch (direction){
    case 0 :{
        m_position.x -= PACMAN_SPEED*deltaTime;
        break;
        }
    case 1:{
        m_position.y += PACMAN_SPEED*deltaTime;
        break;
    }
    case 2:{
        m_position.x += PACMAN_SPEED*deltaTime;
        break;
        }
    case 3:{
        m_position.y -= PACMAN_SPEED*deltaTime;
        }
    }


    //
    //     // Check if the new position collides with any walls
    //     sf::CircleShape tempPlayer = player;
    //     tempPlayer.move(movement);
    //
    //     if (!checkCollision(tempPlayer, walls)) {
    //         player.move(movement); // Apply movement if no collision
    //     }
    //
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

    // tunneling
    m_position = CheckTunneling(m_position);
    notifyObservers();
}

sf::Vector2f PacmanModel::CheckTunneling(sf::Vector2f position) {
    float edge = 1 + m_size.x / 2;
    if (-edge >= position.x){
        position.x = edge ;
        return position;
    }if (edge <= position.x){
        position.x = -edge;
        return position;
    }
    return position;
}



void PacmanModel::setPosition(const sf::Vector2f& position)  {
    m_position = position;
    notifyObservers();

}

void PacmanModel::undoLastMove() {

    switch (direction){
    case 0 :{
        m_position.x += m_lastMove;
        break;
    }
    case 1:{
        m_position.y -=m_lastMove;
        break;
    }
    case 2:{
        m_position.x -= m_lastMove;
        break;
    }
    case 3:{
        m_position.y += m_lastMove;
    }
    }

}

void PacmanModel::loseLife() {
    m_position = m_spawnpoint;
    m_lives -= 1;
}

