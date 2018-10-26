#include "Clouds.h"

// Fixes to make:
//	- clouds are not displaying properly - they show up as white rectangles

Clouds::Clouds()
{
	// Loads cloud one by one; there are 4 clouds in total so there are 4 loop iterations
	for (int i = 1; i < 5; ++i)
		LoadCloud(i);

	// Manually setting position for clouds; only temporary
	m_cloudSprites[0].setPosition(100, 100);
	m_cloudSprites[1].setPosition(0, 150);
}

void Clouds::Update()
{
	// Move each cloud every frame in x-axis by some amount
	for (auto& cloud : m_cloudSprites)
		cloud.move(sf::Vector2f(0.005, 0));
}

// Inherited function draw
void Clouds::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto& cloud : m_cloudSprites)
		target.draw(cloud, states);
}
 
sf::Sprite& Clouds::GetCloud()
{
	return m_cloudSprites[0];
}

void Clouds::LoadCloud(int cloudNum)
{
	sf::Texture tempTexture;
	tempTexture.loadFromFile("Res/Background/Clouds/cloud" + std::to_string(cloudNum) + ".png");
	m_cloudTextures.push_back(tempTexture);

	sf::Sprite tempSprite;
	tempSprite.setTexture(tempTexture);
	m_cloudSprites.push_back(tempSprite);
}
