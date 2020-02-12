#include "Player.h"

Player::Player(sf::RenderWindow* window_ptr)
	:
	m_previousIsTouchingGround	(false),
	m_isTouchingGround			(false),
	m_isHittingLeftWall			(false),
	m_isHittingRightWall		(false),
	m_isIdle					(false),
	m_isSpaceReleased			(true),
	m_verticalVelocity			(0.f),
	m_horizontalVelocity		(0.f),
	SLIDE_SPEED_CHANGE			(0.2f),
	MAX_HORIZONTAL_VELOCITY		(2.5f),
	m_playerScale				(sf::Vector2f(1.5, 1.5)),
	m_mainWindowPtr				(window_ptr)
{
	LoadTextures();
}

void Player::Controls()
{
	m_isIdle = false;
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		m_isSpaceReleased = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (!m_isHittingLeftWall)
		{
			if (m_horizontalVelocity <= MAX_HORIZONTAL_VELOCITY)
				m_horizontalVelocity += SLIDE_SPEED_CHANGE;

			m_playerObject.move(sf::Vector2f(-m_horizontalVelocity, 0));
		}
		else
		{
			m_horizontalVelocity = 0;
		}

		if (m_playerObject.getScale() == m_playerScale)
			m_playerObject.setScale(sf::Vector2f(-m_playerScale.x, m_playerScale.y));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (!m_isHittingRightWall)
		{
			if (m_horizontalVelocity <= MAX_HORIZONTAL_VELOCITY)
				m_horizontalVelocity += SLIDE_SPEED_CHANGE;

			m_playerObject.move(sf::Vector2f(m_horizontalVelocity, 0));
		}
		else
		{
			m_horizontalVelocity = 0;
		}

		if (m_playerObject.getScale() == sf::Vector2f(-m_playerScale.x, m_playerScale.y))
			m_playerObject.setScale(m_playerScale);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_horizontalVelocity = 0;
	}

	if (m_isTouchingGround)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_isSpaceReleased)
		{
			// "launch" player upwards
			m_verticalVelocity = -5.25f;
			m_isTouchingGround = false;
			m_isSpaceReleased = false;
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (m_isTouchingGround)
			m_isIdle = true;

		if (m_horizontalVelocity > 0.f)
			m_horizontalVelocity -= SLIDE_SPEED_CHANGE;
		else
			m_horizontalVelocity = 0.f;

		if (m_playerObject.getScale() == sf::Vector2f(-m_playerScale.x, m_playerScale.y) && !m_isHittingLeftWall)
		{
			m_playerObject.move(sf::Vector2f(-m_horizontalVelocity, 0));
		}
		else if (m_playerObject.getScale() == sf::Vector2f(m_playerScale.x, m_playerScale.y) && !m_isHittingRightWall)
		{
			m_playerObject.move(sf::Vector2f(m_horizontalVelocity, 0));
		}
	}
}

void Player::GotHit()
{
	m_healthCooldownClock.restart();
	m_playerObject.setColor(sf::Color::Red);
	m_verticalVelocity = -4.f;
	m_isTouchingGround = false;
	
	std::cout << "Player got hit" << std::endl;
}

void Player::UpdateGravity()
{
	if (m_isTouchingGround == false)
	{
		m_verticalVelocity = m_verticalVelocity + 0.20f;
		m_playerObject.move(0, m_verticalVelocity);
	}
	else
		m_verticalVelocity = 0.f;
}

bool Player::IsHitByEnemy(std::vector<Enemy>& enemyContainer)
{
	for (auto& enemyObj : enemyContainer)
	{
		if (enemyObj.GetPosition().x <= m_playerObject.getPosition().x
			&& m_playerObject.getPosition().x <= enemyObj.GetPosition().x + enemyObj.GetObject().getSize().x
			&& m_playerObject.getPosition().y - enemyObj.GetPosition().y < 20
			&& m_playerObject.getPosition().y - enemyObj.GetPosition().y > -enemyObj.GetObject().getSize().y)
		{
			return true;
		}
	}
	return false;
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_playerObject, states);
}

sf::Sprite & Player::GetPlayerObject()
{
	return m_playerObject;
}

float Player::GetHorizontalVelocity()
{
	if (m_playerObject.getScale() == sf::Vector2f(m_playerScale.x, m_playerScale.y))
		return m_horizontalVelocity;
	else
		return -m_horizontalVelocity;
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
			m_idleAnimation.AddAnimationFrame(temp);
	}
	m_idleAnimation.SetTimeInterval(0.14f);

	for (int i = 0; i < 6; i++)
	{
		sf::Texture temp;
		std::string filename = std::string("run_").append(std::to_string(i)) + ".png";
		if (!temp.loadFromFile(std::string("Res/Animations/Character/Run/" + filename)))
			std::cerr << "Could not load character texture" << std::endl;
		else
			m_runningAmination.AddAnimationFrame(temp);
	}
	m_runningAmination.SetTimeInterval(0.1f);

	sf::Texture temp;
	std::string filename = std::string("jump_0.png");
	if (!temp.loadFromFile(std::string("Res/Animations/Character/Jump/" + filename)))
		std::cerr << "Could not load character texture" << std::endl;
	else
		m_jumpUpAnimation.AddAnimationFrame(temp);


	for (int i = 1; i < 4; i++)
	{
		sf::Texture temp;
		std::string filename = std::string("jump_").append(std::to_string(i)) + ".png";
		if (!temp.loadFromFile(std::string("Res/Animations/Character/Jump/" + filename)))
			std::cerr << "Could not load character texture" << std::endl;
		else
			m_jumpDownAnimation.AddAnimationFrame(temp);
	}
	m_jumpDownAnimation.SetTimeInterval(0.1f);

	m_playerObject.setTexture(m_idleAnimation.GetFrame(0));
	m_playerObject.setPosition(100, -50);
	m_playerObject.setScale(m_playerScale);
	m_playerObject.setOrigin(sf::Vector2f(m_playerObject.getTexture()->getSize().x / 2.f, m_playerObject.getTexture()->getSize().y / 2.f));
}