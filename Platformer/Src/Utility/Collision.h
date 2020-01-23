#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

class Collision
{
public:
	Collision();
	Collision(sf::Sprite* sprite);
	void AssignSprite(sf::Sprite* sprite);
private:
	bool IsTouchingGround();
private:
	sf::Sprite* m_sprite;
	std::unordered_map<sf::Vector2i, sf::FloatRect>* m_mapPtr;
	bool m_previousIsTouchingGround;
	bool m_isTouchingGround;
	bool m_isHittingLeftWall;
	bool m_isHittingRightWall;
};