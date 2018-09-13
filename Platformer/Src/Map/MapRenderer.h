#pragma once

#include "Texture/BlocksInfo.h"
#include <SFML/Graphics.hpp>
#include <vector>

class MapRenderer
{
public:
	MapRenderer();
	void InitMap(const std::vector<std::string>& textMapFile);
	sf::VertexArray& GetMapObject();
private:
	void SetTexture(int blockNr, sf::Vertex* ptr);
	void SetPosition(int row, int column, sf::Vertex* ptr);
private:
	sf::VertexArray m_mapObject;
};