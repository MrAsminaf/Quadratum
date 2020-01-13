#include "MapRenderer.h"

#include <iostream>

MapRenderer::MapRenderer()
	:
	m_foregroundVertexArray(sf::Quads, 50000),
	m_backgroundVertexArray(sf::Quads, 50000)
{
}

void MapRenderer::InitMapForeground(const std::vector<std::string>& textMapFile)
{
	sf::Vertex* ptr = &m_foregroundVertexArray[0];
	int column = 0;
	int row = 0;

	for (const auto& line : textMapFile)
	{
		for (const auto& letter : line)
		{
			if (letter != ' ')
			{
				int blockNumber = letter - 'a';
				SetPositionForegroundBlock(row, column, ptr);
				SetTexture(blockNumber, ptr);
				ptr += 4;
			}
			++column;
		}
		++row;
		column = 0;
	}
}

void MapRenderer::InitMapBackground(const std::vector<std::string>& backgroundFile)
{
	sf::Vertex* ptr = &m_backgroundVertexArray[0];
	int column = 0;
	int row = 0;

	for (const auto& line : backgroundFile)
	{
		for (const auto& letter : line)
		{
			if (letter != ' ')
			{
				int blockNumber = letter - 'a';
				SetPositionBackgroundBlock(blockNumber, row, column, ptr);
				SetTexture(blockNumber, ptr);
				ptr += 4;
			}
			++column;
		}
		++row;
		column = 0;
	}
}

sf::VertexArray & MapRenderer::GetForegroundObject()
{
	return m_foregroundVertexArray;
}

sf::VertexArray & MapRenderer::GetBackgroundObject()
{
	return m_backgroundVertexArray;
}

void MapRenderer::SetTexture(int blockNr, sf::Vertex* ptr)
{
	if (blockNr <= 16)
	{
		ptr->texCoords = sf::Vector2f(float(blockNr * 16), 0.f);
		(ptr + 1)->texCoords = sf::Vector2f(float((blockNr + 1) * 16), 0.f);
		(ptr + 2)->texCoords = sf::Vector2f(float((blockNr + 1) * 16), 16.f);
		(ptr + 3)->texCoords = sf::Vector2f(float(blockNr * 16), 16.f);
	}
	else
	{
		ptr->texCoords = sf::Vector2f(float((17 * 16) + 32 * (blockNr - 17)), 0.f);
		(ptr + 1)->texCoords = sf::Vector2f(float((17 * 16) + 32 * (blockNr - 16)), 0.f);
		(ptr + 2)->texCoords = sf::Vector2f(float((17 * 16) + 32 * (blockNr - 16)), 16.f);
		(ptr + 3)->texCoords = sf::Vector2f(float((17 * 16) + 32 * (blockNr - 17)), 16.f);
	}
}

void MapRenderer::SetPositionForegroundBlock(int row, int column, sf::Vertex* ptr)
{
	ptr->position = sf::Vector2f(float(BlocksInfo::blockWidth * column), float(BlocksInfo::blockHeight * row));
	(ptr + 1)->position = sf::Vector2f(float(BlocksInfo::blockWidth * (column + 1)), float(BlocksInfo::blockHeight * row));
	(ptr + 2)->position = sf::Vector2f(float(BlocksInfo::blockWidth * (column + 1)), float(BlocksInfo::blockHeight * (row + 1)));
	(ptr + 3)->position = sf::Vector2f(float(BlocksInfo::blockWidth * column), float(BlocksInfo::blockHeight * (row + 1)));
}

void MapRenderer::SetPositionBackgroundBlock(int blockNr, int row, int column, sf::Vertex * ptr)
{
	int i = (blockNr <= 16 ? 1 : 2);

	ptr->position = sf::Vector2f(float(BlocksInfo::blockWidth * column), float(BlocksInfo::blockHeight * row - 16));
	(ptr + 1)->position = sf::Vector2f(float(BlocksInfo::blockWidth * (column + i)), float(BlocksInfo::blockHeight * row - 16));
	(ptr + 2)->position = sf::Vector2f(float(BlocksInfo::blockWidth * (column + i)), float(BlocksInfo::blockHeight * (row + 1) - 16));
	(ptr + 3)->position = sf::Vector2f(float(BlocksInfo::blockWidth * column), float(BlocksInfo::blockHeight * (row + 1) - 16));
}
