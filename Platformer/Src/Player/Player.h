#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>

class Player : public sf::Drawable
{
public:
	Player();
	float Controls(const sf::Time& delta_time);
	void Update(const std::vector<std::string>& map, const sf::Time& delta_time);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite& GetPlayerObject();
private:
	void LoadTextures();
	void IdleAnimation(const sf::Time& delta_time);
	void RunAnimation();
	void JumpAnimation();
	void UpdateGravity(const sf::Time& delta_time);
	void Collision(const std::vector<std::string>& map);
private:
	sf::Sprite m_playerObject;
	std::vector<sf::Texture>m_idleTextures;
	std::vector<sf::Texture>m_runTextures;
	std::vector<sf::Texture>m_jumpTextures;

	bool m_previousIsTouchingGround;
	bool m_isTouchingGround;

	bool m_isHittingLeftWall;
	bool m_isHittingRightWall;
	bool m_isIdle;
	float m_verticalVelocity;
	const float m_horizontalVelocity;
	sf::Clock m_clock;

	const float m_idleAnimationTimeInterval;
	const float m_runAnimationTimeInterval;
	const float m_jumpAnimationTimeInterval;
	const sf::Vector2f m_playerScale;
};