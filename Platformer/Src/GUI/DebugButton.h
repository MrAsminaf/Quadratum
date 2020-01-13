#pragma once

#include "../Window/Window_info.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class DebugButton : public sf::Drawable
{
public:
	DebugButton();
	sf::RectangleShape& GetObject();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update(const sf::RenderWindow& window);
	bool CheckIfClicked(const sf::RenderWindow& window);
private:
	bool isOnDebug;
	sf::RectangleShape m_rectangleShape;
	sf::Clock m_delayTimer;
	const int BUTTON_DELAY = 100;
	const sf::Vector2f DEFAULT_COORDS = { WindowWidth - 150, 10.f };
	const sf::Vector2f DEFAULT_SIZE = { 15.f, 20.f };
};
