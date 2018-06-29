#include "Enemy.h"

Enemy::Enemy(const sf::Vector2i & spawn_position)
	:
	m_defaultHorizontalSpeed(0.1f),
	m_isGoingLeft(true)
{
	m_mainObject.setPosition(sf::Vector2f(spawn_position.x*16, spawn_position.y*16));
	m_mainObject.setFillColor(sf::Color::Red);
	m_mainObject.setSize(sf::Vector2f(16, 16));
}

void Enemy::Update(const std::vector<std::string>& map)
{
	if (m_isGoingLeft)
		m_mainObject.move(sf::Vector2f(-m_defaultHorizontalSpeed, 0));
	else
		m_mainObject.move(sf::Vector2f(m_defaultHorizontalSpeed, 0));

	int x = m_mainObject.getPosition().x / 16;
	int y = m_mainObject.getPosition().y / 16;

	if (m_isGoingLeft)
	{
		if (map.at(y + 1).at(x) == ' ')
			m_isGoingLeft = false;
	}
	else
	{
		if (map.at(y + 1).at(x + 1) == ' ')
			m_isGoingLeft = true;
	}
}

sf::RectangleShape & Enemy::GetObject()
{
	return m_mainObject;
}
