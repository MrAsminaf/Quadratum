#pragma once

#include <SFML/Graphics.hpp>

class Clouds : public sf::Drawable
{
public:
	Clouds();
	void Update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite& GetCloud();
private:
	sf::Texture m_cloudTextue;
	sf::Sprite m_cloudSprite;
};
