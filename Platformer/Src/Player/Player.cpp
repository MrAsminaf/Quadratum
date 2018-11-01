#include "Player.h"

Player::Player()
	:
	m_previousIsTouchingGround	(false),
	m_isTouchingGround			(false),
	m_isHittingLeftWall			(false),
	m_isHittingRightWall		(false),
	m_isIdle					(false),
	m_verticalVelocity			(0),
	m_horizontalVelocity		(0.17f),
	m_idleAnimationTimeInterval	(0.14f),
	m_runAnimationTimeInterval	(0.1f),
	m_jumpAnimationTimeInterval	(0.1f),
	m_playerScale				(sf::Vector2f(1.5, 1.5))
{
	LoadTextures();
}

float Player::Controls(const sf::Time& delta_time)
{
	m_isIdle = false;
	float currentSpeed = 0;

	if(!m_isHittingLeftWall)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_playerObject.move(sf::Vector2f(-m_horizontalVelocity * delta_time.asMilliseconds(), 0));
			currentSpeed = -m_horizontalVelocity * delta_time.asMilliseconds();

			if (m_playerObject.getScale() == m_playerScale)
				m_playerObject.setScale(sf::Vector2f(-m_playerScale.x, m_playerScale.y));
		}

	 if(!m_isHittingRightWall)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_playerObject.move(sf::Vector2f(m_horizontalVelocity * delta_time.asMilliseconds(), 0));
			currentSpeed = m_horizontalVelocity * delta_time.asMilliseconds();

			if (m_playerObject.getScale() == sf::Vector2f(-m_playerScale.x, m_playerScale.y))
				m_playerObject.setScale(m_playerScale);
		}

	if(m_isTouchingGround)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_verticalVelocity = -0.87f ;
			m_isTouchingGround = false;
		}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_isTouchingGround)
		m_isIdle = true;

	return currentSpeed;
}

void Player::Update(const std::vector<std::string>& map, const sf::Time& delta_time)
{
	m_previousIsTouchingGround = m_isTouchingGround;
	UpdateGravity(delta_time);
	Collision(map);

	if (m_isIdle)
		IdleAnimation(delta_time);
	else if (m_isTouchingGround)
		RunAnimation();
	else if (!m_isTouchingGround)
		JumpAnimation();
}

void Player::UpdateGravity(const sf::Time& delta_time)
{
	if (m_isTouchingGround == false)
	{
		m_verticalVelocity += 0.0027f * delta_time.asMilliseconds();
		m_playerObject.move(0, m_verticalVelocity);
	}
	else
		m_verticalVelocity = 0.f;
}

void Player::Collision(const std::vector<std::string>& map)
{
	const int x = m_playerObject.getPosition().x / 16;
	const int y = m_playerObject.getPosition().y / 16;

	if (map.at(y + 1).at(x) != ' ' ||
		(map.at(y + 1).at(x + 1) != ' ' && m_playerObject.getPosition().x + 8 > (x + 1) * 16) ||
		(map.at(y + 1).at(x - 1) != ' ' && m_playerObject.getPosition().x - 8 < x * 16))
	{
		if ((y + 1) * 16 <= m_playerObject.getPosition().y + 16)
		{
			m_isTouchingGround = true;
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
		(map.at(y).at(x) == ' ' && map.at(y + 1).at(x) == ' ' && map.at(y + 1).at(x - 1) != ' ' && m_isTouchingGround == false) ||
		(map.at(y).at(x) == ' ' && map.at(y - 1).at(x) == ' ' && map.at(y).at(x - 1) == ' ' && map.at(y - 1).at(x - 1) != ' '))
	{
		if ((x - 1) * 16 >= m_playerObject.getPosition().x - 28)
		{
			m_isHittingLeftWall = true;
		}
	}
	else
		m_isHittingLeftWall = false;

	if (map.at(y).at(x + 1) != ' ' ||
		(map.at(y).at(x) == ' ' && map.at(y + 1).at(x) == ' ' && map.at(y + 1).at(x + 1) != ' ' && m_isTouchingGround == false) ||
		(map.at(y).at(x) == ' ' && map.at(y - 1).at(x) == ' ' && map.at(y).at(x + 1) == ' ' && map.at(y - 1).at(x + 1) != ' '))
	{
		if ((x + 1) * 16 <= m_playerObject.getPosition().x + 10)
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
}

sf::Sprite & Player::GetPlayerObject()
{
	return m_playerObject;
}

void Player::LoadTextures()
{
	for (int i = 0; i < 4; ++i)
	{
		sf::Texture temp;
		std::string filename = std::string("idle_").append(std::to_string(i)) + ".png";
		if (!temp.loadFromFile(std::string("Res/Animations/Character/Idle/" + filename)))
			std::cerr << "Could not load character texture" << std::endl;
		else
			m_idleTextures.push_back(temp);
	}

	for (int i = 0; i < 6; i++)
	{
		sf::Texture temp;
		std::string filename = std::string("run_").append(std::to_string(i)) + ".png";
		if (!temp.loadFromFile(std::string("Res/Animations/Character/Run/" + filename)))
			std::cerr << "Could not load character texture" << std::endl;
		else
			m_runTextures.push_back(temp);
	}

	for (int i = 0; i < 6; i++)
	{
		sf::Texture temp;
		std::string filename = std::string("jump_").append(std::to_string(i)) + ".png";
		if (!temp.loadFromFile(std::string("Res/Animations/Character/Jump/" + filename)))
			std::cerr << "Could not load character texture" << std::endl;
		else
			m_jumpTextures.push_back(temp);
	}

	m_playerObject.setTexture(m_idleTextures[0]);
	m_playerObject.setPosition(30, 30);
	m_playerObject.setScale(m_playerScale);
	m_playerObject.setOrigin(sf::Vector2f(m_playerObject.getTexture()->getSize().x / 2, m_playerObject.getTexture()->getSize().y / 2));
}

void Player::IdleAnimation(const sf::Time& delta_time)
{	
	sf::Time time = m_clock.getElapsedTime();

	if (time.asSeconds() > m_idleAnimationTimeInterval * 3)
		m_clock.restart();

	if (time.asSeconds() > 0 && time.asSeconds() < m_idleAnimationTimeInterval)
	{
		m_playerObject.setTexture(m_idleTextures.at(0));
	}
	else if (time.asSeconds() > m_idleAnimationTimeInterval && time.asSeconds() < m_idleAnimationTimeInterval * 2)
	{
		m_playerObject.setTexture(m_idleTextures.at(1));
	}
	else if (time.asSeconds() > m_idleAnimationTimeInterval * 2 && time.asSeconds() < m_idleAnimationTimeInterval * 3)
	{
		m_playerObject.setTexture(m_idleTextures.at(2));
	}
}

void Player::RunAnimation()
{
	sf::Time time = m_clock.getElapsedTime();

	if (time.asSeconds() > m_runAnimationTimeInterval * 6)
		m_clock.restart();

	if (time.asSeconds() > 0 && time.asSeconds() < m_runAnimationTimeInterval)
	{
		m_playerObject.setTexture(m_runTextures.at(0));
	}
	else if (time.asSeconds() > m_runAnimationTimeInterval && time.asSeconds() < m_runAnimationTimeInterval * 2)
	{
		m_playerObject.setTexture(m_runTextures.at(1));
	}
	else if (time.asSeconds() > m_runAnimationTimeInterval * 2 && time.asSeconds() < m_runAnimationTimeInterval * 3)
	{
		m_playerObject.setTexture(m_runTextures.at(2));
	}
	else if (time.asSeconds() > m_runAnimationTimeInterval * 3 && time.asSeconds() < m_runAnimationTimeInterval * 4)
	{
		m_playerObject.setTexture(m_runTextures.at(3));
	}
	else if (time.asSeconds() > m_runAnimationTimeInterval * 4 && time.asSeconds() < m_runAnimationTimeInterval * 5)
	{
		m_playerObject.setTexture(m_runTextures.at(4));
	}
	else if (time.asSeconds() > m_runAnimationTimeInterval * 5 && time.asSeconds() < m_runAnimationTimeInterval * 6)
	{
		m_playerObject.setTexture(m_runTextures.at(5));
	}
}

void Player::JumpAnimation()
{
	sf::Time time = m_clock.getElapsedTime();

	if (m_verticalVelocity < 0)
		m_playerObject.setTexture(m_jumpTextures.at(0));
	else if (m_verticalVelocity > 0)
	{
		if (time.asSeconds() > m_jumpAnimationTimeInterval * 3)
			m_clock.restart();

		if (time.asSeconds() > 0 && time.asSeconds() < m_jumpAnimationTimeInterval)
		{
			m_playerObject.setTexture(m_jumpTextures.at(1));
		}
		else if (time.asSeconds() > m_jumpAnimationTimeInterval && time.asSeconds() < m_jumpAnimationTimeInterval * 2)
		{
			m_playerObject.setTexture(m_jumpTextures.at(2));
		}
		else if (time.asSeconds() > m_jumpAnimationTimeInterval * 2 && time.asSeconds() < m_jumpAnimationTimeInterval * 3)
		{
			m_playerObject.setTexture(m_jumpTextures.at(3));
		}
	}
}
