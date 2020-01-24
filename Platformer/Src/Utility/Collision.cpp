#include "Collision.h"

template<typename T1, typename T2>
Collision<typename T1, typename T2>::Collision()
	:
	m_previousIsTouchingGround(false),
	m_isTouchingGround(false),
	m_isHittingLeftWall(false),
	m_isHittingRightWall(false)
{
	if (!m_mapPtr)
		std::cout << "NULL m_mapPtr" << std::endl;
	if (!m_spritePtr)
		std::cout << "NULL m_mapPtr" << std::endl;
}

template<typename T1, typename T2>
Collision<typename T1, typename T2>::Collision(sf::Sprite* sprite, std::unordered_map<sf::Vector2<T1>, sf::Rect<T2>>* map)
	:
	m_spritePtr(sprite),
	m_mapPtr(map)
{
	Collision();
}

template<typename T1, typename T2>
void Collision<typename T1, typename T2>::AssignSprite(sf::Sprite* sprite)
{
	m_spritePtr = sprite;
}

template<typename T1, typename T2>
void Collision<typename T1, typename T2>::AssignMap(std::unordered_map<sf::Vector2<T1>, sf::Rect<T2>>* map)
{
	m_mapPtr = map;
}

template<typename T1, typename T2>
bool Collision<typename T1, typename T2>::IsTouchingGround() const
{
	return m_isTouchingGround;
}

template<typename T1, typename T2>
bool Collision<typename T1, typename T2>::IsHittingLeftWall() const
{
	return m_isHittingLeftWall;
}

template<typename T1, typename T2>
bool Collision<typename T1, typename T2>::IsHittingRightWall() const
{
	return m_isHittingRightWall;
}

template<typename T1, typename T2>
void Collision<typename T1, typename T2>::Check()
{
	if (m_mapPtr == nullptr)
	{
		std::cout << "m_mapPtr is a nullptr" << std::endl;
		return;
	}
	else if (m_spritePtr == nullptr)
	{
		std::cout << "m_spritePtr is a nullptr" << std::endl;
		return;
	}

	const auto pos = m_spritePtr->getPosition();
	const int x = int(pos.x / 16);
	const int y = int(pos.y / 16);

	CheckForTouchingGround(x, y);
	CheckForLeftWallCollision(x, y);
	CheckForRightWallCollision(x, y);
}

template<typename T1, typename T2>
bool Collision<typename T1, typename T2>::CheckForTouchingGround(int x, int y)
{
	if (m_mapPtr->count(sf::Vector2i(x, y + 1)))
	{
		if (m_mapPtr->at(sf::Vector2i(x, y + 1)).intersects(m_spritePtr->getGlobalBounds()))
		{
			m_isTouchingGround = true;
			if (m_spritePtr->getPosition().y + 16 > (y + 1) * 16 + 3)
				m_spritePtr->setPosition(m_spritePtr->getPosition().x, m_spritePtr->getPosition().y - 3);
			return true;
		}
	}
	else if (m_mapPtr->count(sf::Vector2i(x + 1, y + 1)) && !m_mapPtr->count(sf::Vector2i(x, y + 1)) && m_isTouchingGround && abs(m_spritePtr->getPosition().x - x * 16) > 10)
	{
		if (m_mapPtr->at(sf::Vector2i(x + 1, y + 1)).intersects(m_spritePtr->getGlobalBounds()))
		{
			m_isTouchingGround = true;
			if (m_spritePtr->getPosition().y + 16 > (y + 1) * 16 + 3)
				m_spritePtr->setPosition(m_spritePtr->getPosition().x, m_spritePtr->getPosition().y - 3);
			return true;
		}
	}
	else if (m_mapPtr->count(sf::Vector2i(x - 1, y + 1)) && !m_mapPtr->count(sf::Vector2i(x, y + 1)) && m_isTouchingGround && abs((m_spritePtr->getPosition().x + 10) - x * 16) < 16)
	{
		if (m_mapPtr->at(sf::Vector2i(x - 1, y + 1)).intersects(m_spritePtr->getGlobalBounds()))
		{
			m_isTouchingGround = true;
			if (m_spritePtr->getPosition().y + 16 > (y + 1) * 16 + 3)
				m_spritePtr->setPosition(m_spritePtr->getPosition().x, m_spritePtr->getPosition().y - 3);
			return true;
		}
	}
	else if (m_mapPtr->count(sf::Vector2i(x + 1, y + 1)) && !m_mapPtr->count(sf::Vector2i(x, y + 1)) && !m_isTouchingGround && abs(m_spritePtr->getPosition().x - x * 16) > 10)
	{
		if (m_mapPtr->at(sf::Vector2i(x + 1, y + 1)).intersects(m_spritePtr->getGlobalBounds()))
		{
			m_isTouchingGround = true;
			if (m_spritePtr->getPosition().y + 16 > (y + 1) * 16 + 3)
				m_spritePtr->setPosition(m_spritePtr->getPosition().x, m_spritePtr->getPosition().y - 3);
			return true;
		}
	}
	else if (m_mapPtr->count(sf::Vector2i(x - 1, y + 1)) && !m_mapPtr->count(sf::Vector2i(x, y + 1)) && !m_isTouchingGround && abs((m_spritePtr->getPosition().x + 10) - x * 16) < 16)
	{
		if (m_mapPtr->at(sf::Vector2i(x - 1, y + 1)).intersects(m_spritePtr->getGlobalBounds()))
		{
			m_isTouchingGround = true;
			if (m_spritePtr->getPosition().y + 16 > (y + 1) * 16 + 3)
				m_spritePtr->setPosition(m_spritePtr->getPosition().x, m_spritePtr->getPosition().y - 3);
			return true;
		}
	}
	else
	{
		m_isTouchingGround = false;
		return false;
	}
}

template<typename T1, typename T2>
bool Collision<T1, T2>::CheckForLeftWallCollision(int x, int y)
{
	if (m_mapPtr->count(sf::Vector2i(x + 1, y)))
	{
		if (m_mapPtr->at(sf::Vector2i(x + 1, y)).intersects(m_spritePtr->getGlobalBounds()))
		{
			m_isHittingRightWall = true;
			return true;
		}
	}
	else if (m_mapPtr->count(sf::Vector2i(x + 1, y - 1)))
	{
		if (m_mapPtr->at(sf::Vector2i(x + 1, y - 1)).intersects(m_spritePtr->getGlobalBounds()))
		{
			m_isHittingRightWall = true;
			return true;
		}
	}
	else if (m_mapPtr->count(sf::Vector2i(x + 1, y + 1)) && !m_mapPtr->count(sf::Vector2i(x + 1, y)) && !m_isTouchingGround)
	{
		if (m_mapPtr->at(sf::Vector2i(x + 1, y + 1)).intersects(m_spritePtr->getGlobalBounds()))
		{
			m_isHittingRightWall = true;
			return true;
		}
	}
	else
	{
		m_isHittingRightWall = false;
		return false;
	}
}

template<typename T1, typename T2>
bool Collision<T1, T2>::CheckForRightWallCollision(int x, int y)
{
	if (m_spritePtr->getPosition().x < 0)
	{
		m_isHittingLeftWall = true;
		return true;
	}
	else if (m_mapPtr->count(sf::Vector2i(x - 1, y)))
	{
		if (m_mapPtr->at(sf::Vector2i(x - 1, y)).intersects(m_spritePtr->getGlobalBounds()))
		{
			m_isHittingLeftWall = true;
			return true;
		}
	}
	else if (m_mapPtr->count(sf::Vector2i(x - 1, y + 1)) && !m_mapPtr->count(sf::Vector2i(x - 1, y)) && !m_isTouchingGround)
	{
		if (m_mapPtr->at(sf::Vector2i(x - 1, y + 1)).intersects(m_spritePtr->getGlobalBounds()))
		{
			m_isHittingLeftWall = true;
			return true;
		}
	}
	else
	{
		m_isHittingLeftWall = false;
		return false;
	}
}

void TempFunc()
{
	Collision<sf::Vector2i, sf::FloatRect> temoObj;
}
