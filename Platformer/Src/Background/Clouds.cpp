#include "Clouds.h"

Clouds::Clouds()
{
	m_cloudTextue.loadFromFile("Res/Background/Clouds/cloud1.png");
	m_cloudSprite.setTexture(m_cloudTextue);
	m_cloudSprite.setPosition(100, 100);
}

void Clouds::Update()
{
	m_cloudSprite.move(sf::Vector2f(0.005, 0));
}

void Clouds::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_cloudSprite, states);
}

sf::Sprite& Clouds::GetCloud()
{
	return m_cloudSprite;
}
