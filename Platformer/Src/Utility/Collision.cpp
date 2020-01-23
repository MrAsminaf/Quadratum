#include "Collision.h"

Collision::Collision()
	:
	m_previousIsTouchingGround(false),
	m_isTouchingGround(false),
	m_isHittingLeftWall(false),
	m_isHittingRightWall(false)
{
}

Collision::Collision(sf::Sprite* sprite)
	:
	m_sprite(sprite)
{
	Collision();
}

void Collision::AssignSprite(sf::Sprite* sprite)
{
	m_sprite = sprite;
}

bool Collision::IsTouchingGround()
{
	return false;
}
