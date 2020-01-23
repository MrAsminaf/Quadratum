#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>

template<typename T1, typename T2>
class Collision
{
public:
	Collision();
	Collision(sf::Sprite* sprite, std::unordered_map<sf::Vector2<T1>, sf::Rect<T2>>* map);
	void AssignSprite(sf::Sprite* sprite);
	void AssignMap(std::unordered_map<sf::Vector2<T1>, sf::Rect<T2>>* map);

	// Getter functions
	bool IsTouchingGround()const;
	bool IsHittingLeftWall()const;
	bool IsHittingRightWall()const;

	// Main Collision method
	void Check();
private:
	bool CheckForTouchingGround(int x, int y);
	bool CheckForLeftWallCollision(int x, int y);
	bool CheckForRightWallCollision(int x, int y);
private:
	sf::Sprite* m_spritePtr;
	std::unordered_map<sf::Vector2i, sf::FloatRect>* m_mapPtr;
	bool m_previousIsTouchingGround;
	bool m_isTouchingGround;
	bool m_isHittingLeftWall;
	bool m_isHittingRightWall;
};