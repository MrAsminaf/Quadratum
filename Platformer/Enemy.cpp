#include "Enemy.h"

Enemy::Enemy(const sf::Vector2i & spawn_position)
{
	m_mainObject.setPosition(sf::Vector2f(spawn_position.x*16, spawn_position.y*16));
	m_mainObject.setFillColor(sf::Color::Red);
	m_mainObject.setSize(sf::Vector2f(16, 16));
}

sf::RectangleShape & Enemy::GetObject()
{
	return m_mainObject;
}
