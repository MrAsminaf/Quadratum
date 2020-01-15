#pragma once
#include "../Window/Window_info.h"
#include "DebugButton.h"
#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>

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
	void Update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	void InitHealth();

private:
	sf::RenderWindow* m_mainWindowPtr;
	DebugButton m_debugButton;
	std::array<Heart, 3> m_heartsArray;
	sf::Texture m_heartTexture;
};

