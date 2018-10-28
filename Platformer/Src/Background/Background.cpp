#include "Background.h"

Background::Background()
{
	m_skyTexture.loadFromFile("Res/Background/bg4.png");
	m_skySprite.setTexture(m_skyTexture);
	m_skySprite.setPosition(0, 0);
	m_skySprite.setScale(2, 2);
	
	m_farMountainsTexture.loadFromFile("Res/Background/bg3.png");
	m_farMountainsSprite.setTexture(m_farMountainsTexture);
	m_farMountainsSprite.setPosition(-500, 0);
	m_farMountainsSprite.setScale(2, 2);

	m_closeMountainsTexture.loadFromFile("Res/Background/bg2.png");
	m_closeMountainsSprite.setTexture(m_closeMountainsTexture);
	m_closeMountainsSprite.setPosition(-500, 0);
	m_closeMountainsSprite.setScale(2, 2);

	m_grassTexture.loadFromFile("Res/Background/bg1.png");
	m_grassSprite.setTexture(m_grassTexture);
	m_grassSprite.setPosition(-500, 0);
	m_grassSprite.setScale(2, 2);
}

void Background::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_skySprite, states);
	target.draw(m_clouds, states);
	target.draw(m_farMountainsSprite, states);
	target.draw(m_closeMountainsSprite, states);
	target.draw(m_grassSprite, states);
}

void Background::Update(const sf::RenderWindow& window, float playerHorizontalVelocity)
{
	auto pos = window.mapPixelToCoords(sf::Vector2i(0, 0));
	m_skySprite.setPosition(pos);

	m_farMountainsSprite.setPosition(m_farMountainsSprite.getPosition().x, pos.y);
	m_farMountainsSprite.move(playerHorizontalVelocity / 1.10f, 0);

	m_closeMountainsSprite.setPosition(m_closeMountainsSprite.getPosition().x, pos.y);
	m_closeMountainsSprite.move(playerHorizontalVelocity / 1.15f, 0);

	m_grassSprite.setPosition(m_grassSprite.getPosition().x, pos.y);
	m_grassSprite.move(playerHorizontalVelocity / 1.20f, 0);

	m_clouds.Update(window);
	for (int i = 0; i < m_clouds.GetTotalNumberOfClouds(); ++i)
		m_clouds.GetCloud(i).move(playerHorizontalVelocity / 1.05f, 0);
}
