#pragma once
#include "Window/Window_info.h"
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
	UI();
	void Update(const sf::RenderWindow& main_window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	void InitHealth();

private:
	std::array<Heart, 3> m_heartsArray;
	sf::Texture m_heartTexture;
};

