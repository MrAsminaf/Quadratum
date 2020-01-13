#include "DebugButton.h"

DebugButton::DebugButton()
	:
	isOnDebug(false)
{
	m_rectangleShape.setSize(DEFAULT_SIZE);
	m_rectangleShape.setFillColor(sf::Color::Yellow);
	m_rectangleShape.setPosition(DEFAULT_COORDS);
}

sf::RectangleShape& DebugButton::GetObject()
{
	return m_rectangleShape;
}

void DebugButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_rectangleShape, states);
}

void DebugButton::Update(const sf::RenderWindow& window)
{
	m_rectangleShape.setPosition(window.mapPixelToCoords(sf::Vector2i(DEFAULT_COORDS)));
	CheckIfClicked(window);
}

bool DebugButton::CheckIfClicked(const sf::RenderWindow& window)
{ 
	if (sf::Mouse::getPosition(window).x > window.mapCoordsToPixel(m_rectangleShape.getPosition()).x
		&& sf::Mouse::getPosition(window).x < window.mapCoordsToPixel(m_rectangleShape.getPosition()).x + m_rectangleShape.getSize().x * 2
		&& sf::Mouse::getPosition(window).y > window.mapCoordsToPixel(m_rectangleShape.getPosition()).y
		&& sf::Mouse::getPosition(window).y < window.mapCoordsToPixel(m_rectangleShape.getPosition()).y + m_rectangleShape.getSize().y * 2
		&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
		&& m_delayTimer.getElapsedTime().asMilliseconds() > BUTTON_DELAY)
	{
		isOnDebug = !isOnDebug;
		
		if (isOnDebug)
		{
			std::cout << "Debug is on" << std::endl;
			m_rectangleShape.setFillColor(sf::Color::Red);
		}
		else
		{
			std::cout << "Debug is off" << std::endl;
			m_rectangleShape.setFillColor(sf::Color::Yellow);
		}

		m_delayTimer.restart();
	}

	return true;
}
