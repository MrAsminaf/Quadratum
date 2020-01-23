#include "Collision.h"

Collision::Collision()
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

//Collision::Collision(sf::Sprite* sprite, std::unordered_map<sf::Vector2i, sf::FloatRect>* map)
//	:
//	m_spritePtr(sprite),
//	m_mapPtr(map)
//{
//	Collision();
//}

void Collision::AssignSprite(sf::Sprite* sprite)
{
	m_spritePtr = sprite;
}

//void Collision::AssignMap(std::unordered_map<sf::Vector2i, sf::FloatRect>* map)
//{
//	m_mapPtr = map;
//}

bool Collision::IsTouchingGround() const
{
	return m_isTouchingGround;
}

bool Collision::IsHittingLeftWall() const
{
	return m_isHittingLeftWall;
}

bool Collision::IsHittingRightWall() const
{
	return m_isHittingRightWall;
}

void Collision::Check()
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


}

bool Collision::CheckForTouchingGround(int x, int y)
{
	if (m_mapPtr->count(sf::Vector2i(x, y + 1)))
	{
		if (m_mapPtr->at(sf::Vector2i(x, y + 1)).intersects(m_spritePtr->getGlobalBounds()))
		{
			m_isTouchingGround = true;
			if (m_spritePtr->getPosition().y + 16 > (y + 1) * 16 + 3)
				m_spritePtr->setPosition(m_spritePtr->getPosition().x, m_spritePtr->getPosition().y - 3);
		}
	}
	else if (m_mapPtr->count(sf::Vector2i(x + 1, y + 1)) && !m_mapPtr->count(sf::Vector2i(x, y + 1)) && m_isTouchingGround && abs(m_spritePtr->getPosition().x - x * 16) > 10)
	{
		if (m_mapPtr->at(sf::Vector2i(x + 1, y + 1)).intersects(m_spritePtr->getGlobalBounds()))
		{
			m_isTouchingGround = true;

			if (m_spritePtr->getPosition().y + 16 > (y + 1) * 16 + 3)
				m_spritePtr->setPosition(m_spritePtr->getPosition().x, m_spritePtr->getPosition().y - 3);
		}
	}
	else if (m_mapPtr->count(sf::Vector2i(x - 1, y + 1)) && !m_mapPtr->count(sf::Vector2i(x, y + 1)) && m_isTouchingGround && abs((m_spritePtr->getPosition().x + 10) - x * 16) < 16)
	{
		if (m_mapPtr->at(sf::Vector2i(x - 1, y + 1)).intersects(m_spritePtr->getGlobalBounds()))
		{
			m_isTouchingGround = true;

			if (m_spritePtr->getPosition().y + 16 > (y + 1) * 16 + 3)
				m_spritePtr->setPosition(m_spritePtr->getPosition().x, m_spritePtr->getPosition().y - 3);
		}
	}
	else if (m_mapPtr->count(sf::Vector2i(x + 1, y + 1)) && !m_mapPtr->count(sf::Vector2i(x, y + 1)) && !m_isTouchingGround && abs(m_spritePtr->getPosition().x - x * 16) > 10)
	{
		if (m_mapPtr->at(sf::Vector2i(x + 1, y + 1)).intersects(m_spritePtr->getGlobalBounds()))
		{
			m_isTouchingGround = true;

			if (m_spritePtr->getPosition().y + 16 > (y + 1) * 16 + 3)
				m_spritePtr->setPosition(m_spritePtr->getPosition().x, m_spritePtr->getPosition().y - 3);
		}
	}
	else if (m_mapPtr->count(sf::Vector2i(x - 1, y + 1)) && !m_mapPtr->count(sf::Vector2i(x, y + 1)) && !m_isTouchingGround && abs((m_spritePtr->getPosition().x + 10) - x * 16) < 16)
	{
		if (m_mapPtr->at(sf::Vector2i(x - 1, y + 1)).intersects(m_spritePtr->getGlobalBounds()))
		{
			m_isTouchingGround = true;

			if (m_spritePtr->getPosition().y + 16 > (y + 1) * 16 + 3)
				m_spritePtr->setPosition(m_spritePtr->getPosition().x, m_spritePtr->getPosition().y - 3);
		}
	}
	else
	{
		m_isTouchingGround = false;
	}
}
