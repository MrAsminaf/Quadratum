#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Clouds : public sf::Drawable
{
public:
	Clouds();
	void Update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite& GetCloud();
private:
	void LoadCloud(int cloudNum);
private:
	std::vector<sf::Texture>m_cloudTextures;
	std::vector<sf::Sprite>m_cloudSprites;
};
