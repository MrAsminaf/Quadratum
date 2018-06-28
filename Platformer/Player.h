#pragma once

#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>

class Player : public sf::Drawable
{
public:
	Player();
	void Controls();
	void UpdateGravity();
	void Collision(const std::vector<std::string>& map);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::RectangleShape& GetPlayerObject();
private:
	sf::RectangleShape m_playerObject;
	bool m_isTouchingGround;
	bool m_isHittingLeftWall;
	bool m_isHittingRightWall;
	float m_verticalVelocity;
	const float m_horizontalVelocity;
	
	// FOR TEST //
	sf::RectangleShape left;
	sf::RectangleShape right;
	sf::RectangleShape top;
};