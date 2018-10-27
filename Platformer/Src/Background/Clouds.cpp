#include "Clouds.h"
#include <random>


// Console I/O and <exception> for debuging purposes:
#include <iostream>
#include <exception>

Clouds::Clouds()
{
	// Loads cloud one by one; there are 4 clouds in total so there are 4 loop iterations
	for (int i = 1; i < 5; ++i)
		LoadCloudResources(i);


	// Init clouds
	for (int i = 0 ; i < 15; ++i)
	{
		Cloud cloud;
		std::cout << m_cloudTextures.size() << std::endl;
		cloud.sprite.setTexture(m_cloudTextures[i%4]);
		cloud.velocity = GetRandomVelocity();
		cloud.sprite.setPosition(GetRandomXPosition(), GetRandomYPosition());
		m_clouds.push_back(cloud);
	}
}

void Clouds::Update()
{
	// Move each cloud every frame in x-axis by some amount
	for (auto& cloud : m_clouds)
		cloud.sprite.move(sf::Vector2f(0.005, 0));
}


// Inherited function-draw
void Clouds::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (const auto& cloud : m_clouds)
		target.draw(cloud.sprite, states);
}
 

// Get selected cloud sprite
sf::Sprite& Clouds::GetCloud(int index)
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
	std::uniform_real_distribution<> vel(0.001f, 0.01f);

	return vel(rng);
}


// Function for randomizing cloud position in Y-axis
int Clouds::GetRandomYPosition() const
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<> height(0, 250);

	return height(rng);
}

// Function for randomizing cloud position in X-axi 
int Clouds::GetRandomXPosition() const
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<> pos(-300, 300);

	return pos(rng);
}


// Returns the .size() of private member: m_clouds
int Clouds::GetTotalNumberOfClouds() const
{
	return m_clouds.size();
}
