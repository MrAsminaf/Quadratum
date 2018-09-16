#pragma once

#include<SFML/Graphics.hpp>

class Camera
{
public:
	Camera();
	sf::View& GetView();
private:
	sf::View m_view;
	sf::Vector2f m_prevViewSize;
};