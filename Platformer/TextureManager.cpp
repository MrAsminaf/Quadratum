#include "TextureManager.h"

void TextureManager::LoadTextures(const std::string & filename, const int size)
{
	sf::Texture tempTexture;
	if (!tempTexture.loadFromFile(filename))
	{
		std::cerr << "Could not open " << filename << std::endl;
		return;
	}
	
	const int columns = tempTexture.getSize().x / 16;
	const int rows = tempTexture.getSize().y / 16;

	std::cout << columns << " " << rows << std::endl;

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			sf::Texture texture;
			texture.loadFromFile(filename, sf::IntRect(x*size, y*size, size, size));
			m_textures.push_back(texture);
		}
	}
}

std::vector<sf::Texture>& TextureManager::GetTextures()
{
	return m_textures;
}
