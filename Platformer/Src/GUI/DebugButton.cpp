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
	}
}

void DebugButton::Update()
{
	m_debugButtonRectangleShape.setPosition(m_mainWindowPtr->mapPixelToCoords(sf::Vector2i(DEFAULT_COORDS)));

	if (CheckIfClicked())
		SwitchDebugMode();

	if (isOnDebug)
	{
		UpdatePlayerMarker();
	}
	else
	{
		HidePlayerMarker();
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

void DebugButton::UpdatePlayerMarker()
{
	if (m_playerMarker.getFillColor() != COLOR_ON_PRESSED)
		m_playerMarker.setFillColor(COLOR_ON_PRESSED);

	m_playerMarker.setPosition(float(int(m_playerPtr->getPosition().x / 16) * 16), float(int(m_playerPtr->getPosition().y / 16) * 16));
}

void DebugButton::HidePlayerMarker()
{
	m_playerMarker.setFillColor(sf::Color::Transparent);
}
