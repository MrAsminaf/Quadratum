#include "TerrainTextureManager.h"

void TerrainTextureManager::LoadTextures(const std::string & filename, const int size)
{
	if (!m_rawTexture.loadFromFile("Res/" + filename))
	{
		std::cerr << "Could not open " << filename << std::endl;
		return;
	}
	
	const int columns = m_rawTexture.getSize().x / 16;
	const int rows = m_rawTexture.getSize().y / 16;
	
	std::cout << columns << " " << rows << std::endl;

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			sf::Texture texture;
			texture.loadFromFile("Res/" + filename, sf::IntRect(x * size, y * size, size, size));
			m_textures.push_back(texture);
		}
	}
	m_renderStates.texture = &m_rawTexture;
}

std::vector<sf::Texture>& TerrainTextureManager::GetTextures()
{
	return m_textures;
}

sf::RenderStates & TerrainTextureManager::GetRenderStates()
{
	return m_renderStates;
}
