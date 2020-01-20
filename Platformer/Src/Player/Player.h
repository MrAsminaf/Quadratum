#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "../Animations/Animation.h"
#include "../Enemies/Enemy.h"
#include <unordered_map>
#include <cmath>

// temporary
#include <iostream>

class Player : public sf::Drawable
{
public:
	Player(sf::RenderWindow* window_ptr);
	float Controls(const sf::Time& delta_time);
	template<typename T1, typename T2>
	void Update(const std::vector<std::string>& map, const sf::Time& delta_time, std::vector<Enemy>& enemyContainer, 
		std::unordered_map<sf::Vector2<T1>, sf::Rect<T2>>& stdmap);
	void GotHit();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite& GetPlayerObject();
	float GetHorizontalVeloity();
private:
	void LoadTextures();
	void UpdateGravity(const sf::Time& delta_time);
	void Collision(const std::vector<std::string>& map);
	template<typename T1, typename T2>
	void CollisonV2(std::unordered_map<sf::Vector2<T1>, sf::Rect<T2>>& map);
	bool IsHitByEnemy(std::vector<Enemy>& enemyContainer);
private:
	sf::RenderWindow* m_mainWindowPtr;
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
	float m_horizontalVelocity;
	float m_slideVelocity;
	const float MAX_HORIZONTAL_VELOCITY;
	sf::Clock m_healthCooldownClock;
	const sf::Vector2f m_playerScale;

	Animation m_runningAmination;
	Animation m_idleAnimation;
	Animation m_jumpUpAnimation;
	Animation m_jumpDownAnimation;
};

template<typename T1, typename T2>
inline void Player::Update(const std::vector<std::string>& map, const sf::Time& delta_time, std::vector<Enemy>& enemyContainer, 
	std::unordered_map<sf::Vector2<T1>, sf::Rect<T2>>& stdmap)
{
	m_previousIsTouchingGround = m_isTouchingGround;
	UpdateGravity(delta_time);
	//Collision(map);
	CollisonV2(stdmap);

	if (m_isIdle)
		m_idleAnimation.Play(m_playerObject);
	else if (m_isTouchingGround)
		m_runningAmination.Play(m_playerObject);
	else if (!m_isTouchingGround)
	{
		if (m_verticalVelocity < 0)
			m_jumpUpAnimation.Play(m_playerObject);
		else
			m_jumpDownAnimation.Play(m_playerObject);
	}

	if (IsHitByEnemy(enemyContainer) && (m_healthCooldownClock.getElapsedTime().asSeconds() > 2 || m_healthCooldownClock.getElapsedTime().asSeconds() == 0))
		GotHit();

	if (m_healthCooldownClock.getElapsedTime().asSeconds() > 2)
	{
		m_playerObject.setColor(sf::Color::White);
	}
}

template<typename T1, typename T2>
inline void Player::CollisonV2(std::unordered_map<sf::Vector2<T1>, sf::Rect<T2>>& map)
{
	const auto pos = m_playerObject.getPosition();
	const int x = int(pos.x / 16);
	const int y = int(pos.y / 16);

	if (map.count(sf::Vector2i(x, y)))
	{
		if (map.at(sf::Vector2i(x, y)).intersects(m_playerObject.getGlobalBounds()))
		{
			std::cout << "(x, y)" << std::endl;
		}
	}
	if (map.count(sf::Vector2i(x, y + 1)))
	{
		if (map.at(sf::Vector2i(x, y + 1)).intersects(m_playerObject.getGlobalBounds()))
		{
			m_isTouchingGround = true;
		}
	}
	else if (map.count(sf::Vector2i(x + 1, y + 1)) && !map.count(sf::Vector2i(x, y + 1)) && m_isTouchingGround && abs(m_playerObject.getPosition().x - x * 16) > 10)
	{
		if (map.at(sf::Vector2i(x + 1, y + 1)).intersects(m_playerObject.getGlobalBounds()))
		{
			std::cout << "(x + 1, y + 1)" << std::endl;
			m_isTouchingGround = true;
		}
	}
	else if (map.count(sf::Vector2i(x - 1, y + 1)) && !map.count(sf::Vector2i(x, y + 1)) && m_isTouchingGround && abs((m_playerObject.getPosition().x + 10) - x * 16) < 16)
	{
		if (map.at(sf::Vector2i(x - 1, y + 1)).intersects(m_playerObject.getGlobalBounds()))
		{
			std::cout << "(x - 1, y + 1)" << std::endl;
			m_isTouchingGround = true;
		}
	}
	else if (map.count(sf::Vector2i(x + 1, y + 1)) && !map.count(sf::Vector2i(x, y + 1)) && !m_isTouchingGround && abs(m_playerObject.getPosition().x - x * 16) > 10)
	{
		if (map.at(sf::Vector2i(x + 1, y + 1)).intersects(m_playerObject.getGlobalBounds()))
		{
			std::cout << "(x + 1, y + 1)" << std::endl;
			m_isTouchingGround = true;
		}
	}
	else if (map.count(sf::Vector2i(x - 1, y + 1)) && !map.count(sf::Vector2i(x, y + 1)) && !m_isTouchingGround && abs((m_playerObject.getPosition().x + 10) - x * 16) < 16)
	{
		if (map.at(sf::Vector2i(x - 1, y + 1)).intersects(m_playerObject.getGlobalBounds()))
		{
			std::cout << "(x - 1, y + 1)" << std::endl;
			m_isTouchingGround = true;
		}
	}
	else
	{
		m_isTouchingGround = false;
	}

	if (map.count(sf::Vector2i(x, y - 1)) && m_verticalVelocity < 0)
	{
		if (map.at(sf::Vector2i(x, y - 1)).intersects(m_playerObject.getGlobalBounds()))
		{
			std::cout << "(x, y - 1)" << std::endl;
			m_verticalVelocity = -m_verticalVelocity;
		}
	}
	else if (map.count(sf::Vector2i(x - 1, y - 1)) && !m_isTouchingGround && !m_isHittingLeftWall 
		&& m_verticalVelocity < 0 && abs((m_playerObject.getPosition().x + 10) - x * 16) < 16)
	{
		if (map.at(sf::Vector2i(x - 1, y - 1)).intersects(m_playerObject.getGlobalBounds()))
		{
			std::cout << "(x - 1, y - 1)" << std::endl;
			m_verticalVelocity =- m_verticalVelocity;
		}
	}
	else if (map.count(sf::Vector2i(x + 1, y - 1)) && !m_isTouchingGround && !m_isHittingRightWall
		&& m_verticalVelocity < 0 && abs((m_playerObject.getPosition().x + 10) - (x + 1) * 16) > 4)
	{
		if (map.at(sf::Vector2i(x + 1, y - 1)).intersects(m_playerObject.getGlobalBounds()))
		{
			std::cout << "(x + 1, y - 1)" << std::endl;
			m_verticalVelocity = -m_verticalVelocity;
		}
	}

	if (map.count(sf::Vector2i(x + 1, y)))
	{
		if (map.at(sf::Vector2i(x + 1, y)).intersects(m_playerObject.getGlobalBounds()))
		{
			std::cout << "(x + 1, y)" << std::endl;
			m_isHittingRightWall = true;
		}
	}
	else if (map.count(sf::Vector2i(x + 1, y - 1)))
	{
		if (map.at(sf::Vector2i(x + 1, y - 1)).intersects(m_playerObject.getGlobalBounds()))
		{
			std::cout << "(x + 1, y - 1)" << std::endl;
			m_isHittingRightWall = true;
		}
	}
	else if (map.count(sf::Vector2i(x + 1, y + 1)) && !map.count(sf::Vector2i(x + 1, y)) && !m_isTouchingGround)
	{
		if (map.at(sf::Vector2i(x + 1, y + 1)).intersects(m_playerObject.getGlobalBounds()))
		{
			std::cout << "(x + 1, y + 1)" << std::endl;
			m_isHittingRightWall = true;
		}
	}
	else
	{
		m_isHittingRightWall = false;
	}

	if (m_playerObject.getPosition().x < 0)
	{
		m_isHittingLeftWall = true;
	}
	else if (map.count(sf::Vector2i(x - 1, y)))
	{
		if (map.at(sf::Vector2i(x - 1, y)).intersects(m_playerObject.getGlobalBounds()))
		{
			std::cout << "(x - 1, y)" << std::endl;
			m_isHittingLeftWall = true;
		}
	}
	else if (map.count(sf::Vector2i(x - 1, y + 1)) && !map.count(sf::Vector2i(x - 1, y)) && !m_isTouchingGround)
	{
		if (map.at(sf::Vector2i(x - 1, y + 1)).intersects(m_playerObject.getGlobalBounds()))
		{
			std::cout << "(x - 1, y + 1)" << std::endl;
			m_isHittingLeftWall = true;
		}
	}
	else
	{
		m_isHittingLeftWall = false;
	}
}
