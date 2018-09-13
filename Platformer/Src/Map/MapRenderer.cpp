#include "MapRenderer.h"

#include <iostream>

MapRenderer::MapRenderer()
	:
	m_mapObject(sf::Quads, 50000)
{
}

void MapRenderer::InitMap(const std::vector<std::string>& textMapFile)
{
	sf::Vertex* ptr = &m_mapObject[0];
	int column = 0;
	int row = 0;

	for (const auto& line : textMapFile)
	{
		for (const auto& letter : line)
		{
			if (letter != ' ')
			{
				int blockNumber = letter - '0';
				SetPosition(row, column, ptr);
				SetTexture(blockNumber, ptr);
				ptr += 4;
			}
			++column;
		}
		++row;
		column = 0;
	}
}

sf::VertexArray & MapRenderer::GetMapObject()
{
	return m_mapObject;
}

void MapRenderer::SetTexture(int blockNr, sf::Vertex* ptr)
{
	ptr->texCoords = sf::Vector2f(blockNr * 16, 0);
	(ptr + 1)->texCoords = sf::Vector2f((blockNr + 1) * 16, 0);
	(ptr + 2)->texCoords = sf::Vector2f((blockNr + 1) * 16, 16);
	(ptr + 3)->texCoords = sf::Vector2f(blockNr * 16, 16);
}

void MapRenderer::SetPosition(int row, int column, sf::Vertex* ptr)
{
	ptr->position = sf::Vector2f(float(BlocksInfo::blockWidth * column), float(BlocksInfo::blockHeight * row));
	(ptr + 1)->position = sf::Vector2f(float(BlocksInfo::blockWidth * (column + 1)), float(BlocksInfo::blockHeight * row));
	(ptr + 2)->position = sf::Vector2f(float(BlocksInfo::blockWidth * (column + 1)), float(BlocksInfo::blockHeight * (row + 1)));
	(ptr + 3)->position = sf::Vector2f(float(BlocksInfo::blockWidth * column), float(BlocksInfo::blockHeight * (row + 1)));
}
