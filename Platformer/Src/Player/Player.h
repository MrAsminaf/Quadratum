#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "Animations/Animation.h"
#include "Enemies/Enemy.h"

// temporary
#include <iostream>

class Player : public sf::Drawable
{
public:
	Player();
	float Controls(const sf::Time& delta_time);
	void Update(const std::vector<std::string>& map, const sf::Time& delta_time, std::vector<Enemy>& enemyContainer);
	void GotHit();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite& GetPlayerObject();
private:
	void LoadTextures();
	void UpdateGravity(const sf::Time& delta_time);
	void Collision(const std::vector<std::string>& map);
	bool IsHitByEnemy(std::vector<Enemy>& enemyContainer);
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
	sf::Clock m_healthCooldownClock;
	const sf::Vector2f m_playerScale;

	Animation m_runningAmination;
	Animation m_idleAnimation;
	Animation m_jumpUpAnimation;
	Animation m_jumpDownAnimation;
};