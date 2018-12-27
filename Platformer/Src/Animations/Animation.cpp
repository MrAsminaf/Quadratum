#include "Animation.h"

void Animation::AddAnimationFrame(const sf::Texture & frameTexture)
{
	m_animationTextures.push_back(frameTexture);
}

std::size_t Animation::GetFramesNumber() const
{
	return m_animationTextures.size();
}

void Animation::SetTimeInterval(const float time)
{
	m_intervalTime = time;
}

void Animation::Play(sf::Sprite & operationalSprite)
{
	sf::Time elapsedTime = m_clock.getElapsedTime();

	if (elapsedTime.asSeconds() > m_intervalTime * m_animationTextures.size())
		m_clock.restart();

	for (std::size_t i = 0; i <= m_animationTextures.size() - 1; ++i)
	{
		if (elapsedTime.asSeconds() > m_intervalTime * i && elapsedTime.asSeconds() < m_intervalTime * (i + 1))
		{
			operationalSprite.setTexture(m_animationTextures.at(i));
			break;
		}
	}
}

void Animation::DeleteFrame(const unsigned int index)
{
	auto temp = m_animationTextures.begin() + index;
	m_animationTextures.erase(temp);
}

void Animation::DeleteFrame()
{
	m_animationTextures.pop_back();
}

sf::Texture & Animation::GetFrame(const int index)
{
	return m_animationTextures.at(index);
}
