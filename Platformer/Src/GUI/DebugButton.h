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
	void MakePlayerOriginMarker();
	void UpdatePlayerMarker();
	void UpdateMouseMarker();
	void UpdatePlayerOriginMarker();
	void HidePlayerMarker();
	template<typename T1, typename T2> bool CheckMouseIntersects(std::unordered_map<sf::Vector2<T1>, sf::Rect<T2>>& map);
private:
	sf::RenderWindow* m_mainWindowPtr;
	sf::Sprite* m_playerPtr;
	sf::RectangleShape m_playerMarker;
	sf::RectangleShape m_mouseMarker;// temporary for debug
	sf::RectangleShape m_playerOriginMarker;
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
		UpdatePlayerOriginMarker();
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
	const auto pos = sf::Mouse::getPosition(*m_mainWindowPtr);
	const auto pos2 = m_mainWindowPtr->mapPixelToCoords(pos);
	const int x = int(pos2.x / 16);
	const int y = int(pos2.y / 16);

	m_mouseMarker.setFillColor(sf::Color(0, 0, 255, 100));

	if (map.count(sf::Vector2i(x, y)))
	{
		if (map.at(sf::Vector2i(x, y)).intersects(m_mouseMarker.getGlobalBounds()))
		{
			m_mouseMarker.setFillColor(sf::Color::Yellow);
		}
	}
	if (map.count(sf::Vector2i(x, y + 1)))
	{
		if (map.at(sf::Vector2i(x, y + 1)).intersects(m_mouseMarker.getGlobalBounds()))
		{
			m_mouseMarker.setFillColor(sf::Color::Yellow);
		}
	}
	if (map.count(sf::Vector2i(x, y - 1)))
	{
		if (map.at(sf::Vector2i(x, y - 1)).intersects(m_mouseMarker.getGlobalBounds()))
		{
			m_mouseMarker.setFillColor(sf::Color::Yellow);
		}
	}
	if (map.count(sf::Vector2i(x + 1, y)))
	{
		if (map.at(sf::Vector2i(x + 1, y)).intersects(m_mouseMarker.getGlobalBounds()))
		{
			m_mouseMarker.setFillColor(sf::Color::Yellow);
		}
	}
	if (map.count(sf::Vector2i(x + 1, y + 1)))
	{
		if (map.at(sf::Vector2i(x + 1, y + 1)).intersects(m_mouseMarker.getGlobalBounds()))
		{
			m_mouseMarker.setFillColor(sf::Color::Yellow);
		}
	}

	return false;
}
