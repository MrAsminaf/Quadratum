#pragma once

#include "../Window/Window_info.h"
#include "../Texture/BlocksInfo.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <exception>

class DebugButton : public sf::Drawable
{
public:
	DebugButton(sf::RenderWindow* window_ptr, sf::Sprite* player_ptr);
	sf::RectangleShape& GetObject();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	template<typename T1, typename T2> void Update(std::unordered_map<sf::Vector2<T1>, sf::Rect<T2>>& map);
	bool CheckIfClicked();
	void SwitchDebugMode();
private:
	void MakePlayerMarker();
	void MakeMouseMarker();
	void UpdatePlayerMarker();
	void UpdateMouseMarker();
	void HidePlayerMarker();
	template<typename T1, typename T2> bool CheckMouseIntersects(std::unordered_map<sf::Vector2<T1>, sf::Rect<T2>>& map);
private:
	sf::RenderWindow* m_mainWindowPtr;
	sf::Sprite* m_playerPtr;
	sf::RectangleShape m_playerMarker;
	sf::RectangleShape m_mouseMarker; // temporary for debug
	bool isOnDebug;
	const sf::Color COLOR_ON_PRESSED;
	sf::RectangleShape m_debugButtonRectangleShape;
	sf::RectangleShape m_debugPlayerRectangleShape;
	sf::Clock m_delayTimer;
	const int BUTTON_DELAY = 100;
	const sf::Vector2f DEFAULT_COORDS = { WindowWidth - 150, 10.f };
	const sf::Vector2f DEFAULT_SIZE = { 15.f, 20.f };
};

template<typename T1, typename T2>
void DebugButton::Update(std::unordered_map<sf::Vector2<T1>, sf::Rect<T2>>& map)
{
	m_debugButtonRectangleShape.setPosition(m_mainWindowPtr->mapPixelToCoords(sf::Vector2i(DEFAULT_COORDS)));

	if (CheckIfClicked())
		SwitchDebugMode();

	if (isOnDebug)
	{
		UpdatePlayerMarker();
		UpdateMouseMarker();
		CheckMouseIntersects(map);
	}
	else
	{
		HidePlayerMarker();
	}
}

template<typename T1, typename T2>
bool DebugButton::CheckMouseIntersects(std::unordered_map<sf::Vector2<T1>, sf::Rect<T2>>& map)
{
	const auto pos = m_mainWindowPtr->mapPixelToCoords(sf::Mouse::getPosition());
	const int x = int(pos.x / 16);
	const int y = int(pos.y / 16);

	try {
		if (m_mouseMarker.getGlobalBounds().intersects((map.at(sf::Vector2i(x, y)))))
		{
			std::cout << "Intersects" << std::endl;
			return true;
		}
		else
			return false;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << " at: " << x << " " << y << std::endl;
		return false;
	}

}
