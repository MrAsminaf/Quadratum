#pragma once
#include "../Window/Window_info.h"
#include "DebugButton.h"
#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>

struct Heart
{
public:
	int id;
	sf::Sprite sprite;
	bool isActive;
};

class UI : public sf::Drawable
{
public:
	UI(sf::RenderWindow* window_ptr, sf::Sprite* player_ptr);
	template<typename T1, typename T2> void Update(std::unordered_map<sf::Vector2<T1>, sf::Rect<T2>>& map);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	void InitHealth();

private:
	sf::RenderWindow* m_mainWindowPtr;
	DebugButton m_debugButton;
	std::array<Heart, 3> m_heartsArray;
	sf::Texture m_heartTexture;
};

template<typename T1, typename T2>
void UI::Update(std::unordered_map<sf::Vector2<T1>, sf::Rect<T2>>& map)
{
	for (Heart& obj : m_heartsArray)
	{
		obj.sprite.setPosition(m_mainWindowPtr->mapPixelToCoords(sf::Vector2i(WindowWidth - (35 * (3 - obj.id)), 10)));
	}
	m_debugButton.Update(map);
}