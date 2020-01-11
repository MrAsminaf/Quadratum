#pragma once

#include "../Texture/BlocksInfo.h"
#include <SFML/Graphics.hpp>
#include <vector>

class MapRenderer
{
public:
	MapRenderer();
	void InitMapForeground(const std::vector<std::string>& foregroundFile);
	void InitMapBackground(const std::vector<std::string>& backgroundFile);
	sf::VertexArray& GetForegroundObject();
	sf::VertexArray& GetBackgroundObject();
private:
	void SetTexture(int blockNr, sf::Vertex* ptr);
	void SetPositionForegroundBlock(int row, int column, sf::Vertex* ptr);
	void SetPositionBackgroundBlock(int blockNr, int row, int column, sf::Vertex* ptr);
private:
	sf::VertexArray m_foregroundVertexArray;
	sf::VertexArray m_backgroundVertexArray;
};