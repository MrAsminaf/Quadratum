#pragma once

#include<SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy(const sf::Vector2i& spawn_position);
	sf::RectangleShape& GetObject();
private:
	sf::RectangleShape m_mainObject;
};