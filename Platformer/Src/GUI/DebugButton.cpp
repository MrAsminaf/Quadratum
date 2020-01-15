#include "DebugButton.h"

DebugButton::DebugButton(sf::RenderWindow* window_ptr, sf::Sprite* player_ptr)
	:
	isOnDebug(false),
	m_mainWindowPtr(window_ptr),
	m_playerPtr(player_ptr),
	COLOR_ON_PRESSED(sf::Color(255,0,0,150))
{
	m_debugButtonRectangleShape.setSize(DEFAULT_SIZE);
	m_debugButtonRectangleShape.setFillColor(sf::Color::Yellow);
	m_debugButtonRectangleShape.setPosition(DEFAULT_COORDS);

	m_debugPlayerRectangleShape.setSize(sf::Vector2f(BlocksInfo::blockWidth, BlocksInfo::blockHeight));
	m_debugPlayerRectangleShape.setFillColor(sf::Color(255, 0, 0, 50));

	MakePlayerMarker();
	MakeMouseMarker();
}

sf::RectangleShape& DebugButton::GetObject()
{
	return m_debugButtonRectangleShape;
}

void DebugButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_debugButtonRectangleShape, states);

	if (isOnDebug)
	{
		target.draw(m_playerMarker, states);
		target.draw(m_mouseMarker, states);
	}
}

bool DebugButton::CheckIfClicked()
{ 
	if (sf::Mouse::getPosition(*m_mainWindowPtr).x > m_mainWindowPtr->mapCoordsToPixel(m_debugButtonRectangleShape.getPosition()).x
		&& sf::Mouse::getPosition(*m_mainWindowPtr).x < m_mainWindowPtr->mapCoordsToPixel(m_debugButtonRectangleShape.getPosition()).x + m_debugButtonRectangleShape.getSize().x * 2
		&& sf::Mouse::getPosition(*m_mainWindowPtr).y > m_mainWindowPtr->mapCoordsToPixel(m_debugButtonRectangleShape.getPosition()).y
		&& sf::Mouse::getPosition(*m_mainWindowPtr).y < m_mainWindowPtr->mapCoordsToPixel(m_debugButtonRectangleShape.getPosition()).y + m_debugButtonRectangleShape.getSize().y * 2
		&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
		&& m_delayTimer.getElapsedTime().asMilliseconds() > BUTTON_DELAY)
	{
		return true;
	}
	else
		return false;
}

void DebugButton::SwitchDebugMode()
{
	isOnDebug = !isOnDebug;

	if (isOnDebug)
	{
		std::cout << "Debug is on" << std::endl;
		m_debugButtonRectangleShape.setFillColor(sf::Color::Red);
	}
	else
	{
		std::cout << "Debug is off" << std::endl;
		m_debugButtonRectangleShape.setFillColor(sf::Color::Yellow);
	}

	m_delayTimer.restart();
}

void DebugButton::MakePlayerMarker()
{
	m_playerMarker.setSize(sf::Vector2f(16.f, 16.f));
	m_playerMarker.setFillColor(sf::Color(255, 0, 0, 100));
}

void DebugButton::MakeMouseMarker()
{
	m_mouseMarker.setSize(sf::Vector2f(10.f, 10.f));
	m_mouseMarker.setFillColor(sf::Color(0, 0, 255, 100));
}

void DebugButton::UpdatePlayerMarker()
{
	if (m_playerMarker.getFillColor() != COLOR_ON_PRESSED)
		m_playerMarker.setFillColor(COLOR_ON_PRESSED);

	m_playerMarker.setPosition(float(int(m_playerPtr->getPosition().x / 16) * 16), float(int(m_playerPtr->getPosition().y / 16) * 16));
}

void DebugButton::UpdateMouseMarker()
{
	if (!isOnDebug)
		return;

	const auto pos = sf::Mouse::getPosition(*m_mainWindowPtr);
	m_mouseMarker.setPosition(m_mainWindowPtr->mapPixelToCoords(pos));
}

void DebugButton::HidePlayerMarker()
{
	m_playerMarker.setFillColor(sf::Color::Transparent);
}

