#include "Player.h"

Player::Player()
	:
	m_playerObject(sf::Vector2f(16, 16)),
	m_isTouchingGround(false),
	m_isHittingLeftWall(false),
	m_isHittingRightWall(false),
	m_verticalVelocity(0),
	m_horizontalVelocity(0.25f)
{
	m_playerObject.setFillColor(sf::Color::Yellow);
	m_playerObject.setPosition(30, 30);
	m_playerObject.setOrigin(sf::Vector2f(m_playerObject.getSize().x/2, 8));

	// FOR TEST //

	left.setSize(sf::Vector2f(16, 16));
	left.setFillColor(sf::Color(255, 0, 0, 100));

	right.setSize(sf::Vector2f(16, 16));
	right.setFillColor(sf::Color(255, 0, 0, 100));

	top.setSize(sf::Vector2f(16, 16));
	top.setFillColor(sf::Color(255, 0, 0, 100));
}

void Player::Controls()
{
	if(!m_isHittingLeftWall)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			m_playerObject.move(sf::Vector2f(-m_horizontalVelocity, 0));

	if(!m_isHittingRightWall)
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_playerObject.move(sf::Vector2f(m_horizontalVelocity, 0));

	if(m_isTouchingGround)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_verticalVelocity = -0.87f;
			m_isTouchingGround = false;
		}
}

void Player::UpdateGravity()
{
	if (m_isTouchingGround == false)
	{
		m_verticalVelocity += 0.005f;
		m_playerObject.move(0, m_verticalVelocity);
	}
	else
		m_verticalVelocity = 0.f;
}

void Player::Collision(const std::vector<std::string>& map)
{
	const int x = m_playerObject.getPosition().x / 16;
	const int y = m_playerObject.getPosition().y / 16;

	left.setPosition((x - 1) * 16, y*16);
	right.setPosition((x + 1) * 16, y * 16);
	top.setPosition((x) * 16, (y - 1) * 16);

	if (map.at(y + 1).at(x) != ' ' ||
		(map.at(y + 1).at(x + 1) != ' ' && m_playerObject.getPosition().x + 8 > (x + 1) * 16) ||
		(map.at(y + 1).at(x - 1) != ' ' && m_playerObject.getPosition().x - 8 < x * 16))
	{
		if ((y + 1) * 16 <= m_playerObject.getPosition().y + 8)
		{
			m_isTouchingGround = true;
			std::cout << "Ground" << std::endl;
		}
	}
	else
		m_isTouchingGround = false;

	if (map.at(y - 1).at(x) != ' ' && m_playerObject.getPosition().y - 8 < ((y - 1) * 16) + 16 ||
		(map.at(y - 1).at(x) == ' ' && map.at(y - 1).at(x + 1) != ' ' && m_playerObject.getPosition().x + 8 > (x + 1) * 16 && m_playerObject.getPosition().y - 8 < ((y - 1) * 16) + 16) ||
		(map.at(y - 1).at(x) == ' ' && map.at(y - 1).at(x - 1) != ' ' && m_playerObject.getPosition().x - 8 < ((x - 1) * 16) + 16 && m_playerObject.getPosition().y - 8 < ((y - 1) * 16) + 16))  // hitting ceiling
	{
		m_verticalVelocity = -m_verticalVelocity;
	}

	if (map.at(y).at(x - 1) != ' ' ||
		(map.at(y).at(x) == ' ' && map.at(y + 1).at(x) == ' ' && map.at(y + 1).at(x - 1) != ' '/* && m_playerObject.getPosition().x - 8 < ((x-1)*16)+16 && m_playerObject.getPosition().y+8 > (y+1)*16*/) ||
		(map.at(y).at(x) == ' ' && map.at(y - 1).at(x) == ' ' && map.at(y).at(x - 1) == ' ' && map.at(y - 1).at(x - 1) != ' ' /*&& m_playerObject.getPosition().x - 8 < ((x - 1) * 16) + 16 && m_playerObject.getPosition().y - 8 < ((y - 1) * 16) + 16*/))
	{
		if ((x - 1) * 16 >= m_playerObject.getPosition().x - 24)
		{
			m_isHittingLeftWall = true;
		}
	}
	else
		m_isHittingLeftWall = false;

	if (map.at(y).at(x + 1) != ' ')
	{
		if ((x + 1) * 16 <= m_playerObject.getPosition().x + 8)
		{
			m_isHittingRightWall = true;
		}
	}
	else 
		m_isHittingRightWall = false;

}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_playerObject, states);
	target.draw(left, states);
	target.draw(right, states);
	target.draw(top, states);
}

sf::RectangleShape & Player::GetPlayerObject()
{
	return m_playerObject;
}
