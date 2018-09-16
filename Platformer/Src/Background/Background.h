#pragma once

#include <SFML/Graphics.hpp>

class Background : public sf::Drawable
{
public:
	Background();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update(const sf::RenderWindow& window, const float playerHorizontalVelocity);
private:
	sf::Texture m_skyTexture;
	sf::Sprite m_skySprite;
	sf::Texture m_farMountainsTexture;
	sf::Sprite m_farMountainsSprite;
	sf::Texture m_closeMountainsTexture;
	sf::Sprite m_closeMountainsSprite;
	sf::Texture m_grassTexture;
	sf::Sprite m_grassSprite;
};
