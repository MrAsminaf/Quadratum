#pragma once

#include<SFML/Graphics.hpp>
#include<vector>

class Enemy
{
public:
	Enemy(const sf::Vector2i& spawn_position);
	void Update(const std::vector<std::string>& map);
	sf::RectangleShape& GetObject();
	sf::Vector2f GetPosition() const;
private:
	sf::RectangleShape m_mainObject;
	const float m_defaultHorizontalSpeed;
	bool m_isGoingLeft;
};