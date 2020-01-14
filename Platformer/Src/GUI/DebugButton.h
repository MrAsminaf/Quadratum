#pragma once

#include "../Window/Window_info.h"
#include "../Texture/BlocksInfo.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class DebugButton : public sf::Drawable
{
public:
	DebugButton(sf::RenderWindow* window_ptr, sf::Sprite* player_ptr);
	sf::RectangleShape& GetObject();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update();
	bool CheckIfClicked();
	void SwitchDebugMode();
private:
	void MakePlayerMarker();
	void UpdatePlayerMarker();
	void HidePlayerMarker();
private:
	sf::RenderWindow* m_mainWindowPtr;
	sf::Sprite* m_playerPtr;
	sf::RectangleShape m_playerMarker;
	bool isOnDebug;
	const sf::Color COLOR_ON_PRESSED;
	sf::RectangleShape m_debugButtonRectangleShape;
	sf::RectangleShape m_debugPlayerRectangleShape;
	sf::Clock m_delayTimer;
	const int BUTTON_DELAY = 100;
	const sf::Vector2f DEFAULT_COORDS = { WindowWidth - 150, 10.f };
	const sf::Vector2f DEFAULT_SIZE = { 15.f, 20.f };
};
