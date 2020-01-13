#include "Clouds.h"
#include <random>

Clouds::Clouds()
{
	// Loads cloud one by one; there are 4 clouds in total so there are 4 loop iterations
	for (int i = 1; i < 5; ++i)
		LoadCloudResources(i);


	// Init clouds
	for (int i = 0 ; i < 15; ++i)
	{
		Cloud cloud;
		cloud.sprite.setTexture(m_cloudTextures[i % m_cloudTextures.size()]);
		cloud.velocity = float(GetRandomVelocity());
		cloud.sprite.setPosition(float(GetRandomXPosition()), float(GetRandomYPosition()));
		m_clouds.push_back(cloud);
	}
}

void Clouds::Update(const sf::RenderWindow& window)
{
	// Move each cloud every frame on x-axis by some amount
	for (auto& cloud : m_clouds)
	{
		cloud.sprite.move(sf::Vector2f(cloud.velocity, 0.f));
		
		// If cloud has gone out of window boundaries:
		if (window.mapCoordsToPixel(cloud.sprite.getPosition()).x > WindowWidth)
		{
			// Move cloud back to the left side of the window
			auto newPos = window.mapPixelToCoords(sf::Vector2i(0, GetRandomYPosition()));
			cloud.sprite.setPosition(sf::Vector2f(newPos.x - cloud.sprite.getTexture()->getSize().x, newPos.y));
		}
	}
}


// Inherited function-draw
void Clouds::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (const auto& cloud : m_clouds)
		target.draw(cloud.sprite, states);
}
 

// Get selected cloud sprite
sf::Sprite& Clouds::GetSprite(int index)
{
	return m_clouds[index].sprite;
}

void Clouds::LoadCloudResources(int cloudNum)
{
	m_cloudTextures.at(cloudNum - 1).loadFromFile("Res/Background/Clouds/cloud" + std::to_string(cloudNum) + ".png");
	m_cloudSprites.at(cloudNum - 1).setTexture(m_cloudTextures.at(cloudNum - 1));
}


// Function for randomizing cloud velocities
double Clouds::GetRandomVelocity() const
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<> vel(0.001f, 0.02f);

	return vel(rng);
}


// Function for randomizing cloud position on Y-axis
int Clouds::GetRandomYPosition() const
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<> height(0, 250);

	return height(rng);
}

// Function for randomizing cloud position on X-axis
int Clouds::GetRandomXPosition() const
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<> pos(-300, 300);

	return pos(rng);
}


// Returns the .size() of private member: m_clouds
std::size_t Clouds::GetTotalNumberOfClouds() const
{
	return m_clouds.size();
}
