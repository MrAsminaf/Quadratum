#include "Player.h"

Player::Player(sf::RenderWindow* window_ptr)
	:
	m_previousIsTouchingGround	(false),
	m_isTouchingGround			(false),
	m_isHittingLeftWall			(false),
	m_isHittingRightWall		(false),
	m_isIdle					(false),
	m_verticalVelocity			(0.f),
	m_horizontalVelocity		(0.f),
	m_HORIZONTALVELOCITY		(0.17f),
	m_playerScale				(sf::Vector2f(1.5, 1.5)),
	m_mainWindowPtr				(window_ptr)
{
	LoadTextures();
}

float Player::Controls(const sf::Time& delta_time)
{
	m_isIdle = false;
	m_horizontalVelocity = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (!m_isHittingLeftWall)
		{
			testVelocity += 0.003f;
			if (testVelocity > m_HORIZONTALVELOCITY)
				testVelocity = m_HORIZONTALVELOCITY;

			m_playerObject.move(sf::Vector2f(-testVelocity * delta_time.asMilliseconds(), 0));
			m_horizontalVelocity = -testVelocity * delta_time.asMilliseconds();
		}

		if (m_playerObject.getScale() == m_playerScale)
			m_playerObject.setScale(sf::Vector2f(-m_playerScale.x, m_playerScale.y));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (!m_isHittingRightWall)
		{
			testVelocity += 0.003f;
			if (testVelocity > m_HORIZONTALVELOCITY)
				testVelocity = m_HORIZONTALVELOCITY;

			m_playerObject.move(sf::Vector2f(testVelocity * delta_time.asMilliseconds(), 0));
			m_horizontalVelocity = testVelocity * delta_time.asMilliseconds();
		}

		if (m_playerObject.getScale() == sf::Vector2f(-m_playerScale.x, m_playerScale.y))
			m_playerObject.setScale(m_playerScale);
	}

	if (m_isTouchingGround)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_verticalVelocity = -375.f;
			m_isTouchingGround = false;
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (m_isTouchingGround)
			m_isIdle = true;
		
		if (testVelocity > 0.f)
			testVelocity -= 0.003f;
		else
			testVelocity = 0.f;

		if (m_playerObject.getScale() == sf::Vector2f(-m_playerScale.x, m_playerScale.y) && !m_isHittingLeftWall)
		{
			m_playerObject.move(sf::Vector2f(-testVelocity * delta_time.asMilliseconds(), 0));
			m_horizontalVelocity = -testVelocity * delta_time.asMilliseconds();
		}
		else if (m_playerObject.getScale() == sf::Vector2f(m_playerScale.x, m_playerScale.y) && !m_isHittingRightWall)
		{
			m_playerObject.move(sf::Vector2f(testVelocity * delta_time.asMilliseconds(), 0));
			m_horizontalVelocity = testVelocity * delta_time.asMilliseconds();
		}
	}
	return m_horizontalVelocity;
}

void Player::GotHit()
{
	m_healthCooldownClock.restart();
	m_playerObject.setColor(sf::Color::Red);
	m_verticalVelocity = -300.f;
	m_isTouchingGround = false;
	
	std::cout << "Player got hit" << std::endl;
}

void Player::UpdateGravity(const sf::Time& delta_time)
{
	if (m_isTouchingGround == false)
	{
		m_verticalVelocity = m_verticalVelocity + 1000.f * delta_time.asSeconds();
		m_playerObject.move(0, m_verticalVelocity * delta_time.asSeconds());
	}
	else
		m_verticalVelocity = 0.f;
}

void Player::Collision(const std::vector<std::string>& map)
{
	const int x = int(m_playerObject.getPosition().x) / 16;
	const int y = int(m_playerObject.getPosition().y) / 16;

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

void Player::PrintCollisionInfo(const int x, const int y) const
{
	std::cout << "Intersects (" << x << ", " << y << ")" << std::endl;
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_playerObject, states);
}

sf::Sprite & Player::GetPlayerObject()
{
	return m_playerObject;
}

float Player::GetHorizontalVelocity() const
{
	return m_horizontalVelocity;
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
	m_playerObject.setPosition(100, 30);
	m_playerObject.setScale(m_playerScale);
	m_playerObject.setOrigin(sf::Vector2f(m_playerObject.getTexture()->getSize().x / 2.f, m_playerObject.getTexture()->getSize().y / 2.f));
}