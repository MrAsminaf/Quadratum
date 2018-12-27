#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
public:
	void AddAnimationFrame(const sf::Texture& frameTexture);
	std::size_t GetFramesNumber() const;
	void SetTimeInterval(const float time);
	void Play(sf::Sprite& operationalSprite);
	void DeleteFrame(const unsigned int index);
	void DeleteFrame();
	sf::Texture& GetFrame(const int index);
private:
	std::vector<sf::Texture>m_animationTextures;
	float m_intervalTime = 1.0f;
	sf::Clock m_clock;
};